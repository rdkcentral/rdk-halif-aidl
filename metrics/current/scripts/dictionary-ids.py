#!/usr/bin/env python3

#/**
# * Copyright 2026 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
# * SPDX-License-Identifier: Apache-2.0
# */

"""Field identity and declaration checking for the metrics HAL.

    scripts/dictionary-ids.py             check - exits non-zero on failure
    scripts/dictionary-ids.py --sync      rewrite hfp-metrics.yaml from the dictionary
    scripts/dictionary-ids.py --emit-aidl regenerate MetricGroup.aidl / MetricId.aidl

RUN THIS BEFORE COMMITTING any change to the dictionary or the declaration. It
is a pre-commit step for the engineer making the change, deliberately not a CI
gate: the person editing the dictionary is the one who should see the generated
diff and review it, rather than discovering it after the fact on a PR.

IDENTITY IS DERIVED, NOT ALLOCATED
----------------------------------
A field's id is a hash of the contract that governs how a consumer may read it:

    id = first 8 bytes of SHA-256("<domain>.<element>.<field>|<unit>|<kind>")

Nothing allocates it, so there is no registry to consult, no counter to advance
and no collision to resolve when two people add a field on separate branches.
Anyone can compute it offline from the dictionary alone.

What that buys is a check the name alone cannot make. A SoC that declares
`decode_latency_sum_us` but populates milliseconds still matches by name, and
the consumer silently reports figures a thousand times wrong. A `current`
sample quietly reclassified as a `counter` gets differenced and produces
nonsense. Both change the id, so both become a hard mismatch at the client
instead of a wrong number.

Two rules that a counter-allocated id needs a lockfile and a checker to police
are facts about this encoding instead:

  * An id is never reused, because the same id means the same
    name + unit + kind, which is the same field.
  * `unit` and `kind` cannot change under a stable id, because changing either
    produces a different id.

Deliberately NOT hashed: the instance segment (`.0` and `.1` are the same field
on different sources), `writable` (a per-product permission, not the field's
meaning), the prose (a typo fix must not churn the id), and `dictionaryVersion`
(every id would churn on every revision, which defeats the point).

The id is written into each HFP entry so the entry is self-describing and a
client checks without a second lookup. The dictionary stays the source of
truth; deleting an id regenerates it, so a rename or a unit change flows
through on the next --sync.

WHAT STILL NEEDS CHECKING
-------------------------
The hash removes the id rules; it does not remove these:

  * Every name a product declares must exist in the dictionary. There is no
    SoC-private namespace, so no consumer grows per-SoC code.
  * A declared unit/kind must match the dictionary's. The declaration cannot
    redefine a field, only choose whether to serve it.
  * A derived field cannot be declared without the field it derives from.
    Declaring `freeze_duration_ms` without `frames_repeated_missing_frame` is
    not a partial capability, it is an undeliverable declaration - and it
    passes every other check because both names are valid.
"""

from __future__ import annotations

import argparse
import hashlib
import re
import struct
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
DICT = ROOT / "docs/av_field_dictionary.md"
HFP = ROOT / "hfp-metrics.yaml"

# "### `av.video_sink`" or "### `health.poll`"
ELEMENT_HEADING = re.compile(r"^###\s+`([a-z][a-z0-9_]*\.[a-z][a-z0-9_]*)`\s*$")
# "| `frames_decoded` | int64 · frames · `counter` | **Driver** | Definition… |"
FIELD_ROW = re.compile(
    r"^\|\s*`([a-z][a-z0-9_]*)`\s*\|\s*int64[^|·]*·\s*([^\s·]+)\s*·\s*`([a-z_]+)`([^|]*)\|"
    r"\s*([^|]*)\|\s*(.*?)\s*\|\s*$"
)

# A field computed from another cannot be served without its input.
DERIVED_FROM = {
    "av.video_sink.freeze_duration_ms": "av.video_sink.frames_repeated_missing_frame",
    "av.video_sink.freeze_event_count": "av.video_sink.frames_repeated_missing_frame",
    "av.video_sink.max_freeze_duration_ms": "av.video_sink.frames_repeated_missing_frame",
    "av.clock.sync_max_abs_offset_ms": "av.clock.sync_offset_ms",
    "av.clock.sync_time_over_threshold_ms": "av.clock.sync_threshold_ms",
}

# The dictionary renders units for humans; the declaration uses ASCII.
UNIT_ALIASES = {"µs": "us"}


def field_id(path: str, unit: str, kind: str) -> int:
    """Content-derived identity. `path` is <domain>.<element>.<field>."""
    digest = hashlib.sha256(f"{path}|{unit}|{kind}".encode("utf-8")).digest()
    return struct.unpack(">q", digest[:8])[0] & 0x7FFFFFFFFFFFFFFF


def parse_dictionary(text: str) -> dict:
    """{ "<domain>.<element>.<field>": {unit, kind, writable, description} }"""
    entries, element = {}, None
    for line in text.splitlines():
        heading = ELEMENT_HEADING.match(line)
        if heading:
            element = heading.group(1)
            continue
        if element is None:
            continue
        row = FIELD_ROW.match(line)
        if not row:
            continue
        name, unit, kind, kind_tail, _provider, description = row.groups()
        entries[f"{element}.{name}"] = {
            "unit": UNIT_ALIASES.get(unit, unit),
            "kind": kind,
            "writable": "writable" in kind_tail.lower(),
            "description": description.strip(),
        }
    return entries


def strip_markdown(text: str) -> str:
    """Dictionary prose is Markdown; a YAML comment is plain text."""
    text = re.sub(r"\*\*(.+?)\*\*", r"\1", text)
    text = re.sub(r"\*(.+?)\*", r"\1", text)
    text = re.sub(r"`(.+?)`", r"\1", text)
    return text.replace("→", "->").replace("Σ", "sum of").replace("≥", ">=")


def wrap(text: str, width: int, indent: str) -> list[str]:
    lines, current = [], ""
    for word in text.split():
        if current and len(current) + 1 + len(word) > width:
            lines.append(f"{indent}{current}")
            current = word
        else:
            current = f"{current} {word}".strip()
    if current:
        lines.append(f"{indent}{current}")
    return lines


def declared_fields(hfp_text: str) -> list[tuple[int, str, str, dict]]:
    """Every declared field line: (line_no, domain, element, parsed entry)."""
    found, domain, element = [], None, None
    for n, line in enumerate(hfp_text.splitlines()):
        m = re.match(r"^\s*-\s+domain:\s*(\S+)", line)
        if m:
            domain = m.group(1)
            continue
        m = re.match(r"^\s*-\s+element:\s*(\S+)", line)
        if m:
            element = m.group(1)
            continue
        m = re.match(
            r"^(\s*)-\s*\{\s*name:\s*([a-z][a-z0-9_]*)\s*,\s*unit:\s*([a-z]+)\s*,"
            r"\s*kind:\s*([a-z_]+)\s*(.*?)\}\s*$",
            line,
        )
        if m and domain and element:
            indent, name, unit, kind, rest = m.groups()
            found.append(
                (n, domain, element,
                 {"indent": indent, "name": name, "unit": unit, "kind": kind,
                  "rest": rest, "line": line})
            )
    return found


def sync(dictionary: dict, hfp_text: str) -> str:
    """Write the id and the dictionary description onto every declared field."""
    out, decl = [], {d[0]: d for d in declared_fields(hfp_text)}
    lines = hfp_text.splitlines()
    skip_comment_block = False

    for n, line in enumerate(lines):
        # Drop the previously generated comment block; it is regenerated below.
        if line.strip().startswith("#") and skip_comment_block:
            continue
        skip_comment_block = False

        if n not in decl:
            out.append(line)
            continue

        _, domain, element, f = decl[n]
        path = f"{domain}.{element}.{f['name']}"
        entry = dictionary.get(path)
        if entry is None:
            out.append(line)
            continue

        indent = f["indent"]
        if out and out[-1].strip():
            out.append("")
        out.append(f"{indent}# {f['name']}: " + strip_markdown(entry["description"])[:0])
        # name-led description, wrapped under the name
        body = strip_markdown(entry["description"])
        first, *rest_words = body.split()
        head = f"{indent}# {f['name']}: "
        wrapped = wrap(body, 96 - len(head), "")
        out[-1] = head + wrapped[0]
        for extra in wrapped[1:]:
            out.append(f"{indent}#{' ' * (len(f['name']) + 3)}{extra}")

        writable = ", writable: true" if entry["writable"] else ""
        fid = field_id(path, entry["unit"], entry["kind"])
        out.append(
            f"{indent}- {{ name: {f['name']}, unit: {entry['unit']}, "
            f"kind: {entry['kind']}{writable}, id: 0x{fid:016x} }}"
        )
    return "\n".join(out) + "\n"


AIDL_HEADER = """/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.metrics;
"""

# Each group owns a 1000-block, so a metric's group is `value / 1000` and two
# people adding to different groups can never collide on an ordinal.
GROUP_STRIDE = 1000


def enum_name(path: str) -> str:
    """av.video_decoder.frames_decoded -> AV_VIDEO_DECODER_FRAMES_DECODED

    A direct transliteration of the declared name, so the enum and the string
    are visibly the same thing and neither has to be looked up to read the
    other."""
    return path.replace(".", "_").upper()


def groups_of(dictionary: dict) -> dict:
    """{ "<domain>.<element>": [(field, entry), ...] } in dictionary order."""
    grouped: dict = {}
    for path, entry in dictionary.items():
        element, field = path.rsplit(".", 1)
        grouped.setdefault(element, []).append((field, entry))
    return grouped


def emit_group_enum(dictionary: dict) -> str:
    grouped = groups_of(dictionary)
    lines = [AIDL_HEADER, """
/**
 *  @brief     The metric groups this interface can serve.
 *
 *  GENERATED from docs/av_field_dictionary.md by scripts/dictionary-ids.py.
 *  Do not hand-edit - add the element to the dictionary and re-run --emit-aidl.
 *
 *  A group is one <domain>.<element>. Extending the interface with a new group
 *  is an enum value appended here, which is a source-compatible change: a
 *  consumer that does not know a value skips it.
 *
 *  Each group owns a 1000-block of MetricId values, so a metric's group is
 *  `metricId / 1000` and two groups can never collide on an ordinal.
 */
@VintfStability
@Backing(type="int")
enum MetricGroup {
"""]
    for i, element in enumerate(grouped):
        lines.append(f"    /** `{element}` - MetricId values {i * GROUP_STRIDE}"
                     f"..{i * GROUP_STRIDE + GROUP_STRIDE - 1}. */")
        lines.append(f"    {enum_name(element)} = {i},")
        lines.append("")
    lines.append("}")
    return "\n".join(lines).replace("\n\n}", "\n}")


def emit_metric_enum(dictionary: dict) -> str:
    grouped = groups_of(dictionary)
    lines = [AIDL_HEADER, """
/**
 *  @brief     Every metric this interface can serve, keyed by group block.
 *
 *  GENERATED from docs/av_field_dictionary.md by scripts/dictionary-ids.py.
 *  Do not hand-edit - add the field to the dictionary and re-run --emit-aidl.
 *
 *  The name is a direct transliteration of the declared name, so
 *  AV_VIDEO_DECODER_FRAMES_DECODED and `av.video_decoder.frames_decoded` are
 *  visibly the same thing.
 *
 *  Values are banded by group: `metricId / 1000` is the MetricGroup ordinal.
 *  Extending is appending inside a band; an existing value never moves,
 *  because a consumer that cached the mapping would otherwise read a
 *  different field under the value it already knows.
 *
 *  A value's presence here says the interface can carry it. Whether a given
 *  product serves it is `getGroupMetrics()` at runtime - a product that cannot
 *  measure a figure omits it rather than returning 0.
 */
@VintfStability
@Backing(type="int")
enum MetricId {
"""]
    for i, (element, fields) in enumerate(grouped.items()):
        lines.append(f"    /* ---- {element} ---- */")
        lines.append("")
        for j, (field, entry) in enumerate(fields):
            unit = entry["unit"]
            kind = entry["kind"]
            wr = ", writable" if entry["writable"] else ""
            lines.append(f"    /** {unit} - {kind}{wr}. `{element}.{field}` */")
            lines.append(f"    {enum_name(f'{element}.{field}')} = {i * GROUP_STRIDE + j},")
            lines.append("")
    lines.append("}")
    return "\n".join(lines).replace("\n\n}", "\n}")


def check(dictionary: dict, hfp_text: str) -> list[str]:
    problems, declared = [], set()

    for n, domain, element, f in declared_fields(hfp_text):
        path = f"{domain}.{element}.{f['name']}"
        declared.add(path)
        entry = dictionary.get(path)
        if entry is None:
            problems.append(
                f"{HFP.name}:{n + 1}: '{path}' is not defined in the dictionary. "
                f"There is no SoC-private namespace - add a dictionary entry first."
            )
            continue
        if f["unit"] != entry["unit"] or f["kind"] != entry["kind"]:
            problems.append(
                f"{HFP.name}:{n + 1}: '{path}' declared as "
                f"{f['unit']}/{f['kind']}, dictionary defines {entry['unit']}/{entry['kind']}. "
                f"A declaration chooses whether to serve a field; it cannot redefine one."
            )
            continue
        expected = field_id(path, entry["unit"], entry["kind"])
        m = re.search(r"id:\s*0x([0-9a-f]{16})", f["rest"])
        if m and int(m.group(1), 16) != expected:
            problems.append(
                f"{HFP.name}:{n + 1}: '{path}' carries id 0x{m.group(1)}, "
                f"computed 0x{expected:016x}. Delete the id to regenerate it."
            )

    for derived, source in DERIVED_FROM.items():
        if derived in declared and source not in declared:
            problems.append(
                f"{HFP.name}: '{derived}' is declared but '{source}', which it is "
                f"derived from, is not. That declaration cannot be satisfied."
            )
    return problems


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--sync", action="store_true",
                        help="rewrite hfp-metrics.yaml from the dictionary")
    parser.add_argument("--emit-aidl", action="store_true",
                        help="regenerate MetricGroup.aidl and MetricId.aidl")
    args = parser.parse_args()

    dictionary = parse_dictionary(DICT.read_text(encoding="utf-8"))
    if not dictionary:
        print(f"error: no field definitions parsed from {DICT}", file=sys.stderr)
        return 2
    hfp_text = HFP.read_text(encoding="utf-8")

    if args.emit_aidl:
        aidl = ROOT / "com/rdk/hal/metrics"
        (aidl / "MetricGroup.aidl").write_text(emit_group_enum(dictionary), encoding="utf-8")
        (aidl / "MetricId.aidl").write_text(emit_metric_enum(dictionary), encoding="utf-8")
        print(f"emitted MetricGroup.aidl ({len(groups_of(dictionary))} groups) "
              f"and MetricId.aidl ({len(dictionary)} metrics)")

    if args.sync:
        HFP.write_text(sync(dictionary, hfp_text), encoding="utf-8")
        print(f"synced {HFP.name} against {len(dictionary)} dictionary entries")
        hfp_text = HFP.read_text(encoding="utf-8")

    problems = check(dictionary, hfp_text)
    for problem in problems:
        print(f"error: {problem}", file=sys.stderr)
    if problems:
        print(f"\n{len(problems)} problem(s).", file=sys.stderr)
        return 1

    print(f"ok: {len(declared_fields(hfp_text))} declared fields resolve against "
          f"{len(dictionary)} dictionary entries; every id matches.")
    return 0


if __name__ == "__main__":
    sys.exit(main())

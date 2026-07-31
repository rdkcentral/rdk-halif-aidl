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

"""Generator and checker for the HAL Field Dictionary (HFD).

    scripts/dictionary-ids.py             check - exits non-zero on failure
    scripts/dictionary-ids.py --generate  regenerate everything from the HFD

RUN --generate BEFORE COMMITTING any change to the dictionary. It is a
pre-commit step for the engineer making the change, deliberately not a CI gate:
the person editing a field definition is the one who should see the generated
diff and review it, rather than discovering it later on a PR.

THE HFD IS THE ONLY PLACE A FIELD IS AUTHORED
---------------------------------------------
`av-field-dictionary.yaml` is the HAL Field Dictionary - what every declared
field means. It is a declarative file, not prose, because everything below is
generated from it and a generator must not have to parse meaning out of a
document that people edit by hand.

    av-field-dictionary.yaml                      the HFD - authored
        |
        +-> docs/av_field_dictionary.md           human-readable reference
        +-> com/rdk/hal/metrics/MetricNames.aidl  name + contract id constants
        +-> hfp-metrics.yaml                      ids, descriptions
        +-> docs/metrics_requirements.md          one requirement per field

**HFD defines, HFP declares, the HAL carries.**

FIELD CONTRACT ID
-----------------
Every field carries an id derived from the contract that governs how a consumer
may read it:

    id = first 8 bytes of SHA-256("<domain>.<element>.<field>|<unit>|<kind>")

Nothing allocates it, so there is no registry to consult, no counter to advance
and nothing to resolve when two people add a field on separate branches. Anyone
computes it offline from the HFD alone.

It buys a check no key can make on its own. A key - a name or an ordinal -
stays valid while the meaning underneath it changes: a product that declares
`decode_latency_sum_us` but populates milliseconds still matches by name, and
the consumer reports figures a thousand times wrong; a `current` sample
reclassified as a `counter` gets differenced into nonsense. Because `unit` and
`kind` are hashed, both change the id, so a consumer comparing against the id it
was built with sees a hard mismatch instead of a wrong number.

Two rules an allocated id would need policing to hold are properties of this
encoding instead: an id is never reused, because the same id means the same
name, unit and kind - the same field; and `unit` and `kind` cannot change under
a stable id, because changing either produces a different id.

Deliberately NOT hashed: the instance segment (`.0` and `.1` are the same field
on different sources), `writable` (a per-product permission, not the field's
meaning), the description (a typo fix must not churn the id), and
`dictionaryVersion` (every id would churn on every revision).

WHAT STILL NEEDS CHECKING
-------------------------
The id removes the identity rules; it does not remove these:

  * Every name a product declares must exist in the HFD. There is no
    SoC-private namespace, so no consumer grows per-SoC code.
  * A declared unit/kind must match the HFD's. A declaration chooses whether to
    serve a field; it cannot redefine one.
  * A derived field cannot be declared without the field it derives from.
    Declaring `freeze_duration_ms` without `frames_repeated_missing_frame` is
    not a partial capability, it is an undeliverable declaration - and it passes
    every other check because both names are valid.
"""

from __future__ import annotations

import argparse
import hashlib
import re
import struct
import sys
from pathlib import Path

import yaml

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
HFD = ROOT / "av-field-dictionary.yaml"
HFP = ROOT / "hfp-metrics.yaml"
DICT_MD = ROOT / "docs/av_field_dictionary.md"
NAMES = ROOT / "com/rdk/hal/metrics/MetricNames.aidl"
REQS = ROOT / "docs/metrics_requirements.md"

# The HFD renders units for humans; a declaration uses ASCII.
UNIT_ALIASES = {"µs": "us"}

# How each kind may be read. Stated once, emitted into every requirement.
KIND_RULES = {
    "counter": "cumulative since source creation, monotonically non-decreasing, "
               "and never reset on flush or seek",
    "current": "a live sample re-read each poll, absolute, and never summed",
    "high_water": "a monotone maximum since source creation, absolute",
    "config": "the present value of a tunable, absolute",
}

GENERATED = ("GENERATED from av-field-dictionary.yaml by "
             "scripts/dictionary-ids.py. Do not hand-edit.")

LICENCE = """/*
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
 */"""


def field_id(path: str, unit: str, kind: str) -> int:
    """Content-derived identity. `path` is <domain>.<element>.<field>."""
    digest = hashlib.sha256(f"{path}|{unit}|{kind}".encode("utf-8")).digest()
    return struct.unpack(">q", digest[:8])[0] & 0x7FFFFFFFFFFFFFFF


def load_hfd() -> tuple[dict, dict]:
    """Returns (entries, derived_from), preserving authored order."""
    doc = yaml.safe_load(HFD.read_text(encoding="utf-8"))
    entries, derived = {}, {}
    for domain in doc["hfd"]["domains"]:
        for element in domain["elements"]:
            for f in element["fields"]:
                path = f"{domain['domain']}.{element['element']}.{f['name']}"
                entries[path] = {
                    "domain": domain["domain"],
                    "element": element["element"],
                    "field": f["name"],
                    "unit": UNIT_ALIASES.get(f["unit"], f["unit"]),
                    "kind": f["kind"],
                    "writable": bool(f.get("writable", False)),
                    "provider": f.get("provider", "Driver"),
                    "description": f["description"].strip(),
                }
                if f.get("derivedFrom"):
                    derived[path] = f["derivedFrom"]
    return entries, derived


def strip_markdown(text: str) -> str:
    text = re.sub(r"\*\*(.+?)\*\*", r"\1", text)
    text = re.sub(r"\*(.+?)\*", r"\1", text)
    text = re.sub(r"`(.+?)`", r"\1", text)
    return text.replace("→", "->").replace("Σ", "sum of").replace("≥", ">=")


def wrap(text: str, width: int) -> list[str]:
    lines, current = [], ""
    for word in text.split():
        if current and len(current) + 1 + len(word) > width:
            lines.append(current)
            current = word
        else:
            current = f"{current} {word}".strip()
    if current:
        lines.append(current)
    return lines


def const_name(path: str) -> str:
    """av.video_sink.frames_presented -> AV_VIDEO_SINK_FRAMES_PRESENTED"""
    return path.replace(".", "_").upper()


def req_id(path: str) -> str:
    return "HAL.METRICS.FIELD." + path.upper()


# --------------------------------------------------------------------------
# Generators
# --------------------------------------------------------------------------

def emit_names(entries: dict) -> str:
    out = [LICENCE, "package com.rdk.hal.metrics;", "", "/**",
           " *  @brief     Declared metric names and their contract ids.",
           " *",
           f" *  {GENERATED}",
           " *  Add the field to the HFD and re-run --generate.",
           " *",
           " *  A name constant spares a client a string literal it can mistype; the",
           " *  matching `_ID` is what it compares against `MetricFieldInfo.id` to confirm",
           " *  the product means the same thing by that name. A name that still matches",
           " *  while the unit or kind changed underneath is the failure these ids exist",
           " *  to catch.",
           " *",
           " *  These are the three-segment `<domain>.<element>.<field>` forms. A runtime",
           " *  name carries the instance too - `av.video_decoder.0.frames_decoded` - so a",
           " *  client composes the instance in, or matches on the trailing segments.",
           " *",
           " *  Constants only; this interface publishes no service and declares no methods.",
           " */", "@VintfStability", "interface MetricNames", "{"]
    last_element = None
    for path, e in entries.items():
        element = f"{e['domain']}.{e['element']}"
        if element != last_element:
            out.append(f"\n    /* ---- {element} ---- */\n")
            last_element = element
        writable = ", writable" if e["writable"] else ""
        out.append(f"    /** {e['unit']} - {e['kind']}{writable} */")
        out.append(f'    const @utf8InCpp String {const_name(path)} = "{path}";')
        out.append(f"    const long {const_name(path)}_ID = "
                   f"{field_id(path, e['unit'], e['kind'])};\n")
    out.append("}")
    return "\n".join(out) + "\n"


def emit_requirements(entries: dict, derived: dict) -> str:
    out = ["# Metrics Field Requirements", "",
           f"<!-- {GENERATED} -->", "",
           "One requirement per declared field, generated from the HAL Field "
           "Dictionary. Each is independently testable, and its identifier is "
           "derived from the field path, so it is stable for as long as the "
           "field is.", "",
           "A product must satisfy a requirement only for the fields it declares "
           "in `hfp-metrics.yaml`. A field it does not declare is absent at "
           "runtime rather than served as zero.", "",
           "| Requirement | Field | Contract | Definition |", "|---|---|---|---|"]
    for path, e in entries.items():
        rule = KIND_RULES.get(e["kind"], "")
        fid = field_id(path, e["unit"], e["kind"])
        access = "read-write" if e["writable"] else "read-only"
        extra = (f" Derived from `{derived[path]}`, which the product must also "
                 f"declare." if path in derived else "")
        contract = (f"`{e['unit']}` · `{e['kind']}` · {access}<br>id "
                    f"`0x{fid:016x}`")
        definition = f"Shall be reported as {rule}.{extra} {e['description']}"
        out.append(f"| **{req_id(path)}** | `{path}` | {contract} | {definition} |")
    return "\n".join(out) + "\n"


def emit_dictionary_md(entries: dict) -> str:
    """The human-readable reference, generated from the HFD."""
    head = DICT_MD.read_text(encoding="utf-8") if DICT_MD.exists() else ""
    preamble = (head.split("## Fields")[0] if "## Fields" in head
                else "# AV Domain Field Dictionary\n\n")
    tail = ""
    for marker in ("## Episodic Conditions", "## Retired", "## Accuracy"):
        if marker in head:
            tail = head[head.index(marker):]
            break

    out = [preamble.rstrip("\n"), "", f"<!-- Field tables: {GENERATED} -->", "",
           "## Fields"]
    last_element = None
    for path, e in entries.items():
        element = f"{e['domain']}.{e['element']}"
        if element != last_element:
            out += ["", f"### `{element}`", "",
                    "| Field | Type · unit · kind | Provider | id "
                    "| Definition and population rule |",
                    "|---|---|---|---|---|"]
            last_element = element
        fid = field_id(path, e["unit"], e["kind"])
        w = " · **writable**" if e["writable"] else ""
        out.append(f"| `{e['field']}` | int64 · {e['unit']} · `{e['kind']}`{w} "
                   f"| **{e['provider']}** | `0x{fid:016x}` | {e['description']} |")
    out += ["", tail.rstrip("\n"), ""]
    return "\n".join(out)


# --------------------------------------------------------------------------
# HFP sync
# --------------------------------------------------------------------------

def declared_fields(hfp_text: str) -> list[tuple[int, str, str, dict]]:
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
            r"\s*kind:\s*([a-z_]+)\s*(.*?)\}\s*$", line)
        if m and domain and element:
            indent, name, unit, kind, rest = m.groups()
            found.append((n, domain, element,
                          {"indent": indent, "name": name, "unit": unit,
                           "kind": kind, "rest": rest, "line": line}))
    return found


def sync_hfp(entries: dict, hfp_text: str) -> str:
    out, decl = [], {d[0]: d for d in declared_fields(hfp_text)}
    lines, skip = hfp_text.splitlines(), False
    for n, line in enumerate(lines):
        if line.strip().startswith("#") and skip:
            continue
        skip = False
        if n not in decl:
            out.append(line)
            continue
        _, domain, element, f = decl[n]
        path = f"{domain}.{element}.{f['name']}"
        entry = entries.get(path)
        if entry is None:
            out.append(line)
            continue
        indent = f["indent"]
        if out and out[-1].strip():
            out.append("")
        body = strip_markdown(entry["description"])
        head = f"{indent}# {f['name']}: "
        wrapped = wrap(body, 96 - len(head))
        out.append(head + wrapped[0])
        for extra in wrapped[1:]:
            out.append(f"{indent}#{' ' * (len(f['name']) + 3)}{extra}")
        writable = ", writable: true" if entry["writable"] else ""
        fid = field_id(path, entry["unit"], entry["kind"])
        out.append(f"{indent}- {{ name: {f['name']}, unit: {entry['unit']}, "
                   f"kind: {entry['kind']}{writable}, id: 0x{fid:016x} }}")
    return "\n".join(out) + "\n"


# --------------------------------------------------------------------------

def check(entries: dict, derived: dict, hfp_text: str) -> list[str]:
    problems, declared = [], set()
    for n, domain, element, f in declared_fields(hfp_text):
        path = f"{domain}.{element}.{f['name']}"
        declared.add(path)
        entry = entries.get(path)
        if entry is None:
            problems.append(
                f"{HFP.name}:{n + 1}: '{path}' is not defined in the HFD. There is "
                f"no SoC-private namespace - add a dictionary entry first.")
            continue
        if f["unit"] != entry["unit"] or f["kind"] != entry["kind"]:
            problems.append(
                f"{HFP.name}:{n + 1}: '{path}' declared as {f['unit']}/{f['kind']}, "
                f"the HFD defines {entry['unit']}/{entry['kind']}. A declaration "
                f"chooses whether to serve a field; it cannot redefine one.")
            continue
        expected = field_id(path, entry["unit"], entry["kind"])
        m = re.search(r"id:\s*0x([0-9a-f]{16})", f["rest"])
        if m and int(m.group(1), 16) != expected:
            problems.append(
                f"{HFP.name}:{n + 1}: '{path}' carries id 0x{m.group(1)}, computed "
                f"0x{expected:016x}. Re-run --generate.")
    for d, source in derived.items():
        if d in declared and source not in declared:
            problems.append(
                f"{HFP.name}: '{d}' is declared but '{source}', which it is derived "
                f"from, is not. That declaration cannot be satisfied.")
    return problems


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--generate", action="store_true",
                        help="regenerate every artefact from the HFD")
    args = parser.parse_args()

    entries, derived = load_hfd()
    if not entries:
        print(f"error: no fields found in {HFD}", file=sys.stderr)
        return 2

    if args.generate:
        NAMES.write_text(emit_names(entries), encoding="utf-8")
        REQS.write_text(emit_requirements(entries, derived), encoding="utf-8")
        DICT_MD.write_text(emit_dictionary_md(entries), encoding="utf-8")
        HFP.write_text(sync_hfp(entries, HFP.read_text(encoding="utf-8")),
                       encoding="utf-8")
        print(f"generated from {len(entries)} HFD entries:\n"
              f"  {NAMES.relative_to(ROOT)}\n  {REQS.relative_to(ROOT)}\n"
              f"  {DICT_MD.relative_to(ROOT)}\n  {HFP.relative_to(ROOT)}")

    problems = check(entries, derived, HFP.read_text(encoding="utf-8"))
    for problem in problems:
        print(f"error: {problem}", file=sys.stderr)
    if problems:
        print(f"\n{len(problems)} problem(s).", file=sys.stderr)
        return 1

    print(f"ok: {len(declared_fields(HFP.read_text(encoding='utf-8')))} declared "
          f"fields resolve against {len(entries)} HFD entries; every id matches.")
    return 0


if __name__ == "__main__":
    sys.exit(main())

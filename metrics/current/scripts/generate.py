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

"""Generator and checker for the metrics HAL Feature Profile.

    scripts/generate.py

No arguments. It computes each field's contract id and writes it back into the
profile, regenerates the reference doc and the per-field requirements, verifies
the result is stable, checks the profile, and exits non-zero if anything is
wrong. There is nothing to remember and no mode to pick wrongly.

RUN IT BEFORE COMMITTING any change to the profile. It is a pre-commit step for
the engineer making the change, deliberately not a CI gate: the person editing a
field is the one who should see the generated diff and review it, rather than
discovering it later on a PR.

THE PROFILE IS THE CONTRACT
---------------------------
`hfp-metrics.yaml` states the interface data a vendor must implement and return,
and it is what the test suites validate a device against. A field is defined
there and nowhere else - its meaning and this product's declaration of it are
the same statement, so there is no separate dictionary to agree with.

    hfp-metrics.yaml                     authored - the contract
        |
        +-> id: on each field            computed and written back in
        +-> docs/vendor_field_dictionary.md   the reference, and what each
                                              declared field must do

ONE PROFILE PER LAYER
---------------------
This profile is the HAL layer's: what a SoC vendor owes. A layer above the HAL
keeps its own profile in its own repository - the middleware that owns the
session state machine declares its figures there, not here, and a vendor is
never asked to serve them. getCapabilities() returns the union of every profile
live on the device, which composes only because each follows the same shape.

A layer never declares another layer's fields. That is what keeps "who owes this
figure" answerable from the file it appears in.

FIELD CONTRACT ID
-----------------
    id = first 8 bytes of SHA-256("<domain>.<element>.<field>|<unit>|<kind>")

Nothing allocates it, so there is no registry to consult, no counter to advance
and nothing to resolve when two people add a field on separate branches.

It buys a check no key can make on its own. A key - a name or an ordinal -
stays valid while the meaning underneath it changes: a product that declares
`decode_latency_sum_us` but populates milliseconds still matches by name, and
the consumer reports figures a thousand times wrong; a `current` sample
reclassified as a `counter` gets differenced into nonsense. Because `unit` and
`kind` are hashed, both change the id, so a consumer comparing against the id it
was built with sees a hard mismatch instead of a wrong number.

An id is never reused, because the same id means the same name, unit and kind -
the same field. And unit and kind cannot change under a stable id, because
changing either produces a different id. Both are properties of the encoding
rather than rules something has to police.

Deliberately NOT hashed: the instance segment (`.0` and `.1` are the same field
on different sources), `writable` (a per-product permission, not the field's
meaning), and the description (a typo fix must not churn the id).

The id is not generated into the interface. It reaches a client at runtime on
MetricFieldInfo: a client resolves a source's fields once, caches name -> id,
and re-resolves when Capabilities.schemaId changes.
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
HFP = ROOT / "hfp-metrics.yaml"
DICT_MD = ROOT / "docs/vendor_field_dictionary.md"

# A layer above the HAL defines the figures only it produces. Untracked here -
# it belongs to that layer's repository - but when a working copy is present the
# combined view below is generated from it, which is what that layer publishes
# to its own callers.
UPPER_GLOB = "*-field-unique-dictionary.yaml"
COMBINED = ROOT / "docs/combined_field_dictionary.md"

# Units render for humans in one form and travel in another.
UNIT_ALIASES = {"µs": "us"}

# How each kind may be read. Stated once in the dictionary, and the requirement
# a field carries is that its values behave this way.
KIND_RULES = {
    "counter": "cumulative since source creation, monotonically non-decreasing, "
               "and never reset on flush or seek",
    "current": "a live sample re-read each poll, absolute, and never summed",
    "high_water": "a monotone maximum since source creation, absolute",
    "config": "the present value of a tunable, absolute",
}

GENERATED = ("GENERATED from hfp-metrics.yaml by scripts/generate.py. "
             "Do not hand-edit.")

# The slowest cadence an element may declare - the 50 ms freshness floor of
# HAL.METRICS.5. Stated in hfp-metrics-schema.yaml and the module docs too;
# keep the three in step.
SLOWEST_CADENCE_MS = 50

def field_id(path: str, unit: str, kind: str) -> int:
    """Content-derived identity. `path` is <domain>.<element>.<field>."""
    digest = hashlib.sha256(f"{path}|{unit}|{kind}".encode("utf-8")).digest()
    return struct.unpack(">q", digest[:8])[0] & 0x7FFFFFFFFFFFFFFF


def load_profile() -> tuple[dict, dict]:
    """Returns (entries, derived_from) from the HFP, in authored order."""
    entries, derived = {}, {}
    _load(yaml.safe_load(HFP.read_text(encoding="utf-8")), entries, derived, "HAL")
    return entries, derived


def load_upper() -> dict:
    """Fields defined by a layer above the HAL, keyed by layer name.

    Empty when no working copy is present, which is the normal state of this
    repository - those definitions live with the layer that owns them."""
    layers = {}
    for path in sorted(ROOT.glob(UPPER_GLOB)):
        layer = path.name.split("-field-unique-dictionary")[0]
        entries, derived = {}, {}
        _load(yaml.safe_load(path.read_text(encoding="utf-8")), entries, derived, layer)
        layers[layer] = entries
    return layers


def _load(doc: dict, entries: dict, derived: dict, layer: str) -> None:
    root = doc.get("metrics") or doc.get("hfd")
    for domain in root["domains"]:
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
                entries[path]["layer"] = layer
                if f.get("derivedFrom"):
                    derived[path] = f["derivedFrom"]


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


# --------------------------------------------------------------------------
# Generators
# --------------------------------------------------------------------------

def emit_combined(hal: dict, layers: dict) -> str:
    """Every field a caller of the top layer can see, and who produces it.

    A consumer above the middleware reads the union - getCapabilities() returns
    every profile live on the device - so it needs one document covering all of
    them. This is that document, and it is the top layer's to publish."""
    total = len(hal) + sum(len(v) for v in layers.values())
    out = ["# Combined Field Dictionary", "",
           f"<!-- {GENERATED} -->", "",
           "Every field a caller can see, across every layer that declares one. "
           "`getCapabilities()` returns the union of the profiles live on the "
           "device, so this is the document a consumer of the top layer reads.",
           "",
           "The **Layer** column is who produces the figure. A consumer does not "
           "need to know — the name means the same thing wherever it came from — "
           "but it is what makes a missing field answerable: a field absent at "
           "runtime is absent because the layer that owns it did not declare it.",
           "",
           "Contract ids are computed the same way at every layer, from "
           "`path|unit|kind`, so an id means the same thing across the union "
           "without anything having to co-ordinate.", "",
           f"{total} fields: {len(hal)} from the HAL"
           + "".join(f", {len(v)} from {k}" for k, v in layers.items()) + ".", "",
           "| Field | Layer | Type · unit · kind | Provider | id | Definition |",
           "|---|---|---|---|---|---|"]
    merged = dict(hal)
    for entries in layers.values():
        merged.update(entries)
    for path, e in merged.items():
        fid = field_id(path, e["unit"], e["kind"])
        w = " · **writable**" if e["writable"] else ""
        out.append(f"| `{path}` | {e['layer']} | int64 · {e['unit']} · "
                   f"`{e['kind']}`{w} | **{e['provider']}** | `0x{fid:016x}` "
                   f"| {e['description']} |")
    return "\n".join(out) + "\n"


def emit_dictionary_md(entries: dict) -> str:
    """The human-readable reference, generated from the profile."""
    head = DICT_MD.read_text(encoding="utf-8") if DICT_MD.exists() else ""
    preamble = (head.split("## Fields")[0] if "## Fields" in head
                else "# AV Domain Field Dictionary\n\n")
    # The preamble is carried through, so drop any marker a previous run left
    # in it before emitting a fresh one - otherwise they stack.
    preamble = "\n".join(l for l in preamble.splitlines()
                         if "Field tables: GENERATED" not in l)
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

def write_ids(entries: dict) -> str:
    """Write each field's computed id into the profile, in place.

    Line-based so every comment and the authored layout survive. An `id:` line
    is replaced where present and inserted after `kind:` where absent, so
    deleting an id restores it on the next run."""
    lines = HFP.read_text(encoding="utf-8").splitlines()
    out: list[str] = []
    domain = element = name = None

    for line in lines:
        m = re.match(r"^\s*-\s+domain:\s*(\S+)", line)
        if m:
            domain = m.group(1)
        m = re.match(r"^\s*-\s+element:\s*(\S+)", line)
        if m:
            element = m.group(1)
        m = re.match(r"^(\s*)-\s+name:\s*(\S+)\s*$", line)
        if m:
            name = m.group(2)
        if re.match(r"^\s*id:\s*'?0x[0-9a-f]+'?\s*$", line):
            continue                      # regenerated below
        out.append(line)
        m = re.match(r"^(\s*)kind:\s*(\S+)\s*$", line)
        if m and domain and element and name:
            path = f"{domain}.{element}.{name}"
            entry = entries.get(path)
            if entry:
                # Quoted: YAML reads a bare 0x… as an integer, and the id is a
                # 16-digit hex string whose leading zeros carry meaning.
                out.append(f"{m.group(1)}id: "
                           f"'0x{field_id(path, entry['unit'], entry['kind']):016x}'")
    return "\n".join(out) + "\n"


def check(entries: dict, derived: dict) -> list[str]:
    """What the profile cannot be trusted to get right on its own."""
    problems = []
    for path, e in entries.items():
        if e["kind"] not in KIND_RULES:
            problems.append(
                f"{HFP.name}: '{path}' declares kind '{e['kind']}', which is not one "
                f"of {', '.join(sorted(KIND_RULES))}.")
        if not e["description"]:
            problems.append(
                f"{HFP.name}: '{path}' has no description. A vendor reads this file to "
                f"know what to return, so a field without one cannot be implemented.")
    for d, source in derived.items():
        if source not in entries:
            problems.append(
                f"{HFP.name}: '{d}' is derived from '{source}', which is not declared. "
                f"That declaration cannot be satisfied.")
    return problems


def check_elements(doc: dict) -> list[str]:
    """Element-level constraints, which no field-by-field pass can see.

    The schema states these too, but the schema only runs where pykwalify is
    installed. A profile that cannot validate is worth catching here, where
    every author already runs."""
    problems = []
    root = doc.get("metrics") or doc.get("hfd")
    for domain in root["domains"]:
        for element in domain["elements"]:
            where = f"{domain['domain']}.{element['element']}"
            cadence = element.get("pollCadenceMs")
            if cadence is not None and not 1 <= cadence <= SLOWEST_CADENCE_MS:
                problems.append(
                    f"{HFP.name}: '{where}' declares pollCadenceMs {cadence}, outside "
                    f"1..{SLOWEST_CADENCE_MS}. The {SLOWEST_CADENCE_MS} ms freshness "
                    f"floor is promised to partners; an element may declare tighter, "
                    f"never looser.")
            for f in element["fields"]:
                fid = f.get("id")
                if fid is None:
                    continue
                # A bare 0x… is an integer to YAML, so an unquoted id validates
                # as neither the schema's string nor the 16 hex digits it needs.
                if not isinstance(fid, str) or not re.fullmatch(r"0x[0-9a-f]{16}", fid):
                    problems.append(
                        f"{HFP.name}: '{where}.{f['name']}' carries id {fid!r}, which is "
                        f"not a quoted 16-digit lowercase hex string. Delete the id and "
                        f"re-run to regenerate it.")
    return problems


def generate(entries: dict, derived: dict) -> dict:
    """Write every generated artefact. Returns {path: content} as written."""
    HFP.write_text(write_ids(entries), encoding="utf-8")
    DICT_MD.write_text(emit_dictionary_md(entries), encoding="utf-8")
    written = [DICT_MD, HFP]

    layers = load_upper()
    if layers:
        COMBINED.write_text(emit_combined(entries, layers), encoding="utf-8")
        written.append(COMBINED)
    elif COMBINED.exists():
        COMBINED.unlink()          # no upper layer here means no combined view

    return {p: p.read_text(encoding="utf-8") for p in written}


def main() -> int:
    argparse.ArgumentParser(
        description="Regenerate and check everything the HAL Field Dictionary "
                    "drives. Takes no arguments.").parse_args()

    entries, derived = load_profile()
    if not entries:
        print(f"error: no fields found in {HFP}", file=sys.stderr)
        return 2

    first = generate(entries, derived)
    # Two emitters carry their own previous output forward - the HFP's
    # description blocks and the dictionary's preamble. Both have stacked
    # duplicates before, and neither failure is visible in a single run. So
    # generate again and require the result to be identical.
    second = generate(entries, derived)
    unstable = sorted(p.name for p in first if first[p] != second[p])
    if unstable:
        print(f"error: generation is not idempotent - {', '.join(unstable)} "
              f"changed on a second run. An emitter is failing to strip what it "
              f"wrote last time.", file=sys.stderr)
        return 1

    # Re-read the written profile, so the ids checked are the ones that landed.
    written = yaml.safe_load(HFP.read_text(encoding="utf-8"))
    problems = check(entries, derived) + check_elements(written)
    for problem in problems:
        print(f"error: {problem}", file=sys.stderr)
    if problems:
        print(f"\n{len(problems)} problem(s).", file=sys.stderr)
        return 1

    layers = load_upper()
    extra = sum(len(v) for v in layers.values())
    print(f"ok: {len(entries)} fields declared; ids written and generation is stable.")
    if layers:
        print(f"  plus {extra} from {', '.join(layers)} - combined view generated")
    for path in (DICT_MD, HFP):
        print(f"  wrote {path.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())

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
and checks that id against the one it was built against.
"""

from __future__ import annotations

import argparse
import hashlib
import re
import struct
import sys
import textwrap
from pathlib import Path

import yaml

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
HFP = ROOT / "hfp-metrics.yaml"
SCHEMA = ROOT / "hfp-metrics-schema.yaml"
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
    "counter": "cumulative since service start, monotonically non-decreasing, "
               "and never reset on flush or seek",
    "current": "a live sample re-read each capture, absolute, and never summed",
    "high_water": "a monotone maximum since service start, absolute",
    "config": "the present value of a tunable, absolute",
}

GENERATED = ("GENERATED from hfp-metrics.yaml by scripts/generate.py. "
             "Do not hand-edit.")

# The slowest cadence an element may declare - the 50 ms freshness floor of
# HAL.METRICS.5. Stated in hfp-metrics-schema.yaml and the module docs too;
# keep the three in step.
SLOWEST_CADENCE_MS = 50

def cell(text: str) -> str:
    """Table-cell text. A pipe in a description would otherwise open a column,
    and the closed vocabularies are written with pipes."""
    return text.replace("|", "\\|")


def field_id(path: str, unit: str, kind: str) -> int:
    """Content-derived identity. `path` is <domain>.<element>.<field>."""
    digest = hashlib.sha256(f"{path}|{unit}|{kind}".encode("utf-8")).digest()
    return struct.unpack(">q", digest[:8])[0] & 0x7FFFFFFFFFFFFFFF


def profile_versions(doc: dict) -> dict:
    """What a profile states about itself, and each domain's dictionary."""
    root = doc.get("metrics") or doc.get("hfd")
    return {"interface": root.get("interfaceVersion"),
            "schema": root.get("schemaVersion"),
            "domains": {d["domain"]: d.get("dictionaryVersion")
                        for d in root["domains"]}}


def render_versions(v: dict) -> str:
    """The domain dictionary revisions of one profile, as one cell."""
    return ", ".join(f"`{d}` {rev or '—'}" for d, rev in v["domains"].items())


def load_profile() -> tuple[dict, dict, dict, dict]:
    """Returns (entries, derived_from, versions, events) from the HFP."""
    entries, derived = {}, {}
    doc = yaml.safe_load(HFP.read_text(encoding="utf-8"))
    _load(doc, entries, derived, "HAL")
    return entries, derived, profile_versions(doc), load_events(doc)


def load_events(doc: dict) -> dict:
    """Occurrences each element raises, keyed '<domain>.<element>:<kind>'.

    An event carries one occurrence with its own payload, where a counter can
    only say how many happened and a `last_*` field only describes the newest."""
    events = {}
    root = doc.get("metrics") or doc.get("hfd")
    for domain in root["domains"]:
        for element in domain["elements"]:
            for ev in element.get("events") or []:
                key = f"{domain['domain']}.{element['element']}:{ev['kind']}"
                events[key] = {
                    "element": f"{domain['domain']}.{element['element']}",
                    "kind": ev["kind"],
                    "description": ev["description"].strip(),
                    "fields": [{"name": f["name"],
                                "unit": UNIT_ALIASES.get(f["unit"], f["unit"]),
                                "description": f["description"].strip()}
                               for f in ev["fields"]],
                }
    return events


def load_upper() -> tuple[dict, dict]:
    """Fields defined by a layer above the HAL, keyed by layer name, and the
    versions each of those layers states.

    Empty when no working copy is present, which is the normal state of this
    repository - those definitions live with the layer that owns them."""
    layers, versions = {}, {}
    for path in sorted(ROOT.glob(UPPER_GLOB)):
        layer = path.name.split("-field-unique-dictionary")[0]
        entries, derived = {}, {}
        doc = yaml.safe_load(path.read_text(encoding="utf-8"))
        _load(doc, entries, derived, layer)
        layers[layer] = entries
        versions[layer] = profile_versions(doc)
    return layers, versions


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
    # A long word goes on its own line rather than being split: these are field
    # names and identifiers, and a broken one is no longer the thing it names.
    return textwrap.wrap(text, width, break_long_words=False,
                         break_on_hyphens=False)


def const_name(path: str) -> str:
    """av.video_sink.frames_presented -> AV_VIDEO_SINK_FRAMES_PRESENTED"""
    return path.replace(".", "_").upper()


# --------------------------------------------------------------------------
# Generators
# --------------------------------------------------------------------------

def emit_combined(hal: dict, layers: dict, hal_versions: dict,
                  layer_versions: dict) -> str:
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
           "## Versions", "",
           "Each layer versions itself. A figure is cited against the dictionary "
           "revision of the layer that owns it, not against a single number for "
           "the union.", "",
           "| Layer | Interface | Schema | Dictionary |",
           "|---|---|---|---|",
           f"| HAL | {hal_versions['interface'] or '—'} | "
           f"{hal_versions['schema'] or '—'} | {render_versions(hal_versions)} |"]
    for layer, v in layer_versions.items():
        out.append(f"| {layer} | {v['interface'] or '—'} | {v['schema'] or '—'} "
                   f"| {render_versions(v)} |")
    out += ["",
            "## Fields", "",
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
                   f"| {cell(e['description'])} |")
    return "\n".join(out) + "\n"


def emit_events_md(events: dict) -> list[str]:
    """The events section: for each occurrence, its name, trigger and payload."""
    out = ["## Events", "",
           "A counter says how many occurrences there have been and a `last_*` field "
           "describes the newest. This section specifies the occurrence itself - what "
           "it is and what accompanies it - so a vendor knows exactly which moment "
           "moves those fields and a test can assert it did.", "",
           "The description of each event **is its trigger**: the instant a vendor "
           "detects it. Payload names are bare, because the event already fixes which "
           "source and which occurrence they belong to. A payload a product cannot "
           "derive is omitted from the event rather than stated as a placeholder."]
    last_element = None
    for ev in events.values():
        if ev["element"] != last_element:
            out += ["", f"### `{ev['element']}`"]
            last_element = ev["element"]
        out += ["", f"#### `{ev['kind']}`", "", ev["description"], "",
                "| Payload | Unit | Meaning |", "|---|---|---|"]
        for f in ev["fields"]:
            out.append(f"| `{f['name']}` | {f['unit']} | {cell(f['description'])} |")
    return out + [""]


def emit_dictionary_md(entries: dict, versions: dict, events: dict) -> str:
    """The human-readable reference, generated from the profile."""
    head = DICT_MD.read_text(encoding="utf-8") if DICT_MD.exists() else ""
    preamble = (head.split("## Fields")[0] if "## Fields" in head
                else "# AV Domain Field Dictionary\n\n")
    # Versions are generated below, so drop the block a previous run left in
    # the carried-forward preamble rather than stacking another one on it.
    for heading in ("## Versions", "## How this document is produced"):
        preamble = preamble.split(heading)[0]
    # The preamble is carried through, so drop any marker a previous run left
    # in it before emitting a fresh one - otherwise they stack.
    preamble = "\n".join(l for l in preamble.splitlines()
                         if "Field tables: GENERATED" not in l)
    tail = ""
    for marker in ("## Episodic Conditions", "## Accuracy"):
        if marker in head:
            tail = head[head.index(marker):]
            break

    dicts = ", ".join(f"`{d}` {rev or '—'}"
                      for d, rev in versions["domains"].items())
    out = [preamble.rstrip("\n"), "", f"<!-- Field tables: {GENERATED} -->", "",
           "## How this document is produced", "",
           f"**Generated** from `{HFP.name}` by `scripts/generate.py`, from "
           f"dictionary {dicts}.", "",
           "The **Fields** and **Events** sections are written by that script and are "
           "overwritten on every run, so a correction goes in the profile and reaches "
           "this document from there. Everything else here is authored: the sections "
           "above, and **Episodic Conditions** and **Accuracy** below.", "",
           "| | Version |", "|---|---|"]
    for domain, revision in versions["domains"].items():
        out.append(f"| `{domain}` dictionary | {revision or '—'} |")
    out += [f"| Interface | {versions['interface'] or '—'} |",
            f"| Schema | {versions['schema'] or '—'} |", "",
            "The dictionary revision pins the set of names; a field's `id` pins its "
            "unit and kind. Cite both when stating what a device was asked to serve.",
            "", "## Fields"]
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
                   f"| **{e['provider']}** | `0x{fid:016x}` | {cell(e['description'])} |")
    out += [""] + emit_events_md(events) + [tail.rstrip("\n"), ""]
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


def check_schema(paths: list[Path]) -> tuple[list[str], bool]:
    """Validate profiles against hfp-metrics-schema.yaml.

    Returns (problems, ran). The schema is the contract every layer's profile
    is held to, and for six weeks this profile did not satisfy it while nothing
    here noticed - the ids were unquoted, so YAML read them as integers where
    the schema requires strings. Reading the schema is not checking against it.

    pykwalify is not always installed, so `ran` is reported rather than assumed:
    a validation that did not happen must never look like one that passed."""
    try:
        import logging
        from pykwalify.core import Core
        logging.disable(logging.CRITICAL)
    except ImportError:
        return [], False

    problems = []
    for path in paths:
        try:
            Core(source_file=str(path),
                 schema_files=[str(SCHEMA)]).validate(raise_exception=True)
        except Exception as exc:
            first = str(exc).splitlines()
            detail = " ".join(l.strip() for l in first[:4])
            problems.append(f"{path.name}: fails {SCHEMA.name} - {detail}")
    return problems, True


def check_layers(hal: dict, layers: dict) -> list[str]:
    """The one rule that spans profiles: a layer never declares another's field.

    The combined view merges every layer into one table, so a repeated path
    would silently keep one declaration and drop the other - and "who owes this
    figure" stops being answerable from the file it appears in."""
    problems, seen = [], {path: "the HAL" for path in hal}
    for layer, entries in layers.items():
        for path in entries:
            if path in seen:
                problems.append(
                    f"'{path}' is declared by both {seen[path]} and {layer}. A layer "
                    f"never declares another layer's fields, and the combined view "
                    f"cannot show both.")
            else:
                seen[path] = layer
    return problems


def check_events(events: dict) -> list[str]:
    """What an event declaration cannot be trusted to get right on its own."""
    problems = []
    for key, ev in events.items():
        if not ev["description"]:
            problems.append(
                f"{HFP.name}: event '{key}' has no description. The description is "
                f"the trigger - without it a vendor cannot know when to raise it.")
        if not ev["fields"]:
            problems.append(
                f"{HFP.name}: event '{key}' declares no payload. An occurrence with "
                f"nothing to carry is a counter, not an event.")
        seen = set()
        for f in ev["fields"]:
            if f["name"] in seen:
                problems.append(
                    f"{HFP.name}: event '{key}' declares '{f['name']}' twice.")
            seen.add(f["name"])
            if not f["description"]:
                problems.append(
                    f"{HFP.name}: event '{key}' payload '{f['name']}' has no "
                    f"description, so a consumer cannot know what it carries.")
    return problems


def check_episodic(entries: dict, doc_text: str) -> list[str]:
    """Every episodic field must be named in the checklist an implementer reads.

    The Episodic Conditions section is authored, not generated: it states the
    instant each field is written, which the profile does not say. Authored text
    goes stale silently - a field added to the profile simply never appears -
    so require the section to account for every episodic field."""
    if "## Episodic Conditions" not in doc_text:
        return []
    section = doc_text[doc_text.index("## Episodic Conditions"):]
    problems = []
    for path, e in entries.items():
        name = e["field"]
        if not (name.startswith("last_") or name.endswith("_event_count")
                or name == "underflowed"):
            continue
        if f"`{name}`" not in section:
            problems.append(
                f"{DICT_MD.name}: '{path}' reports an occurrence, but the Episodic "
                f"Conditions section never names it - nothing tells an implementer "
                f"at what instant to write it.")
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
            cadence = element.get("captureCadenceMs")
            if cadence is not None and not 1 <= cadence <= SLOWEST_CADENCE_MS:
                problems.append(
                    f"{HFP.name}: '{where}' declares captureCadenceMs {cadence}, outside "
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


def generate(entries: dict, derived: dict, versions: dict, events: dict) -> dict:
    """Write every generated artefact. Returns {path: content} as written."""
    HFP.write_text(write_ids(entries), encoding="utf-8")
    DICT_MD.write_text(emit_dictionary_md(entries, versions, events), encoding="utf-8")
    written = [DICT_MD, HFP]

    layers, layer_versions = load_upper()
    if layers:
        COMBINED.write_text(
            emit_combined(entries, layers, versions, layer_versions),
            encoding="utf-8")
        written.append(COMBINED)
    elif COMBINED.exists():
        COMBINED.unlink()          # no upper layer here means no combined view

    return {p: p.read_text(encoding="utf-8") for p in written}


def main() -> int:
    argparse.ArgumentParser(
        description="Regenerate and check everything the HAL Field Dictionary "
                    "drives. Takes no arguments.").parse_args()

    entries, derived, versions, events = load_profile()
    if not entries:
        print(f"error: no fields found in {HFP}", file=sys.stderr)
        return 2

    # Before writing anything: a path claimed by two layers cannot be rendered
    # in the combined view at all, so fail while the tree is still untouched.
    layers, _ = load_upper()
    collisions = check_layers(entries, layers)
    if collisions:
        for collision in collisions:
            print(f"error: {collision}", file=sys.stderr)
        return 1

    first = generate(entries, derived, versions, events)
    # Two emitters carry their own previous output forward - the HFP's
    # description blocks and the dictionary's preamble. Both have stacked
    # duplicates before, and neither failure is visible in a single run. So
    # generate again and require the result to be identical.
    second = generate(entries, derived, versions, events)
    unstable = sorted(p.name for p in first if first[p] != second[p])
    if unstable:
        print(f"error: generation is not idempotent - {', '.join(unstable)} "
              f"changed on a second run. An emitter is failing to strip what it "
              f"wrote last time.", file=sys.stderr)
        return 1

    # Re-read the written profile, so the ids checked are the ones that landed.
    written = yaml.safe_load(HFP.read_text(encoding="utf-8"))
    problems = (check(entries, derived) + check_elements(written)
                + check_episodic(entries, DICT_MD.read_text(encoding="utf-8"))
                + check_events(events))
    for problem in problems:
        print(f"error: {problem}", file=sys.stderr)
    if problems:
        print(f"\n{len(problems)} problem(s).", file=sys.stderr)
        return 1

    schema_problems, validated = check_schema([HFP])
    for problem in schema_problems:
        print(f"error: {problem}", file=sys.stderr)
    if schema_problems:
        return 1

    extra = sum(len(v) for v in layers.values())
    print(f"ok: {len(entries)} fields declared; ids written and generation is stable.")
    print(f"  {SCHEMA.name}: "
          + ("validated" if validated else
             "NOT VALIDATED - pip install pykwalify (see scripts/requirements.txt)"))
    if layers:
        print(f"  plus {extra} from {', '.join(layers)} - combined view generated")
    for path in (DICT_MD, HFP):
        print(f"  wrote {path.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())

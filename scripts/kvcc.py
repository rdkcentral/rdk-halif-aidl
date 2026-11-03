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

"""kvcc — compile a module's Key Value Contract into constants.

A module owns the keys for the values it produces, and declares them in a
vocabulary beside its interface versions:

    videodecoder/
    |-- kvc/
    |   |-- videodecoder.kvc              the vocabulary
    |   `-- include/                      generated, not committed
    |-- 0.2.0.0/                          frozen interface
    `-- current/                          generated AIDL lands here

A vocabulary has no revisions of its own. It versions with its module's
interface, and the frozen interface is its record.

The declaration is the single source: the AIDL, the documentation and the
header all come from it, so a key is defined once and checked the same way
in every module. A new key is a new member of the module's generated AIDL
enums, which is an additive interface change.

Identity is two levels. The element is the only global identifier: the
first 8 bytes of SHA-256 over "<domain>.<component>", big-endian signed 64-bit
with the sign bit cleared, so a group or event forwarded out of its HAL still
says where it came from. Everything inside the element is scoped by it and
carries the small integer `id` its .kvc declares:

    element    SHA-256("<domain>.<component>")       MetricGroup.id
    key        id, unique among the element's keys     MetricValue.id
    event      id, unique among the element's events   MetricEvent.eventId
    attribute  id, unique among the element's event fields; 0 is `instance`

An id is declared, never taken from position. A vocabulary only grows: once
frozen, a field is never removed, renumbered or redefined, and one whose unit
or kind must change is marked `deprecated` while a new field takes a new id.
The AIDL compiler's compatibility check enforces this, with no frozen record
of its own here: the enums carry the ids, and MetricIdentity carries each
field's "<path>|<unit>|<kind>" as a constant, so a changed unit or kind is a
changed constant value.

Emits, per module:

    <module>/current/com/rdk/hal/<package>/MetricElement.aidl
                                          Metric.aidl
                                          MetricEventKind.aidl
                                          MetricEventAttribute.aidl
                                          MetricIdentity.aidl
    <module>/current/docs/<page>_metrics.md
    <module>/kvc/include/<Component>Keys.h

The AIDL enums name the identifiers so a caller can pass one type-safely. The
metrics page documents every key, event and closed vocabulary beside the
module's own page, so the documentation is generated from the same declaration
as the code. The header carries the same identifiers for a layer that is not
built from AIDL, along with each closed vocabulary and a descriptor table, so
an identifier seen in a log can be resolved back to the name it came from. The
AIDL and the page are committed and checked; the header is not committed.

A closed vocabulary is generated into the header and NEVER into the AIDL: its
members are values a key carries, so adding one must not be an interface
change.

    kvcc.py            regenerate every module that declares a vocabulary
    kvcc.py --check    verify, write nothing, non-zero exit on drift
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

REPO = Path(__file__).resolve().parent.parent

AIDL_LICENCE = """/*
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

KIND_ORDER = ["counter", "current", "high_water", "config"]

# Attribute 0 in every element is the instance a group or event reports. It is
# MetricGroup.ATTRIBUTE_INSTANCE in the envelope, so no .kvc declares it.
INSTANCE_ID = 0
ID_MAX = 0x7FFFFFFF


def element_hash(path: str) -> int:
    """First 8 bytes of SHA-256 over the element path, sign bit cleared."""
    digest = hashlib.sha256(path.encode("utf-8")).digest()
    return struct.unpack(">q", digest[:8])[0] & 0x7FFFFFFFFFFFFFFF


def const(name: str) -> str:
    return re.sub(r"[^A-Z0-9]+", "_", name.upper()).strip("_")


def camel(name: str) -> str:
    return "".join(part.capitalize() for part in re.split(r"[^A-Za-z0-9]+", name))


def flow(text: str) -> str:
    return " ".join(str(text).split())


def block(text: str, indent: str, width: int = 78) -> list[str]:
    lines = textwrap.wrap(flow(text), width=width - len(indent) - 3) or [""]
    return [f"{indent}/**"] + [f"{indent} * {ln}".rstrip() for ln in lines] + \
           [f"{indent} */"]


class Vocabulary:
    """One module's .kvc, with every identifier it defines already computed."""

    def __init__(self, module: str, path: Path):
        doc = yaml.safe_load(path.read_text())
        if doc.get("format") != "kvc":
            raise SystemExit(f"{path}: not a kvc document (missing format: kvc)")
        self.module = module
        self.path = path
        self.schema = doc["schema"]
        self.domain = doc["domain"]
        self.component = doc["component"]
        self.package = doc["package"]
        self.instances = doc.get("instances", 1)
        self.cadence_ms = doc.get("captureCadenceMs")
        self.keys = doc.get("keys") or []
        self.events = doc.get("events") or []
        self.base = f"{self.domain}.{self.component}"
        self._validate()

    def _validate(self) -> None:
        for key in self.keys:
            if key["kind"] not in KIND_ORDER:
                raise SystemExit(
                    f"{self.path}: key '{key['name']}' has kind "
                    f"'{key['kind']}', not one of {KIND_ORDER}")
            if not key.get("description"):
                raise SystemExit(
                    f"{self.path}: key '{key['name']}' has no description, so "
                    f"nothing states what a vendor implements or a test asserts")
        for space, fields in self.spaces().items():
            seen: dict[int, str] = {}
            for name, field in fields:
                ident = field.get("id")
                if not isinstance(ident, int) or isinstance(ident, bool) or \
                        not 1 <= ident <= ID_MAX:
                    raise SystemExit(
                        f"{self.path}: '{name}' needs an id from 1 to {ID_MAX} "
                        f"(0 is reserved for instance in attributes)")
                if ident in seen:
                    raise SystemExit(
                        f"{self.path}: '{name}' and '{seen[ident]}' share "
                        f"{space} id {ident}")
                if "deprecated" in field and not field["deprecated"]:
                    raise SystemExit(
                        f"{self.path}: '{name}' is deprecated with no reason; "
                        f"state what replaces it")
                seen[ident] = name

    def element_id(self) -> int:
        return element_hash(self.base)

    def key_id(self, key: dict) -> int:
        return key["id"]

    def event_id(self, event: dict) -> int:
        return event["id"]

    def attribute_id(self, event: dict, attr: dict) -> int:
        return attr["id"]

    def event_value_id(self, event: dict, value: dict) -> int:
        return value["id"]

    def spaces(self) -> dict[str, list[tuple[str, dict]]]:
        """Each id space the element scopes, as (path, field) pairs."""
        return {
            "keys": [(f"{self.base}.{k['name']}", k) for k in self.keys],
            "events": [(f"{self.base}.{e['name']}", e) for e in self.events],
            "attributes": [(f"{self.base}.{e['name']}.{f['name']}", f)
                           for e, f in self.attributes() + self.event_values()],
        }

    def identities(self) -> list[tuple[str, str, dict]]:
        """(constant, "<path>|<unit>[|<kind>]", field) for every key and event
        field: what an id means, which a frozen interface holds it to. An
        attribute has no kind, so it states the unit alone."""
        out = [(f"KEY_{const(k['name'])}",
                f"{self.base}.{k['name']}|{k['unit']}|{k['kind']}", k)
               for k in self.keys]
        for e, f in self.attributes() + self.event_values():
            terms = [f"{self.base}.{e['name']}.{f['name']}", f["unit"]]
            terms += [f["kind"]] if "kind" in f else []
            out.append((f"ATTRIBUTE_{const(e['name'])}_{const(f['name'])}",
                        "|".join(terms), f))
        return out

    def attributes(self) -> list[tuple[dict, dict]]:
        return [(e, a) for e in self.events for a in e.get("attributes") or []]

    def event_values(self) -> list[tuple[dict, dict]]:
        return [(e, v) for e in self.events for v in e.get("values") or []]

    def vocabularies(self) -> list[tuple[str, list[dict]]]:
        """Closed vocabularies, as (owning field name, members)."""
        out = []
        for key in self.keys:
            if key.get("values"):
                out.append((key["name"], key["values"]))
        for event, attr in self.attributes():
            if attr.get("values"):
                out.append((f"{event['name']}_{attr['name']}", attr["values"]))
        return out

    def every_id(self):
        yield self.base, self.element_id()
        for fields in self.spaces().values():
            for path, field in fields:
                yield path, field["id"]


def member_doc(description: str, field: dict | None) -> list[str]:
    """A member's Doxygen, with @deprecated where its field is superseded."""
    lines = block(description, "    ")
    if field and field.get("deprecated"):
        reason = textwrap.wrap(f"@deprecated {flow(field['deprecated'])}",
                               width=78 - 7)
        lines[-1:-1] = [f"     * {ln}".rstrip() for ln in [""] + reason]
    return lines


def aidl_preamble(v: Vocabulary, brief: str, intro: str) -> list[str]:
    out = [AIDL_LICENCE, f"package com.rdk.hal.{v.package};", ""]
    out += ["/**", f" * @brief     {brief}", " * @author    Gerald Weatherup",
            " *",
            f" * THIS FILE IS GENERATED by scripts/kvcc.py from",
            f" * {v.module}/kvc/{v.module}.kvc (schema {v.schema}). Do not edit:",
            f" * declare the key there and regenerate, so an identifier is",
            f" * declared in one place.",
            " */", ""]
    out += ["/**", f" * @brief {brief}", " *"]
    out += [f" * {ln}".rstrip() for ln in textwrap.wrap(flow(intro), width=74)]
    return out + [" */", "", "@VintfStability"]


def aidl_enum(v: Vocabulary, name: str, brief: str, intro: str,
              members: list[tuple], backing: str = "int") -> str:
    out = aidl_preamble(v, brief, intro)
    out += [f'@Backing(type="{backing}")', f"enum {name}", "{"]
    for member, value, description, *field in members:
        out.append("")
        out += member_doc(description, field[0] if field else None)
        out.append(f"    {member} = "
                   + (f"{value:#018x}," if backing == "long" else f"{value},"))
    out += ["}", ""]
    return "\n".join(out)


def aidl_identity(v: Vocabulary) -> str:
    out = aidl_preamble(
        v, f"What each {v.module} metric id means.",
        "One constant per key and per event field, holding the path, unit "
        "and, for a measurement, kind its id stands for. It exists so the "
        "AIDL compatibility check can see them: a frozen constant's value "
        "cannot change, so a field whose unit or kind changes is refused "
        "and must take a new id. Nothing is served through it. KEY_<NAME> "
        "describes Metric::<NAME>, and ATTRIBUTE_<NAME> describes "
        "MetricEventAttribute::<NAME>.")
    out += ["parcelable MetricIdentity", "{"]
    for name, identity, field in v.identities():
        out.append("")
        out += member_doc(f"`{identity}`", field)
        out.append(f'    const String {name} = "{identity}";')
    out += ["}", ""]
    return "\n".join(out)


def aidl_files(v: Vocabulary) -> dict[Path, str]:
    root = REPO / v.module / "current" / "com" / "rdk" / "hal" / v.package
    files = {
        root / "MetricElement.aidl": aidl_enum(
            v, "MetricElement",
            f"Identifier of the element {v.module} reports.",
            "MetricGroup.id and MetricEvent.groupId carry this. It is the "
            "one global identifier: every key, event and attribute id is "
            "scoped by it. The instance is not part of it, because how many "
            "are live is a property of the moment rather than of the "
            "contract; it is carried as an attribute instead.",
            [(const(v.component), v.element_id(),
              f"`{v.base}` — {v.instances} instance(s)"
              + (f", captured no slower than every {v.cadence_ms} ms"
                 if v.cadence_ms else "") + ".")], backing="long"),
        root / "Metric.aidl": aidl_enum(
            v, "Metric",
            f"The figures {v.module} measures.",
            "MetricValue.id carries one of these, scoped by the element in "
            "MetricGroup.id. A key's name, unit and kind are its identity: "
            "once frozen, an id never changes any of them, so a changed "
            "figure takes a new id rather than a plausible wrong number "
            "answering to the old one.",
            [(const(k["name"]), v.key_id(k),
              f"`{v.base}.{k['name']}` — {k['unit']}, {k['kind']}"
              f"{', writable' if k.get('access') == 'readwrite' else ''}. "
              f"{k['description']}", k) for k in v.keys]),
    }
    if v.events:
        files[root / "MetricEventKind.aidl"] = aidl_enum(
            v, "MetricEventKind",
            f"The occurrences {v.module} raises.",
            "MetricEvent.eventId carries one of these, scoped by the element "
            "in MetricEvent.groupId. An occurrence is "
            "pushed because a read cannot carry it: a condition that began "
            "and ended between two reads is invisible to a reader however "
            "fast it polls.",
            [(const(e["name"]), v.event_id(e),
              f"`{v.base}.{e['name']}` — {e['description']}", e)
             for e in v.events])
    members = [(const(f"{e['name']}_{a['name']}"), v.attribute_id(e, a),
                f"`{v.base}.{e['name']}.{a['name']}` — {a['unit']}. "
                f"{a['description']}", a) for e, a in v.attributes()]
    members += [(const(f"{e['name']}_{x['name']}"), v.event_value_id(e, x),
                 f"`{v.base}.{e['name']}.{x['name']}` — {x['unit']}, "
                 f"{x['kind']}. {x['description']}", x)
                for e, x in v.event_values()]
    if members:
        files[root / "MetricEventAttribute.aidl"] = aidl_enum(
            v, "MetricEventAttribute",
            f"What describes an occurrence {v.module} raised.",
            "An attribute locates and classifies an occurrence rather than "
            "measuring it, so it has no kind. A value an occurrence measured "
            "does carry a kind. Both appear in MetricEvent, in the array that "
            "says which it is, and share one id space scoped by the element, "
            "in which 0 is MetricGroup.ATTRIBUTE_INSTANCE.",
            members)
    files[root / "MetricIdentity.aidl"] = aidl_identity(v)
    return files


def header(v: Vocabulary) -> str:
    guard = f"KVC_{const(v.component)}_VOCABULARY_H"
    out = [
        "/*", " * If not stated otherwise in this file or this component's "
        "LICENSE file the", " * following copyright and licenses apply:", " *",
        " * Copyright 2026 RDK Management", " *",
        ' * Licensed under the Apache License, Version 2.0 (the "License");',
        " * you may not use this file except in compliance with the License.",
        " * You may obtain a copy of the License at", " *",
        " * http://www.apache.org/licenses/LICENSE-2.0", " *",
        " * Unless required by applicable law or agreed to in writing, software",
        ' * distributed under the License is distributed on an "AS IS" BASIS,',
        " * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or "
        "implied.", " * See the License for the specific language governing "
        "permissions and", " * limitations under the License.", " */", "",
        f"/* Generated by kvcc from {v.module}.kvc — schema {v.schema}.",
        " * Do not edit. Regenerate to change. */",
        f"#ifndef {guard}", f"#define {guard}", "", "#include <stdint.h>", "",
        f"#define KVC_{const(v.component)}_SCHEMA     {v.schema}", "",
        "/* Kind decides how a key may legitimately be read. */",
        "typedef enum {",
    ]
    out += [f"    KVC_KIND_{const(k):<10} = {i}," for i, k in enumerate(KIND_ORDER)]
    out += ["    KVC_KIND_ATTRIBUTE  = 4,   /* dimensions an occurrence */",
            "} KvcKind;", ""]

    out.append(f"/* {v.base} — the element itself. */")
    out.append(f"static const int64_t KVC_{const(v.component)}_ELEMENT = "
               f"{v.element_id():#018x};")
    out.append("")
    out.append("/* Attribute 0 in every element: the instance reported. */")
    out.append(f"static const int32_t KVC_{const(v.component)}_INSTANCE = "
               f"{INSTANCE_ID};")
    out.append("")

    for key in v.keys:
        out += [f"/* {v.base}.{key['name']} — int64, {key['unit']}, "
                f"{key['kind']}, {key.get('access', 'read')}. */"]
        out.append(f"static const int32_t "
                   f"KVC_{const(v.component)}_{const(key['name'])} = "
                   f"{v.key_id(key)};")
    out.append("")

    for event in v.events:
        out.append(f"/* {v.base}.{event['name']} — event. */")
        out.append(f"static const int32_t "
                   f"KVC_{const(v.component)}_EVENT_{const(event['name'])} = "
                   f"{v.event_id(event)};")
    if v.events:
        out.append("")

    for event, attr in v.attributes():
        out.append(f"static const int32_t KVC_{const(v.component)}_"
                   f"{const(event['name'])}_{const(attr['name'])} = "
                   f"{v.attribute_id(event, attr)};")
    for event, value in v.event_values():
        out.append(f"static const int32_t KVC_{const(v.component)}_"
                   f"{const(event['name'])}_{const(value['name'])} = "
                   f"{v.event_value_id(event, value)};")
    out.append("")

    for owner, members in v.vocabularies():
        out += [f"/* Closed vocabulary of {v.base}.{owner}.",
                " * Generated here and never into the interface: a member is a "
                "value the key",
                " * carries, so adding one must not be an interface change. */",
                "typedef enum {"]
        for m in members:
            out.append(f"    KVC_{const(owner)}_{const(m['name'])} = "
                       f"{m['value']},   /* {flow(m['description'])} */")
        out += [f"}} Kvc{camel(owner)};", ""]

    out += ["/* Every key in this vocabulary, so an identifier seen in a log "
            "or a", " * diagnostic can be resolved back to the name it came "
            "from. */", "typedef struct {", "    int32_t     id;",
            "    const char *name;", "    const char *unit;",
            "    KvcKind     kind;", "} KvcKeyDescriptor;", "",
            f"static const KvcKeyDescriptor "
            f"KVC_{const(v.component)}_KEYS[] = {{"]
    rows = [(v.key_id(k), f"{v.base}.{k['name']}", k["unit"],
             f"KVC_KIND_{const(k['kind'])}") for k in v.keys]
    rows += [(v.attribute_id(e, a), f"{v.base}.{e['name']}.{a['name']}",
              a["unit"], "KVC_KIND_ATTRIBUTE") for e, a in v.attributes()]
    rows += [(v.event_value_id(e, x), f"{v.base}.{e['name']}.{x['name']}",
              x["unit"], f"KVC_KIND_{const(x['kind'])}")
             for e, x in v.event_values()]
    width = max((len(n) for _, n, _, _ in rows), default=0) + 3
    unit_w = max((len(u) for _, _, u, _ in rows), default=0) + 3
    for ident, name, unit, kind in rows:
        quoted_name = '"{}",'.format(name)
        quoted_unit = '"{}",'.format(unit)
        out.append("    {{ {:>3}, {:<{}} {:<{}} {} }},".format(
            ident, quoted_name, width, quoted_unit, unit_w, kind))
    out += ["};", f"#define KVC_{const(v.component)}_KEY_COUNT {len(rows)}", "",
            f"#endif /* {guard} */", ""]
    return "\n".join(out)


def cell(text: str) -> str:
    return flow(text).replace("|", "\\|")


def definition(field: dict) -> str:
    """A field's definition cell, led by its deprecation where it has one."""
    note = f"**Deprecated.** {flow(field['deprecated'])} " \
        if field.get("deprecated") else ""
    return cell(note + field["description"])


def values_table(members: list[dict]) -> list[str]:
    out = ["| Name | Value | Meaning |", "|---|---|---|"]
    out += [f"| `{m['name']}` | {m['value']} | {cell(m['description'])} |"
            for m in members]
    return out + [""]


def module_page(v: Vocabulary) -> Path | None:
    docs = REPO / v.module / "current" / "docs"
    pages = sorted(p for p in docs.glob("*.md") if not p.stem.endswith("_metrics"))
    return pages[0] if len(pages) == 1 else None


def doc_path(v: Vocabulary) -> Path:
    """<stem>_metrics.md beside the module's own page, so the two sort together."""
    page = module_page(v)
    return REPO / v.module / "current" / "docs" / \
        f"{page.stem if page else v.component}_metrics.md"


def title(v: Vocabulary) -> str:
    """The module page's own heading, so "AV Clock" is not rendered "Clock"."""
    page = module_page(v)
    for line in page.read_text().splitlines() if page else []:
        if line.startswith("# "):
            return re.sub(r"\s+HAL$", "", line[2:].strip())
    return " ".join(w.capitalize() for w in v.component.split("_"))


def markdown(v: Vocabulary) -> str:
    source = f"{v.module}/kvc/{v.module}.kvc"
    blob = "https://github.com/rdkcentral/rdk-halif-aidl/blob/develop"
    out = [f"<!-- GENERATED by scripts/kvcc.py from {source}. Do not edit: "
           "change the .kvc and regenerate. -->", "",
           f"# {title(v)} Metrics", "",
           f"The figures `{v.module}` serves through `getMetrics()`"
           + (" and raises through `onMetricEvent()`" if v.events else "")
           + f", generated from its Key Value Contract [`{v.module}.kvc`]"
           f"({blob}/{source}). Every key is served under the requirements in "
           f"[metrics.md]({blob}/metrics/current/docs/metrics.md).", "",
           "|||", "|-|-|",
           f"|**Element**|`{v.base}`|",
           f"|**Element identifier**|`{v.element_id():#018x}`|",
           f"|**Instances**|{v.instances}|"]
    if v.cadence_ms:
        out.append(f"|**Capture cadence**|no slower than {v.cadence_ms} ms|")
    out += [f"|**Schema**|{v.schema}|", "",
            "## Keys", "",
            "| Key | Unit | Kind | Access | Id | Definition |",
            "|---|---|---|---|---|---|"]
    out += [f"| `{k['name']}` | {k['unit']} | {k['kind']} | "
            f"{k.get('access', 'read')} | {v.key_id(k)} | "
            f"{definition(k)} |" for k in v.keys]
    out.append("")
    for k in v.keys:
        if k.get("values"):
            out += [f"**`{k['name']}` values**", ""] + values_table(k["values"])

    if v.events:
        out += ["## Events", ""]
    for e in v.events:
        out += [f"### `{e['name']}`", "",
                f"Id {v.event_id(e)}. {flow(e['description'])}", ""]
        attrs = e.get("attributes") or []
        if attrs:
            out += ["| Attribute | Unit | Id | Definition |",
                    "|---|---|---|---|"]
            out += [f"| `{a['name']}` | {a['unit']} | "
                    f"{v.attribute_id(e, a)} | {definition(a)} |"
                    for a in attrs]
            out.append("")
        values = e.get("values") or []
        if values:
            out += ["| Value | Unit | Kind | Id | Definition |",
                    "|---|---|---|---|---|"]
            out += [f"| `{x['name']}` | {x['unit']} | {x['kind']} | "
                    f"{v.event_value_id(e, x)} | {definition(x)} |"
                    for x in values]
            out.append("")
        for a in attrs:
            if a.get("values"):
                out += [f"**`{a['name']}` values**", ""] + values_table(a["values"])
    return "\n".join(out).rstrip() + "\n"


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Compile module Key Value Contracts into constants.")
    parser.add_argument("--check", action="store_true",
                        help="verify only; write nothing")
    args = parser.parse_args()

    sources = sorted(REPO.glob("*/kvc/*.kvc"))
    if not sources:
        print("no module declares a vocabulary under kvc/",
              file=sys.stderr)
        return 1

    drifted, written = [], 0
    for source in sources:
        module = source.parent.parent.name
        v = Vocabulary(module, source)
        outputs = aidl_files(v)
        outputs[doc_path(v)] = markdown(v)
        # The header is generated, not committed, so a clean checkout has
        # none to compare and --check verifies only what is committed.
        uncommitted = REPO / module / "kvc" / "include" / \
            f"{camel(v.component)}Keys.h"
        outputs[uncommitted] = header(v)
        for path, content in outputs.items():
            if path.exists() and path.read_text() == content:
                continue
            if args.check and path == uncommitted:
                continue
            if args.check:
                drifted.append(path.relative_to(REPO))
                continue
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(content)
            written += 1
        if not args.check:
            print(f"  {module}: "
                  f"{len(v.keys)} keys, {len(v.events)} events, "
                  f"{len(list(v.every_id()))} identifiers")

    if drifted:
        print("generated output is stale:", file=sys.stderr)
        for path in drifted:
            print(f"  {path}", file=sys.stderr)
        print("run scripts/kvcc.py", file=sys.stderr)
        return 1

    verb = "verified" if args.check else f"generated ({written} file(s) written)"
    print(f"{len(sources)} vocabular{'y' if len(sources) == 1 else 'ies'} {verb}")
    return 0


if __name__ == "__main__":
    sys.exit(main())

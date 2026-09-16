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
vocabulary that sits BESIDE its interface versions rather than inside one:

    videodecoder/
    |-- kvc/
    |   `-- current/
    |       |-- videodecoder.kvc          the vocabulary
    |       `-- include/                  generated, not committed
    |-- 0.2.0.0/                          frozen interface
    `-- current/                          interface.yaml names a kvc floor

That placement is the mechanism, not a convention. Publishing a vocabulary
revision creates a directory under kvc/ and touches no interface version, so
the two carry their own version numbers and move on their own cadences.

An identifier is the first 8 bytes of SHA-256 over the composed path and the
terms that give it meaning, big-endian signed 64-bit with the sign bit cleared.
Nothing allocates one and there is no registry, so a layer computes it rather
than being told it, and a key means the same thing wherever it is declared.

    key        "<domain>.<component>.<name>|<unit>|<kind>"
    attribute  "<domain>.<component>.<event>.<name>|<unit>"
    element    "<domain>.<component>"
    event      "<domain>.<component>.<event>"

An attribute takes no kind term: it dimensions an occurrence rather than
measuring anything, so it has no aggregation semantics to state.

Emits, per module:

    <module>/current/com/rdk/hal/<package>/MetricElement.aidl
                                          Metric.aidl
                                          MetricEventKind.aidl
                                          MetricEventAttribute.aidl
    <module>/kvc/current/include/<Component>Keys.h

The AIDL enums name the identifiers so a caller can pass one type-safely. The
header carries the same identifiers for a layer that is not built from AIDL,
along with each closed vocabulary and a descriptor table, so an identifier seen
in a log can be resolved back to the name it came from.

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


def kvc_id(*terms: str) -> int:
    """First 8 bytes of SHA-256 over the terms joined by '|', sign bit cleared."""
    digest = hashlib.sha256("|".join(terms).encode("utf-8")).digest()
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
        self.version = str(doc["version"])
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
        seen: dict[int, str] = {}
        for name, ident in self.every_id():
            if ident in seen and seen[ident] != name:
                raise SystemExit(
                    f"{self.path}: '{name}' and '{seen[ident]}' collide on "
                    f"{ident:#018x}")
            seen[ident] = name

    def element_id(self) -> int:
        return kvc_id(self.base)

    def key_id(self, key: dict) -> int:
        return kvc_id(f"{self.base}.{key['name']}", key["unit"], key["kind"])

    def event_id(self, event: dict) -> int:
        return kvc_id(f"{self.base}.{event['name']}")

    def attribute_id(self, event: dict, attr: dict) -> int:
        return kvc_id(f"{self.base}.{event['name']}.{attr['name']}", attr["unit"])

    def event_value_id(self, event: dict, value: dict) -> int:
        return kvc_id(f"{self.base}.{event['name']}.{value['name']}",
                      value["unit"], value["kind"])

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
        for key in self.keys:
            yield f"{self.base}.{key['name']}", self.key_id(key)
        for event in self.events:
            yield f"{self.base}.{event['name']}", self.event_id(event)
        for event, attr in self.attributes():
            yield (f"{self.base}.{event['name']}.{attr['name']}",
                   self.attribute_id(event, attr))
        for event, value in self.event_values():
            yield (f"{self.base}.{event['name']}.{value['name']}",
                   self.event_value_id(event, value))


def aidl_enum(v: Vocabulary, name: str, brief: str, intro: str,
              members: list[tuple[str, int, str]]) -> str:
    out = [AIDL_LICENCE, f"package com.rdk.hal.{v.package};", ""]
    out += ["/**", f" * @brief     {brief}", " * @author    Gerald Weatherup",
            " *",
            f" * THIS FILE IS GENERATED by scripts/kvcc.py from",
            f" * {v.module}/kvc/current/{v.module}.kvc (vocabulary {v.version},",
            f" * schema {v.schema}). Do not edit: declare the key there and",
            f" * regenerate, so an identifier is derived rather than typed.",
            " */", ""]
    out += ["/**", f" * @brief {brief}", " *"]
    out += [f" * {ln}".rstrip() for ln in textwrap.wrap(flow(intro), width=74)]
    out += [" */", "", "@VintfStability", '@Backing(type="long")',
            f"enum {name}", "{"]
    for member, value, description in members:
        out.append("")
        out += block(description, "    ")
        out.append(f"    {member} = {value:#018x},")
    out += ["}", ""]
    return "\n".join(out)


def aidl_files(v: Vocabulary) -> dict[Path, str]:
    root = REPO / v.module / "current" / "com" / "rdk" / "hal" / v.package
    files = {
        root / "MetricElement.aidl": aidl_enum(
            v, "MetricElement",
            f"Identifier of the element {v.module} reports.",
            "MetricGroup.id carries this. The instance is not part of it, "
            "because how many are live is a property of the moment rather "
            "than of the contract; it is carried as an attribute instead.",
            [(const(v.component), v.element_id(),
              f"`{v.base}` — {v.instances} instance(s)"
              + (f", captured no slower than every {v.cadence_ms} ms"
                 if v.cadence_ms else "") + ".")]),
        root / "Metric.aidl": aidl_enum(
            v, "Metric",
            f"The figures {v.module} measures.",
            "A value carries aggregation semantics, so its identifier "
            "composes with its kind as well as its unit. Serving one in the "
            "wrong unit, or reading it on the wrong cadence for its kind, is "
            "then a mismatch a consumer can detect rather than a plausible "
            "wrong number.",
            [(const(k["name"]), v.key_id(k),
              f"`{v.base}.{k['name']}` — {k['unit']}, {k['kind']}"
              f"{', writable' if k.get('access') == 'readwrite' else ''}. "
              f"{k['description']}") for k in v.keys]),
    }
    if v.events:
        files[root / "MetricEventKind.aidl"] = aidl_enum(
            v, "MetricEventKind",
            f"The occurrences {v.module} raises.",
            "MetricEvent.eventId carries one of these. An occurrence is "
            "pushed because a read cannot carry it: a condition that began "
            "and ended between two reads is invisible to a reader however "
            "fast it polls.",
            [(const(e["name"]), v.event_id(e),
              f"`{v.base}.{e['name']}` — {e['description']}")
             for e in v.events])
    members = [(const(f"{e['name']}_{a['name']}"), v.attribute_id(e, a),
                f"`{v.base}.{e['name']}.{a['name']}` — {a['unit']}. "
                f"{a['description']}") for e, a in v.attributes()]
    members += [(const(f"{e['name']}_{x['name']}"), v.event_value_id(e, x),
                 f"`{v.base}.{e['name']}.{x['name']}` — {x['unit']}, "
                 f"{x['kind']}. {x['description']}") for e, x in v.event_values()]
    if members:
        files[root / "MetricEventAttribute.aidl"] = aidl_enum(
            v, "MetricEventAttribute",
            f"What describes an occurrence {v.module} raised.",
            "An attribute locates and classifies an occurrence rather than "
            "measuring it, so its identifier composes without a kind term. A "
            "value an occurrence measured does carry a kind. Both appear in "
            "MetricEvent, in the array that says which it is.",
            members)
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
        f"/* Generated by kvcc from {v.module}.kvc — vocabulary {v.version}, "
        f"schema {v.schema}.", " * Do not edit. Regenerate to change. */",
        f"#ifndef {guard}", f"#define {guard}", "", "#include <stdint.h>", "",
        f'#define KVC_{const(v.component)}_VOCABULARY "{v.version}"',
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

    for key in v.keys:
        out += [f"/* {v.base}.{key['name']} — int64, {key['unit']}, "
                f"{key['kind']}, {key.get('access', 'read')}. */"]
        out.append(f"static const int64_t "
                   f"KVC_{const(v.component)}_{const(key['name'])} = "
                   f"{v.key_id(key):#018x};")
    out.append("")

    for event in v.events:
        out.append(f"/* {v.base}.{event['name']} — event. */")
        out.append(f"static const int64_t "
                   f"KVC_{const(v.component)}_EVENT_{const(event['name'])} = "
                   f"{v.event_id(event):#018x};")
    if v.events:
        out.append("")

    for event, attr in v.attributes():
        out.append(f"static const int64_t KVC_{const(v.component)}_"
                   f"{const(event['name'])}_{const(attr['name'])} = "
                   f"{v.attribute_id(event, attr):#018x};")
    for event, value in v.event_values():
        out.append(f"static const int64_t KVC_{const(v.component)}_"
                   f"{const(event['name'])}_{const(value['name'])} = "
                   f"{v.event_value_id(event, value):#018x};")
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
            "from. */", "typedef struct {", "    int64_t     id;",
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
        out.append("    {{ {:#018x}, {:<{}} {:<{}} {} }},".format(
            ident, quoted_name, width, quoted_unit, unit_w, kind))
    out += ["};", f"#define KVC_{const(v.component)}_KEY_COUNT {len(rows)}", "",
            f"#endif /* {guard} */", ""]
    return "\n".join(out)


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Compile module Key Value Contracts into constants.")
    parser.add_argument("--check", action="store_true",
                        help="verify only; write nothing")
    args = parser.parse_args()

    sources = sorted(REPO.glob("*/kvc/current/*.kvc"))
    if not sources:
        print("no module declares a vocabulary under kvc/current/",
              file=sys.stderr)
        return 1

    drifted, written = [], 0
    for source in sources:
        module = source.parent.parent.parent.name
        v = Vocabulary(module, source)
        outputs = aidl_files(v)
        outputs[REPO / module / "kvc" / "current" / "include" /
                f"{camel(v.component)}Keys.h"] = header(v)
        for path, content in outputs.items():
            if path.exists() and path.read_text() == content:
                continue
            if args.check:
                drifted.append(path.relative_to(REPO))
                continue
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(content)
            written += 1
        if not args.check:
            print(f"  {module}: vocabulary {v.version}, "
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

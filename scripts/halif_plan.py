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
"""Resolve the topological build order for a set of RDK HAL components.

The single rdk-halif recipe (and the offline role test) build a chosen set of
components in one pass; this prints the order to build them so each component's
sibling dependencies are built first.

Usage:
  halif_plan.py [--versions <manifest.yaml>] <comp[:ver]> ...
      comp        build the component (version from --versions, else the latest)
      comp:ver    build the given version (overrides --versions)
      --versions  a versions manifest (components: {comp: ver}) pinning versions
  halif_plan.py            # all components, each at its latest

Output: one "<comp> <ver>" line per component, dependencies first. Exits non-zero
if a selected component links a sibling that is not in the selection (the set
must be a closure) or references a version that is not released.
"""
import os
import re
import sys

REPO_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
VER_RE = re.compile(r"^\d+\.\d+\.\d+\.\d+$")
LINK_RE = re.compile(r"([a-z0-9]+)-v(\d+\.\d+\.\d+\.\d+)-cpp")


def version_tuple(v):
    return tuple(int(x) for x in v.split("."))


def released_versions(comp):
    d = os.path.join(REPO_ROOT, comp)
    if not os.path.isdir(d):
        return []
    return sorted(
        (v for v in os.listdir(d)
         if VER_RE.match(v) and os.path.isfile(os.path.join(d, v, "CMakeLists.txt"))),
        key=version_tuple,
    )


def all_components():
    comps = []
    for c in sorted(os.listdir(REPO_ROOT)):
        if not c.startswith(".") and os.path.isdir(os.path.join(REPO_ROOT, c)) and released_versions(c):
            comps.append(c)
    return comps


def links(comp, ver):
    """Return {dep_comp: dep_ver} the snapshot links, from its CMakeLists."""
    out = {}
    with open(os.path.join(REPO_ROOT, comp, ver, "CMakeLists.txt")) as fh:
        text = fh.read()
    for block in re.findall(r"target_link_libraries\(([^)]*)\)", text):
        for dep, dver in LINK_RE.findall(block):
            if dep != comp:
                out[dep] = dver
    return out


def parse_versions(path):
    """Return {component: version} from a manifest's `components:` map."""
    pins, in_comp = {}, False
    with open(path) as fh:
        for line in fh:
            s = line.rstrip("\n")
            if not s.strip() or s.strip().startswith("#"):
                continue
            if re.match(r"^components:\s*$", s):
                in_comp = True
                continue
            if in_comp:
                m = re.match(r"^\s+([A-Za-z0-9_]+):\s*(\S+)\s*$", s)
                if m:
                    pins[m.group(1)] = m.group(2)
                elif not s[0].isspace():
                    in_comp = False
    return pins


def main(argv):
    pins = {}
    if argv and argv[0] == "--versions":
        if len(argv) < 2:
            sys.stderr.write("halif_plan: --versions needs a manifest path\n")
            return 2
        pins = parse_versions(argv[1])
        argv = argv[2:]

    items = argv or all_components()
    sel = {}
    for item in items:
        comp, _, ver = item.partition(":")
        vers = released_versions(comp)
        if not vers:
            sys.stderr.write("halif_plan: no released snapshot for '%s'\n" % comp)
            return 2
        if not ver:                       # not pinned inline; try the manifest, else latest
            ver = pins.get(comp) or vers[-1]
        if ver not in vers:
            sys.stderr.write("halif_plan: %s@%s is not a released snapshot\n" % (comp, ver))
            return 2
        sel[comp] = ver

    # Build the dependency graph within the selection and Kahn-sort it.
    edges = {c: set() for c in sel}       # c depends on edges[c]
    for comp, ver in sel.items():
        for dep, dver in links(comp, ver).items():
            if dep not in sel:
                sys.stderr.write(
                    "halif_plan: %s@%s links %s@%s but %s is not in the selection "
                    "(the set must be a closure)\n" % (comp, ver, dep, dver, dep)
                )
                return 2
            if sel[dep] != dver:
                sys.stderr.write(
                    "halif_plan: %s@%s links %s@%s but the selection pins %s@%s\n"
                    % (comp, ver, dep, dver, dep, sel[dep])
                )
                return 2
            edges[comp].add(dep)

    order = []
    ready = sorted(c for c in sel if not edges[c])
    indeg = {c: set(edges[c]) for c in sel}
    while ready:
        c = ready.pop(0)
        order.append(c)
        for other in sorted(sel):
            if c in indeg[other]:
                indeg[other].discard(c)
                if not indeg[other]:
                    ready.append(other)
        ready.sort()
    if len(order) != len(sel):
        sys.stderr.write("halif_plan: dependency cycle among %s\n"
                         % ", ".join(sorted(set(sel) - set(order))))
        return 2

    for c in order:
        print("%s %s" % (c, sel[c]))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))

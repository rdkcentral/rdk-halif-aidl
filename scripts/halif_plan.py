#!/usr/bin/env python3
#** *****************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2026 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# *     http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
#** ******************************************************************************
"""Resolve the topological build order for a set of RDK HAL components.

The single rdk-halif recipe (and the offline role test) build a chosen set of
components in one pass; this prints the order to build them so each component's
sibling dependencies are built first.

Usage:
  halif_plan.py [--closure] [--versions <manifest.yaml>] <comp[:ver]> ...
      comp        build the component (version from --versions, else the latest)
      comp:ver    build the given version (overrides --versions)
      --versions  a versions manifest (components: {comp: ver}) pinning versions
      --closure   expand each component to its transitive dependencies (so a
                  single component becomes a buildable set)
  halif_plan.py --versions m.yaml   # the manifest's components, at its versions
  halif_plan.py                     # all discovered components, each at latest

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
    for comp in sorted(os.listdir(REPO_ROOT)):
        if not comp.startswith(".") and os.path.isdir(os.path.join(REPO_ROOT, comp)) and released_versions(comp):
            comps.append(comp)
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
    closure = False
    while argv and argv[0] in ("--versions", "--closure"):
        if argv[0] == "--closure":
            closure = True
            argv = argv[1:]
        else:  # --versions
            if len(argv) < 2:
                sys.stderr.write("halif_plan: --versions needs a manifest path\n")
                return 2
            pins = parse_versions(argv[1])
            argv = argv[2:]

    # Component set: explicit args win; else the manifest's components (so a
    # versions manifest drives what is built); else every discovered component.
    if argv:
        items = argv
    elif pins:
        items = sorted(pins)
    else:
        items = all_components()
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

    # --closure: pull in each selected component's transitive dependencies at
    # their exact linked versions, so a single component expands to a buildable
    # set. (Without it a non-closure selection is an error, below.)
    if closure:
        queue = list(sel.items())
        while queue:
            comp, ver = queue.pop()
            for dep, dver in links(comp, ver).items():
                if dep not in sel:
                    sel[dep] = dver
                    queue.append((dep, dver))
                elif sel[dep] != dver:
                    sys.stderr.write(
                        "halif_plan: closure conflict - %s@%s links %s@%s but %s is "
                        "already at %s\n" % (comp, ver, dep, dver, dep, sel[dep])
                    )
                    return 2

    # Build the dependency graph within the selection and Kahn-sort it.
    edges = {comp: set() for comp in sel}  # comp depends on edges[comp]
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
    ready = sorted(comp for comp in sel if not edges[comp])
    indeg = {comp: set(edges[comp]) for comp in sel}
    while ready:
        comp = ready.pop(0)
        order.append(comp)
        for other in sorted(sel):
            if comp in indeg[other]:
                indeg[other].discard(comp)
                if not indeg[other]:
                    ready.append(other)
        ready.sort()
    if len(order) != len(sel):
        sys.stderr.write("halif_plan: dependency cycle among %s\n"
                         % ", ".join(sorted(set(sel) - set(order))))
        return 2

    for comp in order:
        print("%s %s" % (comp, sel[comp]))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))

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

You name only the components you WANT; their dependencies are resolved
automatically (the transitive closure), so `common` and other base interfaces
never have to be listed. The closure is keyed by (component, VERSION), so
DIFFERENT versions of one component coexist in a single build: if hdmicec links
common@A and audiodecoder links common@B, this plans BOTH commons, each built at
the exact version its dependent links.

Usage:
  halif_plan.py [--versions <manifest.yaml>] <comp[:ver]> ...
      comp        build the component (version from --versions, else the latest)
      comp:ver    build the given version (overrides --versions)
      --versions  a versions manifest (components: {comp: ver}) pinning the
                  TOP-LEVEL components' versions; dependencies follow their links
      --closure   accepted for backward compatibility; closure is always resolved
  halif_plan.py --versions m.yaml   # the manifest's components + their closure
  halif_plan.py                     # all discovered components, each at latest

Output: one "<comp> <ver>" line per node, dependencies first (the same component
may appear more than once, at different versions). Exits non-zero only on a real
error: a referenced version that is not released, or a dependency cycle.

Directory structure it expects (REPO_ROOT is four levels up from this file,
because this ships inside the layer so the recipe and its planner travel
together):

  rdk-halif-aidl/                     <- REPO_ROOT
  |-- versions_released.yaml          {comp: ver} - the released cohort
  |-- <comp>/<ver>/                   every released snapshot; SEVERAL versions
  |   |                               of one component coexist, e.g.
  |   |                               avclock/{0.1.0.0,0.2.0.0,0.2.0.1}
  |   |-- CMakeLists.txt              parsed: target_link_libraries() gives the
  |   |                               sibling deps AND their exact versions
  |   |                               (-l<dep>-v<ver>-cpp)
  |   `-- interface.yaml              imports: [<dep>@<ver>] - the declared
  |                                   contract; CMake is parsed instead because
  |                                   it is what the link actually requires
  `-- tests/yocto/meta-rdk-halif-aidl/
      `-- halif_plan.py               <- this file

A component is only discovered if <comp>/<ver>/CMakeLists.txt exists, so
placeholder directories are ignored.
"""
import os
import re
import sys

# This script ships inside the layer at tests/yocto/meta-rdk-halif-aidl/,
# four levels below the repo root it scans for component snapshots.
REPO_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(
    os.path.dirname(os.path.abspath(__file__)))))
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
                m = re.match(r"^\s+([A-Za-z0-9_]+):\s*(\S+)\s*(?:#.*)?$", s)
                if m:
                    pins[m.group(1)] = m.group(2)
                elif not s[0].isspace():
                    in_comp = False
    return pins


def main(argv):
    pins = {}
    while argv and argv[0] in ("--versions", "--closure"):
        if argv[0] == "--closure":
            argv = argv[1:]              # accepted for back-compat; closure is always on
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

    # Seed the selection with the requested (component, version) pairs. Only the
    # TOP-LEVEL components are named here; their dependencies are resolved below.
    sel = set()                          # {(comp, ver)}
    for item in items:
        comp, _, ver = item.partition(":")
        vers = released_versions(comp)
        if not vers:
            sys.stderr.write("halif_plan: no released snapshot for '%s'\n" % comp)
            return 2
        if not ver:                      # not pinned inline; try the manifest, else latest
            ver = pins.get(comp) or vers[-1]
        if ver not in vers:
            sys.stderr.write("halif_plan: %s@%s is not a released snapshot\n" % (comp, ver))
            return 2
        sel.add((comp, ver))

    # Resolve the transitive closure, keyed by (component, VERSION). Because the
    # key carries the version, different versions of the same component coexist:
    # each dependency is pulled in at the exact version its dependent links, so
    # hdmicec's common@A and audiodecoder's common@B are BOTH built. This is why a
    # build never has to name common - it follows from what the selection links.
    queue = list(sel)
    while queue:
        comp, ver = queue.pop()
        for dep, dver in links(comp, ver).items():
            if dver not in released_versions(dep):
                sys.stderr.write("halif_plan: %s@%s links %s@%s which is not a "
                                 "released snapshot\n" % (comp, ver, dep, dver))
                return 2
            if (dep, dver) not in sel:
                sel.add((dep, dver))
                queue.append((dep, dver))

    # Build the dependency graph over (comp, ver) nodes and Kahn-sort it. The
    # closure above guarantees every linked (dep, dver) is a node.
    edges = {node: set() for node in sel}          # node depends on edges[node]
    for (comp, ver) in sel:
        for dep, dver in links(comp, ver).items():
            edges[(comp, ver)].add((dep, dver))

    order = []
    indeg = {n: set(edges[n]) for n in sel}
    ready = sorted(n for n in sel if not indeg[n])
    while ready:
        n = ready.pop(0)
        order.append(n)
        for other in sorted(sel):
            if n in indeg[other]:
                indeg[other].discard(n)
                if not indeg[other]:
                    ready.append(other)
        ready.sort()
    if len(order) != len(sel):
        stuck = sorted(set(sel) - set(order))
        sys.stderr.write("halif_plan: dependency cycle among %s\n"
                         % ", ".join("%s@%s" % cv for cv in stuck))
        return 2

    for (comp, ver) in order:
        print("%s %s" % (comp, ver))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))

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

"""aidl_compat.py - the compiler's verdict on a component's change class.

Compares a component's last released snapshot with current/ two ways, both
with the AIDL compiler the build uses:

    wire    - aidl --checkapi: do binaries built against the old version
              still talk to the new one? equal / compatible / incompatible.
    source  - the C++ headers aidl generates, regenerated for both sides with
              identical flags and compared declaration by declaration: does
              code built against the old headers have to change? Headers the
              component includes from other components are compared too, at
              the dependency version each side was built against, so a type
              change in an import (e.g. common's PropertyValue string arm,
              String16 -> std::string) reaches every component that uses it.

Prints one JSON object:

    {"recommended": "major|minor|bugfix|none",
     "wire": "...", "source": "...", "inherited": "...",
     "evidence": ["...", ...]}

"bugfix" is never returned on its own: when every check is clean the result is
"none", and release.sh turns that into bugfix when the AIDL bytes changed.

Usage: aidl_compat.py --repo <repo> --aidl <aidl binary> [--cache <file>]
                      [--old-repo <checkout>] <component> <released version>

--old-repo takes the old side from another checkout, so a pull request's base
can be compared with its head: `--old-repo <base> <component> current`. Each
side's imports resolve inside its own tree.

With --cache, a verdict is reused while the content of every directory it
read (both sides and their transitive imports) and the aidl binary are
unchanged.
"""

import argparse
import difflib
import hashlib
import json
import os
import re
import subprocess
import sys
import tempfile

RANK = {"none": 0, "bugfix": 1, "minor": 2, "major": 3}
_IMPORT_RE = re.compile(r"^\s+-\s+([A-Za-z0-9_/]+)@(\S+)\s*$")
_INCLUDE_RE = re.compile(r"#include\s+<(com/rdk/hal/[^>]+\.h)>")


def _highest(*classes):
    return max(classes, key=lambda c: RANK[c])


def _imports(comp_dir):
    """[(dep, version)] from a component dir's interface.yaml."""
    path = os.path.join(comp_dir, "interface.yaml")
    out, inblock = [], False
    if not os.path.isfile(path):
        return out
    with open(path) as fh:
        for line in fh:
            if re.match(r"^\s*imports:\s*$", line):
                inblock = True
                continue
            if inblock:
                m = _IMPORT_RE.match(line)
                if m:
                    out.append((m.group(1), m.group(2)))
                elif line.strip() and not line.startswith("    "):
                    inblock = False
    return out


def _root_of(comp_dir):
    """The checkout holding comp_dir: the nearest parent with build_modules.sh."""
    d = os.path.abspath(comp_dir)
    while d != os.path.dirname(d):
        d = os.path.dirname(d)
        if os.path.isfile(os.path.join(d, "build_modules.sh")):
            return d
    return None


def _dep_dirs(repo, comp_dir):
    """{dep: dir} for the transitive imports of comp_dir; the nearest pin wins.
    Imports resolve in comp_dir's own checkout, falling back to repo."""
    root = _root_of(comp_dir) or repo
    found, queue = {}, [comp_dir]
    while queue:
        for dep, ver in _imports(queue.pop(0)):
            d = os.path.join(root, dep, ver)
            if dep not in found and os.path.isdir(d):
                found[dep] = d
                queue.append(d)
    return found


def _aidl_files(root):
    files = []
    for dirpath, dirnames, filenames in os.walk(os.path.join(root, "com")):
        dirnames.sort()
        files += [os.path.join(dirpath, f) for f in sorted(filenames) if f.endswith(".aidl")]
    return files


def _includes(deps):
    return ["-I" + d for d in deps.values()]


# ---------------------------------------------------------------------------
# Wire: aidl --checkapi
# ---------------------------------------------------------------------------

def _checkapi(aidl, level, incs, old, new):
    r = subprocess.run([aidl, "--checkapi=" + level, "--stability=vintf"] + incs + [old, new],
                       capture_output=True, text=True)
    return r.returncode, r.stderr


def wire_check(aidl, repo, old, new, evidence):
    # checkapi takes one include set for both sides and compares only the
    # component's own types; try the new side's imports, then the old's.
    for deps in (_dep_dirs(repo, new), _dep_dirs(repo, old)):
        incs = _includes(deps)
        rc, err = _checkapi(aidl, "equal", incs, old, new)
        if rc == 0:
            return "none"
        rc, err = _checkapi(aidl, "compatible", incs, old, new)
        if rc == 0:
            return "minor"
        if not re.search(r"Couldn't find import|Failed to read|Failed to resolve|Duplicate files", err):
            for line in err.splitlines():
                if line.startswith("ERROR"):
                    evidence.append("wire: " + re.sub(r"^ERROR: \S*/([^/]+\.aidl)[:0-9.-]*: ", r"\1: ", line))
            return "major"
    evidence.append("wire: aidl --checkapi could not resolve the imports")
    return "unknown"


# ---------------------------------------------------------------------------
# Source: regenerated C++ headers
# ---------------------------------------------------------------------------

_HEADER_CACHE = {}


def gen_headers(aidl, repo, comp_dir, workdir):
    """Generate comp_dir's C++ headers; returns the include dir (cached)."""
    if comp_dir in _HEADER_CACHE:
        return _HEADER_CACHE[comp_dir]
    out = os.path.join(workdir, "h%d" % len(_HEADER_CACHE))
    deps = _dep_dirs(repo, comp_dir)
    cmd = [aidl, "--lang=cpp", "--structured", "--min_sdk_version=33", "--stability=vintf",
           "-I" + comp_dir] + _includes(deps) + [
           "-h", os.path.join(out, "include"), "--out", os.path.join(out, "src"),
           "--version=1", "--hash=notfrozen"] + _aidl_files(comp_dir)
    r = subprocess.run(cmd, capture_output=True, text=True)
    inc = os.path.join(out, "include") if r.returncode == 0 else None
    _HEADER_CACHE[comp_dir] = inc
    return inc


def _strip_block(text, start_re):
    """Remove every brace-balanced block whose head matches start_re."""
    while True:
        m = re.search(start_re, text)
        if not m:
            return text
        i = text.find("{", m.end() - 1)
        if i < 0:
            return text
        depth, j = 0, i
        while j < len(text):
            depth += {"{": 1, "}": -1}.get(text[j], 0)
            j += 1
            if depth == 0:
                break
        if j < len(text) and text[j] == ";":
            j += 1
        text = text[:m.start()] + text[j:]


def declarations(path):
    """A header's declarations, normalised: comments, preprocessor lines and
    the boilerplate aidl derives from an enum's value list are dropped, so an
    added enum value reads as one added declaration, not a rewritten array."""
    with open(path, errors="replace") as fh:
        text = fh.read()
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.S)
    text = re.sub(r"//[^\n]*", " ", text)
    text = re.sub(r"^\s*#.*$", " ", text, flags=re.M)
    text = _strip_block(text, r"static\s+inline\s+std::string\s+toString\s*\(")
    text = _strip_block(text, r"constexpr\s+inline\s+std::array<[^=]*=\s*\{")
    text = re.sub(r"\s+", " ", text)
    # Commas split too: an enum body and a template argument list are one
    # statement, and a single added value must not read as a rewrite.
    parts = re.split(r"(?<=[;{},])", text)
    return [p.strip().rstrip(",").strip() for p in parts
            if p.strip().rstrip(",").strip() not in ("", "{", "}", "};", ";")]


def _short(decl, limit=110):
    return decl if len(decl) <= limit else decl[:limit - 1] + "…"


def compare_header(old_h, new_h, label, evidence):
    """Class of the change between two generated headers."""
    old_d, new_d = set(declarations(old_h)), set(declarations(new_h))
    removed, added = sorted(old_d - new_d), sorted(new_d - old_d)
    if not removed and not added:
        return "none"
    if not removed:
        evidence.append("%s: added %s%s" % (label, _short(added[0], 80),
                                            " (+%d more)" % (len(added) - 1) if len(added) > 1 else ""))
        return "minor"
    for r in removed[:3]:
        near = difflib.get_close_matches(r, added, n=1, cutoff=0.6)
        evidence.append("%s: %s" % (label, _short(r) + (" → " + _short(near[0]) if near else " (removed)")))
    return "major"


def source_check(aidl, repo, comp, old, new, workdir, evidence):
    old_inc, new_inc = gen_headers(aidl, repo, old, workdir), gen_headers(aidl, repo, new, workdir)
    if not old_inc or not new_inc:
        evidence.append("source: could not regenerate the C++ headers")
        return "unknown", "unknown"
    own, own_files = "none", set()
    for dirpath, _, filenames in os.walk(new_inc):
        for f in filenames:
            rel = os.path.relpath(os.path.join(dirpath, f), new_inc)
            own_files.add(rel)
    old_files = {os.path.relpath(os.path.join(d, f), old_inc)
                 for d, _, fs in os.walk(old_inc) for f in fs}
    for rel in sorted(old_files - own_files):
        evidence.append("source: %s removed" % rel)
        own = "major"
    for rel in sorted(own_files):
        o, n = os.path.join(old_inc, rel), os.path.join(new_inc, rel)
        own = _highest(own, compare_header(o, n, "source " + os.path.basename(rel), evidence)
                       if os.path.isfile(o) else "minor")
    # Hand-authored public headers at the module root (avbufferhelper.h,
    # halcompat.h) ship in the snapshot's include/ and version with it.
    for f in sorted(set(os.listdir(old)) | set(os.listdir(new))):
        if not f.endswith(".h"):
            continue
        o, n = os.path.join(old, f), os.path.join(new, f)
        if not os.path.isfile(n):
            evidence.append("source: %s removed" % f)
            own = "major"
        elif not os.path.isfile(o):
            own = _highest(own, "minor")
        else:
            own = _highest(own, compare_header(o, n, "source " + f, evidence))

    # Types from other components, at the version each side was built
    # against. A component is affected when a type it names is changed, or
    # (by value, at any depth) contains a changed type. A nested type such
    # as IAudioDecoder::Id is followed through its own block, not through
    # the interface around it; a whole interface it names is followed
    # through its methods, since the code may call any of them. An addition
    # in an import does not force a rebuild; a removed or changed
    # declaration does.
    old_deps, new_deps = _dep_dirs(repo, old), _dep_dirs(repo, new)
    new_dirs = [new_inc]
    changed = {}       # header path -> evidence label
    for dep, new_dir in sorted(new_deps.items()):
        d_new = gen_headers(aidl, repo, new_dir, workdir)
        if d_new:
            new_dirs.append(d_new)
        old_dir = old_deps.get(dep)
        if not old_dir or old_dir == new_dir or not d_new:
            continue
        d_old = gen_headers(aidl, repo, old_dir, workdir)
        if not d_old:
            continue
        for dirpath, _, filenames in os.walk(d_new):
            for f in filenames:
                rel = os.path.relpath(os.path.join(dirpath, f), d_new)
                o = os.path.join(d_old, rel)
                if os.path.isfile(o):
                    ev = []
                    if compare_header(o, os.path.join(d_new, rel), "%s %s" % (dep, f), ev) == "major":
                        changed[rel] = ev
    inherited = "none"
    hits = _reaches_changed(new_inc, own_files, new_dirs, changed)
    for via, rel in hits:
        inherited = "major"
        evidence.append("inherited via %s: %s" % (via, changed[rel][0] if changed[rel] else rel))
    return own, inherited


_QNAME_RE = re.compile(r"::com::rdk::hal(?:::\w+)+")


def _header_for(qname):
    """::com::rdk::hal::pkg::Type::Nested -> ("com/rdk/hal/pkg/Type.h", ["Nested"])."""
    parts = qname.strip(":").split("::")
    for i, p in enumerate(parts):
        if p[:1].isupper():
            return "/".join(parts[:i + 1]) + ".h", parts[i + 1:]
    return None, []


def _class_block(text, name):
    m = re.search(r"\b(?:class|struct)\s+%s\b[^;{]*\{" % re.escape(name), text)
    if not m:
        return ""
    depth, j = 0, m.end() - 1
    while j < len(text):
        depth += {"{": 1, "}": -1}.get(text[j], 0)
        j += 1
        if depth == 0:
            break
    return text[m.end():j]


def _clean(path):
    with open(path, errors="replace") as fh:
        text = fh.read()
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.S)
    return re.sub(r"//[^\n]*", " ", text)


def _reaches_changed(own_inc, own_files, inc_dirs, changed):
    """[(type named by the component, changed header)] it depends on."""
    def find(rel):
        for d in inc_dirs:
            if os.path.isfile(os.path.join(d, rel)):
                return os.path.join(d, rel)
        return None

    def body(qname):
        rel, nested = _header_for(qname)
        path = find(rel) if rel else None
        if not path:
            return rel, ""
        text = _clean(path)
        for n in nested:
            text = _class_block(text, n)
        return rel, text

    memo = {}

    def hit(qname, depth=0):
        if qname in memo:
            return memo[qname]
        memo[qname] = None            # cycle guard
        rel, text = body(qname)
        found = rel if rel in changed else None
        if not found and depth < 8:
            for ref in set(_QNAME_RE.findall(text)):
                if ref != qname and not qname.startswith(ref + "::"):
                    found = hit(ref, depth + 1)
                    if found:
                        break
        memo[qname] = found
        return found

    refs = set()
    for rel in own_files:
        refs.update(_QNAME_RE.findall(_clean(os.path.join(own_inc, rel))))
    out = []
    for ref in sorted(refs):
        rel, _ = _header_for(ref)
        if rel in own_files:
            continue
        found = hit(ref)
        if found:
            out.append((ref.replace("::com::rdk::hal::", ""), found))
    seen, uniq = set(), []
    for via, rel in out:
        if rel not in seen:
            seen.add(rel)
            uniq.append((via, rel))
    return uniq


def _content_key(aidl, repo, old, new):
    """Hash of everything the verdict depends on."""
    h = hashlib.sha1()
    with open(aidl, "rb") as fh:
        h.update(hashlib.sha1(fh.read()).digest())
    h.update(open(__file__, "rb").read())
    dirs = {old, new} | set(_dep_dirs(repo, old).values()) | set(_dep_dirs(repo, new).values())
    for d in sorted(dirs):
        for dirpath, dirnames, filenames in os.walk(d):
            dirnames[:] = sorted(x for x in dirnames if x not in ("include", "src", "docs"))
            for f in sorted(filenames):
                if f.endswith((".aidl", ".h")) or f == "interface.yaml":
                    path = os.path.join(dirpath, f)
                    h.update(os.path.relpath(path, _root_of(d) or repo).encode())
                    h.update(b"old" if d == old else b"")
                    with open(path, "rb") as fh:
                        h.update(hashlib.sha1(fh.read()).digest())
    return h.hexdigest()


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--repo", required=True)
    ap.add_argument("--aidl", required=True)
    ap.add_argument("--cache")
    ap.add_argument("--old-repo")
    ap.add_argument("component")
    ap.add_argument("released")
    a = ap.parse_args(argv)
    # aidl misreads a "./" path prefix as a different package root.
    a.repo = os.path.abspath(a.repo)
    a.old_repo = os.path.abspath(a.old_repo) if a.old_repo else None
    old = os.path.join(a.old_repo or a.repo, a.component, a.released)
    new = os.path.join(a.repo, a.component, "current")
    key = cache = None
    if a.cache:
        key = "%s@%s:%s" % (a.component, a.released, _content_key(a.aidl, a.repo, old, new))
        try:
            with open(a.cache) as fh:
                cache = json.load(fh)
        except (OSError, ValueError):
            cache = {}
        if key in cache:
            json.dump(cache[key], sys.stdout)
            sys.stdout.write("\n")
            return 0
    evidence = []
    wire = wire_check(a.aidl, a.repo, old, new, evidence)
    with tempfile.TemporaryDirectory() as work:
        source, inherited = source_check(a.aidl, a.repo, a.component, old, new, work, evidence)
    known = [c for c in (wire, source, inherited) if c != "unknown"]
    result = {
        "recommended": _highest(*known) if known else "unknown",
        "wire": wire, "source": source, "inherited": inherited,
        "evidence": evidence,
    }
    if cache is not None and result["recommended"] != "unknown":
        cache = {k: v for k, v in cache.items() if not k.startswith(a.component + "@")}
        cache[key] = result
        os.makedirs(os.path.dirname(os.path.abspath(a.cache)), exist_ok=True)
        with open(a.cache + ".tmp", "w") as fh:
            json.dump(cache, fh)
        os.replace(a.cache + ".tmp", a.cache)
    json.dump(result, sys.stdout)
    sys.stdout.write("\n")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))

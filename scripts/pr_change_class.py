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
"""pr_change_class.py - check a pull request's change-class label against the compiler.

For every component whose current/ the pull request touches, aidl_compat.py
compares the base checkout's current/ with the head's. The pull request's label
must be at least the highest class found, so a break is labelled while the pull
request is open, not discovered at the release. A label above the compiler is
accepted: behaviour can change behind an unchanged API.

Labels map as release.sh reads them: "Major Change" (or the retired "Breaking
Change") is major, "Minor Change" minor, "documentation" bugfix, and no class
label is release.sh's default, minor.

Usage: pr_change_class.py --aidl <aidl> --base <base checkout> --base-ref <sha>
                          --labels <comma-separated> [--summary <file>]

Writes a Markdown table to --summary (e.g. $GITHUB_STEP_SUMMARY) and stdout.
Exits 1 when the label is below the compiler's class. A component the compiler
cannot classify (its base does not build, say) is reported, not failed: the
release audit classifies it again at the cut.
"""

import argparse
import json
import os
import re
import subprocess
import sys

RANK = {"none": 0, "bugfix": 1, "minor": 2, "major": 3}
LABEL = {"major": "Major Change", "minor": "Minor Change", "bugfix": "documentation"}
HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)


def label_class(labels):
    names = {l.strip() for l in labels.split(",") if l.strip()}
    if names & {"Major Change", "Breaking Change"}:
        return "major", True
    if "Minor Change" in names:
        return "minor", True
    if "documentation" in names:
        return "bugfix", True
    return "minor", False


def touched_components(base_ref):
    out = subprocess.run(["git", "-C", REPO, "diff", "--name-only", base_ref + "...HEAD"],
                         capture_output=True, text=True, check=True).stdout
    comps = set()
    for path in out.splitlines():
        m = re.match(r"^(.+?)/current/", path)
        if m and os.path.isfile(os.path.join(REPO, m.group(1), "current", "interface.yaml")):
            comps.add(m.group(1))
    return sorted(comps)


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--aidl", required=True)
    ap.add_argument("--base", required=True)
    ap.add_argument("--base-ref", required=True)
    ap.add_argument("--labels", default="")
    ap.add_argument("--summary")
    a = ap.parse_args(argv)

    have, explicit = label_class(a.labels)
    rows, need, unknown = [], "none", []
    for comp in touched_components(a.base_ref):
        if not os.path.isdir(os.path.join(a.base, comp, "current")):
            rows.append((comp, "new", "a new component starts at its initial release"))
            continue
        r = subprocess.run([sys.executable, os.path.join(HERE, "aidl_compat.py"), "--repo", REPO,
                            "--aidl", a.aidl, "--old-repo", a.base, comp, "current"],
                           capture_output=True, text=True)
        try:
            v = json.loads(r.stdout)
        except ValueError:
            rows.append((comp, "unknown", (r.stderr.strip().splitlines() or ["no output"])[-1]))
            unknown.append(comp)
            continue
        cls = v["recommended"]
        if cls == "unknown":
            unknown.append(comp)
        else:
            need = max(need, cls, key=lambda c: RANK[c])
        rows.append((comp, cls, "; ".join(v["evidence"][:3]) or "no interface change"))

    shown = LABEL[have] if explicit else "none (release.sh reads it as minor)"
    lines = ["### Change class: compiler vs label", "",
             "Label: **%s**" % shown, "",
             "| Component | Compiler | Evidence |", "| --- | --- | --- |"]
    lines += ["| `%s` | %s | %s |" % (c, k, e.replace("|", "\\|")) for c, k, e in rows]
    lines.append("")
    failed = RANK[need] > RANK[have]
    if not rows:
        lines.append("No component's `current/` changed.")
    elif failed:
        lines.append("❌ The compiler finds **%s**, above the label. Label this pull request "
                     "**%s**." % (need, LABEL[need]))
    else:
        lines.append("✅ The label covers what the compiler found.")
    if unknown:
        lines.append("")
        lines.append("⚠️ Not classified: %s. The release audit checks %s at the cut."
                     % (", ".join("`%s`" % c for c in unknown), "it" if len(unknown) == 1 else "them"))
    text = "\n".join(lines) + "\n"
    sys.stdout.write(text)
    if a.summary:
        with open(a.summary, "a") as fh:
            fh.write(text)
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))

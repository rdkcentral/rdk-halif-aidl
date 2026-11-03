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

"""release_heatmap.py - the open work by component and milestone, from GitHub.

Run at any time. It reads the open issues, their labels and milestones, and
the Priority and Interface Effect fields of project 41, and writes one markdown
page:

    Heatmap     components (component:* labels) x open milestones
    Checks      a Major on a patch milestone, labels that disagree with the
                Interface Effect, tickets with no milestone/priority/effect
    Milestones  each milestone's tickets, ranked by score

Usage:
    scripts/release_heatmap.py                 # print the page
    scripts/release_heatmap.py -o page.md      # write it to a file
    scripts/release_heatmap.py --publish       # push it to the wiki page
    [--maintainer LOGIN ...]                   # raised by anyone else scores 2

Needs `gh`, logged in with read access to the repo and the project; --publish
also needs push access to the wiki. No workflow or secret is involved (#976).
"""

import argparse
import datetime
import importlib.util
import json
import os
import re
import subprocess
import sys
import tempfile

REPO = os.environ.get("GITHUB_REPOSITORY", "rdkcentral/rdk-halif-aidl")
OWNER, NAME = REPO.split("/")
PROJECT_NUMBER = int(os.environ.get("PROJECT_NUMBER", "41"))
WIKI_PAGE = "Release-Heatmap"
HERE = os.path.dirname(os.path.abspath(__file__))

# The change classes are the project sync's: one mapping from labels to the
# Interface Effect, so this page and the board never read a label differently.
_spec = importlib.util.spec_from_file_location(
    "project_interface_effect", os.path.join(HERE, "project_interface_effect.py"))
pie = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(pie)

BREAKING = {"Major", "CR-Major"}
PRIORITY_POINTS = {"P0": 5, "P1": 3, "P2": 1, "P3": 0}
TIERS = [(7, "Do first"), (4, "Next"), (0, "Later")]
NO_MILESTONE = "No milestone"


def gh_json(args):
    return json.loads(subprocess.check_output(["gh"] + args))


def graphql(query, **variables):
    args = ["api", "graphql", "-f", "query=" + query]
    for k, v in variables.items():
        if v is not None:
            args += ["-f", "%s=%s" % (k, v)]
    return gh_json(args)["data"]


ISSUES = """
query($owner:String!,$name:String!,$cursor:String){
  repository(owner:$owner,name:$name){
    issues(first:50,after:$cursor,states:[OPEN]){
      pageInfo{ hasNextPage endCursor }
      nodes{
        number title url
        author{ login }
        milestone{ title dueOn }
        labels(first:50){ nodes{ name } }
        participants{ totalCount }
        timelineItems(itemTypes:[CROSS_REFERENCED_EVENT]){ totalCount }
        issueDependenciesSummary{ blocking }
        projectItems(first:10){ nodes{
          project{ number }
          fieldValues(first:30){ nodes{
            ... on ProjectV2ItemFieldSingleSelectValue{ name field{ ... on ProjectV2SingleSelectField{ name } } }
          } }
        } }
      }
    }
  }
}
"""


def fetch_issues():
    out, cursor = [], None
    while True:
        page = graphql(ISSUES, owner=OWNER, name=NAME, cursor=cursor)["repository"]["issues"]
        out += page["nodes"]
        if not page["pageInfo"]["hasNextPage"]:
            return out
        cursor = page["pageInfo"]["endCursor"]


def fetch_milestones():
    """Open milestones, in version order, with their due dates."""
    ms = gh_json(["api", "repos/%s/milestones?state=open&per_page=100" % REPO])

    def key(m):
        nums = re.findall(r"\d+", m["title"].split(" ")[0])
        return [int(n) for n in nums] or [10 ** 6]
    return sorted(({"title": m["title"], "due": m["due_on"]} for m in ms), key=key)


def is_patch(title):
    """A patch milestone (x.y.z, z > 0) cannot carry a Major."""
    m = re.match(r"^(\d+)\.(\d+)\.(\d+)", title)
    return bool(m and int(m.group(3)) > 0)


def project_fields(issue):
    for item in issue["projectItems"]["nodes"]:
        if item["project"]["number"] == PROJECT_NUMBER:
            return {v["field"]["name"]: v["name"]
                    for v in item["fieldValues"]["nodes"] if v and v.get("field")}
    return {}


def classify(issue, maintainers, today, next_due):
    labels = [l["name"] for l in issue["labels"]["nodes"]]
    fields = project_fields(issue)
    label_class = pie.class_of(labels)
    # Labels win, as in the project sync; the field fills in where none is set.
    effect = label_class or fields.get("Interface Effect")
    priority = (fields.get("Priority") or "").split(" ")[0] or None
    ms = issue["milestone"]
    due = ms["dueOn"][:10] if ms and ms["dueOn"] else None
    comps = sorted(l[len("component:"):] for l in labels if l.startswith("component:"))
    if not comps:
        comps = ["(infrastructure)"] if "scope:infrastructure" in labels else ["(no component)"]

    score, why = 0, []
    if priority in PRIORITY_POINTS and PRIORITY_POINTS[priority]:
        score += PRIORITY_POINTS[priority]; why.append(priority)
    if issue["issueDependenciesSummary"]["blocking"]:
        score += 3; why.append("blocks %d" % issue["issueDependenciesSummary"]["blocking"])
    login = (issue["author"] or {}).get("login", "")
    if maintainers and login not in maintainers:
        score += 2; why.append("raised by %s" % login)
    if effect in BREAKING:
        score += 2; why.append("breaking")
    if due and due < today:
        score += 2; why.append("overdue")
    elif due and due == next_due:
        score += 1; why.append("next due")
    if issue["participants"]["totalCount"] >= 3:
        score += 1; why.append("%d people" % issue["participants"]["totalCount"])
    if issue["timelineItems"]["totalCount"] >= 6:
        score += 1; why.append("%d refs" % issue["timelineItems"]["totalCount"])

    return {
        "number": issue["number"], "title": issue["title"], "url": issue["url"],
        "milestone": ms["title"] if ms else NO_MILESTONE, "components": comps,
        "effect": effect, "label_class": label_class, "field": fields.get("Interface Effect"),
        "priority": priority, "score": score, "why": why,
        "tier": next(t for floor, t in TIERS if score >= floor),
    }


def heat(n):
    return "·" if n == 0 else "🟨" if n <= 2 else "🟧" if n <= 5 else "🟥"


def cell(tickets):
    if not tickets:
        return "·"
    major = sum(1 for t in tickets if t["effect"] in BREAKING)
    return "%s %d%s" % (heat(len(tickets)), len(tickets), " (%d major)" % major if major else "")


def esc(text):
    return text.replace("|", "\\|")


def link(t):
    return "[#%d](%s) %s" % (t["number"], t["url"], esc(t["title"][:80]))


def render(tickets, milestones, generated):
    used = {t["milestone"] for t in tickets}
    cols = [m["title"] for m in milestones if m["title"] in used]
    cols += [NO_MILESTONE] if NO_MILESTONE in used else []
    short = {c: (c if c == NO_MILESTONE else c.split(" ")[0]) for c in cols}
    comps = sorted({c for t in tickets for c in t["components"]},
                   key=lambda c: (c.startswith("("), c))
    lines = [
        "# Release heatmap", "",
        "_Generated %s by `scripts/release_heatmap.py` from the open issues, their "
        "labels and milestones, and project %d. Do not edit by hand: re-run the "
        "script._" % (generated, PROJECT_NUMBER), "",
        "%d open issues. A ticket on several components counts once on each. "
        "🟨 1–2 · 🟧 3–5 · 🟥 6 or more; _major_ is an Interface Effect of Major "
        "or CR-Major." % len(tickets), "",
        "## Heatmap", "",
        "| Component | " + " | ".join(short[c] for c in cols) + " | Total |",
        "| --- |" + " --- |" * (len(cols) + 1),
    ]
    for comp in comps:
        row = [t for t in tickets if comp in t["components"]]
        lines.append("| %s | %s | %d |" % (comp, " | ".join(
            cell([t for t in row if t["milestone"] == c]) for c in cols), len(row)))
    lines.append("| **Tickets** | %s | **%d** |" % (" | ".join(
        "**%d**" % sum(1 for t in tickets if t["milestone"] == c) for c in cols), len(tickets)))

    # Checks
    checks = []
    for t in tickets:
        if t["effect"] in BREAKING and is_patch(t["milestone"]):
            checks.append((t, "%s on patch milestone %s: a patch release cannot break"
                           % (t["effect"], short[t["milestone"]])))
        if t["field"] and t["label_class"] and t["field"] != t["label_class"]:
            checks.append((t, "labels say %s, Interface Effect says %s"
                           % (t["label_class"], t["field"])))
    gaps = {
        "no milestone": [t for t in tickets if t["milestone"] == NO_MILESTONE],
        "no priority": [t for t in tickets if not t["priority"]],
        "no Interface Effect": [t for t in tickets if not t["effect"]],
    }
    lines += ["", "## Checks", ""]
    if checks:
        lines += ["| Ticket | Problem |", "| --- | --- |"]
        lines += ["| %s | %s |" % (link(t), p) for t, p in checks]
    else:
        lines.append("No Major on a patch milestone, and every label agrees with its Interface Effect.")
    lines += ["", "| Gap | Tickets |", "| --- | --- |"]
    for name, ts in gaps.items():
        nums = ", ".join("[#%d](%s)" % (t["number"], t["url"]) for t in sorted(ts, key=lambda t: t["number"]))
        lines.append("| %s (%d) | %s |" % (name, len(ts), nums or "none"))

    # Milestones
    lines += ["", "## Milestones", "",
              "Score: P0 5, P1 3, P2 1; blocks another ticket 3; breaking 2; overdue 2; "
              "milestone due next 1; three or more people 1; six or more references 1"
              "%s. Do first is 7 or more, Next 4 to 6." % (
                  "; raised by someone other than a maintainer 2"
                  if any("raised by" in w for t in tickets for w in t["why"]) else "")]
    for c in cols:
        ts = sorted((t for t in tickets if t["milestone"] == c), key=lambda t: (-t["score"], t["number"]))
        if not ts:
            continue
        due = next((m["due"][:10] for m in milestones if m["title"] == c and m["due"]), None)
        lines += ["", "### %s%s (%d)" % (c, ", due %s" % due if due else "", len(ts)), "",
                  "| Ticket | Components | Effect | Priority | Score | Tier | Why |",
                  "| --- | --- | --- | --- | --- | --- | --- |"]
        for t in ts:
            lines.append("| %s | %s | %s | %s | %d | %s | %s |" % (
                link(t), ", ".join(t["components"]), t["effect"] or "—", t["priority"] or "—",
                t["score"], t["tier"], ", ".join(t["why"]) or "—"))
    return "\n".join(lines) + "\n"


def publish(page):
    """Commit the page to the wiki repo; a no-op when nothing changed."""
    with tempfile.TemporaryDirectory() as tmp:
        wiki = os.path.join(tmp, "wiki")
        subprocess.run(["git", "clone", "-q", "--depth", "1",
                        "https://github.com/%s.wiki.git" % REPO, wiki], check=True)
        with open(os.path.join(wiki, WIKI_PAGE + ".md"), "w") as fh:
            fh.write(page)
        subprocess.run(["git", "-C", wiki, "add", WIKI_PAGE + ".md"], check=True)
        if subprocess.run(["git", "-C", wiki, "diff", "--cached", "--quiet"]).returncode == 0:
            print("wiki: %s unchanged" % WIKI_PAGE)
            return
        subprocess.run(["git", "-C", wiki, "commit", "-q", "-m", "Update release heatmap"], check=True)
        subprocess.run(["git", "-C", wiki, "push", "-q"], check=True)
        print("wiki: https://github.com/%s/wiki/%s" % (REPO, WIKI_PAGE))


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("-o", "--output")
    ap.add_argument("--publish", action="store_true")
    ap.add_argument("--maintainer", action="append", default=[])
    a = ap.parse_args(argv)

    now = datetime.datetime.now(datetime.timezone.utc)
    today = now.strftime("%Y-%m-%d")
    milestones = fetch_milestones()
    upcoming = sorted(m["due"][:10] for m in milestones if m["due"] and m["due"][:10] >= today)
    next_due = upcoming[0] if upcoming else None
    tickets = [classify(i, set(a.maintainer), today, next_due) for i in fetch_issues()]
    page = render(tickets, milestones, now.strftime("%Y-%m-%d %H:%M UTC"))

    if a.output:
        with open(a.output, "w") as fh:
            fh.write(page)
    if a.publish:
        publish(page)
    if not a.output and not a.publish:
        sys.stdout.write(page)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))

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
page, the heatmap: components (component:* labels; repo-wide work by its
scope:infrastructure, scope:overview or documentation label) against the open
milestones. Each cell lists its tickets, most urgent first, as badges coloured
by change class, each followed by a badge for every PR that closes it. Below it,
the tickets resolved since the last release, with the PRs that took them into
develop.

Usage:
    scripts/release_heatmap.py                 # print the page
    scripts/release_heatmap.py -o page.md      # write it to a file
    scripts/release_heatmap.py --publish       # push it to the wiki page
    [--maintainer LOGIN ...]                   # raised by anyone else scores 2

Needs `gh`, logged in with read access to the repo and the project; --publish
also needs push access to the wiki, through the same login or WIKI_TOKEN, and
refuses a private project. The release-heatmap workflow runs it on ticket
changes and every 15 minutes.
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
import urllib.parse

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
NO_MILESTONE = "No milestone"
UNCLASSIFIED = "(no change class)"
# Change class -> badge letter and colour; the order is the legend's.
BADGE = {"Major": ("M", "d73a4a"), "CR-Major": ("CR", "8b0000"), "New Interface": ("NI", "8250df"),
         "Minor": ("m", "0969da"), "BugFix": ("B", "1a7f37"), "Documentation": ("D", "6e7781"),
         "Infrastructure": ("I", "bf8700"), "Query": ("Q", "bf3989"), UNCLASSIFIED: ("?", "d0d7de")}
REPO_WIDE = [("scope:infrastructure", "(infrastructure)"), ("scope:overview", "(overview)"),
             ("documentation", "(documentation)")]


def gh_json(args):
    return json.loads(subprocess.check_output(["gh"] + args))


def graphql(query, **variables):
    args = ["api", "graphql", "-f", "query=" + query]
    for k, v in variables.items():
        if v is not None:
            args += ["-f", "%s=%s" % (k, v)]
    return gh_json(args)["data"]


ISSUE_FIELDS = """
        number title url closedAt stateReason
        closedByPullRequestsReferences(first:5,includeClosedPrs:true){ nodes{
          number url state isDraft reviewDecision baseRefName
        } }
        author{ login }
        milestone{ title dueOn }
        labels(first:50){ nodes{ name } }
        participants{ totalCount }
        timelineItems(itemTypes:[CROSS_REFERENCED_EVENT]){ totalCount }
        issueDependenciesSummary{ blocking }
        projectItems(first:10){ nodes{
          project{ number owner{ ... on Organization{ login } ... on User{ login } } }
          fieldValues(first:30){ nodes{
            ... on ProjectV2ItemFieldSingleSelectValue{ name field{ ... on ProjectV2SingleSelectField{ name } } }
          } }
        } }
"""

ISSUES = """
query($owner:String!,$name:String!,$cursor:String){
  repository(owner:$owner,name:$name){
    issues(first:50,after:$cursor,states:[OPEN]){
      pageInfo{ hasNextPage endCursor }
      nodes{ %s }
    }
  }
}
""" % ISSUE_FIELDS

# Closed issues touched since a date; the caller keeps those closed after it.
CLOSED = """
query($owner:String!,$name:String!,$cursor:String,$since:DateTime){
  repository(owner:$owner,name:$name){
    issues(first:50,after:$cursor,states:[CLOSED],filterBy:{since:$since}){
      pageInfo{ hasNextPage endCursor }
      nodes{ %s }
    }
  }
}
""" % ISSUE_FIELDS


def fetch_issues(query=ISSUES, **extra):
    out, cursor = [], None
    while True:
        page = graphql(query, owner=OWNER, name=NAME, cursor=cursor, **extra)["repository"]["issues"]
        out += page["nodes"]
        if not page["pageInfo"]["hasNextPage"]:
            return out
        cursor = page["pageInfo"]["endCursor"]


def fetch_last_release():
    """The latest published release, or None before the first one."""
    r = subprocess.run(["gh", "api", "repos/%s/releases/latest" % REPO], capture_output=True, text=True)
    if r.returncode:
        return None
    rel = json.loads(r.stdout)
    return {"tag": rel["tag_name"], "url": rel["html_url"], "at": rel["published_at"]}


def fetch_resolved(since):
    """Issues closed as completed after `since`."""
    return [i for i in fetch_issues(CLOSED, since=since)
            if i["closedAt"] > since and i["stateReason"] == "COMPLETED"]


def version_key(title):
    nums = re.findall(r"\d+", title.split(" ")[0])
    return [int(n) for n in nums] or [10 ** 6]


def fetch_project():
    """The project's title and whether it is public."""
    q = "query($o:String!,$n:Int!){ organization(login:$o){ projectV2(number:$n){ title public } } }"
    data = gh_json(["api", "graphql", "-f", "query=" + q, "-f", "o=" + OWNER, "-F", "n=%d" % PROJECT_NUMBER])
    return ((data["data"].get("organization") or {}).get("projectV2")) or {"title": None, "public": False}


def fetch_milestones():
    """Open milestones, in version order, with their due dates."""
    pages = gh_json(["api", "--paginate", "--slurp", "repos/%s/milestones?state=open&per_page=100" % REPO])
    ms = [m for page in pages for m in page]
    return sorted(({"title": m["title"], "due": m["due_on"]} for m in ms), key=lambda m: version_key(m["title"]))


def project_fields(issue):
    for item in issue["projectItems"]["nodes"]:
        project = item["project"]
        # Project numbers are per owner: another owner's project 41 is not ours.
        if project["number"] == PROJECT_NUMBER and (project.get("owner") or {}).get("login") == OWNER:
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
        # Repo-wide work has no component: its row comes from the scope or class label.
        comps = next(([row] for lbl, row in REPO_WIDE if lbl in labels), ["(no component)"])

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
        "priority": priority, "score": score, "why": why, "prs": pr_states(issue),
    }


# PR state -> badge text and colour; the order is the legend's.
PR_STATE = {"draft": ("draft", "6e7781"), "open": ("open", "bf8700"), "changes": ("changes", "bc4c00"),
            "approved": ("approved", "1a7f37"), "merged": ("merged", "8250df"), "closed": ("closed", "cf222e")}


def pr_states(issue):
    """The PRs that close the ticket (Closes #n, or linked under Development), newest first.

    A PR that only mentions the ticket is not one of them. A closed, unmerged PR
    shows only when it is the ticket's only PR.
    """
    out = []
    for p in (issue.get("closedByPullRequestsReferences") or {}).get("nodes") or []:
        if p["state"] == "MERGED":
            k = "merged"
        elif p["state"] == "CLOSED":
            k = "closed"
        elif p.get("isDraft"):
            k = "draft"
        else:
            k = {"APPROVED": "approved", "CHANGES_REQUESTED": "changes"}.get(p.get("reviewDecision"), "open")
        out.append({"number": p["number"], "url": p["url"], "state": k, "base": p.get("baseRefName")})
    out.sort(key=lambda p: -p["number"])
    live = [p for p in out if p["state"] != "closed"]
    return live or out[:1]


def shield(label, message, colour):
    # shields.io static badge: "-" and "_" are doubled, everything else URL-encoded.
    q = lambda s: urllib.parse.quote(s.replace("-", "--").replace("_", "__"), safe="")
    return "https://img.shields.io/badge/%s-%s-%s" % (q(label), q(message), colour)


def badge(t):
    """The ticket as a badge: its number and change-class letter, coloured by class."""
    # A project option added after this table shows its full name, in grey.
    letter, colour = BADGE.get(t["effect"] or UNCLASSIFIED, (t["effect"], "57606a"))
    return "[![#%d %s](%s)](%s)" % (t["number"], t["effect"] or UNCLASSIFIED,
                                   shield("#%d" % t["number"], letter, colour), t["url"])


def pr_badge(p):
    text, colour = PR_STATE[p["state"]]
    # The arrow is inside the badge, so it cannot wrap away from it; short, to fit a narrow column.
    return "[![PR %d %s](%s)](%s)" % (p["number"], text, shield("↳%d" % p["number"], text, colour), p["url"])


def ticket(t):
    """The ticket's class badge, then each PR that closes it on the line below, marked ↳."""
    return under(badge(t), [pr_badge(p) for p in t["prs"]])


def under(ticket_badge, pr_badges):
    # On the line below, not beside: a narrow column would otherwise wrap a PR away from its ticket.
    return "<br>".join([ticket_badge] + pr_badges)


def legend():
    return " ".join("![%s](%s)" % (cls, shield(letter, cls, colour))
                    for cls, (letter, colour) in BADGE.items())


def pr_legend():
    return " ".join("![PR %s](%s)" % (text, shield("↳PR", text, colour)) for text, colour in PR_STATE.values())


def cell(tickets):
    """Every ticket in the cell as a class badge, most urgent first."""
    if not tickets:
        return "·"
    ranked = sorted(tickets, key=lambda t: (-t["score"], t["number"]))
    return flow([ticket(t) for t in ranked], [bool(t["prs"]) for t in ranked])


def flow(items, alone):
    """Badges side by side; one marked alone gets a line of its own, so its PR never wraps away from it."""
    lines, run = [], []
    for item, own in zip(items, alone):
        if own:
            lines += [" ".join(run)] if run else []
            lines.append(item)
            run = []
        else:
            run.append(item)
    return "<br>".join(lines + ([" ".join(run)] if run else []))


def render(tickets, milestones, generated, project_title="halif_aidl", resolved=(), release=None):
    used = {t["milestone"] for t in tickets}
    cols = [m["title"] for m in milestones if m["title"] in used]
    # An open ticket on a closed milestone is a fault: the work is done and the
    # ticket was not closed, or the milestone was never moved. Show it, flagged.
    closed = sorted(used - set(cols) - {NO_MILESTONE}, key=version_key)
    cols += closed + ([NO_MILESTONE] if NO_MILESTONE in used else [])
    short = {c: (c if c == NO_MILESTONE else c.split(" ")[0]) for c in cols}
    short.update({c: "⚠️ %s closed" % short[c] for c in closed})
    comps = sorted({c for t in tickets for c in t["components"]},
                   key=lambda c: (c.startswith("("), c))
    lines = [
        "# Release heatmap", "",
        "_Generated %s by [`scripts/release_heatmap.py`](https://github.com/%s/blob/develop/"
        "scripts/release_heatmap.py) from the open issues and the [%s](https://github.com/orgs/%s/"
        "projects/%d) project. It updates itself when a ticket changes and every 15 minutes; "
        "do not edit it by hand._" % (generated, REPO, project_title, OWNER, PROJECT_NUMBER), "",
        "%d open issues. A ticket on several components counts once on each. "
        "Each cell lists its tickets, most urgent "
        "first, as a badge coloured by its change class; each PR that closes a ticket is "
        "on the line below it, marked ↳:" % len(tickets), "", legend(), "", "PR: " + pr_legend() + " (open: "
        "review needed; closed: closed unmerged)", "",
        "| Component | " + " | ".join(short[c] for c in cols) + " | Total |",
        "| --- |" + " --- |" * (len(cols) + 1),
    ]
    for comp in comps:
        row = [t for t in tickets if comp in t["components"]]
        lines.append("| %s | %s | %d |" % (comp, " | ".join(
            cell([t for t in row if t["milestone"] == c]) for c in cols), len(row)))
    lines.append("| **Tickets** | %s | **%d** |" % (" | ".join(
        "**%d**" % sum(1 for t in tickets if t["milestone"] == c) for c in cols), len(tickets)))

    if release:
        lines += render_resolved(resolved, release)
    return "\n".join(lines) + "\n"


def render_resolved(tickets, release):
    """What has landed since the last release: completed tickets, and the PRs that took them into develop."""
    lines = ["", "## Resolved since %s" % release["tag"], "",
             "Tickets closed as completed since the [%s release](%s) on %s, with the PRs that "
             "took them into develop." % (release["tag"], release["url"], release["at"][:10]), ""]
    if not tickets:
        return lines + ["Nothing yet."]
    comps = sorted({c for t in tickets for c in t["components"]}, key=lambda c: (c.startswith("("), c))
    lines += ["| Component | Resolved | Total |", "| --- | --- | --- |"]
    for comp in comps:
        row = sorted((t for t in tickets if comp in t["components"]), key=lambda t: t["number"])
        merged = [[p for p in t["prs"] if p["state"] == "merged" and p["base"] == "develop"] for t in row]
        lines.append("| %s | %s | %d |" % (comp, flow(
            [under(badge(t), [pr_badge(p) for p in m]) for t, m in zip(row, merged)],
            [bool(m) for m in merged]), len(row)))
    lines.append("| **Tickets** | | **%d** |" % len(tickets))
    return lines


def wiki_git():
    """git with one credential helper: WIKI_TOKEN when set (CI), else the caller's gh login."""
    helper = ("!f(){ echo username=x-access-token; echo password=$WIKI_TOKEN; }; f"
              if os.environ.get("WIKI_TOKEN") else "!gh auth git-credential")
    return ["git", "-c", "credential.helper=", "-c", "credential.helper=" + helper]


def publish(page):
    """Commit the page to the wiki repo; a no-op when nothing changed."""
    git = wiki_git()
    with tempfile.TemporaryDirectory() as tmp:
        wiki = os.path.join(tmp, "wiki")
        subprocess.run(git + ["clone", "-q", "--depth", "1",
                        "https://github.com/%s.wiki.git" % REPO, wiki], check=True)
        with open(os.path.join(wiki, WIKI_PAGE + ".md"), "w") as fh:
            fh.write(page)
        subprocess.run(["git", "-C", wiki, "add", WIKI_PAGE + ".md"], check=True)
        if subprocess.run(["git", "-C", wiki, "diff", "--cached", "--quiet"]).returncode == 0:
            print("wiki: %s unchanged" % WIKI_PAGE)
            return
        subprocess.run(["git", "-C", wiki, "commit", "-q", "-m", "Update release heatmap"], check=True)
        subprocess.run(git + ["-C", wiki, "push", "-q"], check=True)
        print("wiki: https://github.com/%s/wiki/%s" % (REPO, WIKI_PAGE))


def parse_args(argv):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("-o", "--output")
    ap.add_argument("--publish", action="store_true")
    ap.add_argument("--maintainer", action="extend", nargs="+", default=[], metavar="LOGIN")
    return ap.parse_args(argv)


def main(argv):
    a = parse_args(argv)

    now = datetime.datetime.now(datetime.timezone.utc)
    today = now.strftime("%Y-%m-%d")
    milestones = fetch_milestones()
    upcoming = sorted(m["due"][:10] for m in milestones if m["due"] and m["due"][:10] >= today)
    next_due = upcoming[0] if upcoming else None
    tickets = [classify(i, set(a.maintainer), today, next_due) for i in fetch_issues()]
    release = fetch_last_release()
    resolved = ([classify(i, set(a.maintainer), today, next_due) for i in fetch_resolved(release["at"])]
                if release else [])
    project = fetch_project()
    page = render(tickets, milestones, now.strftime("%Y-%m-%d %H:%M UTC"),
                  project["title"] or "project %d" % PROJECT_NUMBER, resolved, release)

    if a.output:
        with open(a.output, "w") as fh:
            fh.write(page)
    if a.publish:
        if not project["public"]:
            sys.exit("project %d is not public: its fields cannot go on the public wiki" % PROJECT_NUMBER)
        publish(page)
    if not a.output and not a.publish:
        sys.stdout.write(page)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))

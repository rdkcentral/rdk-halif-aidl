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
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
#** ******************************************************************************
"""Audit GitHub Discussions against the issues/PRs raised from them, and open
issues against their milestone.

A ticket counts as *raised from* a discussion when it was created after the
discussion and either the ticket's body references the discussion, or the
discussion's body, a comment or a reply references the ticket (#N or
.../issues|pull|discussions/N). A reference to an older ticket is context — a
parent tracker, or the issue the discussion was split out of — not a raised
ticket. A ticket's comments are not used for the link: a closing comment
pointing at a discussion may be a hand-off or only context, so those tickets
are listed in a separate column for review and do not change the group.
Announcements are not triage threads and are left out.

Part 1 classifies open discussions:
  NOT RAISED   - no tickets raised; still to be concluded or ticketed
  RESOLVE      - tickets raised and all of them closed/merged; close the discussion
  TICKETED     - tickets raised, some still open; close the discussion as resolved
                 once its conclusion is fully carried by the tickets

Part 2 lists every open issue with the discussion(s) it was raised from, its
milestone, and its Project status and priority. Issues with no milestone come
first: that is the triage queue.

Usage: discussion_audit.py [owner/repo] [--account LOGIN] [--project N]

  owner/repo  repository to audit (default rdkcentral/rdk-halif-aidl)
  --account   gh login whose token to use (default: the active gh account)
  --project   Project number for Status/Priority (default 41)

Requires the gh CLI, logged in with read access to the repository.
"""
import argparse
import json
import os
import re
import subprocess
import sys


def repo_arg(value):
    if not re.fullmatch(r"[\w.-]+/[\w.-]+", value):
        raise argparse.ArgumentTypeError(f"expected owner/repo, got {value!r}")
    return value


parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
parser.add_argument("repo", nargs="?", default="rdkcentral/rdk-halif-aidl", type=repo_arg,
                    help="repository to audit, owner/repo (default %(default)s)")
parser.add_argument("--account", help="gh login whose token to use (default: the active gh account)")
parser.add_argument("--project", type=int, default=41, help="Project number for Status/Priority (default %(default)s)")
args = parser.parse_args()

REPO, ACCOUNT, PROJECT = args.repo, args.account, args.project
OWNER, NAME = REPO.split("/")

TOKEN = subprocess.run(["gh", "auth", "token"] + (["--user", ACCOUNT] if ACCOUNT else []),
                       capture_output=True, text=True, check=True).stdout.strip()
ENV = dict(os.environ, GH_TOKEN=TOKEN)


def gql_data(query, **variables):
    args = ["gh", "api", "graphql", "-f", f"query={query}"]
    for k, v in variables.items():
        args += ["-F", f"{k}={v}"] if v is not None else []
    out = subprocess.run(args, capture_output=True, text=True,
                         env=ENV)
    if out.returncode:
        sys.exit(out.stderr)
    return json.loads(out.stdout)["data"]


def gql(query, **variables):
    return gql_data(query, **variables)["repository"]


def page_rest(node, field, fragment, nodes_fragment):
    """Fetch the rest of a nested connection that the first page did not finish.

    `node` holds the first page as node[field] = {pageInfo, nodes}; the remaining
    pages are read through node(id:) and appended, so classification sees all of it.
    """
    conn = node[field]
    while conn["pageInfo"]["hasNextPage"]:
        query = f"""query($id:ID!,$c:String){{node(id:$id){{... on {fragment}{{
          {field}(first:100,after:$c){{pageInfo{{hasNextPage endCursor}} nodes{{{nodes_fragment}}}}}}}}}}}"""
        more = gql_data(query, id=node["id"], c=conn["pageInfo"]["endCursor"])["node"][field]
        conn["nodes"] += more["nodes"]
        conn["pageInfo"] = more["pageInfo"]


def paged(field, nodes_fragment):
    query = f"""query($o:String!,$n:String!,$c:String){{repository(owner:$o,name:$n){{
      {field}(first:50,after:$c){{pageInfo{{hasNextPage endCursor}} nodes{{{nodes_fragment}}}}}}}}}"""
    cursor, items = None, []
    while True:
        page = gql(query, o=OWNER, n=NAME, c=cursor)[field]
        items += page["nodes"]
        if not page["pageInfo"]["hasNextPage"]:
            return items
        cursor = page["pageInfo"]["endCursor"]


PAGE = "pageInfo{hasNextPage endCursor}"


def is_our_project(item):
    # Project numbers are per owner: Project N means the repository owner's.
    p = item["project"]
    return p["number"] == PROJECT and (p.get("owner") or {}).get("login", "").lower() == OWNER.lower()
REPLY_NODES = "body"
COMMENT_NODES = f"id body replies(first:50){{{PAGE} nodes{{{REPLY_NODES}}}}}"
FIELD_NODES = "... on ProjectV2ItemFieldSingleSelectValue{name field{... on ProjectV2SingleSelectField{name}}}"
ITEM_NODES = f"id project{{number owner{{... on Organization{{login}} ... on User{{login}}}}}} fieldValues(first:50){{{PAGE} nodes{{{FIELD_NODES}}}}}"

discussions = paged("discussions", f"""id number title url closed stateReason createdAt updatedAt
    category{{name}} body comments(first:100){{{PAGE} nodes{{{COMMENT_NODES}}}}}""")
for d in discussions:
    page_rest(d, "comments", "Discussion", COMMENT_NODES)
    for c in d["comments"]["nodes"]:
        page_rest(c, "replies", "DiscussionComment", REPLY_NODES)

tickets = paged("issues", f"""id number title url state stateReason createdAt body comments(first:100){{{PAGE} nodes{{body}}}}
    milestone{{title}} assignees(first:5){{nodes{{login}}}}
    projectItems(first:20){{{PAGE} nodes{{{ITEM_NODES}}}}}""")
for t in tickets:
    t["kind"] = "issue"
    page_rest(t, "comments", "Issue", "body")
    page_rest(t, "projectItems", "Issue", ITEM_NODES)
    for item in t["projectItems"]["nodes"]:
        if is_our_project(item):
            page_rest(item, "fieldValues", "ProjectV2Item", FIELD_NODES)
prs = paged("pullRequests", f"""id number title url state createdAt body comments(first:100){{{PAGE} nodes{{body}}}}""")
for p in prs:
    p["kind"] = "PR"
    page_rest(p, "comments", "PullRequest", "body")
tickets += prs

by_ticket = {t["number"]: t for t in tickets}
discussions = [d for d in discussions if d["category"]["name"] != "Announcements"]
by_disc = {d["number"]: d for d in discussions}

# Issues, pull requests and discussions share one number sequence per repository,
# so #N (or an issues/pull/discussions URL) names exactly one of them; the lookup
# against by_disc or by_ticket decides which kind it is.
REF = re.compile(rf"(?:github\.com/{OWNER}/{NAME}/(?:issues|pull|discussions)/|(?<![\w/])#)(\d+)\b")


def texts_of_discussion(d):
    yield d["body"] or ""
    for c in d["comments"]["nodes"]:
        yield c["body"] or ""
        for r in c["replies"]["nodes"]:
            yield r["body"] or ""


def refs(texts):
    return {int(n) for text in texts for n in REF.findall(text)}


raised = {n: {} for n in by_disc}   # disc -> {ticket number: how}
cited = {n: set() for n in by_disc}   # disc -> tickets citing it only in comments
for t in tickets:
    for n in refs(c["body"] or "" for c in t["comments"]["nodes"]) & by_disc.keys():
        cited[n].add(t["number"])
    for n in refs([t["body"] or ""]) & by_disc.keys():
        if t["createdAt"] > by_disc[n]["createdAt"]:
            raised[n][t["number"]] = "ticket cites discussion"
for d in discussions:
    for n in refs(texts_of_discussion(d)) & by_ticket.keys():
        if by_ticket[n]["createdAt"] > d["createdAt"]:
            raised[d["number"]].setdefault(n, "discussion cites newer ticket")

raised_from = {}   # ticket -> discussions it was raised from
for d, links in raised.items():
    for n in links:
        raised_from.setdefault(n, set()).add(d)


def is_open(t):
    return t["state"] == "OPEN"


def unticked(d):
    return sum(len(re.findall(r"^\s*[-*] \[ \]", text, re.M)) for text in texts_of_discussion(d))


def link(n):
    return f"[#{n}]({by_ticket[n]['url']})"


def dlink(n):
    return f"[#{n}]({by_disc[n]['url']})"


def cell(text):
    return text.replace("|", "\\|")


def other(d):
    extra = sorted(cited[d["number"]] - raised[d["number"]].keys())
    return ", ".join(f"{link(n)} {by_ticket[n]['state'].lower()}" for n in extra)


def project_field(t, name):
    for item in t["projectItems"]["nodes"]:
        if not is_our_project(item):
            continue
        for v in item["fieldValues"]["nodes"]:
            if v and v.get("field", {}).get("name") == name:
                return v["name"]
    return ""


# ---- Part 1: discussions -------------------------------------------------------

groups = {"NOT RAISED": [], "RESOLVE": [], "TICKETED": []}
for d in sorted(discussions, key=lambda d: d["number"]):
    if d["closed"]:
        continue
    links = raised[d["number"]]
    if not links:
        groups["NOT RAISED"].append(d)
    elif any(is_open(by_ticket[n]) for n in links):
        groups["TICKETED"].append(d)
    else:
        groups["RESOLVE"].append(d)

closed_with_open = [d for d in discussions if d["closed"]
                    and any(is_open(by_ticket[n]) for n in raised[d["number"]])]

open_issues = sorted((t for t in tickets if t["kind"] == "issue" and is_open(t)),
                     key=lambda t: (t["milestone"] is not None,
                                    (t["milestone"] or {}).get("title", ""), t["number"]))
no_milestone = [t for t in open_issues if t["milestone"] is None]
from_disc = [t for t in open_issues if t["number"] in raised_from]

print(f"# Discussion and ticket audit — {REPO}\n")
print("| Check | Count | Action |\n|---|---|---|")
print(f"| Open discussions, no ticket raised | {len(groups['NOT RAISED'])} | Conclude; raise a ticket only where the interface changes |")
print(f"| Open discussions, every ticket closed | {len(groups['RESOLVE'])} | Close the discussion as resolved |")
print(f"| Open discussions, tickets still open | {len(groups['TICKETED'])} | Close as resolved once the tickets carry the whole conclusion |")
print(f"| Open issues with no milestone | {len(no_milestone)} | Triage: set a milestone, or close |")
print(f"| Open issues raised from a discussion | {len(from_disc)} of {len(open_issues)} | — |")

print("\n# Part 1 — Open discussions")
for name, ds in groups.items():
    print(f"\n## {name}\n")
    if not ds:
        print("None.")
        continue
    print("| Discussion | Category | Last update | Unticked boxes | Tickets raised | Cited in ticket comments |\n|---|---|---|---|---|---|")
    for d in ds:
        cells = ", ".join(
            f"{link(n)} {by_ticket[n]['kind']} {by_ticket[n]['state'].lower()}"
            for n in sorted(raised[d["number"]])) or "—"
        print(f"| {dlink(d['number'])} {cell(d['title'])} | {d['category']['name']} | "
              f"{d['updatedAt'][:10]} | {unticked(d) or ''} | {cells} | {other(d)} |")

if closed_with_open:
    print("\n## Closed discussions with open tickets\n\nNo action — the tickets carry the work.\n")
    for d in closed_with_open:
        opens = [link(n) for n in sorted(raised[d["number"]]) if is_open(by_ticket[n])]
        print(f"- {dlink(d['number'])} {d['title']} — open: {', '.join(opens)}")

# ---- Part 2: open issues -------------------------------------------------------

print("\n# Part 2 — Open issues\n")
print(f"Issues with no milestone first. Status and Priority are from Project {PROJECT}.\n")
print("| Issue | Raised from discussion | Milestone | Status | Priority | Assignee |\n|---|---|---|---|---|---|")
for t in open_issues:
    src = ", ".join(dlink(d) for d in sorted(raised_from.get(t["number"], ()))) or "not from a discussion"
    milestone = (t["milestone"] or {}).get("title") or "**none**"
    assignees = ", ".join(a["login"] for a in t["assignees"]["nodes"]) or "—"
    print(f"| {link(t['number'])} {cell(t['title'][:70])} | {src} | {milestone} | "
          f"{project_field(t, 'Status') or '—'} | {project_field(t, 'Priority') or '—'} | {assignees} |")

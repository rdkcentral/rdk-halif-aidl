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

"""release_heatmap.py - the open work by component and due date, from GitHub.

Run at any time. It reads the open issues, their labels and milestones, and
the Priority and Interface Effect fields of project 41, and writes one markdown
page, the heatmap: components against the due dates of their open milestones,
earliest first, in one section per
priority (#1053). A component is a directory with a metadata.yaml, which holds
its version, priority, devices (stb, tv) and, where they are not
component:<directory>, the labels that point tickets at it. Repo-wide work has
its scope:infrastructure, scope:overview or documentation row. Every component
is listed, whether or not it has tickets. Milestones that share a due date
share a column, a date already past is flagged overdue, a ticket whose
milestone has no due date is under No date, and a ticket with no milestone is
under Triage required. Each cell lists
its tickets, most urgent first, with its open PRs below it, each showing
its change class and review state. A cell is amber when
any of its PRs is breaking, green when they are all compatible. A second
page, Backlog-Review, lists the issues open longer than a year, for review by
hand (#1061).

--set-priority writes each open ticket's and PR's component priority into the
project's Priority field; see component-priority.md for the rules.

Usage:
    scripts/release_heatmap.py                 # print the page
    scripts/release_heatmap.py -o page.md      # write it to a file
    scripts/release_heatmap.py --publish       # push both pages to the wiki
    [--backlog-output page.md]                 # also write the backlog review page
    [--maintainer LOGIN ...]                   # raised by anyone else scores 2
    scripts/release_heatmap.py --set-priority [--dry-run]

Needs `gh`, logged in with read access to the repo and the project; --publish
also needs push access to the wiki, through the same login or WIKI_TOKEN, and
refuses a private project. The release-heatmap workflow runs it with the job's
own GITHUB_TOKEN, which can read the public project's items and push the wiki,
so no repository secret is needed (#986).
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
import time
import urllib.parse

REPO = os.environ.get("GITHUB_REPOSITORY", "rdkcentral/rdk-halif-aidl")
OWNER, NAME = REPO.split("/")
PROJECT_NUMBER = int(os.environ.get("PROJECT_NUMBER", "41"))
WIKI_PAGE = "Release-Heatmap"
HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
PRIORITY_DOC = os.path.join(ROOT, "docs", "governance", "component-priority.md")

# The change classes are the project sync's: one mapping from labels to the
# Interface Effect, so this page and the board never read a label differently.
_spec = importlib.util.spec_from_file_location(
    "project_interface_effect", os.path.join(HERE, "project_interface_effect.py"))
pie = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(pie)

BREAKING = {"Major", "CR-Major"}
PRIORITY_POINTS = {"P0": 5, "P1": 3, "P2": 1, "P3": 0}
NO_MILESTONE = "No milestone"
TRIAGE = "Triage required"   # the heading of the no-milestone column: untriaged work
NO_DATE = "No date"          # the heading of the column for milestones with no due date
UNCLASSIFIED = "(no change class)"
# Change class -> badge letter and colour; the order is the legend's.
BADGE = {"Major": ("M", "d73a4a"), "CR-Major": ("CR", "8b0000"), "New Interface": ("NI", "8250df"),
         "Minor": ("m", "0969da"), "BugFix": ("B", "1a7f37"), "Documentation": ("D", "6e7781"),
         "Infrastructure": ("I", "bf8700"), "Query": ("Q", "bf3989"), UNCLASSIFIED: ("?", "d0d7de")}
REPO_WIDE = [("scope:infrastructure", "(infrastructure)"), ("scope:overview", "(overview)"),
             ("documentation", "(documentation)")]
UNPRIORITISED = {"priority": None, "title": "Not yet prioritised", "rows": [],
                 "about": "Components with no row in the [component priority list](https://github.com/%s/"
                          "blob/develop/docs/governance/component-priority.md)." % REPO}
# A component directory renamed since a release, by its old name: flash shipped as
# firmwareupdate, boot as bootreason.
RENAMED = {"flash": "firmwareupdate", "boot": "bootreason"}
# component:* labels of components that no longer exist: flash is firmwareupdate, cdm became drm,
# and factory was dropped. Not rows even while an old ticket still carries the label.
RETIRED = {"flash", "cdm", "factory"}
# The device classes in metadata.yaml's devices field, as the heatmap groups them.
DEVICE_GROUPS = [("stb", "tv"), ("stb",), ("tv",)]


TRANSIENT = re.compile(r"HTTP 50[234]")


def gh_json(args, retries=4, sleep=None):
    """Run gh and parse its JSON, retrying a transient 502, 503 or 504 (#1037)."""
    sleep = sleep or time.sleep
    for attempt in range(retries):
        r = subprocess.run(["gh"] + args, capture_output=True, text=True)
        if r.returncode == 0:
            return json.loads(r.stdout)
        if TRANSIENT.search(r.stderr) and attempt < retries - 1:
            sys.stderr.write("gh: %s; retrying\n" % r.stderr.strip())
            sleep(2 ** attempt)
            continue
        sys.stderr.write(r.stderr)
        raise subprocess.CalledProcessError(r.returncode, ["gh"] + args, r.stdout, r.stderr)


def graphql(query, **variables):
    args = ["api", "graphql", "-f", "query=" + query]
    for k, v in variables.items():
        if v is not None:
            args += ["-f", "%s=%s" % (k, v)]
    return gh_json(args)["data"]


PR_NODE = ("number url state isDraft reviewDecision baseRefName createdAt labels(first:30){ nodes{ name } } "
           "repository{ isPrivate nameWithOwner }")

PR_FIELDS = """
          pageInfo{ hasNextPage endCursor }
          nodes{ %s }
""" % PR_NODE

# The PRs that mention a ticket without closing it (Refs #n, or a bare #n).
REF_FIELDS = """
          totalCount pageInfo{ hasNextPage endCursor }
          nodes{ ... on CrossReferencedEvent{ source{ ... on PullRequest{ %s title body } } } }
""" % PR_NODE

ISSUE_FIELDS = """
        number title url closedAt stateReason createdAt updatedAt
        closedByPullRequestsReferences(first:20,includeClosedPrs:true){ %s }
        author{ login }
        milestone{ title dueOn }
        labels(first:50){ nodes{ name } }
        participants{ totalCount }
        timelineItems(itemTypes:[CROSS_REFERENCED_EVENT],first:100){ %s }
        issueDependenciesSummary{ blocking }
""" % (PR_FIELDS, REF_FIELDS)

# The project's fields, read from the project's own item list: a workflow's
# GITHUB_TOKEN can read a public project's items, but not an issue's projectItems.
PROJECT_ITEMS = """
query($owner:String!,$number:Int!,$cursor:String){
  organization(login:$owner){ projectV2(number:$number){ items(first:100,after:$cursor){
    pageInfo{ hasNextPage endCursor }
    nodes{
      content{ ... on Issue{ number repository{ nameWithOwner } } }
      fieldValues(first:30){ nodes{
        ... on ProjectV2ItemFieldSingleSelectValue{ name field{ ... on ProjectV2SingleSelectField{ name } } }
      } }
    }
  } } }
}
"""

# The rest of one issue's closing PRs, for the rare ticket with more than a page.
MORE_PRS = """
query($owner:String!,$name:String!,$number:Int!,$cursor:String){
  repository(owner:$owner,name:$name){ issue(number:$number){
    closedByPullRequestsReferences(first:50,after:$cursor,includeClosedPrs:true){ %s }
  } }
}
""" % PR_FIELDS

# The rest of one issue's cross-references, for a ticket referenced more than a page of times.
MORE_REFS = """
query($owner:String!,$name:String!,$number:Int!,$cursor:String){
  repository(owner:$owner,name:$name){ issue(number:$number){
    timelineItems(itemTypes:[CROSS_REFERENCED_EVENT],first:100,after:$cursor){ %s }
  } }
}
""" % REF_FIELDS

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



def fetch_issues(query=ISSUES, repo=REPO, **extra):
    owner, name = repo.split("/")
    out, cursor = [], None
    while True:
        page = graphql(query, owner=owner, name=name, cursor=cursor, **extra)["repository"]["issues"]
        for issue in page["nodes"]:
            complete_prs(issue, repo)
        out += page["nodes"]
        if not page["pageInfo"]["hasNextPage"]:
            return out
        cursor = page["pageInfo"]["endCursor"]


def complete_prs(issue, repo=REPO):
    owner, name = repo.split("/")
    for key, query in (("closedByPullRequestsReferences", MORE_PRS), ("timelineItems", MORE_REFS)):
        conn = issue[key]
        while conn["pageInfo"]["hasNextPage"]:
            more = gh_json(["api", "graphql", "-f", "query=" + query, "-f", "owner=" + owner, "-f", "name=" + name,
                            "-F", "number=%d" % issue["number"], "-f", "cursor=" + conn["pageInfo"]["endCursor"]])
            page = more["data"]["repository"]["issue"][key]
            conn["nodes"] += page["nodes"]
            conn["pageInfo"] = page["pageInfo"]


def version_key(title):
    nums = re.findall(r"\d+", title.split(" ")[0])
    return [int(n) for n in nums] or [10 ** 6]


def fetch_project():
    """The project's title and whether it is public."""
    q = "query($o:String!,$n:Int!){ organization(login:$o){ projectV2(number:$n){ title public } } }"
    data = gh_json(["api", "graphql", "-f", "query=" + q, "-f", "o=" + OWNER, "-F", "n=%d" % PROJECT_NUMBER])
    return ((data["data"].get("organization") or {}).get("projectV2")) or {"title": None, "public": False}


def metadata_dirs(root=ROOT):
    """Every directory, at any depth, with a metadata.yaml: the repo's components."""
    dirs = set()
    for here, subdirs, files in os.walk(root):
        subdirs[:] = [d for d in subdirs if not d.startswith(".") and d not in ("build-tools", "node_modules")]
        if "metadata.yaml" in files and here != root:
            dirs.add(os.path.relpath(here, root).replace(os.sep, "/"))
            subdirs[:] = []
    return dirs


def _labels_field(path):
    with open(path) as fh:
        m = re.search(r"^labels:[ \t]*\[(.*)\]", fh.read(), re.M)
    return [l.strip() for l in m.group(1).split(",") if l.strip()] if m else []


def label_map(root=ROOT):
    """{component label name: component directory}. A component's labels are component:<its
    directory>, unless its metadata.yaml names others in its labels field (bootreason's is
    component:boot; sensor's are component:motion_sensor and component:thermal_sensor)."""
    out = {}
    for d in metadata_dirs(root):
        for label in _labels_field(os.path.join(root, d, "metadata.yaml")) or ["component:" + d]:
            out[label[len("component:"):] if label.startswith("component:") else label] = d
    return out


_LABEL_MAPS = {}


def label_dirs(root=ROOT):
    """label_map(root), read once per root."""
    if root not in _LABEL_MAPS:
        _LABEL_MAPS[root] = label_map(root)
    return _LABEL_MAPS[root]


def row_name(label, dirs=None):
    """The heatmap row of a label: the component directory it names, or the bracketed
    repo-wide row. A label no metadata.yaml claims is its own row. `dirs` is the label map
    to use; by default, this checkout's."""
    if label.startswith("component:"):
        name = label[len("component:"):]
        return (label_dirs() if dirs is None else dirs).get(name, name)
    return dict(REPO_WIDE).get(label, label)


def read_priorities(path=PRIORITY_DOC):
    """The priority sections of component-priority.md, in order: each with its
    priority, heading, first paragraph and its labelled rows."""
    sections, cur = [], None
    with open(path) as fh:
        for line in fh.read().splitlines():
            m = re.match(r"## (P\d) [–-] ", line)
            if m:
                cur = {"priority": m.group(1), "title": line[3:], "about": None, "rows": []}
                sections.append(cur)
            elif line.startswith("## "):
                cur = None
            elif cur and cur["about"] is None and line and not line.startswith("|"):
                cur["about"] = line
            elif cur:
                # | Name | `label` | ...: a row without a label is not a heatmap row.
                m = re.match(r"\|\s*([^|]+?)\s*\|\s*`([^`]+)`", line)
                if m and row_name(m.group(2)) not in [r["row"] for r in cur["rows"]]:
                    cur["rows"].append({"name": m.group(1), "row": row_name(m.group(2))})
    return sections


def rank_of(sections):
    """{row: priority number}; a row in no section ranks below them all."""
    return {r["row"]: int(s["priority"][1:]) for s in sections for r in s["rows"]}


def metadata(row, root=ROOT):
    """The component's version, priority and devices from its metadata.yaml; {} without one.
    A priority of ~ is none; devices is a tuple in DEVICE_GROUPS order."""
    path = os.path.join(root, row, "metadata.yaml")
    if row.startswith("(") or not os.path.exists(path):
        return {}
    with open(path) as fh:
        text = fh.read()
    field = lambda key: (re.search(r"^%s:[ \t]*(.*?)\s*$" % key, text, re.M) or [None, None])[1]
    priority = field("priority")
    devices = {d.strip().lower() for d in (field("devices") or "").strip("[]").split(",") if d.strip()}
    return {"version": (field("version") or "").split(" ")[0] or None,
            "priority": priority if priority and re.match(r"P\d$", priority) else None,
            "devices": tuple(d for d in DEVICE_GROUPS[0] if d in devices)}


def version_of(row, root=ROOT):
    """The component's version from its metadata.yaml, or None."""
    return metadata(row, root).get("version")


def devices_of(row, root=ROOT):
    """The devices that use the component, as the heatmap shows them: STB, TV."""
    return ", ".join(d.upper() for d in metadata(row, root).get("devices", ()))


def all_components(root=ROOT, labels=()):
    """Every component: each directory with a metadata.yaml. Labels only point tickets at them;
    a repo with no metadata.yaml at all (linux_binder_idl) has its component:* labels, but the
    RETIRED ones, as its components instead. A label-only name with an open ticket still gets
    a row, from the ticket."""
    dirs = metadata_dirs(root)
    if dirs:
        return sorted(dirs)
    return sorted({l[len("component:"):] for l in labels if l.startswith("component:")} - RETIRED)


def fetch_labels():
    pages = gh_json(["api", "--paginate", "--slurp", "repos/%s/labels?per_page=100" % REPO])
    return [l["name"] for page in pages for l in page]


def device_order(row, root=ROOT):
    """Where a row sorts by its devices: STB and TV, then STB only, then TV only, then unknown."""
    devices = metadata(row, root).get("devices")
    return DEVICE_GROUPS.index(devices) if devices in DEVICE_GROUPS else len(DEVICE_GROUPS)


def with_metadata(sections, components, root=ROOT):
    """The priority sections with each component in the one its metadata.yaml's priority names,
    and each section's rows grouped by device. The priority list's rows without a metadata.yaml
    (labels such as crypto, and the repo-wide rows) stay where the list puts them."""
    sections = [dict(s, rows=list(s["rows"])) for s in sections]
    names = {r["row"]: r["name"] for s in sections for r in s["rows"]}
    for row in components:
        want = metadata(row, root).get("priority")
        if not want:
            continue
        for s in sections:
            s["rows"] = [r for r in s["rows"] if r["row"] != row]
        sec = next((s for s in sections if s["priority"] == want), None)
        if sec is None:
            sec = {"priority": want, "title": want, "about": None, "rows": []}
            sections.append(sec)
            sections.sort(key=lambda s: s["priority"])
        sec["rows"].append({"name": names.get(row), "row": row})
    for s in sections:
        s["rows"].sort(key=lambda r: (r["row"].startswith("("), device_order(r["row"], root),
                                      (r["name"] or r["row"]).lower()))
    return sections


def fetch_milestones(repo=REPO):
    """Open milestones, in version order, with their due dates."""
    pages = gh_json(["api", "--paginate", "--slurp", "repos/%s/milestones?state=open&per_page=100" % repo])
    ms = [m for page in pages for m in page]
    return sorted(({"title": m["title"], "due": m["due_on"]} for m in ms), key=lambda m: version_key(m["title"]))


def fetch_project_fields(repo=REPO):
    """{issue number: {field: value}} for one repo's issues on the project."""
    nodes, cursor = [], None
    while True:
        args = ["api", "graphql", "-f", "query=" + PROJECT_ITEMS, "-f", "owner=" + OWNER,
                "-F", "number=%d" % PROJECT_NUMBER] + (["-f", "cursor=" + cursor] if cursor else [])
        page = gh_json(args)["data"]["organization"]["projectV2"]["items"]
        nodes += page["nodes"]
        if not page["pageInfo"]["hasNextPage"]:
            return item_fields(nodes, repo)
        cursor = page["pageInfo"]["endCursor"]


def item_fields(nodes, repo=REPO):
    out = {}
    for item in nodes:
        content = item.get("content") or {}
        # The project spans repositories: only the asked-for repo's issues count.
        if content.get("number") and (content.get("repository") or {}).get("nameWithOwner") == repo:
            out[content["number"]] = {v["field"]["name"]: v["name"]
                                      for v in item["fieldValues"]["nodes"] if v and v.get("field")}
    return out


def project_fields(issue):
    return issue.get("projectFields") or {}


def age_days(created, today):
    """Whole days from an ISO timestamp to today (YYYY-MM-DD), or None without both."""
    if not created or not today:
        return None
    try:
        return (datetime.date.fromisoformat(today[:10]) - datetime.date.fromisoformat(created[:10])).days
    except ValueError:
        return None


def age_text(days):
    if days is None:
        return "?"
    return "%dd" % days if days < 14 else "%dw" % (days // 7) if days < 365 else "%dy%s" % (
        days // 365, "+" if days % 365 >= 30 else "")


def classify(issue, maintainers, today, next_due, repo=REPO, dirs=None):
    labels = [l["name"] for l in issue["labels"]["nodes"]]
    fields = project_fields(issue)
    label_class = pie.class_of(labels)
    # Labels win, as in the project sync; the field fills in where none is set.
    effect = label_class or fields.get("Interface Effect")
    priority = (fields.get("Priority") or "").split(" ")[0] or None
    ms = issue["milestone"]
    due = ms["dueOn"][:10] if ms and ms["dueOn"] else None
    # This checkout's metadata.yaml maps this repo's labels; another repo's labels are their own rows.
    if dirs is None:
        dirs = label_dirs() if repo == REPO else {}
    comps = sorted({row_name(l, dirs) for l in labels if l.startswith("component:")})
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
        "milestone": ms["title"] if ms else NO_MILESTONE, "due": due, "components": comps,
        "effect": effect, "label_class": label_class, "field": fields.get("Interface Effect"),
        "priority": priority, "score": score, "why": why, "prs": pr_states(issue),
        "open_prs": open_prs(issue, repo),
        "age": age_days(issue.get("createdAt"), today), "updated": (issue.get("updatedAt") or "")[:10],
    }


# PR state -> badge text and colour; the order is the legend's.
PR_STATE = {"draft": ("draft", "6e7781"), "open": ("open", "bf8700"), "changes": ("changes", "bc4c00"),
            "approved": ("approved", "1a7f37"), "merged": ("merged", "8250df")}
OPEN = ("draft", "open", "changes", "approved")


def pr_state(p):
    """The badge state of one PR node: merged, closed, draft, approved, changes or open."""
    if p["state"] == "MERGED":
        return "merged"
    if p["state"] == "CLOSED":
        return "closed"
    if p.get("isDraft"):
        return "draft"
    return {"APPROVED": "approved", "CHANGES_REQUESTED": "changes"}.get(p.get("reviewDecision"), "open")


def pr_entries(nodes):
    """Public PRs as badge entries, one per PR (by URL, so same-numbered PRs in other repos stay apart),
    newest first; closed unmerged PRs are left out."""
    out = {}
    for p in nodes:
        if not p or "number" not in p or (p.get("repository") or {}).get("isPrivate"):
            continue   # not a PR, or a private repository's PR, which never goes on the public wiki
        k = pr_state(p)
        # The same PR can arrive in several snapshots taken moments apart. Closed
        # and merged are final, so they win over an earlier or later open one.
        if (out.get(p["url"]) or {}).get("state") in ("closed", "merged"):
            continue
        labels = [l["name"] for l in ((p.get("labels") or {}).get("nodes") or [])]
        out[p["url"]] = {"number": p["number"], "url": p["url"], "state": k, "base": p.get("baseRefName"),
                         "effect": pie.class_of(labels), "created": p.get("createdAt")}
    return sorted((e for e in out.values() if e["state"] != "closed"), key=lambda p: (-p["number"], p["url"]))


def pr_states(issue):
    """The PRs that close the ticket (Closes #n, or linked under Development): the ones that resolve it."""
    return pr_entries((issue.get("closedByPullRequestsReferences") or {}).get("nodes") or [])


def open_prs(issue, repo=REPO):
    """The ticket's open PRs: those that close it, and those in its repo that name it with `Refs #n`.

    Any other mention (a quoted title, a "see #n") is not work on the ticket.
    """
    refs = [(e.get("source") or {}) for e in (issue.get("timelineItems") or {}).get("nodes") or []]
    names_it = re.compile(r"\bRefs\b:?\s+#%d\b" % issue["number"], re.I)
    refs = [p for p in refs if (p.get("repository") or {}).get("nameWithOwner") == repo
            and names_it.search("%s\n%s" % (p.get("title") or "", p.get("body") or ""))]
    closing = (issue.get("closedByPullRequestsReferences") or {}).get("nodes") or []
    return [p for p in pr_entries(closing + refs) if p["state"] in OPEN]


def row_of(t, rank=None):
    """The one row a ticket is shown in: its highest-priority component, then the first alphabetically."""
    rank = rank or {}
    return min(t["components"], key=lambda c: (rank.get(c, 9), c))


def rows(tickets, rank=None):
    """Row names in display order: components first, then the bracketed catch-all rows."""
    return sorted({row_of(t, rank) for t in tickets}, key=lambda c: (c.startswith("("), c))


VERSION_COLOUR = "0969da"   # the version badge in a row heading, apart from the ticket badges' grey


def version_badge(v):
    """The component version as a badge: the wiki strips text colour, so colour comes from an image."""
    return "![%s](https://img.shields.io/badge/%s-%s)" % (
        v, urllib.parse.quote(v.replace("-", "--").replace("_", "__"), safe=""), VERSION_COLOUR)


def row_heading(row, name=None, root=ROOT):
    """The row's name, then its component version, as a badge, where it has one."""
    v = version_of(row, root)
    return "%s %s" % (name or row, version_badge(v)) if v else (name or row)


def column_heading(col, today=None):
    """A due date, flagged when it has already passed; the two catch-all columns as they are."""
    if col in (NO_DATE, TRIAGE) or not today or col >= today:
        return col
    return "⚠️ %s<br>overdue" % col


RELEASE_TAG = re.compile(r"^\d+\.\d+\.\d+$")


def _git(root, *args):
    r = subprocess.run(["git", "-C", root] + list(args), capture_output=True, text=True)
    return r.stdout if r.returncode == 0 else ""


def release_history(root=ROOT, count=4):
    """The last `count` releases and the one before them, oldest first, with each component's
    version at each: {"tags": [...], "versions": {row: {tag: version}}}. None when the checkout
    has fewer than two release tags (a shallow clone has none)."""
    tags = sorted((t for t in _git(root, "tag").split() if RELEASE_TAG.match(t)), key=version_key)
    tags = tags[-(count + 1):]
    if len(tags) < 2:
        return None
    versions = {}
    for tag in tags:
        for path in _git(root, "ls-tree", "-r", "--name-only", tag).split():
            if not path.endswith("/metadata.yaml"):
                continue
            m = re.search(r"^version:\s*(\S+)", _git(root, "show", "%s:%s" % (tag, path)), re.M)
            d = path[:-len("/metadata.yaml")]
            d = RENAMED.get(d, d)
            if m:
                versions.setdefault(d, {})[tag] = m.group(1)
    return {"tags": tags, "versions": versions}


BACKLOG_PAGE = "Backlog-Review"
BACKLOG_DAYS = 365   # an issue open this long is listed for review (#1061)


def render_backlog(tickets, generated, days=BACKLOG_DAYS):
    """Every open issue older than `days`, oldest first, for review by hand: nothing is closed here."""
    old = sorted((t for t in tickets if (t.get("age") or 0) >= days), key=lambda t: (-t["age"], t["number"]))
    lines = ["# Backlog review", "",
             "_Generated %s by [`scripts/release_heatmap.py`](https://github.com/%s/blob/develop/"
             "scripts/release_heatmap.py). Do not edit it by hand._" % (generated, REPO), "",
             "%d open issues have been open for %d days or more. An issue open that long is probably "
             "not important: review each one, then close it or give it a milestone. Nothing here is "
             "closed automatically. The open work by component is on [Release heatmap](%s)." % (
                 len(old), days, WIKI_PAGE), ""]
    if not old:
        return "\n".join(lines + ["None."]) + "\n"
    lines += [md_row(["Issue", "Title", "Component", "Milestone", "Age", "Last activity"]), md_row(["---"] * 6)]
    for t in old:
        lines.append(md_row([badge(t), t["title"].replace("|", "\\|"), ", ".join(t["components"]),
                             TRIAGE if t["milestone"] == NO_MILESTONE else t["milestone"],
                             age_text(t["age"]), t.get("updated") or "?"]))
    return "\n".join(lines) + "\n"



def md_row(cells):
    """One markdown table row: as many cells as the header, whatever their content."""
    return "| " + " | ".join(cells) + " |"


def shield(label, message, colour):
    # shields.io static badge: "-" and "_" are doubled, everything else URL-encoded.
    q = lambda s: urllib.parse.quote(s.replace("-", "--").replace("_", "__"), safe="")
    return "https://img.shields.io/badge/%s-%s-%s" % (q(label), q(message), colour)


def badge(t):
    """The ticket as a badge: its number. The change class is on its PRs."""
    return "[![#%d](https://img.shields.io/badge/%s-6e7781)](%s)" % (
        t["number"], urllib.parse.quote("#%d" % t["number"], safe=""), t["url"])


def class_letter(effect):
    """A change class's letter; a class added to the project after BADGE shows its full name."""
    return BADGE.get(effect or UNCLASSIFIED, (effect, None))[0]


def pr_badge(p):
    """The PR as a badge: its number, change-class letter and review state, coloured by review state."""
    word, colour = PR_STATE[p["state"]]
    text = "%s %s" % (class_letter(p.get("effect")), word)
    # The arrow is inside the badge, so it cannot wrap away from it; short, to fit a narrow column.
    return "[![PR %d %s](%s)](%s)" % (p["number"], text, shield("↳%d" % p["number"], text, colour), p["url"])


def ticket(t):
    """The ticket's class badge, then each of its open PRs on the line below, marked ↳."""
    return under(badge(t), [pr_badge(p) for p in t["open_prs"]])


def under(ticket_badge, pr_badges):
    # On the line below, not beside: a narrow column would otherwise wrap a PR away from its ticket.
    return "<br>".join([ticket_badge] + pr_badges)


def legend():
    """The page's key: cell colours, review-state colours and the change-class letters on PRs."""
    states = " ".join("![%s](%s)" % (PR_STATE[k][0], shield("↳PR", PR_STATE[k][0], PR_STATE[k][1])) for k in OPEN)
    letters = ", ".join("**%s** %s" % (letter, cls) for cls, (letter, _) in BADGE.items())
    return ("🟧 a Major or CR-Major PR in the cell · 🟩 only compatible PRs (Minor, BugFix, New Interface, "
            "Documentation and the like) · no colour: no PR yet.\n\nPR review state: " + states +
            "\n\nEach PR shows its change class and review state (%s): %s." % (
                ", ".join(PR_STATE[k][0] for k in OPEN), letters))


def cell_colour(tickets):
    """🟧 when any open PR in the cell is breaking, 🟩 when its PRs are all compatible, "" with none."""
    effects = [p.get("effect") for t in tickets for p in t["open_prs"]]
    if not effects:
        return ""
    return "🟧" if any(e in BREAKING for e in effects) else "🟩"


def cell(tickets):
    """Every ticket in the cell as a class badge, most urgent first."""
    if not tickets:
        return "·"
    ranked = sorted(tickets, key=lambda t: (-t["score"], t["number"]))
    body = flow([ticket(t) for t in ranked], [bool(t["open_prs"]) for t in ranked])
    colour = cell_colour(tickets)
    return "%s<br>%s" % (colour, body) if colour else body


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


def sectioned(tickets, sections, components, root=ROOT):
    """The page's sections: each priority's rows, then every other row under Not yet prioritised.
    A priority row is shown when it is a component, has an open ticket, or is a repo-wide row: a
    listed label with neither, such as Crypto with no open ticket, still ranks but is not shown."""
    rank = rank_of(sections)
    shown = set(components) | {row_of(t, rank) for t in tickets}
    rest = sorted(shown - set(rank), key=lambda c: (c.startswith("("), device_order(c, root), c))
    kept = [dict(s, rows=[r for r in s["rows"] if r["row"] in shown or r["row"].startswith("(")])
            for s in sections]
    other = dict(UNPRIORITISED, rows=[{"name": None, "row": r} for r in rest])
    return [s for s in kept if s["rows"]] + ([other] if rest else []), rank



def due_dates(tickets, milestones):
    """Each milestone's due date, YYYY-MM-DD: the open milestones' own, else the date a ticket carries."""
    due = {t["milestone"]: t["due"][:10] for t in tickets if t.get("due")}
    due.update({m["title"]: m["due"][:10] for m in milestones if m["due"]})
    return due


def column_of(t, due):
    """The ticket's column: its milestone's due date, No date, or Triage required with no milestone."""
    if t["milestone"] == NO_MILESTONE:
        return TRIAGE
    return due.get(t["milestone"]) or NO_DATE


def date_columns(tickets, due, today=None):
    """The due dates the tickets use, earliest first, then No date, then Triage required, and each
    one's heading. Tickets on a closed milestone are expected under Triage required (see on_open_milestones)."""
    used = {column_of(t, due) for t in tickets}
    cols = sorted(used - {NO_DATE, TRIAGE}) + [c for c in (NO_DATE, TRIAGE) if c in used]
    return cols, {c: column_heading(c, today) for c in cols}


def on_open_milestones(tickets, milestones):
    """The tickets with any closed milestone taken off, so they show under No milestone, and the
    ones that were on a closed milestone. A closed milestone has no column: an open ticket on one
    is a fault, the work done but not closed or the milestone never moved."""
    open_titles = {m["title"] for m in milestones}
    stray = [t for t in tickets if t["milestone"] not in open_titles and t["milestone"] != NO_MILESTONE]
    return [dict(t, milestone=NO_MILESTONE) if t in stray else t for t in tickets], stray


def generated_note(generated, project_title, what):
    return ("_Generated %s by [`scripts/release_heatmap.py`](https://github.com/%s/blob/develop/"
            "scripts/release_heatmap.py) from %s and the [%s](https://github.com/orgs/%s/"
            "projects/%d) project. It updates itself when a ticket changes; do not edit it by "
            "hand._" % (generated, REPO, what, project_title, OWNER, PROJECT_NUMBER))


def render(tickets, milestones, generated, project_title="halif_aidl", sections=(), components=(), root=ROOT,
           history=None, backlog_page=None):
    tickets, stray = on_open_milestones(tickets, milestones)
    today = generated[:10] if re.match(r"\d{4}-\d\d-\d\d", generated) else None
    due = due_dates(tickets, milestones)
    cols, short = date_columns(tickets, due, today)
    if history:
        # A component in the last release stays on the page until a release without it.
        last = history["tags"][-1]
        components = set(components) | {r for r, v in history["versions"].items() if last in v}
    groups, rank = sectioned(tickets, list(sections), components, root)
    lines = ["# Release heatmap", "", generated_note(generated, project_title, "the open issues"), ""]
    if backlog_page:
        lines += ["Issues open longer than a year are listed for review on [%s](%s)." % (
            backlog_page.replace("-", " "), backlog_page), ""]
    lines += [
        "%d open issues, each shown once: a ticket on several components is in the "
        "row of its highest-priority component, so the row totals add up to the open issues. "
        "Every component is listed, with its version, whether or not it has tickets. "
        "Priority and devices come from each component's metadata.yaml; within a priority, "
        "components used on both STB and TV come first, then STB only, then TV only. "
        "Each cell lists its tickets, most urgent first, each with its open PRs on the line "
        "below it, marked ↳. Each column is a due date, earliest first, taken from the ticket's "
        "milestone; a date already past is marked overdue. A ticket whose milestone has no due date "
        "is under No date, and one with no milestone is under Triage required." % len(tickets), "",
        legend(),
    ]
    if stray:
        lines += ["", "⚠️ Open on a closed milestone, so shown under Triage required: " + ", ".join(
            "[#%d](%s) (%s)" % (t["number"], t["url"], t["milestone"]) for t in sorted(stray, key=lambda t: t["number"]))
            + ". Move each to an open milestone, or close it."]
    for sec in groups:
        lines += ["", "## " + sec["title"], ""] + ([sec["about"], ""] if sec["about"] else []) + [
            md_row(["Component", "Devices"] + [short[c] for c in cols] + ["Total"]),
            md_row(["---"] * (len(cols) + 3))]
        in_sec = []
        for r in sec["rows"]:
            row = [t for t in tickets if row_of(t, rank) == r["row"]]
            in_sec += row
            lines.append(md_row([row_heading(r["row"], r["name"], root), devices_of(r["row"], root)] + [
                cell([t for t in row if column_of(t, due) == c]) for c in cols] + [str(len(row))]))
        lines.append(md_row(["**Tickets**", ""] + ["**%d**" % sum(1 for t in in_sec if column_of(t, due) == c)
                                                  for c in cols] + ["**%d**" % len(in_sec)]))

    return "\n".join(lines) + "\n"


# Every open item on the project, issues and PRs alike, with its Priority.
PRIORITY_ITEMS = """
query($owner:String!,$number:Int!,$cursor:String){
  organization(login:$owner){ projectV2(number:$number){
    id
    field(name:"Priority"){ ... on ProjectV2SingleSelectField{ id options{ id name } } }
    items(first:100,after:$cursor){
      pageInfo{ hasNextPage endCursor }
      nodes{
        id
        fieldValueByName(name:"Priority"){ ... on ProjectV2ItemFieldSingleSelectValue{ name } }
        content{
          ... on Issue{ number issueState: state repository{ nameWithOwner } labels(first:50){ nodes{ name } } }
          ... on PullRequest{ number prState: state repository{ nameWithOwner } labels(first:50){ nodes{ name } } }
        }
      }
    }
  } }
}
"""

SET_PRIORITY = """
mutation($p:ID!,$i:ID!,$f:ID!,$o:String!){
  updateProjectV2ItemFieldValue(input:{projectId:$p,itemId:$i,fieldId:$f,value:{singleSelectOptionId:$o}}){
    projectV2Item{ id }
  }
}
"""


def wanted_priority(labels, current, sections):
    """The Priority an open ticket or PR should carry, or None to leave it as it is.

    Its highest-priority component's; with no component label, its repo-wide
    row's, but only where Priority is empty. P0 is a hand-set override.
    """
    if current == "P0":
        return None
    rank = rank_of(sections)
    comps = [row_name(l) for l in labels if l.startswith("component:")]
    if comps:
        ranks = [rank[c] for c in comps if c in rank]
    else:
        row = next((r for lbl, r in REPO_WIDE if lbl in labels), None)
        ranks = [rank[row]] if row in rank and not current else []
    want = "P%d" % min(ranks) if ranks else None
    return want if want != current else None


def set_priorities(dry_run, sections, out=sys.stdout):
    """Align every open ticket's and PR's Priority with its component's (#1053)."""
    items, cursor, project = [], None, None
    while True:
        args = ["api", "graphql", "-f", "query=" + PRIORITY_ITEMS, "-f", "owner=" + OWNER,
                "-F", "number=%d" % PROJECT_NUMBER] + (["-f", "cursor=" + cursor] if cursor else [])
        project = gh_json(args)["data"]["organization"]["projectV2"]
        items += project["items"]["nodes"]
        if not project["items"]["pageInfo"]["hasNextPage"]:
            break
        cursor = project["items"]["pageInfo"]["endCursor"]
    options = {o["name"].split(" ")[0]: o["id"] for o in project["field"]["options"]}
    changed = 0
    for item in items:
        c = item.get("content") or {}
        if (c.get("issueState") or c.get("prState")) != "OPEN" or (c.get("repository") or {}).get("nameWithOwner") != REPO:
            continue
        current = ((item.get("fieldValueByName") or {}).get("name") or "").split(" ")[0] or None
        want = wanted_priority([l["name"] for l in c["labels"]["nodes"]], current, sections)
        if not want:
            continue
        changed += 1
        out.write("#%d: %s -> %s\n" % (c["number"], current or "none", want))
        if not dry_run:
            gh_json(["api", "graphql", "-f", "query=" + SET_PRIORITY, "-f", "p=" + project["id"],
                     "-f", "i=" + item["id"], "-f", "f=" + project["field"]["id"], "-f", "o=" + options[want]])
    out.write("%d to change%s\n" % (changed, " (dry run)" if dry_run else ""))
    return changed


def wiki_git():
    """git with one credential helper: WIKI_TOKEN when set (CI), else the caller's gh login."""
    helper = ("!f(){ echo username=x-access-token; echo password=$WIKI_TOKEN; }; f"
              if os.environ.get("WIKI_TOKEN") else "!gh auth git-credential")
    return ["git", "-c", "credential.helper=", "-c", "credential.helper=" + helper]


def publish(pages):
    """Commit {wiki page: markdown} to the wiki repo in one commit; a no-op when nothing changed."""
    git = wiki_git()
    with tempfile.TemporaryDirectory() as tmp:
        wiki = os.path.join(tmp, "wiki")
        subprocess.run(git + ["clone", "-q", "--depth", "1",
                        "https://github.com/%s.wiki.git" % REPO, wiki], check=True)
        for name, page in pages.items():
            with open(os.path.join(wiki, name + ".md"), "w") as fh:
                fh.write(page)
            subprocess.run(["git", "-C", wiki, "add", name + ".md"], check=True)
        if subprocess.run(["git", "-C", wiki, "diff", "--cached", "--quiet"]).returncode == 0:
            print("wiki: %s unchanged" % ", ".join(pages))
            return
        subprocess.run(["git", "-C", wiki, "commit", "-q", "-m", "Update release heatmap"], check=True)
        subprocess.run(git + ["-C", wiki, "push", "-q"], check=True)
        for name in pages:
            print("wiki: https://github.com/%s/wiki/%s" % (REPO, name))


def parse_args(argv):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("-o", "--output")
    ap.add_argument("--backlog-output", metavar="PATH", help="also write the backlog review page here")
    ap.add_argument("--publish", action="store_true")
    ap.add_argument("--maintainer", action="extend", nargs="+", default=[], metavar="LOGIN")
    ap.add_argument("--set-priority", action="store_true",
                    help="set each open ticket's and PR's project Priority from its component")
    ap.add_argument("--dry-run", action="store_true", help="with --set-priority: print, change nothing")
    return ap.parse_args(argv)


def main(argv):
    a = parse_args(argv)
    if a.set_priority:
        set_priorities(a.dry_run, with_metadata(read_priorities(), all_components()))
        return 0
    components = all_components(labels=fetch_labels())
    sections = with_metadata(read_priorities(), components)

    now = datetime.datetime.now(datetime.timezone.utc)
    today = now.strftime("%Y-%m-%d")
    milestones = fetch_milestones()
    upcoming = sorted(m["due"][:10] for m in milestones if m["due"] and m["due"][:10] >= today)
    next_due = upcoming[0] if upcoming else None
    fields = fetch_project_fields()
    with_fields = lambda issues: [dict(i, projectFields=fields.get(i["number"], {})) for i in issues]
    tickets = [classify(i, set(a.maintainer), today, next_due) for i in with_fields(fetch_issues())]
    project = fetch_project()
    generated = now.strftime("%Y-%m-%d %H:%M UTC")
    title = project["title"] or "project %d" % PROJECT_NUMBER
    page = render(tickets, milestones, generated, title, sections, components,
                  history=release_history(), backlog_page=BACKLOG_PAGE)
    backlog = render_backlog(tickets, generated)

    if a.output:
        with open(a.output, "w") as fh:
            fh.write(page)
    if a.backlog_output:
        with open(a.backlog_output, "w") as fh:
            fh.write(backlog)
    if a.publish:
        if not project["public"]:
            sys.exit("project %d is not public: its fields cannot go on the public wiki" % PROJECT_NUMBER)
        publish({WIKI_PAGE: page, BACKLOG_PAGE: backlog})
    if not a.output and not a.publish:
        sys.stdout.write(page)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))

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

"""triage_action_list.py - what is waiting on whom, across PRs, tickets and discussions.

Run at any time. It reads the open pull requests, the open issues that need
triage, and the open discussions, and writes one markdown page in priority
order: pull requests first, then tickets, then discussions. Each row says what
should happen next and who it is waiting on.

A thread that asks several questions carries a question tracker: one comment by
a maintainer holding the marker below and a table, one row per question.

    <!-- triage:questions -->
    | # | Question | Status | Where |
    | --- | --- | --- | --- |
    | 1 | Is PTS in ns or us? | Answered | <link to the reply> |
    | 2 | Should flush() block? | Ticketed | #1013 |

Status is one of Open, Answered, Ticketed, Rejected or Duplicate. A Ticketed
row counts as done once every ticket it names is closed. The page counts the
rows, so a thread whose questions are all covered shows as ready to close.

Usage:
    scripts/triage_action_list.py                    # write out/triage/Triage-Action-List.md
    scripts/triage_action_list.py -o page.md         # write it elsewhere
    scripts/triage_action_list.py -o -               # print it
    scripts/triage_action_list.py --publish          # push it to the wiki page
    [--maintainer LOGIN ...] [--stale-days N]

Needs `gh`, logged in with read access to the repo (GH_TOKEN, when set, is
used instead); --publish also needs push access to the wiki, through the same
login or WIKI_TOKEN.
"""

import argparse
import datetime
import importlib.util
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)

# The GitHub helpers and the wiki push are the heatmap's: one retry policy, one
# credential path, for both pages.
_spec = importlib.util.spec_from_file_location("release_heatmap", os.path.join(HERE, "release_heatmap.py"))
rh = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(rh)

REPO, OWNER, NAME = rh.REPO, rh.OWNER, rh.NAME
WIKI_PAGE = "Triage-Action-List"
DEFAULT_OUT = os.path.join(ROOT, "out", "triage", WIKI_PAGE + ".md")
# The people whose reply counts as "us". Org membership cannot tell them apart:
# most people who raise questions here are rdkcentral members too.
MAINTAINERS = ("Ulrond",)
STALE_DAYS = 14
TRACKER = "<!-- triage:questions -->"
STATUSES = ("open", "answered", "ticketed", "rejected", "duplicate")

PAGE = "pageInfo{ hasNextPage endCursor }"
WHO = "author{ login } createdAt"

OPEN_PRS = """
query($owner:String!,$name:String!,$cursor:String){
  repository(owner:$owner,name:$name){ pullRequests(first:50,after:$cursor,states:[OPEN]){
    %s
    nodes{
      number title url isDraft createdAt updatedAt reviewDecision mergeable baseRefName
      author{ login }
      milestone{ title }
      reviewRequests(first:10){ nodes{ requestedReviewer{ ... on User{ login } ... on Team{ slug } } } }
      commits(last:1){ nodes{ commit{ statusCheckRollup{ state } } } }
      closingIssuesReferences(first:10){ nodes{ number url } }
    }
  } }
}
""" % PAGE

OPEN_ISSUES = """
query($owner:String!,$name:String!,$cursor:String){
  repository(owner:$owner,name:$name){ issues(first:50,after:$cursor,states:[OPEN]){
    %s
    nodes{
      id number title url body createdAt updatedAt
      author{ login }
      milestone{ title }
      labels(first:30){ nodes{ name } }
      comments(first:100){ %s nodes{ %s body } }
    }
  } }
}
""" % (PAGE, PAGE, WHO)

OPEN_DISCUSSIONS = """
query($owner:String!,$name:String!,$cursor:String){
  repository(owner:$owner,name:$name){ discussions(first:25,after:$cursor,states:[OPEN]){
    %s
    nodes{
      id number title url body createdAt updatedAt
      author{ login }
      category{ name }
      comments(first:100){ %s nodes{ id %s body replies(first:50){ %s nodes{ %s body } } } }
    }
  } }
}
""" % (PAGE, PAGE, WHO, PAGE, WHO)

# Every issue and PR, open or closed: a discussion's raised tickets, and the
# state of a ticket a question tracker names.
ALL_TICKETS = """
query($owner:String!,$name:String!,$cursor:String){
  repository(owner:$owner,name:$name){ %s(first:100,after:$cursor){
    %s
    nodes{ number url state createdAt body }
  } }
}
"""

MORE = """
query($id:ID!,$cursor:String){ node(id:$id){ ... on %s{
  %s(first:100,after:$cursor){ %s nodes{ %s } }
} } }
"""


def paged(query, field, **variables):
    out, cursor = [], None
    while True:
        page = rh.graphql(query, owner=OWNER, name=NAME, cursor=cursor, **variables)["repository"][field]
        out += page["nodes"]
        if not page["pageInfo"]["hasNextPage"]:
            return out
        cursor = page["pageInfo"]["endCursor"]


def complete(node, field, typename, fragment):
    """Read the rest of a nested connection the first page did not finish."""
    conn = node[field]
    while conn["pageInfo"]["hasNextPage"]:
        more = rh.graphql(MORE % (typename, field, PAGE, fragment), id=node["id"],
                          cursor=conn["pageInfo"]["endCursor"])["node"][field]
        conn["nodes"] += more["nodes"]
        conn["pageInfo"] = more["pageInfo"]


def fetch():
    prs = paged(OPEN_PRS, "pullRequests")
    issues = paged(OPEN_ISSUES, "issues")
    for i in issues:
        complete(i, "comments", "Issue", WHO + " body")
    discussions = paged(OPEN_DISCUSSIONS, "discussions")
    for d in discussions:
        complete(d, "comments", "Discussion", "id %s body replies(first:50){ %s nodes{ %s body } }" % (WHO, PAGE, WHO))
        for c in d["comments"]["nodes"]:
            complete(c, "replies", "DiscussionComment", WHO + " body")
    tickets = {}
    for field in ("issues", "pullRequests"):
        for t in paged(ALL_TICKETS % (field, PAGE), field):
            tickets[t["number"]] = dict(t, kind="PR" if field == "pullRequests" else "issue")
    return prs, issues, discussions, tickets


# ---- reading the threads -----------------------------------------------------

def login(node):
    return (node.get("author") or {}).get("login") or "ghost"


def is_bot(name):
    return name.endswith("[bot]") or name in ("github-actions", "Copilot", "copilot-pull-request-reviewer")


def posts(thread):
    """The opening post, then every comment and reply, oldest first."""
    out = [{"author": thread.get("author"), "createdAt": thread["createdAt"], "body": thread.get("body") or ""}]
    for c in (thread.get("comments") or {}).get("nodes") or []:
        out.append(c)
        out += ((c.get("replies") or {}).get("nodes") or [])
    return sorted(out, key=lambda p: p["createdAt"])


def last_word(thread):
    """The newest post by a person, not a bot."""
    people = [p for p in posts(thread) if not is_bot(login(p))]
    return people[-1] if people else posts(thread)[0]


REF = re.compile(r"(?:github\.com/%s/%s/(?:issues|pull|discussions)/|(?<![\w/&])#)(\d+)\b"
                 % (re.escape(OWNER), re.escape(NAME)))


def refs(text):
    return [int(n) for n in REF.findall(text or "")]


def tracker(thread, maintainers):
    """The question rows of the thread's newest tracker comment by a maintainer, or None."""
    found = None
    for p in posts(thread):
        if TRACKER in p["body"] and login(p) in maintainers:
            found = p
    if not found:
        return None
    rows = []
    for line in found["body"].split(TRACKER, 1)[1].splitlines():
        cells = [c.strip() for c in line.strip().strip("|").split("|")]
        if len(cells) < 3 or not re.fullmatch(r"\d+", cells[0]):
            continue   # the header, the rule, or prose after the table
        status = (cells[2].split() or ["open"])[0].lower()
        rows.append({"n": int(cells[0]), "question": cells[1],
                     "status": status if status in STATUSES else "open",
                     "refs": refs(" ".join(cells[3:]))})
    return rows


def question_counts(rows, tickets):
    """{open, answered, ticketed, done}: a Ticketed row is done once all its tickets are closed."""
    out = {"open": 0, "answered": 0, "ticketed": 0, "done": 0}
    for r in rows:
        if r["status"] == "open":
            out["open"] += 1
        elif r["status"] == "ticketed":
            live = [n for n in r["refs"] if n in tickets and tickets[n]["state"] == "OPEN"]
            if r["refs"] and not live:
                out["done"] += 1
            elif r["refs"]:
                out["ticketed"] += 1
            else:
                out["open"] += 1   # ticketed, but no ticket named: still to do
        else:
            out["answered"] += 1   # answered, rejected or duplicate
    return out


def asks_several(thread):
    """A rough guess that the opening post asks more than one question."""
    body = re.sub(r"```.*?```", "", thread.get("body") or "", flags=re.S)
    return len(re.findall(r"\?(?:\s|$)", body)) >= 2


def raised_tickets(d, tickets):
    """Tickets raised from a discussion: newer than it, and named in it or naming it.

    The rule is discussion_audit.py's (#885): a reference to an older ticket is
    context, not a ticket raised.
    """
    out = set()
    for n in refs(" ".join(p["body"] for p in posts(d))):
        if n in tickets and tickets[n]["createdAt"] > d["createdAt"]:
            out.add(n)
    for n, t in tickets.items():
        if t["createdAt"] > d["createdAt"] and d["number"] in refs(t["body"]):
            out.add(n)
    return sorted(out)


# ---- deciding the next action ------------------------------------------------

def days(since, now):
    return (now - datetime.datetime.fromisoformat(since.replace("Z", "+00:00"))).days


# Pull requests, most urgent first: the order of this list is the page's.
PR_WAIT = [
    ("conflicts", "Rebase on develop: conflicts"),
    ("failing", "Fix CI: checks failing"),
    ("changes", "Address review: changes requested"),
    ("approved", "Merge: approved"),
    ("review", "Review needed"),
    ("draft", "Draft"),
]


def pr_action(pr):
    checks = ((((pr.get("commits") or {}).get("nodes") or [{}])[-1].get("commit") or {})
              .get("statusCheckRollup") or {}).get("state")
    if pr.get("isDraft"):
        return "draft"
    if pr.get("mergeable") == "CONFLICTING":
        return "conflicts"
    if checks in ("FAILURE", "ERROR"):
        return "failing"
    return {"CHANGES_REQUESTED": "changes", "APPROVED": "approved"}.get(pr.get("reviewDecision"), "review")


def pr_waiting_on(pr, action, maintainers):
    if action in ("conflicts", "failing", "changes", "draft"):
        return login(pr)
    if action == "approved":
        return "maintainers"
    asked = [r["requestedReviewer"].get("login") or "@" + r["requestedReviewer"].get("slug", "")
             for r in (pr.get("reviewRequests") or {}).get("nodes") or [] if r.get("requestedReviewer")]
    return ", ".join(asked) or "maintainers"


# Tickets and discussions, most urgent first.
THREAD_ACTIONS = [
    ("reply", "Reply: the last word is theirs"),
    ("close", "Close: every question answered or its ticket closed"),
    ("close-ticketed", "Close as ticketed: the open tickets carry the rest"),
    ("tracker", "Add a question tracker: several questions asked"),
    ("nudge", "Nudge or close: waiting on them, gone quiet"),
    ("wait", "Waiting on them"),
]


def thread_action(thread, rows, counts, raised, tickets, maintainers, stale, now):
    last = last_word(thread)
    theirs = login(last) not in maintainers
    if rows is not None and counts["open"] == 0:
        return "close-ticketed" if counts["ticketed"] else "close"
    if rows is None and raised and all(tickets[n]["state"] != "OPEN" for n in raised):
        return "close"
    if theirs:
        return "reply"
    if rows is None and asks_several(thread):
        return "tracker"
    if days(last["createdAt"], now) >= stale:
        return "nudge"
    return "wait"


def needs_triage(issue, maintainers):
    """An open issue belongs on this page when it is a query, has no milestone,
    carries a tracker, or is waiting on us; the heatmap carries the rest."""
    labels = {l["name"] for l in issue["labels"]["nodes"]}
    return ("Query" in labels or not issue.get("milestone") or tracker(issue, maintainers) is not None
            or login(last_word(issue)) not in maintainers)


# ---- the page ----------------------------------------------------------------

def cell(text):
    return (text or "").replace("|", "\\|").replace("\n", " ")


def link(n, url, title, width=70):
    title = title if len(title) <= width else title[:width - 1] + "…"
    return "[#%d](%s) %s" % (n, url, cell(title))


def questions(rows, counts):
    if rows is None:
        return "no tracker"
    parts = ["%d open" % counts["open"]] if counts["open"] else []
    parts += ["%d answered" % counts["answered"]] if counts["answered"] else []
    parts += ["%d ticketed" % counts["ticketed"]] if counts["ticketed"] else []
    parts += ["%d ticket closed" % counts["done"]] if counts["done"] else []
    return "%d: %s" % (len(rows), ", ".join(parts) or "none")


def ago(since, now):
    d = days(since, now)
    return "today" if d == 0 else "%dd" % d


def build(prs, issues, discussions, tickets, now, maintainers=MAINTAINERS, stale=STALE_DAYS):
    """Every row of the page, decided: {"prs": [...], "tickets": [...], "discussions": [...]}."""
    pr_rows = []
    for pr in prs:
        action = pr_action(pr)
        pr_rows.append({"pr": pr, "action": action, "waiting": pr_waiting_on(pr, action, maintainers),
                        "stale": days(pr["updatedAt"], now) >= stale})
    order = [k for k, _ in PR_WAIT]
    pr_rows.sort(key=lambda r: (order.index(r["action"]), r["pr"]["createdAt"]))

    def threads(items, discussion):
        out = []
        for t in items:
            rows = tracker(t, maintainers)
            counts = question_counts(rows or [], tickets)
            raised = raised_tickets(t, tickets) if discussion else []
            out.append({"thread": t, "rows": rows, "counts": counts, "raised": raised,
                        "last": last_word(t),
                        "action": thread_action(t, rows, counts, raised, tickets, maintainers, stale, now)})
        order = [k for k, _ in THREAD_ACTIONS]
        return sorted(out, key=lambda r: (order.index(r["action"]), r["last"]["createdAt"]))

    return {"prs": pr_rows,
            "tickets": threads([i for i in issues if needs_triage(i, maintainers)], False),
            "discussions": threads([d for d in discussions if d["category"]["name"] != "Announcements"], True),
            "skipped": sum(1 for i in issues if not needs_triage(i, maintainers))}


def render(built, tickets, now, maintainers=MAINTAINERS, stale=STALE_DAYS):
    generated = now.strftime("%Y-%m-%d %H:%M UTC")
    lines = [
        "# Triage action list", "",
        "_Generated %s by [`scripts/triage_action_list.py`](https://github.com/%s/blob/develop/scripts/"
        "triage_action_list.py). It updates itself when a PR, ticket or discussion changes; do not edit "
        "it by hand._" % (generated, REPO), "",
        "What is waiting on whom, most urgent first: pull requests, then tickets, then discussions. "
        "\"Us\" is %s. Quiet means no activity for %d days or more." % (", ".join(sorted(maintainers)), stale), "",
        "| Next action | Pull requests | Tickets | Discussions |", "| --- | --- | --- | --- |",
    ]
    for key, text in PR_WAIT:
        n = sum(1 for r in built["prs"] if r["action"] == key)
        if n:
            lines.append("| %s | %d | | |" % (text, n))
    for key, text in THREAD_ACTIONS:
        t = sum(1 for r in built["tickets"] if r["action"] == key)
        d = sum(1 for r in built["discussions"] if r["action"] == key)
        if t or d:
            lines.append("| %s | | %s | %s |" % (text, t or "", d or ""))
    lines.append("| **Total** | **%d** | **%d** | **%d** |"
                 % (len(built["prs"]), len(built["tickets"]), len(built["discussions"])))

    lines += ["", "## Pull requests", ""]
    if not built["prs"]:
        lines.append("None open.")
    else:
        lines += ["| Pull request | Author | Next action | Waiting on | Open for | Last activity | Closes |",
                  "| --- | --- | --- | --- | --- | --- | --- |"]
        text = dict(PR_WAIT)
        for r in built["prs"]:
            pr = r["pr"]
            closes = ", ".join("[#%d](%s)" % (i["number"], i["url"])
                               for i in (pr.get("closingIssuesReferences") or {}).get("nodes") or [])
            lines.append("| %s | %s | %s | %s | %s | %s%s | %s |" % (
                link(pr["number"], pr["url"], pr["title"]), login(pr), text[r["action"]].split(":")[0],
                r["waiting"], ago(pr["createdAt"], now), ago(pr["updatedAt"], now),
                " (quiet)" if r["stale"] else "", closes or "—"))

    lines += ["", "## Tickets", "",
              "Open issues labelled Query, with no milestone, with a question tracker, or whose last word is "
              "not ours. The other %d open issues are on the [release heatmap](Release-Heatmap)." % built["skipped"],
              ""]
    lines += thread_table(built["tickets"], tickets, now, discussion=False)
    lines += ["", "## Discussions", "", "Open discussions, except announcements.", ""]
    lines += thread_table(built["discussions"], tickets, now, discussion=True)

    lines += ["", "## Tracking the questions in a thread", "",
              "When a ticket or discussion asks several questions, add one comment to it that starts with "
              "`%s` and holds a table with a row per question:" % TRACKER, "",
              "```markdown", TRACKER, "| # | Question | Status | Where |", "| --- | --- | --- | --- |",
              "| 1 | Is PTS in ns or µs? | Answered | link to the reply |",
              "| 2 | Should flush() block? | Ticketed | #1013 |", "```", "",
              "Status is Open, Answered, Ticketed, Rejected or Duplicate. A Ticketed row counts as done once "
              "every ticket it names is closed. Edit the comment as questions are answered; this page follows."]
    return "\n".join(lines) + "\n"


def thread_table(rows, tickets, now, discussion):
    if not rows:
        return ["None."]
    head = "| %s | Raised by | Next action | Questions | %sLast word | Last activity |" % (
        "Discussion" if discussion else "Ticket", "Tickets raised | " if discussion else "Milestone | ")
    out = [head, "|" + " --- |" * (7)]
    text = dict(THREAD_ACTIONS)
    for r in rows:
        t = r["thread"]
        if discussion:
            extra = ", ".join("[#%d](%s) %s" % (n, tickets[n]["url"], tickets[n]["state"].lower())
                              for n in r["raised"]) or "—"
        else:
            extra = (t.get("milestone") or {}).get("title") or "**none**"
        out.append("| %s | %s | %s | %s | %s | %s | %s |" % (
            link(t["number"], t["url"], t["title"]), login(t), text[r["action"]].split(":")[0],
            questions(r["rows"], r["counts"]), cell(extra), login(r["last"]), ago(r["last"]["createdAt"], now)))
    return out


def parse_args(argv):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("-o", "--output", help="file to write, or - for stdout (default %s)"
                    % os.path.relpath(DEFAULT_OUT, ROOT))
    ap.add_argument("--publish", action="store_true", help="push the page to the wiki")
    ap.add_argument("--maintainer", action="extend", nargs="+", default=[], metavar="LOGIN",
                    help="whose reply counts as ours (default %s)" % ", ".join(MAINTAINERS))
    ap.add_argument("--stale-days", type=int, default=STALE_DAYS, metavar="N",
                    help="days without activity before a thread is quiet (default %(default)s)")
    return ap.parse_args(argv)


def main(argv):
    a = parse_args(argv)
    maintainers = set(a.maintainer or MAINTAINERS)
    now = datetime.datetime.now(datetime.timezone.utc)
    prs, issues, discussions, tickets = fetch()
    page = render(build(prs, issues, discussions, tickets, now, maintainers, a.stale_days),
                  tickets, now, maintainers, a.stale_days)

    if a.output == "-":
        sys.stdout.write(page)
    elif a.output or not a.publish:
        out = a.output or DEFAULT_OUT
        os.makedirs(os.path.dirname(os.path.abspath(out)), exist_ok=True)
        with open(out, "w") as fh:
            fh.write(page)
        print("wrote %s" % out)
    if a.publish:
        rh.publish(page, WIKI_PAGE, "Update triage action list")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))

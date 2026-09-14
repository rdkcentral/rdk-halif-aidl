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

"""Keep the project's Interface Effect field and the repo change-class labels in sync.

The same classification lives on three surfaces that do not talk to each other:
a ticket's labels, its pull request's labels, and the project field. Any of them
can be edited, so the sync has to work out which one moved rather than assuming.

  Sync state
    Each project item carries the value this script last wrote, in the
    `Interface Effect Sync` text field. Comparing labels and field against that
    stored value identifies the surface that actually changed. Without it a
    board edit is indistinguishable from a stale field and gets reverted.

  Who wins
    - Only the labels moved      -> the field is rewritten.
    - Only the field moved       -> the label is applied to the ticket.
    - Both moved                 -> the labels win; the divergence is reported.
    - PR vs its linked issue     -> the PR wins, because the PR is the change.
                                    A PR with no class inherits the issue's.
    - CR and New Interface       -> governance markers, not change classes. They
                                    are written *with* `Major Change`, never
                                    instead of it: docs/governance/versioning-sop.md
                                    is explicit that `release.sh` reads
                                    `Major Change` for the bump and never reads
                                    `CR`, so replacing it would lose the bump.

  Milestones
    Mirrored between a PR and its linked issues on the same rule, so a release
    view slicing on the milestone shows the whole of a release - the merged
    work included - rather than whichever side happened to be stamped.

  Scope
    Open tickets, plus closed ones still inside an open milestone. A closed
    ticket in a finished release is the record of what happened, and rewriting
    its labels a year later only generates notifications. `--all` includes it
    when that is genuinely wanted.

Subcommands:
  sync-item  --number N   one ticket, for a labeled/unlabeled event
  reconcile               every ticket, both directions (the scheduled sweep)
  check                   fail if the field options or labels have drifted

Auth: GH_TOKEN must hold `project` scope. The Actions GITHUB_TOKEN cannot read
or write organisation projects, so a PAT or App token is required.
"""

import argparse
import json
import os
import sys
import time
import urllib.error
import urllib.request

API = "https://api.github.com/graphql"

ORG = os.environ.get("PROJECT_ORG", "rdkcentral")
PROJECT_NUMBER = int(os.environ.get("PROJECT_NUMBER", "41"))
REPO_OWNER, REPO_NAME = os.environ.get(
    "GITHUB_REPOSITORY", "rdkcentral/rdk-halif-aidl"
).split("/")
FIELD_NAME = os.environ.get("PROJECT_FIELD_NAME", "Interface Effect")
STATE_FIELD_NAME = os.environ.get("PROJECT_STATE_FIELD_NAME", "Interface Effect Sync")

# Option -> (colour, labels selecting it), most significant first. A CR is a
# major change by shape raised at programme level, so it outranks Major and is
# named CR-Major. A brand-new interface is major by definition.
MAPPING = [
    ("CR-Major", "PURPLE", ["CR"]),
    ("New Interface", "ORANGE", ["New Interface"]),
    ("Major", "RED", ["Major Change", "Breaking Change"]),
    ("Minor", "BLUE", ["Minor Change"]),
    ("BugFix", "YELLOW", ["bug"]),
    ("Documentation", "GRAY", ["documentation"]),
]

# Display order of the options on the board.
OPTION_ORDER = ["Major", "CR-Major", "New Interface", "Minor", "BugFix", "Documentation"]

# Precedence, strongest first - MAPPING order is the precedence order.
PRECEDENCE = [option for option, _colour, _labels in MAPPING]

# What a board selection writes back. CR-Major and New Interface carry
# `Major Change` with them: the version bump is label-driven and `release.sh`
# only ever reads the change class, so a marker that replaced it would quietly
# turn a major release into a minor one.
#
# BugFix is the exception with no release meaning: it writes `bug`, which the
# bump logic does not read - a bugfix bump comes from `documentation` or from a
# linked issue of type Bug. Selecting BugFix on the board therefore classifies
# the ticket for people, not for the release. #827 decides whether the field or
# the labels drive the bump.
WRITEBACK_LABELS = {
    "CR-Major": ["CR", "Major Change"],
    "New Interface": ["New Interface", "Major Change"],
    "Major": ["Major Change"],
    "Minor": ["Minor Change"],
    "BugFix": ["bug"],
    "Documentation": ["documentation"],
}

# Every label the mapping owns: applying one means removing the others.
OWNED_LABELS = {label for _o, _c, labels in MAPPING for label in labels}

COLOUR_OF = {option: colour for option, colour, _l in MAPPING}
LABELS_OF = {option: labels for option, _c, labels in MAPPING}


class GraphQLError(RuntimeError):
    pass


def _token():
    tok = os.environ.get("GH_TOKEN") or os.environ.get("GITHUB_TOKEN")
    if not tok:
        sys.exit("GH_TOKEN with `project` scope is required")
    return tok


def gql(query, variables=None, retries=5):
    """POST a GraphQL document, waiting out throttling and transient 5xx."""
    payload = json.dumps({"query": query, "variables": variables or {}}).encode()
    for attempt in range(retries):
        req = urllib.request.Request(
            API,
            data=payload,
            headers={
                "Authorization": f"bearer {_token()}",
                "Content-Type": "application/json",
                "User-Agent": "rdk-halif-aidl-project-sync",
            },
        )
        try:
            with urllib.request.urlopen(req) as resp:
                body = json.loads(resp.read())
        except urllib.error.HTTPError as exc:
            if exc.code in (502, 503, 504) and attempt < retries - 1:
                time.sleep(2**attempt)
                continue
            raise
        if "errors" in body:
            message = "; ".join(e.get("message", "?") for e in body["errors"])
            if "rate limit" in message.lower() and attempt < retries - 1:
                time.sleep(2**attempt * 5)
                continue
            raise GraphQLError(message)
        return body["data"]
    raise GraphQLError("retries exhausted")


def class_of(labels):
    """The option a set of labels selects, or None if it carries no mapped label."""
    names = set(labels)
    for option, _colour, mapped in MAPPING:
        if names & set(mapped):
            return option
    return None


# --------------------------------------------------------------------------
# project / repo lookups
# --------------------------------------------------------------------------

ITEM_FIELDS = """
  id
  effect: fieldValueByName(name:"%s"){
    ... on ProjectV2ItemFieldSingleSelectValue{ name }
  }
  synced: fieldValueByName(name:"%s"){
    ... on ProjectV2ItemFieldTextValue{ text }
  }
  project{ number }
"""


def _item_fields():
    return ITEM_FIELDS % (FIELD_NAME, STATE_FIELD_NAME)


class Project:
    """Ids for the project and the two fields this script maintains."""

    def __init__(self):
        data = gql(
            """
            query($org:String!,$number:Int!){
              organization(login:$org){
                projectV2(number:$number){
                  id
                  fields(first:60){
                    nodes{
                      ... on ProjectV2Field{ id name dataType }
                      ... on ProjectV2SingleSelectField{ id name options{ id name color } }
                    }
                  }
                }
              }
            }
            """,
            {"org": ORG, "number": PROJECT_NUMBER},
        )
        project = data["organization"]["projectV2"]
        if not project:
            sys.exit(f"project {ORG}/{PROJECT_NUMBER} is not visible to this token")
        self.id = project["id"]
        self.field_id = None
        self.state_field_id = None
        self.options = {}
        for node in project["fields"]["nodes"]:
            if not node:
                continue
            if node.get("name") == FIELD_NAME and "options" in node:
                self.field_id = node["id"]
                self.options = {o["name"]: o for o in node["options"]}
            elif node.get("name") == STATE_FIELD_NAME:
                self.state_field_id = node["id"]
        if not self.field_id:
            sys.exit(f"field {FIELD_NAME!r} not found on project {PROJECT_NUMBER}")
        if not self.state_field_id:
            sys.exit(
                f"text field {STATE_FIELD_NAME!r} not found on project "
                f"{PROJECT_NUMBER} — create it before running the sync"
            )


def add_item(project, content_id):
    data = gql(
        """
        mutation($project:ID!,$content:ID!){
          addProjectV2ItemById(input:{projectId:$project,contentId:$content}){ item{ id } }
        }
        """,
        {"project": project.id, "content": content_id},
    )
    return data["addProjectV2ItemById"]["item"]["id"]


def set_effect(project, item_id, option):
    gql(
        """
        mutation($p:ID!,$i:ID!,$f:ID!,$o:String!){
          updateProjectV2ItemFieldValue(input:{
            projectId:$p,itemId:$i,fieldId:$f,value:{singleSelectOptionId:$o}
          }){ projectV2Item{ id } }
        }
        """,
        {
            "p": project.id,
            "i": item_id,
            "f": project.field_id,
            "o": project.options[option]["id"],
        },
    )


def read_item(project, item_id):
    """Re-read one item's two fields, to check nothing moved under a sweep."""
    data = gql(
        """
        query($id:ID!){ node(id:$id){ ... on ProjectV2Item{ %s } } }
        """
        % _item_fields(),
        {"id": item_id},
    )
    return data.get("node")


def clear_effect(project, item_id):
    gql(
        """
        mutation($p:ID!,$i:ID!,$f:ID!){
          clearProjectV2ItemFieldValue(input:{projectId:$p,itemId:$i,fieldId:$f}){
            projectV2Item{ id }
          }
        }
        """,
        {"p": project.id, "i": item_id, "f": project.field_id},
    )


def set_state(project, item_id, value):
    gql(
        """
        mutation($p:ID!,$i:ID!,$f:ID!,$t:String!){
          updateProjectV2ItemFieldValue(input:{
            projectId:$p,itemId:$i,fieldId:$f,value:{text:$t}
          }){ projectV2Item{ id } }
        }
        """,
        {"p": project.id, "i": item_id, "f": project.state_field_id, "t": value or ""},
    )


_label_ids = {}


def label_id(name):
    if name not in _label_ids:
        data = gql(
            """
            query($owner:String!,$name:String!,$label:String!){
              repository(owner:$owner,name:$name){ label(name:$label){ id } }
            }
            """,
            {"owner": REPO_OWNER, "name": REPO_NAME, "label": name},
        )
        node = data["repository"]["label"]
        _label_ids[name] = node["id"] if node else None
    return _label_ids[name]


def remove_owned_labels(content_id, current_labels):
    """Strip every classification label, for a ticket cleared on the board."""
    ids = [label_id(name) for name in current_labels if name in OWNED_LABELS]
    ids = [i for i in ids if i]
    if not ids:
        return
    gql(
        """
        mutation($l:ID!,$ids:[ID!]!){
          removeLabelsFromLabelable(input:{labelableId:$l,labelIds:$ids}){ clientMutationId }
        }
        """,
        {"l": content_id, "ids": ids},
    )


def apply_labels(content_id, option, current_labels):
    """Apply every label an option implies, and strip only what it displaces.

    Returns False when a label the option needs does not exist in the repo, so
    the caller can leave the sync state alone and let the next sweep retry.
    """
    wanted = WRITEBACK_LABELS[option]
    missing = [name for name in wanted if not label_id(name)]
    if missing:
        print(f"    ! label(s) {missing} missing from the repo — skipped")
        return False

    additions = [label_id(name) for name in wanted if name not in current_labels]
    if additions:
        gql(
            """
            mutation($l:ID!,$ids:[ID!]!){
              addLabelsToLabelable(input:{labelableId:$l,labelIds:$ids}){ clientMutationId }
            }
            """,
            {"l": content_id, "ids": additions},
        )

    # A retired alias of the same class (Breaking Change for Major) is left
    # alone; only a label belonging to a class this option replaces is removed.
    keep = set(wanted) | set(LABELS_OF[option])
    stale = [label_id(name) for name in current_labels if name in OWNED_LABELS and name not in keep]
    stale = [i for i in stale if i]
    if stale:
        gql(
            """
            mutation($l:ID!,$ids:[ID!]!){
              removeLabelsFromLabelable(input:{labelableId:$l,labelIds:$ids}){ clientMutationId }
            }
            """,
            {"l": content_id, "ids": stale},
        )
    return True


# --------------------------------------------------------------------------
# the sync itself
# --------------------------------------------------------------------------


def our_item(ticket):
    for item in ticket["projectItems"]["nodes"]:
        if item["project"]["number"] == PROJECT_NUMBER:
            return item
    return None


def resolve(labels_class, field_class, synced):
    """Which class wins, and why, given the three surfaces and the stored state.

    Returns (winner, reason). `winner` may be None when nothing is classified.
    """
    if labels_class == field_class:
        return labels_class, "agree"
    labels_moved = labels_class != synced
    field_moved = field_class != synced
    if field_moved and not labels_moved:
        # Someone classified it on the board: that is the new truth.
        return field_class, "board edit"
    if labels_moved and not field_moved:
        return labels_class, "label edit"
    if labels_moved and field_moved:
        return labels_class, "both moved, labels win"
    # Neither moved but they differ: the field was never written. Labels lead.
    return labels_class, "field never set"


def sync_ticket(project, ticket, dry_run, report):
    """Bring one ticket's labels, project item and stored state into agreement."""
    number = ticket["number"]
    labels = [n["name"] for n in ticket["labels"]["nodes"]]
    labels_class = class_of(labels)

    item = our_item(ticket)
    if item is None:
        if dry_run:
            report.append(f"#{number}: would add to project")
            return "would-add"
        item = {"id": add_item(project, ticket["id"]), "effect": None, "synced": None}
        report.append(f"#{number}: added to project")

    field_class = (item.get("effect") or {}).get("name")
    synced = (item.get("synced") or {}).get("text") or None

    # An option nobody mapped (a stale rename, or one added by hand on the
    # board) must not be resolved into a label lookup that raises.
    if field_class and field_class not in WRITEBACK_LABELS:
        report.append(f"#{number}: board value {field_class!r} is not in the mapping")
        return None

    winner, reason = resolve(labels_class, field_class, synced)

    if winner is None:
        # The classification is gone from whichever surface still held it.
        # Clearing only the field would leave the labels to restore it on the
        # next sweep, so clearing on the board has to take the labels with it.
        if field_class or synced or labels_class:
            if not dry_run:
                if field_class:
                    clear_effect(project, item["id"])
                if labels_class:
                    remove_owned_labels(ticket["id"], labels)
                set_state(project, item["id"], "")
            report.append(f"#{number}: cleared, classification removed")
            return "changed"
        return None

    # A ticket carrying only `CR` already resolves to CR-Major, so comparing
    # classes alone would never add the `Major Change` that carries the bump.
    # Normalise whenever any label the option implies is absent.
    absent = [name for name in WRITEBACK_LABELS[winner] if name not in labels]
    needs_write = (
        winner != field_class or winner != labels_class or absent or winner != synced
    )

    # A sweep reads every ticket and then writes, so an event-driven run can
    # land in between and this snapshot goes stale. Re-read the item before the
    # first write and step aside if it moved - the next sweep sees the new value
    # rather than this one overwriting it.
    if needs_write and not dry_run:
        fresh = read_item(project, item["id"])
        if fresh is not None:
            fresh_class = (fresh.get("effect") or {}).get("name")
            fresh_state = (fresh.get("synced") or {}).get("text") or None
            if fresh_class != field_class or fresh_state != synced:
                report.append(f"#{number}: skipped, the item moved while the sweep ran")
                return None

    actions = []
    labels_written = True
    if winner != field_class:
        if not dry_run:
            set_effect(project, item["id"], winner)
        actions.append(f"field->{winner}")
    if winner != labels_class or absent:
        if not dry_run:
            labels_written = apply_labels(ticket["id"], winner, labels)
        actions.append(f"label->{'+'.join(WRITEBACK_LABELS[winner])}")
    # Record the sync only once the writes landed: a label that could not be
    # written must be retried by the next sweep, not marked as done.
    if winner != synced and labels_written and not dry_run:
        set_state(project, item["id"], winner)

    if actions:
        report.append(f"#{number}: {', '.join(actions)} ({reason})")
        return "changed"
    return None


def set_milestone(node_id, milestone_id, is_pr):
    mutation = (
        "mutation($id:ID!,$m:ID){updatePullRequest(input:{pullRequestId:$id,"
        "milestoneId:$m}){clientMutationId}}"
        if is_pr
        else "mutation($id:ID!,$m:ID){updateIssue(input:{id:$id,milestoneId:$m})"
        "{clientMutationId}}"
    )
    gql(mutation, {"id": node_id, "m": milestone_id})


def mirror_milestone(pr, linked, dry_run, report):
    """Keep a PR and its linked issues on the same milestone, PR first.

    A release view slices on the milestone, so a PR stamped for the release
    whose issue is not (or the reverse) leaves half the release invisible.
    """
    # Settle on the source before touching anything, so a PR with no milestone
    # and several linked issues does not adopt one and leave the earlier issues
    # outside the release view.
    pr_milestone = pr.get("milestone")
    source = pr_milestone or next(
        (issue["milestone"] for issue in linked if issue.get("milestone")), None
    )
    if not source:
        return

    if not pr_milestone:
        if not dry_run:
            set_milestone(pr["id"], source["id"], is_pr=True)
        pr["milestone"] = source
        report.append(f"PR #{pr['number']}: milestone -> {source['title']} (inherited)")

    for issue in linked:
        issue_milestone = issue.get("milestone")
        if not issue_milestone or issue_milestone["title"] != source["title"]:
            if not dry_run:
                set_milestone(issue["id"], source["id"], is_pr=False)
            report.append(
                f"#{issue['number']}: milestone -> {source['title']} "
                f"(from PR #{pr['number']})"
            )


def propagate_pr_to_issues(pr, dry_run, report):
    """The PR is the change: its class overwrites a linked issue that differs.

    A PR with no class inherits from its linked issue instead, so a classified
    ticket still reaches the board through its PR.
    """
    linked = pr.get("closingIssuesReferences", {}).get("nodes", [])
    if not linked:
        return []
    mirror_milestone(pr, linked, dry_run, report)
    pr_labels = [n["name"] for n in pr["labels"]["nodes"]]
    pr_class = class_of(pr_labels)
    touched = []

    if pr_class is None:
        # Take the strongest class across every linked issue rather than
        # whichever the API returned first, then fall through so the remaining
        # linked issues are brought up to it as well.
        candidates = [
            class_of([n["name"] for n in issue["labels"]["nodes"]]) for issue in linked
        ]
        candidates = [c for c in candidates if c]
        if not candidates:
            return []
        inherited = min(candidates, key=PRECEDENCE.index)
        if not dry_run:
            if not apply_labels(pr["id"], inherited, pr_labels):
                # The write failed, so the PR still has no class. Leave the
                # local object alone and let the next sweep retry.
                return []
            # Reflect the write locally so the caller syncs this PR's item with
            # the class it now has, not the one it had.
            pr["labels"]["nodes"] = [
                {"name": name}
                for name in sorted(set(pr_labels) | set(WRITEBACK_LABELS[inherited]))
            ]
        report.append(f"PR #{pr['number']}: inherited {inherited} from its linked issues")
        pr_class = inherited
        pr_labels = [n["name"] for n in pr["labels"]["nodes"]]

    for issue in linked:
        issue_labels = [n["name"] for n in issue["labels"]["nodes"]]
        if class_of(issue_labels) != pr_class:
            if not dry_run:
                apply_labels(issue["id"], pr_class, issue_labels)
            report.append(
                f"#{issue['number']}: {pr_class} from PR #{pr['number']} (PR wins)"
            )
            touched.append(issue["number"])
    return touched


TICKET_QUERY = """
query($owner:String!,$name:String!,$cursor:String){
  repository(owner:$owner,name:$name){
    %(kind)s(first:50,after:$cursor,states:[%(states)s]){
      pageInfo{ hasNextPage endCursor }
      nodes{
        id number state
        milestone{ id title state }
        labels(first:50){ nodes{ name } }
        %(links)s
        projectItems(first:20,includeArchived:false){ nodes{ %(item)s } }
      }
    }
  }
}
"""

LINKS = """
        closingIssuesReferences(first:10){
          nodes{ id number milestone{ id title state } labels(first:50){ nodes{ name } } }
        }
"""


def fetch(kind, states, links):
    cursor = None
    while True:
        data = gql(
            TICKET_QUERY
            % {
                "kind": kind,
                "states": states,
                "links": LINKS if links else "",
                "item": _item_fields(),
            },
            {"owner": REPO_OWNER, "name": REPO_NAME, "cursor": cursor},
        )
        block = data["repository"][kind]
        for node in block["nodes"]:
            yield node
        if not block["pageInfo"]["hasNextPage"]:
            return
        cursor = block["pageInfo"]["endCursor"]


def in_scope(ticket, everything):
    """Open work, plus closed work still inside an open milestone.

    A closed ticket in a finished release is the record of what happened;
    rewriting its labels once the release has shipped only sends notifications
    to everyone who touched it.
    """
    if everything:
        return True
    if ticket.get("state") == "OPEN":
        return True
    milestone = ticket.get("milestone")
    return bool(milestone and milestone.get("state") == "OPEN")


def cmd_reconcile(args):
    project = Project()
    missing = [o for o in OPTION_ORDER if o not in project.options]
    if missing:
        sys.exit(f"field is missing options {missing} — run `check` first")

    report = []
    prs = [
        pr
        for pr in fetch("pullRequests", "OPEN,CLOSED,MERGED", links=True)
        if in_scope(pr, args.all)
    ]
    for pr in prs:
        propagate_pr_to_issues(pr, args.dry_run, report)
    propagated = len(report)

    issues = [
        issue
        for issue in fetch("issues", "OPEN,CLOSED", links=False)
        if in_scope(issue, args.all)
    ]
    for ticket in prs + issues:
        sync_ticket(project, ticket, args.dry_run, report)

    for line in report:
        print(f"  {line}")
    seen = len(prs) + len(issues)
    headline = (
        f"{seen} tickets in scope, {len(report)} change(s): "
        f"{propagated} between PRs and their issues, "
        f"{len(report) - propagated} on project items"
    )
    print(f"\n{headline}")
    summary = os.environ.get("GITHUB_STEP_SUMMARY")
    if summary:
        with open(summary, "a", encoding="utf-8") as handle:
            handle.write(f"### Interface Effect sync\n\n{headline}\n\n")
            for line in report[:100]:
                handle.write(f"- {line}\n")


def cmd_sync_item(args):
    project = Project()
    data = gql(
        """
        query($owner:String!,$name:String!,$number:Int!){
          repository(owner:$owner,name:$name){
            issueOrPullRequest(number:$number){
              ... on Issue{ id number milestone{ id title } labels(first:50){nodes{name}}
                projectItems(first:20,includeArchived:false){nodes{ %(item)s }} }
              ... on PullRequest{ id number milestone{ id title } labels(first:50){nodes{name}}
                %(links)s
                projectItems(first:20,includeArchived:false){nodes{ %(item)s }} }
            }
          }
        }
        """
        % {"item": _item_fields(), "links": LINKS},
        {"owner": REPO_OWNER, "name": REPO_NAME, "number": args.number},
    )
    ticket = data["repository"]["issueOrPullRequest"]
    if not ticket:
        sys.exit(f"#{args.number} not found")

    report = []
    touched = propagate_pr_to_issues(ticket, args.dry_run, report)
    sync_ticket(project, ticket, args.dry_run, report)

    # A linked issue that just changed needs its own item updating too.
    for number in touched:
        follow = gql(
            """
            query($owner:String!,$name:String!,$number:Int!){
              repository(owner:$owner,name:$name){
                issue(number:$number){ id number labels(first:50){nodes{name}}
                  projectItems(first:20,includeArchived:false){nodes{ %s }} }
              }
            }
            """
            % _item_fields(),
            {"owner": REPO_OWNER, "name": REPO_NAME, "number": number},
        )["repository"]["issue"]
        if follow:
            sync_ticket(project, follow, args.dry_run, report)

    for line in report or [f"#{args.number}: already in sync"]:
        print(f"  {line}")


def cmd_check(args):
    """Fail when the field options or the mapped labels have drifted."""
    project = Project()
    problems = []

    for option in OPTION_ORDER:
        got = project.options.get(option)
        if not got:
            problems.append(f"option {option!r} is missing from the field")
        elif got["color"] != COLOUR_OF[option]:
            problems.append(
                f"option {option!r} is {got['color']}, the mapping says {COLOUR_OF[option]}"
            )
    for extra in set(project.options) - set(OPTION_ORDER):
        problems.append(f"option {extra!r} on the field is not in the mapping")

    have = set()
    cursor = None
    while True:
        data = gql(
            """
            query($owner:String!,$name:String!,$cursor:String){
              repository(owner:$owner,name:$name){
                labels(first:100,after:$cursor){
                  pageInfo{ hasNextPage endCursor } nodes{ name }
                }
              }
            }
            """,
            {"owner": REPO_OWNER, "name": REPO_NAME, "cursor": cursor},
        )["repository"]["labels"]
        have.update(n["name"] for n in data["nodes"])
        if not data["pageInfo"]["hasNextPage"]:
            break
        cursor = data["pageInfo"]["endCursor"]

    for label in sorted(OWNED_LABELS):
        if label not in have:
            problems.append(f"label {label!r} is mapped but does not exist in the repo")

    for problem in problems:
        print(f"  drift: {problem}")
    if problems:
        sys.exit(f"{len(problems)} drift(s) between the labels and the project field")
    print("labels and field options agree")


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    sub = parser.add_subparsers(dest="command", required=True)

    one = sub.add_parser("sync-item", help="sync one ticket after a label event")
    one.add_argument("--number", type=int, required=True)
    one.add_argument("--dry-run", action="store_true")
    one.set_defaults(func=cmd_sync_item)

    every = sub.add_parser("reconcile", help="sweep tickets in scope, both directions")
    every.add_argument("--dry-run", action="store_true")
    every.add_argument(
        "--all",
        action="store_true",
        help="include closed tickets whose milestone has shipped",
    )
    every.set_defaults(func=cmd_reconcile)

    guard = sub.add_parser("check", help="fail on drift between labels and options")
    guard.set_defaults(func=cmd_check)

    args = parser.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()

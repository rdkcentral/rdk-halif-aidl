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

# The label written when the board is the only surface that classified a ticket.
WRITEBACK_LABEL = {option: labels[0] for option, _colour, labels in MAPPING}

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


def apply_label(content_id, option, current_labels):
    """Put the option's label on a ticket and strip the other mapped ones."""
    wanted = WRITEBACK_LABEL[option]
    target = label_id(wanted)
    if not target:
        print(f"    ! label {wanted!r} missing from the repo — skipped")
        return False
    if wanted not in current_labels:
        gql(
            """
            mutation($l:ID!,$ids:[ID!]!){
              addLabelsToLabelable(input:{labelableId:$l,labelIds:$ids}){ clientMutationId }
            }
            """,
            {"l": content_id, "ids": [target]},
        )
    stale = [
        label_id(name)
        for name in current_labels
        if name in OWNED_LABELS and name not in LABELS_OF[option]
    ]
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
    winner, reason = resolve(labels_class, field_class, synced)

    if winner is None:
        return None

    actions = []
    if winner != field_class:
        if not dry_run:
            set_effect(project, item["id"], winner)
        actions.append(f"field->{winner}")
    if winner != labels_class:
        if not dry_run:
            apply_label(ticket["id"], winner, labels)
        actions.append(f"label->{WRITEBACK_LABEL[winner]}")
    if winner != synced and not dry_run:
        set_state(project, item["id"], winner)

    if actions:
        report.append(f"#{number}: {', '.join(actions)} ({reason})")
        return "changed"
    return None


def propagate_pr_to_issues(pr, dry_run, report):
    """The PR is the change: its class overwrites a linked issue that differs.

    A PR with no class inherits from its linked issue instead, so a classified
    ticket still reaches the board through its PR.
    """
    linked = pr.get("closingIssuesReferences", {}).get("nodes", [])
    if not linked:
        return []
    pr_labels = [n["name"] for n in pr["labels"]["nodes"]]
    pr_class = class_of(pr_labels)
    touched = []

    if pr_class is None:
        for issue in linked:
            issue_class = class_of([n["name"] for n in issue["labels"]["nodes"]])
            if issue_class:
                if not dry_run:
                    apply_label(pr["id"], issue_class, pr_labels)
                report.append(
                    f"PR #{pr['number']}: inherited {issue_class} from #{issue['number']}"
                )
                return [pr["number"]]
        return []

    for issue in linked:
        issue_labels = [n["name"] for n in issue["labels"]["nodes"]]
        if class_of(issue_labels) != pr_class:
            if not dry_run:
                apply_label(issue["id"], pr_class, issue_labels)
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
        id number
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
          nodes{ id number labels(first:50){ nodes{ name } } }
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


def cmd_reconcile(args):
    project = Project()
    missing = [o for o in OPTION_ORDER if o not in project.options]
    if missing:
        sys.exit(f"field is missing options {missing} — run `check` first")

    report = []
    prs = list(fetch("pullRequests", "OPEN,CLOSED,MERGED", links=True))
    for pr in prs:
        propagate_pr_to_issues(pr, args.dry_run, report)

    changed = 0
    seen = 0
    for ticket in prs + list(fetch("issues", "OPEN,CLOSED", links=False)):
        seen += 1
        if sync_ticket(project, ticket, args.dry_run, report):
            changed += 1

    for line in report:
        print(f"  {line}")
    print(f"\n{seen} tickets examined, {changed} changed")
    summary = os.environ.get("GITHUB_STEP_SUMMARY")
    if summary:
        with open(summary, "a", encoding="utf-8") as handle:
            handle.write(f"### Interface Effect sync\n\n{seen} examined, {changed} changed\n\n")
            for line in report[:100]:
                handle.write(f"- {line}\n")


def cmd_sync_item(args):
    project = Project()
    data = gql(
        """
        query($owner:String!,$name:String!,$number:Int!){
          repository(owner:$owner,name:$name){
            issueOrPullRequest(number:$number){
              ... on Issue{ id number labels(first:50){nodes{name}}
                projectItems(first:20,includeArchived:false){nodes{ %(item)s }} }
              ... on PullRequest{ id number labels(first:50){nodes{name}}
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

    every = sub.add_parser("reconcile", help="sweep every ticket, both directions")
    every.add_argument("--dry-run", action="store_true")
    every.set_defaults(func=cmd_reconcile)

    guard = sub.add_parser("check", help="fail on drift between labels and options")
    guard.set_defaults(func=cmd_check)

    args = parser.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()

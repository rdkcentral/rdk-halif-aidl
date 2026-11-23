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

"""Tests for scripts/triage_action_list.py: trackers, next actions and the page.

Run: python3 -m unittest discover -s tests/scripts
"""

import datetime
import importlib.util
import os
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
spec = importlib.util.spec_from_file_location("triage_action_list",
                                              os.path.join(ROOT, "scripts", "triage_action_list.py"))
tal = importlib.util.module_from_spec(spec)
spec.loader.exec_module(tal)

NOW = datetime.datetime(2026, 11, 23, tzinfo=datetime.timezone.utc)
US = {"Ulrond"}


def post(who, when, body=""):
    return {"author": {"login": who}, "createdAt": when, "body": body}


def thread(number=1, author="asker", created="2026-11-01T00:00:00Z", body="One question?", comments=(),
           milestone=None, labels=(), category="General"):
    return {"number": number, "title": "T%d" % number, "url": "u%d" % number, "author": {"login": author},
            "createdAt": created, "updatedAt": created, "body": body,
            "milestone": {"title": milestone} if milestone else None,
            "labels": {"nodes": [{"name": l} for l in labels]}, "category": {"name": category},
            "comments": {"nodes": list(comments)}}


def table(*rows):
    return "\n".join([tal.TRACKER, "| # | Question | Status | Where |", "| --- | --- | --- | --- |"]
                     + ["| %d | %s | %s | %s |" % r for r in rows])


def ticket(n, state="OPEN", created="2026-11-10T00:00:00Z", body=""):
    return {"number": n, "url": "t%d" % n, "state": state, "createdAt": created, "body": body, "kind": "issue"}


class Tracker(unittest.TestCase):
    def test_reads_rows_from_a_maintainer_comment(self):
        t = thread(comments=[post("Ulrond", "2026-11-02T00:00:00Z",
                                  table((1, "PTS units?", "Answered", "link"), (2, "flush?", "Ticketed", "#20")))])
        rows = tal.tracker(t, US)
        self.assertEqual([(r["n"], r["status"], r["refs"]) for r in rows],
                         [(1, "answered", []), (2, "ticketed", [20])])

    def test_ignores_a_tracker_from_anyone_else(self):
        t = thread(comments=[post("asker", "2026-11-02T00:00:00Z", table((1, "q", "Answered", "")))])
        self.assertIsNone(tal.tracker(t, US))

    def test_unknown_status_counts_as_open(self):
        t = thread(comments=[post("Ulrond", "2026-11-02T00:00:00Z", table((1, "q", "maybe", "")))])
        self.assertEqual(tal.tracker(t, US)[0]["status"], "open")

    def test_ticketed_row_is_done_once_its_ticket_closes(self):
        rows = [{"status": "ticketed", "refs": [20]}, {"status": "ticketed", "refs": [21]},
                {"status": "ticketed", "refs": []}, {"status": "rejected", "refs": []}]
        counts = tal.question_counts(rows, {20: ticket(20, "CLOSED"), 21: ticket(21)})
        self.assertEqual(counts, {"open": 1, "answered": 1, "ticketed": 1, "done": 1})


class ThreadAction(unittest.TestCase):
    def act(self, t, tickets=None, raised=()):
        rows = tal.tracker(t, US)
        counts = tal.question_counts(rows or [], tickets or {})
        return tal.thread_action(t, rows, counts, list(raised), tickets or {}, US, 14, NOW)

    def test_their_last_word_needs_a_reply(self):
        self.assertEqual(self.act(thread(created="2026-11-20T00:00:00Z")), "reply")

    def test_a_bot_never_has_the_last_word(self):
        t = thread(comments=[post("Ulrond", "2026-11-20T00:00:00Z"), post("github-actions[bot]", "2026-11-21T00:00:00Z")])
        self.assertEqual(self.act(t), "wait")

    def test_all_questions_covered_closes(self):
        t = thread(comments=[post("Ulrond", "2026-11-02T00:00:00Z", table((1, "q", "Answered", "")))])
        self.assertEqual(self.act(t), "close")

    def test_open_tickets_close_as_ticketed(self):
        t = thread(comments=[post("Ulrond", "2026-11-02T00:00:00Z", table((1, "q", "Ticketed", "#20")))])
        self.assertEqual(self.act(t, {20: ticket(20)}), "close-ticketed")

    def test_raised_tickets_all_closed_closes(self):
        self.assertEqual(self.act(thread(), {20: ticket(20, "CLOSED")}, raised=[20]), "close")

    def test_several_questions_without_a_tracker(self):
        t = thread(body="Is it A? Is it B?", comments=[post("Ulrond", "2026-11-20T00:00:00Z")])
        self.assertEqual(self.act(t), "tracker")

    def test_quiet_after_our_reply_is_a_nudge(self):
        t = thread(comments=[post("Ulrond", "2026-11-02T00:00:00Z")])
        self.assertEqual(self.act(t), "nudge")


class Raised(unittest.TestCase):
    def test_newer_ticket_named_either_way_is_raised_older_is_context(self):
        d = thread(number=5, body="see #3 and #20")
        tickets = {3: ticket(3, created="2026-10-01T00:00:00Z"), 20: ticket(20),
                   21: ticket(21, body="From #5")}
        self.assertEqual(tal.raised_tickets(d, tickets), [20, 21])


class PullRequests(unittest.TestCase):
    def pr(self, **kw):
        base = {"number": 9, "title": "P", "url": "p9", "author": {"login": "dev"}, "isDraft": False,
                "mergeable": "MERGEABLE", "reviewDecision": "REVIEW_REQUIRED",
                "createdAt": "2026-11-01T00:00:00Z", "updatedAt": "2026-11-20T00:00:00Z",
                "commits": {"nodes": [{"commit": {"statusCheckRollup": {"state": "SUCCESS"}}}]},
                "reviewRequests": {"nodes": [{"requestedReviewer": {"slug": "team"}}]},
                "closingIssuesReferences": {"nodes": []}}
        base.update(kw)
        return base

    def test_states_in_priority_order(self):
        self.assertEqual(tal.pr_action(self.pr(mergeable="CONFLICTING")), "conflicts")
        self.assertEqual(tal.pr_action(self.pr(commits={"nodes": [{"commit": {"statusCheckRollup": {"state": "FAILURE"}}}]})), "failing")
        self.assertEqual(tal.pr_action(self.pr(reviewDecision="CHANGES_REQUESTED")), "changes")
        self.assertEqual(tal.pr_action(self.pr(reviewDecision="APPROVED")), "approved")
        self.assertEqual(tal.pr_action(self.pr()), "review")
        self.assertEqual(tal.pr_action(self.pr(isDraft=True, mergeable="CONFLICTING")), "draft")

    def test_review_waits_on_the_requested_reviewers(self):
        self.assertEqual(tal.pr_waiting_on(self.pr(), "review", US), "@team")
        self.assertEqual(tal.pr_waiting_on(self.pr(), "changes", US), "dev")


class Page(unittest.TestCase):
    def test_renders_every_section_with_prs_first(self):
        prs = [PullRequests().pr()]
        issues = [thread(number=2, labels=["Query"])]
        discussions = [thread(number=3), thread(number=4, category="Announcements")]
        page = tal.render(tal.build(prs, issues, discussions, {}, NOW, US), {}, NOW, US)
        self.assertLess(page.index("## Pull requests"), page.index("## Tickets"))
        self.assertLess(page.index("## Tickets"), page.index("## Discussions"))
        self.assertIn("[#3](u3)", page)
        self.assertNotIn("[#4](u4)", page)

    def test_a_milestoned_issue_waiting_on_them_is_left_to_the_heatmap(self):
        i = thread(number=2, milestone="0.24.0", comments=[post("Ulrond", "2026-11-20T00:00:00Z")])
        self.assertEqual(tal.build([], [i], [], {}, NOW, US)["skipped"], 1)


if __name__ == "__main__":
    unittest.main()

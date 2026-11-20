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

"""Tests for scripts/release_heatmap.py: classification, scoring and checks.

Run: python3 -m unittest discover -s tests/scripts
"""

import importlib.util
import io
import os
import tempfile
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
spec = importlib.util.spec_from_file_location("release_heatmap",
                                              os.path.join(ROOT, "scripts", "release_heatmap.py"))
rh = importlib.util.module_from_spec(spec)
spec.loader.exec_module(rh)


def issue(number=1, labels=(), milestone=None, due=None, author="someone", priority=None,
          effect=None, blocking=0, people=1, refs=0, prs=(), ref_prs=()):
    values = []
    if priority:
        values.append({"name": priority, "field": {"name": "Priority"}})
    if effect:
        values.append({"name": effect, "field": {"name": "Interface Effect"}})
    return {
        "number": number, "title": "T%d" % number, "url": "u%d" % number,
        "author": {"login": author},
        "milestone": {"title": milestone, "dueOn": due} if milestone else None,
        "labels": {"nodes": [{"name": l} for l in labels]},
        "participants": {"totalCount": people},
        "timelineItems": {"totalCount": refs, "nodes": [{"source": dict(
            {"url": "p%d" % p["number"], "isDraft": False, "reviewDecision": None, "baseRefName": "develop",
             "repository": {"isPrivate": False, "nameWithOwner": rh.REPO}, "body": "Refs #%d" % number}, **p)}
            for p in ref_prs]},
        "issueDependenciesSummary": {"blocking": blocking},
        "closedByPullRequestsReferences": {"pageInfo": {"hasNextPage": False}, "nodes": [dict(
            {"url": "p%d" % p["number"], "isDraft": False, "reviewDecision": None, "baseRefName": "develop"}, **p)
            for p in prs]},
        "projectFields": {v["field"]["name"]: v["name"] for v in values},
    }


class Classify(unittest.TestCase):

    def test_components_from_labels(self):
        t = rh.classify(issue(labels=["component:audiosink", "component:videosink"]), set(), "2026-11-03", None)
        self.assertEqual(t["components"], ["audiosink", "videosink"])

    def test_infrastructure_and_no_component(self):
        self.assertEqual(rh.classify(issue(labels=["scope:infrastructure"]), set(), "2026-11-03", None)["components"],
                         ["(infrastructure)"])
        self.assertEqual(rh.classify(issue(), set(), "2026-11-03", None)["components"], ["(no component)"])

    def test_repo_wide_rows(self):
        def comps(labels):
            return rh.classify(issue(labels=labels), set(), "2026-11-03", None)["components"]
        self.assertEqual(comps(["scope:overview", "documentation"]), ["(overview)"])
        self.assertEqual(comps(["documentation"]), ["(documentation)"])
        self.assertEqual(comps(["documentation", "component:panel"]), ["panel"])

    def test_labels_win_over_field(self):
        t = rh.classify(issue(labels=["Major Change"], effect="Minor"), set(), "2026-11-03", None)
        self.assertEqual(t["effect"], "Major")

    def test_field_fills_in_without_label(self):
        t = rh.classify(issue(effect="Minor"), set(), "2026-11-03", None)
        self.assertEqual(t["effect"], "Minor")

    def test_project_fields_only_for_this_repo(self):
        def node(n, repo, prio):
            return {"content": {"number": n, "repository": {"nameWithOwner": repo}},
                    "fieldValues": {"nodes": [{}, {"name": prio, "field": {"name": "Priority"}}]}}
        got = rh.item_fields([node(1, rh.REPO, "P1 - High"), node(1, "rdkcentral/other", "P0 - Critical"),
                              {"content": {}, "fieldValues": {"nodes": []}}])
        self.assertEqual(got, {1: {"Priority": "P1 - High"}})

    def test_query_is_the_weakest_class(self):
        def effect(labels):
            return rh.classify(issue(labels=labels), set(), "2026-11-03", None)["effect"]
        self.assertEqual(effect(["Query"]), "Query")
        self.assertEqual(effect(["Query", "Minor Change"]), "Minor")
        self.assertEqual(effect(["Query", "scope:infrastructure"]), "Infrastructure")

    def test_score(self):
        t = rh.classify(issue(labels=["Major Change"], milestone="0.24.0", due="2026-10-30T00:00:00Z",
                              priority="P0 - Critical", blocking=1, people=3, refs=6, author="ext"),
                        {"Ulrond"}, "2026-11-03", None)
        # P0 5 + blocks 3 + raised by other 2 + breaking 2 + overdue 2 + people 1 + refs 1
        self.assertEqual(t["score"], 16)

    def test_next_due_scores_one(self):
        t = rh.classify(issue(milestone="0.25.0", due="2026-11-30T00:00:00Z"), set(), "2026-11-03", "2026-11-30")
        self.assertEqual(t["score"], 1)


class Render(unittest.TestCase):

    def test_cell_badges_each_ticket_by_class(self):
        major = rh.classify(issue(1, labels=["Major Change", "component:panel"], milestone="0.24.0"), set(), "2026-11-03", None)
        minor = rh.classify(issue(2, labels=["Minor Change", "component:panel"], milestone="0.24.0"), set(), "2026-11-03", None)
        none = rh.classify(issue(3, labels=["component:panel"], milestone="0.24.0"), set(), "2026-11-03", None)
        page = rh.render([major, minor, none], [{"title": "0.24.0", "due": None}], "now")
        self.assertIn("[![#1 Major](https://img.shields.io/badge/%231-M-d73a4a)](u1)", page)
        self.assertIn("[![#2 Minor](https://img.shields.io/badge/%232-m-0969da)](u2)", page)
        self.assertIn("[![#3 (no change class)](https://img.shields.io/badge/%233-%3F-d0d7de)](u3)", page)
        self.assertNotIn("## Checks", page)

    def test_unknown_class_badge_shows_its_name(self):
        t = rh.classify(issue(5, effect="Spike"), set(), "2026-11-03", None)
        self.assertEqual(rh.badge(t), "[![#5 Spike](https://img.shields.io/badge/%235-Spike-57606a)](u5)")

    def test_shield_escapes_dashes_and_spaces(self):
        self.assertEqual(rh.shield("CR", "CR-Major", "8b0000"),
                         "https://img.shields.io/badge/CR-CR--Major-8b0000")
        self.assertEqual(rh.shield("NI", "New Interface", "8250df"),
                         "https://img.shields.io/badge/NI-New%20Interface-8250df")

    def test_page_is_only_the_heatmap(self):
        t = rh.classify(issue(1, labels=["Minor Change"], milestone="0.24.0"), set(), "2026-11-03", None)
        page = rh.render([t], [{"title": "0.24.0", "due": None}], "now", sections=SECTIONS)
        self.assertEqual([l for l in page.splitlines() if l.startswith("#")],
                         ["# Release heatmap", "## P1 – Critical", "## P3 – Low", "## Not yet prioritised"])

    def test_closed_milestone_is_flagged(self):
        t = rh.classify(issue(1, labels=["component:panel"], milestone="0.22.0"), set(), "2026-11-03", None)
        page = rh.render([t], [{"title": "0.24.0", "due": None}], "now")
        self.assertIn("| Component | ⚠️ 0.22.0 closed | Total |", page)

    def test_maintainer_takes_several_logins(self):
        a = rh.parse_args(["--maintainer", "alice", "bob", "--maintainer", "carol"])
        self.assertEqual(a.maintainer, ["alice", "bob", "carol"])

    def test_pr_states(self):
        def states(prs):
            return [(p["number"], p["state"]) for p in rh.pr_states(issue(prs=prs))]
        self.assertEqual(states([{"number": 5, "state": "OPEN", "isDraft": True},
                                 {"number": 7, "state": "OPEN", "reviewDecision": "APPROVED"},
                                 {"number": 6, "state": "MERGED"},
                                 {"number": 4, "state": "CLOSED"}]),
                         [(7, "approved"), (6, "merged"), (5, "draft")])
        self.assertEqual(states([{"number": 4, "state": "CLOSED"}]), [])
        self.assertEqual(states([{"number": 8, "state": "OPEN", "reviewDecision": "CHANGES_REQUESTED"}]),
                         [(8, "changes")])

    def test_open_prs_take_closing_and_referencing_prs(self):
        t = issue(prs=[{"number": 961, "state": "CLOSED"}, {"number": 970, "state": "MERGED"}],
                  ref_prs=[{"number": 962, "state": "OPEN"},
                           {"number": 963, "state": "OPEN", "isDraft": True},
                           {"number": 964, "state": "CLOSED"},
                           {"number": 965, "state": "OPEN",
                            "repository": {"isPrivate": False, "nameWithOwner": "other/repo"}}])
        t["timelineItems"]["nodes"].append({"source": {}})   # a cross-reference from an issue, not a PR
        self.assertEqual([(p["number"], p["state"]) for p in rh.open_prs(t)], [(963, "draft"), (962, "open")])

    def test_a_mention_is_not_a_reference(self):
        t = issue(783, ref_prs=[{"number": 1014, "state": "OPEN",
                                 "body": "Closes #1008\nas the AV components do in #792 (... (#783))."},
                                {"number": 1015, "state": "OPEN", "body": "Refs #7830"},
                                {"number": 1016, "state": "OPEN", "body": "Part of the work.\n\nRefs: #783"},
                                {"number": 1017, "state": "OPEN", "title": "Refs #783: metrics", "body": ""}])
        self.assertEqual([p["number"] for p in rh.open_prs(t)], [1017, 1016])

    def test_a_pr_both_closing_and_referencing_shows_once(self):
        t = issue(prs=[{"number": 962, "state": "OPEN"}], ref_prs=[{"number": 962, "state": "OPEN"}])
        self.assertEqual([p["number"] for p in rh.open_prs(t)], [962])

    def test_a_pr_closed_between_snapshots_is_not_open(self):
        for first, second in (("OPEN", "CLOSED"), ("CLOSED", "OPEN"), ("OPEN", "MERGED")):
            t = issue(prs=[{"number": 5, "state": first}], ref_prs=[{"number": 5, "state": second}])
            self.assertEqual(rh.open_prs(t), [], (first, second))

    def test_same_number_in_another_repo_is_a_different_pr(self):
        t = issue(prs=[{"number": 12, "state": "OPEN", "url": "https://github.com/a/x/pull/12"},
                       {"number": 12, "state": "OPEN", "url": "https://github.com/b/y/pull/12"}])
        self.assertEqual(len(rh.open_prs(t)), 2)

    def test_open_ticket_shows_only_open_prs(self):
        t = rh.classify(issue(1, labels=["component:panel"], milestone="0.24.0",
                              prs=[{"number": 8, "state": "CLOSED"}, {"number": 7, "state": "MERGED"}],
                              ref_prs=[{"number": 9, "state": "OPEN"}]), set(), "2026-11-03", None)
        page = rh.render([t], [{"title": "0.24.0", "due": None}], "now")
        self.assertIn("(p9)", page)
        self.assertNotIn("(p8)", page)
        self.assertNotIn("(p7)", page)
        self.assertNotIn("closed unmerged", page)

    def test_private_prs_are_left_out(self):
        prs = rh.pr_states(issue(prs=[{"number": 3, "state": "OPEN", "repository": {"isPrivate": True}},
                                      {"number": 4, "state": "OPEN", "repository": {"isPrivate": False}}]))
        self.assertEqual([p["number"] for p in prs], [4])

    def test_release_lookup_fails_loudly(self):
        import subprocess
        real = subprocess.run
        try:
            subprocess.run = lambda *a, **k: subprocess.CompletedProcess(a, 1, "", "gh: Not Found (HTTP 404)")
            self.assertIsNone(rh.fetch_last_release())
            subprocess.run = lambda *a, **k: subprocess.CompletedProcess(a, 1, "", "gh: HTTP 502")
            with self.assertRaises(RuntimeError):
                rh.fetch_last_release()
        finally:
            subprocess.run = real

    def test_gh_json_retries_a_transient_5xx(self):
        import subprocess
        real = subprocess.run
        replies = [subprocess.CompletedProcess([], 1, "", "gh: HTTP 504"),
                   subprocess.CompletedProcess([], 0, '{"data": 1}', "")]
        waits = []
        try:
            subprocess.run = lambda *a, **k: replies.pop(0)
            self.assertEqual(rh.gh_json(["api", "x"], sleep=waits.append), {"data": 1})
            self.assertEqual(waits, [1])
        finally:
            subprocess.run = real

    def test_gh_json_gives_up_on_a_lasting_or_other_error(self):
        import subprocess
        real = subprocess.run
        waits = []
        try:
            subprocess.run = lambda *a, **k: subprocess.CompletedProcess(a, 1, "", "gh: HTTP 503")
            with self.assertRaises(subprocess.CalledProcessError):
                rh.gh_json(["api", "x"], retries=3, sleep=waits.append)
            self.assertEqual(waits, [1, 2])
            waits.clear()
            subprocess.run = lambda *a, **k: subprocess.CompletedProcess(a, 1, "", "gh: Not Found (HTTP 404)")
            with self.assertRaises(subprocess.CalledProcessError):
                rh.gh_json(["api", "x"], sleep=waits.append)
            self.assertEqual(waits, [])
        finally:
            subprocess.run = real

    def test_cell_has_the_pr_under_the_ticket(self):
        t = rh.classify(issue(1, labels=["Minor Change", "component:panel"], milestone="0.24.0",
                              prs=[{"number": 9, "state": "OPEN"}]), set(), "2026-11-03", None)
        page = rh.render([t], [{"title": "0.24.0", "due": None}], "now")
        self.assertIn("(u1)<br>[![PR 9 open](https://img.shields.io/badge/%E2%86%B39-open-bf8700)](p9)", page)

    def test_resolved_shows_only_prs_merged_into_develop(self):
        t = rh.classify(issue(2, labels=["bug", "component:panel"], milestone="0.24.0",
                              prs=[{"number": 11, "state": "MERGED"},
                                   {"number": 12, "state": "MERGED", "baseRefName": "main"}]),
                        set(), "2026-11-03", None)
        release = {"tag": "0.23.0", "url": "r", "at": "2026-10-26T23:10:03Z"}
        section = rh.render([], [], "now", resolved=[t], release=release).split("## Resolved since 0.23.0")[1]
        self.assertIn("%E2%86%B311-merged", section)
        self.assertNotIn("%E2%86%B312", section)
        self.assertIn("| **Tickets** | | **1** |", section)

    def test_a_ticket_on_several_components_is_in_its_first_row(self):
        one = rh.classify(issue(1, labels=["component:panel"], milestone="0.24.0"), set(), "2026-11-03", None)
        two = rh.classify(issue(2, labels=["component:videosink", "component:audiosink"], milestone="0.24.0"),
                          set(), "2026-11-03", None)
        page = rh.render([one, two], [{"title": "0.24.0", "due": None}], "now", root=EMPTY)
        self.assertEqual(page.count("](u2)"), 1)
        self.assertIn("| audiosink | [", page)
        self.assertNotIn("| videosink |", page)
        self.assertNotIn("several components) |", page)
        totals = [int(l.rsplit("|", 2)[1]) for l in page.splitlines()
                  if l.startswith("| ") and not l.startswith(("| Component", "| ---", "| **"))]
        self.assertEqual(sum(totals), 2)

    def test_resolved_section_needs_a_release(self):
        self.assertNotIn("## Resolved", rh.render([], [], "now"))
        release = {"tag": "0.23.0", "url": "r", "at": "2026-10-26T23:10:03Z"}
        self.assertIn("Nothing yet.", rh.render([], [], "now", resolved=[], release=release))

    def test_ticket_with_a_pr_gets_its_own_line(self):
        self.assertEqual(rh.flow(["a", "b", "c", "d"], [False, True, False, False]), "a<br>b<br>c d")


EMPTY = tempfile.mkdtemp()   # a repo root with no metadata.yaml: rows carry no version
SECTIONS = [
    {"priority": "P1", "title": "P1 – Critical", "about": "Core.",
     "rows": [{"name": "DRM", "row": "drm"}, {"name": "Video Sink", "row": "videosink"}]},
    {"priority": "P3", "title": "P3 – Low", "about": "Later.",
     "rows": [{"name": "Panel", "row": "panel"}, {"name": "General documentation", "row": "(documentation)"}]},
]


class Priorities(unittest.TestCase):

    def test_reads_the_component_priority_list(self):
        secs = rh.read_priorities()
        self.assertEqual([s["priority"] for s in secs], ["P1", "P2", "P3"])
        rank = rh.rank_of(secs)
        self.assertEqual((rank["drm"], rank["avclock"], rank["hdmioutput"]), (1, 1, 1))
        self.assertEqual((rank["boot"], rank["vsi/abstractfilesystem"]), (2, 2))
        self.assertEqual((rank["panel"], rank["(documentation)"], rank["(infrastructure)"]), (3, 3, 3))
        self.assertTrue(all(s["about"] for s in secs))
        # The HAL architecture documentation row has no label, so it is no heatmap row.
        self.assertNotIn("HAL architecture documentation", [r["name"] for s in secs for r in s["rows"]])

    def test_every_component_is_listed_even_without_tickets(self):
        page = rh.render([], [], "now", sections=SECTIONS, components=["drm", "videosink", "ffv"], root=EMPTY)
        p1 = page.split("## P1")[1].split("## P3")[0]
        self.assertIn("| DRM |  | 0 |", p1)
        self.assertIn("| Video Sink |  | 0 |", p1)
        self.assertIn("| ffv |  | 0 |", page.split("## Not yet prioritised")[1])

    def test_a_ticket_goes_to_its_highest_priority_component(self):
        t = rh.classify(issue(4, labels=["component:panel", "component:videosink"], milestone="0.24.0"),
                        set(), "2026-11-03", None)
        page = rh.render([t], [{"title": "0.24.0", "due": None}], "now", sections=SECTIONS, root=EMPTY)
        self.assertIn("| Video Sink | [![#4", page)
        self.assertIn("| Panel | · | 0 |", page)

    def test_row_heading_has_the_component_version(self):
        root = tempfile.mkdtemp()
        for d, v in (("drm", "0.2.0.0"), ("bootreason", "0.2.1.0")):
            os.makedirs(os.path.join(root, d))
            with open(os.path.join(root, d, "metadata.yaml"), "w") as fh:
                fh.write("component: %s\nversion: %s\nstatus: GREEN\n" % (d, v))
        self.assertEqual(rh.row_heading("drm", "DRM", root), "DRM 0.2.0.0")
        self.assertEqual(rh.row_heading("boot", "Boot", root), "Boot 0.2.1.0")
        self.assertEqual(rh.row_heading("crypto", "Crypto", root), "Crypto")
        self.assertEqual(rh.row_heading("(documentation)", "General documentation", root), "General documentation")
        self.assertEqual(rh.all_components(root, ["component:crypto", "component:boot", "bug"]),
                         ["boot", "crypto", "drm"])

    def test_column_heading_has_the_due_date(self):
        t = rh.classify(issue(1, labels=["component:drm"], milestone="0.23.1"), set(), "2026-11-03", None)
        u = rh.classify(issue(2, labels=["component:drm"], milestone="0.24.0 - Next"), set(), "2026-11-03", None)
        page = rh.render([t, u], [{"title": "0.23.1", "due": "2026-11-28T08:00:00Z"},
                                  {"title": "0.24.0 - Next", "due": None}], "now", sections=SECTIONS, root=EMPTY)
        self.assertIn("| Component | 0.23.1<br>due 2026-11-28 | 0.24.0<br>no date | Total |", page)

    def test_wanted_priority(self):
        w = lambda labels, cur=None: rh.wanted_priority(labels, cur, SECTIONS)
        self.assertEqual(w(["component:panel", "component:drm"]), "P1")
        self.assertEqual(w(["component:panel"], "P1"), "P3")
        self.assertIsNone(w(["component:panel"], "P3"))          # already right
        self.assertIsNone(w(["component:drm"], "P0"))            # P0 is a hand-set override
        self.assertIsNone(w(["component:ffv"], "P2"))            # not yet prioritised
        self.assertEqual(w(["component:ffv", "component:panel"]), "P3")
        self.assertEqual(w(["documentation"]), "P3")             # repo-wide: filled in when empty
        self.assertIsNone(w(["documentation"], "P1"))            # ... but a hand-set value stays
        self.assertIsNone(w(["scope:overview", "documentation"]))  # the overview row is not prioritised

    def test_set_priorities_dry_run_changes_nothing(self):
        def node(n, labels, prio=None, state="OPEN", repo=rh.REPO):
            return {"id": "I%d" % n, "fieldValueByName": {"name": prio} if prio else None,
                    "content": {"number": n, "state": state, "repository": {"nameWithOwner": repo},
                                "labels": {"nodes": [{"name": l} for l in labels]}}}
        page = {"data": {"organization": {"projectV2": {
            "id": "P", "field": {"id": "F", "options": [{"id": "o1", "name": "P1 - High"},
                                                        {"id": "o3", "name": "P3 - Low"}]},
            "items": {"pageInfo": {"hasNextPage": False}, "nodes": [
                node(1, ["component:drm"], "P3 - Low"), node(2, ["component:drm"], "P1 - High"),
                node(3, ["component:drm"], state="CLOSED"), node(4, ["component:drm"], repo="other/x"),
                node(5, ["component:panel"])]}}}}}
        calls, real = [], rh.gh_json
        try:
            rh.gh_json = lambda args, **k: calls.append(args) or page
            out = io.StringIO()
            self.assertEqual(rh.set_priorities(True, SECTIONS, out), 2)
            self.assertEqual(len(calls), 1)
            self.assertIn("#1: P3 -> P1", out.getvalue())
            self.assertIn("#5: none -> P3", out.getvalue())
            calls.clear()
            rh.set_priorities(False, SECTIONS, io.StringIO())
            self.assertEqual([c[-1] for c in calls[1:]], ["o=o1", "o=o3"])
        finally:
            rh.gh_json = real


if __name__ == "__main__":
    unittest.main()

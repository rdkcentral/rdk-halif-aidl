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

"""Tests for the project sync's linked-issue rules: a PR's class wins over a
board edit on the issue it closes, and a cross-repo closing reference is left
to its own repository (#970).

Run: python3 -m unittest discover -s tests/scripts
"""
import importlib.util
import os
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
spec = importlib.util.spec_from_file_location(
    "pie", os.path.join(HERE, "..", "..", "scripts", "project_interface_effect.py"))
pie = importlib.util.module_from_spec(spec)
spec.loader.exec_module(pie)

HERE_REPO = "%s/%s" % (pie.REPO_OWNER, pie.REPO_NAME)


def pr(labels, *links):
    return {"labels": {"nodes": [{"name": l} for l in labels]},
            "closingIssuesReferences": {"nodes": [
                {"id": i, "repository": {"nameWithOwner": repo}} for i, repo in links]}}


class PrWins(unittest.TestCase):

    def test_board_edit_gives_way_to_the_pr(self):
        self.assertEqual(pie.pr_wins("Major", "board edit", "Minor"), ("Minor", "PR wins over a board edit"))

    def test_label_edit_is_left_alone(self):
        self.assertEqual(pie.pr_wins("Major", "label edit", "Minor"), ("Major", "label edit"))

    def test_no_pr_class_changes_nothing(self):
        self.assertEqual(pie.pr_wins("Major", "board edit", None), ("Major", "board edit"))


class Links(unittest.TestCase):

    def test_cross_repo_reference_is_skipped(self):
        t = pr([], ("I1", HERE_REPO), ("I2", "other/repo"))
        self.assertEqual([n["id"] for n in pie.same_repo_links(t)], ["I1"])

    def test_repository_names_match_without_case(self):
        t = pr([], ("I1", HERE_REPO.upper()))
        self.assertEqual([n["id"] for n in pie.same_repo_links(t)], ["I1"])

    def test_strongest_pr_class_per_issue(self):
        minor = next(o for o in pie.PRECEDENCE if "Minor Change" in pie.LABELS_OF[o])
        major = next(o for o in pie.PRECEDENCE if "Major Change" in pie.LABELS_OF[o])
        got = pie.pr_classes([pr(["Minor Change"], ("I1", HERE_REPO)),
                              pr(["Major Change"], ("I1", HERE_REPO), ("I9", "other/repo")),
                              pr([], ("I2", HERE_REPO))])
        self.assertEqual(got, {"I1": major})
        self.assertNotEqual(minor, major)



class OnlyThePrCarriesTheClass(unittest.TestCase):
    """#1053: an issue says Interface Change or documentation; the PR sets the class."""

    def setUp(self):
        self.calls = []
        self.saved = {n: getattr(pie, n) for n in
                      ("set_effect", "set_state", "apply_labels", "remove_owned_labels",
                       "moved_since_read", "mirror_milestone")}
        pie.set_effect = lambda proj, item, opt: self.calls.append(("field", opt))
        pie.set_state = lambda proj, item, val: self.calls.append(("state", val))
        pie.apply_labels = lambda *a: self.calls.append(("labels",)) or True
        pie.remove_owned_labels = lambda *a: self.calls.append(("labels",))
        pie.moved_since_read = lambda *a, **k: False
        pie.mirror_milestone = lambda *a: None

    def tearDown(self):
        for n, f in self.saved.items():
            setattr(pie, n, f)

    def issue(self, labels, field=None, synced=None):
        return {"id": "I1", "number": 7, "labels": {"nodes": [{"name": l} for l in labels]},
                "projectItems": {"nodes": [{"id": "PI", "project": {"number": pie.PROJECT_NUMBER},
                                            "effect": {"name": field} if field else None,
                                            "synced": {"text": synced} if synced else None}]}}

    def test_issue_field_takes_its_prs_class_and_no_label(self):
        report = []
        self.assertEqual(pie.sync_ticket(None, self.issue(["Interface Change"]), False, report, prefer="Major"),
                         "changed")
        self.assertEqual(self.calls, [("field", "Major"), ("state", "Major")])
        self.assertEqual(report, ["#7: field->Major (from its PRs)"])

    def test_issue_board_edit_writes_no_label(self):
        # Someone picked Minor on the board; with no PR it stands, and no label follows it.
        self.assertIsNone(pie.sync_ticket(None, self.issue([], field="Minor", synced=None), False, [], prefer=None))
        self.assertNotIn(("labels",), self.calls)

    def test_documentation_issue_reads_as_documentation(self):
        pie.sync_ticket(None, self.issue(["documentation"]), False, [], prefer=None)
        self.assertEqual(self.calls, [("field", "Documentation"), ("state", "Documentation")])

    def test_issue_with_nothing_is_left_alone(self):
        self.assertIsNone(pie.sync_ticket(None, self.issue(["Interface Change"]), False, [], prefer=None))
        self.assertEqual(self.calls, [])

    def test_pr_writes_no_label_to_its_issue_and_inherits_none(self):
        for labels in (["Major Change"], []):
            t = pr(labels, ("I1", HERE_REPO))
            t["number"] = 3
            self.assertEqual(pie.propagate_pr_to_issues(t, False, []), ["I1"])
            self.assertEqual([n["name"] for n in t["labels"]["nodes"]], labels)
        self.assertEqual(self.calls, [])


if __name__ == "__main__":
    unittest.main()

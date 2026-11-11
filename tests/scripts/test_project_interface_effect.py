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

    def test_strongest_pr_class_per_issue(self):
        minor = next(o for o in pie.PRECEDENCE if "Minor Change" in pie.LABELS_OF[o])
        major = next(o for o in pie.PRECEDENCE if "Major Change" in pie.LABELS_OF[o])
        got = pie.pr_classes([pr(["Minor Change"], ("I1", HERE_REPO)),
                              pr(["Major Change"], ("I1", HERE_REPO), ("I9", "other/repo")),
                              pr([], ("I2", HERE_REPO))])
        self.assertEqual(got, {"I1": major})
        self.assertNotEqual(minor, major)


if __name__ == "__main__":
    unittest.main()

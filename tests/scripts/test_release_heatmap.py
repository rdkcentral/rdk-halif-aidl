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
import os
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
spec = importlib.util.spec_from_file_location("release_heatmap",
                                              os.path.join(ROOT, "scripts", "release_heatmap.py"))
rh = importlib.util.module_from_spec(spec)
spec.loader.exec_module(rh)


def issue(number=1, labels=(), milestone=None, due=None, author="someone", priority=None,
          effect=None, blocking=0, people=1, refs=0):
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
        "timelineItems": {"totalCount": refs},
        "issueDependenciesSummary": {"blocking": blocking},
        "projectItems": {"nodes": [{"project": {"number": rh.PROJECT_NUMBER},
                                    "fieldValues": {"nodes": values}}]},
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

    def test_score(self):
        t = rh.classify(issue(labels=["Major Change"], milestone="0.24.0", due="2026-10-30T00:00:00Z",
                              priority="P0 - Critical", blocking=1, people=3, refs=6, author="ext"),
                        {"Ulrond"}, "2026-11-03", None)
        # P0 5 + blocks 3 + raised by other 2 + breaking 2 + overdue 2 + people 1 + refs 1
        self.assertEqual(t["score"], 16)
        self.assertEqual(t["tier"], "Do first")

    def test_next_due_scores_one(self):
        t = rh.classify(issue(milestone="0.25.0", due="2026-11-30T00:00:00Z"), set(), "2026-11-03", "2026-11-30")
        self.assertEqual(t["score"], 1)
        self.assertEqual(t["tier"], "Later")


class Render(unittest.TestCase):

    def test_cell_lists_tickets_major_in_bold(self):
        major = rh.classify(issue(1, labels=["Major Change", "component:panel"], milestone="0.24.0"), set(), "2026-11-03", None)
        minor = rh.classify(issue(2, labels=["Minor Change", "component:panel"], milestone="0.24.0"), set(), "2026-11-03", None)
        page = rh.render([major, minor], [{"title": "0.24.0", "due": None}], "now")
        self.assertIn("**[#1](u1)**", page)
        self.assertIn(" [#2](u2)", page)
        self.assertNotIn("## Checks", page)

    def test_change_class_rows(self):
        def t(n, labels):
            return rh.classify(issue(n, labels=labels, milestone="0.24.0"), set(), "2026-11-03", None)
        page = rh.render([t(1, ["Major Change"]), t(2, ["Minor Change"]), t(3, ["documentation"]),
                          t(4, ["New Interface"]), t(5, [])],
                         [{"title": "0.24.0", "due": None}], "now")
        section = page.split("## Change class")[1].split("## Milestones")[0]
        rows = [l.split(" | ")[0] for l in section.splitlines() if l.startswith("| ") and "---" not in l]
        self.assertEqual(rows, ["| Change class", "| Major", "| New Interface", "| Minor",
                                "| Documentation", "| (no change class)"])
        self.assertIn("| New Interface | 🟨 1<br>[#4](u4) | 1 |", section)

    def test_heat(self):
        self.assertEqual([rh.heat(n) for n in (0, 1, 3, 6)], ["·", "🟨", "🟧", "🟥"])


if __name__ == "__main__":
    unittest.main()

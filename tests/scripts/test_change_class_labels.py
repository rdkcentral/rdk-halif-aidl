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

"""Tests for how the change-class labels are read: New Interface is its own
class, below Major and above Minor (#973).

Run: python3 -m unittest discover -s tests/scripts
"""

import importlib.util
import os
import re
import subprocess
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


def _load(name):
    spec = importlib.util.spec_from_file_location(name, os.path.join(ROOT, "scripts", name + ".py"))
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


pie = _load("project_interface_effect")
pcc = _load("pr_change_class")


class ProjectInterfaceEffect(unittest.TestCase):

    def test_new_interface_alone_is_new_interface(self):
        self.assertEqual(pie.class_of(["New Interface"]), "New Interface")

    def test_new_interface_outranks_minor(self):
        self.assertEqual(pie.class_of(["New Interface", "Minor Change"]), "New Interface")

    def test_major_outranks_new_interface(self):
        self.assertEqual(pie.class_of(["New Interface", "Major Change"]), "Major")

    def test_cr_still_major(self):
        self.assertEqual(pie.class_of(["CR", "Major Change"]), "CR-Major")
        self.assertIn("Major Change", pie.WRITEBACK_LABELS["CR-Major"])

    def test_new_interface_writes_no_major(self):
        self.assertEqual(pie.WRITEBACK_LABELS["New Interface"], ["New Interface"])


class PrChangeClass(unittest.TestCase):

    def test_new_interface_is_explicit_minor(self):
        self.assertEqual(pcc.label_class("New Interface,enhancement"), ("minor", True))

    def test_major_wins_over_new_interface(self):
        self.assertEqual(pcc.label_class("New Interface,Major Change"), ("major", True))

    def test_no_class_label(self):
        self.assertEqual(pcc.label_class("enhancement"), ("minor", False))


if __name__ == "__main__":
    unittest.main()


class SyncVerb(unittest.TestCase):
    """release.sh sync-labels: when a PR's class label is raised, lowered or kept (#973)."""

    @staticmethod
    def verb(want, have, all_owned, labels):
        src = open(os.path.join(os.path.dirname(__file__), "..", "..", "scripts", "release.sh")).read()
        func = re.search(r"^_sync_verb\(\) \{.*?^\}", src, re.M | re.S).group(0)
        out = subprocess.run(["bash", "-c", func + '\n_sync_verb "$@"', "-", str(want), str(have), str(all_owned),
                              "\n".join(labels)], capture_output=True, text=True, check=True)
        return out.stdout.strip()

    def test_raise(self):
        self.assertEqual(self.verb(3, 2, 1, ["Minor Change"]), "raise")

    def test_lower_when_every_component_is_owned(self):
        self.assertEqual(self.verb(1, 2, 1, ["Minor Change"]), "lower")

    def test_keep_when_a_component_is_not_owned(self):
        self.assertEqual(self.verb(1, 2, 0, ["Minor Change"]), "keep")

    def test_new_interface_is_never_lowered(self):
        self.assertEqual(self.verb(1, 2, 1, ["New Interface"]), "keep")

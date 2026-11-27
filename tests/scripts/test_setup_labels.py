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

"""Tests for setup_labels.sh's delete_label: a legacy label still on a ticket,
or one whose use cannot be counted, is kept (#1020).

Run: python3 -m unittest discover -s tests/scripts
"""
import os
import re
import stat
import subprocess
import tempfile
import unittest

SCRIPT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "scripts", "setup_labels.sh")

# A stand-in for gh: answers the search with $USED (or fails when it is
# "fail"), and records any delete in $LOG.
FAKE_GH = """#!/bin/bash
if [ "$1" = api ]; then
    [ "$USED" = fail ] && exit 1
    echo "$USED"; exit 0
fi
if [ "$1 $2" = "label delete" ]; then echo "deleted $3" >> "$LOG"; exit 0; fi
exit 1
"""


class DeleteLabel(unittest.TestCase):

    def run_delete(self, used, dry_run="false"):
        func = re.search(r"^delete_label\(\) \{.*?^\}", open(SCRIPT).read(), re.M | re.S).group(0)
        with tempfile.TemporaryDirectory() as tmp:
            gh = os.path.join(tmp, "gh")
            with open(gh, "w") as f:
                f.write(FAKE_GH)
            os.chmod(gh, stat.S_IRWXU)
            log = os.path.join(tmp, "log")
            env = dict(os.environ, PATH=tmp + os.pathsep + os.environ["PATH"], USED=used, LOG=log)
            out = subprocess.run(["bash", "-c", "REPO=o/r; KEPT=0; DRY_RUN=%s\n%s\ndelete_label team:X\necho KEPT=$KEPT"
                                  % (dry_run, func)], env=env, capture_output=True, text=True, check=True)
            deleted = open(log).read() if os.path.exists(log) else ""
        return out.stdout + out.stderr, deleted

    def test_label_in_use_is_kept(self):
        out, deleted = self.run_delete("3")
        self.assertEqual(deleted, "")
        self.assertIn("still on 3 ticket(s)", out)
        self.assertIn("KEPT=1", out)

    def test_unused_label_is_deleted(self):
        out, deleted = self.run_delete("0")
        self.assertEqual(deleted, "deleted team:X\n")
        self.assertIn("KEPT=0", out)

    def test_count_failure_keeps_the_label(self):
        out, deleted = self.run_delete("fail")
        self.assertEqual(deleted, "")
        self.assertIn("could not count", out)

    def test_dry_run_deletes_nothing(self):
        out, deleted = self.run_delete("0", dry_run="true")
        self.assertEqual(deleted, "")
        self.assertIn("Would delete", out)


if __name__ == "__main__":
    unittest.main()

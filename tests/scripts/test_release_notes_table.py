#!/usr/bin/env python3
# Copyright 2026 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0
"""The release notes' Component bumps table (#1079): release.sh writes one row
per bumped component and reads a confirmation back from it, or from the bullet
list used up to 0.23.1."""

import os
import re
import subprocess
import tempfile
import unittest

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
RELEASE_SH = os.path.join(ROOT, "scripts", "release.sh")


def helpers():
    """The notes helpers from release.sh, without running the script itself."""
    text = open(RELEASE_SH).read()
    names = ["_version_bump", "_bump_class", "_notes_confirmed", "_notes_bump_row"]
    out = []
    for name in names:
        m = re.search(r"^%s\(\) \{.*?^\}\n" % re.escape(name), text, re.S | re.M)
        assert m, name
        out.append(m.group(0))
    return "\n".join(out)


def bash(script):
    return subprocess.run(["bash", "-c", helpers() + "\n" + script], capture_output=True,
                          text=True, check=True).stdout


REASON = "Flush and EOS behaviour defined (#890) | owed EOS (#955)"


class ReleaseNotesTable(unittest.TestCase):

    def test_rows(self):
        out = bash('_notes_bump_row audiodecoder 0.3.0.0 0.3.1.0 minor "%s"\n'
                   '_notes_bump_row audiomixer 0.4.0.0 0.4.1.0 "" ""\n'
                   '_notes_bump_row panel 0.2.0.0 0.2.0.1 "" ""\n'
                   '_notes_bump_row ringbuffer "" 0.1.0.0 "" ""' % REASON).splitlines()
        self.assertEqual(out, [
            "| `audiodecoder` | 0.3.0.0 | 0.3.1.0 | Minor (confirmed) | "
            "Flush and EOS behaviour defined (#890) \\| owed EOS (#955) |",
            "| `audiomixer` | 0.4.0.0 | 0.4.1.0 | Minor | The compiler's class |",
            "| `panel` | 0.2.0.0 | 0.2.0.1 | Bugfix | The compiler's class |",
            "| `ringbuffer` | — | 0.1.0.0 | New | First release |"])

    def test_a_confirmation_reads_back_from_the_table_and_the_old_list(self):
        with tempfile.TemporaryDirectory() as d:
            new, old = os.path.join(d, "new.md"), os.path.join(d, "old.md")
            rows = bash('_notes_bump_row audiodecoder 0.3.0.0 0.3.1.0 minor "%s"\n'
                        '_notes_bump_row audiomixer 0.4.0.0 0.4.1.0 "" ""' % REASON)
            open(new, "w").write("## Component bumps\n\n| Component | From | To | Class | Why |\n"
                                 "| --- | --- | --- | --- | --- |\n" + rows)
            open(old, "w").write("- `deepsleep` → 0.1.1.0 (confirmed minor: #892 adds reset-timer support)\n")
            self.assertEqual(bash('_notes_confirmed audiodecoder 0.3.1.0 "%s"' % new).strip(),
                             "confirmed minor: " + REASON)
            self.assertEqual(bash('_notes_confirmed audiomixer 0.4.1.0 "%s"' % new).strip(), "")
            self.assertEqual(bash('_notes_confirmed audiodecoder 0.3.0.1 "%s"' % new).strip(), "")
            self.assertEqual(bash('_notes_confirmed deepsleep 0.1.1.0 "%s"' % old).strip(),
                             "confirmed minor: #892 adds reset-timer support")

    def test_the_released_notes_still_parse(self):
        # 0.23.0's notes use the bullet list; its confirmations must still be found.
        notes = os.path.join(ROOT, "docs", "releases", "0.23.0.md")
        self.assertTrue(bash('_notes_confirmed hdmicec 0.2.0.0 "%s"' % notes).startswith("confirmed major: #837"))


if __name__ == "__main__":
    unittest.main()

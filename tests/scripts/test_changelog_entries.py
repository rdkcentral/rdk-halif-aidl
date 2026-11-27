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
"""CHANGELOG.md entries (#1082): release.sh lists each merged PR by its title,
skips other merges, and lists commits made directly on the branch."""

import os
import re
import subprocess
import tempfile
import unittest

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
RELEASE_SH = os.path.join(ROOT, "scripts", "release.sh")


def entries_function():
    m = re.search(r"^changelog_entries\(\) \{.*?^\}\n", open(RELEASE_SH).read(), re.S | re.M)
    assert m
    return m.group(0)


def git(repo, *args, msg=None):
    env = dict(os.environ, GIT_AUTHOR_NAME="t", GIT_AUTHOR_EMAIL="t@example.com",
               GIT_COMMITTER_NAME="t", GIT_COMMITTER_EMAIL="t@example.com")
    cmd = ["git", "-C", repo, "-c", "commit.gpgsign=false", "-c", "tag.gpgsign=false"] + list(args)
    if msg is not None:
        cmd += ["-m", msg]
    subprocess.run(cmd, check=True, capture_output=True, env=env)


class ChangelogEntries(unittest.TestCase):

    def test_merged_prs_are_listed_by_title(self):
        with tempfile.TemporaryDirectory() as repo:
            git(repo, "init", "-q", "-b", "develop")
            git(repo, "commit", "--allow-empty", "-q", msg="base")
            git(repo, "tag", "0.1.0")
            # A PR merged with a merge commit: subject names the PR, body's first line is its title.
            git(repo, "switch", "-q", "-c", "feature/7-thing")
            git(repo, "commit", "--allow-empty", "-q", msg="work on the thing")
            git(repo, "switch", "-q", "develop")
            # A long body (the squashed commit list GitHub writes) must not break the read under
            # pipefail: a reader that stops early makes git log die of SIGPIPE.
            body = "Add #7: The thing\n\n" + "\n".join("* commit %d of the squash" % i for i in range(20000))
            msg_file = os.path.join(repo, ".git", "MERGE_BODY")
            with open(msg_file, "w") as fh:
                fh.write("Merge pull request #12 from org/feature/7-thing\n\n" + body + "\n")
            git(repo, "merge", "--no-ff", "-q", "feature/7-thing", "-F", msg_file)
            # A branch merge that is not a PR is skipped.
            git(repo, "switch", "-q", "-c", "side")
            git(repo, "commit", "--allow-empty", "-q", msg="side work")
            git(repo, "switch", "-q", "develop")
            git(repo, "merge", "--no-ff", "-q", "side", msg="Merge branch 'side' into develop")
            # Commits made directly on develop: plain, and with a trailing PR number.
            git(repo, "commit", "--allow-empty", "-q", msg="Squashed commit of the following:")
            git(repo, "commit", "--allow-empty", "-q", msg="Merge #10: Sort imports (#9)")
            # release.sh runs under set -euo pipefail; so does the test.
            out = subprocess.run(["bash", "-c", "set -euo pipefail\n" + entries_function()
                                  + "\nchangelog_entries 0.1.0..HEAD org/repo"],
                                 env=dict(os.environ, REPO_ROOT=repo), capture_output=True, text=True,
                                 check=True).stdout.splitlines()
        self.assertEqual(out, [
            "- Merge #10: Sort imports (#9) [`#9`](https://github.com/org/repo/pull/9)",
            "- Squashed commit of the following:",
            "- Add #7: The thing [`#12`](https://github.com/org/repo/pull/12)",
        ])


if __name__ == "__main__":
    unittest.main()

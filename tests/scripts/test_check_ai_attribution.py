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

"""Tests for check_ai_attribution.sh: an AI tool footer in the PR description
or a co-author trailer naming the tool fails the check (#1031).

Run: python3 -m unittest discover -s tests/scripts
"""
import os
import subprocess
import tempfile
import unittest

SCRIPT = os.path.join(os.path.dirname(__file__), "..", "..", "scripts", "check_ai_attribution.sh")
FOOTER = "\U0001F916 Generated with [Claude Code](https://claude.com/claude-code)"
TRAILER = "Co-Authored-By: Claude <noreply@anthropic.com>"


def local_env(**extra):
    """The environment outside GitHub Actions, so errors go to stderr."""
    env = dict(os.environ, **extra)
    env.pop("GITHUB_ACTIONS", None)
    return env


class CheckAiAttribution(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.repo = self.tmp.name
        self.git("init", "-q", "-b", "develop")
        self.commit("Add base")
        self.git("branch", "base")

    def tearDown(self):
        self.tmp.cleanup()

    def git(self, *args):
        subprocess.run(["git", "-C", self.repo, "-c", "user.name=t", "-c",
                        "user.email=1+t@users.noreply.github.com", *args],
                       check=True, capture_output=True)

    def commit(self, message):
        self.git("commit", "-q", "--allow-empty", "-m", message)

    def run_check(self, body=None):
        args = ["bash", os.path.abspath(SCRIPT), "base..HEAD"]
        if body is not None:
            path = os.path.join(self.repo, "body.md")
            with open(path, "w") as f:
                f.write(body)
            args += ["--body-file", path]
        return subprocess.run(args, cwd=self.repo, capture_output=True, text=True, env=local_env())

    def test_clean_pr_passes(self):
        self.commit("Fix #1: Something\n\nCo-authored-by: Jo <2+jo@users.noreply.github.com>")
        result = self.run_check("Closes #1\n\nA clean description.")
        self.assertEqual(result.returncode, 0, result.stderr)

    def test_footer_in_description_fails(self):
        self.commit("Fix #1: Something")
        result = self.run_check("Closes #1\n\n" + FOOTER + "\n")
        self.assertEqual(result.returncode, 1)
        self.assertIn("PR description has an AI tool footer", result.stderr)

    def test_trailer_in_commit_fails(self):
        self.commit("Fix #1: Something\n\n" + TRAILER)
        result = self.run_check()
        self.assertEqual(result.returncode, 1)
        self.assertIn("co-author trailer", result.stderr)

    def test_trailer_with_any_case_and_name_fails(self):
        self.commit("Fix #1: Something\n\nco-authored-by: Claude Opus <noreply@anthropic.com>")
        self.assertEqual(self.run_check().returncode, 1)

    def test_mention_in_prose_passes(self):
        self.commit("Fix #1: Explain the Claude Code footer check")
        self.assertEqual(self.run_check("Mentions Claude in prose only.").returncode, 0)

    def test_unreadable_range_fails(self):
        result = subprocess.run(["bash", os.path.abspath(SCRIPT), "nosuch..HEAD"], cwd=self.repo,
                                capture_output=True, text=True, env=local_env())
        self.assertEqual(result.returncode, 2)
        self.assertIn("cannot read range", result.stderr)

    def test_missing_body_file_fails(self):
        result = subprocess.run(["bash", os.path.abspath(SCRIPT), "base..HEAD", "--body-file",
                                 os.path.join(self.repo, "missing.md")], cwd=self.repo,
                                capture_output=True, text=True, env=local_env())
        self.assertEqual(result.returncode, 2)

    def test_failed_github_read_fails(self):
        # A gh that always fails stands in for an API outage in --pr mode.
        bindir = os.path.join(self.repo, "bin")
        os.mkdir(bindir)
        with open(os.path.join(bindir, "gh"), "w") as f:
            f.write("#!/bin/sh\necho 'HTTP 502' >&2\nexit 1\n")
        os.chmod(os.path.join(bindir, "gh"), 0o755)
        env = local_env(PATH=bindir + os.pathsep + os.environ["PATH"])
        result = subprocess.run(["bash", os.path.abspath(SCRIPT), "--pr", "1"], cwd=self.repo,
                                capture_output=True, text=True, env=env)
        self.assertEqual(result.returncode, 2)
        self.assertNotIn("No AI tool attribution found", result.stdout)


if __name__ == "__main__":
    unittest.main()

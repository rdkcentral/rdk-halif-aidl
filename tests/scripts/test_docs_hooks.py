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

"""Tests for the docs build hook's link resolution (#1018).

Run: python3 -m unittest discover -s tests/scripts
"""
import importlib.util
import os
import sys
import tempfile
import types
import unittest

# The hook imports two mkdocs classes; stand-ins let it load without mkdocs installed.
for name in ("mkdocs", "mkdocs.structure", "mkdocs.structure.nav", "mkdocs.structure.pages"):
    sys.modules.setdefault(name, types.ModuleType(name))
sys.modules["mkdocs.structure.nav"].Section = type("Section", (), {})
sys.modules["mkdocs.structure.pages"].Page = type("Page", (), {})

HERE = os.path.dirname(os.path.abspath(__file__))
spec = importlib.util.spec_from_file_location("docs_hooks", os.path.join(HERE, "..", "..", "docs", "scripts", "docs_hooks.py"))
hooks = importlib.util.module_from_spec(spec)
spec.loader.exec_module(hooks)


class File:
    def __init__(self, src_uri, abs_src_path):
        self.src_uri, self.abs_src_path = src_uri, abs_src_path


class SourceLinks(unittest.TestCase):

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        root = self.root = os.path.realpath(self.tmp.name)
        for p in ("docs/architecture/hla.md", "docs/whitepapers/client.md", "scripts/release.sh",
                  "common/current/docs/common.md", "drm/0.1.0.0/docs/drm.md"):
            os.makedirs(os.path.dirname(os.path.join(root, p)), exist_ok=True)
            open(os.path.join(root, p), "w").close()
        hooks._repo_root, hooks._docs_dir, hooks._commit = root, "docs", "abc123"
        hooks._newest.clear()
        merged = os.path.join(root, "..", "merged")   # the monorepo plugin's copy of docs_dir
        self.files = [File("architecture/hla.md", os.path.join(merged, "architecture/hla.md")),
                      File("whitepapers/client.md", os.path.join(merged, "whitepapers/client.md")),
                      File("common/common.md", os.path.join(root, "common/current/docs/common.md")),
                      File("drm-0.1.0.0/drm.md", os.path.join(root, "drm/0.1.0.0/docs/drm.md"))]
        self.config = {"repo_url": "https://github.com/o/r"}

    def tearDown(self):
        self.tmp.cleanup()

    def render(self, uri, source, markdown):
        page = types.SimpleNamespace(file=File(uri, os.path.join(self.root, source)))
        return hooks._source_link(markdown, page, self.config, self.files)

    def test_repository_file_links_to_the_built_commit(self):
        out = self.render("architecture/hla.md", "docs/architecture/hla.md", "[r](../../scripts/release.sh)")
        self.assertEqual(out, "[r](https://github.com/o/r/blob/abc123/scripts/release.sh)")

    def test_page_read_from_the_merged_copy_resolves_from_the_repository(self):
        page = types.SimpleNamespace(file=File("architecture/hla.md", "/elsewhere/merged/architecture/hla.md"))
        out = hooks._source_link("[r](../../scripts/release.sh)", page, self.config, self.files)
        self.assertEqual(out, "[r](https://github.com/o/r/blob/abc123/scripts/release.sh)")

    def test_source_relative_page_link_goes_to_the_site_page(self):
        out = self.render("common/common.md", "common/current/docs/common.md",
                          "[w](../../../docs/whitepapers/client.md#use)")
        self.assertEqual(out, "[w](../whitepapers/client.md#use)")

    def test_link_that_already_resolves_is_untouched(self):
        md = "[w](../whitepapers/client.md)"
        self.assertEqual(self.render("common/common.md", "common/current/docs/common.md", md), md)

    def test_link_in_code_is_untouched(self):
        md = "Write `[r](../../scripts/release.sh)` like this.\n\n```\n[r](../../scripts/release.sh)\n```\n"
        self.assertEqual(self.render("architecture/hla.md", "docs/architecture/hla.md", md), md)

    def test_named_dead_link_keeps_its_text(self):
        out = self.render("drm-0.1.0.0/drm.md", "drm/0.1.0.0/docs/drm.md", "- [CDM](../cdm/cdm.md)")
        self.assertEqual(out, "- CDM")

    def test_unknown_dead_link_is_left_for_the_build_to_report(self):
        md = "[x](../nowhere.md)"
        self.assertEqual(self.render("architecture/hla.md", "docs/architecture/hla.md", md), md)


if __name__ == "__main__":
    unittest.main()

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

# MkDocs hooks, registered in mkdocs.yml. Both work in memory only; no file on
# disk is touched.
#
# Every build: a nav section that directly holds the single page of a component
# doc set becomes that page, under the section's title. A doc set is usually one
# page, so the nav reads "DRM > 0.1.0.0" rather than "DRM > 0.1.0.0 > DRM HAL".
#
# Release build only (mkdocs.release.yml, written by build_docs.sh): a release
# publishes each component only as its frozen snapshots, <component>-<X.Y.Z.W>/,
# so a link to a sibling component's current docs, ../<component>/page.md, has
# no target. Point it at that component's newest snapshot instead.

import glob
import os
import re

from mkdocs.structure.nav import Section
from mkdocs.structure.pages import Page

RELEASE_CONFIG = "mkdocs.release.yml"
VERSION_DIR = re.compile(r"^\d+\.\d+\.\d+\.\d+$")

# ](../<component>/  — a markdown link into a sibling component's current docs.
SIBLING_LINK = re.compile(r"(\]\(\.\./)([a-z0-9_]+)/")

_newest = {}
_doc_sets = set()


def _version_key(version):
    return tuple(int(part) for part in version.split("."))


def _site_name(mkdocs_yml):
    with open(mkdocs_yml, encoding="utf-8") as f:
        for line in f:
            if line.startswith("site_name:"):
                return line.split(":", 1)[1].strip()
    return None


def on_config(config):
    """Record the site_name of every component doc set and, for a release
    build, the newest snapshot of every component."""
    repo_root = os.path.dirname(os.path.abspath(config.config_file_path))
    _doc_sets.clear()
    for pattern in ("*/*/mkdocs.yml", "*/*/*/mkdocs.yml"):
        for mkdocs_yml in glob.glob(os.path.join(repo_root, pattern)):
            name = _site_name(mkdocs_yml)
            if name:
                _doc_sets.add(name)

    _newest.clear()
    if os.path.basename(config.config_file_path) != RELEASE_CONFIG:
        return config
    for component in os.listdir(repo_root):
        component_dir = os.path.join(repo_root, component)
        if not os.path.isdir(component_dir):
            continue
        versions = [
            entry for entry in os.listdir(component_dir)
            if VERSION_DIR.match(entry)
            and os.path.isfile(os.path.join(component_dir, entry, "mkdocs.yml"))
        ]
        if versions:
            _newest[component] = max(versions, key=_version_key)
    return config


def _collapse(items, parent):
    collapsed = []
    for item in items:
        if isinstance(item, Section):
            # Only a section that itself holds the page (a version, "Current",
            # or a single-set entry such as Broadcast) collapses; the component
            # section above it keeps its version entries.
            only = item.children[0] if len(item.children) == 1 else None
            item.children = _collapse(item.children, item)
            if isinstance(only, Page) and only.file.src_uri.split("/")[0] in _doc_sets:
                page = only
                page.title = item.title
                item = page
        item.parent = parent
        collapsed.append(item)
    return collapsed


def on_nav(nav, config, files):
    nav.items = _collapse(nav.items, None)
    return nav


def _rewrite(match):
    component = match.group(2)
    if component not in _newest:
        return match.group(0)
    return f"{match.group(1)}{component}-{_newest[component]}/"


def on_page_markdown(markdown, page, config, files):
    if not _newest:
        return markdown
    return SIBLING_LINK.sub(_rewrite, markdown)

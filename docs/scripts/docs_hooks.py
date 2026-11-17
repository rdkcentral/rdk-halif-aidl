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
#
# Every build: a relative link written against the page's source file (as
# GitHub shows it) rather than its place in the site has no target in the site
# (#1018). Resolve it against the source file instead: a page that is in the
# site gets a link to that page, and any other repository file (a script, a
# header, a recipe) a link to it on GitHub.

import glob
import os
import re

from mkdocs.structure.nav import Section
from mkdocs.structure.pages import Page

RELEASE_CONFIG = "mkdocs.release.yml"
VERSION_DIR = re.compile(r"^\d+\.\d+\.\d+\.\d+$")

# ](../<component>/  — a markdown link into a sibling component's current docs.
SIBLING_LINK = re.compile(r"(\]\(\.\./)([a-z0-9_]+)/")

# ](target) or ](target#anchor) — a relative link, not a URL or an anchor alone.
RELATIVE_LINK = re.compile(r"\]\((?!https?:|mailto:|#|/)([^)\s#]+)(#[^)\s]*)?\)")

# Links in released snapshots whose target exists nowhere; a snapshot is frozen,
# so the text stays and the link goes. drm 0.1.0.0 named a CDM page that was
# never written (drm 0.2.0.0 dropped the link).
NO_TARGET = {("drm/0.1.0.0/docs/drm.md", "../cdm/cdm.md")}

_newest = {}
_doc_sets = set()
_repo_root = None
_docs_dir = "docs"   # docs_dir as mkdocs.yml writes it; the monorepo plugin moves the live one to /tmp


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
    global _repo_root, _docs_dir
    repo_root = os.path.dirname(os.path.abspath(config.config_file_path))
    _repo_root = repo_root
    with open(config.config_file_path, encoding="utf-8") as f:
        for line in f:
            if line.startswith("docs_dir:"):
                _docs_dir = line.split(":", 1)[1].split("#", 1)[0].strip() or "docs"
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


def _source_link(markdown, page, config, files):
    """Repoint links that only resolve against the page's source file."""
    in_site = {f.src_uri for f in files}
    # Site pages by their path in the repository. The monorepo plugin serves
    # docs_dir pages from a merged copy outside the repository, so such a
    # page's repository path is <docs_dir>/<uri>.
    by_path = {}
    for f in files:
        real = os.path.realpath(f.abs_src_path or "")
        if _repo_root and real.startswith(_repo_root + os.sep):
            by_path[os.path.relpath(real, _repo_root)] = f.src_uri
        else:
            by_path.setdefault(os.path.normpath(os.path.join(_docs_dir, f.src_uri)), f.src_uri)
    src = os.path.realpath(page.file.abs_src_path or "")
    src_rel = os.path.relpath(src, _repo_root) if _repo_root else ""
    here = os.path.dirname(page.file.src_uri)
    repo_url = (config.get("repo_url") or "").rstrip("/")

    def fix(match):
        target, anchor = match.group(1), match.group(2) or ""
        if os.path.normpath(os.path.join(here, target)) in in_site:
            return match.group(0)   # already a link mkdocs resolves
        if (src_rel, target) in NO_TARGET:
            return None
        on_disk = os.path.realpath(os.path.join(os.path.dirname(src), target))
        repo_rel = os.path.relpath(on_disk, _repo_root) if _repo_root else ""
        parts = repo_rel.split(os.sep)
        if repo_rel not in by_path and len(parts) > 2 and parts[1] == "current" and parts[0] in _newest:
            # A release publishes a component only as its snapshots: use the newest.
            repo_rel = os.sep.join([parts[0], _newest[parts[0]]] + parts[2:])
        if repo_rel in by_path:
            return "](%s%s)" % (os.path.relpath(by_path[repo_rel], here or "."), anchor)
        if _repo_root and on_disk.startswith(_repo_root + os.sep) and os.path.exists(on_disk) and repo_url:
            return "](%s/blob/develop/%s%s)" % (repo_url, os.path.relpath(on_disk, _repo_root), anchor)
        return match.group(0)

    out, pos = [], 0
    for m in RELATIVE_LINK.finditer(markdown):
        new = fix(m)
        if new is None:   # NO_TARGET: keep the link text, drop the link
            start = markdown.rfind("[", pos, m.start())
            out.append(markdown[pos:start] + markdown[start + 1:m.start()])
        else:
            out.append(markdown[pos:m.start()] + new)
        pos = m.end()
    out.append(markdown[pos:])
    return "".join(out)


def on_page_markdown(markdown, page, config, files):
    markdown = _source_link(markdown, page, config, files)
    if not _newest:
        return markdown
    return SIBLING_LINK.sub(_rewrite, markdown)

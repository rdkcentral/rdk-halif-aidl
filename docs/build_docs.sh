#!/usr/bin/env bash

#/**
# * Copyright 2025 RDK Management
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

# ----------------------------------------------------------------------------
# Resolve paths from the script's own location, so the script works no matter
# what directory it is invoked from (e.g. ./docs/build_docs.sh or ./build_docs.sh).
# ----------------------------------------------------------------------------
SCRIPT_DIR="$(cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")" && pwd)"   # the docs/ directory
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"                                # repo root (holds mkdocs.yml)
VENV_DIR="${SCRIPT_DIR}/python_venv"
MKDOCS="${VENV_DIR}/bin/mkdocs"
MIKE="${VENV_DIR}/bin/mike"

# Put the venv on PATH for the rest of the script. Invoking mkdocs and mike by
# absolute path is not sufficient: mike spawns mkdocs as a *named* subprocess,
# so with the venv absent from PATH `mike deploy` dies with
#   error: [Errno 2] No such file or directory: 'mkdocs'
# VIRTUAL_ENV is exported alongside it so the child sees a fully-formed venv.
export VIRTUAL_ENV="${VENV_DIR}"
export PATH="${VENV_DIR}/bin:${PATH}"

cd "${REPO_ROOT}" || { echo "[ERROR] cannot cd to repo root ${REPO_ROOT}"; exit 1; }

# ----------------------------------------------------------------------------
# Function to enhance echo
# ----------------------------------------------------------------------------
function ECHO()
{
    echo -e "$*"
}

# ----------------------------------------------------------------------------
# clone_repo <url> <dir> <ref> : Check out <ref> (a tag or commit) of <url> in
# <dir>, cloning it first if needed. Every build of the site uses the same
# external content until <ref> is changed here.
#
# An existing clone on another commit is moved to <ref>; --force discards the
# link rewrite below, which is applied again after the checkout.
# ----------------------------------------------------------------------------
function clone_repo
{
  local repo_url="$1" target_dir="$2" ref="$3"

  if [ ! -d "${target_dir}/.git" ]; then
    echo "[INFO] Cloning ${repo_url} to ${target_dir}"
    rm -rf "${target_dir}"
    git clone --quiet "${repo_url}" "${target_dir}" \
      || { echo "[ERROR] git clone ${repo_url} failed"; exit 1; }
  fi

  if [ "$(git -C "${target_dir}" rev-parse HEAD)" != \
       "$(git -C "${target_dir}" rev-parse --verify --quiet "${ref}^{commit}")" ]; then
    git -C "${target_dir}" fetch --quiet --tags origin \
      || { echo "[ERROR] git fetch in ${target_dir} failed"; exit 1; }
    git -C "${target_dir}" checkout --quiet --force --detach "${ref}" \
      || { echo "[ERROR] ${repo_url} has no ref ${ref}"; exit 1; }
    echo "[INFO] ${target_dir} at ${ref}"
  fi
}

# ----------------------------------------------------------------------------
# External content, pinned. The ut-core wiki has no tags, so it is pinned to a
# commit; when it is tagged, pin the tag instead.
# ----------------------------------------------------------------------------
UT_CORE_WIKI_REF="a6005396be3b476808209cb2b073ffb68d8d64a0"

clone_repo "https://github.com/rdkcentral/ut-core.wiki.git" "docs/external_content/ut-core-wiki" "${UT_CORE_WIKI_REF}"
#clone_repo "https://github.com/rdkcentral/L4-vendor_system_tests/wiki" "docs/external_content/L4-vendor_system_tests-wiki"
#clone_repo "https://github.com/rdkcentral/another-repo.git" "docs/external_content/another-repo"  # Example
#... add more repo clones like this...

# A GitHub wiki resolves a link such as ](/rdkcentral/ut-core/wiki/Page) against
# github.com; on this site it resolves against the docs host and 404s. Make
# every such link absolute. Safe to repeat: rewritten links no longer match.
while IFS= read -r wiki_md; do
  # -i.bak + rm: the in-place form GNU and BSD sed both accept.
  sed -i.bak 's#](/rdkcentral/#](https://github.com/rdkcentral/#g' "${wiki_md}" && rm -f "${wiki_md}.bak"
done < <(grep -rlF '](/rdkcentral/' docs/external_content --include='*.md' 2>/dev/null)

# ----------------------------------------------------------------------------
# usage() : Print the help/usage text.
# ----------------------------------------------------------------------------
function usage() 
{
  cat <<EOF
Usage: $0 [COMMAND] [OPTIONS]

Commands:
  serve        Serve the site locally (mkdocs serve), with the Current docs.
  build        Build the site into the "site" directory (mkdocs build), with
               the Current docs.
  release      Release the site as [version] (default: the newest X.Y.Z tag),
               built from the checkout, without the Current docs: the
               published versions plus this one as the default. Locally it
               is served at http://localhost:8000; nothing is pushed.
  set-default  Mark a deployed version as the default.
  delete       Delete a deployed version.
  help         Show this help message.

Options:
  --release    serve/build only: leave out the Current docs, as release does.
  --publish    release only: push the result to GitHub Pages and wait for
               it to go live.
  -h, --help   Show this help message.

Examples:
  $0 serve          Serve your MkDocs site on localhost:8000
  $0 serve --release  Serve it as a release publishes it (no Current docs)
  $0 build          Build your MkDocs site into the 'site' directory
  $0 set-default    <version> - Set the default version of the deployed docs
  $0 delete         <version> - Delete a version of your MK Docs
  $0 release        Release the newest tag locally, as it will be published
  $0 release 0.22.0 --publish  Publish 0.22.0 to GitHub Pages as the default
  $0 help           Show this help message
EOF
}

# ----------------------------------------------------------------------------
# list_subsite_mkdocs() : Print every component mkdocs.yml the top-level nav
# can include (<component>/current/, <component>/<X.Y.Z.W>/, vsi/<name>/...),
# one absolute path per line, sorted. The root mkdocs.yml is excluded.
#
# Portable across GNU and BSD find: the version filter is a grep -E pass, not
# find -regextype, which BSD find does not support.
# ----------------------------------------------------------------------------
function list_subsite_mkdocs()
{
  find "${REPO_ROOT}" -maxdepth 4 \
       \( -name .git -o -name out -o -name site -o -name build -o -name external_content -o -name python_venv \) -prune \
       -o -name mkdocs.yml ! -path "${REPO_ROOT}/mkdocs.yml" -print \
    | sort
}

# ----------------------------------------------------------------------------
# list_snapshot_mkdocs() : Print the subset of list_subsite_mkdocs() that are
# frozen snapshots (<component>/<X.Y.Z.W>/mkdocs.yml).
# ----------------------------------------------------------------------------
function list_snapshot_mkdocs()
{
  list_subsite_mkdocs | grep -E '/[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+/mkdocs\.yml$'
}

# ----------------------------------------------------------------------------
# normalize_snapshot_site_names() : Ensure every snapshot mkdocs.yml carries a
# unique site_name.
#
# create_snapshot() copies <component>/current/mkdocs.yml verbatim, so a fresh
# snapshot inherits the bare component site_name. Once the top-level nav
# registers current/ and the snapshot together, the mkdocs-monorepo plugin
# rejects the duplicate names and the build aborts. Rewrite each
# <component>/<X.Y.Z.W>/mkdocs.yml to "site_name: <component>-<version>";
# current/ keeps the bare component name. Runs before every command that
# builds the site, so the publish flow needs no manual site-name pass.
# ----------------------------------------------------------------------------
function normalize_snapshot_site_names()
{
  local fixed=0
  local snapshot_yml comp_dir version component expected current_name

  while IFS= read -r snapshot_yml; do
    comp_dir="$(dirname "$(dirname "${snapshot_yml}")")"
    component="$(basename "${comp_dir}")"
    version="$(basename "$(dirname "${snapshot_yml}")")"
    expected="${component}-${version}"
    current_name="$(sed -n 's/^site_name:[[:space:]]*//p' "${snapshot_yml}" | head -1)"
    if [ "${current_name}" != "${expected}" ]; then
      # -i.bak + rm: the in-place form GNU and BSD sed both accept.
      sed -i.bak "s/^site_name:.*/site_name: ${expected}/" "${snapshot_yml}" && rm -f "${snapshot_yml}.bak"
      echo "[INFO]   normalized ${snapshot_yml#"${REPO_ROOT}"/}: site_name '${current_name}' -> '${expected}'"
      fixed=$((fixed + 1))
    fi
  done < <(list_snapshot_mkdocs)

  if [ ${fixed} -gt 0 ]; then
    echo "[INFO] normalized ${fixed} snapshot site_name(s) — commit the corrected mkdocs.yml file(s)."
  fi
}

# ----------------------------------------------------------------------------
# check_nav_coverage() : Report every component doc set and every release
# notes page that has no entry in the top-level mkdocs.yml nav.
#
# The mkdocs-monorepo plugin builds only the doc sets the nav includes, so a
# snapshot with no nav entry is absent from the site without any warning.
# Prints one line per missing entry and returns 1 if any are missing.
# ----------------------------------------------------------------------------
function check_nav_coverage()
{
  local nav="${REPO_ROOT}/mkdocs.yml"
  local missing=0
  local subsite_yml notes rel

  while IFS= read -r subsite_yml; do
    rel="${subsite_yml#"${REPO_ROOT}"/}"
    if ! grep -qF "'!include ${rel}'" "${nav}"; then
      echo "[ERROR]   no nav entry for ${rel}"
      missing=$((missing + 1))
    fi
  done < <(list_subsite_mkdocs)

  for notes in "${SCRIPT_DIR}"/releases/*.md; do
    [ -e "${notes}" ] || continue
    rel="releases/$(basename "${notes}")"
    if ! grep -qE "^[[:space:]]*-[[:space:]]+[^:]+:[[:space:]]+${rel//./\\.}[[:space:]]*$" "${nav}"; then
      echo "[ERROR]   no Release Notes nav entry for docs/${rel}"
      missing=$((missing + 1))
    fi
  done

  if [ ${missing} -gt 0 ]; then
    echo "[ERROR] ${missing} doc set(s) missing from the mkdocs.yml nav — add them before building."
    return 1
  fi
  return 0
}

# ----------------------------------------------------------------------------
# write_release_config() : Write mkdocs.release.yml, the mkdocs.yml nav without
# its "Current" entries.
#
# current/ is the working copy for the next release, so a published release
# lists only frozen snapshots. Entries with no snapshot (Broadcast, the VSI
# pages) are not labelled "Current" and stay. The file sits beside mkdocs.yml
# so its !include paths resolve, and is removed when the script exits.
# ----------------------------------------------------------------------------
RELEASE_CONFIG="mkdocs.release.yml"

# Commands run when the script exits, in order.
CLEANUP=()
function on_exit() { local c; for c in "${CLEANUP[@]}"; do eval "${c}"; done; }
trap on_exit EXIT

function write_release_config()
{
  grep -vE "^[[:space:]]*-[[:space:]]+Current:[[:space:]]" "${REPO_ROOT}/mkdocs.yml" \
    > "${REPO_ROOT}/${RELEASE_CONFIG}"
  CLEANUP+=("rm -f '${REPO_ROOT}/${RELEASE_CONFIG}'")
}

# ----------------------------------------------------------------------------
# Releasing the site. `release` and `release --publish` run the same steps on
# a copy of origin/gh-pages; only --publish pushes it.
# ----------------------------------------------------------------------------
PAGES_BRANCH="gh-pages"
LOCAL_PAGES_BRANCH="docs-release-local"
# The site's path on its host, from site_url: /rdk-halif-aidl/
SITE_PATH="$(sed -nE 's#^site_url:[[:space:]]*https?://[^/]+##p' "${REPO_ROOT}/mkdocs.yml" | head -1)"

# resolve_version [version] : Print the version to release: the one given, or
# the newest X.Y.Z tag reachable from HEAD. Warns when the checkout is not that
# tag, because the site is built from the checkout.
function resolve_version()
{
  local version="$1"
  if [ -z "${version}" ]; then
    version="$(git -C "${REPO_ROOT}" describe --tags --abbrev=0 --match '[0-9]*.[0-9]*.[0-9]*' 2>/dev/null)"
    [ -n "${version}" ] || { echo "[ERROR] no X.Y.Z release tag is reachable from HEAD; give the version." >&2; exit 1; }
  fi
  if ! git -C "${REPO_ROOT}" rev-parse --quiet --verify "refs/tags/${version}" >/dev/null; then
    echo "[WARNING] there is no tag ${version}; the checkout is released as ${version}." >&2
  elif [ "$(git -C "${REPO_ROOT}" rev-parse "${version}^{commit}")" != "$(git -C "${REPO_ROOT}" rev-parse HEAD)" ]; then
    echo "[WARNING] HEAD is not tag ${version}; the checkout ($(git -C "${REPO_ROOT}" rev-parse --short HEAD)) is released as ${version}." >&2
  fi
  echo "${version}"
}

# release_site <branch> <version> : Make <branch> origin/gh-pages plus
# <version> built from the checkout, as the default version, with a root that
# holds only mike's files and the no-version 404 redirect (#831).
function release_site()
{
  local branch="$1" version="$2" tree

  echo "[INFO] Starting from origin/${PAGES_BRANCH}..."
  git -C "${REPO_ROOT}" fetch --quiet origin "${PAGES_BRANCH}" \
    || { echo "[ERROR] git fetch origin ${PAGES_BRANCH} failed"; exit 1; }
  git -C "${REPO_ROOT}" branch --quiet --force "${branch}" FETCH_HEAD \
    || { echo "[ERROR] cannot reset branch ${branch} to origin/${PAGES_BRANCH}"; exit 1; }

  write_release_config
  echo "[INFO] mike deploy ${version}"
  "${MIKE}" deploy --ignore-remote-status -F "${RELEASE_CONFIG}" -b "${branch}" "${version}" \
    || { echo "[ERROR] mike deploy ${version} failed"; exit 1; }
  echo "[INFO] mike set-default ${version}"
  "${MIKE}" set-default --ignore-remote-status -F "${RELEASE_CONFIG}" -b "${branch}" "${version}" \
    || { echo "[ERROR] mike set-default ${version} failed"; exit 1; }

  echo "[INFO] Removing unversioned pages and writing the no-version redirect..."
  tree="$(mktemp -d)"
  git -C "${REPO_ROOT}" worktree add --quiet "${tree}" "${branch}" \
    || { echo "[ERROR] cannot check out ${branch}"; exit 1; }
  "${VENV_DIR}/bin/python" "${SCRIPT_DIR}/scripts/tidy_pages.py" "${tree}" "${SITE_PATH}" "${version}" \
    || { git -C "${REPO_ROOT}" worktree remove --force "${tree}"; echo "[ERROR] tidy_pages.py failed"; exit 1; }
  git -C "${tree}" add --all
  if ! git -C "${tree}" diff --cached --quiet; then
    git -C "${tree}" commit --quiet -m "Root holds only versioned docs; a path with no version opens ${version}" \
      || { git -C "${REPO_ROOT}" worktree remove --force "${tree}"; echo "[ERROR] commit to ${branch} failed"; exit 1; }
  fi
  git -C "${REPO_ROOT}" worktree remove --force "${tree}"
}

# wait_for_pages <commit> : Wait for the GitHub Pages build of <commit> on
# gh-pages to succeed. Fails after 10 minutes.
function wait_for_pages()
{
  local commit="$1" repo_slug attempt run_status status conclusion run_id
  repo_slug="$(git -C "${REPO_ROOT}" config --get remote.origin.url \
                | sed -E 's|.*github.com[:/](.*/.+).git$|\1|; s|.*github.com[:/](.*/.+)$|\1|')"
  for attempt in $(seq 1 60); do
    run_status="$(gh run list --repo "${repo_slug}" --workflow pages-build-deployment --branch "${PAGES_BRANCH}" \
        --commit "${commit}" --limit 1 --json status,conclusion,databaseId \
        --jq '.[0] | "\(.status):\(.conclusion):\(.databaseId)"' 2>/dev/null || true)"
    IFS=':' read -r status conclusion run_id <<<"${run_status}"
    if [ "${status}" = "completed" ]; then
      [ "${conclusion}" = "success" ] && { echo "[INFO]   GitHub Pages build ${run_id} succeeded."; return 0; }
      echo "[ERROR]   GitHub Pages build ${run_id} ended '${conclusion}'."
      return 1
    fi
    echo "[INFO]   ${attempt}/60: GitHub Pages build ${status:-not started}, waiting..."
    sleep 10
  done
  echo "[ERROR] GitHub Pages did not publish ${commit} within 10 minutes."
  return 1
}

# ----------------------------------------------------------------------------
# main() : Main entry point. Handle command-line arguments, then run commands.
# ----------------------------------------------------------------------------
function main() 
{
  local CMD=$1
  shift || true  # Shift off the first argument to allow further options

  case "${CMD}" in
    serve|build|release)
      normalize_snapshot_site_names
      ;;
  esac

  # A gap in the nav fails every command that publishes or builds the site;
  # serve only warns, so a nav edit in progress can still be previewed.
  case "${CMD}" in
    build|release)
      check_nav_coverage || exit 1
      ;;
    serve)
      check_nav_coverage || echo "[WARNING] serving with an incomplete nav."
      ;;
  esac

  # serve and build include the "Current" docs unless --release is given;
  # release never includes them.
  local CONFIG="mkdocs.yml"
  if [ "${CMD}" != "release" ] && [ "${1:-}" = "--release" ]; then
    shift
    write_release_config
    CONFIG="${RELEASE_CONFIG}"
  fi

  case "${CMD}" in
    serve)
      echo "[INFO] Serving MkDocs locally (${CONFIG})..."
      "${MKDOCS}" serve -f "${CONFIG}" -a 0.0.0.0:8000 "$@"
      ;;

    build)
      echo "[INFO] Building MkDocs site (${CONFIG})..."
      "${MKDOCS}" build -f "${CONFIG}"
      ;;

    set-default)
      echo "[INFO] Deploying MkDocs site to gh-pages..."
      # Check if the second argument (the version) is provided
      # "$#" is the number of positional parameters
      # If "$2" is empty, it means no version was provided after "deploy"
      VERSION_TO_DEPLOY="$1"      
      echo VERSION:[$VERSION_TO_DEPLOY] @:{$@}
      if [ -z "$VERSION_TO_DEPLOY" ]; then
          echo "[ERROR] Missing version argument for 'set-default'. Usage: $0 set-default <version> [alias...]"
          exit 1 # Exit with an error code
      fi
      # Extract the version from the arguments
      "${MIKE}" set-default ${VERSION_TO_DEPLOY} --push
      ;;

    delete)
      echo "[INFO] Delelting <$1> in gh-pages..."
      # Check if the second argument (the version) is provided
      # "$#" is the number of positional parameters
      # If "$2" is empty, it means no version was provided after "deploy"
      VERSION_TO_DEPLOY="$1"
      echo VERSION:[$VERSION_TO_DEPLOY] @:{$@}
      if [ -z "$VERSION_TO_DEPLOY" ]; then
          echo "[ERROR] Missing version argument for 'delete'. Usage: $0 delete <version> [alias...]"
          exit 1 # Exit with an error code
      fi
      # Extract the version from the arguments
      "${MIKE}" delete ${VERSION_TO_DEPLOY} --push
      ;;

    release)
      local version="" publish=0 arg tree commit
      for arg in "$@"; do
        case "${arg}" in
          --publish) publish=1 ;;
          *) version="${arg}" ;;
        esac
      done
      version="$(resolve_version "${version}")" || exit 1

      if [ "${publish}" -eq 0 ]; then
        echo "[INFO] Releasing ${version} locally (nothing is pushed)"
        release_site "${LOCAL_PAGES_BRANCH}" "${version}"
        tree="$(mktemp -d)"
        CLEANUP+=("rm -rf '${tree}'" "git -C '${REPO_ROOT}' branch --quiet -D '${LOCAL_PAGES_BRANCH}'")
        git -C "${REPO_ROOT}" archive "${LOCAL_PAGES_BRANCH}" | tar -x -C "${tree}"
        "${VENV_DIR}/bin/python" "${SCRIPT_DIR}/scripts/serve_pages.py" "${tree}" "${SITE_PATH}" 8000
        exit 0
      fi

      command -v gh >/dev/null 2>&1 \
        || { echo "[ERROR] release --publish needs 'gh' (GitHub CLI) to wait for the GitHub Pages build."; exit 1; }
      echo "[INFO] Releasing ${version} to GitHub Pages"
      release_site "${PAGES_BRANCH}" "${version}"
      commit="$(git -C "${REPO_ROOT}" rev-parse "${PAGES_BRANCH}")"
      echo "[INFO] Pushing ${PAGES_BRANCH} (${commit:0:12})..."
      git -C "${REPO_ROOT}" push --quiet origin "${PAGES_BRANCH}" \
        || { echo "[ERROR] git push origin ${PAGES_BRANCH} failed"; exit 1; }
      wait_for_pages "${commit}" || exit 1
      echo "[INFO] ✓ ${version} published as the default version."
      ;;

    help|-h|--h|--help|"")
      # If user typed 'help', '-h', '--help', or gave no args -> show usage
      usage
      ;;

    *)
      echo "[ERROR] Unknown command: '${CMD}'"
      usage
      exit 1
      ;;
  esac
}

# ----------------------------------------------------------------------------
# Set up the Python virtual environment (idempotent).
# The venv's binaries are invoked by absolute path, so no activation /
# PATH manipulation is needed and there is no PEP 668 system-pip conflict.
# ----------------------------------------------------------------------------
if [ ! -x "${VENV_DIR}/bin/python" ]; then
  echo "[INFO] Creating Python virtual environment: ${VENV_DIR}"
  python3 -m venv "${VENV_DIR}" || { echo "[ERROR] failed to create venv"; exit 1; }
fi

echo "[INFO] Installing documentation requirements..."
# pip is pinned like every package in requirements.txt, so each run installs
# the same toolchain.
PIP_VERSION="26.2.1"
"${VENV_DIR}/bin/pip" install --quiet "pip==${PIP_VERSION}" || { echo "[ERROR] pip install pip==${PIP_VERSION} failed"; exit 1; }
"${VENV_DIR}/bin/pip" install --quiet -r "${SCRIPT_DIR}/requirements.txt" || { echo "[ERROR] pip install failed"; exit 1; }

# ----------------------------------------------------------------------------
# Run main() with all script arguments.
# ----------------------------------------------------------------------------
main "$@"

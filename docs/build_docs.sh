#!/usr/bin/env bash
#** *****************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2025 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# *
# http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
#* ******************************************************************************

# ----------------------------------------------------------------------------
# Resolve paths from the script's own location, so the script works no matter
# what directory it is invoked from (e.g. ./docs/build_docs.sh or ./build_docs.sh).
# ----------------------------------------------------------------------------
SCRIPT_DIR="$(cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")" && pwd)"   # the docs/ directory
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"                                # repo root (holds mkdocs.yml)
VENV_DIR="${SCRIPT_DIR}/python_venv"
MKDOCS="${VENV_DIR}/bin/mkdocs"
MIKE="${VENV_DIR}/bin/mike"

cd "${REPO_ROOT}" || { echo "[ERROR] cannot cd to repo root ${REPO_ROOT}"; exit 1; }

# ----------------------------------------------------------------------------
# Function to enhance echo
# ----------------------------------------------------------------------------
function ECHO()
{
    echo -e "$*"
}

# ----------------------------------------------------------------------------
# Function to clone a repository if it doesn't have a.done file
# ----------------------------------------------------------------------------
function clone_repo
{
  repo_url="$1"
  target_dir="$2"
  done_file="$target_dir/.done"

  # Check if directory exists (using -d)
  if [ ! -d "$target_dir" ]; then
    mkdir -p "$target_dir"
  fi

  # Check if.done file exists (using -f)
  if [ ! -f "$done_file" ]; then
    echo "Cloning $repo_url to $target_dir"
    git clone "$repo_url" "$target_dir"
    touch "$done_file"  # Create.done file
  else
    echo "$target_dir already cloned. Skipping."
  fi
}

# ----------------------------------------------------------------------------
# Clone repositories (call the function directly)
# ----------------------------------------------------------------------------
clone_repo "https://github.com/rdkcentral/ut-core.wiki.git" "docs/external_content/ut-core-wiki"
#clone_repo "https://github.com/rdkcentral/L4-vendor_system_tests/wiki" "docs/external_content/L4-vendor_system_tests-wiki"
#clone_repo "https://github.com/rdkcentral/another-repo.git" "docs/external_content/another-repo"  # Example
#... add more repo clones like this...

# ----------------------------------------------------------------------------
# usage() : Print the help/usage text.
# ----------------------------------------------------------------------------
function usage() 
{
  cat <<EOF
Usage: $0 [COMMAND] [OPTIONS]

Commands:
  serve        Serve the site locally (mkdocs serve).
  build        Build the site into the "site" directory (mkdocs build).
  deploy       Deploy the site to the "gh-pages" branch (mkdocs gh-deploy).
  set-default  Mark a deployed version as the default.
  delete       Delete a deployed version.
  release      One-shot version release: deploy <version>, wait for the
               GitHub Pages publish to finish, then set <version> as
               default. Use this from automation so the caller doesn't
               have to coordinate the GH Pages publish delay.
  help         Show this help message.

Options:
  -h, --help   Show this help message.

Examples:
  $0 serve          Serve your MkDocs site on localhost:8000
  $0 build          Build your MkDocs site into the 'site' directory
  $0 deploy         <version> - Deploy your MkDocs site to GitHub Pages
  $0 set-default    <version> - Set the default version of the deployed docs
  $0 delete         <version> - Delete a version of your MK Docs
  $0 release        <version> - Deploy + wait for GitHub Pages publish + set-default
  $0 help           Show this help message
EOF
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
      sed -i "s/^site_name:.*/site_name: ${expected}/" "${snapshot_yml}"
      echo "[INFO]   normalized ${snapshot_yml#"${REPO_ROOT}"/}: site_name '${current_name}' -> '${expected}'"
      fixed=$((fixed + 1))
    fi
  done < <(find "${REPO_ROOT}" -maxdepth 4 \
             \( -name out -o -name site -o -name build -o -name external_content -o -name python_venv \) -prune \
             -o -regextype posix-extended \
             -regex '.*/[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+/mkdocs\.yml' -print)

  if [ ${fixed} -gt 0 ]; then
    echo "[INFO] normalized ${fixed} snapshot site_name(s) — commit the corrected mkdocs.yml file(s)."
  fi
}

# ----------------------------------------------------------------------------
# main() : Main entry point. Handle command-line arguments, then run commands.
# ----------------------------------------------------------------------------
function main() 
{
  local CMD=$1
  shift || true  # Shift off the first argument to allow further options

  case "${CMD}" in
    serve|build|deploy|release)
      normalize_snapshot_site_names
      ;;
  esac

  case "${CMD}" in
    serve)
      echo "[INFO] Serving MkDocs locally..."
      "${MKDOCS}" serve -a 0.0.0.0:8000 "$@"
      ;;

    build)
      echo "[INFO] Building MkDocs site..."
      "${MKDOCS}" build
      ;;

    deploy)
      echo "[INFO] Deploying MkDocs site to gh-pages..."
      # Check if the second argument (the version) is provided
      # "$#" is the number of positional parameters
      # If "$2" is empty, it means no version was provided after "deploy"
      VERSION_TO_DEPLOY="$1"      
      echo VERSION:[$VERSION_TO_DEPLOY] @:{$@}
      if [ -z "$VERSION_TO_DEPLOY" ]; then
          echo "[ERROR] Missing version argument for 'deploy'. Usage: $0 deploy <version> [alias...]"
          exit 1 # Exit with an error code
      fi
      # Extract the version from the arguments
      "${MIKE}" deploy "${VERSION_TO_DEPLOY}" --push
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
      # One-shot docs release: mike deploy --push, wait for the
      # GitHub Pages build to publish, then mike set-default --push.
      #
      # Why the wait: `mike set-default` updates the `versions.json`
      # consumed by the served docs site. If we run it immediately
      # after `mike deploy`, the served site may still be on the
      # previous gh-pages commit and the version-switcher won't show
      # <version> until GH Pages re-publishes. Running set-default
      # while Pages is mid-build can also leave the live site
      # transiently inconsistent. So we gate set-default on the
      # `pages-build-deployment` workflow run that GH triggers when
      # `mike deploy` pushes to gh-pages.
      #
      # No external coordination: the caller invokes
      #   ./docs/build_docs.sh release <version>
      # and gets back exit 0 only when the full deploy+publish+
      # set-default cycle is done.
      VERSION_TO_RELEASE="$1"
      if [ -z "${VERSION_TO_RELEASE}" ]; then
          echo "[ERROR] Missing version argument for 'release'. Usage: $0 release <version>"
          exit 1
      fi
      if ! command -v gh >/dev/null 2>&1; then
          echo "[ERROR] release requires 'gh' (GitHub CLI) to poll the pages-build-deployment workflow."
          exit 1
      fi
      # Resolve <owner>/<repo> from the origin remote so we don't
      # hard-code rdkcentral/rdk-halif-aidl here.
      REPO_SLUG="$(git -C "${REPO_ROOT}" config --get remote.origin.url \
                    | sed -E 's|.*github.com[:/](.*/.+).git$|\1|; s|.*github.com[:/](.*/.+)$|\1|')"
      if [ -z "${REPO_SLUG}" ]; then
          echo "[ERROR] could not resolve <owner>/<repo> from origin remote."
          exit 1
      fi
      echo "[INFO] release ${VERSION_TO_RELEASE} (repo: ${REPO_SLUG})"

      echo "[INFO] step 1/3 — mike deploy ${VERSION_TO_RELEASE} --push"
      "${MIKE}" deploy "${VERSION_TO_RELEASE}" --push \
          || { echo "[ERROR] mike deploy failed"; exit 1; }

      echo "[INFO] step 2/3 — waiting for GitHub Pages to publish gh-pages..."
      # Poll the latest pages-build-deployment workflow run until it
      # reaches a terminal state. Bound the wait so we don't hang
      # forever if GH Pages is degraded — at 10s poll interval over
      # 10 min (60 attempts) that's the practical worst case before
      # we give up and ask the operator to retry set-default later.
      PAGES_WORKFLOW="pages-build-deployment"
      MAX_ATTEMPTS=60
      attempt=0
      pages_ok=0
      while [ ${attempt} -lt ${MAX_ATTEMPTS} ]; do
          attempt=$((attempt + 1))
          # databaseId is the numeric run id; we look at the most
          # recent run of the pages-build-deployment workflow on the
          # gh-pages branch.
          run_status="$(gh run list \
              --repo "${REPO_SLUG}" \
              --workflow "${PAGES_WORKFLOW}" \
              --branch gh-pages \
              --limit 1 \
              --json status,conclusion,databaseId \
              --jq '.[0] | "\(.status):\(.conclusion):\(.databaseId)"' 2>/dev/null || true)"
          if [ -z "${run_status}" ]; then
              echo "[INFO]   attempt ${attempt}/${MAX_ATTEMPTS}: no pages-build-deployment runs visible yet, waiting..."
              sleep 10
              continue
          fi
          IFS=':' read -r status conclusion run_id <<<"${run_status}"
          if [ "${status}" = "completed" ]; then
              if [ "${conclusion}" = "success" ]; then
                  echo "[INFO]   pages-build-deployment run ${run_id} succeeded."
                  pages_ok=1
                  break
              else
                  echo "[ERROR]   pages-build-deployment run ${run_id} ended with conclusion '${conclusion}'."
                  exit 1
              fi
          fi
          echo "[INFO]   attempt ${attempt}/${MAX_ATTEMPTS}: pages-build-deployment status=${status}, waiting..."
          sleep 10
      done
      if [ "${pages_ok}" -ne 1 ]; then
          echo "[ERROR] GitHub Pages did not publish within $((MAX_ATTEMPTS * 10))s. Re-run later:"
          echo "         ./docs/build_docs.sh set-default ${VERSION_TO_RELEASE}"
          exit 1
      fi

      echo "[INFO] step 3/3 — mike set-default ${VERSION_TO_RELEASE} --push"
      "${MIKE}" set-default "${VERSION_TO_RELEASE}" --push \
          || { echo "[ERROR] mike set-default failed"; exit 1; }

      echo "[INFO] ✓ release ${VERSION_TO_RELEASE} complete: deployed, published, set as default."
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
"${VENV_DIR}/bin/pip" install --quiet --upgrade pip || { echo "[ERROR] pip upgrade failed"; exit 1; }
"${VENV_DIR}/bin/pip" install --quiet -r "${SCRIPT_DIR}/requirements.txt" || { echo "[ERROR] pip install failed"; exit 1; }

# ----------------------------------------------------------------------------
# Run main() with all script arguments.
# ----------------------------------------------------------------------------
main "$@"

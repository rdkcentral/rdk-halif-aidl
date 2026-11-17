#!/usr/bin/env bash
#** *****************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
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
#** ******************************************************************************
#
# check_ai_attribution.sh — fail when a PR carries an AI tool's attribution
# (#1031): a "Generated with Claude Code" footer, or a co-author trailer
# naming Claude or an anthropic.com address. A tool is not an author, and a
# merge copies commit messages onto develop.
#
# Usage:
#   scripts/check_ai_attribution.sh [<range>] [--body-file <file>]
#       Checks every commit message in <range> (default origin/develop..HEAD)
#       and, if given, the PR description saved in <file>.
#   scripts/check_ai_attribution.sh --pr <number>
#       Reads the PR's description and commit messages from GitHub (gh).

set -euo pipefail

REPO="${REPO:-rdkcentral/rdk-halif-aidl}"
FOOTER='Generated with \[?Claude'
TRAILER='^[[:space:]]*Co-authored-by:.*(Claude|anthropic\.com)'

range="origin/develop..HEAD"
body_file=""
pr=""
while [[ $# -gt 0 ]]; do
    case "$1" in
        --body-file) body_file="$2"; shift 2 ;;
        --pr) pr="$2"; shift 2 ;;
        *) range="$1"; shift ;;
    esac
done

report() {
    if [[ -n "${GITHUB_ACTIONS:-}" ]]; then
        echo "::error title=AI attribution::$1"
    else
        echo "ERROR: $1" >&2
    fi
}

failures=0

# check <where> <text>
check() {
    local line
    while IFS= read -r line; do
        if grep -qiE "${FOOTER}" <<< "${line}"; then
            report "$1 has an AI tool footer: ${line}"
            failures=$((failures + 1))
        elif grep -qiE "${TRAILER}" <<< "${line}"; then
            report "$1 has an AI tool co-author trailer: ${line}"
            failures=$((failures + 1))
        fi
    done <<< "$2"
}

if [[ -n "${pr}" ]]; then
    check "PR #${pr} description" "$(gh pr view "${pr}" --repo "${REPO}" --json body --jq .body)"
    while IFS=$'\t' read -r oid; do
        [[ -n "${oid}" ]] || continue
        check "commit ${oid:0:8}" "$(gh api "repos/${REPO}/commits/${oid}" --jq .commit.message)"
    done < <(gh pr view "${pr}" --repo "${REPO}" --json commits --jq '.commits[].oid')
else
    [[ -z "${body_file}" ]] || check "PR description" "$(cat "${body_file}")"
    for sha in $(git rev-list "${range}"); do
        check "commit ${sha:0:8}" "$(git log -1 --format=%B "${sha}")"
    done
fi

if (( failures > 0 )); then
    cat >&2 <<'EOF'

Remove the AI tool's footer from the PR description, and its co-author
trailer from the commit messages (interactive rebase 'reword', then push
with --force-with-lease). Configure the tool not to add them.
EOF
    exit 1
fi

echo "No AI tool attribution found."

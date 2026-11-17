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
# with an anthropic.com address or a Claude product or model name. A tool
# is not an author, and a merge copies commit messages onto develop.
#
# Usage:
#   scripts/check_ai_attribution.sh [<range>] [--body-file <file>]
#       Checks every commit message in <range> (default origin/develop..HEAD)
#       and, if given, the PR description saved in <file>.
#   scripts/check_ai_attribution.sh --pr <number>
#       Reads the PR's description and commit messages from GitHub (gh).
#   scripts/check_ai_attribution.sh --message-file <file>
#       Checks one commit message before the commit is made: the pre-commit
#       commit-msg hook in .pre-commit-config.yaml. Git's "#" comment lines
#       are ignored.
#
# Exit: 0 clean, 1 attribution found, 2 an input could not be read.

set -euo pipefail

REPO="${REPO:-rdkcentral/rdk-halif-aidl}"
# The footer as the tool writes it: a line of its own, optionally after an
# emoji. The words quoted inside other prose are not the footer.
FOOTER='^[^[:alnum:]]*Generated with \[?Claude Code\]?(\([^)]*\))?[[:space:]]*$'
# The tool's identities only: its anthropic.com address, or its product and
# model names. A person called Claude is a co-author like any other.
TRAILER='^[[:space:]]*Co-authored-by:(.*@anthropic\.com|[[:space:]]*Claude[[:space:]]+(Code|Opus|Sonnet|Haiku|Fable)([[:space:]]|<|$))'

range="origin/develop..HEAD"
body_file=""
message_file=""
pr=""
while [[ $# -gt 0 ]]; do
    case "$1" in
        --body-file) body_file="$2"; shift 2 ;;
        --pr) pr="$2"; shift 2 ;;
        --message-file) message_file="$2"; shift 2 ;;
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

# Every read is a checked assignment: input that cannot be read is a failure,
# never clean content.
cannot_read() {
    report "cannot read $1"
    exit 2
}

if [[ -n "${message_file}" ]]; then
    message="$(grep -v '^#' "${message_file}")" || [[ -r "${message_file}" ]] \
        || cannot_read "${message_file}"
    check "commit message" "${message}"
elif [[ -n "${pr}" ]]; then
    body="$(gh pr view "${pr}" --repo "${REPO}" --json body --jq .body)" \
        || cannot_read "PR #${pr} description"
    check "PR #${pr} description" "${body}"
    oids="$(gh pr view "${pr}" --repo "${REPO}" --json commits --jq '.commits[].oid')" \
        || cannot_read "PR #${pr} commit list"
    for oid in ${oids}; do
        message="$(gh api "repos/${REPO}/commits/${oid}" --jq .commit.message)" \
            || cannot_read "commit ${oid:0:8}"
        check "commit ${oid:0:8}" "${message}"
    done
else
    if [[ -n "${body_file}" ]]; then
        body="$(cat "${body_file}")" || cannot_read "${body_file}"
        check "PR description" "${body}"
    fi
    revs="$(git rev-list "${range}")" || cannot_read "range ${range}"
    for sha in ${revs}; do
        message="$(git log -1 --format=%B "${sha}")" || cannot_read "commit ${sha:0:8}"
        check "commit ${sha:0:8}" "${message}"
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

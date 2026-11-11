#!/usr/bin/env bash

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

# merge_pr.sh — merge a pull request with its project Interface Effect in step.
#
# The project sync (scripts/project_interface_effect.py) needs a token with
# `project` scope, which a workflow does not have here, so it runs at merge,
# under the caller's own gh login (#970):
#
#   1. check   - the labels and the Interface Effect options still agree
#   2. sync    - the PR's field from its labels, and its linked issues from it
#   3. merge   - gh pr merge, with the options given (default --merge
#                --delete-branch)
#   4. sync    - again, so the issues and milestones carry the merged result
#
# Usage:
#   scripts/merge_pr.sh <PR_NUMBER> [--dry-run] [gh pr merge options...]
#   e.g. scripts/merge_pr.sh 974 --admin
#
# --dry-run reports what the sync would change and does not merge.
# Exits 3 when the merge is deferred (--auto, merge queue): the final sync is
# then left to be run once the PR has merged.

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
REPO="rdkcentral/rdk-halif-aidl"
SYNC="${REPO_ROOT}/scripts/project_interface_effect.py"

PR="${1:-}"
if ! [[ "$PR" =~ ^[0-9]+$ ]]; then
    echo "Usage: $0 <PR_NUMBER> [--dry-run] [gh pr merge options...]" >&2
    exit 1
fi
shift

DRY_RUN=false
MERGE_ARGS=()
for a in "$@"; do
    if [ "$a" = "--dry-run" ]; then DRY_RUN=true; else MERGE_ARGS+=("$a"); fi
done
[ ${#MERGE_ARGS[@]} -eq 0 ] && MERGE_ARGS=(--merge --delete-branch)

export GH_TOKEN="${GH_TOKEN:-$(gh auth token)}"
export GITHUB_REPOSITORY="$REPO"

sync() {
    local args=(sync-item --number "$PR")
    $DRY_RUN && args+=(--dry-run)
    python3 "$SYNC" "${args[@]}"
}

state=$(gh pr view "$PR" --repo "$REPO" --json state --jq .state)
if [ "$state" != "OPEN" ]; then
    echo "PR #${PR} is ${state}, not open" >&2
    exit 1
fi

echo "==> Labels and Interface Effect options"
python3 "$SYNC" check

echo "==> Interface Effect before merge"
sync

if $DRY_RUN; then
    echo "Dry run: not merging #${PR}."
    exit 0
fi

echo "==> Merging #${PR} (${MERGE_ARGS[*]})"
gh pr merge "$PR" --repo "$REPO" "${MERGE_ARGS[@]}"

# --auto or a merge queue can return before the PR is merged; the final sync
# must see the merged PR, so it is not run early.
state=$(gh pr view "$PR" --repo "$REPO" --json state --jq .state)
if [ "$state" != "MERGED" ]; then
    echo "#${PR} is ${state}, not merged yet (auto-merge or merge queue)." >&2
    echo "Once it merges, run: GH_TOKEN=\"\${GH_TOKEN:-\$(gh auth token)}\" GITHUB_REPOSITORY=${REPO} python3 scripts/project_interface_effect.py sync-item --number ${PR}" >&2
    exit 3
fi

echo "==> Interface Effect after merge"
sync

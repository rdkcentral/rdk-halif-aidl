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
# check_commit_emails.sh — fail when a commit in a range is authored or
# committed with anything other than a GitHub noreply address (#898).
#
# Permitted:
#   <id>+<login>@users.noreply.github.com   a contributor's public GitHub ID
#   noreply@github.com                      commits made in the GitHub web UI
#
# Usage: scripts/check_commit_emails.sh [<range>]
#   <range>  git revision range, default origin/develop..HEAD

set -euo pipefail

range="${1:-origin/develop..HEAD}"

permitted() {
    local email="${1,,}"
    [[ "${email}" == *@users.noreply.github.com || "${email}" == noreply@github.com ]]
}

failures=0
while IFS=$'\t' read -r sha author_email committer_email subject; do
    for role in author committer; do
        if [[ "${role}" == author ]]; then email="${author_email}"; else email="${committer_email}"; fi
        permitted "${email}" && continue
        failures=$((failures + 1))
        msg="${sha:0:8} ${role} <${email}> is not a GitHub noreply address: ${subject}"
        if [[ -n "${GITHUB_ACTIONS:-}" ]]; then
            echo "::error title=Commit email::${msg}"
        else
            echo "ERROR: ${msg}" >&2
        fi
    done
done < <(git log --format='%H%x09%ae%x09%ce%x09%s' "${range}")

if (( failures > 0 )); then
    cat >&2 <<'EOF'

Commits must use your GitHub noreply address, shown under
GitHub > Settings > Emails. Set it and rewrite the commits.
On a branch that carries only your own commits:

  git config user.email <id>+<login>@users.noreply.github.com
  git rebase -x 'git commit --amend --no-edit --reset-author' origin/develop
  git push --force-with-lease
EOF
    exit 1
fi

echo "All commits in ${range} use GitHub noreply addresses."

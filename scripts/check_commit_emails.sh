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
# check_commit_emails.sh — check the email addresses in a range of commits
# (#898). A squash merge copies every commit message onto develop, so the
# message trailers are checked as well as the author and committer.
#
#   error    author or committer is not a GitHub noreply address
#   error    a trailer (Co-authored-by:, Signed-off-by:, ...) carries an
#            email that is not a GitHub noreply address
#   warning  any Co-authored-by: trailer
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

# report <error|warning> <title> <message>
report() {
    if [[ -n "${GITHUB_ACTIONS:-}" ]]; then
        echo "::$1 title=$2::$3"
    else
        echo "${1^^}: $3" >&2
    fi
}

identity_failures=0
trailer_failures=0
warnings=0

for sha in $(git rev-list "${range}"); do
    IFS=$'\t' read -r author_email committer_email subject \
        < <(git log -1 --format='%ae%x09%ce%x09%s' "${sha}")

    for role in author committer; do
        if [[ "${role}" == author ]]; then email="${author_email}"; else email="${committer_email}"; fi
        permitted "${email}" && continue
        identity_failures=$((identity_failures + 1))
        report error "Commit email" \
            "${sha:0:8} ${role} <${email}> is not a GitHub noreply address: ${subject}"
    done

    declare -A seen=()
    while IFS= read -r line; do
        [[ "${line}" =~ ^[[:space:]]*([A-Za-z-]+):.*\<([^\>]+@[^\>]+)\> ]] || continue
        key="${BASH_REMATCH[1]}"
        email="${BASH_REMATCH[2]}"
        [[ -n "${seen[${key,,} ${email,,}]:-}" ]] && continue
        seen["${key,,} ${email,,}"]=1
        if ! permitted "${email}"; then
            trailer_failures=$((trailer_failures + 1))
            report error "Commit message email" \
                "${sha:0:8} '${key}: <${email}>' is not a GitHub noreply address: ${subject}"
        elif [[ "${key,,}" == co-authored-by ]]; then
            warnings=$((warnings + 1))
            report warning "Co-authored-by" \
                "${sha:0:8} has a Co-authored-by trailer for <${email}>: ${subject}"
        fi
    done < <(git log -1 --format=%B "${sha}")
done

if (( identity_failures > 0 )); then
    cat >&2 <<'EOF'

Commits must use your GitHub noreply address, shown under
GitHub > Settings > Emails. Set it and rewrite the commits.
On a branch that carries only your own commits:

  git config user.email <id>+<login>@users.noreply.github.com
  git rebase -x 'git commit --amend --no-edit --reset-author' origin/develop
  git push --force-with-lease
EOF
fi

if (( trailer_failures > 0 )); then
    cat >&2 <<'EOF'

Commit messages must not carry email addresses other than GitHub noreply
addresses: a squash merge copies them onto develop. Remove the trailer
with an interactive rebase ('reword'), then push with --force-with-lease.
Tools that add trailers automatically (such as an AI assistant's
Co-Authored-By line) must be configured not to.
EOF
fi

if (( identity_failures + trailer_failures > 0 )); then
    exit 1
fi

echo "All commits in ${range} use GitHub noreply addresses (${warnings} Co-authored-by warning(s))."

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
#   error    the range or a commit cannot be read
#   error    an address on a trailer line (Co-authored-by:, Signed-off-by:,
#            Cc:, ...) is not a GitHub noreply address - who is it?
#   error    a trailer's noreply address names an account that does not exist
#   warning  a co-author that is a GitHub bot account, not a person
#   warning  any other co-author, to be confirmed by the reviewer
#
# Accounts are looked up through the GitHub API when GH_TOKEN is set;
# without it, or if the API fails, nonexistent accounts are not detected and
# every GitHub co-author gets the plain warning.
#
# Permitted:
#   <id>+<login>@users.noreply.github.com   a contributor's public GitHub ID
#   <login>@users.noreply.github.com        the same, for pre-2017 accounts
#   noreply@github.com                      commits made in the GitHub web UI
#
# Usage: scripts/check_commit_emails.sh [<range>]
#   <range>  git revision range, default origin/develop..HEAD

set -euo pipefail

range="${1:-origin/develop..HEAD}"

permitted() {
    local email="${1,,}"
    [[ "${email}" =~ ^[^@[:space:]]+@users\.noreply\.github\.com$ || "${email}" == noreply@github.com ]]
}

# Prints the GitHub account type (User, Bot, ...) of a noreply address,
# "Missing" when GitHub says the account does not exist, or nothing when it
# cannot be looked up (no GH_TOKEN, no gh, API failure).
account_type() {
    local local_part="${1%%@*}" endpoint out
    [[ -n "${GH_TOKEN:-}" ]] && command -v gh >/dev/null || return 0
    # <id>+<login>: look up by id, as some bots (Copilot) have no users/<login>.
    if [[ "${local_part}" =~ ^([0-9]+)\+ ]]; then
        endpoint="user/${BASH_REMATCH[1]}"
    else
        endpoint="users/${local_part}"
    fi
    if out="$(gh api "${endpoint}" --jq .type 2>&1)"; then
        echo "${out}"
    elif [[ "${out}" == *"HTTP 404"* ]]; then
        echo Missing
    fi
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

# Checked assignments: a range or commit git cannot read fails the check.
revs="$(git rev-list "${range}")"

for sha in ${revs}; do
    info="$(git log -1 --format='%ae%x09%ce%x09%s' "${sha}")"
    message="$(git log -1 --format=%B "${sha}")"
    IFS=$'\t' read -r author_email committer_email subject <<< "${info}"

    for role in author committer; do
        if [[ "${role}" == author ]]; then email="${author_email}"; else email="${committer_email}"; fi
        permitted "${email}" && continue
        identity_failures=$((identity_failures + 1))
        report error "Commit email" \
            "${sha:0:8} ${role} <${email}> is not a GitHub noreply address: ${subject}"
    done

    # Every address on a "Key: value" line is checked, bare or in <...>,
    # however many the line carries.
    declare -A seen=()
    while IFS= read -r line; do
        [[ "${line}" =~ ^[[:space:]]*([A-Za-z-]+):[[:space:]]*(.*@.*)$ ]] || continue
        key="${BASH_REMATCH[1]}"
        value="${BASH_REMATCH[2]}"
        while IFS= read -r email; do
            [[ -n "${seen[${key,,} ${email,,}]:-}" ]] && continue
            seen["${key,,} ${email,,}"]=1
            if ! permitted "${email}"; then
                trailer_failures=$((trailer_failures + 1))
                report error "${key}" \
                    "${sha:0:8} ${key}: <${email}> is not a GitHub account - who is this? ${subject}"
                continue
            fi
            [[ "${email,,}" == noreply@github.com ]] && continue
            type="$(account_type "${email}")"
            if [[ "${type}" == Missing ]]; then
                trailer_failures=$((trailer_failures + 1))
                report error "${key}" \
                    "${sha:0:8} ${key}: <${email}> names a GitHub account that does not exist: ${subject}"
            elif [[ "${key,,}" == co-authored-by && "${type}" == Bot ]]; then
                warnings=$((warnings + 1))
                report warning "Co-authored-by" \
                    "${sha:0:8} co-author <${email}> is a bot account, not a person: ${subject}"
            elif [[ "${key,,}" == co-authored-by ]]; then
                warnings=$((warnings + 1))
                report warning "Co-authored-by" \
                    "${sha:0:8} co-author <${email}> - confirm they co-authored this: ${subject}"
            fi
        # The local part may be empty (so "<@users.noreply.github.com>" is
        # caught); the domain needs a dot, so an "@mention" is not an address.
        done < <(grep -oE '[^][[:space:]<>,;"()@]*@[^][[:space:]<>,;"()@]+\.[^][[:space:]<>,;"()@]+' <<< "${value}")
    done <<< "${message}"
    unset seen
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

Every person named in a commit trailer must be a GitHub account, given
by its noreply address: a squash merge copies the trailer onto develop.
A tool is not a co-author. Remove the trailer with an interactive rebase
('reword') and push with --force-with-lease, and configure any tool that
adds trailers automatically not to.
EOF
fi

if (( identity_failures + trailer_failures > 0 )); then
    exit 1
fi

echo "All commits in ${range} use GitHub noreply addresses (${warnings} Co-authored-by warning(s))."

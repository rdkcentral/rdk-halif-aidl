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
# Reads the metadata.yaml reviewers for components affected by a PR,
# maps internal team names to GitHub team slugs, and requests reviews
# from teams that have not yet completed their review.
#
# Usage: bash scripts/request_reviews.sh <PR_NUMBER> [--dry-run]
#
# Requires: gh CLI authenticated with access to rdkcentral org

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
MAPPING_FILE="${REPO_ROOT}/scripts/team_mapping.yaml"
REPO="rdkcentral/rdk-halif-aidl"

if [ -z "${1:-}" ]; then
    echo "Usage: $0 <PR_NUMBER> [--dry-run]"
    exit 1
fi

PR_NUMBER="$1"
DRY_RUN="${2:-}"

# --- Load team mapping ---
declare -A TEAM_MAP
while IFS=': ' read -r key value; do
    # Skip comments and blank lines
    [[ "$key" =~ ^#.*$ || -z "$key" ]] && continue
    TEAM_MAP["$key"]="$value"
done < "$MAPPING_FILE"

echo "Loaded ${#TEAM_MAP[@]} team mappings"

# --- Get changed files from the PR ---
echo "Fetching changed files for PR #${PR_NUMBER}..."
CHANGED_FILES=$(gh pr view "$PR_NUMBER" --repo "$REPO" --json files --jq '.files[].path')

# --- Derive affected components from file paths ---
declare -A COMPONENTS
for file in $CHANGED_FILES; do
    # Match top-level component dirs (e.g. audiodecoder/..., boot/...)
    # or nested ones (e.g. vsi/kernel/...)
    component=""
    if [[ "$file" =~ ^(vsi/[^/]+)/ ]]; then
        component="${BASH_REMATCH[1]}"
    elif [[ "$file" =~ ^([^/]+)/ ]]; then
        candidate="${BASH_REMATCH[1]}"
        # Only count as component if it has a metadata.yaml
        if [ -f "${REPO_ROOT}/${candidate}/metadata.yaml" ]; then
            component="$candidate"
        fi
    fi
    if [ -n "$component" ]; then
        COMPONENTS["$component"]=1
    fi
done

if [ ${#COMPONENTS[@]} -eq 0 ]; then
    echo "No component metadata.yaml found for changed files. Nothing to do."
    exit 0
fi

echo "Affected components: ${!COMPONENTS[*]}"

# --- Collect teams that need to review ---
declare -A REVIEW_TEAMS

for component in "${!COMPONENTS[@]}"; do
    metadata="${REPO_ROOT}/${component}/metadata.yaml"
    if [ ! -f "$metadata" ]; then
        echo "  WARN: ${metadata} not found, skipping"
        continue
    fi

    echo "  Reading ${component}/metadata.yaml..."
    in_reviewers=false
    while IFS= read -r line; do
        if [[ "$line" =~ ^reviewers: ]]; then
            in_reviewers=true
            continue
        fi
        # Exit reviewers block on next top-level key
        if $in_reviewers && [[ "$line" =~ ^[a-zA-Z] ]]; then
            break
        fi
        if $in_reviewers; then
            # Parse "    Team_Name: status"
            if [[ "$line" =~ ^[[:space:]]+([A-Za-z_]+):[[:space:]]+(.+) ]]; then
                team="${BASH_REMATCH[1]}"
                status="${BASH_REMATCH[2]}"
                # Request review from teams that haven't completed review
                if [ "$status" != "reviewed" ] && [ "$status" != "abstained" ]; then
                    if [ -n "${TEAM_MAP[$team]:-}" ]; then
                        REVIEW_TEAMS["${TEAM_MAP[$team]}"]="$team ($status) [${component}]"
                    else
                        echo "    WARN: No GitHub team mapping for '${team}'"
                    fi
                fi
            fi
        fi
    done < "$metadata"
done

if [ ${#REVIEW_TEAMS[@]} -eq 0 ]; then
    echo "All reviewer teams have completed their reviews. No requests needed."
    exit 0
fi

# --- Request reviews ---
echo ""
echo "Teams to request review from:"
for slug in "${!REVIEW_TEAMS[@]}"; do
    echo "  ${slug} ← ${REVIEW_TEAMS[$slug]}"
done

if [ "$DRY_RUN" = "--dry-run" ]; then
    echo ""
    echo "[DRY RUN] Would run:"
    for slug in "${!REVIEW_TEAMS[@]}"; do
        echo "  gh pr edit ${PR_NUMBER} --repo ${REPO} --add-reviewer rdkcentral/${slug}"
    done
else
    echo ""
    for slug in "${!REVIEW_TEAMS[@]}"; do
        echo "Requesting review from rdkcentral/${slug}..."
        gh pr edit "$PR_NUMBER" --repo "$REPO" --add-reviewer "rdkcentral/${slug}" 2>&1 || echo "  WARN: Failed to add ${slug}"
    done
    echo "Done."
fi

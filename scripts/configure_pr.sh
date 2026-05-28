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
# configure_pr.sh — apply the standard configuration to a pull request:
#   * Labels       — component:<name> for each affected component, plus
#                    breaking-change (conventional-commit "!:" title) and
#                    documentation (docs-only change).
#   * Assignees    — the PR author.
#   * Reviewers    — every reviewer team declared in the affected components'
#                    metadata.yaml, mapped to GitHub team slugs. A PR always
#                    requests the relevant teams regardless of the metadata
#                    baseline review status.
#   * Project      — sets the halif_aidl project Status to "Under Review".
#
# Usage:
#   scripts/configure_pr.sh <PR_NUMBER> [--dry-run]
#   scripts/configure_pr.sh --all       [--dry-run]
#
# --dry-run prints every change that WOULD be made, and applies nothing.
#
# Requires: gh CLI authenticated with write access to rdkcentral/rdk-halif-aidl.

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
REPO="rdkcentral/rdk-halif-aidl"
MAPPING_FILE="${REPO_ROOT}/scripts/team_mapping.yaml"
PROJECT_TITLE="halif_aidl"
TARGET_STATUS="Under Review"

# --- Args -------------------------------------------------------------------
PR_ARG="${1:-}"
DRY_RUN=false
for a in "${@:2}"; do [ "$a" = "--dry-run" ] && DRY_RUN=true; done
[ "$PR_ARG" = "--dry-run" ] && { PR_ARG=""; DRY_RUN=true; }

if [ -z "$PR_ARG" ]; then
    echo "Usage: $0 <PR_NUMBER|--all> [--dry-run]"
    exit 1
fi

$DRY_RUN && echo "=== DRY RUN — no changes will be made ===" && echo

# Counter for non-fatal issues — surfaced at end of run and used to set a
# non-zero exit code so CI can detect partial failures (failed gh pr edit
# calls, unmapped reviewer teams, etc.).
WARN_COUNT=0

# --- Team mapping -----------------------------------------------------------
declare -A TEAM_MAP
while IFS=': ' read -r key value; do
    [[ "$key" =~ ^#.*$ || -z "$key" ]] && continue
    TEAM_MAP["$key"]="$value"
done < "$MAPPING_FILE"

# --- Configure a single PR --------------------------------------------------
configure_one_pr() {
    local pr="$1"
    echo "──────────────────────────────────────────────────────────────"
    local meta
    meta=$(gh pr view "$pr" --repo "$REPO" --json number,title,author,labels,assignees,files,isDraft 2>/dev/null) || {
        echo "PR #${pr}: could not read — skipping"; return; }

    local title author
    title=$(echo "$meta" | python3 -c 'import json,sys;print(json.load(sys.stdin)["title"])')
    author=$(echo "$meta" | python3 -c 'import json,sys;print(json.load(sys.stdin)["author"]["login"])')
    echo "PR #${pr}: ${title}"
    echo "  author: ${author}"

    # -- Derive affected components from changed files --
    local components
    components=$(echo "$meta" | python3 -c '
import json,sys,os
root="'"$REPO_ROOT"'"
comps=set()
for f in json.load(sys.stdin)["files"]:
    p=f["path"]; parts=p.split("/")
    if not parts: continue
    cand = "vsi/"+parts[1] if parts[0]=="vsi" and len(parts)>1 else parts[0]
    if os.path.isfile(os.path.join(root,cand,"metadata.yaml")):
        comps.add(cand)
print(" ".join(sorted(comps)))
')
    if [ -z "$components" ]; then
        echo "  components: (none with metadata.yaml) — labels/reviewers skipped"
    else
        echo "  components: ${components}"
    fi

    # -- Desired labels --
    local current_labels desired_labels=""
    current_labels=$(echo "$meta" | python3 -c 'import json,sys;print(",".join(l["name"] for l in json.load(sys.stdin)["labels"]))')
    for c in $components; do desired_labels+="component:${c}\n"; done
    # breaking-change: conventional-commit "!" before the colon
    if [[ "$title" =~ ^[a-z]+(\([^\)]*\))?!: ]]; then desired_labels+="breaking-change\n"; fi
    # documentation-change: every changed file is doc-like. Predicate mirrors
    # scripts/release.sh:is_doc_like_path so the two scripts agree on what
    # counts as docs-only (release.sh consumes this label to drive a patch bump).
    local docs_only
    docs_only=$(echo "$meta" | python3 -c '
import json,sys,os.path
def is_doc(p):
    if p.startswith("docs/") or "/docs/" in p: return True
    if p.endswith(".md") or p.endswith(".rst") or p.endswith(".txt"): return True
    base = os.path.basename(p)
    if base == "README" or base.startswith("README."): return True
    if base == "CHANGELOG" or base.startswith("CHANGELOG."): return True
    if base == "metadata.yaml": return True
    if base.startswith("hfp-") and base.endswith(".yaml"): return True
    return False
fs=[f["path"] for f in json.load(sys.stdin)["files"]]
print("yes" if fs and all(is_doc(p) for p in fs) else "no")
')
    [ "$docs_only" = "yes" ] && desired_labels+="documentation\n"

    local add_labels=()
    while IFS= read -r lbl; do
        [ -z "$lbl" ] && continue
        if [[ ",${current_labels}," != *",${lbl},"* ]]; then add_labels+=("$lbl"); fi
    done < <(echo -e "$desired_labels")

    if [ ${#add_labels[@]} -eq 0 ]; then
        echo "  labels: up to date"
    else
        echo "  labels: + ${add_labels[*]}"
        if ! $DRY_RUN; then
            local args=(); for l in "${add_labels[@]}"; do args+=(--add-label "$l"); done
            if gh pr edit "$pr" --repo "$REPO" "${args[@]}" >/dev/null; then
                echo "    applied"
            else
                echo "    WARN: gh pr edit failed to add labels" >&2
                WARN_COUNT=$((WARN_COUNT + 1))
            fi
        fi
    fi

    # -- Assignee = author (bots cannot be assignees) --
    local current_assignees
    current_assignees=$(echo "$meta" | python3 -c 'import json,sys;print(",".join(a["login"] for a in json.load(sys.stdin)["assignees"]))')
    if [[ "$author" == *"[bot]" || "$author" == app/* ]]; then
        echo "  assignee: author '${author}' is a bot — skipped"
    elif [[ ",${current_assignees}," == *",${author},"* ]]; then
        echo "  assignee: ${author} already set"
    else
        echo "  assignee: + ${author}"
        if ! $DRY_RUN; then
            if gh pr edit "$pr" --repo "$REPO" --add-assignee "$author" >/dev/null; then
                echo "    applied"
            else
                echo "    WARN: gh pr edit failed to add assignee '${author}'" >&2
                WARN_COUNT=$((WARN_COUNT + 1))
            fi
        fi
    fi

    # -- Reviewer teams: union of all teams in affected components' metadata --
    local -A want_teams=()
    for c in $components; do
        local md="${REPO_ROOT}/${c}/metadata.yaml"
        [ -f "$md" ] || continue
        local in_rev=false
        while IFS= read -r line; do
            [[ "$line" =~ ^reviewers: ]] && { in_rev=true; continue; }
            $in_rev && [[ "$line" =~ ^[a-zA-Z] ]] && break
            if $in_rev && [[ "$line" =~ ^[[:space:]]+([A-Za-z_]+): ]]; then
                local team="${BASH_REMATCH[1]}"
                if [ -n "${TEAM_MAP[$team]:-}" ]; then
                    want_teams["${TEAM_MAP[$team]}"]=1
                else
                    echo "    WARN: no GitHub team mapping for '${team}' (${c}) — add an entry to ${MAPPING_FILE#${REPO_ROOT}/}" >&2
                    WARN_COUNT=$((WARN_COUNT + 1))
                fi
            fi
        done < "$md"
    done
    if [ ${#want_teams[@]} -eq 0 ]; then
        echo "  reviewers: (no teams derived)"
    else
        echo "  reviewers: request teams → ${!want_teams[*]}"
        if ! $DRY_RUN; then
            for slug in "${!want_teams[@]}"; do
                gh pr edit "$pr" --repo "$REPO" --add-reviewer "rdkcentral/${slug}" 2>/dev/null \
                    && echo "    requested ${slug}" || echo "    WARN: could not request ${slug}"
            done
        fi
    fi

    # -- Project Status → Under Review (resolved from the PR's own item) --
    local item_json
    item_json=$(gh api graphql -f query='
      { repository(owner:"rdkcentral",name:"rdk-halif-aidl"){ pullRequest(number:'"$pr"'){
          projectItems(first:10){ nodes{ id
            project{ id title field(name:"Status"){ ... on ProjectV2SingleSelectField { id options{ id name } } } }
            fieldValueByName(name:"Status"){ ... on ProjectV2ItemFieldSingleSelectValue { name } } } } } } }' 2>/dev/null || true)
    local proj_id item_id field_id option_id cur_status
    read -r proj_id item_id field_id option_id cur_status < <(echo "$item_json" | python3 -c '
import json,sys
want_proj="'"$PROJECT_TITLE"'"; want_status="'"$TARGET_STATUS"'"
try: nodes=json.load(sys.stdin)["data"]["repository"]["pullRequest"]["projectItems"]["nodes"]
except Exception: nodes=[]
for n in nodes:
    pr=n.get("project") or {}
    if pr.get("title")==want_proj:
        fld=pr.get("field") or {}
        opt=next((o["id"] for o in fld.get("options",[]) if o["name"]==want_status),"")
        fv=n.get("fieldValueByName") or {}
        print(pr.get("id",""), n["id"], fld.get("id",""), opt, (fv.get("name") or "(unset)").replace(" ","_"))
        break
else: print("    ")
')
    # Only advance to "Under Review" from a pre-review state — never regress a
    # PR that is already further along the pipeline.
    local ADVANCEABLE="|(unset)|Todo|In Progress|Architecture Review Required|Architecture Changes Requested|Review Requested|"
    local cs="${cur_status//_/ }"
    if [ -z "$item_id" ]; then
        echo "  project: PR not in '${PROJECT_TITLE}' project — skipped"
    elif [ -z "$option_id" ]; then
        echo "  project: '${TARGET_STATUS}' is not an option on the Status field — skipped"
    elif [ "$cs" = "$TARGET_STATUS" ]; then
        echo "  project: status already '${TARGET_STATUS}'"
    elif [[ "$ADVANCEABLE" != *"|${cs}|"* ]]; then
        echo "  project: status '${cs}' is at/past '${TARGET_STATUS}' — left unchanged"
    else
        echo "  project: status '${cs}' → '${TARGET_STATUS}'"
        if ! $DRY_RUN; then
            gh api graphql -f query='mutation{updateProjectV2ItemFieldValue(input:{projectId:"'"$proj_id"'",itemId:"'"$item_id"'",fieldId:"'"$field_id"'",value:{singleSelectOptionId:"'"$option_id"'"}}){projectV2Item{id}}}' >/dev/null \
                && echo "    applied"
        fi
    fi
}

# --- Main -------------------------------------------------------------------
if [ "$PR_ARG" = "--all" ]; then
    PRS=$(gh pr list --repo "$REPO" --state open --limit 200 --json number --jq '.[].number')
    echo "Configuring $(echo "$PRS" | wc -w) open PR(s)"
    for pr in $PRS; do configure_one_pr "$pr"; done
else
    configure_one_pr "$PR_ARG"
fi
echo "──────────────────────────────────────────────────────────────"
$DRY_RUN && echo "Dry run complete — re-run without --dry-run to apply." || echo "Done."

if [ "$WARN_COUNT" -gt 0 ]; then
    echo
    echo "Completed with ${WARN_COUNT} warning(s) — see WARN lines above."
    exit 1
fi

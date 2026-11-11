#!/bin/bash
# =============================================================================
# GitHub Label Setup
# Creates component, workflow, and scope labels on the GitHub repository.
# Removes legacy labels from earlier versions of this script, except any a
# ticket still carries, which are kept and reported (#1020).
# Idempotent — safe to re-run; existing labels are updated to this file.
#
# Components are discovered from the directory structure — any directory
# containing a metadata.yaml file is treated as a component.
#
# Usage:
#   ./scripts/setup_labels.sh [--dry-run]
# =============================================================================

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
REPO="rdkcentral/rdk-halif-aidl"
DRY_RUN=false
FAILED=0
KEPT=0

if [ "${1:-}" = "--dry-run" ]; then
    DRY_RUN=true
    echo "[DRY RUN] No changes will be made."
    echo ""
fi

# ---------------------------------------------------------------------------
# Discover components from directory structure (metadata.yaml = component)
# ---------------------------------------------------------------------------

COMPONENTS=$(find "$REPO_ROOT" -name "metadata.yaml" -not -path "*/docs/*" -not -path "*/scripts/*" \
    | sed "s|$REPO_ROOT/||;s|/metadata.yaml||" | sort)

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

create_label() {
    local name="$1" color="$2" description="$3"
    if $DRY_RUN; then
        printf "  Would create:  %-40s  #%-6s  %s\n" "$name" "$color" "$description"
        return
    fi
    # --force updates an existing label, so colours and descriptions stay in
    # step with this file; a real failure (a description over GitHub's
    # 100-character limit, say) is reported rather than read as "Exists".
    if gh label create "$name" --repo "$REPO" --color "$color" --description "$description" --force 2>/dev/null; then
        echo "  Set:     $name"
    else
        echo "  FAILED:  $name" >&2
        FAILED=$((FAILED + 1))
    fi
}

# Deleting a label strips it from every ticket that carries it, so a legacy
# label still in use is kept and reported, never deleted (#1020). If the use
# count cannot be read, the label is kept too.
delete_label() {
    local name="$1" used
    used=$(gh api -X GET search/issues -f q="repo:${REPO} label:\"${name}\"" --jq .total_count 2>/dev/null) || used=""
    if [[ ! "${used}" =~ ^[0-9]+$ ]]; then
        echo "  Kept:    ${name} (could not count its tickets)" >&2
        KEPT=$((KEPT + 1))
        return
    fi
    if [ "${used}" -gt 0 ]; then
        echo "  Kept:    ${name} (still on ${used} ticket(s); migrate them first)" >&2
        KEPT=$((KEPT + 1))
        return
    fi
    if $DRY_RUN; then
        printf "  Would delete:  %s\n" "$name"
        return
    fi
    if gh label delete "$name" --repo "$REPO" --yes 2>/dev/null; then
        echo "  Deleted: $name"
    fi
}

# ---------------------------------------------------------------------------
# Remove legacy labels (from earlier versions of this script)
# ---------------------------------------------------------------------------

echo "Cleaning up legacy labels..."

# Legacy status labels (RAG status is in metadata.yaml)
for lbl in "status:green" "status:amber" "status:red"; do
    delete_label "$lbl"
done

# Legacy workflow labels
for lbl in "review-cycle" "sprint-required" "scope:multi-component" "scope:documentation" "documentation-change" \
           "breaking-change"; do
    # `breaking-change` was replaced in #545 and the class was folded into
    # `Major Change` in #712 — delete the lowercase form. `documentation`
    # is kept (see Change-class labels below — the bugfix tier).
    delete_label "$lbl"
done

# Legacy team labels (PRs are assigned to GitHub teams directly)
for team in RTAB_Group Architecture Product_Architecture VTS_Team \
            AV_Architecture Broadcast_Team Control_Manager_Architecture \
            Graphics_Architecture Connectivity_Architecture Kernel_Architecture \
            Radio_Architecture; do
    delete_label "team:${team}"
done

# Legacy module: labels (renamed to component:)
for comp in $COMPONENTS; do
    delete_label "module:${comp}"
done

echo ""

# ---------------------------------------------------------------------------
# Component labels (one per metadata.yaml in the repo)
# ---------------------------------------------------------------------------

echo "Component labels:"

COMPONENT_COLOR="1d76db"
for comp in $COMPONENTS; do
    create_label "component:${comp}" "$COMPONENT_COLOR" "HAL component: ${comp}"
done

# Deprecated component labels — kept so historical PRs retain their labels.
# `flash` was renamed to `firmwareupdate` in #523. The `flash/` directory is
# retained as a historical snapshot for backward compatibility, but its
# `metadata.yaml` has been removed so the component scan above no longer
# discovers it — hence we re-create the label here so it is not lost.
create_label "component:flash" "$COMPONENT_COLOR" "HAL component: flash (deprecated — renamed to firmwareupdate, #523)"

echo ""

# ---------------------------------------------------------------------------
# Workflow labels
# ---------------------------------------------------------------------------

echo "Change-class labels (every PR carries exactly one, see #712 — label names mean what the fields mean):"
create_label "Major Change"         "b60205" "Breaking interface change (renames/removals/signature changes) — bumps major"
create_label "Minor Change"         "a2eeef" "Additive, backwards-compatible interface change — bumps minor; the default for real work"
create_label "documentation"        "0075ca" "Surface untouched (docs, comments, metadata): bumps bugfix; auto-applied when every file is doc-like"
create_label "Breaking Change"      "d4c5f9" "RETIRED (#712): alias of Major Change accepted during transition — do not apply to new PRs"

echo ""

# ---------------------------------------------------------------------------
# Process / governance labels
#
# `CR` marks an ABI change that must go through wider review sign-off and be
# scheduled into a release deliberately. It is INDEPENDENT of the change-class
# above: the change-class answers "how does the version number move?", `CR`
# answers "is this an ABI change needing review + scheduling?" — so it is
# orthogonal and co-exists with a change-class label (an ABI change is a
# `Breaking Change`). It does NOT affect the version bump; `release.sh` never
# reads it.
#
# `New Interface` marks a brand-new interface surface (a new component). It is
# a change class of its own, below Major and above Minor: adding a component
# breaks nothing, and a new component releases at 0.1.0.0 whatever the label
# (#973). Both are mirrored to the project's `Interface Effect` field by
# scripts/project_interface_effect.py; CR is written alongside `Major Change`.
# ---------------------------------------------------------------------------

echo "Process / governance labels:"
create_label "CR"                    "5319e7" "Change Request — ABI change needing wider review sign-off + separate release scheduling"
create_label "New Interface"         "d93f0b" "New component: its own change class, below Major, above Minor; releases at 0.1.0.0"

echo ""

# ---------------------------------------------------------------------------
# Scope labels (for cross-cutting / infrastructure work)
# ---------------------------------------------------------------------------

echo "Scope labels:"
create_label "scope:infrastructure"  "bfd4f2" "Repo tooling, CI/CD, scripts, governance docs"
create_label "scope:overview"        "d4c5f9" "Overview / tracking ticket spanning multiple components"

echo ""
if [ "${KEPT}" -gt 0 ]; then
    echo "${KEPT} legacy label(s) kept because tickets still carry them." >&2
fi
if [ "${FAILED}" -gt 0 ]; then
    echo "Done, with ${FAILED} label(s) not set." >&2
    exit 1
fi
echo "Done."

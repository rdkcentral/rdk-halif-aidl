#!/bin/bash
# =============================================================================
# GitHub Label Setup
# Creates component, workflow, and scope labels on the GitHub repository.
# Removes any legacy labels from earlier versions of this script.
# Idempotent — safe to re-run; existing labels are skipped.
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
    if gh label create "$name" --repo "$REPO" --color "$color" --description "$description" 2>/dev/null; then
        echo "  Created: $name"
    else
        echo "  Exists:  $name"
    fi
}

delete_label() {
    local name="$1"
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
for lbl in "review-cycle" "sprint-required" "scope:multi-component" "scope:documentation" "documentation-change"; do
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

echo ""

# ---------------------------------------------------------------------------
# Workflow labels
# ---------------------------------------------------------------------------

echo "Workflow labels:"
create_label "breaking-change"      "b60205" "Breaking interface change — bumps generation"
create_label "documentation"        "0075ca" "Documentation-only change — no interface change"

echo ""

# ---------------------------------------------------------------------------
# Scope labels (for cross-cutting / infrastructure work)
# ---------------------------------------------------------------------------

echo "Scope labels:"
create_label "scope:infrastructure"  "bfd4f2" "Repo tooling, CI/CD, scripts, governance docs"
create_label "scope:overview"        "d4c5f9" "Overview / tracking ticket spanning multiple components"

echo ""
echo "Done."

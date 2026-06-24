#!/bin/bash
# =============================================================================
# PR Cycle Manager
# Manages the 14+5 review lifecycle for HAL component metadata.
#
# Usage:
#   ./scripts/pr_cycle.sh <component> --start [date]
#   ./scripts/pr_cycle.sh <component> --stop
#   ./scripts/pr_cycle.sh --clear
#   ./scripts/pr_cycle.sh --help
#
# Actions:
#   --start [date]  Begin a 14+5 review cycle (sets lifecycle dates)
#   --stop          End the review cycle for a component (clears dates)
#   --clear         Clear lifecycle dates on ALL components (mass reset)
#   --help          Show this help message
#
# Only updates lifecycle dates. Does NOT change RAG status or reviewers.
# =============================================================================

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

list_components() {
    find "$REPO_ROOT" -name "metadata.yaml" -not -path "*/docs/*" -not -path "*/scripts/*" \
        | sed "s|$REPO_ROOT/||;s|/metadata.yaml||" | sort
}

show_help() {
    cat <<'EOF'
PR Cycle Manager — 14+5 Review Lifecycle

Usage:
  pr_cycle.sh <component> --start [date]   Start a review cycle
  pr_cycle.sh <component> --stop           End a review cycle
  pr_cycle.sh --clear                      Clear ALL component dates
  pr_cycle.sh --help                       Show this help

Actions:
  --start   Sets review_started, review_deadline (+14 days),
            and target_green_date (+5 business days) in metadata.yaml.
            Optional [date] argument (YYYY-MM-DD), defaults to today.

  --stop    Clears the lifecycle dates for a single component,
            signalling that the review cycle has ended.

  --clear   Clears lifecycle dates across ALL components.
            Use this to reset stale batch dates.

Notes:
  Only lifecycle dates are changed. RAG status and reviewer states
  are managed separately.

EOF
    echo "Available components:"
    list_components | sed 's/^/  /'
}

resolve_metadata() {
    local comp="$1"
    local meta="${REPO_ROOT}/${comp}/metadata.yaml"
    if [ ! -f "$meta" ]; then
        echo "ERROR: metadata.yaml not found at: ${comp}/metadata.yaml" >&2
        echo "" >&2
        echo "Available components:" >&2
        list_components | sed 's/^/  /' >&2
        exit 1
    fi
    echo "$meta"
}

add_business_days() {
    local current="$1"
    local days_to_add="$2"
    local added=0
    while [ "$added" -lt "$days_to_add" ]; do
        current=$(date -d "${current} + 1 day" +%Y-%m-%d)
        local dow
        dow=$(date -d "$current" +%u)  # 1=Mon ... 7=Sun
        if [ "$dow" -le 5 ]; then
            added=$((added + 1))
        fi
    done
    echo "$current"
}

clear_dates() {
    local file="$1"
    sed -i \
        -e 's/^\(  review_started:\).*/\1 ~/' \
        -e 's/^\(  review_deadline:\).*/\1 ~/' \
        -e 's/^\(  target_green_date:\).*/\1 ~/' \
        "$file"
}

regen_report() {
    "${REPO_ROOT}/scripts/generate_rag_report.sh" >/dev/null
}

# ---------------------------------------------------------------------------
# Argument parsing
# ---------------------------------------------------------------------------

if [ $# -lt 1 ]; then
    show_help
    exit 1
fi

# Handle global flags first
case "$1" in
    --help|-h)
        show_help
        exit 0
        ;;
    --clear)
        echo ""
        echo "Clearing lifecycle dates on all components..."
        for f in $(find "$REPO_ROOT" -name "metadata.yaml" -not -path "*/docs/*" -not -path "*/scripts/*" | sort); do
            clear_dates "$f"
            rel="${f#$REPO_ROOT/}"
            echo "  Cleared: ${rel%/metadata.yaml}"
        done
        regen_report
        echo ""
        echo "  Updated: RAG_STATUS_REPORT.md"
        echo ""
        exit 0
        ;;
esac

# Component-level actions require at least 2 args
COMPONENT="$1"
ACTION="${2:---help}"

case "$ACTION" in
    --start)
        START_DATE="${3:-$(date +%Y-%m-%d)}"
        METADATA=$(resolve_metadata "$COMPONENT")

        # Validate date
        if ! date -d "$START_DATE" +%Y-%m-%d >/dev/null 2>&1; then
            echo "ERROR: Invalid date format '${START_DATE}'. Use YYYY-MM-DD." >&2
            exit 1
        fi

        REVIEW_DEADLINE=$(date -d "${START_DATE} + 14 days" +%Y-%m-%d)
        TARGET_GREEN=$(add_business_days "$REVIEW_DEADLINE" 5)

        sed -i \
            -e "s/^\(  review_started:\).*/\1 ${START_DATE}/" \
            -e "s/^\(  review_deadline:\).*/\1 ${REVIEW_DEADLINE}/" \
            -e "s/^\(  target_green_date:\).*/\1 ${TARGET_GREEN}/" \
            "$METADATA"

        regen_report

        echo ""
        echo "Release cycle started for: ${COMPONENT}"
        echo "  Review window:  ${START_DATE} -> ${REVIEW_DEADLINE}  (14 days)"
        echo "  Resolution by:  ${TARGET_GREEN}  (5 business days)"
        echo ""
        echo "  Updated: ${COMPONENT}/metadata.yaml"
        echo "  Updated: RAG_STATUS_REPORT.md"
        echo ""
        ;;

    --stop)
        METADATA=$(resolve_metadata "$COMPONENT")
        clear_dates "$METADATA"
        regen_report

        echo ""
        echo "Release cycle stopped for: ${COMPONENT}"
        echo "  Lifecycle dates cleared."
        echo ""
        echo "  Updated: ${COMPONENT}/metadata.yaml"
        echo "  Updated: RAG_STATUS_REPORT.md"
        echo ""
        ;;

    *)
        echo "ERROR: Unknown action '${ACTION}'" >&2
        echo "" >&2
        echo "Usage:" >&2
        echo "  pr_cycle.sh <component> --start [date]" >&2
        echo "  pr_cycle.sh <component> --stop" >&2
        echo "  pr_cycle.sh --clear" >&2
        echo "  pr_cycle.sh --help" >&2
        exit 1
        ;;
esac

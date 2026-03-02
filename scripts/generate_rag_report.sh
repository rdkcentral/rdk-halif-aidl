#!/bin/bash
# =============================================================================
# RAG Status Report Generator
# Parses metadata.yaml files across all HAL/VSI components and generates
# a markdown dashboard showing interface readiness on develop.
# =============================================================================

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
OUTPUT="${REPO_ROOT}/RAG_STATUS_REPORT.md"
TODAY=$(date +%Y-%m-%d)

# Collect all metadata.yaml files (exclude docs)
METADATA_FILES=$(find "$REPO_ROOT" -name "metadata.yaml" -not -path "*/docs/*" -not -path "*/scripts/*" | sort)

# Counters
GREEN_COUNT=0
AMBER_COUNT=0
RED_COUNT=0
TOTAL=0

# Temporary arrays for each status, split by SOC/OEM/Shared
GREEN_SOC_ROWS=""
GREEN_OEM_ROWS=""
GREEN_SHARED_ROWS=""
AMBER_SOC_ROWS=""
AMBER_OEM_ROWS=""
AMBER_SHARED_ROWS=""
RED_SOC_ROWS=""
RED_OEM_ROWS=""
RED_SHARED_ROWS=""
GREEN_SOC_REVIEW_ROWS=""
GREEN_OEM_REVIEW_ROWS=""
AMBER_SOC_REVIEW_ROWS=""
AMBER_OEM_REVIEW_ROWS=""
RED_SOC_REVIEW_ROWS=""
RED_OEM_REVIEW_ROWS=""

# RAG colour indicators
RAG_GREEN="🟢"
RAG_AMBER="🟡"
RAG_RED="🔴"

# Parse a single YAML value by key (top-level only)
yaml_val() {
    local file="$1" key="$2"
    awk -v k="$key" '$0 ~ "^"k": " {gsub("^"k": *",""); gsub(/"/,""); print; exit}' "$file"
}

# Parse a nested YAML value (e.g. notes.priority)
yaml_nested() {
    local file="$1" parent="$2" key="$3"
    awk -v p="$parent" -v k="$key" '
        $0 ~ "^"p":" {found=1; next}
        found && /^[^ #]/ {found=0}
        found && $0 ~ "^  "k": " {
            gsub("^  "k": *","")
            gsub(/"/,"")
            print
            exit
        }
    ' "$file"
}

# Parse reviewer map (Team: status) and return "reviewed/total" count
yaml_review_progress() {
    local file="$1"
    awk '
        /^reviewers:/ {found=1; next}
        found && /^[^ #]/ {found=0}
        found && /^    [A-Za-z]/ {
            split($0, a, ": ")
            gsub(/^ +/, "", a[1])
            total++
            if (a[2] == "reviewed") reviewed++
            else if (a[2] == "abstained") abstained++
        }
        END { printf "%d/%d", reviewed+0, total+0 }
    ' "$file"
}

# Get review status for a specific team from a file
yaml_reviewer_status() {
    local file="$1" team="$2"
    awk -v t="$team" '
        /^reviewers:/ {found=1; next}
        found && /^[^ #]/ {found=0}
        found && index($0, t": ") {
            sub(/.*: /, "")
            print
            exit
        }
    ' "$file"
}

# Map reviewer status to visual indicator
review_icon() {
    case "$1" in
        reviewed)  echo "✅" ;;
        pending)   echo "☐" ;;
        abstained) echo "➖" ;;
        *)         echo "N/A" ;;
    esac
}

# All teams (column order)
ALL_TEAMS="Architecture VTS_Team AV_Architecture Broadcast_Team Control_Manager_Team Graphics_Architecture Bluetooth_Architecture Kernel_Architecture"

# Derive component path label (e.g. "vsi/kernel" or "boot")
component_path() {
    local file="$1"
    local rel="${file#$REPO_ROOT/}"
    echo "$rel" | sed 's|/current/metadata.yaml||'
}

# Map status to colour indicator
rag_icon() {
    case "$1" in
        GREEN) echo "$RAG_GREEN" ;;
        AMBER) echo "$RAG_AMBER" ;;
        RED)   echo "$RAG_RED" ;;
        *)     echo "⚪" ;;
    esac
}

for f in $METADATA_FILES; do
    TOTAL=$((TOTAL + 1))

    comp=$(yaml_val "$f" "component")
    version=$(yaml_val "$f" "version")
    status=$(yaml_val "$f" "status")
    description=$(yaml_val "$f" "description")
    comp_type=$(yaml_val "$f" "type")
    priority=$(yaml_nested "$f" "notes" "priority")
    status_detail=$(yaml_nested "$f" "notes" "status_detail")
    action=$(yaml_nested "$f" "notes" "action")
    owners=$(yaml_nested "$f" "notes" "owners")
    risk=$(yaml_nested "$f" "notes" "risk")
    review_progress=$(yaml_review_progress "$f")
    path=$(component_path "$f")
    icon=$(rag_icon "$status")

    # Build row (AMBER/RED use full detail)
    row="| ${icon} | ${path} | ${version} | ${priority:-—} | ${status_detail:-—} | ${action:-—} | ${review_progress} | ${owners:-—} |"

    # Build GREEN row (simplified: description + owners, no reviews)
    green_row="| ${icon} | ${path} | ${version} | ${description:-—} | ${owners:-—} |"

    # Build review detail row with per-team columns
    detail_row="| ${icon} | ${path} | ${review_progress}"
    for team in $ALL_TEAMS; do
        team_status=$(yaml_reviewer_status "$f" "$team")
        detail_row="${detail_row} | $(review_icon "$team_status")"
    done
    detail_row="${detail_row} |"

    # Helper: append row to the correct SOC/OEM/Shared bucket
    append_row() {
        local soc_var="$1" oem_var="$2" shared_var="$3" the_row="$4"
        if [ "$comp_type" = "SOC" ]; then
            eval "${soc_var}=\"\${${soc_var}}\${the_row}\\n\""
        elif [ "$comp_type" = "OEM" ]; then
            eval "${oem_var}=\"\${${oem_var}}\${the_row}\\n\""
        else
            eval "${shared_var}=\"\${${shared_var}}\${the_row}\\n\""
        fi
    }

    # Helper: append review row to the correct SOC/OEM bucket
    append_review_row() {
        local soc_var="$1" oem_var="$2" the_row="$3"
        if [ "$comp_type" = "SOC" ]; then
            eval "${soc_var}=\"\${${soc_var}}\${the_row}\\n\""
        else
            eval "${oem_var}=\"\${${oem_var}}\${the_row}\\n\""
        fi
    }

    case "$status" in
        GREEN)
            GREEN_COUNT=$((GREEN_COUNT + 1))
            append_row GREEN_SOC_ROWS GREEN_OEM_ROWS GREEN_SHARED_ROWS "$green_row"
            append_review_row GREEN_SOC_REVIEW_ROWS GREEN_OEM_REVIEW_ROWS "$detail_row"
            # If component has a risk note, also list it in AMBER as a watch item
            if [ -n "$risk" ]; then
                amber_row="| ${RAG_AMBER} | ${path} *(SVP risk)* | ${version} | ${priority:-—} | ${status_detail:-—} | ${risk} | ${review_progress} | ${owners:-—} |"
                append_row AMBER_SOC_ROWS AMBER_OEM_ROWS AMBER_SHARED_ROWS "$amber_row"
            fi
            ;;
        AMBER)
            AMBER_COUNT=$((AMBER_COUNT + 1))
            append_row AMBER_SOC_ROWS AMBER_OEM_ROWS AMBER_SHARED_ROWS "$row"
            append_review_row AMBER_SOC_REVIEW_ROWS AMBER_OEM_REVIEW_ROWS "${priority:-99}\t${detail_row}"
            ;;
        RED)
            RED_COUNT=$((RED_COUNT + 1))
            append_row RED_SOC_ROWS RED_OEM_ROWS RED_SHARED_ROWS "$row"
            append_review_row RED_SOC_REVIEW_ROWS RED_OEM_REVIEW_ROWS "${priority:-99}\t${detail_row}"
            ;;
    esac
done

# Git describe for traceability
GIT_DESCRIBE=$(git -C "$REPO_ROOT" describe --tags --always 2>/dev/null || git -C "$REPO_ROOT" rev-parse --short HEAD)
GIT_BRANCH=$(git -C "$REPO_ROOT" rev-parse --abbrev-ref HEAD 2>/dev/null)

# Generate report
cat > "$OUTPUT" << HEADER
# HAL Interface RAG Status Report

| | |
|---|---|
| **Generated** | ${TODAY} |
| **Branch** | \`${GIT_BRANCH}\` |
| **Version** | \`${GIT_DESCRIBE}\` |
| **Components** | ${TOTAL} |
| ${RAG_GREEN} **GREEN** | ${GREEN_COUNT} |
| ${RAG_AMBER} **AMBER** | ${AMBER_COUNT} |
| ${RAG_RED} **RED** | ${RED_COUNT} |

---

## Summary

| Status | Count | Meaning |
|--------|-------|---------|
| ${RAG_GREEN} GREEN | **${GREEN_COUNT}** | Reviewed & Approved — Interface stable on develop |
| ${RAG_AMBER} AMBER | **${AMBER_COUNT}** | Under Active Review — Design iteration in progress |
| ${RAG_RED} RED | **${RED_COUNT}** | Not Started / Blocked — Strategy or definition required |

---

## ${RAG_GREEN} GREEN — Reviewed & Approved

### SOC Components

| | Component | Version | Description | Owners |
|---|-----------|---------|-------------|--------|
HEADER

echo -e "$GREEN_SOC_ROWS" >> "$OUTPUT"

cat >> "$OUTPUT" << 'GREEN_OEM'

### OEM Components

| | Component | Version | Description | Owners |
|---|-----------|---------|-------------|--------|
GREEN_OEM

echo -e "$GREEN_OEM_ROWS" >> "$OUTPUT"

if [ -n "$GREEN_SHARED_ROWS" ]; then
cat >> "$OUTPUT" << 'GREEN_SHARED'

### Shared

| | Component | Version | Description | Owners |
|---|-----------|---------|-------------|--------|
GREEN_SHARED
echo -e "$GREEN_SHARED_ROWS" >> "$OUTPUT"
fi

cat >> "$OUTPUT" << 'SECTION2'

---

## 🟡 AMBER — Under Active Review

### SOC Components

| | Component | Version | Priority | Detail | Action Required | Reviews | Owners |
|---|-----------|---------|----------|--------|-----------------|---------|--------|
SECTION2

printf '%b' "$AMBER_SOC_ROWS" | grep -v '^$' | sort -t'|' -k5 -n >> "$OUTPUT"
echo "" >> "$OUTPUT"

cat >> "$OUTPUT" << 'AMBER_OEM'

### OEM Components

| | Component | Version | Priority | Detail | Action Required | Reviews | Owners |
|---|-----------|---------|----------|--------|-----------------|---------|--------|
AMBER_OEM

printf '%b' "$AMBER_OEM_ROWS" | grep -v '^$' | sort -t'|' -k5 -n >> "$OUTPUT"
echo "" >> "$OUTPUT"

if [ -n "$AMBER_SHARED_ROWS" ]; then
cat >> "$OUTPUT" << 'AMBER_SHARED'

### Shared

| | Component | Version | Priority | Detail | Action Required | Reviews | Owners |
|---|-----------|---------|----------|--------|-----------------|---------|--------|
AMBER_SHARED
printf '%b' "$AMBER_SHARED_ROWS" | grep -v '^$' | sort -t'|' -k5 -n >> "$OUTPUT"
echo "" >> "$OUTPUT"
fi

cat >> "$OUTPUT" << 'SECTION3'

---

## 🔴 RED — Not Started / Blocked

### SOC Components

| | Component | Version | Priority | Detail | Action Required | Reviews | Owners |
|---|-----------|---------|----------|--------|-----------------|---------|--------|
SECTION3

printf '%b' "$RED_SOC_ROWS" | grep -v '^$' | sort -t'|' -k5 -n >> "$OUTPUT"
echo "" >> "$OUTPUT"

cat >> "$OUTPUT" << 'RED_OEM'

### OEM Components

| | Component | Version | Priority | Detail | Action Required | Reviews | Owners |
|---|-----------|---------|----------|--------|-----------------|---------|--------|
RED_OEM

printf '%b' "$RED_OEM_ROWS" | grep -v '^$' | sort -t'|' -k5 -n >> "$OUTPUT"
echo "" >> "$OUTPUT"

if [ -n "$RED_SHARED_ROWS" ]; then
cat >> "$OUTPUT" << 'RED_SHARED'

### Shared

| | Component | Version | Priority | Detail | Action Required | Reviews | Owners |
|---|-----------|---------|----------|--------|-----------------|---------|--------|
RED_SHARED
echo -e "$RED_SHARED_ROWS" >> "$OUTPUT"
fi

REVIEW_HEADER="| | Component | Progress | Arch | VTS | AV | Broadcast | CtrlMgr | Graphics | BT/Net | Kernel |
|---|-----------|----------|------|-----|-----|-----------|---------|----------|--------|--------|"

cat >> "$OUTPUT" << 'REVIEW_SECTION'

---

## Review Status by Component

> ✅ Reviewed | ☐ Pending | ➖ Abstained | N/A Not assigned

### SOC Components

REVIEW_SECTION

echo "$REVIEW_HEADER" >> "$OUTPUT"
printf '%b' "$GREEN_SOC_REVIEW_ROWS" >> "$OUTPUT"
printf '%b' "$AMBER_SOC_REVIEW_ROWS" | grep -v '^$' | sort -t$'\t' -k1 -n | cut -f2- >> "$OUTPUT"
printf '%b' "$RED_SOC_REVIEW_ROWS" | grep -v '^$' | sort -t$'\t' -k1 -n | cut -f2- >> "$OUTPUT"

cat >> "$OUTPUT" << 'REVIEW_OEM'

### OEM Components

REVIEW_OEM

echo "$REVIEW_HEADER" >> "$OUTPUT"
printf '%b' "$GREEN_OEM_REVIEW_ROWS" >> "$OUTPUT"
printf '%b' "$AMBER_OEM_REVIEW_ROWS" | grep -v '^$' | sort -t$'\t' -k1 -n | cut -f2- >> "$OUTPUT"
printf '%b' "$RED_OEM_REVIEW_ROWS" | grep -v '^$' | sort -t$'\t' -k1 -n | cut -f2- >> "$OUTPUT"

cat >> "$OUTPUT" << 'FOOTER'

---

## Reviewer Team Coverage

> **Note:** Architecture and Product_Architecture are the same organisational group reviewing as separate stakeholders, with members drawn from various teams.

| Team | Role |
|------|------|
| RTAB_Group | All components |
| Architecture | All components |
| Product_Architecture | All components |
| VTS_Team | All components |
| AV_Architecture | Audio/Video pipeline components |
| Broadcast_Team | Broadcast/tuner components |
| Control_Manager_Team | Remote control & input management |
| Graphics_Architecture | Graphics, display & composition |
| Bluetooth_Architecture | Bluetooth, Wi-Fi & connectivity |
| Kernel_Architecture | System, kernel, boot & platform |

---

### RAG Key

- 🟢 **GREEN** — Interface reviewed, approved and stable. Ready for implementation.
- 🟡 **AMBER** — Interface under active review. Design iteration in progress.
- 🔴 **RED** — Interface not yet started or blocked. Requires architecture strategy, AIDL definition, or team alignment.

---

*Report generated by `scripts/generate_rag_report.sh`*
FOOTER

echo "Report generated: ${OUTPUT}"

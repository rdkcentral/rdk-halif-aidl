#!/usr/bin/env bash
# Format AIDL files under the directories listed below using the .clang-format in this directory.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ASSUME_FILENAME="${SCRIPT_DIR}/dummy.java"
FORMAT_DIRS=(
    "${SCRIPT_DIR}/broadcast"
)

for dir in "${FORMAT_DIRS[@]}"; do
    if [[ -d "${dir}" ]]; then
        find "${dir}" -name "*.aidl" -print0 | while IFS= read -r -d '' f; do
            clang-format -assume-filename="${ASSUME_FILENAME}" < "${f}" > "${f}.tmp" && mv "${f}.tmp" "${f}"
        done
    fi
done

echo "Formatted all AIDL files in: ${FORMAT_DIRS[*]}"

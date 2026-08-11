#!/usr/bin/env bash
# Format all AIDL files under current/ using the .clang-format in this directory.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ASSUME_FILENAME="${SCRIPT_DIR}/dummy.java"

find "${SCRIPT_DIR}/." -name "*.aidl" | while IFS= read -r f; do
    clang-format -assume-filename="${ASSUME_FILENAME}" < "${f}" > "${f}.tmp" && mv "${f}.tmp" "${f}"
done

echo "Formatted all AIDL files."

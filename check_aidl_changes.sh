#!/usr/bin/env bash

#/**
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
# * SPDX-License-Identifier: Apache-2.0
# */

# AIDL Source Change Detection Tool
#
# This tool detects changes in AIDL source files by comparing SHA256 hashes.
# It helps ensure that the build system always uses the latest source files.
#
# Usage:
#     check_aidl_changes.sh MODULE SOURCE_DIR STABLE_DIR VERSION [--force] [--quiet]
#
#     MODULE       Module name (e.g., boot, deepsleep)
#     SOURCE_DIR   Source directory containing module/current/
#     STABLE_DIR   Stable directory containing stable/aidl/
#     VERSION      Version to check (e.g., current)
#     --force      Force copy regardless of hash check (optional)
#     --quiet      Only output on changes or errors (optional)
#
# Returns:
#     0 - No changes detected
#     1 - Changes detected (copy required)
#     2 - Error occurred

set -euo pipefail

# Parse arguments
if [ $# -lt 4 ]; then
    echo "Error: Missing required arguments" >&2
    echo "Usage: $0 MODULE SOURCE_DIR STABLE_DIR VERSION [--force] [--quiet]" >&2
    exit 2
fi

MODULE="$1"
SOURCE_DIR="$2"
STABLE_DIR="$3"
VERSION="$4"
FORCE_COPY=false
QUIET=false

# Parse optional flags
shift 4
while [ $# -gt 0 ]; do
    case "$1" in
        --force)
            FORCE_COPY=true
            shift
            ;;
        --quiet)
            QUIET=true
            shift
            ;;
        *)
            echo "Error: Unknown option: $1" >&2
            exit 2
            ;;
    esac
done

# Build paths
MODULE_SOURCE="${SOURCE_DIR}/${MODULE}/${VERSION}"
MODULE_STABLE="${STABLE_DIR}/aidl/${MODULE}/${VERSION}"
HASH_FILE="${STABLE_DIR}/.aidl_hashes"
CACHE_KEY="${MODULE}/${VERSION}"

# Function to output messages (respects --quiet)
log_info() {
    if [ "$QUIET" = false ]; then
        echo "$@"
    fi
}

log_error() {
    echo "$@" >&2
}

# Function to compute SHA256 hash of a file
compute_file_hash() {
    local file="$1"
    if [ -f "$file" ]; then
        sha256sum "$file" | awk '{print $1}'
    else
        echo ""
    fi
}

# Function to compute hashes for all AIDL files in a directory
compute_directory_hashes() {
    local dir="$1"
    local temp_file=$(mktemp)

    # Find all .aidl files, sort them, compute hashes
    if [ -d "$dir" ]; then
        find "$dir" -name "*.aidl" -type f | sort | while read -r aidl_file; do
            local rel_path=$(realpath --relative-to="$dir" "$aidl_file")
            local file_hash=$(compute_file_hash "$aidl_file")
            echo "${rel_path}|${file_hash}"
        done > "$temp_file"
    fi

    cat "$temp_file"
    rm -f "$temp_file"
}

# Function to load hash cache for a specific module
load_hash_cache() {
    local cache_key="$1"
    local temp_file=$(mktemp)

    if [ -f "$HASH_FILE" ]; then
        # Extract hashes for this specific module from the cache file
        # Cache format: module/version|relative_path|hash
        grep "^${cache_key}|" "$HASH_FILE" | cut -d'|' -f2- > "$temp_file" || true
    fi

    cat "$temp_file"
    rm -f "$temp_file"
}

# Function to save hash cache for a specific module
save_hash_cache() {
    local cache_key="$1"
    local new_hashes="$2"

    mkdir -p "$(dirname "$HASH_FILE")"

    # Create temporary file for new cache
    local temp_cache=$(mktemp)

    # If hash file exists, copy all entries except for this module
    if [ -f "$HASH_FILE" ]; then
        grep -v "^${cache_key}|" "$HASH_FILE" > "$temp_cache" || true
    fi

    # Add new hashes for this module
    echo "$new_hashes" | while read -r line; do
        [ -n "$line" ] && echo "${cache_key}|${line}"
    done >> "$temp_cache"

    # Replace old cache with new cache
    mv "$temp_cache" "$HASH_FILE"
}

# Check if source directory exists
if [ ! -d "$MODULE_SOURCE" ]; then
    log_error "Error: Source directory not found: $MODULE_SOURCE"
    exit 2
fi

# In force mode, always indicate copy needed
if [ "$FORCE_COPY" = true ]; then
    log_info "Force mode: Will copy $MODULE regardless of changes"
    exit 1
fi

# Check if stable directory exists (first time build)
if [ ! -d "$MODULE_STABLE" ]; then
    log_info "First build: $MODULE stable directory doesn't exist"
    # Save current hashes as baseline
    current_hashes=$(compute_directory_hashes "$MODULE_SOURCE")
    if [ -z "$current_hashes" ]; then
        log_error "Warning: No AIDL files found in $MODULE_SOURCE"
        exit 2
    fi
    save_hash_cache "$CACHE_KEY" "$current_hashes"
    exit 1
fi

# Compute current source hashes
current_hashes=$(compute_directory_hashes "$MODULE_SOURCE")

if [ -z "$current_hashes" ]; then
    log_error "Warning: No AIDL files found in $MODULE_SOURCE"
    exit 2
fi

# Load cached hashes
cached_hashes=$(load_hash_cache "$CACHE_KEY")

if [ -z "$cached_hashes" ]; then
    log_info "No hash cache for $MODULE: Will copy to establish baseline"
    save_hash_cache "$CACHE_KEY" "$current_hashes"
    exit 1
fi

# Compare hashes by creating associative arrays
declare -A current_map
declare -A cached_map
changed_files=()

# Populate current hash map
while IFS='|' read -r path hash; do
    [ -n "$path" ] && current_map["$path"]="$hash"
done <<< "$current_hashes"

# Populate cached hash map
while IFS='|' read -r path hash; do
    [ -n "$path" ] && cached_map["$path"]="$hash"
done <<< "$cached_hashes"

# Check for new or modified files
for path in "${!current_map[@]}"; do
    if [ -z "${cached_map[$path]:-}" ]; then
        changed_files+=("  NEW: $path")
    elif [ "${current_map[$path]}" != "${cached_map[$path]}" ]; then
        changed_files+=("  MODIFIED: $path")
    fi
done

# Check for deleted files
for path in "${!cached_map[@]}"; do
    if [ -z "${current_map[$path]:-}" ]; then
        changed_files+=("  DELETED: $path")
    fi
done

# Report results
if [ ${#changed_files[@]} -gt 0 ]; then
    log_info "Changes detected in $MODULE:"
    for change in "${changed_files[@]}"; do
        log_info "$change"
    done

    # CRITICAL: Remove generated code to force regeneration
    # CMake only generates if .cpp files don't exist, so we must delete them
    GENERATED_DIR="${STABLE_DIR}/generated/${MODULE}/${VERSION}"
    if [ -d "$GENERATED_DIR" ]; then
        log_info "Removing stale generated code: $GENERATED_DIR"
        rm -rf "$GENERATED_DIR"
    fi

    # Update cache with new hashes
    save_hash_cache "$CACHE_KEY" "$current_hashes"
    exit 1
fi

log_info "No changes in $MODULE - using cached AIDL files"
exit 0

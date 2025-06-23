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
# *
# http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
#* ******************************************************************************

# --- Global Variables ---
MY_PATH="$(realpath ${BASH_SOURCE[0]})"
MY_DIR="$(dirname ${MY_PATH})"

# --- Configuration ---
# The base path relative to where this script is executed
# If your source directories are e.g., ../../some_dir/A, ../../some_dir/B
# then SOURCE_BASE should be set to "../../some_dir"
SOURCE_BASE_PATH="${MY_DIR}/../../"

# The destination path where the directories will be copied
# Make sure this directory exists or rsync might create it in an unexpected location
# Example: "/path/to/your/docs/temporary_aidl_files"
DESTINATION_PATH="${MY_DIR}/../../docs/src_link" # Corrected to be relative to MY_DIR/../../

# List of directory names to rsync.
# These names will be appended to SOURCE_BASE_PATH to form the source path,
# and also appended to DESTINATION_PATH to form the destination path.
# Example: If 'my_module' is in this list, rsync will try to sync
#  '../../my_module/' to '/path/to/your/docs/temporary_aidl_files/my_module/'
declare -a DIR_LIST=(
"audiodecoder"
"audiosink"
"avbuffer"
"avclock"
"boot"
"broadcast"
"cdm"
"cec"
"common"
"deepsleep"
"deviceinfo"
"flash"
"hdmiinput"
"hdmioutput"
"indicator"
"panel"
"planecontrol"
"videodecoder"
"videosink"
)

# --- Rsync Options (Initial) ---
# Default rsync options for normal (non-quiet) mode
# -a: archive mode (preserves permissions, timestamps, owner, group, symlinks, recursive)
# -z: compress file data during the transfer
# -v: verbose output (will be overridden in quiet mode)
# -q: quiet (will be added in quiet mode)
# --progress: show progress during transfer (will be removed in quiet mode)
DEFAULT_RSYNC_OPTIONS="-azv --progress"

# --- Script Control Flags ---
QUIET_MODE=0 # 0 for normal (verbose), 1 for quiet

# --- Functions for Conditional Output ---
# This function prints messages only if QUIET_MODE is not enabled
print_info() {
    if [ "${QUIET_MODE}" -eq 0 ]; then
        echo "[INFO] $@"
    fi
}

# This function always prints warnings/errors
print_warning() {
    echo "[WARNING] $@" >&2 # Output to stderr
}

print_error() {
    echo "[ERROR] $@" >&2 # Output to stderr
}

# --- Argument Parsing ---
# Loop through arguments to check for --quiet
TEMP_ARGS=()
for arg in "$@"; do
    case "${arg}" in
        --quiet)
            QUIET_MODE=1
            ;;
        *)
            TEMP_ARGS+=("${arg}") # Store other arguments if any (though not expected for this script's current design)
            ;;
    esac
done
# Reassign positional parameters if you were processing other arguments
# set -- "${TEMP_ARGS[@]}"


# --- Set Final Rsync Options based on QUIET_MODE ---
if [ "${QUIET_MODE}" -eq 1 ]; then
    RSYNC_OPTIONS="-azq" # Quiet mode: -a (archive), -z (compress), -q (quiet)
    # Removing -v and --progress for quiet mode
else
    RSYNC_OPTIONS="${DEFAULT_RSYNC_OPTIONS}" # Normal mode
fi

# --- Main Script Logic ---

print_info "Starting rsync operations..."
print_info "Source Base Path: ${SOURCE_BASE_PATH}"
print_info "Destination Path: ${DESTINATION_PATH}"
print_info "Directories to sync: ${DIR_LIST[*]}"
print_info "Rsync Options: ${RSYNC_OPTIONS}"
print_info ""

# Check if the destination path exists
if [ ! -d "${DESTINATION_PATH}" ]; then
    print_warning "Destination path '${DESTINATION_PATH}' does not exist. Creating it."
    mkdir -p "${DESTINATION_PATH}" || { print_error "Could not create destination directory. Exiting."; exit 1; }
fi

# Loop through each directory in the list
for dir_name in "${DIR_LIST[@]}"; do
    SOURCE_DIR="${SOURCE_BASE_PATH}${dir_name}"
    DEST_SUB_DIR="${DESTINATION_PATH}/${dir_name}"

    if [ "${QUIET_MODE}" -eq 0 ]; then
        echo "--------------------------------------------------"
        echo "Attempting to sync:"
        echo "  From: ${SOURCE_DIR}/"
        echo "  To:   ${DEST_SUB_DIR}/"
        echo "--------------------------------------------------"
    else
        # In quiet mode, just a single line per sync operation
        echo "Syncing '${dir_name}'..."
    fi

    # Check if the source directory exists
    if [ ! -d "${SOURCE_DIR}" ]; then
        print_error "Source directory '${SOURCE_DIR}' does not exist. Skipping this directory."
        continue # Move to the next directory in the list
    fi

    # Create the target subdirectory in the destination if it doesn't exist
    mkdir -p "${DEST_SUB_DIR}" || { print_error "Could not create subdirectory '${DEST_SUB_DIR}'. Skipping."; continue; }

    # Perform the rsync operation
    rsync ${RSYNC_OPTIONS} "${SOURCE_DIR}/" "${DEST_SUB_DIR}/"

    if [ $? -eq 0 ]; then
        print_info "SUCCESS: '${dir_name}' synced successfully."
    else
        print_error "FAILED: '${dir_name}' sync failed. See above errors for details."
        # Optionally, you can exit here if a single failure should stop the whole script
        # exit 1
    fi
    print_info ""
done

print_info "All rsync operations attempted."
print_info "Done."

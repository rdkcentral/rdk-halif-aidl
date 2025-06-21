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

# --- Configuration ---
# The base path relative to where this script is executed
# If your source directories are e.g., ../../some_dir/A, ../../some_dir/B
# then SOURCE_BASE should be set to "../../some_dir"
MY_PATH="$(realpath ${BASH_SOURCE[0]})"
MY_DIR="$(dirname ${MY_PATH})"
SOURCE_BASE_PATH="${MY_DIR}/../.."

# The destination path where the directories will be copied
# Make sure this directory exists or rsync might create it in an unexpected location
# Example: "/path/to/your/docs/temporary_aidl_files"
DESTINATION_PATH=${SOURCE_BASE_PATH}/docs/src_link

# List of directory names to rsync.
# These names will be appended to SOURCE_BASE_PATH to form the source path,
# and also appended to DESTINATION_PATH to form the destination path.
# Example: If 'my_module' is in this list, rsync will try to sync
#          '../../my_module/' to '/path/to/your/docs/temporary_aidl_files/my_module/'
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
# If your 'dir' is simply a top-level directory directly under ../../, you can list it like:
# declare -a DIR_LIST=(
#     "my_source_module_1"
#     "another_module"
# )

# Rsync options
# -a: archive mode (preserves permissions, timestamps, owner, group, symlinks, recursive)
# -v: verbose output
# --delete: deletes extraneous files from dest dir (if they don't exist in source) - USE WITH CAUTION!
#           Remove if you only want to add, not synchronize removals.
# --progress: show progress during transfer
RSYNC_OPTIONS="-azv --progress" # Consider adding --delete if you want a true sync

# --- Script Logic ---

echo "Starting rsync operations..."
echo "Source Base Path: ${SOURCE_BASE_PATH}"
echo "Destination Path: ${DESTINATION_PATH}"
echo "Directories to sync: ${DIR_LIST[*]}"
echo "Rsync Options: ${RSYNC_OPTIONS}"
echo ""

# Check if the destination path exists
if [ ! -d "${DESTINATION_PATH}" ]; then
    echo "WARNING: Destination path '${DESTINATION_PATH}' does not exist. Creating it."
    mkdir -p "${DESTINATION_PATH}" || { echo "ERROR: Could not create destination directory. Exiting."; exit 1; }
fi

# Loop through each directory in the list
for dir_name in "${DIR_LIST[@]}"; do
    SOURCE_DIR="${SOURCE_BASE_PATH}${dir_name}"
    DEST_SUB_DIR="${DESTINATION_PATH}/${dir_name}"

    echo "--------------------------------------------------"
    echo "Attempting to sync:"
    echo "  From: ${SOURCE_DIR}/"
    echo "  To:   ${DEST_SUB_DIR}/"
    echo "--------------------------------------------------"

    # Check if the source directory exists
    if [ ! -d "${SOURCE_DIR}" ]; then
        echo "ERROR: Source directory '${SOURCE_DIR}' does not exist. Skipping this directory."
        continue # Move to the next directory in the list
    fi

    # Create the target subdirectory in the destination if it doesn't exist
    mkdir -p "${DEST_SUB_DIR}" || { echo "ERROR: Could not create subdirectory '${DEST_SUB_DIR}'. Skipping."; continue; }

    # Perform the rsync operation
    # The trailing slash on SOURCE_DIR/ is important:
    # it copies the *contents* of SOURCE_DIR into DEST_SUB_DIR,
    # rather than copying SOURCE_DIR itself as a subdirectory within DEST_SUB_DIR.
    rsync ${RSYNC_OPTIONS} "${SOURCE_DIR}/" "${DEST_SUB_DIR}/"

    if [ $? -eq 0 ]; then
        echo "SUCCESS: '${dir_name}' synced successfully."
    else
        echo "FAILED: '${dir_name}' sync failed. See above errors for details."
        # Optionally, you can exit here if a single failure should stop the whole script
        # exit 1
    fi
    echo ""
done

echo "All rsync operations attempted."
echo "Done."
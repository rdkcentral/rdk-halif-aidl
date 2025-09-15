#!/usr/bin/env bash

#/**
# * Copyright 2024 Comcast Cable Communications Management, LLC
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

# Define repository and installation paths
MY_PATH="$(realpath ${BASH_SOURCE[0]})"
MY_DIR="$(dirname ${MY_PATH})"
REPO_URL="https://github.com/rdkcentral/linux_binder_idl"
REPO_BRANCH="feature/CPESP-5462_AIDL_Versioning_for_RDK-E_HAL"
INSTALL_DIR="$MY_DIR/build-tools"
CLONE_DIR="${BUILD_DIR}"
BINDER_BIN_DIR="$INSTALL_DIR/linux_binder_idl"
PROFILE_FILE="$HOME/.bashrc"
SCRIPT_FILE="$BASH_SOURCE"

# Function to check if the repository is already cloned
clone_repo() 
{
    if [ -d "$INSTALL_DIR" ]; then
        echo "Binder tools already cloned at $INSTALL_DIR. Skipping clone."
    else
        echo "Cloning Binder tools repository..."
        mkdir -p ${INSTALL_DIR}
        git clone -b ${REPO_BRANCH} "$REPO_URL" "$INSTALL_DIR/linux_binder_idl"
    fi
}

# Function to check if the binary path is already in PATH
setup_path() 
{
    if [[ ":$PATH:" == *":$BINDER_BIN_DIR:"* ]]; then
        echo "Binder tools path is already set up."
    else
        echo "Binder tools path is not in the environment PATH."
        echo "To add it permanently, run the following command:"
        echo "    echo 'export PATH="$BINDER_BIN_DIR:\$PATH"' >> "$PROFILE_FILE""
        echo "Then restart your terminal or run 'source $PROFILE_FILE' to apply changes."
    fi
}

# Function to verify installation
verify_installation() 
{
    if command -v binder &> /dev/null; then
        echo "Binder tools installation successful."
    else
        echo "Installation failed or binder command not found. Ensure the path is correctly set."
    fi
}

# Function to check if script was sourced
check_sourced() 
{
    if [[ "$SCRIPT_FILE" == "$0" ]]; then
        echo "Warning: This script should be sourced. Run it using:"
        echo "    source $SCRIPT_FILE"
        return 1
    fi
}

# Execute functions
check_sourced
clone_repo
setup_path
verify_installation

echo "Binder tools setup complete."

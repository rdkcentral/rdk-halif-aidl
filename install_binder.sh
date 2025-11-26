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
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
#** ******************************************************************************

# Define repository and installation paths
MY_PATH="$(realpath ${BASH_SOURCE[0]})"
MY_DIR="$(dirname ${MY_PATH})"
REPO_URL="https://github.com/rdkcentral/linux_binder_idl"
INSTALL_DIR="$MY_DIR/build-tools"
CLONE_DIR="${BUILD_DIR}"
BINDER_BIN_DIR="$INSTALL_DIR/linux_binder_idl"
PROFILE_FILE="$HOME/.bashrc"
SCRIPT_FILE="$BASH_SOURCE"


# Minimal ANSI colour vars (why: standard, portable)
RED="\033[0;31m"
YELLOW="\033[1;33m"
GREEN="\033[0;32m"
RESET="\033[0m"

# Function to check if the repository is already cloned
clone_repo() 
{
    if [ -d "$INSTALL_DIR" ]; then
        echo "Binder tools already cloned at $INSTALL_DIR. Skipping clone."
    else
        echo "Cloning Binder tools repository..."
        mkdir -p ${INSTALL_DIR}
        git clone "$REPO_URL" "$INSTALL_DIR/linux_binder_idl"
    fi
}

# Detect shell & profile file (why: correct file for correct user shell)
detect_profile() {
    if [ -n "$ZSH_VERSION" ]; then
        echo "$HOME/.zshrc"
    elif [ -n "$BASH_VERSION" ]; then
        echo "$HOME/.bashrc"
    else
        echo "$HOME/.profile"
    fi
}

PROFILE_FILE="$(detect_profile)"
EXPORT_LINE="export PATH=\"$BINDER_BIN_DIR:\$PATH\""

setup_path_auto() {
    mkdir -p "$BINDER_BIN_DIR"

    if grep -Fxq "$EXPORT_LINE" "$PROFILE_FILE"; then
        echo -e "${GREEN}Binder tool path is already in PATH.${RESET}"
        return
    fi

    echo -e "${YELLOW}Adding Binder tool path to PATH automatically...${RESET}"
    {
        echo ""
        echo "# Added by Binder setup script"
        echo "$EXPORT_LINE"
    } >> "$PROFILE_FILE"

    # Apply immediately (why: user doesn’t need to restart shell)
    # shellcheck disable=SC1090
    source "$PROFILE_FILE"

    echo -e "${GREEN}Binder tool path added successfully!${RESET}"
    echo -e "${YELLOW}Profile updated: $PROFILE_FILE${RESET}"
}

# Function to verify installation
verify_installation() 
{
    if command -v aidl_ops &> /dev/null; then
        echo "Binder tools installation successful."
    else
        echo "Installation failed or aidl_ops tool not found. Ensure the path is correctly set."
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
setup_path_auto
verify_installation

echo "Binder tools setup complete."

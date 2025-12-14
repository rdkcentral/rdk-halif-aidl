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

# Define paths relative to this script location
MY_PATH="$(realpath "${BASH_SOURCE[0]}")"
MY_DIR="$(dirname "${MY_PATH}")"
REPO_URL="https://github.com/rdkcentral/linux_binder_idl"

# Where we put the tools
INSTALL_DIR="$MY_DIR/build-tools"
BINDER_REPO_DIR="$INSTALL_DIR/linux_binder_idl"
BINDER_BUILD_SCRIPT="$BINDER_REPO_DIR/build-linux-binder-aidl.sh"
STAMP_FILE="$BINDER_REPO_DIR/.installed_successfully"

<<<<<<< Updated upstream

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
=======
# EXPORT THIS for other scripts to use
export BINDER_TOOLCHAIN_ROOT="$BINDER_REPO_DIR"

# ------------------------------------------------------------------------------
# 1. CLONE
# ------------------------------------------------------------------------------
clone_repo() {
    if [ -d "$BINDER_REPO_DIR" ]; then
        # Repo exists, but check if it's empty or valid? 
        # For now assume existence is enough.
        return 0
>>>>>>> Stashed changes
    fi

    echo "📦 Cloning Binder tools repository..."
    mkdir -p "$INSTALL_DIR"
    git clone "$REPO_URL" "$BINDER_REPO_DIR" || return 1
}

<<<<<<< Updated upstream
# Detect shell & profile file (why: correct file for correct user shell)
detect_profile() {
    if [ -n "$ZSH_VERSION" ]; then
        echo "$HOME/.zshrc"
    elif [ -n "$BASH_VERSION" ]; then
        echo "$HOME/.bashrc"
    else
        echo "$HOME/.profile"
=======
# ------------------------------------------------------------------------------
# 2. BUILD (Idempotent)
# ------------------------------------------------------------------------------
build_tools() {
    # FAST EXIT: If stamp exists, we are done.
    if [ -f "$STAMP_FILE" ]; then
        return 0
>>>>>>> Stashed changes
    fi

<<<<<<< Updated upstream
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
=======
    if [ ! -f "$BINDER_BUILD_SCRIPT" ]; then
        echo "❌ Error: Build script not found at $BINDER_BUILD_SCRIPT"
        return 1
>>>>>>> Stashed changes
    fi

    echo "🚀 Building Linux Binder Toolchain (This runs once)..."
    
    # Execute the build script in a subshell to protect current directory context
    (cd "$BINDER_REPO_DIR" && /bin/bash "$BINDER_BUILD_SCRIPT")
    
    if [ $? -eq 0 ]; then
        touch "$STAMP_FILE"
        echo "✅ Toolchain build complete."
    else
        echo "❌ Toolchain build failed."
        return 1
    fi
}

<<<<<<< Updated upstream
# Execute functions
check_sourced
clone_repo
setup_path_auto
verify_installation
=======
# ------------------------------------------------------------------------------
# 3. SETUP PATH (Exports to current shell)
# ------------------------------------------------------------------------------
setup_path() {
    LOCAL_BIN="$BINDER_REPO_DIR/local/bin"
    if [[ ":$PATH:" != *":$LOCAL_BIN:"* ]]; then
        export PATH="$LOCAL_BIN:$PATH"
    fi
}
>>>>>>> Stashed changes

# ------------------------------------------------------------------------------
# MAIN EXECUTION
# ------------------------------------------------------------------------------
clone_repo || return 1
build_tools || return 1
setup_path
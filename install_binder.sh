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

# Show help if requested (only when executed, not sourced)
if [[ "${1:-}" == "--help" ]] || [[ "${1:-}" == "-h" ]]; then
    cat << EOF
Usage: ./install_binder.sh
   or: source ./install_binder.sh

Install and setup the Android Binder toolchain for AIDL development.

Description:
  This script:
  1. Clones the linux_binder_idl repository (if not present)
  2. Builds the AIDL compiler tools (aidl, aidl-cpp)
  3. Builds the target Binder libraries (libbinder.so, etc.)
  4. Adds tools to PATH for current shell
  5. Exports BINDER_TOOLCHAIN_ROOT environment variable

Usage:
  Execute directly:  ./install_binder.sh
  Source in shell:   source ./install_binder.sh

  When sourced, PATH is updated in your current shell.
  When executed, you must source it or restart your shell.

Output:
  Host tools:    build-tools/linux_binder_idl/out/host/bin/
  Target libs:   build-tools/linux_binder_idl/out/target/lib/
  Headers:       build-tools/linux_binder_idl/out/target/include/

Environment:
  BINDER_TOOLCHAIN_ROOT  Set to toolchain directory
  PATH                   Updated to include host tools

Examples:
  ./install_binder.sh           # Install toolchain
  source ./install_binder.sh    # Install and update current shell

EOF
    exit 0
fi

# Define paths relative to this script location
MY_PATH="$(realpath "${BASH_SOURCE[0]}")"
MY_DIR="$(dirname "${MY_PATH}")"
REPO_URL="https://github.com/rdkcentral/linux_binder_idl"

# Where we put the tools
INSTALL_DIR="$MY_DIR/build-tools"
BINDER_REPO_DIR="$INSTALL_DIR/linux_binder_idl"
BINDER_HOST_BUILD_SCRIPT="$BINDER_REPO_DIR/build-aidl-generator-tool.sh"
BINDER_TARGET_BUILD_SCRIPT="$BINDER_REPO_DIR/build-linux-binder-aidl.sh"
STAMP_FILE="$BINDER_REPO_DIR/.installed_successfully"

# EXPORT THIS for other scripts to use
export BINDER_TOOLCHAIN_ROOT="$BINDER_REPO_DIR"

# ------------------------------------------------------------------------------
# 1. CLONE
# ------------------------------------------------------------------------------
clone_repo() {
    if [ -d "$BINDER_REPO_DIR" ]; then
        echo "📦 Binder tools already cloned at $BINDER_REPO_DIR"
        return 0
    fi

    echo "📦 Cloning Binder tools repository..."
    mkdir -p "$INSTALL_DIR"
    git clone "$REPO_URL" "$BINDER_REPO_DIR" || return 1
}

# ------------------------------------------------------------------------------
# 2. BUILD (Idempotent)
# ------------------------------------------------------------------------------
build_tools() {
    # FAST EXIT: If stamp exists, we are done.
    if [ -f "$STAMP_FILE" ]; then
        echo "✅ Toolchain already built (stamp file exists)"
        return 0
    fi

    if [ ! -f "$BINDER_HOST_BUILD_SCRIPT" ]; then
        echo "❌ Error: Build script not found at $BINDER_HOST_BUILD_SCRIPT"
        return 1
    fi

    echo "🚀 Building Linux Binder Toolchain (host tools only)..."
    echo "   This builds the AIDL compiler for code generation on the build machine."
    echo "   Target binder libraries are built separately per platform."
    
    # Execute the host build script in a subshell
    (cd "$BINDER_REPO_DIR" && /bin/bash "$BINDER_HOST_BUILD_SCRIPT")
    
    if [ $? -eq 0 ]; then
        touch "$STAMP_FILE"
        echo "✅ Toolchain build complete."
    else
        echo "❌ Toolchain build failed."
        return 1
    fi
}

# ------------------------------------------------------------------------------
# 3. SETUP PATH (Exports to current shell)
# ------------------------------------------------------------------------------
setup_path() {
    HOST_BIN="$BINDER_REPO_DIR/out/host/bin"
    if [ ! -d "$HOST_BIN" ]; then
        echo "⚠️  Warning: Host bin directory not found: $HOST_BIN"
        return 1
    fi
    
    if [[ ":$PATH:" != *":$HOST_BIN:"* ]]; then
        export PATH="$HOST_BIN:$PATH"
        echo "✅ Added $HOST_BIN to PATH"
    fi
}

# ------------------------------------------------------------------------------
# MAIN EXECUTION
# ------------------------------------------------------------------------------
clone_repo || exit 1
build_tools || exit 1
setup_path

echo "✅ Binder toolchain setup complete"

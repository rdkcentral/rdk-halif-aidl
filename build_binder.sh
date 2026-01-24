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
Usage: ./build_binder.sh [clean]
   or: source ./build_binder.sh

Build and install the Android Binder SDK for RDK HAL AIDL modules.

Description:
  This script (Stage 1 of two-stage build):
  1. Clones the linux_binder_idl repository (if not present)
  2. Builds and installs Binder SDK to out/target/:
     - Binder runtime libraries (libbinder, libutils, etc.)
     - AIDL compiler tools (aidl, aidl-cpp)
     - Headers for development
  3. Creates .sdk_ready marker file
  4. Adds tools to PATH for current shell

Usage:
  Execute directly:  ./build_binder.sh [clean]
  Source in shell:   source ./build_binder.sh

  clean - Force rebuild by removing existing SDK and build directories

Output (Stage 1 - Binder SDK):
  out/target/bin/       - servicemanager (runtime)
  out/target/lib/       - Binder runtime libraries
  out/build/include/    - Binder headers (build-time only)
  out/target/.sdk_ready - Marker indicating SDK is ready

Environment Variables (optional overrides):
  BINDER_VERSION        - Git tag/branch/commit to checkout
                          (default: 2.0.0)
  BINDER_INSTALL_DIR    - Where to clone linux_binder_idl
                          (default: build-tools/)
  BINDER_SOURCE_DIR     - Existing linux_binder_idl location
                          (default: build-tools/linux_binder_idl)
  BINDER_BUILD_DIR      - CMake build directory
                          (default: build/binder)
  BINDER_SDK_DIR        - Final SDK installation directory
                          (default: out/target)

Environment (exported):
  BINDER_TOOLCHAIN_ROOT  Set to toolchain directory
  PATH                   Updated to include AIDL compiler tools

Examples:
  ./build_binder.sh           # Build Binder SDK (version 2.0.0)
  ./build_binder.sh clean     # Force rebuild
  source ./build_binder.sh    # Build and update current shell

  # Pin to different version:
  BINDER_VERSION=main ./build_binder.sh

  # Yocto/BitBake override example:
  BINDER_SDK_DIR=/path/to/sysroot/usr ./build_binder.sh

  # Use existing linux_binder_idl clone:
  BINDER_SOURCE_DIR=/path/to/linux_binder_idl ./build_binder.sh

Next Steps:
  Build HAL modules with: ./build_module.sh <module>

EOF
    exit 0
fi

# Define paths relative to this script location
MY_PATH="$(realpath "${BASH_SOURCE[0]}")"
MY_DIR="$(dirname "${MY_PATH}")"
REPO_URL="https://github.com/rdkcentral/linux_binder_idl"
BINDER_VERSION="${BINDER_VERSION:-2.0.0}"  # Default to 2.0.0, override with tag/commit/branch

# Parse arguments
CLEAN=false
if [ "${1:-}" = "clean" ]; then
    CLEAN=true
fi

# Where we put the tools - allow environment overrides
INSTALL_DIR="${BINDER_INSTALL_DIR:-$MY_DIR/build-tools}"
BINDER_REPO_DIR="${BINDER_SOURCE_DIR:-$INSTALL_DIR/linux_binder_idl}"
BINDER_BUILD_DIR="${BINDER_BUILD_DIR:-$MY_DIR/build/binder}"
SDK_INSTALL_DIR="${BINDER_SDK_DIR:-$MY_DIR/out/target}"
SDK_INCLUDE_DIR="${BINDER_SDK_INCLUDE_DIR:-$MY_DIR/out/build}"

# EXPORT THIS for other scripts to use
export BINDER_TOOLCHAIN_ROOT="$BINDER_REPO_DIR"

echo "========================================"
echo "  RDK HAL AIDL - Binder SDK Build"
echo "========================================"
echo "Version: $BINDER_VERSION"
echo "Source:  $BINDER_REPO_DIR"
echo "Build:   $BINDER_BUILD_DIR"
echo "Install (runtime): $SDK_INSTALL_DIR"
echo "Install (headers): $SDK_INCLUDE_DIR"
echo "========================================"
echo ""

# ------------------------------------------------------------------------------
# 1. CLONE
# ------------------------------------------------------------------------------
clone_repo() {
    if [ -d "$BINDER_REPO_DIR" ]; then
        echo "✓ Binder source already cloned at $BINDER_REPO_DIR"

        # Show current branch/commit for information only
        if [ "$CLEAN" != true ]; then
            cd "$BINDER_REPO_DIR"
            CURRENT_REF=$(git rev-parse --abbrev-ref HEAD 2>/dev/null || git rev-parse --short HEAD 2>/dev/null)
            echo "   Current: $CURRENT_REF"
            cd - > /dev/null
        fi

        return 0
    fi

    echo "Cloning Binder toolchain repository (version: $BINDER_VERSION)..."
    mkdir -p "$INSTALL_DIR"

    # Clone repository
    git clone "$REPO_URL" "$BINDER_REPO_DIR" || return 1

    # Checkout requested version (branch, tag, or commit)
    cd "$BINDER_REPO_DIR"
    if git checkout "$BINDER_VERSION" 2>/dev/null; then
        echo "✓ Cloned and checked out version $BINDER_VERSION"
    else
        echo "⚠️  Version/branch '$BINDER_VERSION' not found, using default branch"
        echo "   This is normal for development versions"
    fi
    cd - > /dev/null
}

# ------------------------------------------------------------------------------
# 2. CLEAN (if requested)
# ------------------------------------------------------------------------------
clean_build() {
    if [ "$CLEAN" = true ]; then
        echo "Cleaning previous build..."

        # Clean toolchain build artifacts if toolchain exists
        if [ -d "$BINDER_REPO_DIR" ] && [ -f "$BINDER_REPO_DIR/build-linux-binder-aidl.sh" ]; then
            echo "  Cleaning toolchain build artifacts..."
            cd "$BINDER_REPO_DIR"
            bash build-linux-binder-aidl.sh --clean 2>/dev/null || true
            cd - > /dev/null
            echo "  ✓ Toolchain cleaned"
        fi

        # Clean SDK installation directories
        rm -rf "$BINDER_BUILD_DIR" "$SDK_INSTALL_DIR" "$SDK_INCLUDE_DIR"
        echo "✓ Cleaned"
        echo ""
        echo "Removed:"
        echo "  - $BINDER_BUILD_DIR"
        echo "  - $SDK_INSTALL_DIR"
        echo "  - $SDK_INCLUDE_DIR"
        echo ""
        echo "✅ Clean complete"
        exit 0
    fi
}

# ------------------------------------------------------------------------------
# 3. BUILD SDK (Using CMake)
# ------------------------------------------------------------------------------
build_sdk() {
    # Check if SDK already exists
    if [ -f "$SDK_INSTALL_DIR/.sdk_ready" ] && [ "$CLEAN" != true ]; then
        echo "✓ Binder SDK already built at $SDK_INSTALL_DIR"
        echo ""
        echo "To rebuild, run: ./build_binder.sh clean"
        echo ""
        return 0
    fi

    if [ ! -d "$BINDER_REPO_DIR" ]; then
        echo "❌ Error: Binder source not found at $BINDER_REPO_DIR"
        return 1
    fi

    echo "Configuring binder SDK..."
    cmake -S "$BINDER_REPO_DIR" -B "$BINDER_BUILD_DIR" \
        -DCMAKE_INSTALL_PREFIX="$SDK_INSTALL_DIR" \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_HOST_AIDL=ON

    if [ $? -ne 0 ]; then
        echo ""
        echo "❌ ERROR: CMake configuration failed"
        return 1
    fi

    echo ""
    echo "Building binder SDK..."
    cmake --build "$BINDER_BUILD_DIR" -j$(nproc)

    if [ $? -ne 0 ]; then
        echo ""
        echo "❌ ERROR: Build failed"
        return 1
    fi

    echo ""
    echo "Installing binder SDK to $SDK_INSTALL_DIR..."
    cmake --install "$BINDER_BUILD_DIR"

    if [ $? -ne 0 ]; then
        echo ""
        echo "❌ ERROR: Installation failed"
        return 1
    fi

    echo ""
    echo "Organizing SDK structure..."

    # Move libraries to binder subdirectory in target
    if [ -d "$SDK_INSTALL_DIR/lib" ] && [ ! -d "$SDK_INSTALL_DIR/lib/binder" ]; then
        mkdir -p "$SDK_INSTALL_DIR/lib/binder"
        mv "$SDK_INSTALL_DIR"/lib/*.so* "$SDK_INSTALL_DIR/lib/binder/" 2>/dev/null || true
    fi

    # Move headers to out/build/include (separate from runtime)
    if [ -d "$SDK_INSTALL_DIR/include" ]; then
        mkdir -p "$SDK_INCLUDE_DIR/include/binder_sdk"
        # Move all header directories to build location
        find "$SDK_INSTALL_DIR/include" -mindepth 1 -maxdepth 1 -type d \
            -exec mv {} "$SDK_INCLUDE_DIR/include/binder_sdk/" \; 2>/dev/null || true
        # Also handle any loose header files at top level
        find "$SDK_INSTALL_DIR/include" -maxdepth 1 -type f -name "*.h" \
            -exec mv {} "$SDK_INCLUDE_DIR/include/binder_sdk/" \; 2>/dev/null || true
        # Remove empty include directory from target
        rmdir "$SDK_INSTALL_DIR/include" 2>/dev/null || true
    fi

    # Create halif placeholder directories
    mkdir -p "$SDK_INSTALL_DIR/lib/halif"

    # Create marker files
    touch "$SDK_INSTALL_DIR/.sdk_ready"
    touch "$SDK_INCLUDE_DIR/.sdk_ready"

    echo "✓ SDK structure organized"
    echo ""
    echo "✓ Binder SDK build complete"
}

# ------------------------------------------------------------------------------
# 4. SETUP PATH (Exports to current shell)
# ------------------------------------------------------------------------------
setup_path() {
    AIDL_BIN="$SDK_INSTALL_DIR/bin"
    if [ ! -d "$AIDL_BIN" ]; then
        echo "⚠️  Warning: AIDL bin directory not found: $AIDL_BIN"
        return 1
    fi

    if [[ ":$PATH:" != *":$AIDL_BIN:"* ]]; then
        export PATH="$AIDL_BIN:$PATH"
        echo "✓ Added $AIDL_BIN to PATH"
    fi
}

# ------------------------------------------------------------------------------
# MAIN EXECUTION
# ------------------------------------------------------------------------------
clone_repo || exit 1
clean_build
build_sdk || exit 1
setup_path

echo ""
echo "========================================"
echo "  ✓ Binder SDK Ready"
echo "========================================"
echo ""
echo "SDK installed to: $SDK_INSTALL_DIR"
echo ""
echo "Structure:"
echo "  Binder libraries:    $(find $SDK_INSTALL_DIR/lib/binder -name '*.so' 2>/dev/null | wc -l) files"
echo "  Binder headers:      $(find $SDK_INSTALL_DIR/include/binder_sdk -name '*.h' 2>/dev/null | wc -l) files"
echo "  AIDL compiler:       $(find $SDK_INSTALL_DIR/bin -type f -executable 2>/dev/null | wc -l) files"
echo "  HAL libraries:       (populated by build_module.sh)"
echo "  HAL headers:         (populated by build_module.sh)"
echo ""
echo "Next step: Build HAL modules"
echo "  Example: ./build_module.sh boot"
echo ""

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

# Helper script to update AIDL APIs and build interface libraries.
# 
# This script:
#   1. Runs aidl_ops -u to copy {module}/current/*.aidl → stable/aidl/{module}/current/
#   2. Generates C++ code → stable/generated/{module}/current/
#   3. Builds libraries from generated code
#
# Usage:
#   ./build_interfaces.sh [module]
#       module: "all" (default) or specific module name (e.g., "boot", "videodecoder")
#
# Examples:
#   ./build_interfaces.sh              # Update API and build all modules
#   ./build_interfaces.sh all          # Update API and build all modules
#   ./build_interfaces.sh videodecoder # Update API and build only videodecoder

set -euo pipefail

# Show help if requested
if [[ "${1:-}" == "--help" ]] || [[ "${1:-}" == "-h" ]]; then
    cat << EOF
Usage: ./build_interfaces.sh [module] [--version <ver>]

Build AIDL interface libraries.

Arguments:
  module     Module to build (default: all)
             - "all"  : Build all modules
             - <name> : Build specific module (e.g., boot, videodecoder)

Options:
  --version <ver>    Version to build (default: current)
                     - "current" : Working development version
                     - "v1"      : Frozen version 1
                     - "v2"      : Frozen version 2, etc.

  --help, -h         Show this help message

Description:
  This script performs a complete build:
  1. Updates AIDL APIs (copies module/current → stable/<module>/<version>/)
  2. Generates C++ code → stable/generated/<module>/<version>/
  3. Builds shared libraries (.so) and headers (.h)
  4. Outputs everything to out/ directory ready for deployment

Build Configuration:
  Use CC/CXX environment variables to control compiler and flags:
    CC=gcc CXX=g++ ./build_interfaces.sh <module>              # Release (default)
    CC="gcc -g" CXX="g++ -g" ./build_interfaces.sh <module>   # Debug build
    CC=arm-linux-gnueabihf-gcc ./build_interfaces.sh <module>  # Cross-compile

Examples:
  ./build_interfaces.sh                        # Build all modules
  ./build_interfaces.sh boot                   # Build boot module
  ./build_interfaces.sh boot --version current # Explicit version
  ./build_interfaces.sh videodecoder --version v1  # Build frozen v1

Output Structure:
  stable/
    <module>/<version>/<module>-api/    # AIDL source definitions
    generated/<module>/<version>/       # Generated C++ code
  out/
    include/                            # All headers for target
    lib/                                # All .so files for target

Workflow:
  1. Edit:   vim <module>/current/com/rdk/hal/<module>/*.aidl
  2. Build:  ./build_interfaces.sh <module>
  3. Test:   (copy out/ to target device)
  4. Freeze: ./freeze_interface.sh <module>

EOF
    exit 0
fi

# Ensure binder toolchain is installed and PATH is set
if [ -f "./install_binder.sh" ]; then
    source ./install_binder.sh
    if [ $? -ne 0 ]; then
        echo "❌ Critical Error: Failed to setup Binder Toolchain."
        exit 1
    fi
else
    echo "❌ Error: install_binder.sh not found in root."
    exit 1
fi

# Parse arguments
MODULE="${1:-all}"
VERSION="current"

shift || true  # Remove first argument
while [[ $# -gt 0 ]]; do
    case "$1" in
        --version)
            VERSION="$2"
            shift 2
            ;;
        *)
            echo "❌ Unknown option: $1"
            echo "Run './build_interfaces.sh --help' for usage."
            exit 1
            ;;
    esac
done

ROOT_DIR=$(pwd)
STABLE_DIR="${ROOT_DIR}/stable"
OUT_DIR="${ROOT_DIR}/out"              # Final output: headers + libs for deployment
BUILD_DIR="${ROOT_DIR}/build/${VERSION}"  # CMake build directory
SDK_INCLUDE_DIR="${BUILD_DIR}/sdk/include"
SDK_LIB_DIR="${BUILD_DIR}/sdk/lib"

# Use BINDER_TOOLCHAIN_ROOT exported by install_binder.sh
BINDER_ROOT="${BINDER_TOOLCHAIN_ROOT:-${ROOT_DIR}/build-tools/linux_binder_idl}"
AIDL_OPS="${BINDER_ROOT}/host/aidl_ops.py"

echo "=========================================="
echo "  Building AIDL Interfaces"
echo "  Module:     $MODULE"
echo "  Version:    $VERSION"
echo "  Compiler:   ${CC:-gcc} / ${CXX:-g++}"
echo "  Output:     $OUT_DIR"
echo "=========================================="

mkdir -p "$OUT_DIR"
mkdir -p "$BUILD_DIR"
mkdir -p "$SDK_INCLUDE_DIR"
mkdir -p "$SDK_LIB_DIR"

# Stage SDK from toolchain
echo "--> [Step 1/4] Staging SDK..."
TOOLCHAIN_INSTALL_DIR="$BINDER_ROOT/out/target"
if [ -d "$TOOLCHAIN_INSTALL_DIR/include" ]; then
    cp -au "$TOOLCHAIN_INSTALL_DIR/include/." "$SDK_INCLUDE_DIR/" 2>/dev/null || true
fi
if [ -d "$TOOLCHAIN_INSTALL_DIR/lib" ]; then
    cp -au "$TOOLCHAIN_INSTALL_DIR/lib/"*.so* "$SDK_LIB_DIR/" 2>/dev/null || true
fi

# Determine which modules to process
if [ "$MODULE" == "all" ]; then
    echo "--> [Step 2/4] Calculating build order..."
    $AIDL_OPS -a -r "$ROOT_DIR" -o "$STABLE_DIR" > /dev/null
    DEPS_FILE="${STABLE_DIR}/dependencies.txt"
    if [ -f "$DEPS_FILE" ]; then
        MODULES=$(grep -- "-vcurrent-cpp:" "$DEPS_FILE" | cut -d: -f1 | sed 's/-vcurrent-cpp//')
        echo "    Build Order: [ $(echo $MODULES | tr '\n' ' ') ]"
    else
        echo "❌ Failed to generate dependency tree"
        exit 1
    fi
else
    MODULES="$MODULE"
fi

# Update APIs for each module
echo "--> [Step 3/4] Updating APIs..."
for mod in $MODULES; do
    echo "    Updating: $mod"
    $AIDL_OPS -u -r "$ROOT_DIR" -o "$STABLE_DIR" "$mod" || exit 1
done

# Sanitize generated files (mutex include fix)
if [ -d "$STABLE_DIR/generated" ]; then
    grep -rl "std::mutex" "$STABLE_DIR/generated" 2>/dev/null | while read -r file; do
        [ -f "$file" ] || continue
        if ! grep -q "#include <mutex>" "$file"; then
            if grep -q "^#include" "$file"; then
                sed -i '0,/^#include/s//#include <mutex>\n&/' "$file"
            elif grep -q "^#pragma once" "$file"; then
                sed -i 's/^#pragma once/#pragma once\n#include <mutex>/' "$file"
            else
                sed -i '1i #include <mutex>' "$file"
            fi
        fi
    done
fi

# Build with CMake
echo "--> [Step 4/4] Building libraries..."

# Pass the module name to CMake if building a specific module
if [ "$MODULE" != "all" ]; then
    MODULE_ARG="-DAIDL_TARGET=${MODULE}"
else
    MODULE_ARG=""
fi

cmake -S"${ROOT_DIR}" -B"${BUILD_DIR}" \
    -DAIDL_SRC_VERSION="${VERSION}" \
    -DLINUX_BINDER_AIDL_ROOT="${BINDER_ROOT}" \
    -DLINUX_BINDER_AIDL_ROOT_OUT="${STABLE_DIR}" \
    -DHOST_AIDL_DIR="${BINDER_ROOT}/host" \
    -DINTERFACES_ROOT_DIRS="${ROOT_DIR}" \
    -DSDK_INCLUDE_DIR="${SDK_INCLUDE_DIR}" \
    -DSDK_LIB_DIR="${SDK_LIB_DIR}" \
    ${MODULE_ARG}

if [ $? -ne 0 ]; then
    echo "❌ CMake configuration failed"
    exit 1
fi

JOBS=$(command -v nproc >/dev/null 2>&1 && nproc || echo 4)
cmake --build "${BUILD_DIR}" -j"$JOBS"

if [ $? -eq 0 ]; then
    # Copy outputs to out/ directory
    echo "--> [Step 5/5] Staging deployment files..."
    mkdir -p "${OUT_DIR}/include" "${OUT_DIR}/lib"
    
    # Copy generated headers and built libraries
    if [ -d "${STABLE_DIR}/generated" ]; then
        find "${STABLE_DIR}/generated" -name "*.h" -exec cp {} "${OUT_DIR}/include/" \; 2>/dev/null || true
    fi
    if [ -d "${BUILD_DIR}" ]; then
        find "${BUILD_DIR}" -name "*.so*" -exec cp {} "${OUT_DIR}/lib/" \; 2>/dev/null || true
    fi
    
    echo ""
    echo "✅ Build Complete"
    echo "   AIDL sources:  stable/<module>/${VERSION}/<module>-api/"
    echo "   Generated C++: stable/generated/<module>/${VERSION}/"
    echo "   Deployment:    ${OUT_DIR}/"
    echo "                  ├── include/  (headers)"
    echo "                  └── lib/      (libraries)"
    echo ""
    echo "   💡 Deploy out/ directory to target device"
    echo "   To freeze: ./freeze_interface.sh <module>"
else
    echo "❌ Build failed"
    exit 1
fi


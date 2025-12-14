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

set -euo pipefail
IFS=$'\n\t'

# =========================================================
# CONFIGURATION
# =========================================================
TARGET="${1:-all}"
ROOT_DIR=$(pwd)

# 1. PRE-FLIGHT: Ensure Toolchain is Ready
# ---------------------------------------------------------
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

# 1b. Activate Python Venv
if [ -f "./activate_venv.sh" ]; then
    source ./activate_venv.sh
fi

# =========================================================
# BUILD CONFIG
# =========================================================
BUILD_BASE="${ROOT_DIR}/build"
AIDL_OUT_DIR="${BUILD_BASE}/out"        
CMAKE_BUILD_DIR="${BUILD_BASE}/current" 
SDK_INCLUDE_DIR="${AIDL_OUT_DIR}/include"
SDK_LIB_DIR="${AIDL_OUT_DIR}/lib"

# Use the variable exported by install_binder.sh, or fallback
AIDL_TOOL_ROOT="${BINDER_TOOLCHAIN_ROOT:-$ROOT_DIR/build-tools/linux_binder_idl}"
AIDL_OPS="${AIDL_TOOL_ROOT}/host/aidl_ops.py"
DEPS_FILE="${AIDL_OUT_DIR}/dependencies.txt"

echo "=========================================="
echo "  DEV BUILD: Dynamic Discovery Mode       "
echo "  Toolchain: $AIDL_TOOL_ROOT"
echo "=========================================="

mkdir -p "$AIDL_OUT_DIR"
mkdir -p "$CMAKE_BUILD_DIR"
mkdir -p "$SDK_INCLUDE_DIR"
mkdir -p "$SDK_LIB_DIR"

# ---------------------------------------------------------
# PHASE 0: Stage SDK (From the verified toolchain)
# ---------------------------------------------------------
echo "--> [Step 0/4] Staging SDK..."
TOOLCHAIN_INSTALL_DIR="$AIDL_TOOL_ROOT/local"

# Copy Headers
cp -au "$TOOLCHAIN_INSTALL_DIR/include/." "$SDK_INCLUDE_DIR/" 2>/dev/null

# Copy Libraries
cp -au "$TOOLCHAIN_INSTALL_DIR/lib/"*.so* "$SDK_LIB_DIR/" 2>/dev/null

# ---------------------------------------------------------
# PHASE 1: Topology
# ---------------------------------------------------------
if [ "$TARGET" == "all" ]; then
    echo "--> [Step 1/4] Calculating Build Order..."
    $AIDL_OPS -a -r "$ROOT_DIR" -o "$AIDL_OUT_DIR" > /dev/null
    MODULES=$(grep -- "-vcurrent-cpp:" "$DEPS_FILE" | cut -d: -f1 | sed 's/-vcurrent-cpp//')
    echo "    Build Order: [ $(echo $MODULES | tr '\n' ' ') ]"
else
    MODULES="$TARGET"
fi

# ---------------------------------------------------------
# PHASE 2: Update APIs
# ---------------------------------------------------------
for mod in $MODULES; do
    echo "--> [Step 2/4] Updating API: $mod"
    $AIDL_OPS -u -r "$ROOT_DIR" -o "$AIDL_OUT_DIR" "$mod" || exit 1
done

# ---------------------------------------------------------
# PHASE 3: Generate & Configure
# ---------------------------------------------------------
echo "--> [Step 3/4] Configuring CMake..."

# PHASE 3.5: Sanitize generated files that use std::mutex but don't include <mutex>
echo "--> [Step 3.5] Sanitizing generated mutex usage..."

if [ -d "$ROOT_DIR/stable/generated" ]; then
    grep -rl "std::mutex" "$ROOT_DIR/stable/generated" | while read -r file; do
        # Skip non-regular files, just in case
        [ -f "$file" ] || continue

        # If it already includes <mutex>, nothing to do
        if grep -q "#include <mutex>" "$file"; then
            continue
        fi

        # Case 1: has at least one #include – insert before the first one
        if grep -q "^#include" "$file"; then
            sed -i '0,/^#include/s//#include <mutex>\n&/' "$file"
            continue
        fi

        # Case 2: no includes, but has #pragma once – insert after it
        if grep -q "^#pragma once" "$file"; then
            sed -i 's/^#pragma once/#pragma once\n#include <mutex>/' "$file"
            continue
        fi

        # Case 3: no includes, no pragma once – insert at top
        sed -i '1i #include <mutex>' "$file"
    done
fi

cd "$CMAKE_BUILD_DIR"

cmake "$ROOT_DIR" \
    -DAIDL_TARGET="$TARGET" \
    -DAIDL_SRC_VERSION="current" \
    -DCMAKE_BUILD_TYPE=Debug \
    -DLINUX_BINDER_AIDL_ROOT_OUT="$AIDL_OUT_DIR" \
    -DINTERFACES_ROOT_DIRS="$ROOT_DIR" \
    -DLINUX_BINDER_AIDL_ROOT="$AIDL_TOOL_ROOT" \
    -DSDK_INCLUDE_DIR="$SDK_INCLUDE_DIR" \
    -DSDK_LIB_DIR="$SDK_LIB_DIR"

if [ $? -ne 0 ]; then
    echo "❌ CMake Configuration Failed."
    exit 1
fi

# ---------------------------------------------------------
# PHASE 4: Compile
# ---------------------------------------------------------
echo "--> [Step 4/4] Compiling..."
JOBS=$(command -v nproc >/dev/null 2>&1 && nproc || echo 4)
make -j"$JOBS"
if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Build Succeeded."
    echo "   Generated files are located in: $AIDL_OUT_DIR"
else
    echo "❌ Build Failed."
    exit 1
fi
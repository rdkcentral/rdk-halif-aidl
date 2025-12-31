#!/bin/bash
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

# @brief Build RDK HAL AIDL module
#
# This script builds a specific HAL module that depends on the Binder SDK.
# This is Stage 2 of the two-stage build process.
#
# Usage:
#   ./build_module.sh <module> [version] [clean]
#
# Examples:
#   ./build_module.sh boot              # Build boot module, current version
#   ./build_module.sh videodecoder current clean   # Clean build
#   ./build_module.sh all               # Build all modules
#
# Output:
#   out/lib/<module>/lib<module>-vcurrent-cpp.so
#   out/include/com/rdk/hal/<module>/*.h

set -e  # Exit on error

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# Parse arguments
MODULE="${1:-all}"
VERSION="${2:-current}"
CLEAN=false

if [ "$2" = "clean" ] || [ "$3" = "clean" ]; then
    CLEAN=true
fi

BINDER_SDK_DIR="$PWD/out/target"
MODULE_BUILD_DIR="build/$MODULE"
OUT_DIR="$PWD/out"

echo "========================================"
echo "  RDK HAL AIDL - Module Build"
echo "========================================"
echo "Module:  $MODULE"
echo "Version: $VERSION"
echo "Build:   $MODULE_BUILD_DIR"
echo "Output:  $OUT_DIR"
echo "========================================"
echo ""

# Verify binder SDK exists (Stage 1 must complete first)
if [ ! -f "$BINDER_SDK_DIR/.sdk_ready" ]; then
    echo "ERROR: Binder SDK not found!"
    echo ""
    echo "You must build the Binder SDK first (Stage 1):"
    echo "  ./install_binder.sh"
    echo ""
    exit 1
fi

echo "✓ Binder SDK found at $BINDER_SDK_DIR"
echo ""

# Clean if requested
if [ "$CLEAN" = true ]; then
    echo "Cleaning previous build..."
    rm -rf "$MODULE_BUILD_DIR"
    
    # Also clean module output directory
    if [ "$MODULE" != "all" ]; then
        rm -rf "$OUT_DIR/lib/$MODULE" "$OUT_DIR/include/com/rdk/hal/$MODULE"
    fi
    
    echo "✓ Cleaned"
    echo ""
fi

# Configure module build
echo "Configuring module $MODULE..."
cmake -S . -B "$MODULE_BUILD_DIR" \
    -DINTERFACE_TARGET="$MODULE" \
    -DAIDL_SRC_VERSION="$VERSION" \
    -DBINDER_SDK_DIR="$BINDER_SDK_DIR" \
    -DOUT_DIR="$OUT_DIR"

if [ $? -ne 0 ]; then
    echo ""
    echo "ERROR: CMake configuration failed"
    exit 1
fi

echo ""
echo "Building module $MODULE..."
cmake --build "$MODULE_BUILD_DIR" -j$(nproc)

if [ $? -ne 0 ]; then
    echo ""
    echo "ERROR: Build failed"
    exit 1
fi

echo ""
echo "========================================"
echo "  ✓ Module Build Complete"
echo "========================================"
echo ""
echo "Output directory: $OUT_DIR"
echo ""

if [ "$MODULE" != "all" ]; then
    echo "Libraries:"
    find "$OUT_DIR/lib" -name "lib${MODULE}*.so" 2>/dev/null | head -10 || echo "  (none found)"
    echo ""
    echo "Headers:"
    find "$OUT_DIR/include/com/rdk/hal/$MODULE" -name "*.h" 2>/dev/null | wc -l | xargs echo "  " "files"
else
    echo "Libraries: $(find $OUT_DIR/lib -name '*.so' 2>/dev/null | wc -l) files"
    echo "Headers:   $(find $OUT_DIR/include -name '*.h' 2>/dev/null | wc -l) files"
fi

echo ""
echo "SDK ready for deployment from: $OUT_DIR"
echo ""

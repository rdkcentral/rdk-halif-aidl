#!/usr/bin/env bash

#** *****************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2026 RDK Management
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

# Production build script for HAL modules
#
# This script compiles HAL libraries from pre-generated C++ code.
# It does NOT run AIDL generation - code must already exist in stable/generated/
#
# Usage:
#   ./build_modules.sh [module|command] [options]
#
# Examples:
#   ./build_modules.sh all              # Build all modules
#   ./build_modules.sh boot             # Build boot module only
#   ./build_modules.sh all --clean      # Clean build
#   ./build_modules.sh clean            # Remove out/ directory
#   ./build_modules.sh --help           # Show help

# Show help if no arguments or help requested
if [[ $# -eq 0 ]] || [[ "${1:-}" == "--help" ]] || [[ "${1:-}" == "-h" ]] || [[ "${1:-}" == "--h" ]]; then
    cat << 'EOF'
Usage: ./build_modules.sh [module|command] [options]

Build HAL module libraries from pre-generated C++ code (Stage 3 only).

Arguments:
  module     Module to build (default: all)
             - "all"  : Build all modules
             - <name> : Build specific module (e.g., boot, videodecoder)

Commands:
  manifest   Build the component set from versions.yaml (each at its
             pinned version). Use --file <path> for an alternate manifest.
  clean      Remove out/ directory (build artifacts)
  cleanall   Remove out/ and build/ directories

Options:
  --clean            Clean build directory before building
  --version <ver>    Version to build (default: current)
  --sdk-dir <path>   Binder SDK location (default: out/target)
  --build-dir <path> CMake build directory (default: build/current)
  --jobs <N>         Number of parallel build jobs (default: nproc)
  --help, -h         Show this help message

Description:
  This script performs Stage 3 of the build process:
  - Compiles pre-generated C++ from stable/generated/
  - Links against Binder SDK (must exist from Stage 1 or Yocto)
  - Outputs libraries to out/target/lib/halif/
  - Outputs headers to out/build/include/

  ⚠️  This is a Stage 3 (compilation only) script.
  For full workflow, use ./build_interfaces.sh <module>

Prerequisites:
  1. Binder SDK must exist:
     - Development: Run ./build_interfaces.sh <module> (stages SDK)
     - Production: Provided by Yocto's linux-binder recipe

  2. Generated C++ must exist in stable/generated/
     - Development: Run ./build_interfaces.sh <module> (generates code)
     - Production: Pre-generated code is committed to repo

Build Configuration:
  Use environment variables to control compiler and flags:

    # Standard build (uses system defaults)
    ./build_modules.sh all

    # Custom compiler
    CC=gcc CXX=g++ ./build_modules.sh all

    # With custom flags
    CC=gcc CFLAGS="-O2 -g" CXXFLAGS="-O2 -g" ./build_modules.sh all

    # Cross-compilation (Yocto pattern)
    CC=arm-linux-gnueabihf-gcc \
    CXX=arm-linux-gnueabihf-g++ \
    CFLAGS="-march=armv7-a" \
    CXXFLAGS="-march=armv7-a" \
    LDFLAGS="-Wl,--hash-style=gnu" \
    ./build_modules.sh all --sdk-dir /opt/sysroot/usr

  Supported variables: CC, CXX, CFLAGS, CXXFLAGS, LDFLAGS

Examples:
  # Basic usage
  ./build_modules.sh all                              # Build all modules
  ./build_modules.sh boot                             # Build boot only
  ./build_modules.sh boot --version current           # Explicit version
  ./build_modules.sh boot --version v1                # Build frozen version

  # Clean builds
  ./build_modules.sh clean                            # Remove out/ directory
  ./build_modules.sh cleanall                         # Remove out/ and build/
  ./build_modules.sh all --clean                      # Clean before build

  # Custom SDK location (for Yocto/cross-compilation)
  ./build_modules.sh all --sdk-dir /opt/sysroot/usr

  # Parallel builds
  ./build_modules.sh all --jobs 8                     # 8 parallel jobs

  # Yocto/BitBake integration
  CC="${CC}" CXX="${CXX}" \
  CFLAGS="${CFLAGS}" CXXFLAGS="${CXXFLAGS}" LDFLAGS="${LDFLAGS}" \
  ./build_modules.sh all --sdk-dir ${STAGING_DIR}${prefix}

Output:
  Libraries: out/target/lib/halif/lib<module>-vcurrent-cpp.so
  Headers:   out/build/include/<module>/

For Development Workflow:
  To modify AIDL interfaces and regenerate C++ code, use:
    ./build_interfaces.sh <module>

EOF
    exit 0
fi

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$SCRIPT_DIR"

#######################################################################
# Parse Arguments
#######################################################################

# Check for clean commands first
case "${1:-}" in
    clean)
        echo "🧹 Cleaning out/ directory..."
        rm -rf "$ROOT_DIR/out"
        echo "✓ Removed: $ROOT_DIR/out/"
        echo ""
        echo "✅ Clean complete"
        exit 0
        ;;
    cleanall)
        echo "🧹 Cleaning out/ and build/ directories..."
        rm -rf "$ROOT_DIR/out"
        rm -rf "$ROOT_DIR/build"
        echo "✓ Removed: $ROOT_DIR/out/"
        echo "✓ Removed: $ROOT_DIR/build/"
        echo ""
        echo "✅ Clean complete"
        exit 0
        ;;
    sdk|sdk-only)
        echo "→ Redirecting: ./build_modules.sh sdk → ./build_binder.sh sdk"
        echo ""

        BUILD_BINDER_SCRIPT="$ROOT_DIR/build_binder.sh"

        if [ ! -f "$BUILD_BINDER_SCRIPT" ]; then
            echo "❌ ERROR: build_binder.sh not found at $BUILD_BINDER_SCRIPT"
            exit 1
        fi

        # Execute build_binder.sh
        exec "$BUILD_BINDER_SCRIPT" "${@:2}"
        ;;
    manifest)
        # Build the component set described by versions.yaml, each at the
        # version the manifest pins it to.
        MANIFEST="$ROOT_DIR/versions.yaml"
        if [[ "${2:-}" == "--file" && -n "${3:-}" ]]; then
            MANIFEST="$3"
        fi
        if [[ ! -f "$MANIFEST" ]]; then
            echo "❌ ERROR: version manifest not found: $MANIFEST"
            exit 1
        fi

        DEFAULT_VER="$(grep -E '^default:' "$MANIFEST" | head -1 | awk '{print $2}')"
        DEFAULT_VER="${DEFAULT_VER:-current}"

        # Read "<component> <version>" pairs from the components: map.
        mapfile -t MANIFEST_PAIRS < <(awk -v def="$DEFAULT_VER" '
            /^components:/      { inmap=1; next }
            inmap && /^[^[:space:]#]/ { inmap=0 }
            inmap && /^[[:space:]]+[A-Za-z0-9_]+:/ {
                gsub(/:/, " "); print $1, ($2 == "" ? def : $2)
            }' "$MANIFEST")

        if [[ ${#MANIFEST_PAIRS[@]} -eq 0 ]]; then
            echo "❌ ERROR: no components listed in $MANIFEST"
            exit 1
        fi

        echo "📋 Version manifest: $MANIFEST"
        echo "   ${#MANIFEST_PAIRS[@]} component(s), default version '${DEFAULT_VER}'"
        echo ""

        # Components pinned to 'current' build together in one pass; any
        # component pinned to a released version is built individually.
        ALL_CURRENT=true
        for pair in "${MANIFEST_PAIRS[@]}"; do
            read -r _ ver <<< "$pair"
            [[ "$ver" != "current" ]] && ALL_CURRENT=false
        done

        rc=0
        if $ALL_CURRENT; then
            "$0" all || rc=$?
        else
            for pair in "${MANIFEST_PAIRS[@]}"; do
                read -r comp ver <<< "$pair"
                echo "── building ${comp} (version ${ver}) ──"
                "$0" "$comp" --version "$ver" || rc=$?
            done
        fi
        exit $rc
        ;;
esac

MODULE="${1:-all}"
VERSION="current"
SDK_DIR=""
BUILD_DIR=""
JOBS=$(nproc 2>/dev/null || echo 4)
CLEAN=false

shift 1 2>/dev/null || true

while [[ $# -gt 0 ]]; do
    case "$1" in
        --clean)
            CLEAN=true
            shift
            ;;
        --version)
            VERSION="$2"
            shift 2
            ;;
        --sdk-dir)
            SDK_DIR="$2"
            shift 2
            ;;
        --build-dir)
            BUILD_DIR="$2"
            shift 2
            ;;
        --jobs|-j)
            JOBS="$2"
            shift 2
            ;;
        *)
            echo "❌ Unknown option: $1"
            echo "Run './build_modules.sh --help' for usage"
            exit 1
            ;;
    esac
done

# Set defaults
if [[ -z "$SDK_DIR" ]]; then
    SDK_DIR="$ROOT_DIR/out/target"
fi

if [[ -z "$BUILD_DIR" ]]; then
    BUILD_DIR="$ROOT_DIR/build/current"
fi

#######################################################################
# Validation
#######################################################################

echo "========================================="
echo "  HAL Module Build (Stage 3)"
echo "========================================="
echo "Module:     $MODULE"
echo "Version:    $VERSION"
echo "SDK:        $SDK_DIR"
echo "Build Dir:  $BUILD_DIR"
echo "Jobs:       $JOBS"
echo "========================================="
echo ""

# Check for Binder SDK
if [[ ! -f "$SDK_DIR/.sdk_ready" ]]; then
    echo "❌ ERROR: Binder SDK not found at $SDK_DIR"
    echo ""
    echo "The Binder SDK must be installed before building modules."
    echo ""
    echo "Development: Run ./build_interfaces.sh <module>"
    echo "Production:  Ensure linux-binder recipe is built (Yocto)"
    echo ""
    exit 1
fi

echo "✓ Binder SDK found at $SDK_DIR"

# Module-local layout: each component holds its own AIDL and generates its
# own C++ into <module>/current/{include,src}. The CMake configure step
# generates any missing sources, so there is no central stable/generated
# tree to pre-check here.
MODULE_COUNT=$(ls -d "$ROOT_DIR"/*/current/interface.yaml 2>/dev/null | wc -l)
echo "✓ Found $MODULE_COUNT component interface(s)"

# Validate specific module exists if not building all
if [[ "$MODULE" != "all" ]]; then
    if [[ ! -f "$ROOT_DIR/$MODULE/current/interface.yaml" ]]; then
        echo "❌ ERROR: Component '$MODULE' not found ($ROOT_DIR/$MODULE/current/interface.yaml)"
        echo ""
        echo "Available components:"
        ls -d "$ROOT_DIR"/*/current/interface.yaml 2>/dev/null \
            | sed -E 's#.*/([^/]+)/current/interface.yaml#  \1#' | sort
        echo ""
        exit 1
    fi
    echo "✓ Component '$MODULE' exists"
fi

echo ""

#######################################################################
# Clean if requested
#######################################################################

if [[ "$CLEAN" == true ]]; then
    echo "🧹 Cleaning build directory: $BUILD_DIR"
    rm -rf "$BUILD_DIR"
    echo "✓ Clean complete"
    echo ""
fi

#######################################################################
# CMake Configure
#######################################################################

echo "⚙️  Configuring CMake..."
echo ""

cmake -S "$ROOT_DIR" -B "$BUILD_DIR" \
    -DINTERFACE_TARGET="$MODULE" \
    -DAIDL_SRC_VERSION="$VERSION" \
    -DBINDER_SDK_DIR="$SDK_DIR"

if [[ $? -ne 0 ]]; then
    echo ""
    echo "❌ CMake configuration failed"
    exit 1
fi

echo ""
echo "✓ CMake configuration complete"
echo ""

#######################################################################
# Build
#######################################################################

echo "🔨 Building HAL modules..."
echo ""

cmake --build "$BUILD_DIR" -j"$JOBS"

if [[ $? -ne 0 ]]; then
    echo ""
    echo "❌ Build failed"
    exit 1
fi

echo ""
echo "✓ Build complete"
echo ""

#######################################################################
# Summary
#######################################################################

OUT_DIR="$ROOT_DIR/out/target"
LIB_DIR="$OUT_DIR/lib/halif"
INC_DIR="$ROOT_DIR/out/build/include"

echo "========================================="
echo "  Build Summary"
echo "========================================="
echo ""

# Count built libraries
if [[ -d "$LIB_DIR" ]]; then
    LIB_COUNT=$(find "$LIB_DIR" -name "*.so" 2>/dev/null | wc -l)
    echo "Libraries: $LIB_COUNT built"
    echo "  Location: $LIB_DIR"
    echo ""
    if [[ $LIB_COUNT -gt 0 ]] && [[ $LIB_COUNT -le 10 ]]; then
        echo "  Built libraries:"
        find "$LIB_DIR" -name "*.so" -exec basename {} \; | sort | sed 's/^/    - /'
        echo ""
    fi
fi

# Count staged headers
if [[ -d "$INC_DIR" ]]; then
    HEADER_COUNT=$(find "$INC_DIR" -name "*.h" 2>/dev/null | wc -l)
    echo "Headers: $HEADER_COUNT staged"
    echo "  Location: $INC_DIR"
    echo ""
fi

echo "========================================="
echo "✅ Build completed successfully!"
echo "========================================="
echo ""

exit 0

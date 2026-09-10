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

# Orchestration helper to build AIDL interface libraries.
#
# Module-local layout (Phase B, #493): each component keeps its AIDL and
# generated C++ together under <module>/current/. This script:
#   1. Stages the Binder SDK (Stage 1, via build_binder.sh).
#   2. Delegates generation + compilation to build_modules.sh, which
#      regenerates module-local C++ as needed during CMake configure.
# The central stable/ tree is retired; build_modules.sh does the build.
#
# Usage:
#   ./build_interfaces.sh [module]
#       module: "all" (default) or specific module name (e.g., "boot", "videodecoder")
#
# Examples:
#   ./build_interfaces.sh              # Build all modules
#   ./build_interfaces.sh all          # Build all modules
#   ./build_interfaces.sh videodecoder # Build only videodecoder

set -euo pipefail

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SCRIPT_PATH="$SCRIPT_DIR/$(basename "${BASH_SOURCE[0]}")"

# Host-toolchain guard (#624): build / sdk operations need a native toolchain,
# and Yocto/cross builds must call CMake directly (see
# docs/standards/build_integration.md). clean/help do no toolchain work, so
# they stay usable in any environment.
case "${1:-}" in
    clean|cleanstable|cleanall|--help|-h|"") ;;
    *) source "$SCRIPT_DIR/dev_env_guard.sh"; halif_guard_dev_host_env || exit 1 ;;
esac

# Show help if no arguments or help requested
if [[ $# -eq 0 ]] || [[ "${1:-}" == "--help" ]] || [[ "${1:-}" == "-h" ]]; then
    cat << EOF
Usage: ./build_interfaces.sh <module|command> [--version <ver>]

Build AIDL interface libraries or clean build artifacts.

Arguments:
  module     Module to build (required)
             - "all"  : Build all modules
             - <name> : Build specific module (e.g., boot, videodecoder)

Commands:
  sdk             Stage Binder SDK only (Stage 1), skip AIDL generation and compilation
  sdk-only        Alias for 'sdk'
  clean           Remove out/ directory (build outputs)
  cleanstable     Remove a legacy stable/ directory if one is present
  cleanall        Remove out/, stable/, and build-tools/ directories

  (The stable/-based test* subcommands were retired with the module-local
   restructure (#493); build verification lives under tests/.)

Options:
  --version <ver>    Version to build (default: current)
                     - "current" : in-development interface
                     - "0.1.0.0" : a released snapshot directory

  --help, -h         Show this help message

Description:
  This script performs a complete build:
  1. Stage 1: Stage Binder SDK from toolchain to out/target/
  2. Stage 2: Generate module-local C++ into <module>/current/{include,src}
  3. Stage 3: Compile libraries and stage to out/
  Stages 2-3 are delegated to build_modules.sh.

  Use 'sdk' or 'sdk-only' command to only perform Stage 1 (SDK staging).

Build Configuration:
  Use CC/CXX environment variables to control compiler and flags:
    CC=gcc CXX=g++ ./build_interfaces.sh <module>              # Release (default)
    CC="gcc -g" CXX="g++ -g" ./build_interfaces.sh <module>   # Debug build

  Cross-compilation / Yocto: this wrapper is host-only and refuses to run in a
  cross/OpenEmbedded environment. Production/cross builds invoke CMake directly
  — see docs/standards/build_integration.md.

Examples:
  # Building
  ./build_interfaces.sh all                    # Build all modules (all stages)
  ./build_interfaces.sh boot                   # Build boot module (all stages)
  ./build_interfaces.sh sdk                    # Stage SDK only (Stage 1)
  ./build_interfaces.sh boot --version current # Explicit version

  # Cleaning
  ./build_interfaces.sh clean                  # Remove build outputs (out/)
  ./build_interfaces.sh cleanall               # Remove all artifacts

Output Structure:
  <module>/current/
    include/  src/                      # Generated C++ (module-local, committed)
  out/target/
    lib/
      binder/                           # Binder runtime libraries (*.so)
      halif/                            # HAL interface libraries (*.so)
    include/
      binder_sdk/                       # Binder headers (for compilation)
      halif/                            # HAL interface headers
    .sdk_ready                          # SDK marker file

Workflow:
  1. Edit:    vim <module>/current/com/rdk/hal/<module>/*.aidl
  2. Build:   ./build_interfaces.sh all
  3. Verify:  ./build_modules.sh all
  4. Deploy:  scp -r out/target/* device:/usr/
  5. Release: ./release.sh             # cohort-wide release sweep (dry-run first)

EOF
    exit 0
fi

#######################################################################
# Pre-flight checks (#571)
#######################################################################
#
# Same purpose as in build_modules.sh: surface broken-env failures as
# a single actionable line rather than cryptic CMake / Python output
# deep in the run. Skipped for clean / sdk-only commands which must
# work in any state.

preflight_check_interfaces() {
    # Toolchain artefacts present. Honour BINDER_TOOLCHAIN_ROOT /
    # BINDER_SOURCE_DIR overrides used by Yocto and cross-compile
    # flows. The 'sdk' / 'sdk-only' commands stage the toolchain
    # itself and bypass this check via the case statement below.
    local toolchain_root="${BINDER_TOOLCHAIN_ROOT:-${BINDER_SOURCE_DIR:-$SCRIPT_DIR/build-tools/linux_binder_idl}}"
    if [[ ! -f "$toolchain_root/host/aidl_ops.py" ]]; then
        echo "❌ AIDL toolchain not found at $toolchain_root/host/aidl_ops.py." >&2
        echo "   Fix: run ./build_interfaces.sh sdk to stage the toolchain," >&2
        echo "        ./build_binder.sh to bootstrap, symlink build-tools/" >&2
        echo "        from a known-good worktree, or set BINDER_TOOLCHAIN_ROOT" >&2
        echo "        (or BINDER_SOURCE_DIR) to the toolchain location." >&2
        exit 1
    fi
}

# Run pre-flight unless the user asked for a clean/sdk command — those
# must work in any environment state.
case "${1:-}" in
    clean|cleanstable|cleanall|sdk|sdk-only|--help|-h|"") : ;;  # skip preflight
    *) preflight_check_interfaces ;;
esac

# Handle commands
case "${1:-}" in
    sdk|sdk-only)
        echo "=========================================="
        echo "  Stage 1: Binder SDK Build & Staging"
        echo "=========================================="
        echo ""

        # Call build_binder.sh to handle SDK build
        BUILD_BINDER_SCRIPT="$SCRIPT_DIR/build_binder.sh"

        if [ ! -f "$BUILD_BINDER_SCRIPT" ]; then
            echo "❌ ERROR: build_binder.sh not found at $BUILD_BINDER_SCRIPT"
            echo ""
            exit 1
        fi

        # Execute build_binder.sh (it handles clone, build, organize, PATH setup)
        if ! bash "$BUILD_BINDER_SCRIPT"; then
            echo ""
            echo "❌ ERROR: Binder SDK build failed"
            echo ""
            exit 1
        fi

        echo ""
        echo "✅ Stage 1 Complete - Binder SDK Ready"
        echo ""
        echo "SDK Location: $SCRIPT_DIR/out/target/"
        echo ""
        exit 0
        ;;
    clean)
        echo "🧹 Cleaning build outputs..."
        rm -rf out/
        echo "✅ Removed out/ directory"
        exit 0
        ;;
    cleanstable)
        echo "🧹 Cleaning generated code and AIDL copies..."
        rm -rf stable/
        echo "✅ Removed stable/ directory"
        exit 0
        ;;
    cleanall)
        echo "🧹 Cleaning all build artifacts..."
        rm -rf out/ stable/ build-tools/
        echo "✅ Removed out/, stable/, and build-tools/ directories"
        exit 0
        ;;
    test|test-all|test-validation|test-cmake)
        # The stable/-based test subcommands were retired with the
        # module-local restructure (#493) - they exercised the central
        # stable/generated tree that no longer exists. Module-local build
        # verification is moving to the tests/ smoke harness.
        echo "ℹ️  '$1' was retired with the module-local restructure (#493)."
        echo "    Build verification now lives under tests/ (smoke harness)."
        echo "    Quick check: ./build_modules.sh all"
        exit 0
        ;;
esac

# Ensure binder toolchain is installed and PATH is set
if [ -f "./build_binder.sh" ]; then
    source ./build_binder.sh
    if [ $? -ne 0 ]; then
        echo "❌ Critical Error: Failed to setup Binder Toolchain."
        exit 1
    fi
else
    echo "❌ Error: build_binder.sh not found in root."
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

# Use BINDER_TOOLCHAIN_ROOT exported by build_binder.sh
BINDER_ROOT="${BINDER_TOOLCHAIN_ROOT:-${ROOT_DIR}/build-tools/linux_binder_idl}"
AIDL_OPS="${BINDER_ROOT}/host/aidl_ops.py"

# SDK location where build_binder.sh installs (not toolchain source)
SDK_DIR="${ROOT_DIR}/out/target"

echo "=========================================="
echo "  Building AIDL Interfaces"
echo "  Module:     $MODULE"
echo "  Version:    $VERSION"
echo "  Compiler:   ${CC:-gcc} / ${CXX:-g++}"
echo "  Output:     $OUT_DIR"
echo "=========================================="

mkdir -p "$OUT_DIR"

#######################################################################
# Module-local build (Phase B, #493)
#
# The central stable/ tree is retired: each component generates its C++
# in place under <module>/current/{include,src}. AIDL update/generation
# (Stage 2) and compilation (Stage 3) are both handled by
# build_modules.sh, whose CMake configure step regenerates any missing
# module-local sources. build_interfaces.sh stays the orchestration
# entry point - it stages the Binder SDK (above) and then delegates.
#
# The legacy aidl_ops -u / stable/ machinery is intentionally retained
# in the toolchain but is no longer driven from here.
#######################################################################

BUILD_MODULES_SCRIPT="${ROOT_DIR}/build_modules.sh"
if [ ! -x "$BUILD_MODULES_SCRIPT" ]; then
    echo "❌ build_modules.sh not found or not executable: $BUILD_MODULES_SCRIPT"
    exit 1
fi

echo "--> Building '${MODULE}' (version ${VERSION}) via build_modules.sh ..."
echo ""

if ! "$BUILD_MODULES_SCRIPT" "$MODULE" --version "$VERSION"; then
    echo "❌ Build failed"
    exit 1
fi

BINDER_LIBS=$(ls out/target/lib/binder/*.so 2>/dev/null | wc -l || echo 0)
MODULE_LIBS=$(ls out/target/lib/rdk-halif-aidl/*.so 2>/dev/null | wc -l || echo 0)

echo ""
echo "✅ Build Complete - SDK Ready for Deployment"
echo ""
echo "   📦 Runtime libraries:"
echo "      • Binder libraries: ${BINDER_LIBS} files (out/target/lib/binder/)"
echo "      • HAL libraries:    ${MODULE_LIBS} files (out/target/lib/rdk-halif-aidl/)"
echo ""
echo "   📂 Generated C++ is module-local: <module>/current/{include,src}/"
echo ""
echo "   📂 Deploy to target device:"
echo "      scp -r out/target/bin/* device:/usr/bin/"
echo "      scp -r out/target/lib/* device:/usr/lib/"
echo ""

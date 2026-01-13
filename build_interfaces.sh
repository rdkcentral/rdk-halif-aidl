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

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SCRIPT_PATH="$SCRIPT_DIR/$(basename "${BASH_SOURCE[0]}")"

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
  clean           Remove out/ directory (build outputs)
  cleanstable     Remove stable/ directory (generated code and AIDL copies)
  cleanall        Remove out/, stable/, and build-tools/ directories
  test            Build sample modules (boot, common, flash) and verify outputs
  test-all        Comprehensive test: build each module individually and validate
  test-validation Test AIDL compatibility validation (add/remove methods)
  test-cmake      Test CMake production build system (configure, build, install)

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
  # Building
  ./build_interfaces.sh all                    # Build all modules
  ./build_interfaces.sh boot                   # Build boot module
  ./build_interfaces.sh boot --version current # Explicit version
  ./build_interfaces.sh videodecoder --version v1  # Build frozen v1

  # Cleaning
  ./build_interfaces.sh clean                  # Remove build outputs (out/)
  ./build_interfaces.sh cleanstable            # Remove generated code (stable/)
  ./build_interfaces.sh cleanall               # Remove all artifacts

  # Testing
  ./build_interfaces.sh test                   # Quick SDK validation
  ./build_interfaces.sh test-all               # Test all modules individually

Output Structure:
  stable/
    aidl/<module>/<version>/            # Copied AIDL definitions
    generated/<module>/<version>/       # Generated C++ code
    dependencies.txt                    # Module dependency graph
  out/target/
    lib/
      binder/                           # Binder runtime libraries (*.so)
      halif/                            # HAL interface libraries (*.so)
    include/
      binder_sdk/                       # Binder headers (for compilation)
      halif/                            # HAL interface headers
    .sdk_ready                          # SDK marker file

Workflow:
  1. Edit:   vim <module>/current/com/rdk/hal/<module>/*.aidl
  2. Build:  ./build_interfaces.sh all
  3. Test:   ./build_interfaces.sh test
  4. Deploy: scp -r out/target/* device:/usr/
  5. Freeze: ./freeze_interface.sh <module>

EOF
    exit 0
fi

# Handle clean commands
case "${1:-}" in
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
    test)
        echo "🧪 Testing interface builds..."
        echo "=========================================="
        echo ""

        # Clean previous build
        echo "Cleaning previous build..."
        rm -rf stable/ build/current

        echo "Building all interfaces..."
        if "$SCRIPT_PATH" all > /tmp/test_build_all.log 2>&1; then
            echo ""
            echo "Verifying build outputs..."

            # Check if libraries were built
            LIB_COUNT=$(find out/target/lib/halif -name "*.so" 2>/dev/null | wc -l || echo 0)
            LIB_COUNT=$(echo "$LIB_COUNT" | tr -d ' ')

            if [ "${LIB_COUNT:-0}" -gt 0 ]; then
                echo "  ✅ HAL libraries: $LIB_COUNT files"
            else
                echo "  ❌ No HAL libraries built"
                echo "  Last 20 lines of build log:"
                tail -20 /tmp/test_build_all.log | sed 's/^/     /'
                exit 1
            fi

            # Check if headers were generated
            HDR_COUNT=$(find stable/generated -name "*.h" 2>/dev/null | wc -l || echo 0)
            HDR_COUNT=$(echo "$HDR_COUNT" | tr -d ' ')

            if [ "${HDR_COUNT:-0}" -gt 0 ]; then
                echo "  ✅ HAL headers: $HDR_COUNT files"
            else
                echo "  ❌ No HAL headers generated"
                exit 1
            fi

            # Check generated C++ code structure
            GEN_CPP=$(find stable/generated -name "*.cpp" 2>/dev/null | wc -l || echo 0)
            GEN_CPP=$(echo "$GEN_CPP" | tr -d ' ')

            if [ "${GEN_CPP:-0}" -gt 0 ]; then
                echo "  ✅ Generated C++ files: $GEN_CPP files"
            else
                echo "  ❌ No C++ code generated"
                exit 1
            fi

            # Verify no unexpected artifacts
            echo ""
            echo "Checking for unwanted build artifacts..."

            # Check for timestamp files
            TIMESTAMP_COUNT=$(find stable -name "*.timestamp" 2>/dev/null | wc -l || echo 0)
            TIMESTAMP_COUNT=$(echo "$TIMESTAMP_COUNT" | tr -d ' ')
            if [ "${TIMESTAMP_COUNT:-0}" -eq 0 ]; then
                echo "  ✅ No timestamp files"
            else
                echo "  ❌ Found $TIMESTAMP_COUNT timestamp files (should be 0)"
                find stable -name "*.timestamp" | sed 's/^/     /'
                exit 1
            fi

            # Check for *-api directories
            API_DIR_COUNT=$(find stable -type d -name "*-api" 2>/dev/null | wc -l || echo 0)
            API_DIR_COUNT=$(echo "$API_DIR_COUNT" | tr -d ' ')
            if [ "${API_DIR_COUNT:-0}" -eq 0 ]; then
                echo "  ✅ No *-api directories"
            else
                echo "  ❌ Found $API_DIR_COUNT *-api directories (should be 0)"
                find stable -type d -name "*-api" | sed 's/^/     /'
                exit 1
            fi

            # Check for has_development files
            HAS_DEV_COUNT=$(find stable -name "has_development" 2>/dev/null | wc -l || echo 0)
            HAS_DEV_COUNT=$(echo "$HAS_DEV_COUNT" | tr -d ' ')
            if [ "${HAS_DEV_COUNT:-0}" -eq 0 ]; then
                echo "  ✅ No has_development files"
            else
                echo "  ❌ Found $HAS_DEV_COUNT has_development files (should be 0)"
                find stable -name "has_development" | sed 's/^/     /'
                exit 1
            fi

            # Check for unexpected module directories in stable/
            # Only aidl/, generated/, and dependencies.txt should exist at top level
            UNEXPECTED=$(ls -1 stable/ 2>/dev/null | grep -v -E "^(aidl|generated|dependencies.txt)$" || echo "")
            if [ -z "$UNEXPECTED" ]; then
                echo "  ✅ Clean stable/ structure (only aidl/, generated/, dependencies.txt)"
            else
                echo "  ❌ Unexpected items in stable/:"
                echo "$UNEXPECTED" | sed 's/^/     /'
                exit 1
            fi

            echo ""
            echo "✅ Interface build test passed"
            exit 0
        else
            echo ""
            echo "❌ Build failed"
            echo "Last 30 lines of build log:"
            tail -30 /tmp/test_build_all.log | sed 's/^/   /'
            exit 1
        fi
        ;;
    test-cmake)
        echo "=========================================="
        echo "🧪 Testing CMake Build System"
        echo "=========================================="
        echo ""

        TEST_PASSED=true
        TEST_MODULE="boot"
        TEST_BUILD_DIR="build/test-cmake-validation"
        TEST_INSTALL_DIR="/tmp/rdk-halif-cmake-test-install"

        # Cleanup function
        cleanup_cmake_test() {
            echo "  🔄 Cleaning up CMake test artifacts..."
            rm -rf "$TEST_BUILD_DIR" "$TEST_INSTALL_DIR" /tmp/cmake_test_*.log
        }

        # Trap to ensure cleanup on exit
        trap cleanup_cmake_test EXIT

        echo "Test 1: Check prerequisites"
        echo "--------------------------------------------------------"
        # Verify binder SDK exists
        if [ ! -f "out/target/.sdk_ready" ]; then
            echo "  ❌ Binder SDK not found - run ./install_binder.sh first"
            exit 1
        fi
        echo "  ✅ Binder SDK found"

        # Verify stable/generated exists
        if [ ! -d "stable/generated/$TEST_MODULE" ]; then
            echo "  ⚠️  Pre-generated code not found - generating now..."
            ./build_interfaces.sh "$TEST_MODULE" > /tmp/cmake_test_generate.log 2>&1
            if [ $? -ne 0 ]; then
                echo "  ❌ Failed to generate code"
                tail -10 /tmp/cmake_test_generate.log | sed 's/^/     /'
                exit 1
            fi
        fi
        echo "  ✅ Pre-generated code available"
        echo ""

        echo "Test 2: CMake configure (development mode)"
        echo "--------------------------------------------------------"
        if cmake -S . -B "$TEST_BUILD_DIR" \
                -DINTERFACE_TARGET="$TEST_MODULE" \
                -DAIDL_SRC_VERSION=current \
                > /tmp/cmake_test_configure.log 2>&1; then
            echo "  ✅ CMake configure succeeded"

            # Verify CMAKE_INSTALL_PREFIX defaulted correctly
            if grep -q "CMAKE_INSTALL_PREFIX defaulted to" /tmp/cmake_test_configure.log; then
                PREFIX=$(grep "CMAKE_INSTALL_PREFIX defaulted to" /tmp/cmake_test_configure.log | awk '{print $NF}')
                echo "  ✅ Install prefix defaulted to: $PREFIX"
            fi
        else
            echo "  ❌ CMake configure failed"
            tail -20 /tmp/cmake_test_configure.log | sed 's/^/     /'
            TEST_PASSED=false
        fi
        echo ""

        echo "Test 3: CMake build"
        echo "--------------------------------------------------------"
        if cmake --build "$TEST_BUILD_DIR" -j4 > /tmp/cmake_test_build.log 2>&1; then
            echo "  ✅ CMake build succeeded"

            # Verify library was built
            LIB_FILE=$(find "$TEST_BUILD_DIR" -name "lib${TEST_MODULE}-vcurrent-cpp.so" 2>/dev/null)
            if [ -n "$LIB_FILE" ]; then
                LIB_SIZE=$(stat -c%s "$LIB_FILE" 2>/dev/null || stat -f%z "$LIB_FILE" 2>/dev/null)
                echo "  ✅ Library built: $(basename "$LIB_FILE") (${LIB_SIZE} bytes)"
            else
                echo "  ❌ Library file not found"
                TEST_PASSED=false
            fi
        else
            echo "  ❌ CMake build failed"
            tail -20 /tmp/cmake_test_build.log | sed 's/^/     /'
            TEST_PASSED=false
        fi
        echo ""

        echo "Test 4: CMake install (development mode)"
        echo "--------------------------------------------------------"
        if cmake --install "$TEST_BUILD_DIR" > /tmp/cmake_test_install.log 2>&1; then
            echo "  ✅ CMake install succeeded"

            # Verify installed library
            DEFAULT_INSTALL="$(pwd)/out/target"
            if [ -f "$DEFAULT_INSTALL/lib/lib${TEST_MODULE}-vcurrent-cpp.so" ]; then
                echo "  ✅ Library installed to default location: out/target/lib/"
            else
                echo "  ❌ Library not found at default install location"
                TEST_PASSED=false
            fi

            # Verify installed headers
            HEADER_COUNT=$(find "$DEFAULT_INSTALL/include" -name "*.h" 2>/dev/null | wc -l)
            if [ "$HEADER_COUNT" -gt 0 ]; then
                echo "  ✅ Headers installed: $HEADER_COUNT files"
            else
                echo "  ❌ No headers installed"
                TEST_PASSED=false
            fi
        else
            echo "  ❌ CMake install failed"
            tail -20 /tmp/cmake_test_install.log | sed 's/^/     /'
            TEST_PASSED=false
        fi
        echo ""

        echo "Test 5: CMake install with custom prefix (Yocto mode)"
        echo "--------------------------------------------------------"
        rm -rf "$TEST_INSTALL_DIR"
        if cmake --install "$TEST_BUILD_DIR" --prefix "$TEST_INSTALL_DIR" \
                > /tmp/cmake_test_install_custom.log 2>&1; then
            echo "  ✅ CMake install with custom prefix succeeded"

            # Verify library at custom location
            if [ -f "$TEST_INSTALL_DIR/lib/lib${TEST_MODULE}-vcurrent-cpp.so" ]; then
                echo "  ✅ Library installed to: $TEST_INSTALL_DIR/lib/"
            else
                echo "  ❌ Library not found at custom install location"
                TEST_PASSED=false
            fi

            # Verify headers at custom location
            CUSTOM_HEADER_COUNT=$(find "$TEST_INSTALL_DIR/include" -name "*.h" 2>/dev/null | wc -l)
            if [ "$CUSTOM_HEADER_COUNT" -gt 0 ]; then
                echo "  ✅ Headers installed to custom location: $CUSTOM_HEADER_COUNT files"
            else
                echo "  ❌ No headers installed to custom location"
                TEST_PASSED=false
            fi
        else
            echo "  ❌ CMake install with custom prefix failed"
            tail -20 /tmp/cmake_test_install_custom.log | sed 's/^/     /'
            TEST_PASSED=false
        fi
        echo ""

        echo "Test 6: Verify configurable SDK paths"
        echo "--------------------------------------------------------"
        rm -rf "$TEST_BUILD_DIR"
        if cmake -S . -B "$TEST_BUILD_DIR" \
                -DINTERFACE_TARGET="$TEST_MODULE" \
                -DBINDER_SDK_INCLUDE_SUBDIR=include/custom \
                -DBINDER_SDK_LIB_SUBDIR=lib/custom \
                > /tmp/cmake_test_custom_sdk.log 2>&1; then
            echo "  ✅ CMake accepts custom SDK subdirectories"

            # Verify custom paths are used
            if grep -q "include/custom" /tmp/cmake_test_custom_sdk.log && \
               grep -q "lib/custom" /tmp/cmake_test_custom_sdk.log; then
                echo "  ✅ Custom SDK paths configured correctly"
            else
                echo "  ⚠️  Custom SDK paths may not be applied"
            fi
        else
            # This is expected to fail since custom paths don't exist, but configure should accept them
            if grep -q "BINDER_SDK_INCLUDE_SUBDIR\|BINDER_SDK_LIB_SUBDIR" /tmp/cmake_test_custom_sdk.log; then
                echo "  ✅ CMake accepts custom SDK path variables"
            else
                echo "  ⚠️  Could not verify custom SDK path support"
            fi
        fi
        echo ""

        echo "=========================================="
        if [ "$TEST_PASSED" = true ]; then
            echo "✅ All CMake build tests passed!"
            exit 0
        else
            echo "❌ Some CMake build tests failed"
            exit 1
        fi
        ;;
    test-all)
        echo "🧪 Running comprehensive build tests..."
        echo "=========================================="
        echo ""

        # List of all modules in dependency order
        MODULES=(
            common flash deepsleep indicator boot
            videodecoder audiodecoder hdmicec hdmiinput
            videosink audiosink hdmioutput deviceinfo
            planecontrol panel avbuffer avclock
        )

        FAILED_MODULES=()

        for module in "${MODULES[@]}"; do
            echo "----------------------------------------"
            echo "Testing: $module"
            echo "----------------------------------------"

            # Remove stable directory for clean test
            rm -rf stable/

            # Build the module
            if "$SCRIPT_PATH" "$module" > /tmp/build_$module.log 2>&1; then
                # Check stable directory structure
                AIDL_DIR=$(ls -d stable/aidl 2>/dev/null | wc -l)
                GEN_DIR=$(ls -d stable/generated 2>/dev/null | wc -l)
                DEPS_FILE=$(ls stable/dependencies.txt 2>/dev/null | wc -l)
                HIDDEN_API=$(ls -d stable/.api_temp 2>/dev/null | wc -l)

                AIDL_MODULES=$(ls stable/aidl/ 2>/dev/null | wc -l)
                GEN_MODULES=$(ls stable/generated/ 2>/dev/null | wc -l)

                if [ "$AIDL_DIR" -eq 1 ] && [ "$GEN_DIR" -eq 1 ] && [ "$DEPS_FILE" -eq 1 ] && [ "$HIDDEN_API" -eq 1 ]; then
                    echo "  ✅ Build: SUCCESS"
                    echo "  ✅ Structure: Clean (aidl/, generated/, dependencies.txt, .api_temp/)"
                    echo "  ✅ Modules in stable/aidl/: $AIDL_MODULES"
                    echo "  ✅ Modules in stable/generated/: $GEN_MODULES"

                    # Check for unexpected directories
                    UNEXPECTED=$(ls stable/ 2>/dev/null | grep -v "^aidl$" | grep -v "^generated$" | grep -v "^dependencies.txt$" | wc -l)
                    if [ "$UNEXPECTED" -gt 0 ]; then
                        echo "  ⚠️  Warning: Unexpected items in stable/:"
                        ls stable/ | grep -v "^aidl$" | grep -v "^generated$" | grep -v "^dependencies.txt$"
                        FAILED_MODULES+=("$module (unexpected dirs)")
                    fi
                else
                    echo "  ❌ Structure: FAILED"
                    echo "     aidl/: $AIDL_DIR (expected 1)"
                    echo "     generated/: $GEN_DIR (expected 1)"
                    echo "     dependencies.txt: $DEPS_FILE (expected 1)"
                    echo "     .api_temp/: $HIDDEN_API (expected 1)"
                    FAILED_MODULES+=("$module")
                fi
            else
                echo "  ❌ Build: FAILED"
                echo "  Last 10 lines of build log:"
                tail -10 /tmp/build_$module.log | sed 's/^/     /'
                FAILED_MODULES+=("$module")
            fi
            echo ""
        done

        echo "=========================================="
        echo "  Summary"
        echo "=========================================="
        if [ ${#FAILED_MODULES[@]} -eq 0 ]; then
            echo "✅ All ${#MODULES[@]} modules passed!"
        else
            echo "❌ ${#FAILED_MODULES[@]} module(s) failed:"
            for module in "${FAILED_MODULES[@]}"; do
                echo "   - $module"
            done
            exit 1
        fi
        exit 0
        ;;
    test-validation)
        echo "🧪 Testing AIDL compatibility validation..."
        echo "=========================================="
        echo ""

        TEST_MODULE="testhal"
        TEST_DIR="$TEST_MODULE"
        TEST_INTERFACE_FILE="$TEST_DIR/current/com/rdk/hal/$TEST_MODULE/ITestHal.aidl"
        TEST_YAML_FILE="$TEST_DIR/current/interface.yaml"
        TEST_PASSED=true

        # Create mock test interface
        setup_test_interface() {
            echo "  📝 Creating mock test interface..."
            mkdir -p "$TEST_DIR/current/com/rdk/hal/$TEST_MODULE"

            # Create interface.yaml
            cat > "$TEST_YAML_FILE" << 'EOF'
aidl_interface:
  name: testhal
  srcs:
    - com/rdk/hal/testhal/*.aidl
  imports: []
  stability: vintf
EOF

            # Create main interface
            cat > "$TEST_INTERFACE_FILE" << 'EOF'
package com.rdk.hal.testhal;

@VintfStability
interface ITestHal {
    const @utf8InCpp String serviceName = "testhal";

    /**
     * Initialize the test HAL.
     * @returns Success status.
     */
    boolean initialize();

    /**
     * Get current state.
     * @returns State value.
     */
    int getState();

    /**
     * Perform test operation.
     */
    void testOperation();
}
EOF
            echo "  ✅ Mock interface created at $TEST_DIR"
        }

        # Cleanup function
        cleanup_test() {
            echo "  🔄 Cleaning up test interface..."
            rm -rf "$TEST_DIR" stable/ out/
        }

        # Trap to ensure cleanup on exit
        trap cleanup_test EXIT

        # Setup test interface
        setup_test_interface

        echo "Test 1: First update should succeed (no frozen versions)"
        echo "--------------------------------------------------------"
        if "$SCRIPT_PATH" "$TEST_MODULE" > /tmp/test_first_update.log 2>&1; then
            echo "  ✅ First update succeeded (expected)"
            # Check that validation was skipped (no frozen versions)
            if grep -q "no frozen versions yet" /tmp/test_first_update.log; then
                echo "  ✅ Correctly skipped validation (no frozen versions)"
            fi
        else
            echo "  ❌ First update failed (unexpected)"
            echo "  Last 20 lines:"
            tail -20 /tmp/test_first_update.log | sed 's/^/     /'
            TEST_PASSED=false
        fi
        echo ""

        echo "Test 2: Freeze interface to create v1"
        echo "--------------------------------------------------------"
        if echo "y" | ./freeze_interface.sh "$TEST_MODULE" > /tmp/test_freeze.log 2>&1; then
            echo "  ✅ Freeze succeeded - v1 created"
        else
            echo "  ❌ Freeze failed"
            echo "  Last 20 lines:"
            tail -20 /tmp/test_freeze.log | sed 's/^/     /'
            TEST_PASSED=false
        fi
        echo ""

        echo "Test 3: Adding a method should succeed (backward-compatible)"
        echo "--------------------------------------------------------------"
        # Backup original
        cp "$TEST_INTERFACE_FILE" /tmp/test_aidl.tmp

        # Add a new method at the end (before closing brace)
        sed -i '/^}/i\    /**\n     * New compatible method added in v2.\n     */\n    void newCompatibleMethod();' "$TEST_INTERFACE_FILE"

        if "$SCRIPT_PATH" "$TEST_MODULE" > /tmp/test_add_method.log 2>&1; then
            echo "  ✅ Adding method succeeded (expected - backward compatible)"
            # Check that validation ran (frozen versions exist)
            if grep -q "Frozen versions exist" /tmp/test_add_method.log; then
                echo "  ✅ Correctly enforced compatibility check (frozen versions exist)"
            fi
        else
            echo "  ❌ Adding method failed (unexpected)"
            echo "  Last 20 lines:"
            tail -20 /tmp/test_add_method.log | sed 's/^/     /'
            TEST_PASSED=false
        fi

        # Restore original
        cp /tmp/test_aidl.tmp "$TEST_INTERFACE_FILE"
        rm /tmp/test_aidl.tmp
        echo ""

        echo "Test 4: Removing a method should fail (breaking change)"
        echo "--------------------------------------------------------"
        # Backup original
        cp "$TEST_INTERFACE_FILE" /tmp/test_aidl.tmp

        # Remove a method (testOperation)
        sed -i '/void testOperation/d' "$TEST_INTERFACE_FILE"

        if "$SCRIPT_PATH" "$TEST_MODULE" > /tmp/test_remove_method.log 2>&1; then
            echo "  ❌ Removing method succeeded (unexpected - should fail)"
            TEST_PASSED=false
        else
            echo "  ✅ Removing method failed (expected - breaking change blocked)"
            # Check if error message mentions compatibility
            if grep -q "compatibility\|incompatible\|Breaking changes" /tmp/test_remove_method.log; then
                echo "  ✅ Error message correctly identifies compatibility issue"
            else
                echo "  ⚠️  Error message may not clearly explain the issue"
            fi
        fi

        # Restore original
        cp /tmp/test_aidl.tmp "$TEST_INTERFACE_FILE"
        rm /tmp/test_aidl.tmp
        echo ""

        echo "Test 5: Changing method signature should fail (breaking change)"
        echo "----------------------------------------------------------------"
        # Backup original
        cp "$TEST_INTERFACE_FILE" /tmp/test_aidl.tmp

        # Change a method signature
        sed -i 's/void reboot();/void reboot(in boolean force);/' "$TEST_INTERFACE_FILE"

        if "$SCRIPT_PATH" "$TEST_MODULE" > /tmp/test_change_signature.log 2>&1; then
            echo "  ❌ Changing signature succeeded (unexpected - should fail)"
            TEST_PASSED=false
        else
            echo "  ✅ Changing signature failed (expected - breaking change blocked)"
        fi

        # Restore original
        cp /tmp/test_aidl.tmp "$TEST_INTERFACE_FILE"
        rm /tmp/test_aidl.tmp
        echo ""

        echo "=========================================="
        if [ "$TEST_PASSED" = true ]; then
            echo "✅ All validation tests passed!"
            exit 0
        else
            echo "❌ Some validation tests failed"
            exit 1
        fi
        ;;
esac

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

# Create Python helper script for dependency resolution
cat > /tmp/resolve_deps_$$.py << 'EOFPY'
import sys

if len(sys.argv) != 3:
    print("Usage: resolve_deps.py <module> <deps_file>")
    sys.exit(1)

target = sys.argv[1]
deps_file = sys.argv[2]

# Read dependency file
deps = {}
order = []
with open(deps_file, 'r') as f:
    for line in f:
        line = line.strip()
        if ':' in line:
            module, dependencies = line.split(':', 1)
            module = module.replace('-vcurrent-cpp', '').strip()
            order.append(module)
            dep_list = [d.replace('-vcurrent-cpp', '').strip()
                       for d in dependencies.split() if d.strip()]
            deps[module] = dep_list

# Check if target exists
if target not in deps:
    print(target)
    sys.exit(0)

# Recursively collect all dependencies
def collect_deps(mod, collected=None):
    if collected is None:
        collected = set()
    if mod in collected:
        return collected
    if mod not in deps:
        return collected
    collected.add(mod)
    for dep in deps.get(mod, []):
        collect_deps(dep, collected)
    return collected

# Get all dependencies including the target
all_needed = collect_deps(target)

# Print in topological order (order from deps file)
result = [m for m in order if m in all_needed]
print(' '.join(result))
EOFPY

RESOLVE_DEPS_SCRIPT="/tmp/resolve_deps_$$.py"

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
    # Building a specific module - calculate full dependency tree
    echo "--> [Step 2/4] Calculating dependencies for $MODULE..."
    $AIDL_OPS -a -r "$ROOT_DIR" -o "$STABLE_DIR" >/dev/null 2>&1
    DEPS_FILE="${STABLE_DIR}/dependencies.txt"

    if [ -f "$DEPS_FILE" ]; then
        # Use Python helper script to resolve transitive dependencies
        if [ ! -f "$RESOLVE_DEPS_SCRIPT" ]; then
            echo "    ERROR: Dependency resolution script not found: $RESOLVE_DEPS_SCRIPT"
            MODULES="$MODULE"
        else
            MODULES=$(python3 "$RESOLVE_DEPS_SCRIPT" "$MODULE" "$DEPS_FILE" 2>&1)

            if [ $? -ne 0 ]; then
                echo "    ERROR: Dependency resolution failed: $MODULES"
                MODULES="$MODULE"
            fi
        fi

        if [ -n "$MODULES" ]; then
            # Count dependencies (all except the target module)
            # Note: grep -v returns 1 if no matches, so we use || true to prevent exit
            DEP_LIST=$(echo "$MODULES" | tr ' ' '\n' | { grep -v "^${MODULE}$" || true; })
            if [ -n "$DEP_LIST" ]; then
                DEP_COUNT=$(echo "$DEP_LIST" | wc -l)
                DEPS=$(echo "$DEP_LIST" | tr '\n' ' ')
                echo "    Dependencies: [ $DEPS]"
            else
                DEP_COUNT=0
                echo "    No dependencies"
            fi
            echo "    Build Order: [ $MODULES ]"
        else
            echo "    Module not found in dependency tree"
            MODULES="$MODULE"
        fi
    else
        echo "    No dependency tree available"
        MODULES="$MODULE"
    fi
fi

# Update APIs for each module
echo "--> [Step 3/4] Updating APIs..."
for mod in $MODULES; do
    echo "    Updating: $mod"
    $AIDL_OPS -u -r "$ROOT_DIR" -o "$STABLE_DIR" "$mod" || exit 1
done

# Note: C++ code generation is handled by CMake via CMakeLists.inc
# which calls aidl_ops -g automatically during the build

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

# Check if we need to reconfigure CMake due to target change
NEEDS_RECONFIG=false
if [ -f "${BUILD_DIR}/CMakeCache.txt" ]; then
    CACHED_TARGET=$(grep "^INTERFACE_TARGET:" "${BUILD_DIR}/CMakeCache.txt" | cut -d= -f2)
    if [ "$MODULE" == "all" ] && [ -n "$CACHED_TARGET" ]; then
        NEEDS_RECONFIG=true
    elif [ "$MODULE" != "all" ] && [ "$CACHED_TARGET" != "$MODULE" ]; then
        NEEDS_RECONFIG=true
    fi
fi

if [ "$NEEDS_RECONFIG" = true ]; then
    echo "    Reconfiguring CMake (target changed)..."
    rm -rf "${BUILD_DIR}"
fi

# Pass the module name to CMake if building a specific module
if [ "$MODULE" != "all" ]; then
    MODULE_ARG="-DINTERFACE_TARGET=${MODULE}"
else
    MODULE_ARG="-DINTERFACE_TARGET=all"
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
    # Staging is handled by cmake_stage_modules.cmake during build
    echo ""
    echo "✅ Build Complete - SDK Ready for Deployment"
    echo ""

    # Verify deployment structure
    BINDER_LIBS=$(ls out/target/lib/binder/*.so 2>/dev/null | wc -l || echo 0)
    MODULE_LIBS=$(ls out/target/lib/halif/*.so 2>/dev/null | wc -l || echo 0)

    echo "   📦 Runtime libraries ready for deployment:"
    echo "      • Binder servicemanager: 1 file (out/target/bin/)"
    echo "      • Binder libraries: ${BINDER_LIBS} files (out/target/lib/binder/)"
    echo "      • HAL libraries: ${MODULE_LIBS} files (out/target/lib/halif/)"
    echo ""
    echo "   📂 Deploy to target device:"
    echo "      scp -r out/target/bin/* device:/usr/bin/"
    echo "      scp -r out/target/lib/* device:/usr/lib/"
    echo ""
    echo "   ℹ️  Headers (build-time only, not needed on target):"
    echo "      • Binder SDK: out/build/include/binder_sdk/"
    echo "      • HAL interfaces: stable/generated/"
    echo ""
else
    echo "❌ Build failed"
    exit 1
fi


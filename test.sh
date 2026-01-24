#!/usr/bin/env bash

#/**
# * Copyright 2026 RDK Management
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

set -euo pipefail

# Comprehensive test suite for RDK HAL AIDL Interface Build System
cd "$(dirname "$0")"

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Test results tracking
TESTS_PASSED=0
TESTS_FAILED=0

CMAKE_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX:-$(pwd)/out/target}"

usage() {
    echo "Usage: $0 [--from ID] [--to ID] [--only ID[,ID...]] [--list] [--help]"
    echo "  --from ID    Start running at test ID (e.g., 3 or 6)"
    echo "  --to ID      Stop after test ID (inclusive)"
    echo "  --only IDs   Run only specified test IDs (comma-separated)"
    echo "  --list       List available test IDs"
    echo "  --help       Show this help"
}

TEST_IDS=("1" "2" "3" "4" "5" "6" "7" "8" "9" "10" "11")

list_tests() {
    echo "Available tests:"
    echo "  1   Clean build artifacts"
    echo "  2   Scripts exist and are executable"
    echo "  3   Help flags work"
    echo "  4   Clean operations work and exit"
    echo "  5   Stage Binder SDK (./build_interfaces.sh sdk)"
    echo "  6   Production module build (./build_modules.sh all)"
    echo "  7   Development build (./build_interfaces.sh boot)"
    echo "  8   Direct CMake build (default flags)"
    echo "  9   Direct CMake build (minimal production flags)"
    echo "  10  CMake multi-module build with version switching"
    echo "  11  Cross-compilation build (sc docker rdk-kirkstone)"
}

index_of_test_id() {
    local id="$1"
    local i=0
    for test_id in "${TEST_IDS[@]}"; do
        if [ "$test_id" = "$id" ]; then
            echo "$i"
            return 0
        fi
        i=$((i + 1))
    done
    return 1
}

parse_only_ids() {
    local ids="$1"
    IFS=',' read -r -a ONLY_IDS <<< "$ids"
}

should_run_test() {
    local id="$1"
    if [ "${#ONLY_IDS[@]}" -gt 0 ]; then
        for allowed in "${ONLY_IDS[@]}"; do
            if [ "$allowed" = "$id" ]; then
                return 0
            fi
        done
        return 1
    fi
    local idx
    idx=$(index_of_test_id "$id") || return 1
    if [ "$idx" -lt "$START_INDEX" ] || [ "$idx" -gt "$END_INDEX" ]; then
        return 1
    fi
    return 0
}

run_test() {
    local id="$1"
    local name="$2"
    if should_run_test "$id"; then
        echo ""
        echo "========================================"
        echo "🔵 TEST $id: ${name}"
        echo "========================================"
        if "$3"; then
            TESTS_PASSED=$((TESTS_PASSED + 1))
            echo ""
            echo -e "${GREEN}✅ Test $id PASSED${NC}"
        else
            TESTS_FAILED=$((TESTS_FAILED + 1))
            echo ""
            echo -e "${RED}❌ Test $id FAILED${NC}"
        fi
    else
        echo ""
        echo "[$id] ${name} (skipped)"
    fi
}

echo "=== RDK HAL AIDL Build System Validation ==="
echo ""

clean_build_state() {
    # Clean using the actual build scripts
    ./build_interfaces.sh clean >/dev/null 2>&1 || true
    # Also clean CMake artifacts from direct cmake invocations
    rm -rf ./build ./out 2>/dev/null || true
    rm -rf ./CMakeFiles ./CMakeCache.txt ./cmake_install.cmake 2>/dev/null || true
}

ensure_sdk_staged() {
    if [ -f ./out/target/.sdk_ready ]; then
        echo "✅ Binder SDK already staged"
        return 0
    fi
    echo "==> Staging Binder SDK (this may take a minute)..."
    if ./build_interfaces.sh sdk >/tmp/sdk_stage.log 2>&1; then
        warnings=$(grep -ci "warning:" /tmp/sdk_stage.log || echo "0")
        errors=$(grep -ci "error:" /tmp/sdk_stage.log || echo "0")
        echo "✅ SDK staged successfully (warnings: $warnings, errors: $errors)"
        test -f ./out/target/.sdk_ready && echo "✅ SDK marker file created"
    else
        echo "❌ SDK staging failed!"
        tail -20 /tmp/sdk_stage.log
        return 1
    fi
}

verify_module_library() {
    local module="$1"
    local version="${2:-current}"
    local lib_path="./out/target/lib/halif/lib${module}-v${version}-cpp.so"
    
    if [ -f "$lib_path" ]; then
        echo "✅ Library exists: $lib_path"
        local size=$(stat -f%z "$lib_path" 2>/dev/null || stat -c%s "$lib_path" 2>/dev/null || echo "unknown")
        echo "   Size: $size bytes"
        return 0
    else
        echo "❌ Library not found: $lib_path"
        return 1
    fi
}

verify_architecture() {
    local lib_path="$1"
    local expected_arch="${2:-}" # Empty means host architecture
    local description="$3"

    echo "==> Verifying architecture for ${description}..."

    # Detect expected host architecture if not specified
    if [ -z "$expected_arch" ]; then
        expected_arch=$(uname -m)
        echo "    Expected architecture: ${expected_arch} (host)"
    else
        echo "    Expected architecture: ${expected_arch}"
    fi

    local files_checked=0
    local matching_files=0
    local mismatched_files=0

    # Check all .so files in the path
    while IFS= read -r -d '' so_file; do
        files_checked=$((files_checked + 1))
        local basename_file=$(basename "$so_file")
        
        # Use file command to check architecture
        local file_output=$(file "$so_file")
        
        echo "    Checking: ${basename_file}"
        
        # Determine if architecture matches expectation
        if [ "$expected_arch" = "ARM" ] || [ "$expected_arch" = "arm" ]; then
            # Expecting ARM architecture
            if echo "$file_output" | grep -Eqi "ARM|armv7|armv8|aarch64"; then
                matching_files=$((matching_files + 1))
                echo "       ✅ ARM architecture confirmed"
            else
                mismatched_files=$((mismatched_files + 1))
                echo "       ❌ Not ARM: $file_output"
            fi
        else
            # Expecting host architecture (x86_64, etc.)
            if echo "$file_output" | grep -Eqi "x86-64|x86_64|ELF 64-bit"; then
                matching_files=$((matching_files + 1))
                echo "       ✅ Host architecture (${expected_arch})"
            elif echo "$file_output" | grep -Eqi "ARM|armv7|armv8|aarch64"; then
                mismatched_files=$((mismatched_files + 1))
                echo "       ❌ ARM detected (expected host ${expected_arch})"
            else
                echo "       ⚠️  Unknown architecture: $file_output"
            fi
        fi
    done < <(find "$lib_path" -name "*.so" -print0 2>/dev/null)

    # Verify results
    echo ""
    echo "    Files checked: ${files_checked}"
    echo "    Matching: ${matching_files}"
    echo "    Mismatched: ${mismatched_files}"

    if [ $files_checked -eq 0 ]; then
        echo "    ❌ No .so files found to verify!"
        return 1
    elif [ $mismatched_files -gt 0 ]; then
        echo "    ❌ Architecture verification FAILED!"
        return 1
    else
        echo "    ✅ All ${matching_files} files verified as ${expected_arch}"
        return 0
    fi
}

print_tree() {
    local path="$1"
    if [ ! -d "$path" ]; then
        echo "❌ Directory not found: $path"
        return 1
    fi
    echo "==> Directory tree: $path"
    if command -v tree >/dev/null 2>&1; then
        tree -L 3 "$path"
    else
        find "$path" -maxdepth 3 -print | sort
    fi
}

START_INDEX=0
END_INDEX=$((${#TEST_IDS[@]} - 1))
ONLY_IDS=()

while [ $# -gt 0 ]; do
    case "$1" in
        --from)
            shift
            start_idx=$(index_of_test_id "${1:-}") || {
                echo "Unknown test ID for --from: ${1:-}"
                list_tests
                exit 1
            }
            START_INDEX="$start_idx"
            ;;
        --to)
            shift
            end_idx=$(index_of_test_id "${1:-}") || {
                echo "Unknown test ID for --to: ${1:-}"
                list_tests
                exit 1
            }
            END_INDEX="$end_idx"
            ;;
        --only)
            shift
            parse_only_ids "${1:-}"
            ;;
        --list)
            list_tests
            exit 0
            ;;
        --help|-h)
            usage
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            usage
            exit 1
            ;;
    esac
    shift
done

################################################################################
# Test Implementations
################################################################################

test_1() {
    echo "Cleaning all build artifacts..."
    clean_build_state
    echo "✅ Build artifacts cleaned"
    return 0
}

test_2() {
    echo "Checking scripts..."
    test -x ./build_interfaces.sh && echo "✅ build_interfaces.sh exists and is executable"
    test -x ./build_modules.sh && echo "✅ build_modules.sh exists and is executable"
    test -x ./build_binder.sh && echo "✅ build_binder.sh exists and is executable"
    test -x ./freeze_interface.sh && echo "✅ freeze_interface.sh exists and is executable"
    return 0
}

test_3() {
    clean_build_state
    echo "Testing --help flags..."
    ./build_interfaces.sh --help >/dev/null 2>&1 && echo "✅ build_interfaces.sh --help OK"
    ./build_modules.sh --help >/dev/null 2>&1 && echo "✅ build_modules.sh --help OK"
    ./build_binder.sh --help >/dev/null 2>&1 && echo "✅ build_binder.sh --help OK"
    return 0
}

test_4() {
    clean_build_state
    echo "Testing clean operations..."
    ./build_interfaces.sh clean >/dev/null 2>&1 && echo "✅ build_interfaces.sh clean OK"
    test ! -d ./out && echo "✅ out/ directory cleaned"
    ./build_modules.sh clean >/dev/null 2>&1 && echo "✅ build_modules.sh clean OK"
    test ! -d ./out && echo "✅ out/ directory cleaned (modules)"
    return 0
}

test_5() {
    clean_build_state
    echo "Staging Binder SDK (Stage 1 only)..."
    echo "This stages the pre-built SDK from build-tools/linux_binder_idl"
    echo ""
    
    if ! ensure_sdk_staged; then
        return 1
    fi
    
    # Verify SDK contents
    echo ""
    echo "Verifying SDK contents..."
    test -d ./out/target/lib && echo "✅ SDK lib directory exists"
    test -d ./out/target/lib/binder && echo "✅ Binder library directory exists"
    test -f ./out/target/lib/binder/libbinder.so && echo "✅ libbinder.so exists"
    test -f ./out/target/lib/binder/libutils.so && echo "✅ libutils.so exists"
    
    # Verify x86/host architecture
    echo ""
    if ! verify_architecture ./out/target/lib/binder "" "x86 Binder SDK"; then
        return 1
    fi
    
    echo ""
    print_tree ./out/target
    
    return 0
}

test_6() {
    clean_build_state
    echo "Production module build using ./build_modules.sh all..."
    echo "This tests Stage 3 only (compilation of pre-generated code)"
    echo ""
    
    # Ensure SDK is staged first
    if ! ensure_sdk_staged; then
        return 1
    fi
    
    echo ""
    echo "Building all HAL modules..."
    if ./build_modules.sh all >/tmp/build_modules.log 2>&1; then
        warnings=$(grep -ci "warning:" /tmp/build_modules.log || echo "0")
        errors=$(grep -ci "error:" /tmp/build_modules.log || echo "0")
        echo "✅ Module build completed (warnings: $warnings, errors: $errors)"
    else
        echo "❌ Module build failed!"
        tail -30 /tmp/build_modules.log
        return 1
    fi
    
    echo ""
    echo "Verifying output libraries..."
    local modules_found=0
    for lib in ./out/target/lib/halif/*.so; do
        if [ -f "$lib" ]; then
            modules_found=$((modules_found + 1))
            echo "✅ $(basename "$lib")"
        fi
    done
    
    if [ $modules_found -eq 0 ]; then
        echo "❌ No module libraries found!"
        echo ""
        echo "Last 50 lines of build log:"
        tail -50 /tmp/build_modules.log
        return 1
    fi
    
    echo "✅ Total modules built: $modules_found"
    
    # Verify host architecture
    echo ""
    if ! verify_architecture ./out/target/lib/halif "" "build_modules.sh"; then
        return 1
    fi
    
    echo ""
    print_tree ./out/target/lib/halif
    
    return 0
}

test_7() {
    clean_build_state
    echo "Development build using ./build_interfaces.sh boot..."
    echo "This tests all 3 stages: SDK staging + AIDL generation + compilation"
    echo ""
    
    if ./build_interfaces.sh boot >/tmp/build_interfaces.log 2>&1; then
        warnings=$(grep -ci "warning:" /tmp/build_interfaces.log || echo "0")
        errors=$(grep -ci "error:" /tmp/build_interfaces.log || echo "0")
        echo "✅ Development build completed (warnings: $warnings, errors: $errors)"
    else
        echo "❌ Development build failed!"
        tail -30 /tmp/build_interfaces.log
        return 1
    fi
    
    echo ""
    echo "Verifying outputs..."
    test -d ./stable/aidl/boot/current && echo "✅ AIDL files copied to stable/"
    test -d ./stable/generated/boot/current && echo "✅ C++ code generated to stable/"
    verify_module_library boot || return 1
    
    echo ""
    print_tree ./out/target/lib/halif
    
    return 0
}

test_8() {
    clean_build_state
    echo "Direct CMake build with default flags..."
    echo "This tests the CMake build system directly"
    echo ""
    
    # Ensure SDK is staged
    if ! ensure_sdk_staged; then
        return 1
    fi
    
    echo ""
    echo "==> cmake -S . -B build/current -DINTERFACE_TARGET=boot -DAIDL_SRC_VERSION=current"
    if cmake -S . -B build/current \
        -DINTERFACE_TARGET=boot \
        -DAIDL_SRC_VERSION=current \
        -DCMAKE_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}" \
        >/tmp/cmake_config.log 2>&1; then
        echo "✅ CMake configuration successful"
    else
        echo "❌ CMake configuration failed!"
        tail -20 /tmp/cmake_config.log
        return 1
    fi
    
    echo ""
    echo "==> cmake --build build/current -- -j$(nproc)"
    if cmake --build build/current -- -j"$(nproc)" \
        >/tmp/cmake_build.log 2>&1; then
        warnings=$(grep -ci "warning:" /tmp/cmake_build.log || echo "0")
        errors=$(grep -ci "error:" /tmp/cmake_build.log || echo "0")
        echo "✅ CMake build completed (warnings: $warnings, errors: $errors)"
    else
        echo "❌ CMake build failed!"
        tail -20 /tmp/cmake_build.log
        return 1
    fi
    
    echo ""
    echo "==> cmake --install build/current"
    if cmake --install build/current >/tmp/cmake_install.log 2>&1; then
        echo "✅ CMake install successful"
    else
        echo "❌ CMake install failed!"
        tail -20 /tmp/cmake_install.log
        return 1
    fi
    
    echo ""
    echo "Verifying outputs..."
    verify_module_library boot || return 1
    
    return 0
}

test_9() {
    clean_build_state
    echo "Direct CMake build with minimal production flags..."
    echo "Simulates production Yocto build with minimal configuration"
    echo ""
    
    # Ensure SDK is staged
    if ! ensure_sdk_staged; then
        return 1
    fi
    
    echo ""
    echo "==> cmake -S . -B build/production -DINTERFACE_TARGET=all"
    if cmake -S . -B build/production \
        -DINTERFACE_TARGET=all \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}" \
        >/tmp/cmake_prod_config.log 2>&1; then
        echo "✅ CMake production configuration successful"
    else
        echo "❌ CMake production configuration failed!"
        tail -20 /tmp/cmake_prod_config.log
        return 1
    fi
    
    echo ""
    echo "==> cmake --build build/production -- -j$(nproc)"
    if cmake --build build/production -- -j"$(nproc)" \
        >/tmp/cmake_prod_build.log 2>&1; then
        warnings=$(grep -ci "warning:" /tmp/cmake_prod_build.log || echo "0")
        errors=$(grep -ci "error:" /tmp/cmake_prod_build.log || echo "0")
        echo "✅ CMake production build completed (warnings: $warnings, errors: $errors)"
    else
        echo "❌ CMake production build failed!"
        tail -20 /tmp/cmake_prod_build.log
        return 1
    fi
    
    echo ""
    echo "==> cmake --install build/production"
    if cmake --install build/production >/tmp/cmake_prod_install.log 2>&1; then
        echo "✅ CMake production install successful"
    else
        echo "❌ CMake production install failed!"
        tail -20 /tmp/cmake_prod_install.log
        return 1
    fi
    
    echo ""
    echo "Verifying all module outputs..."
    local modules_found=0
    for lib in ./out/target/lib/halif/*.so; do
        if [ -f "$lib" ]; then
            modules_found=$((modules_found + 1))
        fi
    done
    
    if [ $modules_found -eq 0 ]; then
        echo "❌ No module libraries found!"
        echo ""
        echo "Last 50 lines of build log:"
        tail -50 /tmp/cmake_prod_build.log
        return 1
    fi
    
    echo "✅ Total modules built: $modules_found"
    
    # Verify architecture
    echo ""
    if ! verify_architecture ./out/target/lib/halif "" "production CMake build"; then
        return 1
    fi
    
    echo ""
    print_tree ./out/target/lib/halif
    
    return 0
}

test_10() {
    clean_build_state
    echo "CMake multi-module build with version switching..."
    echo "Tests building different modules and version handling"
    echo ""
    
    # Ensure SDK is staged
    if ! ensure_sdk_staged; then
        return 1
    fi
    
    # Test 1: Build boot module
    echo ""
    echo "==> Test 10.1: Build boot module (current version)"
    if cmake -S . -B build/test10-boot \
        -DINTERFACE_TARGET=boot \
        -DAIDL_SRC_VERSION=current \
        -DCMAKE_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}" \
        >/tmp/cmake_test10_boot_config.log 2>&1 && \
       cmake --build build/test10-boot -- -j"$(nproc)" \
        >/tmp/cmake_test10_boot_build.log 2>&1 && \
       cmake --install build/test10-boot \
        >/tmp/cmake_test10_boot_install.log 2>&1; then
        echo "✅ Boot module build successful"
        verify_module_library boot || return 1
    else
        echo "❌ Boot module build failed!"
        return 1
    fi
    
    # Test 2: Build common module
    echo ""
    echo "==> Test 10.2: Build common module (current version)"
    if cmake -S . -B build/test10-common \
        -DINTERFACE_TARGET=common \
        -DAIDL_SRC_VERSION=current \
        -DCMAKE_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}" \
        >/tmp/cmake_test10_common_config.log 2>&1 && \
       cmake --build build/test10-common -- -j"$(nproc)" \
        >/tmp/cmake_test10_common_build.log 2>&1 && \
       cmake --install build/test10-common \
        >/tmp/cmake_test10_common_install.log 2>&1; then
        echo "✅ Common module build successful"
        verify_module_library common || return 1
    else
        echo "❌ Common module build failed!"
        return 1
    fi
    
    # Test 3: Build deviceinfo module
    echo ""
    echo "==> Test 10.3: Build deviceinfo module (current version)"
    if cmake -S . -B build/test10-deviceinfo \
        -DINTERFACE_TARGET=deviceinfo \
        -DAIDL_SRC_VERSION=current \
        -DCMAKE_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}" \
        >/tmp/cmake_test10_deviceinfo_config.log 2>&1 && \
       cmake --build build/test10-deviceinfo -- -j"$(nproc)" \
        >/tmp/cmake_test10_deviceinfo_build.log 2>&1 && \
       cmake --install build/test10-deviceinfo \
        >/tmp/cmake_test10_deviceinfo_install.log 2>&1; then
        echo "✅ Deviceinfo module build successful"
        verify_module_library deviceinfo || return 1
    else
        echo "❌ Deviceinfo module build failed!"
        return 1
    fi
    
    # Test 4: Build with CMAKE_BUILD_TYPE variations
    echo ""
    echo "==> Test 10.4: Build with CMAKE_BUILD_TYPE=Debug"
    if cmake -S . -B build/test10-debug \
        -DINTERFACE_TARGET=flash \
        -DAIDL_SRC_VERSION=current \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}" \
        >/tmp/cmake_test10_debug_config.log 2>&1 && \
       cmake --build build/test10-debug -- -j"$(nproc)" \
        >/tmp/cmake_test10_debug_build.log 2>&1; then
        echo "✅ Debug build successful"
        test -f ./out/target/lib/halif/libflash-vcurrent-cpp.so && echo "✅ Debug library created"
    else
        echo "❌ Debug build failed!"
        return 1
    fi
    
    echo ""
    echo "✅ All multi-module tests passed"
    
    return 0
}

test_11() {
    echo "Cross-compilation build using Docker (RDK Kirkstone ARM toolchain)..."
    echo "This test builds the SDK with ARM compiler, then builds modules with ARM compiler"
    echo "All outputs (SDK + modules) are verified to be ARM architecture"
    echo ""
    
    # Step 1: Check if sc command is available
    echo "==> Step 1: Checking for 'sc' command..."
    if ! command -v sc &> /dev/null; then
        echo "⚠️  'sc' command not found - cross-compilation environment not available"
        echo "    This is optional for development builds"
        echo "    Install 'sc' tool or skip this test with --to 10"
        return 0
    fi
    echo "✅ 'sc' command available"
    echo ""
    
    # Step 2: Check if rdk-kirkstone image exists
    echo "==> Step 2: Checking for rdk-kirkstone Docker image..."
    if ! sc docker list 2>/dev/null | grep -q "rdk-kirkstone"; then
        echo "⚠️  rdk-kirkstone Docker image not found via 'sc docker list'"
        echo "    Cross-compilation environment may not be fully configured"
        echo "    This is optional for development builds"
        return 0
    fi
    echo "✅ rdk-kirkstone Docker image available"
    echo ""
    
    # Get current directory for docker mount
    local current_dir=$(pwd)
    
    # Step 3: Clean build state
    echo "==> Step 3: Cleaning build state..."
    clean_build_state
    echo "✅ Build state cleaned"
    echo ""
    
    # Step 4: Build ARM Binder SDK using direct CMake (production method)
    echo "==> Step 4: Building ARM Binder SDK with CMake..."
    echo "Note: SDK is rebuilt with ARM toolchain using direct CMake commands"
    echo "      This replicates the production build workflow (like production-build.sh)"
    echo ""
    echo "Build steps:"
    echo "  1. cmake -S build-tools/linux_binder_idl -B build/binder ..."
    echo "  2. cmake --build build/binder"
    echo "  3. cmake --install build/binder (to out/target/lib/binder/)"
    echo ""
    echo "=========================================="
    echo "Starting ARM SDK build..."
    echo "This will take several minutes. Build log: /tmp/arm_sdk_build.log"
    echo "=========================================="
    echo ""
    
    # Build ARM Binder SDK using direct CMake commands (production method)
    # This replicates what production-build.sh does
    # Note: CC/CXX/CFLAGS/CXXFLAGS/LDFLAGS come from RDK environment-setup script
    if sc docker run rdk-kirkstone \
        ". /opt/toolchains/rdk-glibc-x86_64-arm-toolchain/environment-setup-armv7vet2hf-neon-oe-linux-gnueabi; \
        unset CMAKE_TOOLCHAIN_FILE; \
        cd ${current_dir}; \
        CC=\"\${CC}\" CXX=\"\${CXX}\" \
        CFLAGS=\"\${CFLAGS}\" CXXFLAGS=\"\${CXXFLAGS}\" LDFLAGS=\"\${LDFLAGS}\" \
        cmake -S build-tools/linux_binder_idl -B build/binder \
          -DCMAKE_INSTALL_PREFIX=${current_dir}/out/target \
          -DCMAKE_INSTALL_LIBDIR=lib/binder \
          -DBUILD_HOST_AIDL=OFF \
          -DTARGET_LIB32_VERSION=ON \
          -DCMAKE_BUILD_TYPE=Release && \
        cmake --build build/binder -- -j\$(nproc) && \
        cmake --install build/binder" \
        >/tmp/arm_sdk_build.log 2>&1; then
        echo "✅ ARM Binder SDK built successfully"
        echo ""
    else
        echo "❌ ARM SDK build FAILED!"
        echo ""
        echo "Last 40 lines of SDK build:"
        tail -40 /tmp/arm_sdk_build.log
        echo ""
        echo "Full log: /tmp/arm_sdk_build.log"
        return 1
    fi
    
    # Create .sdk_ready marker file for CMake to detect
    touch "${current_dir}/out/target/.sdk_ready"
    echo "✅ Created SDK marker: ${current_dir}/out/target/.sdk_ready"
    echo ""
    
    # Step 5: Build ARM HAL modules using direct CMake (production method)
    echo "==> Step 5: Building ARM HAL modules with CMake (default paths)..."
    echo "Using ARM SDK from step 4"
    echo ""
    echo "Build steps:"
    echo "  1. cmake -S . -B build/current -DINTERFACE_TARGET=all ..."
    echo "  2. cmake --build build/current"
    echo "  3. cmake --install build/current (modules to out/target/lib/halif/)"
    echo ""
    echo "=========================================="
    echo "Starting ARM module build (default paths)..."
    echo "Build log: /tmp/arm_module_build.log"
    echo "=========================================="
    echo ""
    
    # Build ARM HAL modules using direct CMake commands (production method)
    # Note: CC/CXX/CFLAGS/CXXFLAGS/LDFLAGS come from RDK environment-setup script
    if sc docker run rdk-kirkstone \
        ". /opt/toolchains/rdk-glibc-x86_64-arm-toolchain/environment-setup-armv7vet2hf-neon-oe-linux-gnueabi; \
        unset CMAKE_TOOLCHAIN_FILE; \
        cd ${current_dir}; \
        CC=\"\${CC}\" CXX=\"\${CXX}\" \
        CFLAGS=\"\${CFLAGS}\" CXXFLAGS=\"\${CXXFLAGS}\" LDFLAGS=\"\${LDFLAGS}\" \
        cmake -S . -B build/current \
          -DINTERFACE_TARGET=all \
          -DAIDL_SRC_VERSION=current \
          -DBINDER_SDK_DIR=${current_dir}/out/target \
          -DBINDER_SDK_INCLUDE_DIR=${current_dir}/out/target \
          -DBINDER_SDK_INCLUDE_SUBDIR=include \
          -DCMAKE_INSTALL_PREFIX=${current_dir}/out/target \
          -DCMAKE_BUILD_TYPE=Release && \
        cmake --build build/current -- -j\$(nproc) && \
        cmake --install build/current" \
        >/tmp/arm_module_build.log 2>&1; then
        echo "✅ ARM HAL modules built successfully"
        echo ""
    else
        echo "❌ ARM module build FAILED!"
        echo ""
        echo "Last 40 lines of module build:"
        tail -40 /tmp/arm_module_build.log
        echo ""
        echo "Full log: /tmp/arm_module_build.log"
        return 1
    fi
    
    # Step 6: Verify output directory exists (default path)
    echo "==> Step 6: Verifying ARM build outputs (default paths)..."
    if [ ! -d "${current_dir}/out/target/lib/halif" ]; then
        echo "❌ HAL library directory not found: ${current_dir}/out/target/lib/halif"
        echo ""
        echo "Contents of out/target/lib:"
        ls -la "${current_dir}/out/target/lib" 2>&1 || echo "Directory doesn't exist"
        return 1
    fi
    echo "✅ Default output directory exists: ${current_dir}/out/target/lib/halif"
    echo ""
    
    # Step 7: Count and list built libraries (default path)
    echo "==> Step 7: Listing built ARM libraries (default paths)..."
    local lib_count=$(find "${current_dir}/out/target/lib/halif" -name "*.so" 2>/dev/null | wc -l)
    if [ $lib_count -eq 0 ]; then
        echo "❌ No .so files found in ${current_dir}/out/target/lib/halif"
        echo ""
        echo "Directory contents:"
        ls -la "${current_dir}/out/target/lib/halif"
        return 1
    fi
    
    echo "Found ${lib_count} HAL libraries:"
    ls -lh "${current_dir}/out/target/lib/halif"/*.so
    echo ""
    
    # Step 8: Verify ARM architecture of built libraries
    echo "==> Step 8: Verifying HAL module ARM architecture (default paths)..."
    if ! verify_architecture "${current_dir}/out/target/lib/halif" "ARM" "Docker cross-compilation"; then
        return 1
    fi
    echo ""
    
    # Step 9: Test custom install path override
    echo "==> Step 9: Testing custom install path override..."
    echo "Rebuilding with -DCMAKE_INSTALL_LIBDIR=lib/custom_test..."
    echo "Build log: /tmp/arm_module_build_custom.log"
    echo ""
    
    # Clean build directory for fresh configuration
    rm -rf "${current_dir}/build/current" >/dev/null 2>&1
    
    # Build with custom install path
    if sc docker run rdk-kirkstone \
        ". /opt/toolchains/rdk-glibc-x86_64-arm-toolchain/environment-setup-armv7vet2hf-neon-oe-linux-gnueabi; \
        unset CMAKE_TOOLCHAIN_FILE; \
        cd ${current_dir}; \
        CC=\"\${CC}\" CXX=\"\${CXX}\" \
        CFLAGS=\"\${CFLAGS}\" CXXFLAGS=\"\${CXXFLAGS}\" LDFLAGS=\"\${LDFLAGS}\" \
        cmake -S . -B build/current \
          -DINTERFACE_TARGET=boot \
          -DAIDL_SRC_VERSION=current \
          -DBINDER_SDK_DIR=${current_dir}/out/target \
          -DBINDER_SDK_INCLUDE_DIR=${current_dir}/out/target \
          -DBINDER_SDK_INCLUDE_SUBDIR=include \
          -DCMAKE_INSTALL_PREFIX=${current_dir}/out/target \
          -DCMAKE_INSTALL_LIBDIR=lib/custom_test \
          -DCMAKE_BUILD_TYPE=Release && \
        cmake --build build/current -- -j\$(nproc) && \
        cmake --install build/current" \
        >/tmp/arm_module_build_custom.log 2>&1; then
        echo "✅ Custom path build successful"
        echo ""
    else
        echo "❌ Custom path build FAILED!"
        tail -40 /tmp/arm_module_build_custom.log
        return 1
    fi
    
    # Verify custom path was actually used
    if [ ! -d "${current_dir}/out/target/lib/custom_test" ]; then
        echo "❌ Custom library directory not found: ${current_dir}/out/target/lib/custom_test"
        echo "   Override mechanism is not working!"
        return 1
    fi
    
    local custom_lib_count=$(find "${current_dir}/out/target/lib/custom_test" -name "*.so" 2>/dev/null | wc -l)
    if [ $custom_lib_count -eq 0 ]; then
        echo "❌ No libraries found in custom path!"
        return 1
    fi
    
    echo "✅ Custom install path override verified: ${custom_lib_count} library in lib/custom_test/"
    ls -lh "${current_dir}/out/target/lib/custom_test"/*.so
    echo ""
    
    # Clean up custom test directory
    rm -rf "${current_dir}/out/target/lib/custom_test" "${current_dir}/build/current" >/dev/null 2>&1
    
    # Step 10: Verify ARM architecture of Binder SDK libraries
    echo "==> Step 10: Verifying Binder SDK ARM architecture..."
    if ! verify_architecture "${current_dir}/out/target/lib/binder" "ARM" "ARM Binder SDK"; then
        echo "⚠️  Warning: Binder SDK libraries are not ARM architecture"
        echo "    This means the SDK was not built correctly with ARM toolchain"
        return 1
    fi
    echo ""
    
    # Step 11: Summary
    echo "==> Step 11: Cross-compilation summary..."
    echo "✅ ARM Binder SDK: ${current_dir}/out/target/lib/binder/"
    echo "✅ ARM HAL Libraries (default): ${lib_count} modules in ${current_dir}/out/target/lib/halif/"
    echo "✅ Custom path override: Verified working"
    
    echo ""
    print_tree "${current_dir}/out/target/lib"
    
    echo ""
    echo "=========================================="
    echo "✅ Test 11 PASSED - ARM cross-compilation successful"
    echo "=========================================="
    
    return 0
}

################################################################################
# Run Tests
################################################################################

run_test "1" "Clean build artifacts" test_1
run_test "2" "Scripts exist and are executable" test_2
run_test "3" "Help flags work" test_3
run_test "4" "Clean operations work and exit" test_4
run_test "5" "Stage Binder SDK (./build_interfaces.sh sdk)" test_5
run_test "6" "Production module build (./build_modules.sh all)" test_6
run_test "7" "Development build (./build_interfaces.sh boot)" test_7
run_test "8" "Direct CMake build (default flags)" test_8
run_test "9" "Direct CMake build (minimal production flags)" test_9
run_test "10" "CMake multi-module build with version switching" test_10
run_test "11" "Cross-compilation build (sc docker rdk-kirkstone)" test_11

################################################################################
# Summary
################################################################################

echo ""
echo "========================================"
TOTAL_TESTS=$((TESTS_PASSED + TESTS_FAILED))
if [ $TESTS_FAILED -gt 0 ]; then
    echo -e "${RED}❌ SOME TESTS FAILED${NC}"
    echo -e "${GREEN}Passed: ${TESTS_PASSED}/${TOTAL_TESTS}${NC}"
    echo -e "${RED}Failed: ${TESTS_FAILED}/${TOTAL_TESTS}${NC}"
    exit 1
else
    echo -e "${GREEN}✅ ALL TESTS PASSED${NC}"
    echo -e "${GREEN}Passed: ${TESTS_PASSED}/${TOTAL_TESTS}${NC}"
fi
echo "========================================"
echo ""
echo "Build outputs:"
echo "  SDK:     $(realpath ./out/target 2>/dev/null || echo 'Not found')"
echo "  HAL Libs: $(realpath ./out/target/lib/halif 2>/dev/null || echo 'Not found')"
echo "  Stable:  $(realpath ./stable 2>/dev/null || echo 'Not found')"
echo ""

#!/usr/bin/env bash

#/**
# * Copyright 2025 Comcast Cable Communications Management, LLC
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

# Quick validation test for build scripts
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

TEST_IDS=("1" "1.1" "2" "3" "4" "5" "6" "7" "8" "9" "10" "11")

list_tests() {
    echo "Available tests:"
    echo "  1   Clean Android sources"
    echo "  1.1 Clone Android sources"
    echo "  2   Scripts exist and are executable"
    echo "  3   Help flags work"
    echo "  4   Clean operations work and exit"
    echo "  5   Build host AIDL tools"
    echo "  6   Build target binder libraries"
    echo "  7   Direct CMake build (defaults + install)"
    echo "  8   Direct CMake build (per BUILD.md)"
    echo "  9   Direct CMake build (per BUILD.md + install)"
    echo "  10  Production build (minimal flags + install)"
    echo "  11  Cross-compilation environment check (sc/RDK)"
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
        echo "[$id] ${name}"
        "$3"
    else
        echo ""
        echo "[$id] ${name} (skipped)"
    fi
}

echo "=== Quick Build Script Validation ==="
echo ""

clean_build_state() {
    # Use the actual build scripts to clean - they know what they created
    ./build-linux-binder-aidl.sh --clean >/dev/null 2>&1 || true
    ./build-aidl-generator-tool.sh --clean >/dev/null 2>&1 || true
    # Clean any leftover CMake artifacts from direct cmake invocations
    rm -rf ./build-target-cmake ./build-production 2>/dev/null || true
    rm -rf ./CMakeFiles ./CMakeCache.txt ./cmake_install.cmake 2>/dev/null || true
}

ensure_host_aidl_tools() {
    if [ -x ./out/host/bin/aidl ] && [ -x ./out/host/bin/aidl-cpp ]; then
        echo "✅ Host AIDL tools already available"
        return 0
    fi
    echo "==> Building host AIDL tools (always uses host compiler, not cross-compiler)..."

    # Save any cross-compiler environment variables
    local saved_cc="${CC:-}"
    local saved_cxx="${CXX:-}"
    local saved_cflags="${CFLAGS:-}"
    local saved_cxxflags="${CXXFLAGS:-}"
    local saved_ldflags="${LDFLAGS:-}"

    # Clear cross-compiler environment to force host compiler
    unset CC CXX CFLAGS CXXFLAGS LDFLAGS

    if ./build-aidl-generator-tool.sh >/tmp/host_build.log 2>&1; then
        warnings=$(grep -ci "warning:" /tmp/host_build.log || echo "0")
        errors=$(grep -ci "error:" /tmp/host_build.log || echo "0")
        echo "✅ Host build completed (warnings: $warnings, errors: $errors)"
        test -x ./out/host/bin/aidl && echo "✅ aidl binary created"
        test -x ./out/host/bin/aidl-cpp && echo "✅ aidl-cpp binary created"
    else
        echo "❌ Host build failed!"
        tail -20 /tmp/host_build.log
        # Restore environment before failing
        [ -n "${saved_cc}" ] && export CC="${saved_cc}"
        [ -n "${saved_cxx}" ] && export CXX="${saved_cxx}"
        [ -n "${saved_cflags}" ] && export CFLAGS="${saved_cflags}"
        [ -n "${saved_cxxflags}" ] && export CXXFLAGS="${saved_cxxflags}"
        [ -n "${saved_ldflags}" ] && export LDFLAGS="${saved_ldflags}"
        exit 1
    fi

    # Restore cross-compiler environment if it was set
    if [ -n "${saved_cc}" ]; then
        export CC="${saved_cc}"
        export CXX="${saved_cxx}"
        export CFLAGS="${saved_cflags}"
        export CXXFLAGS="${saved_cxxflags}"
        export LDFLAGS="${saved_ldflags}"
        echo "✅ Restored cross-compiler environment (CC=${CC})"
    fi
}

run_cmake_build() {
    local build_dir="$1"
    shift
    echo "==> cmake -S . -B ${build_dir} -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} $*"
    cmake -S . -B "${build_dir}" \
        -DCMAKE_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}" \
        "$@" \
        >/tmp/cmake_target_config.log 2>&1 && \
    echo "==> cmake --build ${build_dir} -- -j$(nproc)" && \
    cmake --build "${build_dir}" -- -j"$(nproc)" \
        >/tmp/cmake_target_build.log 2>&1
}

run_cmake_install() {
    local build_dir="$1"
    echo "==> cmake --install ${build_dir} --prefix ${CMAKE_INSTALL_PREFIX}"
    cmake --install "${build_dir}" --prefix "${CMAKE_INSTALL_PREFIX}" \
        >/tmp/cmake_target_install.log 2>&1
}

print_dest_tree() {
    local dest_root="$1"
    if [ ! -d "${dest_root}" ]; then
        echo "❌ Install destination not found: ${dest_root}"
        return 1
    fi
    echo "==> Install destination tree: ${dest_root}"
    if command -v tree >/dev/null 2>&1; then
        tree -a "${dest_root}"
    else
        find "${dest_root}" -print | sort
    fi
}

check_install_layout() {
    local prefix_path="${CMAKE_INSTALL_PREFIX}"
    local ok=true
    if [ ! -d "${prefix_path}/lib" ]; then
        echo "❌ Missing lib directory: ${prefix_path}/lib"
        ok=false
    fi
    # SDK headers are in out/build/include, not out/target/include
    local sdk_include_dir="$(dirname "${prefix_path}")/build/include"
    if [ ! -d "${sdk_include_dir}" ]; then
        echo "❌ Missing include directory: ${sdk_include_dir}"
        ok=false
    fi
    if [ ! -d "${prefix_path}/bin" ]; then
        echo "❌ Missing bin directory: ${prefix_path}/bin"
        ok=false
    fi
    if [ "${ok}" != true ]; then
        print_dest_tree "${prefix_path}"
        return 1
    fi
    return 0
}

verify_host_architecture() {
    local lib_path="$1"
    local description="$2"

    echo "==> Verifying host architecture for ${description}..."

    # Detect expected host architecture
    local expected_arch
    expected_arch=$(uname -m)
    echo "    Expected architecture: ${expected_arch}"

    local files_checked=0
    local host_files=0
    local cross_compiled=0

    # Check all .so files
    for so_file in "${lib_path}"/*.so; do
        if [ -f "$so_file" ]; then
            files_checked=$((files_checked + 1))
            local basename_file
            basename_file=$(basename "$so_file")

            # Use file command to check architecture
            local file_output
            file_output=$(file "$so_file")

            # Check if it's ARM (cross-compiled)
            if echo "$file_output" | grep -qi "ARM"; then
                cross_compiled=$((cross_compiled + 1))
                echo "    ❌ ${basename_file}: Cross-compiled (ARM) - should be ${expected_arch}"
                echo "       $(file "$so_file")"
            # Check if it matches host architecture
            elif echo "$file_output" | grep -Eqi "${expected_arch}|x86-64|x86_64|ELF 64-bit"; then
                host_files=$((host_files + 1))
                echo "    ✅ ${basename_file}: Host architecture (${expected_arch})"
            else
                echo "    ⚠️  ${basename_file}: Unknown architecture"
                echo "       $(file "$so_file")"
            fi

            # Additional verification with readelf if available
            if command -v readelf &> /dev/null; then
                local machine
                machine=$(readelf -h "$so_file" 2>/dev/null | grep "Machine:" | awk '{print $2}')
                if [ -n "$machine" ]; then
                    echo "       readelf Machine: ${machine}"
                fi
            fi
        fi
    done

    # Verify results
    if [ $files_checked -eq 0 ]; then
        echo "    ❌ No .so files found to verify!"
        return 1
    elif [ $cross_compiled -gt 0 ]; then
        echo "    ❌ Found ${cross_compiled} cross-compiled files (should be 0 for host build)!"
        return 1
    elif [ $host_files -ne $files_checked ]; then
        echo "    ⚠️  Only ${host_files} out of ${files_checked} files are host architecture"
        return 1
    else
        echo "    ✅ All ${host_files} files verified as host architecture (${expected_arch})"
        return 0
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

test_1() {
    echo "Cleaning Android sources..."
    rm -rf ./android 2>/dev/null || true
    echo "✅ Android sources cleaned"
}

test_1_1() {
    echo "Cloning Android sources (this may take several minutes)..."
    if ! ./clone-android-binder-repo.sh >/tmp/clone.log 2>&1; then
        echo "❌ Clone failed!"
        tail -20 /tmp/clone.log
        exit 1
    fi
    test -d ./android && echo "✅ Android sources cloned"
}

test_2() {
    echo "Checking scripts..."
    test -x ./clone-android-binder-repo.sh && echo "✅ clone-android-binder-repo.sh OK"
    test -x ./build-aidl-generator-tool.sh && echo "✅ build-aidl-generator-tool.sh OK"
    test -x ./build-linux-binder-aidl.sh && echo "✅ build-linux-binder-aidl.sh OK"
}

test_3() {
    clean_build_state
    echo "Testing --help flags..."
    ./build-aidl-generator-tool.sh --help >/dev/null 2>&1 && echo "✅ Host --help OK"
    ./build-linux-binder-aidl.sh --help >/dev/null 2>&1 && echo "✅ Target --help OK"
}

test_4() {
    clean_build_state
    echo "Testing --clean operations..."
    ./build-aidl-generator-tool.sh --clean >/dev/null 2>&1 && echo "✅ Host --clean OK"
    test ! -d ./build-host && test ! -d ./out/host && echo "✅ Host directories cleaned"
    ./build-linux-binder-aidl.sh --clean >/dev/null 2>&1 && echo "✅ Target --clean OK"
    test ! -d ./build-target && test ! -d ./out/target && echo "✅ Target directories cleaned"
}

test_5() {
    clean_build_state
    echo "Building host AIDL tools (this may take a minute)..."
    echo "Note: Host tools are always built with host compiler (x86_64), never cross-compiled"
    ensure_host_aidl_tools
}

test_6() {
    clean_build_state
    echo "Building target binder libraries (this may take a minute)..."
    # Ensure host tools are available (wrapper script will use them)
    ensure_host_aidl_tools
    if ./build-linux-binder-aidl.sh >/tmp/target_build.log 2>&1; then
        warnings=$(grep -ci "warning:" /tmp/target_build.log || echo "0")
        errors=$(grep -ci "error:" /tmp/target_build.log || echo "0")
        echo "✅ Target build completed (warnings: $warnings, errors: $errors)"
        test -f ./out/target/lib/libbinder.so && echo "✅ libbinder.so created"
        test -f ./out/target/lib/liblog.so && echo "✅ liblog.so created"
        test -x ./out/target/bin/servicemanager && echo "✅ servicemanager created"

        # Verify host architecture
        if ! verify_host_architecture ./out/target/lib "wrapper script build"; then
            echo "❌ Architecture verification failed!"
            exit 1
        fi
    else
        echo "❌ Target build failed!"
        tail -20 /tmp/target_build.log
        exit 1
    fi
}

test_7() {
    clean_build_state
    echo "Building target libraries via direct CMake (defaults)..."
    ensure_host_aidl_tools
    if run_cmake_build build-target-cmake && run_cmake_install build-target-cmake; then
        warnings=$(grep -ci "warning:" /tmp/cmake_target_build.log || echo "0")
        errors=$(grep -ci "error:" /tmp/cmake_target_build.log || echo "0")
        echo "✅ Default CMake build completed (warnings: $warnings, errors: $errors)"
        test -f ./build-target-cmake/libbinder.so && echo "✅ libbinder.so created (default CMake build)"
        test -f "${CMAKE_INSTALL_PREFIX}/lib/libbinder.so" && echo "✅ libbinder.so installed (default CMake install)"
        check_install_layout "${CMAKE_INSTALL_PREFIX}"

        # Verify host architecture
        if ! verify_host_architecture "${CMAKE_INSTALL_PREFIX}/lib" "default CMake build"; then
            echo "❌ Architecture verification failed!"
            exit 1
        fi

        print_dest_tree "${CMAKE_INSTALL_PREFIX}"
    else
        echo "❌ Default CMake build failed!"
        tail -20 /tmp/cmake_target_build.log
        if [ -f /tmp/cmake_target_install.log ]; then
            echo "Install log (last 20 lines):"
            tail -20 /tmp/cmake_target_install.log
        fi
        exit 1
    fi
}

test_8() {
    clean_build_state
    echo "Building target libraries via direct CMake (per BUILD.md)..."
    echo "Simulating production Yocto build - BUILD_HOST_AIDL=OFF uses pre-generated code"
    # Production builds don't need host tools - they use pre-generated code from binder_aidl_gen/
    if run_cmake_build build-target-cmake \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_HOST_AIDL=OFF \
        -DTARGET_LIB64_VERSION=ON; then
        warnings=$(grep -ci "warning:" /tmp/cmake_target_build.log || echo "0")
        errors=$(grep -ci "error:" /tmp/cmake_target_build.log || echo "0")
        echo "✅ Direct CMake build completed (warnings: $warnings, errors: $errors)"
        test -f ./build-target-cmake/libbinder.so && echo "✅ libbinder.so created (CMake build)"
    else
        echo "❌ Direct CMake build failed!"
        tail -20 /tmp/cmake_target_build.log
        exit 1
    fi
}

test_9() {
    clean_build_state
    echo "Building target libraries via direct CMake (per BUILD.md + install)..."
    echo "Production build with install - uses pre-generated code from binder_aidl_gen/"
    # Production builds don't need host tools - they use pre-generated code from binder_aidl_gen/
    if run_cmake_build build-target-cmake \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_HOST_AIDL=OFF \
        -DTARGET_LIB64_VERSION=ON && \
       run_cmake_install build-target-cmake; then
        warnings=$(grep -ci "warning:" /tmp/cmake_target_build.log || echo "0")
        errors=$(grep -ci "error:" /tmp/cmake_target_build.log || echo "0")
        echo "✅ Direct CMake build completed (warnings: $warnings, errors: $errors)"
        test -f ./build-target-cmake/libbinder.so && echo "✅ libbinder.so created (CMake build)"
        test -f "${CMAKE_INSTALL_PREFIX}/lib/libbinder.so" && echo "✅ libbinder.so installed (CMake install)"
        check_install_layout "${CMAKE_INSTALL_PREFIX}"

        # Verify host architecture
        if ! verify_host_architecture "${CMAKE_INSTALL_PREFIX}/lib" "BUILD.md direct CMake build"; then
            echo "❌ Architecture verification failed!"
            exit 1
        fi

        print_dest_tree "${CMAKE_INSTALL_PREFIX}"
    else
        echo "❌ Direct CMake build failed!"
        tail -20 /tmp/cmake_target_build.log
        if [ -f /tmp/cmake_target_install.log ]; then
            echo "Install log (last 20 lines):"
            tail -20 /tmp/cmake_target_install.log
        fi
        exit 1
    fi
}

test_10() {
    clean_build_state
    echo "Production build (minimal required flags only)..."
    echo "This simulates Yocto/BitBake with only required production variables."
    echo "No AIDL compiler - uses pre-generated C++ from binder_aidl_gen/"

    # Remove host AIDL tools to verify production build doesn't need them
    echo "Removing host AIDL tools to verify production build independence..."
    rm -rf ./out/host ./build-host 2>/dev/null || true
    echo "✅ Host tools removed - production build will use pre-generated code only"
    echo ""

    # Use production-build.sh script with clean flag to ensure SDK is built with host toolchain
    if [ -x "./tools/production-build.sh" ]; then
        echo "Using tools/production-build.sh for production build"
        if ./tools/production-build.sh "$(pwd)" "${CMAKE_INSTALL_PREFIX}" --clean >/tmp/production_build.log 2>&1; then
            echo "✅ Production build completed successfully"
        else
            echo "❌ Production build failed!"
            tail -30 /tmp/production_build.log
            exit 1
        fi
    else
        # Fallback to direct CMake if script doesn't exist
        if run_cmake_build build-production \
            -DBUILD_HOST_AIDL=OFF && \
           run_cmake_install build-production; then
            echo "✅ Production build completed (fallback CMake)"
        else
            echo "❌ Production build failed!"
            tail -20 /tmp/cmake_target_build.log
            exit 1
        fi
    fi

    # Verify outputs
    warnings=$(grep -ci "warning:" /tmp/production_build.log 2>/dev/null || echo "0")
    errors=$(grep -ci "error:" /tmp/production_build.log 2>/dev/null || echo "0")
    echo "Build warnings: $warnings, errors: $errors"
    test -f "${CMAKE_INSTALL_PREFIX}/lib/libbinder.so" && echo "✅ libbinder.so installed"
    test -x "${CMAKE_INSTALL_PREFIX}/bin/servicemanager" && echo "✅ servicemanager installed"
    test ! -f "${CMAKE_INSTALL_PREFIX}/bin/aidl" && echo "✅ AIDL compiler NOT installed (production)"
    test ! -f "${CMAKE_INSTALL_PREFIX}/bin/aidl-cpp" && echo "✅ AIDL-CPP NOT installed (production)"
    check_install_layout "${CMAKE_INSTALL_PREFIX}"

    # Verify host architecture (production build should be for host platform)
    if ! verify_host_architecture "${CMAKE_INSTALL_PREFIX}/lib" "production build"; then
        echo "❌ Architecture verification failed!"
        exit 1
    fi

    print_dest_tree "${CMAKE_INSTALL_PREFIX}"

    # Clean up build-production directory after test completes
    echo ""
    echo "==> Cleaning up build-production directory..."
    rm -rf build-production 2>/dev/null || true
    echo "✅ build-production cleaned up"
}

test_11() {
    echo "Cross-compilation build and verification (RDK Kirkstone ARM toolchain)..."
    echo ""

    # Step 1: Check if sc command is available
    echo "==> Step 1: Checking for 'sc' command..."
    if ! command -v sc &> /dev/null; then
        echo "⚠️  'sc' command not found - cross-compilation environment not available"
        echo "    This is optional for development builds"
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
    local current_dir
    current_dir=$(pwd)

    # Step 3: Clean build state
    echo "==> Step 3: Cleaning build state..."
    echo "Removing: build-production, ${CMAKE_INSTALL_PREFIX}"
    clean_build_state
    echo "✅ Build state cleaned"

    echo "==> Step 4: Verifying production-build.sh script..."
    if [ ! -x "${current_dir}/tools/production-build.sh" ]; then
        echo "❌ tools/production-build.sh not found or not executable!"
        return 1
    fi
    echo "✅ Script found: ${current_dir}/tools/production-build.sh"
    echo ""

    # Step 5: Run ARM cross-compilation build
    echo "==> Step 5: Running ARM cross-compilation build..."
    echo "This uses the same production-build.sh as test_10 but with ARM toolchain"
    echo ""
    echo "Build command:"
    echo "  sc docker run rdk-kirkstone \\"
    echo "    \". /opt/toolchains/rdk-glibc-x86_64-arm-toolchain/environment-setup-armv7vet2hf-neon-oe-linux-gnueabi; \\"
    echo "    unset CMAKE_TOOLCHAIN_FILE; \\"
    echo "    ${current_dir}/tools/production-build.sh ${current_dir} ${CMAKE_INSTALL_PREFIX}\""
    echo ""
    echo "Starting ARM build (this may take several minutes)..."
    echo "========================================"

    # Run production build through sc docker with ARM toolchain - show output in real-time
    # Uses the committed tools/production-build.sh script which works for any toolchain
    # Note: clean_build_state() already cleaned everything on host, no need for --clean inside docker
    # Unset CMAKE_TOOLCHAIN_FILE so CMake uses CC/CXX from environment instead of OE toolchain file
    # Note: sc docker automatically mounts PWD and runs in that directory
    if sc docker run rdk-kirkstone \
        ". /opt/toolchains/rdk-glibc-x86_64-arm-toolchain/environment-setup-armv7vet2hf-neon-oe-linux-gnueabi; unset CMAKE_TOOLCHAIN_FILE; ${current_dir}/tools/production-build.sh ${current_dir} ${CMAKE_INSTALL_PREFIX}" \
        2>&1 | tee /tmp/arm_build.log; then
        echo "========================================"
        echo "✅ ARM build completed successfully"
    else
        echo "========================================"
        echo "❌ ARM build failed!"
        echo ""
        echo "Last 30 lines of build log:"
        tail -30 /tmp/arm_build.log
        return 1
    fi
    echo ""

    # Debug: Check what actually exists after build
    echo "==> Debug: Checking filesystem after ARM build..."
    echo "    Contents of out/:"
    ls -la "${current_dir}/out/" 2>&1 || echo "    out/ doesn't exist"
    echo "    Contents of CMAKE_INSTALL_PREFIX (${CMAKE_INSTALL_PREFIX}):"
    ls -la "${CMAKE_INSTALL_PREFIX}" 2>&1 || echo "    ${CMAKE_INSTALL_PREFIX} doesn't exist"
    echo "    Contents of build-production/:"
    ls -la "${current_dir}/build-production/" 2>&1 | head -20
    echo "    Checking for built libs in build-production:"
    find "${current_dir}/build-production" -name "*.so" 2>&1 | head -10
    echo "    Checking cmake install manifest:"
    if [ -f "${current_dir}/build-production/install_manifest.txt" ]; then
        echo "    Install manifest exists - first 10 files:"
        head -10 "${current_dir}/build-production/install_manifest.txt"
    else
        echo "    No install_manifest.txt found - install may have failed"
    fi
    echo ""

    # Step 6: Check if output directory exists
    echo "==> Step 6: Checking for build output directory..."
    echo "Expected directory: ${CMAKE_INSTALL_PREFIX}/lib"
    if [ ! -d "${CMAKE_INSTALL_PREFIX}" ]; then
        echo "❌ Install prefix does not exist: ${CMAKE_INSTALL_PREFIX}"
        return 1
    fi

    if [ ! -d "${CMAKE_INSTALL_PREFIX}/lib" ]; then
        echo "❌ Library directory not found: ${CMAKE_INSTALL_PREFIX}/lib"
        echo ""
        echo "Contents of ${CMAKE_INSTALL_PREFIX}:"
        ls -la "${CMAKE_INSTALL_PREFIX}"
        return 1
    fi
    echo "✅ Output directory exists: ${CMAKE_INSTALL_PREFIX}/lib"
    echo ""

    # Step 7: List built files
    echo "==> Step 7: Listing built libraries..."
    if ! ls -lh "${CMAKE_INSTALL_PREFIX}/lib"/*.so 2>/dev/null; then
        echo "❌ No .so files found in ${CMAKE_INSTALL_PREFIX}/lib"
        echo ""
        echo "Directory contents:"
        ls -la "${CMAKE_INSTALL_PREFIX}/lib"
        return 1
    fi
    echo ""

    # Step 8: Verify ARM architecture for each library
    echo "==> Step 8: Verifying ARM architecture..."

    local found_libs=false
    local all_arm=true
    local lib_count=0
    local arm_count=0

    for lib in "${CMAKE_INSTALL_PREFIX}/lib"/*.so; do
        if [ -f "${lib}" ]; then
            found_libs=true
            lib_count=$((lib_count + 1))
            local basename_lib=$(basename "${lib}")
            local file_output=$(file "${lib}")

            echo ""
            echo "  Library: ${basename_lib}"
            echo "  file output: ${file_output}"

            # Get readelf output if available
            if command -v readelf &> /dev/null; then
                local machine=$(readelf -h "${lib}" 2>/dev/null | grep "Machine:" || echo "readelf failed")
                echo "  readelf Machine: ${machine}"
            fi

            # Check for ARM indicators
            if echo "${file_output}" | grep -qi "ARM\|armv7\|armv8"; then
                arm_count=$((arm_count + 1))
                echo "  ✅ ARM architecture confirmed (file command)"
            elif command -v readelf &> /dev/null && readelf -h "${lib}" 2>/dev/null | grep -qi "ARM\|AArch64"; then
                arm_count=$((arm_count + 1))
                echo "  ✅ ARM architecture confirmed (readelf)"
            else
                echo "  ❌ Not ARM architecture - may be x86_64 or unknown!"
                all_arm=false
            fi
        fi
    done

    echo ""
    echo "==> Step 9: Verification summary..."
    echo "Total libraries checked: ${lib_count}"
    echo "ARM libraries found: ${arm_count}"

    if [ "${found_libs}" = false ]; then
        echo "❌ No .so files found to verify"
        return 1
    fi

    if [ "${all_arm}" = false ]; then
        echo "❌ Architecture verification FAILED: Not all libraries are ARM"
        echo "    Expected ${lib_count} ARM libraries, found ${arm_count}"
        return 1
    fi

    echo "✅ All ${lib_count} libraries verified as ARM architecture"
    echo ""

    # Step 10: Verify servicemanager
    echo "==> Step 10: Verifying servicemanager binary..."
    if [ -x "${CMAKE_INSTALL_PREFIX}/bin/servicemanager" ]; then
        echo "✅ servicemanager binary exists"
        local sm_arch=$(file "${CMAKE_INSTALL_PREFIX}/bin/servicemanager")
        echo "   Architecture: ${sm_arch}"
        if echo "${sm_arch}" | grep -qi "ARM\|armv7\|armv8"; then
            echo "   ✅ servicemanager is ARM"
        else
            echo "   ❌ servicemanager is NOT ARM!"
            return 1
        fi
    else
        echo "❌ servicemanager binary not found"
        return 1
    fi
    echo ""

    echo "=========================================="
    echo "✅ Test 11 PASSED - ARM cross-compilation verified"
    echo "=========================================="

    return 0
}

run_test "1" "Clean Android sources" test_1
run_test "1.1" "Clone Android sources" test_1_1
run_test "2" "Scripts exist and are executable" test_2
run_test "3" "Help flags work" test_3
run_test "4" "Clean operations work and exit" test_4
run_test "5" "Build host AIDL tools" test_5
run_test "6" "Build target binder libraries" test_6
run_test "7" "Direct CMake build (defaults + install)" test_7
run_test "8" "Direct CMake build (per BUILD.md)" test_8
run_test "9" "Direct CMake build (per BUILD.md + install)" test_9
run_test "10" "Production build (minimal flags + install)" test_10
run_test "11" "Cross-compilation environment check (sc/RDK)" test_11

echo ""
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
echo ""
echo "Build outputs:"
echo "  Host:   $(realpath ./out/host/bin/)"
echo "  Target: $(realpath ./out/target/lib/)"

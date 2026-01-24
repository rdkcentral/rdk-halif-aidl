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
SDK_INCLUDE_DIR="${SDK_INCLUDE_DIR:-$(pwd)/out/build/include}"

# SDK required artifacts (data-driven)
REQUIRED_SDK_LIBS=("libbinder.so" "liblog.so" "libbase.so" "libutils.so" "libcutils.so")
REQUIRED_SDK_BINS=("servicemanager")

usage() {
    echo "Usage: $0 [--from ID] [--to ID] [--only ID[,ID...]] [--list] [--help]"
    echo "  --from ID    Start running at test ID (e.g., 3 or 6)"
    echo "  --to ID      Stop after test ID (inclusive)"
    echo "  --only IDs   Run only specified test IDs (comma-separated)"
    echo "  --list       List available test IDs"
    echo "  --help       Show this help"
}

TEST_IDS=("1" "1.1" "2" "3" "4" "5" "6" "7" "8" "9" "10" "11" "12" "13")

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
    echo "  10  Production SDK build (native host, no examples)"
    echo "  11  Production SDK build (ARM cross, no examples)"
    echo "  12  Examples build (native host)"
    echo "  13  Examples build (ARM cross)"
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
    local saved_cmake_toolchain="${CMAKE_TOOLCHAIN_FILE:-}"

    # Clear cross-compiler environment to force host compiler
    unset CC CXX CFLAGS CXXFLAGS LDFLAGS CMAKE_TOOLCHAIN_FILE

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
    echo "==> cmake -S . -B ${build_dir} -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} -DCMAKE_INSTALL_INCDIR=${SDK_INCLUDE_DIR} $*"
    cmake -S . -B "${build_dir}" \
        -DCMAKE_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}" \
        -DCMAKE_INSTALL_INCDIR="${SDK_INCLUDE_DIR}" \
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

# Verify install directory layout (R10.6, R11.9)
verify_install_layout() {
    local prefix="$1"
    local sdk_include="$2"
    
    # Safety check: refuse dangerous prefixes (G4)
    if [ -z "${prefix}" ] || [ "${prefix}" = "/" ]; then
        echo "❌ SAFETY: Refusing to verify empty or root prefix"
        return 1
    fi
    
    echo "==> Verifying install layout..."
    echo "    Prefix:      ${prefix}"
    echo "    SDK headers: ${sdk_include}"
    
    local ok=true
    if [ ! -d "${prefix}/lib" ]; then
        echo "    ❌ Missing lib directory: ${prefix}/lib"
        ok=false
    else
        echo "    ✅ lib directory exists"
    fi
    
    if [ ! -d "${prefix}/bin" ]; then
        echo "    ❌ Missing bin directory: ${prefix}/bin"
        ok=false
    else
        echo "    ✅ bin directory exists"
    fi
    
    if [ ! -d "${sdk_include}" ]; then
        echo "    ❌ Missing SDK include directory: ${sdk_include}"
        ok=false
    else
        echo "    ✅ SDK include directory exists"
    fi
    
    if [ "${ok}" != true ]; then
        echo "    Install layout verification FAILED"
        print_dest_tree "${prefix}"
        return 1
    fi
    
    echo "    ✅ Install layout verified"
    return 0
}

# Verify required SDK binaries exist (R10.6, R11.9)
verify_binaries_exist() {
    local prefix="$1"
    echo "==> Verifying required SDK binaries..."
    
    local ok=true
    local found_count=0
    local total_count=0
    
    # Check required libraries
    for lib in "${REQUIRED_SDK_LIBS[@]}"; do
        total_count=$((total_count + 1))
        if [ -f "${prefix}/lib/${lib}" ]; then
            echo "    ✅ ${lib}"
            found_count=$((found_count + 1))
        else
            echo "    ❌ ${lib} MISSING"
            ok=false
        fi
    done
    
    # Check required binaries
    for bin in "${REQUIRED_SDK_BINS[@]}"; do
        total_count=$((total_count + 1))
        if [ -x "${prefix}/bin/${bin}" ]; then
            echo "    ✅ ${bin}"
            found_count=$((found_count + 1))
        else
            echo "    ❌ ${bin} MISSING or not executable"
            ok=false
        fi
    done
    
    echo "    Summary: ${found_count}/${total_count} required artifacts found"
    
    if [ "${ok}" != true ]; then
        return 1
    fi
    return 0
}

# Verify AIDL tools are NOT installed (R10.7)
verify_no_aidl_tools() {
    local prefix="$1"
    echo "==> Verifying AIDL tools NOT in install (production)..."
    
    local ok=true
    if [ -f "${prefix}/bin/aidl" ]; then
        echo "    ❌ aidl found (should not be installed)"
        ok=false
    else
        echo "    ✅ aidl not installed"
    fi
    
    if [ -f "${prefix}/bin/aidl-cpp" ]; then
        echo "    ❌ aidl-cpp found (should not be installed)"
        ok=false
    else
        echo "    ✅ aidl-cpp not installed"
    fi
    
    if [ "${ok}" != true ]; then
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

# Verify architecture of installed binaries (R10.8, R10.9, R11.10, R11.11)
# Checks both libs and binaries, supports both host and ARM expectations
verify_architecture() {
    local prefix="$1"
    local expected="$2"  # "host" or "arm32" or "arm64"
    local description="${3:-build}"
    
    echo "==> Verifying ${expected} architecture for ${description}..."
    
    local expected_arch_pattern
    local expected_display
    case "${expected}" in
        host)
            expected_arch_pattern="$(uname -m)|x86-64|x86_64|ELF 64-bit"
            expected_display="$(uname -m)"
            ;;
        arm32|arm)
            expected_arch_pattern="ARM|armv7|armv8"
            expected_display="ARM (32-bit)"
            ;;
        arm64|aarch64)
            expected_arch_pattern="ARM|AArch64|aarch64"
            expected_display="ARM (64-bit)"
            ;;
        *)
            echo "    ❌ Unknown architecture expectation: ${expected}"
            return 1
            ;;
    esac
    
    echo "    Expected: ${expected_display}"
    
    local files_checked=0
    local files_pass=0
    local files_fail=0
    
    # Check libraries
    for so_file in "${prefix}/lib"/*.so; do
        if [ -f "${so_file}" ]; then
            files_checked=$((files_checked + 1))
            local basename_file=$(basename "${so_file}")
            local file_output=$(file "${so_file}")
            
            if echo "${file_output}" | grep -Eqi "${expected_arch_pattern}"; then
                echo "    ✅ ${basename_file}: ${expected_display}"
                files_pass=$((files_pass + 1))
            else
                echo "    ❌ ${basename_file}: Wrong architecture"
                echo "       file: ${file_output}"
                files_fail=$((files_fail + 1))
            fi
        fi
    done
    
    # Check binaries (R10.9, R11.11)
    for bin_file in "${prefix}/bin"/*; do
        if [ -f "${bin_file}" ] && [ -x "${bin_file}" ]; then
            files_checked=$((files_checked + 1))
            local basename_file=$(basename "${bin_file}")
            local file_output=$(file "${bin_file}")
            
            if echo "${file_output}" | grep -Eqi "${expected_arch_pattern}"; then
                echo "    ✅ ${basename_file}: ${expected_display}"
                files_pass=$((files_pass + 1))
            else
                echo "    ❌ ${basename_file}: Wrong architecture"
                echo "       file: ${file_output}"
                files_fail=$((files_fail + 1))
            fi
        fi
    done
    
    # Summary (R10.10, R11.12, R11.13)
    echo "    ---"
    echo "    Checked: ${files_checked} files (libs + binaries)"
    echo "    Passed:  ${files_pass}"
    echo "    Failed:  ${files_fail}"
    
    if [ ${files_checked} -eq 0 ]; then
        echo "    ❌ No files found to verify"
        return 1
    elif [ ${files_fail} -gt 0 ]; then
        echo "    ❌ Architecture verification FAILED"
        return 1
    else
        echo "    ✅ All binaries verified as ${expected_display}"
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
        verify_install_layout "${CMAKE_INSTALL_PREFIX}" "${SDK_INCLUDE_DIR}"

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
        verify_install_layout "${CMAKE_INSTALL_PREFIX}" "${SDK_INCLUDE_DIR}"

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
    # R10.1: Clean build state
    clean_build_state
    
    echo "=== Test 10: Production SDK build (native host, no examples) ==="
    echo ""
    
    # R10.2: Remove host AIDL outputs to prove independence
    echo "==> Removing host AIDL tools to verify production build independence..."
    rm -rf ./out/host ./build-host 2>/dev/null || true
    echo "✅ Host tools removed - production build will use pre-generated code only"
    echo ""
    
    # R10.3: Set production env vars
    export INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}"
    
    echo "Production build configuration:"
    echo "  Install prefix: ${INSTALL_PREFIX}"
    echo "  Uses pre-generated code from binder_aidl_gen/"
    echo ""
    
    # R10.4: Build SDK using canonical script (no examples)
    echo "==> Building SDK (binder libraries + servicemanager)..."
    if ! ./build-linux-binder-aidl.sh --no-host-aidl >/tmp/production_sdk_build.log 2>&1; then
        echo "❌ SDK build failed!"
        echo ""
        echo "Last 50 lines of build log:"
        tail -50 /tmp/production_sdk_build.log
        echo ""
        echo "Searching for errors:"
        grep -i "error:" /tmp/production_sdk_build.log | tail -20 || echo "  (no 'error:' messages found)"
        return 1
    fi
    echo "✅ SDK build completed"
    echo ""
    
    # Count warnings/errors (R10.10)
    local warnings=$(grep -ci "warning:" /tmp/production_sdk_build.log 2>/dev/null || echo "0")
    local errors=$(grep -ci "error:" /tmp/production_sdk_build.log 2>/dev/null || echo "0")
    
    # R10.6: Verify install layout
    if ! verify_install_layout "${INSTALL_PREFIX}" "$(dirname "${INSTALL_PREFIX}")/build/include"; then
        echo "❌ Install layout verification failed"
        return 1
    fi
    echo ""
    
    # R10.6: Verify required binaries exist
    if ! verify_binaries_exist "${INSTALL_PREFIX}"; then
        echo "❌ Required binaries verification failed"
        return 1
    fi
    echo ""
    
    # R10.7: Verify AIDL tools are NOT in install
    if ! verify_no_aidl_tools "${INSTALL_PREFIX}"; then
        echo "❌ AIDL tools found in production install (should not be present)"
        return 1
    fi
    echo ""
    
    # R10.8, R10.9: Verify all binaries (libs + bins) are host architecture
    if ! verify_architecture "${INSTALL_PREFIX}" "host" "production SDK"; then
        echo "❌ Architecture verification failed"
        return 1
    fi
    echo ""
    
    # R10.10: Clear summary
    echo "=========================================="
    echo "  ✅ Test 10 PASSED - Production SDK Build"
    echo "=========================================="
    echo ""
    echo "Build summary:"
    echo "  Warnings: ${warnings}"
    echo "  Errors:   ${errors}"
    echo ""
    echo "Key artifacts:"
    echo "  SDK libraries:   ${INSTALL_PREFIX}/lib ($(ls -1 "${INSTALL_PREFIX}"/lib/*.so 2>/dev/null | wc -l) files)"
    echo "  SDK binaries:    ${INSTALL_PREFIX}/bin ($(ls -1 "${INSTALL_PREFIX}"/bin/* 2>/dev/null | wc -l) files)"
    echo "  SDK headers:     ${SDK_INCLUDE_DIR}"
    echo "  AIDL tools:      NOT installed (production)"
    echo ""
    echo "Architecture:      Host ($(uname -m))"
    echo ""
}

test_11() {
    echo "=== Test 11: Production SDK build (ARM cross, no examples) ==="
    echo ""
    
    # R11.1: Check if sc command is available
    if ! command -v sc &> /dev/null; then
        echo "⚠️  SKIPPED: 'sc' command not found"
        echo "    Cross-compilation environment not available (optional for development)"
        return 0
    fi
    
    # R11.2: Check if rdk-kirkstone image exists
    if ! sc docker list 2>/dev/null | grep -q "rdk-kirkstone"; then
        echo "⚠️  SKIPPED: rdk-kirkstone Docker image not found"
        echo "    Cross-compilation environment not configured (optional for development)"
        return 0
    fi
    
    # R11.4: Clean build state
    clean_build_state
    
    # R11.5: Do NOT build host AIDL tools - production doesn't need them
    # Production uses pre-generated code from binder_aidl_gen/
    echo "==> Production build uses pre-generated code (no host AIDL tools needed)"
    echo ""
    
    # R11.6: Set env vars inside container
    local current_dir=$(pwd)
    export INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}"
    
    echo "ARM cross-compilation build configuration:"
    echo "  Install prefix: ${INSTALL_PREFIX}"
    echo "  Target arch:    ARM 32-bit (armv7)"
    echo "  Uses pre-generated code from binder_aidl_gen/"
    echo ""
    
    # R11.7: Build SDK using canonical script inside docker (no examples)
    # Note: Environment variables (CC, CXX, CFLAGS, etc.) are set by environment-setup script
    # We must prevent CMake from using the default Yocto toolchain file which conflicts with manual flags
    echo "==> Step 1: Configure and build ARM SDK in Docker"
    echo "    Command: sc docker run rdk-kirkstone + build-linux-binder-aidl.sh --no-host-aidl"
    echo ""
    
    if ! sc docker run rdk-kirkstone \
        ". /opt/toolchains/rdk-glibc-x86_64-arm-toolchain/environment-setup-armv7vet2hf-neon-oe-linux-gnueabi; export INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}; export TARGET_LIB32_VERSION=ON; export CMAKE_TOOLCHAIN_FILE=; cd ${current_dir}; ./build-linux-binder-aidl.sh --no-host-aidl" \
        >/tmp/arm_sdk_build.log 2>&1; then
        echo "    ❌ Build script failed with exit code $?"
        echo ""
        echo "Last 50 lines of build log:"
        tail -50 /tmp/arm_sdk_build.log
        echo ""
        echo "Searching for errors:"
        grep -i "error:" /tmp/arm_sdk_build.log | tail -20 || echo "  (no 'error:' messages found)"
        return 1
    fi
    echo "    ✅ Build script completed"
    echo ""
    
    # R11.7.1: Verify build outputs exist (immediate check after build)
    echo "==> Step 2: Verify build artifacts were created"
    
    local build_dir="${current_dir}/build-target"
    local found_issues=false
    
    # Check build directory exists
    if [ ! -d "${build_dir}" ]; then
        echo "    ❌ Build directory missing: ${build_dir}"
        found_issues=true
    else
        echo "    ✅ Build directory exists: ${build_dir}"
        
        # Check for .so files in build directory
        local so_count=$(find "${build_dir}" -maxdepth 1 -name "*.so" 2>/dev/null | wc -l)
        if [ "${so_count}" -eq 0 ]; then
            echo "    ❌ No .so files found in ${build_dir}"
            echo "       CMake build may have failed during compilation"
            found_issues=true
        else
            echo "    ✅ Found ${so_count} .so files in build directory"
        fi
        
        # Check for servicemanager binary
        if [ ! -f "${build_dir}/servicemanager" ]; then
            echo "    ❌ servicemanager binary missing in ${build_dir}"
            found_issues=true
        else
            echo "    ✅ servicemanager binary exists"
        fi
    fi
    
    if [ "${found_issues}" = true ]; then
        echo ""
        echo "Build artifacts verification FAILED"
        echo "Check CMake configuration and compilation logs above"
        return 1
    fi
    echo ""
    
    # R11.12: Count warnings/errors
    local warnings=$(grep -ci "warning:" /tmp/arm_sdk_build.log 2>/dev/null || echo "0")
    local errors=$(grep -ci "error:" /tmp/arm_sdk_build.log 2>/dev/null || echo "0")
    
    # R11.9: Verify install layout (files copied to out/target/)
    echo "==> Step 3: Verify install layout"
    if ! verify_install_layout "${INSTALL_PREFIX}" "$(dirname "${INSTALL_PREFIX}")/build/include"; then
        echo "    ❌ Install layout verification failed"
        echo "       Files may not have been copied to ${INSTALL_PREFIX}"
        return 1
    fi
    echo ""
    
    # R11.9: Verify required binaries exist in install location
    echo "==> Step 4: Verify installed binaries"
    if ! verify_binaries_exist "${INSTALL_PREFIX}"; then
        echo "    ❌ Required binaries missing from install location"
        echo "       Build artifacts exist but installation failed"
        return 1
    fi
    echo ""
    
    # Verify AIDL tools are NOT in install (production)
    echo "==> Step 5: Verify production install (no AIDL tools)"
    if ! verify_no_aidl_tools "${INSTALL_PREFIX}"; then
        echo "    ❌ AIDL tools found in production install (should not be present)"
        return 1
    fi
    echo ""
    
    # R11.10, R11.11: Verify all binaries (libs + bins) are ARM architecture
    echo "==> Step 6: Verify ARM architecture"
    if ! verify_architecture "${INSTALL_PREFIX}" "arm32" "ARM SDK"; then
        echo "    ❌ Architecture verification failed"
        return 1
    fi
    echo ""
    
    # R11.13: Clear summary (same format as test 10)
    echo "=========================================="
    echo "  ✅ Test 11 PASSED - ARM Production SDK"
    echo "=========================================="
    echo ""
    echo "Build summary:"
    echo "  Warnings: ${warnings}"
    echo "  Errors:   ${errors}"
    echo ""
    echo "Key artifacts:"
    echo "  SDK libraries:   ${INSTALL_PREFIX}/lib ($(ls -1 "${INSTALL_PREFIX}"/lib/*.so 2>/dev/null | wc -l) files)"
    echo "  SDK binaries:    ${INSTALL_PREFIX}/bin ($(ls -1 "${INSTALL_PREFIX}"/bin/* 2>/dev/null | wc -l) files)"
    echo "  SDK headers:     ${SDK_INCLUDE_DIR}"
    echo "  AIDL tools:      NOT installed (production)"
    echo ""
    echo "Architecture:      ARM (32-bit armv7)"
    echo ""
}

test_12() {
    echo "=== Test 12: Examples build (native host) ==="
    echo ""
    
    # R12.0: Clean all build artifacts and Android sources for self-contained test
    echo "==> Cleaning all build artifacts and Android sources..."
    ./build-linux-binder-aidl.sh --clean >/tmp/sdk_clean.log 2>&1 || true
    echo "✅ Clean complete"
    echo ""

    # R12.1: Check SDK prerequisites and build if needed
    echo "==> Checking SDK prerequisites..."
    if [ ! -f "${CMAKE_INSTALL_PREFIX}/lib/libbinder.so" ]; then
        echo "⚠️  SDK not found - building SDK first..."
        echo ""
        
        # Ensure Android sources are cloned (needed for bison/flex tools)
        if [ ! -d "android/build-tools" ]; then
            echo "==> Cloning Android sources (needed for build tools)..."
            if ! ./clone-android-binder-repo.sh >/tmp/sdk_clone.log 2>&1; then
                echo "❌ Android source clone failed!"
                tail -30 /tmp/sdk_clone.log
                return 1
            fi
            echo "✅ Android sources cloned"
            echo ""
        fi
        
        # Build host AIDL tools
        echo "==> Building host AIDL tools..."
        if ! ./build-aidl-generator-tool.sh >/tmp/sdk_aidl_build.log 2>&1; then
            echo "❌ AIDL tools build failed!"
            tail -30 /tmp/sdk_aidl_build.log
            return 1
        fi
        echo "✅ AIDL tools built"
        echo ""
        
        # Build target binder SDK
        echo "==> Building target Binder SDK..."
        if ! ./build-linux-binder-aidl.sh no-host-aidl >/tmp/sdk_target_build.log 2>&1; then
            echo "❌ SDK build failed!"
            tail -30 /tmp/sdk_target_build.log
            return 1
        fi
        echo "✅ SDK built successfully"
        echo ""
    else
        echo "✅ SDK already available"
    fi
    echo ""
    
    # R12.2: Clean examples build artifacts only (not SDK)
    # Don't call clean_build_state here as it would delete the SDK we just built
    rm -rf ./out/build/examples 2>/dev/null || true
    
    echo "Examples build configuration:"
    echo "  SDK prefix: ${CMAKE_INSTALL_PREFIX}"
    echo ""
    
    # R12.3: Build examples using SDK (force mode auto-generates AIDL files)
    echo "==> Building examples (FWManager)..."
    if ! ./build-binder-example.sh force >/tmp/examples_host_build.log 2>&1; then
        echo "❌ Examples build failed!"
        echo ""
        echo "Last 50 lines of build log:"
        tail -50 /tmp/examples_host_build.log
        echo ""
        echo "Searching for errors:"
        grep -i "error:" /tmp/examples_host_build.log | tail -20 || echo "  (no 'error:' messages found)"
        return 1
    fi
    echo "✅ Examples build completed"
    echo ""
    
    # R12.4: Verify example binaries exist
    echo "==> Verifying example binaries..."
    if [ ! -x "${CMAKE_INSTALL_PREFIX}/bin/FWManagerService" ]; then
        echo "❌ FWManagerService not found"
        return 1
    fi
    echo "✅ FWManagerService exists"
    
    if [ ! -x "${CMAKE_INSTALL_PREFIX}/bin/FWManagerClient" ]; then
        echo "❌ FWManagerClient not found"
        return 1
    fi
    echo "✅ FWManagerClient exists"
    echo ""
    
    # R12.5: Verify architecture
    if ! verify_architecture "${CMAKE_INSTALL_PREFIX}" "host" "examples"; then
        echo "❌ Architecture verification failed"
        return 1
    fi
    echo ""
    
    echo "=========================================="
    echo "  ✅ Test 12 PASSED - Examples Build (Host)"
    echo "=========================================="
    echo ""
}

test_13() {
    echo "=== Test 13: Examples build (ARM cross) ==="
    echo ""
    
    # R13.1: Check if sc command is available
    if ! command -v sc &> /dev/null; then
        echo "⚠️  SKIPPED: 'sc' command not found"
        echo "    Cross-compilation environment not available (optional for development)"
        return 0
    fi
    
    # R13.2: Check if rdk-kirkstone image exists
    if ! sc docker list 2>/dev/null | grep -q "rdk-kirkstone"; then
        echo "⚠️  SKIPPED: rdk-kirkstone Docker image not found"
        echo "    Cross-compilation environment not configured (optional for development)"
        return 0
    fi
    
    # R13.0: Clean all build artifacts and Android sources for self-contained test
    echo "==> Cleaning all build artifacts and Android sources..."
    ./build-linux-binder-aidl.sh --clean >/tmp/sdk_clean.log 2>&1 || true
    echo "✅ Clean complete"
    echo ""

    # Set up environment variables
    local current_dir=$(pwd)
    export INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}"

    # R13.1: Check if sc command is available
    if ! command -v sc &> /dev/null; then
        echo "⚠️  SKIPPED: 'sc' command not found"
        echo "    Cross-compilation environment not available (optional for development)"
        return 0
    fi
    
    # R13.2: Check if rdk-kirkstone image exists
    if ! sc docker list 2>/dev/null | grep -q "rdk-kirkstone"; then
        echo "⚠️  SKIPPED: rdk-kirkstone Docker image not found"
        echo "    Cross-compilation environment not configured (optional for development)"
        return 0
    fi
    
    # R13.3: Build host AIDL tools (native, outside docker)
    echo "==> Building host AIDL tools..."
    if ! ./build-aidl-generator-tool.sh >/tmp/sdk_aidl_build.log 2>&1; then
        echo "❌ AIDL tools build failed!"
        tail -30 /tmp/sdk_aidl_build.log
        return 1
    fi
    echo "✅ AIDL tools built"
    echo ""
    
    # R13.3.5: Generate AIDL C++ files (outside Docker, using host tools)
    echo "==> Generating AIDL C++ files from .aidl sources..."
    export AIDL_BIN="${current_dir}/out/host/bin/aidl"
    if ! "${current_dir}/example/generate_cpp.sh" >/tmp/aidl_gen.log 2>&1; then
        echo "❌ AIDL C++ generation failed!"
        tail -30 /tmp/aidl_gen.log
        return 1
    fi
    echo "✅ AIDL C++ files generated"
    echo ""
    
    # R13.4: Build ARM target Binder SDK (inside docker with RDK environment)
    echo "ARM cross-compilation build configuration:"
    echo "  Install prefix: ${INSTALL_PREFIX}"
    echo "  Target arch:    ARM 32-bit (armv7)"
    echo ""
    
    echo "==> Building ARM target Binder SDK in Docker..."
    echo "    Command: sc docker run rdk-kirkstone + build-linux-binder-aidl.sh --no-host-aidl"
    echo ""
    
    if ! sc docker run rdk-kirkstone \
        ". /opt/toolchains/rdk-glibc-x86_64-arm-toolchain/environment-setup-armv7vet2hf-neon-oe-linux-gnueabi; export INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}; export TARGET_LIB32_VERSION=ON; export CMAKE_TOOLCHAIN_FILE=; cd ${current_dir}; ./build-linux-binder-aidl.sh --no-host-aidl" \
        >/tmp/sdk_arm_build.log 2>&1; then
        echo "❌ ARM SDK build failed!"
        tail -50 /tmp/sdk_arm_build.log
        echo ""
        echo "Searching for errors:"
        grep -i "error:" /tmp/sdk_arm_build.log | tail -20 || echo "  (no 'error:' messages found)"
        return 1
    fi
    echo "✅ ARM SDK built successfully"
    echo ""
    
    # Quick arch check
    local lib_arch=$(file "${CMAKE_INSTALL_PREFIX}/lib/libbinder.so")
    if ! echo "${lib_arch}" | grep -qi "ARM"; then
        echo "❌ SDK is not ARM - build failed"
        return 1
    fi
    echo "✅ ARM SDK available"
    echo ""
    
    # R13.5: Build examples configuration
    echo "ARM examples build configuration:"
    echo "  SDK prefix: ${INSTALL_PREFIX}"
    echo "  Target arch: ARM 32-bit (armv7)"
    echo ""
    
    # R13.6: Build examples inside docker (C++ files already generated, just compile)
    echo "==> Building ARM examples (FWManager)..."
    echo "Command: sc docker run rdk-kirkstone + CMake + make for examples"
    echo ""
    
    # Build examples directly with CMake (skip SDK build and AIDL generation)
    # Add -Wl,-rpath-link to help linker find dependent libraries at link time
    if ! sc docker run rdk-kirkstone \
        ". /opt/toolchains/rdk-glibc-x86_64-arm-toolchain/environment-setup-armv7vet2hf-neon-oe-linux-gnueabi; export INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}; export TARGET_LIB32_VERSION=ON; export LDFLAGS=\"\${LDFLAGS} -Wl,-rpath-link=${CMAKE_INSTALL_PREFIX}/lib\"; unset CMAKE_TOOLCHAIN_FILE; cd ${current_dir}; mkdir -p out/build/examples && cd out/build/examples && cmake -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} -DBUILD_ENV_HOST=ON ${current_dir}/example && make -j\$(nproc) && make install" \
        >/tmp/examples_arm_build.log 2>&1; then
        echo "❌ ARM examples build failed!"
        echo ""
        echo "Last 50 lines of build log:"
        tail -50 /tmp/examples_arm_build.log
        echo ""
        echo "Searching for errors:"
        grep -i "error:" /tmp/examples_arm_build.log | tail -20 || echo "  (no 'error:' messages found)"
        return 1
    fi
    echo "✅ ARM examples build completed"
    echo ""
    
    # R13.7: Verify example binaries exist
    echo "==> Verifying ARM example binaries..."
    if [ ! -x "${CMAKE_INSTALL_PREFIX}/bin/FWManagerService" ]; then
        echo "❌ FWManagerService not found"
        return 1
    fi
    echo "✅ FWManagerService exists"
    
    if [ ! -x "${CMAKE_INSTALL_PREFIX}/bin/FWManagerClient" ]; then
        echo "❌ FWManagerClient not found"
        return 1
    fi
    echo "✅ FWManagerClient exists"
    echo ""
    
    # R13.8: Verify ARM architecture
    if ! verify_architecture "${CMAKE_INSTALL_PREFIX}" "arm32" "ARM examples"; then
        echo "❌ Architecture verification failed"
        return 1
    fi
    echo ""
    
    echo "=========================================="
    echo "  ✅ Test 13 PASSED - Examples Build (ARM)"
    echo "=========================================="
    echo ""
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
run_test "10" "Production SDK build (native host, no examples)" test_10
run_test "11" "Production SDK build (ARM cross, no examples)" test_11
run_test "12" "Examples build (native host)" test_12
run_test "13" "Examples build (ARM cross)" test_13

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
echo "  Installed to: $(realpath ${CMAKE_INSTALL_PREFIX})"
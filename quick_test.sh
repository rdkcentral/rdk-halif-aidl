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
    echo "  11  Docker cross-compilation (RDK Kirkstone ARM toolchain)"
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
    rm -rf ./build-host ./build-target ./build-target-cmake 2>/dev/null || true
    rm -rf ./out/host ./out/target 2>/dev/null || true
    rm -rf ./CMakeFiles ./CMakeCache.txt ./cmake_install.cmake 2>/dev/null || true
}

ensure_host_aidl_tools() {
    if [ -x ./out/host/bin/aidl ] && [ -x ./out/host/bin/aidl-cpp ]; then
        return 0
    fi
    echo "==> Building host AIDL tools for CMake build..."
    if ./build-aidl-generator-tool.sh >/tmp/host_build.log 2>&1; then
        warnings=$(grep -ci "warning:" /tmp/host_build.log || echo "0")
        errors=$(grep -ci "error:" /tmp/host_build.log || echo "0")
        echo "✅ Host build completed (warnings: $warnings, errors: $errors)"
        test -x ./out/host/bin/aidl && echo "✅ aidl binary created"
        test -x ./out/host/bin/aidl-cpp && echo "✅ aidl-cpp binary created"
    else
        echo "❌ Host build failed!"
        tail -20 /tmp/host_build.log
        exit 1
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
    if [ ! -d "${prefix_path}/include" ]; then
        echo "❌ Missing include directory: ${prefix_path}/include"
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
    if ./build-aidl-generator-tool.sh >/tmp/host_build.log 2>&1; then
        warnings=$(grep -ci "warning:" /tmp/host_build.log || echo "0")
        errors=$(grep -ci "error:" /tmp/host_build.log || echo "0")
        echo "✅ Host build completed (warnings: $warnings, errors: $errors)"
        test -x ./out/host/bin/aidl && echo "✅ aidl binary created"
        test -x ./out/host/bin/aidl-cpp && echo "✅ aidl-cpp binary created"
    else
        echo "❌ Host build failed!"
        tail -20 /tmp/host_build.log
        exit 1
    fi
}

test_6() {
    clean_build_state
    echo "Building target binder libraries (this may take a minute)..."
    if ./build-linux-binder-aidl.sh >/tmp/target_build.log 2>&1; then
        warnings=$(grep -ci "warning:" /tmp/target_build.log || echo "0")
        errors=$(grep -ci "error:" /tmp/target_build.log || echo "0")
        echo "✅ Target build completed (warnings: $warnings, errors: $errors)"
        test -f ./out/target/lib/libbinder.so && echo "✅ libbinder.so created"
        test -f ./out/target/lib/liblog.so && echo "✅ liblog.so created"
        test -x ./out/target/bin/servicemanager && echo "✅ servicemanager created"
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
    ensure_host_aidl_tools
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
    ensure_host_aidl_tools
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
    if run_cmake_build build-production \
        -DBUILD_HOST_AIDL=OFF && \
       run_cmake_install build-production; then
        warnings=$(grep -ci "warning:" /tmp/cmake_target_build.log || echo "0")
        errors=$(grep -ci "error:" /tmp/cmake_target_build.log || echo "0")
        echo "✅ Production build completed (warnings: $warnings, errors: $errors)"
        test -f ./build-production/libbinder.so && echo "✅ libbinder.so created"
        test -f "${CMAKE_INSTALL_PREFIX}/lib/libbinder.so" && echo "✅ libbinder.so installed"
        test -x "${CMAKE_INSTALL_PREFIX}/bin/servicemanager" && echo "✅ servicemanager installed"
        test ! -f "${CMAKE_INSTALL_PREFIX}/bin/aidl" && echo "✅ AIDL compiler NOT installed (production)"
        test ! -f "${CMAKE_INSTALL_PREFIX}/bin/aidl-cpp" && echo "✅ AIDL-CPP NOT installed (production)"
        check_install_layout "${CMAKE_INSTALL_PREFIX}"
        print_dest_tree "${CMAKE_INSTALL_PREFIX}"
    else
        echo "❌ Production build failed!"
        tail -20 /tmp/cmake_target_build.log
        if [ -f /tmp/cmake_target_install.log ]; then
            echo "Install log (last 20 lines):"
            tail -20 /tmp/cmake_target_install.log
        fi
        exit 1
    fi
}

test_11() {
    echo "Docker cross-compilation test (RDK Kirkstone ARM toolchain)..."
    
    # Check if docker command is available
    if ! command -v docker &> /dev/null; then
        echo "⚠️  Docker not installed - skipping cross-compilation test"
        return 0
    fi
    
    # Check if rdk-kirkstone image exists
    if ! docker images | grep -q "rdk-kirkstone"; then
        echo "⚠️  rdk-kirkstone Docker image not found - skipping cross-compilation test"
        echo "    To run this test, ensure rdk-kirkstone image is available"
        return 0
    fi
    
    clean_build_state
    echo "Building with RDK Kirkstone ARM toolchain in Docker..."
    echo "This tests cross-compilation with sysroot and ARM target flags."
    
    # Build in Docker with ARM toolchain environment
    if docker run --rm -v "$(pwd):/workspace" -w /workspace rdk-kirkstone bash -c '
        . /opt/toolchains/rdk-glibc-x86_64-arm-toolchain/environment-setup-armv7vet2hf-neon-oe-linux-gnueabi && \
        export TARGET_LIB32_VERSION=ON && \
        ./build-linux-binder-aidl.sh
    ' >/tmp/docker_cross_build.log 2>&1; then
        warnings=$(grep -ci "warning:" /tmp/docker_cross_build.log || echo "0")
        errors=$(grep -ci "error:" /tmp/docker_cross_build.log || echo "0")
        echo "✅ Docker cross-compilation completed (warnings: $warnings, errors: $errors)"
        test -f ./out/target/lib/libbinder.so && echo "✅ libbinder.so created (ARM cross-compile)"
        test -x ./out/target/bin/servicemanager && echo "✅ servicemanager created (ARM cross-compile)"
        
        # Verify ARM architecture
        if command -v file &> /dev/null; then
            file_output=$(file ./out/target/lib/libbinder.so)
            if echo "$file_output" | grep -q "ARM"; then
                echo "✅ Verified ARM architecture: $file_output"
            else
                echo "⚠️  Warning: Expected ARM binary, got: $file_output"
            fi
        fi
    else
        echo "❌ Docker cross-compilation failed!"
        tail -30 /tmp/docker_cross_build.log
        TESTS_FAILED=$((TESTS_FAILED + 1))
        return 1
    fi
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
run_test "11" "Docker cross-compilation (RDK Kirkstone ARM)" test_11

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

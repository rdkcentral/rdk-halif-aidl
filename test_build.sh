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

###########################################################
# test_build.sh
#
# Comprehensive build test for Linux Binder AIDL toolchain.
# Tests all build scripts to ensure they work correctly:
#   0. Clone Android source repositories
#   1. Clean operations (--clean flag)
#   2. Full host AIDL compiler build
#   3. Full target binder libraries build
#   4. Verification of outputs
#   5. Zero warnings/errors check
###########################################################

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "${SCRIPT_DIR}"

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Test results
TESTS_PASSED=0
TESTS_FAILED=0
TEST_LOG="${SCRIPT_DIR}/test_build.log"

# Clear previous log
> "${TEST_LOG}"

###########################################################
# Helper functions
###########################################################

print_header() {
    echo -e "${BLUE}=========================================="
    echo -e "  $1"
    echo -e "==========================================${NC}"
}

print_test() {
    echo -e "${YELLOW}[TEST]${NC} $1"
}

print_pass() {
    echo -e "${GREEN}✅ PASS:${NC} $1"
    TESTS_PASSED=$((TESTS_PASSED + 1))
}

print_fail() {
    echo -e "${RED}❌ FAIL:${NC} $1"
    TESTS_FAILED=$((TESTS_FAILED + 1))
}

print_info() {
    echo -e "${BLUE}ℹ️  INFO:${NC} $1"
}

check_file_exists() {
    local file="$1"
    local description="$2"
    
    if [ -f "$file" ]; then
        print_pass "$description exists: $file"
        return 0
    else
        print_fail "$description not found: $file"
        return 1
    fi
}

check_warnings_errors() {
    local log_file="$1"
    local description="$2"
    
    local warning_count=$(grep -ciE "warning:" "$log_file" 2>/dev/null || echo "0")
    local error_count=$(grep -ciE "error:" "$log_file" 2>/dev/null || echo "0")
    
    # Remove any whitespace/newlines
    warning_count=$(echo "$warning_count" | tr -d '\n\r ')
    error_count=$(echo "$error_count" | tr -d '\n\r ')
    
    # Default to 0 if empty
    warning_count=${warning_count:-0}
    error_count=${error_count:-0}
    
    if [ "$error_count" -eq 0 ] && [ "$warning_count" -eq 0 ]; then
        print_pass "$description - No warnings or errors"
        return 0
    else
        print_fail "$description - Found warnings/errors (warnings: $warning_count, errors: $error_count)"
        echo "First 10 warnings/errors:" | tee -a "${TEST_LOG}"
        grep -iE "warning:|error:" "$log_file" 2>/dev/null | head -10 | tee -a "${TEST_LOG}"
        return 1
    fi
}

###########################################################
# Test 0: Clone Android source repositories
###########################################################

print_header "Test 0: Android Source Repository Clone"

print_test "Checking clone-android-binder-repo.sh"
if [ -x "./clone-android-binder-repo.sh" ]; then
    print_pass "clone-android-binder-repo.sh is executable"
else
    print_fail "clone-android-binder-repo.sh not found or not executable"
    exit 1
fi

# Check if android directory already exists
if [ -d "./android" ]; then
    print_info "Android directory already exists - testing re-clone"
fi

print_test "Cloning Android AOSP repositories (this may take several minutes)"
if ./clone-android-binder-repo.sh 2>&1 | tee /tmp/clone.log; then
    print_pass "Clone script completed successfully"
    
    # Verify android directory was created
    if [ -d "./android" ]; then
        print_pass "android/ directory created"
    else
        print_fail "android/ directory not created"
    fi
    
    # Verify key repositories were cloned
    print_test "Verifying cloned repositories"
    
    REQUIRED_REPOS=(
        "native"
        "aidl"
        "fmtlib"
        "logging"
        "libbase"
        "core"
        "googletest"
        "build-tools"
    )
    
    for repo in "${REQUIRED_REPOS[@]}"; do
        if [ -d "./android/${repo}" ]; then
            print_pass "Repository cloned: ${repo}"
            
            # Verify it's a git repository
            if [ -d "./android/${repo}/.git" ]; then
                print_pass "${repo} is a valid git repository"
                
                # Check if it's on the correct tag
                pushd "./android/${repo}" > /dev/null
                current_ref=$(git describe --tags 2>/dev/null || git rev-parse --short HEAD)
                popd > /dev/null
                print_info "${repo} at: ${current_ref}"
            else
                print_fail "${repo} is not a git repository"
            fi
        else
            print_fail "Repository missing: ${repo}"
        fi
    done
    
    # Verify patches were applied
    print_test "Verifying patches applied"
    PATCHED_REPOS=("aidl" "core" "libbase" "logging" "native")
    
    for repo in "${PATCHED_REPOS[@]}"; do
        if [ -d "./android/${repo}" ]; then
            pushd "./android/${repo}" > /dev/null
            # Check if there are any applied patches (look for modified files)
            if git diff --quiet HEAD 2>/dev/null; then
                print_info "${repo}: No modifications (patch may be empty or already applied)"
            else
                print_pass "${repo}: Patch applied (has modifications)"
            fi
            popd > /dev/null
        fi
    done
    
    # Check disk space used
    if command -v du &> /dev/null; then
        android_size=$(du -sh ./android 2>/dev/null | cut -f1)
        print_info "Android source size: ${android_size}"
    fi
    
else
    print_fail "Clone script failed"
    echo "Last 50 lines of clone log:" | tee -a "${TEST_LOG}"
    tail -50 /tmp/clone.log | tee -a "${TEST_LOG}"
    exit 1
fi

###########################################################
# Test 1: Check build scripts exist and are executable
###########################################################

print_header "Test 1: Build Scripts Validation"

print_test "Checking build-aidl-generator-tool.sh"
if [ -x "./build-aidl-generator-tool.sh" ]; then
    print_pass "build-aidl-generator-tool.sh is executable"
else
    print_fail "build-aidl-generator-tool.sh not found or not executable"
    exit 1
fi

print_test "Checking build-linux-binder-aidl.sh"
if [ -x "./build-linux-binder-aidl.sh" ]; then
    print_pass "build-linux-binder-aidl.sh is executable"
else
    print_fail "build-linux-binder-aidl.sh not found or not executable"
    exit 1
fi

print_test "Checking CMakeLists.txt"
if [ -f "./CMakeLists.txt" ]; then
    print_pass "CMakeLists.txt exists"
else
    print_fail "CMakeLists.txt not found"
    exit 1
fi

###########################################################
# Test 1.5: Default CMake flags
###########################################################

print_header "Test 1.5: Default CMake Flags"

print_test "Configuring CMake with defaults"
rm -rf ./build-default-cmake 2>/dev/null || true
if cmake -S . -B ./build-default-cmake > /tmp/default_config.log 2>&1; then
    print_pass "Default CMake configure completed"

    if grep -q "^CMAKE_BUILD_TYPE:STRING=Release$" ./build-default-cmake/CMakeCache.txt; then
        print_pass "Default CMAKE_BUILD_TYPE is Release"
    else
        print_fail "Default CMAKE_BUILD_TYPE is not Release"
    fi

    if grep -q "^BUILD_HOST_AIDL:BOOL=ON$" ./build-default-cmake/CMakeCache.txt; then
        print_pass "Default BUILD_HOST_AIDL is ON"
    else
        print_fail "Default BUILD_HOST_AIDL is not ON"
    fi
else
    print_fail "Default CMake configure failed"
    tail -20 /tmp/default_config.log | tee -a "${TEST_LOG}"
fi
rm -rf ./build-default-cmake 2>/dev/null || true

###########################################################
# Test 2: Clean operations
###########################################################

print_header "Test 2: Clean Operations"

print_test "Testing build-aidl-generator-tool.sh --clean"
if ./build-aidl-generator-tool.sh --clean > /tmp/host_clean.log 2>&1; then
    print_pass "Host clean completed successfully"
    
    # Verify directories were removed
    if [ ! -d "./build-host" ] && [ ! -d "./out/host" ]; then
        print_pass "Host build directories removed"
    else
        print_fail "Host build directories still exist after clean"
    fi
else
    print_fail "Host clean failed"
    cat /tmp/host_clean.log | tee -a "${TEST_LOG}"
fi

print_test "Testing build-linux-binder-aidl.sh --clean"
if ./build-linux-binder-aidl.sh --clean > /tmp/target_clean.log 2>&1; then
    print_pass "Target clean completed successfully"
    
    # Verify directories were removed
    if [ ! -d "./build-target" ] && [ ! -d "./out/target" ]; then
        print_pass "Target build directories removed"
    else
        print_fail "Target build directories still exist after clean"
    fi
else
    print_fail "Target clean failed"
    cat /tmp/target_clean.log | tee -a "${TEST_LOG}"
fi

###########################################################
# Test 3: Build host AIDL compiler
###########################################################

print_header "Test 3: Host AIDL Compiler Build"

print_test "Building host AIDL tools (aidl, aidl-cpp)"
if ./build-aidl-generator-tool.sh 2>&1 | tee /tmp/host_build.log; then
    print_pass "Host AIDL tools build completed"
    
    # Check for warnings/errors
    check_warnings_errors /tmp/host_build.log "Host build"
    
    # Verify outputs
    check_file_exists "./out/host/bin/aidl" "aidl compiler"
    check_file_exists "./out/host/bin/aidl-cpp" "aidl-cpp compiler"
    
    # Check if binaries are executable
    if [ -x "./out/host/bin/aidl" ]; then
        print_pass "aidl binary is executable"
    else
        print_fail "aidl binary not executable"
    fi
    
    if [ -x "./out/host/bin/aidl-cpp" ]; then
        print_pass "aidl-cpp binary is executable"
    else
        print_fail "aidl-cpp binary not executable"
    fi
    
else
    print_fail "Host AIDL tools build failed"
    echo "Last 50 lines of build log:" | tee -a "${TEST_LOG}"
    tail -50 /tmp/host_build.log | tee -a "${TEST_LOG}"
fi

###########################################################
# Test 4: Build target binder libraries
###########################################################

print_header "Test 4: Target Binder Libraries Build"

print_info "Target build requires host AIDL tools from Test 3"
print_test "Building target binder libraries"
if ./build-linux-binder-aidl.sh 2>&1 | tee /tmp/target_build.log; then
    print_pass "Target binder libraries build completed"
    
    # Check for warnings/errors
    check_warnings_errors /tmp/target_build.log "Target build"
    
    # Verify outputs
    print_test "Checking for binder libraries"
    if ls ./out/target/lib/*.so 1> /dev/null 2>&1; then
        print_pass "Binder .so libraries found"
        
        # List key libraries
        for lib in libbinder.so liblog.so libbase.so libcutils.so libutils.so; do
            if [ -f "./out/target/lib/${lib}" ]; then
                print_pass "Found ${lib}"
            else
                print_fail "Missing ${lib}"
            fi
        done
    else
        print_fail "No .so libraries found in out/target/lib/"
    fi
    
    # Check for servicemanager
    check_file_exists "./out/target/bin/servicemanager" "servicemanager binary"
    
    # Check for headers
    if [ -d "./out/target/include" ] && [ -n "$(ls -A ./out/target/include 2>/dev/null)" ]; then
        print_pass "Header files installed in out/target/include/"
    else
        print_fail "No header files in out/target/include/"
    fi
    
else
    print_fail "Target binder libraries build failed"
    echo "Last 50 lines of build log:" | tee -a "${TEST_LOG}"
    tail -50 /tmp/target_build.log | tee -a "${TEST_LOG}"
fi

###########################################################
# Test 5: Help flags
###########################################################

print_header "Test 5: Help Flags"

print_test "Testing build-aidl-generator-tool.sh --help"
if ./build-aidl-generator-tool.sh --help > /tmp/host_help.log 2>&1; then
    if grep -q "Usage:" /tmp/host_help.log; then
        print_pass "Host script --help displays usage"
    else
        print_fail "Host script --help missing usage text"
    fi
else
    print_fail "Host script --help failed"
fi

print_test "Testing build-linux-binder-aidl.sh --help"
if ./build-linux-binder-aidl.sh --help > /tmp/target_help.log 2>&1; then
    if grep -q "Usage:" /tmp/target_help.log; then
        print_pass "Target script --help displays usage"
    else
        print_fail "Target script --help missing usage text"
    fi
else
    print_fail "Target script --help failed"
fi

###########################################################
# Test 6: Rebuild test (verify incremental build works)
###########################################################

print_header "Test 6: Incremental Build"

print_test "Testing incremental host build (no clean)"
if ./build-aidl-generator-tool.sh > /tmp/host_rebuild.log 2>&1; then
    print_pass "Host incremental build succeeded"
    
    # Should be much faster - check it used cached targets
    if grep -q "Built target" /tmp/host_rebuild.log; then
        print_pass "Incremental build used cached targets"
    fi
else
    print_fail "Host incremental build failed"
fi

print_test "Testing incremental target build (no clean)"
if ./build-linux-binder-aidl.sh > /tmp/target_rebuild.log 2>&1; then
    print_pass "Target incremental build succeeded"
else
    print_fail "Target incremental build failed"
fi

###########################################################
# Summary
###########################################################

print_header "Test Summary"

TOTAL_TESTS=$((TESTS_PASSED + TESTS_FAILED))

echo -e "${GREEN}Passed: ${TESTS_PASSED}/${TOTAL_TESTS}${NC}"
if [ $TESTS_FAILED -gt 0 ]; then
    echo -e "${RED}Failed: ${TESTS_FAILED}/${TOTAL_TESTS}${NC}"
    echo ""
    echo -e "${RED}❌ BUILD TEST FAILED${NC}"
    echo "Check ${TEST_LOG} for details"
    exit 1
else
    echo -e "${GREEN}Failed: 0/${TOTAL_TESTS}${NC}"
    echo ""
    echo -e "${GREEN}✅ ALL BUILD TESTS PASSED${NC}"
    echo ""
    echo "Build artifacts:"
    echo "  Host tools:   $(realpath ./out/host/bin/)"
    echo "  Target libs:  $(realpath ./out/target/lib/)"
    echo "  Target bin:   $(realpath ./out/target/bin/)"
    echo "  Headers:      $(realpath ./out/target/include/)"
    exit 0
fi

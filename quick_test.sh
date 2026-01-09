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

echo "=== Quick Build Script Validation ==="
echo ""

# Test 1: Clean Android sources
echo "[1/7] Cleaning Android sources..."
rm -rf ./android 2>/dev/null || true
echo "✅ Android sources cleaned"

# Test 1.1: Clone Android sources
echo "[1.1/7] Cloning Android sources (this may take several minutes)..."
if ! ./clone-android-binder-repo.sh >/tmp/clone.log 2>&1; then
    echo "❌ Clone failed!"
    tail -20 /tmp/clone.log
    exit 1
fi
test -d ./android && echo "✅ Android sources cloned"

# Test 2: Scripts exist and are executable
echo ""
echo "[2/7] Checking scripts..."
test -x ./clone-android-binder-repo.sh && echo "✅ clone-android-binder-repo.sh OK"
test -x ./build-aidl-generator-tool.sh && echo "✅ build-aidl-generator-tool.sh OK"
test -x ./build-linux-binder-aidl.sh && echo "✅ build-linux-binder-aidl.sh OK"

# Test 3: Help flags work
echo ""
echo "[3/7] Testing --help flags..."
./build-aidl-generator-tool.sh --help >/dev/null 2>&1 && echo "✅ Host --help OK"
./build-linux-binder-aidl.sh --help >/dev/null 2>&1 && echo "✅ Target --help OK"

# Test 4: Clean operations work and exit
echo ""
echo "[4/7] Testing --clean operations..."
./build-aidl-generator-tool.sh --clean >/dev/null 2>&1 && echo "✅ Host --clean OK"
test ! -d ./build-host && test ! -d ./out/host && echo "✅ Host directories cleaned"
./build-linux-binder-aidl.sh --clean >/dev/null 2>&1 && echo "✅ Target --clean OK"
test ! -d ./build-target && test ! -d ./out/target && echo "✅ Target directories cleaned"

# Test 5: Build host tools
echo ""
echo "[5/7] Building host AIDL tools (this may take a minute)..."
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

# Clean before target build to ensure isolation
echo ""
echo "==> Cleaning before target build..."
./build-linux-binder-aidl.sh --clean >/dev/null 2>&1

# Test 6: Build target libraries  
echo ""
echo "[6/7] Building target binder libraries (this may take a minute)..."
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

echo ""
echo "==> Cleaning before direct CMake build..."
./build-linux-binder-aidl.sh --clean >/dev/null 2>&1
rm -rf ./build-target-cmake 2>/dev/null || true

echo ""
echo "==> Rebuilding host AIDL tools for direct CMake build..."
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

echo ""
echo "[7/7] Building target libraries via direct CMake (per BUILD.md)..."
if cmake -S . -B build-target-cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_CORE_SDK=ON \
    -DBUILD_HOST_AIDL=OFF \
    -DTARGET_LIB64_VERSION=ON \
    >/tmp/cmake_target_config.log 2>&1 && \
   cmake --build build-target-cmake -- -j"$(nproc)" >/tmp/cmake_target_build.log 2>&1; then
    warnings=$(grep -ci "warning:" /tmp/cmake_target_build.log || echo "0")
    errors=$(grep -ci "error:" /tmp/cmake_target_build.log || echo "0")
    echo "✅ Direct CMake build completed (warnings: $warnings, errors: $errors)"
    test -f ./build-target-cmake/libbinder.so && echo "✅ libbinder.so created (CMake build)"
else
    echo "❌ Direct CMake build failed!"
    tail -20 /tmp/cmake_target_build.log
    exit 1
fi

echo ""
echo "✅ ALL TESTS PASSED"
echo ""
echo "Build outputs:"
echo "  Host:   $(realpath ./out/host/bin/)"
echo "  Target: $(realpath ./out/target/lib/)"

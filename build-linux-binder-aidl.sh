#!/usr/bin/env bash

#/**
# * Copyright 2024 Comcast Cable Communications Management, LLC
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# *     http://www.apache.org/licenses/LICENSE-2.0
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

# -------------------------------------------------------------------
# build-linux-binder-aidl.sh
#
# Builds the Android Binder libraries and servicemanager for the TARGET.
# These run on the embedded device (typically ARM).
#
# Output:
#   - out/target/lib/*.so (libbinder.so, liblog.so, libbase.so, etc.)
#   - out/target/bin/servicemanager
#   - out/build/include/ (binder headers)
#
# Build Variables:
#   CC, CXX        - Target cross-compiler (e.g., arm-linux-gnueabihf-gcc)
#                    If NOT set: Uses system default (gcc/g++ from build-essential)
#   CFLAGS         - C compiler flags (e.g., sysroot, target-specific flags)
#   CXXFLAGS       - C++ compiler flags
#   LDFLAGS        - Linker flags
#   BUILD_TYPE     - Debug or Release (default: Release)
#   TARGET_LIB32_VERSION - Set to ON for 32-bit target (default: OFF for 64-bit)
#
# Options:
#   clean          - Remove all build artifacts and source directories (android/, build-*, out/)
#   no-host-aidl   - Skip building the host AIDL generator tool
#
# Native build (uses system GCC from build-essential):
#   ./build-linux-binder-aidl.sh
#
# Cross-compile (Yocto-style with sysroot):
#   export CC=arm-linux-gnueabihf-gcc
#   export CXX=arm-linux-gnueabihf-g++
#   export CFLAGS="--sysroot=/path/to/sysroot -march=armv7-a"
#   export CXXFLAGS="--sysroot=/path/to/sysroot -march=armv7-a"
#   export LDFLAGS="--sysroot=/path/to/sysroot"
#   export TARGET_LIB32_VERSION=ON
#   ./build-linux-binder-aidl.sh
#
# Note: This builds for the TARGET architecture.
#       When CC/CXX are NOT set: CMake auto-detects system compiler (native build)
#       When CC/CXX ARE set: Uses specified cross-compiler (Yocto/embedded build)
# -------------------------------------------------------------------

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ROOT_DIR="${SCRIPT_DIR}"

BUILD_DIR="${ROOT_DIR}/build-target"
OUT_DIR="${ROOT_DIR}/out"
BUILD_TYPE="${BUILD_TYPE:-Release}"
TARGET_LIB32="${TARGET_LIB32_VERSION:-OFF}"
CLEAN_BUILD=false
BUILD_HOST_AIDL_TOOL=true

# Use CC/CXX/CFLAGS etc. for target cross-compilation
# If not set, use system default (native build)
# Yocto will set these with sysroot, target arch, etc.
TARGET_CC="${CC:-}"
TARGET_CXX="${CXX:-}"
TARGET_CFLAGS="${CFLAGS:-}"
TARGET_CXXFLAGS="${CXXFLAGS:-}"
TARGET_LDFLAGS="${LDFLAGS:-}"

# Parse arguments
for arg in "$@"; do
  case "$arg" in
    --clean|clean)
      CLEAN_BUILD=true
      ;;
    --help|-h|help)
      echo "Usage: $0 [clean] [no-host-aidl] [help]"
      echo "  clean          Remove all build artifacts and source directories (android/, build-*, out/)"
      echo "  no-host-aidl   Skip building the host AIDL generator tool"
      echo "  help           Show this help message"
      exit 0
      ;;
    --no-host-aidl|no-host-aidl)
      BUILD_HOST_AIDL_TOOL=false
      ;;
    *)
      echo "Unknown option: $arg"
      echo "Use 'help' for usage information"
      exit 1
      ;;
  esac
done

echo "=========================================="
echo "  Building Binder Target Libraries"
echo "=========================================="
echo "Root dir:        ${ROOT_DIR}"
echo "Build dir:       ${BUILD_DIR}"
echo "Output dir:      ${OUT_DIR}"
echo "Build type:      ${BUILD_TYPE}"
echo "Target 32-bit:   ${TARGET_LIB32}"
echo "Target CC:       ${TARGET_CC:-system default}"
echo "Target CXX:      ${TARGET_CXX:-system default}"
echo "Target CFLAGS:   ${TARGET_CFLAGS:-none}"
echo "Target CXXFLAGS: ${TARGET_CXXFLAGS:-none}"
echo "Target LDFLAGS:  ${TARGET_LDFLAGS:-none}"
echo "Clean build:     ${CLEAN_BUILD}"
echo "Build host AIDL: ${BUILD_HOST_AIDL_TOOL}"
echo "=========================================="

if [ "$CLEAN_BUILD" = true ]; then
  echo "==> Cleaning all build artifacts and source directories..."
  rm -rf "${BUILD_DIR}" 2>/dev/null || true
  echo "    Cleaned: ${BUILD_DIR}"
  rm -rf "${ROOT_DIR}/build-target-cmake" 2>/dev/null || true
  echo "    Cleaned: ${ROOT_DIR}/build-target-cmake"
  rm -rf "${ROOT_DIR}/CMakeFiles" 2>/dev/null || true
  echo "    Cleaned: ${ROOT_DIR}/CMakeFiles"
  rm -rf "${ROOT_DIR}/out" 2>/dev/null || true
  echo "    Cleaned: ${ROOT_DIR}/out"
  rm -rf "${ROOT_DIR}/build-host" 2>/dev/null || true
  echo "    Cleaned: ${ROOT_DIR}/build-host"
  rm -rf "${ROOT_DIR}/build-target" 2>/dev/null || true
  echo "    Cleaned: ${ROOT_DIR}/build-target"
  rm -rf "${ROOT_DIR}/android" 2>/dev/null || true
  echo "    Cleaned: ${ROOT_DIR}/android"
  echo "✅ Complete clean finished"
  exit 0
fi

# Remove stale in-source CMake artifacts from legacy builds.
rm -rf "${ROOT_DIR}/build-target-cmake" 2>/dev/null || true
rm -rf "${ROOT_DIR}/CMakeFiles" 2>/dev/null || true

# Build host AIDL tool first (needed for generating binder AIDL stubs/proxies)
if [ "$BUILD_HOST_AIDL_TOOL" = true ]; then
  echo "==> Building host AIDL tools..."
  BUILD_TYPE="${BUILD_TYPE}" "${ROOT_DIR}/build-aidl-generator-tool.sh"
fi

mkdir -p "${BUILD_DIR}"
mkdir -p "${OUT_DIR}/target/lib" "${OUT_DIR}/target/bin"
mkdir -p "${OUT_DIR}/build/include"

echo "==> Configuring CMake for target binder libraries..."

# Prepare CMake arguments
CMAKE_ARGS=(
  -S "${ROOT_DIR}"
  -B "${BUILD_DIR}"
  -DCMAKE_BUILD_TYPE="${BUILD_TYPE}"  -DCMAKE_INSTALL_PREFIX="${OUT_DIR}/target"
  -DCMAKE_INSTALL_INCDIR="${OUT_DIR}/build/include"  -DBUILD_HOST_AIDL=OFF
  -DTARGET_LIB32_VERSION="${TARGET_LIB32}"
)

# Add compiler settings if provided (Yocto cross-compilation)
if [ -n "${TARGET_CC}" ]; then
  CMAKE_ARGS+=(-DCMAKE_C_COMPILER="${TARGET_CC}")
fi
if [ -n "${TARGET_CXX}" ]; then
  CMAKE_ARGS+=(-DCMAKE_CXX_COMPILER="${TARGET_CXX}")
fi

# Add flags if provided (Yocto sysroot, target-specific flags)
if [ -n "${TARGET_CFLAGS}" ]; then
  CMAKE_ARGS+=(-DCMAKE_C_FLAGS="${TARGET_CFLAGS}")
fi
if [ -n "${TARGET_CXXFLAGS}" ]; then
  CMAKE_ARGS+=(-DCMAKE_CXX_FLAGS="${TARGET_CXXFLAGS}")
fi
if [ -n "${TARGET_LDFLAGS}" ]; then
  CMAKE_ARGS+=(-DCMAKE_EXE_LINKER_FLAGS="${TARGET_LDFLAGS}")
  CMAKE_ARGS+=(-DCMAKE_SHARED_LINKER_FLAGS="${TARGET_LDFLAGS}")
fi

# Run CMake configuration
cmake "${CMAKE_ARGS[@]}"

echo "==> Building target binder libraries..."
cmake --build "${BUILD_DIR}" --target all -- -j"$(nproc)"

echo "==> Installing to ${OUT_DIR}/target/ and ${OUT_DIR}/build/include/..."
cp "${BUILD_DIR}"/*.so "${OUT_DIR}/target/lib/" 2>/dev/null || true
cp "${BUILD_DIR}"/servicemanager "${OUT_DIR}/target/bin/" 2>/dev/null || true

# Install SDK headers using CMake (to out/build/include)
cmake --install "${BUILD_DIR}"

echo ""
echo "✅ Target binder libraries built successfully"
echo "   Libraries:      ${OUT_DIR}/target/lib/"
echo "   Servicemanager: ${OUT_DIR}/target/bin/servicemanager"
echo "   Headers:        ${OUT_DIR}/build/include/"

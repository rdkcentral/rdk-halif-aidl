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
# Output: out/target/
#   - lib/*.so (libbinder.so, liblog.so, libbase.so, etc.)
#   - bin/servicemanager
#   - include/ (binder headers)
#
# Build Variables:
#   CC, CXX        - Target cross-compiler (e.g., arm-linux-gnueabihf-gcc)
#   BUILD_TYPE     - Debug or Release (default: Release)
#   TARGET_LIB32   - Set to ON for 32-bit target (default: OFF for 64-bit)
#
# Options:
#   --clean        - Clean build and output directories before building
#
# Example cross-compile:
#   export CC=arm-linux-gnueabihf-gcc
#   export CXX=arm-linux-gnueabihf-g++
#   export TARGET_LIB32_VERSION=ON
#   ./build-linux-binder-aidl.sh
#
# Note: This builds for the TARGET architecture.
#       Yocto/bitbake should set CC/CXX appropriately.
# -------------------------------------------------------------------

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ROOT_DIR="${SCRIPT_DIR}"

BUILD_DIR="${ROOT_DIR}/build-target"
OUT_DIR="${ROOT_DIR}/out/target"
BUILD_TYPE="${BUILD_TYPE:-Release}"
TARGET_LIB32="${TARGET_LIB32_VERSION:-OFF}"
CLEAN_BUILD=false

# Use CC/CXX for target cross-compilation
# If not set, use system default (native build)
TARGET_CC="${CC:-}"
TARGET_CXX="${CXX:-}"

# Parse arguments
for arg in "$@"; do
  case "$arg" in
    --clean)
      CLEAN_BUILD=true
      ;;
    --help|-h)
      echo "Usage: $0 [--clean] [--help]"
      echo "  --clean  Clean build and output directories before building"
      echo "  --help   Show this help message"
      exit 0
      ;;
    *)
      echo "Unknown option: $arg"
      echo "Use --help for usage information"
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
echo "Clean build:     ${CLEAN_BUILD}"
echo "=========================================="

if [ "$CLEAN_BUILD" = true ]; then
  echo "==> Cleaning build and output directories..."
  rm -rf "${BUILD_DIR}" "${OUT_DIR}" 2>/dev/null || true
  echo "    Cleaned: ${BUILD_DIR}"
  echo "    Cleaned: ${OUT_DIR}"
  echo "✅ Clean complete"
  exit 0
fi

mkdir -p "${BUILD_DIR}"
mkdir -p "${OUT_DIR}/lib" "${OUT_DIR}/bin" "${OUT_DIR}/include"

pushd "${BUILD_DIR}" > /dev/null

echo "==> Configuring CMake for target binder libraries..."

# Set CMAKE compilers if cross-compilation is requested
if [ -n "${TARGET_CC}" ] && [ -n "${TARGET_CXX}" ]; then
  CMAKE_C_COMPILER="${TARGET_CC}" \
  CMAKE_CXX_COMPILER="${TARGET_CXX}" \
  cmake "${ROOT_DIR}" \
    -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
    -DBUILD_CORE_SDK=ON \
    -DBUILD_HOST_AIDL=OFF \
    -DTARGET_LIB32_VERSION="${TARGET_LIB32}"
else
  cmake "${ROOT_DIR}" \
    -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
    -DBUILD_CORE_SDK=ON \
    -DBUILD_HOST_AIDL=OFF \
    -DTARGET_LIB32_VERSION="${TARGET_LIB32}"
fi

echo "==> Building target binder libraries..."
cmake --build . --target all -- -j"$(nproc)"

echo "==> Installing to ${OUT_DIR}..."
cp *.so "${OUT_DIR}/lib/" 2>/dev/null || true
cp servicemanager "${OUT_DIR}/bin/" 2>/dev/null || true

# Install headers
cp -r "${ROOT_DIR}/binder_aidl_gen/include/"* "${OUT_DIR}/include/" 2>/dev/null || true
cp -r "${ROOT_DIR}/android/native/libs/binder/include/binder" "${OUT_DIR}/include/" 2>/dev/null || true
cp -r "${ROOT_DIR}/android/native/libs/binder/ndk/include_cpp/"* "${OUT_DIR}/include/" 2>/dev/null || true
cp -r "${ROOT_DIR}/android/libbase/include/"* "${OUT_DIR}/include/" 2>/dev/null || true
cp -r "${ROOT_DIR}/android/core/libutils/include/"* "${OUT_DIR}/include/" 2>/dev/null || true
cp -r "${ROOT_DIR}/android/core/libcutils/include/"* "${OUT_DIR}/include/" 2>/dev/null || true
cp -r "${ROOT_DIR}/android/logging/liblog/include/"* "${OUT_DIR}/include/" 2>/dev/null || true

popd > /dev/null

echo ""
echo "✅ Target binder libraries built successfully"
echo "   Libraries:      ${OUT_DIR}/lib/"
echo "   Servicemanager: ${OUT_DIR}/bin/servicemanager"
echo "   Headers:        ${OUT_DIR}/include/"

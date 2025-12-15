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
# build-aidl-generator-tool.sh
#
# Builds ONLY the host AIDL compiler tools (aidl, aidl-cpp)
# These run on the build machine to generate code.
#
# Output: out/host/
#   - bin/aidl
#   - bin/aidl-cpp
#
# Build Variables:
#   HOST_CC, HOST_CXX  - Host compiler (default: gcc/g++ for native architecture)
#   BUILD_TYPE         - Debug or Release (default: Release)
#
# Options:
#   --clean        - Clean build and output directories before building
#
# Note: This ALWAYS builds for the HOST architecture (build machine).
#       CC/CXX environment variables are IGNORED (may be target cross-compilers).
#       Use HOST_CC/HOST_CXX to override native compilers if needed.
# -------------------------------------------------------------------

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ROOT_DIR="${SCRIPT_DIR}"

BUILD_DIR="${ROOT_DIR}/build-host"
OUT_DIR="${ROOT_DIR}/out/host"
BUILD_TYPE="${BUILD_TYPE:-Release}"
CLEAN_BUILD=false

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

# Force native x86_64 compilers for host tools
# Host tools MUST run on the build machine, not the target
# Ignore any cross-compilation environment (Yocto CC/CXX)
HOST_CC="${HOST_CC:-gcc}"
HOST_CXX="${HOST_CXX:-g++}"

echo "=========================================="
echo "  Building AIDL Host Tools"
echo "=========================================="
echo "Root dir:        ${ROOT_DIR}"
echo "Build dir:       ${BUILD_DIR}"
echo "Output dir:      ${OUT_DIR}"
echo "Build type:      ${BUILD_TYPE}"
echo "Host CC:         ${HOST_CC}"
echo "Host CXX:        ${HOST_CXX}"
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
mkdir -p "${OUT_DIR}/bin"

pushd "${BUILD_DIR}" > /dev/null

echo "==> Configuring CMake for host AIDL tools..."

# Force CMAKE to use native compilers for host tools
CMAKE_C_COMPILER="${HOST_CC}" \
CMAKE_CXX_COMPILER="${HOST_CXX}" \
cmake "${ROOT_DIR}" \
  -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
  -DBUILD_CORE_SDK=ON \
  -DBUILD_HOST_AIDL=ON

echo "==> Building host AIDL compiler (and required libraries)..."
cmake --build . --target aidl aidl-cpp -- -j"$(nproc)"

echo "==> Installing to ${OUT_DIR}..."
cp aidl aidl-cpp "${OUT_DIR}/bin/"

popd > /dev/null

echo ""
echo "✅ Host AIDL tools built successfully"
echo "   Output: ${OUT_DIR}/bin/aidl"
echo "   Output: ${OUT_DIR}/bin/aidl-cpp"

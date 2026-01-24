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
CLEAN_BUILD=false
BUILD_HOST_AIDL_TOOL=true

# Install prefix configuration (override via environment for custom locations)
INSTALL_PREFIX="${INSTALL_PREFIX:-${OUT_DIR}/target}"
SDK_INCLUDE_DIR="${SDK_INCLUDE_DIR:-${OUT_DIR}/build/include}"

# Use CC/CXX/CFLAGS etc. for target cross-compilation
# If not set, use system default (native build)
# Yocto/OE often embeds flags directly in CC/CXX - extract just the compiler executable
TARGET_CC="${CC:-}"
TARGET_CXX="${CXX:-}"

# Extract compiler executable from CC/CXX if they contain flags
# Yocto pattern: CC="arm-oe-linux-gnueabi-gcc -march=... --sysroot=..."
if [ -n "${TARGET_CC}" ]; then
    # Extract first word (compiler path/name) and flags separately
    TARGET_CC_EXEC=$(echo "${TARGET_CC}" | awk '{print $1}')
    TARGET_CC_FLAGS=$(echo "${TARGET_CC}" | cut -d' ' -f2-)
    if [ "${TARGET_CC_EXEC}" = "${TARGET_CC_FLAGS}" ]; then
        # No flags in CC, just compiler
        TARGET_CC_FLAGS=""
    fi
    TARGET_CC="${TARGET_CC_EXEC}"
else
    TARGET_CC_FLAGS=""
fi

if [ -n "${TARGET_CXX}" ]; then
    TARGET_CXX_EXEC=$(echo "${TARGET_CXX}" | awk '{print $1}')
    TARGET_CXX_FLAGS=$(echo "${TARGET_CXX}" | cut -d' ' -f2-)
    if [ "${TARGET_CXX_EXEC}" = "${TARGET_CXX_FLAGS}" ]; then
        TARGET_CXX_FLAGS=""
    fi
    TARGET_CXX="${TARGET_CXX_EXEC}"
else
    TARGET_CXX_FLAGS=""
fi

# Merge extracted CC/CXX flags into CFLAGS/CXXFLAGS
TARGET_CFLAGS="${TARGET_CC_FLAGS:+${TARGET_CC_FLAGS} }${CFLAGS:-}"
TARGET_CXXFLAGS="${TARGET_CXX_FLAGS:+${TARGET_CXX_FLAGS} }${CXXFLAGS:-}"
TARGET_LDFLAGS="${LDFLAGS:-}"

# Architecture configuration - must be set explicitly by Yocto or user
# Validate that exactly one architecture flag is set
if [ -n "${TARGET_LIB32_VERSION:-}" ] && [ -n "${TARGET_LIB64_VERSION:-}" ]; then
    echo "❌ Error: Both TARGET_LIB32_VERSION and TARGET_LIB64_VERSION are set"
    echo "   Please set exactly one architecture flag."
    exit 1
fi

if [ -z "${TARGET_LIB32_VERSION:-}" ] && [ -z "${TARGET_LIB64_VERSION:-}" ]; then
    # Default to 64-bit for native builds if not specified
    TARGET_LIB32="OFF"
    TARGET_ARCH_DISPLAY="64-bit (default)"
else
    if [ "${TARGET_LIB32_VERSION:-OFF}" = "ON" ]; then
        TARGET_LIB32="ON"
        TARGET_ARCH_DISPLAY="32-bit"
    else
        TARGET_LIB32="OFF"
        TARGET_ARCH_DISPLAY="64-bit"
    fi
fi

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
  
  # Clean build directories
  rm -rf "${BUILD_DIR}" 2>/dev/null || true
  echo "    Cleaned: ${BUILD_DIR}"
  rm -rf "${ROOT_DIR}/build-target-cmake" 2>/dev/null || true
  echo "    Cleaned: ${ROOT_DIR}/build-target-cmake"
  rm -rf "${ROOT_DIR}/build-host" 2>/dev/null || true
  echo "    Cleaned: ${ROOT_DIR}/build-host"
  rm -rf "${ROOT_DIR}/build-target" 2>/dev/null || true
  echo "    Cleaned: ${ROOT_DIR}/build-target"
  
  # Clean all output directories (target, host, build, examples)
  rm -rf "${OUT_DIR}" 2>/dev/null || true
  echo "    Cleaned: ${OUT_DIR} (all subdirectories: target, host, build)"
  
  # Clean CMake artifacts
  rm -rf "${ROOT_DIR}/CMakeFiles" 2>/dev/null || true
  echo "    Cleaned: ${ROOT_DIR}/CMakeFiles"
  
  # Clean Android sources (bison/flex tools)
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
mkdir -p "${INSTALL_PREFIX}/lib" "${INSTALL_PREFIX}/bin"
mkdir -p "${SDK_INCLUDE_DIR}"

echo "==> Configuring CMake for target binder libraries..."

# Prepare CMake arguments
CMAKE_ARGS=(
  -S "${ROOT_DIR}"
  -B "${BUILD_DIR}"
  -DCMAKE_BUILD_TYPE="${BUILD_TYPE}"
  -DCMAKE_INSTALL_PREFIX="${INSTALL_PREFIX}"
  -DCMAKE_INSTALL_INCDIR="${SDK_INCLUDE_DIR}"
  -DBUILD_HOST_AIDL=OFF
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

# Handle CMAKE_TOOLCHAIN_FILE
# When cross-compiling with manual flags (Yocto environment-setup),
# we need to prevent CMake from auto-detecting incompatible toolchain files
if [ -n "${CMAKE_TOOLCHAIN_FILE+x}" ]; then
  # Variable is set (even if empty) - respect user's choice
  if [ -z "${CMAKE_TOOLCHAIN_FILE}" ]; then
    # Explicitly disabled (empty string)
    CMAKE_ARGS+=(-DCMAKE_TOOLCHAIN_FILE=)
  else
    # User provided a toolchain file
    CMAKE_ARGS+=(-DCMAKE_TOOLCHAIN_FILE="${CMAKE_TOOLCHAIN_FILE}")
  fi
fi

# Run CMake configuration
cmake "${CMAKE_ARGS[@]}"

echo "==> Building target binder libraries..."
cmake --build "${BUILD_DIR}" --target all -- -j"$(nproc)"

echo "==> Installing to ${INSTALL_PREFIX}/ and ${SDK_INCLUDE_DIR}/..."

# Copy build artifacts to install prefix
# Note: CMake build outputs to CMAKE_BINARY_DIR, then we copy to INSTALL_PREFIX
if [ -f "${BUILD_DIR}"/servicemanager ]; then
    cp "${BUILD_DIR}"/servicemanager "${INSTALL_PREFIX}/bin/" || {
        echo "❌ Failed to copy servicemanager"
        exit 1
    }
    echo "   ✓ Copied servicemanager"
else
    echo "⚠️  Warning: servicemanager not found in ${BUILD_DIR}/"
fi

# Copy shared libraries
SO_FILES=$(find "${BUILD_DIR}" -maxdepth 1 -name "*.so" 2>/dev/null)
if [ -n "${SO_FILES}" ]; then
    cp "${BUILD_DIR}"/*.so "${INSTALL_PREFIX}/lib/" || {
        echo "❌ Failed to copy shared libraries"
        exit 1
    }
    echo "   ✓ Copied $(echo "${SO_FILES}" | wc -l) shared libraries"
else
    echo "❌ Error: No shared libraries (.so files) found in ${BUILD_DIR}/"
    echo "   Build may have failed silently. Check CMake output above."
    exit 1
fi

# Install SDK headers using CMake
cmake --install "${BUILD_DIR}" || {
    echo "❌ CMake install failed"
    exit 1
}

echo ""
echo "✅ Target binder libraries built successfully"
echo "   Libraries:      ${INSTALL_PREFIX}/lib/"
echo "   Servicemanager: ${INSTALL_PREFIX}/bin/servicemanager"
echo "   Headers:        ${SDK_INCLUDE_DIR}/"

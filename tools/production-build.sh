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

# ==============================================================================
# production-build.sh
#
# Production build script for Linux Binder - works with any toolchain.
# Can be used for both native (host) builds and cross-compilation (ARM).
# The toolchain environment must be set up before calling this script.
#
# IMPORTANT: The SDK (libbinder, liblog, etc.) must be rebuilt with the same
# toolchain used for the final build. Use --clean to ensure fresh SDK build.
#
# Usage:
#   # Native build (uses system compiler):
#   ./tools/production-build.sh /path/to/source /path/to/install [--clean]
#
#   # Cross-compilation (source toolchain first):
#   source /opt/toolchains/.../environment-setup-...
#   ./tools/production-build.sh /path/to/source /path/to/install --clean
#
#   # In RDK docker:
#   sc docker run rdk-kirkstone ". /opt/toolchains/.../.../environment-setup-...; \
#     /path/to/production-build.sh /path/to/source /path/to/install --clean"
# ==============================================================================

set -e

CLEAN_BUILD=false
SOURCE_DIR=""
INSTALL_PREFIX=""

# Parse arguments
for arg in "$@"; do
    case "$arg" in
        --clean)
            CLEAN_BUILD=true
            ;;
        *)
            if [ -z "$SOURCE_DIR" ]; then
                SOURCE_DIR="$arg"
            elif [ -z "$INSTALL_PREFIX" ]; then
                INSTALL_PREFIX="$arg"
            fi
            ;;
    esac
done

if [ -z "$SOURCE_DIR" ] || [ -z "$INSTALL_PREFIX" ]; then
    echo "Usage: $0 <source_dir> <install_prefix> [--clean]"
    echo "  source_dir     - Path to linux_binder_idl source directory"
    echo "  install_prefix - Path where libraries/binaries will be installed"
    echo "  --clean        - Clean build artifacts and SDK before building (recommended for toolchain changes)"
    exit 1
fi

# Convert to absolute paths
SOURCE_DIR="$(cd "$SOURCE_DIR" && pwd)"
INSTALL_PREFIX="$(mkdir -p "$INSTALL_PREFIX" && cd "$INSTALL_PREFIX" && pwd)"

if [ ! -d "${SOURCE_DIR}" ]; then
    echo "Error: Source directory does not exist: ${SOURCE_DIR}"
    exit 1
fi

cd "${SOURCE_DIR}"

echo "========================================"
echo "  Production Build"
echo "========================================"
echo "Source:  ${SOURCE_DIR}"
echo "Install: ${INSTALL_PREFIX}"
echo "Compiler: ${CC:-system default}"
echo "Clean:   ${CLEAN_BUILD}"
echo "========================================"
echo ""

if [ "${CLEAN_BUILD}" = true ]; then
    echo "==> Cleaning build artifacts and SDK..."
    rm -rf build-production 2>/dev/null || true
    rm -rf "${INSTALL_PREFIX}" 2>/dev/null || true
    echo "    Cleaned: build-production"
    echo "    Cleaned: ${INSTALL_PREFIX}"
    echo ""
fi

echo "==> Configuring production build..."

# Compute SDK include directory relative to install prefix
# If INSTALL_PREFIX is /path/to/out/target, headers go to /path/to/out/build/include
SDK_INCLUDE_DIR="$(dirname "${INSTALL_PREFIX}")/build/include"

cmake -S . -B build-production \
    -DCMAKE_INSTALL_PREFIX="${INSTALL_PREFIX}" \
    -DCMAKE_INSTALL_INCDIR="${SDK_INCLUDE_DIR}" \
    -DBUILD_HOST_AIDL=OFF

echo "==> Building production libraries (SDK will be built with current toolchain)..."
cmake --build build-production -- -j$(nproc)

echo "==> Installing production libraries..."
cmake --install build-production --prefix "${INSTALL_PREFIX}"

echo "==> Build complete!"
echo ""
echo "Installed to: ${INSTALL_PREFIX}"

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

# ==============================================================================
# build-binder-example.sh
#
# Build example client/server code that links against the target Binder SDK.
#
# Behaviour:
#   - Always calls build-linux-binder-aidl.sh first (stamps make this cheap).
#   - Uses its own build directory: ${BUILD_DIR}/examples
#   - Runs CMake and builds the example targets.
#
# Flags:
#   --force   Force rebuild of examples (and pass --force to Binder SDK build).
#   --clean   Remove examples build dir (and pass --clean to Binder SDK build).
#   --help    Show usage.
# ==============================================================================

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# shellcheck source=/dev/null
. "${SCRIPT_DIR}/setup-env.sh"

TARGET_SDK_DIR="${TARGET_SDK_DIR:-${WORK_DIR}/local}"
EXAMPLE_BUILD_DIR="${BUILD_DIR}/examples"

FORCE=0
CLEAN=0

usage() {
  cat <<EOF
Usage: $(basename "$0") [--force] [--clean] [--help]

Build binder example binaries that link against the target Binder SDK.

Options:
  --force   Force rebuild of Binder SDK and examples.
  --clean   Remove examples build directory (and clean Binder SDK as well).
  --help    Show this help and exit.

Environment:
  WORK_DIR       Root of repo.
  BUILD_DIR      Root for build artifacts.
  TARGET_SDK_DIR Target Binder SDK root (libs + headers).
EOF
}

while [ $# -gt 0 ]; do
  case "$1" in
    --force) FORCE=1 ;;
    --clean) CLEAN=1 ;;
    --help)  usage; exit 0 ;;
    *) LOGE "Unknown option: $1"; usage; exit 1 ;;
  esac
  shift
done

LOGI "==== build-binder-example.sh ===="
LOGI "WORK_DIR        = ${WORK_DIR}"
LOGI "BUILD_DIR       = ${BUILD_DIR}"
LOGI "TARGET_SDK_DIR  = ${TARGET_SDK_DIR}"
LOGI "FORCE=${FORCE} CLEAN=${CLEAN}"

# ------------------------------------------------------------------------------
# 1) Ensure Binder SDK is built
# ------------------------------------------------------------------------------
BUILD_ARGS=()
[ "${FORCE}" -eq 1 ] && BUILD_ARGS+=("--force")
[ "${CLEAN}" -eq 1 ] && BUILD_ARGS+=("--clean")

"${SCRIPT_DIR}/build-linux-binder-aidl.sh" "${BUILD_ARGS[@]}"

# ------------------------------------------------------------------------------
# 2) Handle clean for examples
# ------------------------------------------------------------------------------
if [ "${CLEAN}" -eq 1 ]; then
  LOGW "Cleaning binder example build directory..."
  RM "${EXAMPLE_BUILD_DIR}"
fi

MKDIR "${EXAMPLE_BUILD_DIR}"
CD "${EXAMPLE_BUILD_DIR}"

# ------------------------------------------------------------------------------
# 3) Configure & build examples
# ------------------------------------------------------------------------------
LOGI "Configuring CMake for binder examples..."
"${CMAKE}" \
  -DCMAKE_INSTALL_PREFIX="${TARGET_SDK_DIR}" \
  -DBUILD_ENV_HOST=ON \
  "${WORK_DIR}"

LOGI "Building binder example binaries..."
# If you have explicit example targets, list them here instead of 'all'.
"${MAKE}" -j"$(nproc)"

LOGI "==== Binder examples build complete ===="

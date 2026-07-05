#!/usr/bin/env bash
#** *****************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2026 RDK Management
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
#** ******************************************************************************
#
# run-fake-yocto.sh - emulate a Yocto/BitBake build of the HAL libraries
# without a real BitBake, so the production CMake path can be smoke-tested
# offline.
#
# It reproduces, with plain shell + cmake, what a real recipe would do:
#
#   linux-binder recipe   -> stages the Binder SDK into a sysroot, FLAT:
#                              <sysroot>/usr/{include/binder_sdk, lib/binder}
#   rdk-halif-aidl recipe -> do_configure / do_compile / do_install against
#                              that staged sysroot (DEPENDS = "linux-binder").
#
# The point is to exercise the *flat* SDK layout (which differs from the local
# dev split of out/build vs out/target) and the install() path - the bits a
# normal ./build_modules.sh run never touches. See hal-aidl.bb.sample for the
# recipe shape this mirrors.
#
# Usage:
#   ./tests/fake-yocto/run-fake-yocto.sh [--keep]
#       --keep   do not delete the work directory on exit
#
set -uo pipefail

REPO_ROOT="$(cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")/../.." && pwd)"
cd "${REPO_ROOT}"

KEEP=false
[ "${1:-}" = "--keep" ] && KEEP=true
[ "${1:-}" = "--help" ] || [ "${1:-}" = "-h" ] && { sed -n '23,42p' "${BASH_SOURCE[0]}" | sed 's/^# \{0,1\}//'; exit 0; }

WORK="$(mktemp -d "${TMPDIR:-/tmp}/fake-yocto.XXXXXX")"
SYSROOT="${WORK}/recipe-sysroot/usr"     # mirrors ${STAGING_DIR_HOST}${prefix}
IMAGE="${WORK}/image"                    # mirrors ${D}
BUILD="${WORK}/build"                    # mirrors ${B}

cleanup() { [ "${KEEP}" = true ] || rm -rf "${WORK}"; }
trap cleanup EXIT

fail() { echo ""; echo "❌ FAKE-YOCTO FAILED: $1"; exit 1; }

echo "========================================="
echo "  fake-yocto: offline production-build test"
echo "  work dir: ${WORK}"
echo "========================================="

#######################################################################
# Task 1 - linux-binder recipe: build + stage the Binder SDK (flat).
#
# A real linux-binder recipe populates the sysroot via do_populate_sysroot.
# Here we build the SDK once with build_binder.sh and copy it into the
# sysroot in the FLAT layout a Yocto consumer sees:
#   <sysroot>/usr/include/binder_sdk/   (headers)
#   <sysroot>/usr/lib/binder/           (runtime libs)
#######################################################################
echo ""
echo "[linux-binder] building + staging the Binder SDK ..."
if [ ! -f "${REPO_ROOT}/out/target/.sdk_ready" ]; then
    ./build_binder.sh > "${WORK}/build_binder.log" 2>&1 \
        || fail "build_binder.sh failed (see ${WORK}/build_binder.log)"
fi

mkdir -p "${SYSROOT}/include" "${SYSROOT}/lib" "${SYSROOT}/bin"
cp -r "${REPO_ROOT}/out/build/include/binder_sdk" "${SYSROOT}/include/" \
    || fail "binder SDK headers not found at out/build/include/binder_sdk"
cp -r "${REPO_ROOT}/out/target/lib/binder"        "${SYSROOT}/lib/" \
    || fail "binder runtime libs not found at out/target/lib/binder"
[ -d "${REPO_ROOT}/out/target/bin" ] && cp -r "${REPO_ROOT}/out/target/bin/." "${SYSROOT}/bin/"
# The build expects an .sdk_ready marker at BINDER_SDK_DIR.
cp "${REPO_ROOT}/out/target/.sdk_ready" "${SYSROOT}/.sdk_ready"
echo "[linux-binder] staged flat SDK -> ${SYSROOT}"

#######################################################################
# Task 2 - rdk-halif-aidl recipe: do_configure.
#
# Mirrors the recipe in hal-aidl.bb.sample. The SDK is the flat sysroot;
# both BINDER_SDK_DIR and BINDER_SDK_INCLUDE_DIR point at it (in the local
# dev tree those two diverge, which is why both must be passed here).
#######################################################################
echo ""
echo "[hal-aidl] do_configure ..."
cmake -S "${REPO_ROOT}" -B "${BUILD}" \
    -DINTERFACE_TARGET=all \
    -DBINDER_SDK_DIR="${SYSROOT}" \
    -DBINDER_SDK_INCLUDE_DIR="${SYSROOT}" \
    -DCMAKE_INSTALL_PREFIX="${IMAGE}/usr" \
    > "${WORK}/configure.log" 2>&1 \
    || { tail -25 "${WORK}/configure.log" | sed 's/^/    /'; fail "do_configure (cmake configure)"; }

#######################################################################
# Task 3 - do_compile.
#######################################################################
echo "[hal-aidl] do_compile ..."
cmake --build "${BUILD}" -j"$(nproc 2>/dev/null || echo 4)" \
    > "${WORK}/compile.log" 2>&1 \
    || { tail -25 "${WORK}/compile.log" | sed 's/^/    /'; fail "do_compile (cmake build)"; }

#######################################################################
# Task 4 - do_install.
#######################################################################
echo "[hal-aidl] do_install ..."
cmake --install "${BUILD}" > "${WORK}/install.log" 2>&1 \
    || { tail -25 "${WORK}/install.log" | sed 's/^/    /'; fail "do_install (cmake install)"; }

#######################################################################
# Verify the image.
#######################################################################
echo ""
echo "[verify] checking installed image ..."
IMG_LIB_DIR="${IMAGE}/usr/lib/halif"
EXPECTED=$(ls -d "${REPO_ROOT}"/*/current/interface.yaml 2>/dev/null | wc -l)
INSTALLED=$(find "${IMG_LIB_DIR}" -name 'lib*-vcurrent-cpp.so' -type f 2>/dev/null | wc -l)

echo "    image lib dir: ${IMG_LIB_DIR}"
echo "    expected ${EXPECTED} HAL libraries, installed ${INSTALLED}"

[ "${INSTALLED}" -eq "${EXPECTED}" ] || fail "expected ${EXPECTED} HAL libraries in the image, found ${INSTALLED}"

#######################################################################
# Task 5 - flexible binder header path: FLAT (Yocto sysroot) layout (#644).
#######################################################################
# Tasks 1-4 stage headers under include/binder_sdk (the dev subdir). Real Yocto
# stages them flat under <sysroot>/usr/include (binder/ directly, no binder_sdk
# subdir). Pass BINDER_SDK_INCLUDE_DIR as the staging *prefix* — the form the
# README documents (`${STAGING_DIR}/usr`) — and verify the component CMake
# resolves prefix/include via the #644 flexible candidate. Configure-only
# (fast); the pre-fix logic FATALs at the binder-header check, so absence of
# that error == resolved.
echo ""
echo "[verify] flat-layout binder header resolution (#644) ..."
FLAT="${WORK}/flat-sysroot/usr"
mkdir -p "${FLAT}/include" "${FLAT}/lib"
cp -r "${REPO_ROOT}/out/build/include/binder_sdk/." "${FLAT}/include/"   # flat: binder/, utils/, ...
cp -r "${REPO_ROOT}/out/target/lib/binder"          "${FLAT}/lib/"
cmake -S "${REPO_ROOT}/common/current" -B "${WORK}/flat-build" \
    -DBINDER_SDK_DIR="${FLAT}" \
    -DBINDER_SDK_INCLUDE_DIR="${FLAT}" \
    -DHALIF_INCLUDE_DIR="${FLAT}/include" -DHALIF_LIB_DIR="${FLAT}/lib" \
    > "${WORK}/flat-configure.log" 2>&1 || true
if grep -q 'Binder SDK headers not found' "${WORK}/flat-configure.log"; then
    tail -15 "${WORK}/flat-configure.log" | sed 's/^/    /'
    fail "#644: flat binder header layout not resolved (BINDER_SDK_INCLUDE_DIR as a direct include dir)"
fi
echo "    ✓ flat binder headers resolved via BINDER_SDK_INCLUDE_DIR (#644)"

echo ""
echo "========================================="
echo "✅ fake-yocto: production build + install OK (${INSTALLED} HAL libraries)"
echo "========================================="
[ "${KEEP}" = true ] && echo "work dir kept at ${WORK}"
exit 0

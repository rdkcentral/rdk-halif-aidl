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
# run-fake-yocto-per-component.sh - emulate a REAL per-component Yocto build of
# the released HAL snapshots, the way the generated meta-rdk-halif recipes do.
#
# This is the honest counterpart to run-fake-yocto.sh. That script drives the
# top-level CMake and passes only because it fabricates a ${BINDER_SDK_DIR}/
# .sdk_ready marker and runs in a dev tree where the codegen toolchain is
# present - so it cannot catch the failure a real integrator hits. A real
# linux-binder recipe stages libbinder WITHOUT that marker, and a production
# host has no AIDL toolchain, so the top-level path is not viable there (#661).
#
# The supported production path is PER COMPONENT: each released snapshot is
# built from its self-contained <comp>/<ver>/CMakeLists.txt against the staged
# Binder SDK - no .sdk_ready, no toolchain, no codegen. Inter-component
# dependencies (from each snapshot's interface.yaml `imports:`) are satisfied by
# building dependencies first and staging their lib + headers into the sysroot,
# exactly as bitbake DEPENDS + do_populate_sysroot would.
#
# The test proves both directions with hdmicec@0.1.0.0 -> common@0.2.0.0:
#   NEGATIVE control - build hdmicec with the dependency NOT staged. Must FAIL
#                      (this is the exact "cannot find -lcommon-v0.2.0.0-cpp"
#                      breakage reported on release/0.22.0).
#   POSITIVE         - build hdmicec with common staged (lib + headers). Must
#                      SUCCEED and produce libhdmicec-v0.1.0.0-cpp.so.
#
# Usage:
#   ./tests/fake-yocto/run-fake-yocto-per-component.sh [--keep]
#       --keep   do not delete the work directory on exit
#
set -uo pipefail

REPO_ROOT="$(cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")/../.." && pwd)"
cd "${REPO_ROOT}"

KEEP=false
[ "${1:-}" = "--keep" ] && KEEP=true
{ [ "${1:-}" = "--help" ] || [ "${1:-}" = "-h" ]; } && { sed -n '23,52p' "${BASH_SOURCE[0]}" | sed 's/^# \{0,1\}//'; exit 0; }

# The dependency pair under test. hdmicec's interface.yaml declares
# `imports: [common@0.2.0.0]`; keep this in sync with that contract.
DEP_COMP="common";  DEP_VER="0.2.0.0"
MOD_COMP="hdmicec"; MOD_VER="0.1.0.0"

WORK="$(mktemp -d "${TMPDIR:-/tmp}/fake-yocto-pc.XXXXXX")"
SYSROOT="${WORK}/recipe-sysroot/usr"     # mirrors ${STAGING_DIR_HOST}${prefix}
HALIF_LIBS="${SYSROOT}/lib/halif"        # where module install() drops lib*-cpp.so
HALIF_INCS="${SYSROOT}/include/halif"    # dependents look under here for <dep>/<ver>/include

cleanup() { [ "${KEEP}" = true ] || rm -rf "${WORK}"; }
trap cleanup EXIT

fail() { echo ""; echo "❌ FAKE-YOCTO(per-component) FAILED: $1"; exit 1; }

echo "========================================="
echo "  fake-yocto: per-component staged build"
echo "  ${MOD_COMP}@${MOD_VER} -> ${DEP_COMP}@${DEP_VER}"
echo "  work dir: ${WORK}"
echo "========================================="

#######################################################################
# Task 1 - linux-binder recipe: stage the Binder SDK (flat), NO .sdk_ready.
#
# A real linux-binder recipe populates the sysroot via do_populate_sysroot and
# does NOT drop a build_binder.sh .sdk_ready marker. The per-component CMake
# does not require one - proving the marker is a dev-only sentinel.
#######################################################################
echo ""
echo "[linux-binder] staging Binder SDK (flat, no .sdk_ready) ..."
if [ ! -f "${REPO_ROOT}/out/target/.sdk_ready" ]; then
    ./build_binder.sh > "${WORK}/build_binder.log" 2>&1 \
        || fail "build_binder.sh failed (see ${WORK}/build_binder.log)"
fi
mkdir -p "${SYSROOT}/include" "${SYSROOT}/lib"
cp -r "${REPO_ROOT}/out/build/include/binder_sdk" "${SYSROOT}/include/" \
    || fail "binder SDK headers not found at out/build/include/binder_sdk"
cp -r "${REPO_ROOT}/out/target/lib/binder"        "${SYSROOT}/lib/" \
    || fail "binder runtime libs not found at out/target/lib/binder"
# Deliberately NOT copied: out/target/.sdk_ready
echo "[linux-binder] staged -> ${SYSROOT} (no .sdk_ready marker)"

# build_one <comp> <ver> <build-dir> : configure+build a snapshot from its
# self-contained CMakeLists against the staged SDK. HALIF dirs point at the
# sysroot halif layout, so a dependency is resolved iff it has been staged.
build_one() {
    local comp="$1" ver="$2" bdir="$3"
    cmake -S "${REPO_ROOT}/${comp}/${ver}" -B "${bdir}" \
        -DBINDER_SDK_DIR="${SYSROOT}" \
        -DBINDER_SDK_INCLUDE_DIR="${SYSROOT}" \
        -DHALIF_LIB_DIR="${HALIF_LIBS}" \
        -DHALIF_INCLUDE_DIR="${HALIF_INCS}" \
        -DCMAKE_INSTALL_PREFIX="${SYSROOT}" \
        > "${bdir}.configure.log" 2>&1 || return 1
    cmake --build "${bdir}" -j"$(nproc 2>/dev/null || echo 4)" \
        > "${bdir}.compile.log" 2>&1 || return 1
    return 0
}

# stage_dep <comp> <ver> <build-dir> : mirror the meta-rdk-halif recipe's
# do_install - install the built .so (module CMake -> lib/halif) AND stage the
# snapshot's committed headers so dependents resolve
# ${HALIF_INCLUDE_DIR}/<comp>/<ver>/include. The header step is what the module
# install() rule does NOT do; the recipe/bbclass adds it.
stage_dep() {
    local comp="$1" ver="$2" bdir="$3"
    cmake --install "${bdir}" > "${bdir}.install.log" 2>&1 || return 1
    install -d "${HALIF_INCS}/${comp}/${ver}"
    cp -r "${REPO_ROOT}/${comp}/${ver}/include" "${HALIF_INCS}/${comp}/${ver}/" || return 1
    return 0
}

#######################################################################
# Task 2 - rdk-halif-common recipe: build + stage the dependency.
#######################################################################
echo ""
echo "[rdk-halif-${DEP_COMP}] do_configure/do_compile ..."
build_one "${DEP_COMP}" "${DEP_VER}" "${WORK}/build-${DEP_COMP}" \
    || { tail -20 "${WORK}/build-${DEP_COMP}".*.log | sed 's/^/    /'; fail "building ${DEP_COMP}@${DEP_VER}"; }
echo "[rdk-halif-${DEP_COMP}] do_install (stage lib + headers) ..."
stage_dep "${DEP_COMP}" "${DEP_VER}" "${WORK}/build-${DEP_COMP}" \
    || fail "staging ${DEP_COMP}@${DEP_VER}"
ls "${HALIF_LIBS}/lib${DEP_COMP}-v${DEP_VER}-cpp.so" >/dev/null 2>&1 \
    || fail "expected lib${DEP_COMP}-v${DEP_VER}-cpp.so in ${HALIF_LIBS}"
echo "    ✓ staged lib${DEP_COMP}-v${DEP_VER}-cpp.so + headers"

#######################################################################
# Task 3 - NEGATIVE control: dependency NOT staged -> must fail.
#
# This is the failure reported on release/0.22.0: build the dependent against a
# sysroot where the dependency's lib/headers are absent. A pass here would mean
# the test cannot detect the regression, so an unexpected SUCCESS is a failure.
#######################################################################
echo ""
echo "[negative] build ${MOD_COMP} with ${DEP_COMP} NOT staged (expect failure) ..."
EMPTY="${WORK}/empty-sysroot/usr"
mkdir -p "${EMPTY}/include" "${EMPTY}/lib"
cp -r "${REPO_ROOT}/out/build/include/binder_sdk" "${EMPTY}/include/"
cp -r "${REPO_ROOT}/out/target/lib/binder"        "${EMPTY}/lib/"
if cmake -S "${REPO_ROOT}/${MOD_COMP}/${MOD_VER}" -B "${WORK}/neg" \
        -DBINDER_SDK_DIR="${EMPTY}" -DBINDER_SDK_INCLUDE_DIR="${EMPTY}" \
        -DHALIF_LIB_DIR="${EMPTY}/lib/halif" -DHALIF_INCLUDE_DIR="${EMPTY}/include/halif" \
        > "${WORK}/neg.configure.log" 2>&1 \
     && cmake --build "${WORK}/neg" > "${WORK}/neg.compile.log" 2>&1; then
    fail "negative control unexpectedly SUCCEEDED - ${MOD_COMP} built without ${DEP_COMP} staged"
fi
echo "    ✓ reproduced: ${MOD_COMP} fails to build when ${DEP_COMP}@${DEP_VER} is not staged"

#######################################################################
# Task 4 - POSITIVE: dependency staged -> must succeed.
#######################################################################
echo ""
echo "[rdk-halif-${MOD_COMP}] build against staged ${DEP_COMP} (expect success) ..."
build_one "${MOD_COMP}" "${MOD_VER}" "${WORK}/build-${MOD_COMP}" \
    || { tail -20 "${WORK}/build-${MOD_COMP}".*.log | sed 's/^/    /'; fail "building ${MOD_COMP}@${MOD_VER} against staged ${DEP_COMP}"; }
find "${WORK}/build-${MOD_COMP}" -name "lib${MOD_COMP}-v${MOD_VER}-cpp.so" | grep -q . \
    || fail "expected lib${MOD_COMP}-v${MOD_VER}-cpp.so was not produced"
echo "    ✓ built lib${MOD_COMP}-v${MOD_VER}-cpp.so linked against ${DEP_COMP}@${DEP_VER}"

echo ""
echo "========================================="
echo "✅ fake-yocto per-component: staged inter-module build OK"
echo "   (negative control reproduced the release/0.22.0 breakage)"
echo "========================================="
[ "${KEEP}" = true ] && echo "work dir kept at ${WORK}"
exit 0

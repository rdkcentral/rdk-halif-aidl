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
# run-yocto-roles.sh - prove the vendor and middleware build configurations build
# DIVERGENT component versions from the same meta-rdk-halif recipes, each to its
# own destination.
#
# Offline emulation (no BitBake): for each role it reads that role's versions
# manifest (versions_vendor.yaml / versions_mw.yaml - the same files the parent
# meta-<role> layer feeds in via HALIF_VERSIONS_FILE), resolves the build order
# with scripts/halif_plan.py, builds each pinned snapshot against the staged
# Binder SDK, installs to a role-specific sysroot, and asserts the pinned
# versions land there. The vendor cohort is 0.2.x and the MW cohort is 0.1.x, so
# a pass demonstrates version divergence plus destination isolation from one
# shared recipe.
#
# Usage:
#   ./tests/yocto/run-yocto-roles.sh [--keep]
#
set -uo pipefail

REPO_ROOT="$(cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")/../.." && pwd)"
cd "${REPO_ROOT}"

KEEP=false
[ "${1:-}" = "--keep" ] && KEEP=true

WORK="$(mktemp -d "${TMPDIR:-/tmp}/yocto-roles.XXXXXX")"
SDK="${WORK}/sdk/usr"
cleanup() { [ "${KEEP}" = true ] || rm -rf "${WORK}"; }
trap cleanup EXIT
fail() { echo ""; echo "❌ YOCTO-ROLES FAILED: $1"; exit 1; }

echo "========================================="
echo "  yocto roles: vendor vs MW version divergence"
echo "  work dir: ${WORK}"
echo "========================================="

# --- stage the Binder SDK once (shared, no .sdk_ready marker) ---
if [ ! -f "${REPO_ROOT}/out/target/.sdk_ready" ]; then
    ./build_binder.sh > "${WORK}/build_binder.log" 2>&1 || fail "build_binder.sh"
fi
mkdir -p "${SDK}/include" "${SDK}/lib"
cp -r "${REPO_ROOT}/out/build/include/binder_sdk" "${SDK}/include/" || fail "binder headers"
cp -r "${REPO_ROOT}/out/target/lib/binder"        "${SDK}/lib/"     || fail "binder libs"

# read_manifest <file> : print "<comp> <ver>" lines from the components: map
read_manifest() {
    sed -n '/^components:/,$ { s/^[[:space:]]\{1,\}\([A-Za-z0-9_]\{1,\}\):[[:space:]]*\([0-9][0-9.]*\).*/\1 \2/p }' "$1"
}

# build_into <role-sysroot> <comp> <ver> : build the snapshot and install its
# lib + headers into the role sysroot's halif layout (mirrors the bbclass).
build_into() {
    local sys="$1" comp="$2" ver="$3"
    local bdir="${WORK}/build-${comp}-${ver}"
    cmake -S "${REPO_ROOT}/${comp}/${ver}" -B "${bdir}" \
        -DBINDER_SDK_DIR="${SDK}" -DBINDER_SDK_INCLUDE_DIR="${SDK}" \
        -DHALIF_LIB_DIR="${sys}/lib/halif" -DHALIF_INCLUDE_DIR="${sys}/include/halif" \
        > "${bdir}.cfg.log" 2>&1 || { tail -15 "${bdir}.cfg.log" | sed 's/^/    /'; fail "configure ${comp}@${ver}"; }
    cmake --build "${bdir}" -j"$(nproc 2>/dev/null || echo 4)" \
        > "${bdir}.build.log" 2>&1 || { tail -15 "${bdir}.build.log" | sed 's/^/    /'; fail "build ${comp}@${ver}"; }
    install -d "${sys}/lib/halif" "${sys}/include/halif/${comp}/${ver}"
    install -m 0755 "${bdir}"/lib${comp}-v${ver}-cpp.so "${sys}/lib/halif/" || fail "stage lib ${comp}@${ver}"
    cp -r "${REPO_ROOT}/${comp}/${ver}/include" "${sys}/include/halif/${comp}/${ver}/" \
        || fail "stage headers ${comp}@${ver}"
}

# build_role <role> : build every component in versions_<role>.yaml, in the
# topological order scripts/halif_plan.py resolves - exactly what the single
# rdk-halif recipe's do_compile does.
build_role() {
    local role="$1"
    local manifest="${REPO_ROOT}/tests/yocto/meta-${role}/conf/versions_${role}.yaml"
    local sys="${WORK}/${role}/usr"
    [ -f "${manifest}" ] || fail "missing manifest ${manifest}"
    echo ""
    echo "[${role}] building cohort from $(basename "${manifest}") ..."
    # Components to build (the manifest's keys); versions come from the manifest
    # itself via --versions - exactly how the recipe consumes it.
    local comps="" comp ver
    while read -r comp ver; do
        [ -n "${comp}" ] && comps="${comps} ${comp}"
    done <<< "$(read_manifest "${manifest}")"
    # topological build order (dependencies first)
    local plan
    plan="$("${REPO_ROOT}/scripts/halif_plan.py" --versions "${manifest}" ${comps})" \
        || fail "halif_plan for ${role}"
    while read -r comp ver; do
        [ -n "${comp}" ] && build_into "${sys}" "${comp}" "${ver}" && echo "    ✓ ${comp}@${ver}"
    done <<< "${plan}"
}

build_role vendor
build_role mw

# --- assert divergence: each role's dest carries its own pinned versions ---
echo ""
echo "[verify] destinations carry the divergent cohorts ..."
assert_lib() {  # role ver comp
    local f="${WORK}/$1/usr/lib/halif/lib$3-v$2-cpp.so"
    [ -f "${f}" ] || fail "expected $3@$2 in the $1 destination ($f)"
    echo "    ✓ $1 dest has lib$3-v$2-cpp.so"
}
assert_absent() {  # role ver comp  (the OTHER role's version must not be here)
    local f="${WORK}/$1/usr/lib/halif/lib$3-v$2-cpp.so"
    [ ! -f "${f}" ] || fail "$1 destination unexpectedly contains $3@$2"
}
assert_lib vendor 0.2.0.0 common
assert_lib vendor 0.2.0.0 avclock
assert_lib mw     0.1.0.0 common
assert_lib mw     0.1.0.0 avclock
assert_absent vendor 0.1.0.0 common
assert_absent mw     0.2.0.0 common

echo ""
echo "========================================="
echo "✅ yocto roles: vendor (0.2.x) and MW (0.1.x) built divergent cohorts"
echo "   from the same recipes, each into its own destination"
echo "========================================="
[ "${KEEP}" = true ] && echo "work dir kept at ${WORK}"
exit 0

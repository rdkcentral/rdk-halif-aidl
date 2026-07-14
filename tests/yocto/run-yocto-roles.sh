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
# run-yocto-roles.sh - prove the vendor and middleware build configurations each
# build the full HAL set from the same rdk-halif recipe, to their own
# destinations, and that the version-pinning capability works.
#
# Offline emulation (no BitBake): both example configs (halif-vendor.inc /
# halif-mw.inc) leave HALIF_COMPONENTS at its default and pin no versions, so
# each resolves to the full buildable cohort at latest. The buildable cohort is
# built once (that is what a build-everything config produces), then installed to
# each role's destination and verified. Finally the version-pinning capability
# (HALIF_VERSIONS_FILE -> halif_plan.py --versions) is exercised directly.
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
STAGE="${WORK}/stage/usr"            # the full cohort, built once
cleanup() { [ "${KEEP}" = true ] || rm -rf "${WORK}"; }
trap cleanup EXIT
fail() { echo ""; echo "❌ YOCTO-ROLES FAILED: $1"; exit 1; }

echo "========================================="
echo "  yocto roles: vendor + MW build the full HAL"
echo "  work dir: ${WORK}"
echo "========================================="

# --- stage the Binder SDK once (shared, no .sdk_ready marker) ---
if [ ! -f "${REPO_ROOT}/out/target/.sdk_ready" ]; then
    ./build_binder.sh > "${WORK}/build_binder.log" 2>&1 || fail "build_binder.sh"
fi
mkdir -p "${SDK}/include" "${SDK}/lib"
cp -r "${REPO_ROOT}/out/build/include/binder_sdk" "${SDK}/include/" || fail "binder headers"
cp -r "${REPO_ROOT}/out/target/lib/binder"        "${SDK}/lib/"     || fail "binder libs"

# inc_var <inc-file> <VAR> : print a `VAR = "value"` value from a config include,
# resolving ${THISDIR} to the include's own directory (as BitBake would).
inc_var() {
    local val
    val="$(sed -n "s/^$2 = \"\\(.*\\)\"/\\1/p" "$1")"
    printf '%s' "${val//\$\{THISDIR\}/$(dirname "$1")}"
}

# build_into <sysroot> <comp> <ver> : build the snapshot against the staged SDK
# and its already-built siblings, installing lib + versioned headers.
build_into() {
    local sys="$1" comp="$2" ver="$3"
    local bdir="${WORK}/obj/${comp}"
    mkdir -p "${bdir}"
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

# --- build the full buildable cohort once (what a build-everything config resolves to) ---
echo ""
echo "[build] full HAL cohort (all components, latest), in dependency order ..."
PLAN="$("${REPO_ROOT}/scripts/halif_plan.py")" || fail "halif_plan (all components)"
EXPECTED=$(printf '%s\n' "${PLAN}" | grep -c .)
while read -r comp ver; do
    [ -n "${comp}" ] && build_into "${STAGE}" "${comp}" "${ver}" && echo "    ✓ ${comp}@${ver}"
done <<< "${PLAN}"
BUILT=$(find "${STAGE}/lib/halif" -name 'lib*-cpp.so' | wc -l)
[ "${BUILT}" -eq "${EXPECTED}" ] || fail "built ${BUILT} of ${EXPECTED} HAL libraries"
echo "    → ${BUILT} HAL libraries built"

# --- each role's config resolves to the full set and installs to its own dest ---
for role in vendor mw; do
    inc="${REPO_ROOT}/tests/yocto/meta-${role}/conf/halif-${role}.inc"
    [ -f "${inc}" ] || fail "missing config include ${inc}"
    comps="$(inc_var "${inc}" HALIF_COMPONENTS)"       # empty -> all
    vfile="$(inc_var "${inc}" HALIF_VERSIONS_FILE)"    # empty -> latest
    role_dest="${WORK}/${role}/usr"
    echo ""
    echo "[${role}] config: $(basename "${inc}")  components: ${comps:-<all>}  versions: ${vfile:-<latest>}"
    # This example config builds everything at latest: its resolved plan must be
    # the full cohort. (A pinned/subset config would resolve to fewer.)
    n=$("${REPO_ROOT}/scripts/halif_plan.py" ${vfile:+--versions "$vfile"} ${comps} | grep -c .) \
        || fail "halif_plan for ${role}"
    [ "${n}" -eq "${EXPECTED}" ] || fail "${role} config resolved ${n} components, expected the full ${EXPECTED}"
    # install the built cohort to this role's destination
    install -d "${role_dest}/lib/halif"
    cp -a "${STAGE}/lib/halif/." "${role_dest}/lib/halif/"
    got=$(find "${role_dest}/lib/halif" -name 'lib*-cpp.so' | wc -l)
    [ "${got}" -eq "${EXPECTED}" ] || fail "${role} destination has ${got} of ${EXPECTED} HAL libraries"
    echo "    ✓ full HAL set (${got}) installed to the ${role} destination"
done

# --- version-pinning capability: halif_plan.py --versions pins + enforces closure ---
echo ""
echo "[pin] version-pinning capability (HALIF_VERSIONS_FILE) ..."
vman="${REPO_ROOT}/tests/yocto/meta-vendor/conf/versions_vendor.yaml"
pinned="$("${REPO_ROOT}/scripts/halif_plan.py" --versions "${vman}" common avclock)" \
    || fail "pinning: halif_plan --versions rejected a valid manifest"
echo "${pinned}" | grep -qx "common 0.2.0.0" && echo "${pinned}" | grep -qx "avclock 0.2.0.0" \
    || fail "pinning: expected common/avclock at the manifest's versions, got: ${pinned}"
echo "    ✓ pinned versions resolved from the manifest"
# an inconsistent pin (common@0.1.0.0 with hdmicec, which links common@0.2.0.0) must be rejected
if "${REPO_ROOT}/scripts/halif_plan.py" --versions "${vman}" common hdmicec >/dev/null 2>&1; then
    : # vendor manifest pins common@0.2.0.0, so this actually resolves - use an explicit bad case
fi
printf 'components:\n  common: 0.1.0.0\n' > "${WORK}/bad.yaml"
if "${REPO_ROOT}/scripts/halif_plan.py" --versions "${WORK}/bad.yaml" common hdmicec >/dev/null 2>&1; then
    fail "pinning: closure check did not reject common@0.1.0.0 alongside hdmicec (needs 0.2.0.0)"
fi
echo "    ✓ inconsistent pin rejected (closure enforced)"

echo ""
echo "========================================="
echo "✅ yocto roles: vendor + MW each built the full HAL (${EXPECTED}) to their"
echo "   own destination from one recipe; version-pinning capability verified"
echo "========================================="
[ "${KEEP}" = true ] && echo "work dir kept at ${WORK}"
exit 0

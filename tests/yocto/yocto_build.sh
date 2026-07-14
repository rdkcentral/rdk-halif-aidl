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
# yocto_build.sh <vendor|mw> [<versions-manifest>] [--keep]
#
# EXAMPLE offline build of the RDK HAL interface libraries for one role,
# emulating (without BitBake) what the rdk-halif recipe's do_compile does. It
# builds EVERY component at the versions in the manifest, in dependency order,
# and installs each component's library + versioned headers to the role's
# destination.
#
# The versions manifest is PASSED IN; it defaults to the repository's
# versions_released.yaml - the real released cohort. Point it at any manifest
# (components: {comp: ver}) to build a different set; unpinned components build
# their latest snapshot.
#
#   ./tests/yocto/yocto_build.sh vendor
#   ./tests/yocto/yocto_build.sh mw /path/to/versions.yaml
#   DEST=/path/to/rootfs/usr ./tests/yocto/yocto_build.sh vendor --keep
#
set -uo pipefail

ROLE="${1:-}"
case "${ROLE}" in
    vendor|mw) ;;
    *) echo "usage: $0 <vendor|mw> [versions-manifest] [--keep]" >&2; exit 2 ;;
esac

REPO_ROOT="$(cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")/../.." && pwd)"
cd "${REPO_ROOT}"

VERSIONS="${2:-${REPO_ROOT}/versions_released.yaml}"
[ -f "${VERSIONS}" ] || { echo "yocto_build: no versions manifest at ${VERSIONS}" >&2; exit 2; }
KEEP=false
for a in "$@"; do [ "$a" = "--keep" ] && KEEP=true; done

WORK="$(mktemp -d "${TMPDIR:-/tmp}/yocto-build-${ROLE}.XXXXXX")"
SDK="${WORK}/sdk/usr"
STAGE="${WORK}/stage/usr"                 # built cohort (dependencies for later builds)
DEST="${DEST:-${WORK}/image/usr}"         # role destination (override with DEST=...)
cleanup() { [ "${KEEP}" = true ] || rm -rf "${WORK}"; }
trap cleanup EXIT
fail() { echo ""; echo "❌ yocto_build(${ROLE}) FAILED: $1"; exit 1; }

echo "========================================="
echo "  yocto_build: ${ROLE} HAL"
echo "  versions:    $(basename "${VERSIONS}")"
echo "  destination: ${DEST}"
echo "========================================="

# --- linux-binder: stage the Binder SDK (flat sysroot, no .sdk_ready marker) ---
if [ ! -f "${REPO_ROOT}/out/target/.sdk_ready" ]; then
    ./build_binder.sh > "${WORK}/build_binder.log" 2>&1 || fail "build_binder.sh"
fi
mkdir -p "${SDK}/include" "${SDK}/lib"
cp -r "${REPO_ROOT}/out/build/include/binder_sdk" "${SDK}/include/" || fail "binder headers"
cp -r "${REPO_ROOT}/out/target/lib/binder"        "${SDK}/lib/"     || fail "binder libs"

# --- resolve the build order at the manifest's versions ---
PLAN="$("${REPO_ROOT}/scripts/halif_plan.py" --versions "${VERSIONS}")" \
    || fail "halif_plan.py --versions ${VERSIONS}"
N=$(printf '%s\n' "${PLAN}" | grep -c .)
echo ""
echo "[plan] ${N} components in dependency order"

# --- build each component against the SDK + already-built siblings ---
while read -r comp ver; do
    [ -z "${comp}" ] && continue
    bdir="${WORK}/obj/${comp}"; mkdir -p "${bdir}"
    cmake -S "${REPO_ROOT}/${comp}/${ver}" -B "${bdir}" \
        -DBINDER_SDK_DIR="${SDK}" -DBINDER_SDK_INCLUDE_DIR="${SDK}" \
        -DHALIF_LIB_DIR="${STAGE}/lib/halif" -DHALIF_INCLUDE_DIR="${STAGE}/include/halif" \
        > "${bdir}.cfg.log" 2>&1 || { tail -15 "${bdir}.cfg.log" | sed 's/^/    /'; fail "configure ${comp}@${ver}"; }
    cmake --build "${bdir}" -j"$(nproc 2>/dev/null || echo 4)" \
        > "${bdir}.bld.log" 2>&1 || { tail -15 "${bdir}.bld.log" | sed 's/^/    /'; fail "build ${comp}@${ver}"; }
    install -d "${STAGE}/lib/halif" "${STAGE}/include/halif/${comp}/${ver}"
    install -m 0755 "${bdir}/lib${comp}-v${ver}-cpp.so" "${STAGE}/lib/halif/" || fail "stage lib ${comp}@${ver}"
    cp -r "${REPO_ROOT}/${comp}/${ver}/include" "${STAGE}/include/halif/${comp}/${ver}/" || fail "stage headers ${comp}@${ver}"
    echo "    ✓ ${comp}@${ver}"
done <<< "${PLAN}"

# --- install the built HAL to the role destination ---
install -d "${DEST}/lib/halif" "${DEST}/include/halif"
cp -a "${STAGE}/lib/halif/." "${DEST}/lib/halif/"
cp -a "${STAGE}/include/halif/." "${DEST}/include/halif/"
GOT=$(find "${DEST}/lib/halif" -name 'lib*-cpp.so' | wc -l)
[ "${GOT}" -eq "${N}" ] || fail "installed ${GOT} of ${N} HAL libraries to ${DEST}"

echo ""
echo "========================================="
echo "✅ yocto_build(${ROLE}): ${GOT} HAL libraries from $(basename "${VERSIONS}")"
echo "   installed to ${DEST}/lib/halif (headers under include/halif/<comp>/<ver>)"
echo "========================================="
[ "${KEEP}" = true ] && echo "work dir kept at ${WORK}"
exit 0

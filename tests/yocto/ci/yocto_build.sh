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
# (components: {comp: ver}) to build a different set - the components it lists,
# at the versions it pins.
#
#   ./tests/yocto/ci/yocto_build.sh vendor
#   ./tests/yocto/ci/yocto_build.sh mw /path/to/versions.yaml
#   DEST=/path/to/rootfs/usr ./tests/yocto/ci/yocto_build.sh vendor --keep
#
#
# ---------------------------------------------------------------------------
# tests/yocto/ci/ is OUR test harness - NOT consumption material. Integrators
# consume the layer at tests/yocto/meta-rdk-halif-aidl/. These scripts emulate
# what the rdk-halif-aidl recipe's do_compile/do_install do, WITHOUT BitBake.
#
# Reads (repo root is three levels up from this file):
#   rdk-halif-aidl/<comp>/<ver>/CMakeLists.txt   the committed snapshots
#   rdk-halif-aidl/versions_released.yaml        the released cohort
#   tests/yocto/meta-rdk-halif-aidl/halif_plan.py  resolves the build order
#
# Work dir - a fresh mktemp EVERY run, nothing persists:
#   <work>/sdk/usr/{include,lib}                 staged Binder SDK
#   <work>/obj/<comp>/                           per-component CMake build dir.
#                                                Keyed by component only, which
#                                                is safe here precisely because
#                                                <work> is always new; the recipe
#                                                versions its obj/ because ${B}
#                                                persists across rebuilds.
#   <work>/stage/usr/lib/rdk-halif-aidl/         built siblings, so components
#   <work>/stage/usr/include/rdk-halif-aidl/     later in the plan can link them
#
# Produces - the same layout the recipe's packages ship, rooted at the role MOUNT
# (a partition, sibling of /usr - not an FHS /usr/lib path):
#   <dest>/<mount>/rdk-halif-aidl/lib<comp>-v<ver>-cpp.so
#   <dest>/<mount>/rdk-halif-aidl/include/<comp>/<ver>/include/com/rdk/hal/...
# where <mount> is /vendor or /mw. <dest> is the rootfs ROOT (override with DEST=).
# ---------------------------------------------------------------------------
set -uo pipefail

ROLE="${1:-}"
case "${ROLE}" in
    vendor|mw) ;;
    *) echo "usage: $0 <vendor|mw> [versions-manifest] [--keep]" >&2; exit 2 ;;
esac
# The role IS the mount point (a partition), matching the recipe's HALIF_MOUNT_POINT.
MOUNT="/${ROLE}"

REPO_ROOT="$(cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")/../../.." && pwd)"
cd "${REPO_ROOT}"

# Args after the role: --keep is a flag (any position); the first non-flag is
# the versions manifest. This keeps `<role> --keep` working with no manifest.
KEEP=false
VERSIONS=""
shift
for a in "$@"; do
    case "$a" in
        --keep) KEEP=true ;;
        *) [ -z "${VERSIONS}" ] && VERSIONS="$a" \
               || { echo "yocto_build: unexpected argument '$a'" >&2; exit 2; } ;;
    esac
done
VERSIONS="${VERSIONS:-${REPO_ROOT}/versions_released.yaml}"
[ -f "${VERSIONS}" ] || { echo "yocto_build: no versions manifest at ${VERSIONS}" >&2; exit 2; }

WORK="$(mktemp -d "${TMPDIR:-/tmp}/yocto-build-${ROLE}.XXXXXX")"
SDK="${WORK}/sdk/usr"
STAGE="${WORK}/stage/usr"                 # built cohort (dependencies for later builds)
DEST="${DEST:-${WORK}/image}"            # rootfs ROOT (override with DEST=...); the
                                          # HAL installs under ${DEST}${MOUNT}/rdk-halif-aidl
HALIF_DEST="${DEST}${MOUNT}/rdk-halif-aidl"
cleanup() { [ "${KEEP}" = true ] || rm -rf "${WORK}"; }
trap cleanup EXIT
fail() { echo ""; echo "❌ yocto_build(${ROLE}) FAILED: $1"; exit 1; }

echo "========================================="
echo "  yocto_build: ${ROLE} HAL"
echo "  versions manifest: ${VERSIONS}"
echo "  destination:       ${DEST}"
echo "========================================="

# --- resolve the build order at the manifest's versions, and state it upfront ---
PLAN="$("${REPO_ROOT}/tests/yocto/meta-rdk-halif-aidl/halif_plan.py" --versions "${VERSIONS}")" \
    || fail "halif_plan.py --versions ${VERSIONS}"
N=$(printf '%s\n' "${PLAN}" | grep -c .)
echo ""
echo "[plan] ${N} components to build, versions read from ${VERSIONS} (dependency order):"
printf '%s\n' "${PLAN}" | awk 'NF{printf "         %s@%s\n", $1, $2}'
echo ""

# --- linux-binder: stage the Binder SDK (flat sysroot, no .sdk_ready marker) ---
echo "[linux-binder] staging Binder SDK ..."
if [ ! -f "${REPO_ROOT}/out/target/.sdk_ready" ]; then
    ./build_binder.sh > "${WORK}/build_binder.log" 2>&1 || fail "build_binder.sh"
fi
mkdir -p "${SDK}/include" "${SDK}/lib"
cp -r "${REPO_ROOT}/out/build/include/binder_sdk" "${SDK}/include/" || fail "binder headers"
cp -r "${REPO_ROOT}/out/target/lib/binder"        "${SDK}/lib/"     || fail "binder libs"

# --- build each component against the SDK + already-built siblings ---
while read -r comp ver; do
    [ -z "${comp}" ] && continue
    bdir="${WORK}/obj/${comp}"; mkdir -p "${bdir}"
    cmake -S "${REPO_ROOT}/${comp}/${ver}" -B "${bdir}" \
        -DBINDER_SDK_DIR="${SDK}" -DBINDER_SDK_INCLUDE_DIR="${SDK}" \
        -DHALIF_LIB_DIR="${STAGE}/lib/rdk-halif-aidl" -DHALIF_INCLUDE_DIR="${STAGE}/include/rdk-halif-aidl" \
        > "${bdir}.cfg.log" 2>&1 || { tail -15 "${bdir}.cfg.log" | sed 's/^/    /'; fail "configure ${comp}@${ver}"; }
    cmake --build "${bdir}" -j"$(nproc 2>/dev/null || echo 4)" \
        > "${bdir}.bld.log" 2>&1 || { tail -15 "${bdir}.bld.log" | sed 's/^/    /'; fail "build ${comp}@${ver}"; }
    install -d "${STAGE}/lib/rdk-halif-aidl" "${STAGE}/include/rdk-halif-aidl/${comp}/${ver}"
    install -m 0755 "${bdir}/lib${comp}-v${ver}-cpp.so" "${STAGE}/lib/rdk-halif-aidl/" || fail "stage lib ${comp}@${ver}"
    cp -r "${REPO_ROOT}/${comp}/${ver}/include" "${STAGE}/include/rdk-halif-aidl/${comp}/${ver}/" || fail "stage headers ${comp}@${ver}"
    echo "    ✓ ${comp}@${ver}"
done <<< "${PLAN}"

# --- install the built HAL to the role MOUNT (do_install: libs flat on the mount,
#     headers under the mount's include/ subdir - exactly as the recipe ships) ---
install -d "${HALIF_DEST}" "${HALIF_DEST}/include"
cp -a "${STAGE}/lib/rdk-halif-aidl/." "${HALIF_DEST}/"
cp -a "${STAGE}/include/rdk-halif-aidl/." "${HALIF_DEST}/include/"
GOT=$(find "${HALIF_DEST}" -maxdepth 1 -name 'lib*-cpp.so' | wc -l)
[ "${GOT}" -eq "${N}" ] || fail "installed ${GOT} of ${N} HAL libraries to ${HALIF_DEST}"

echo ""
echo "========================================="
echo "✅ yocto_build(${ROLE}): ${GOT} HAL libraries from $(basename "${VERSIONS}")"
echo "   installed to ${HALIF_DEST} (headers under include/<comp>/<ver>)"
echo "========================================="
[ "${KEEP}" = true ] && echo "work dir kept at ${WORK}"
exit 0

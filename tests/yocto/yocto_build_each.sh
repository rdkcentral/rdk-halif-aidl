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
# yocto_build_each.sh [<versions-manifest>]
#
# Build EVERY released component INDIVIDUALLY, then tear it down before the next:
# for each component it builds that component's dependency closure into a FRESH,
# empty sysroot, verifies the component's library was produced, and removes the
# output. Proves each <comp>/<ver>/CMakeLists.txt builds on its own - the cohort
# on this branch (e.g. release/0.22.0) - not only as part of one cumulative build.
#
# Versions come from the manifest passed in (default: the repo's
# versions_released.yaml). The Binder SDK is staged once and shared read-only.
#
#   ./tests/yocto/yocto_build_each.sh
#   ./tests/yocto/yocto_build_each.sh /path/to/versions.yaml
#
set -uo pipefail

REPO_ROOT="$(cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")/../.." && pwd)"
cd "${REPO_ROOT}"

VERSIONS="${1:-${REPO_ROOT}/versions_released.yaml}"
[ -f "${VERSIONS}" ] || { echo "yocto_build_each: no versions manifest at ${VERSIONS}" >&2; exit 2; }

ROOT="$(mktemp -d "${TMPDIR:-/tmp}/yocto-each.XXXXXX")"
SDK="${ROOT}/sdk/usr"
trap 'rm -rf "${ROOT}"' EXIT
fail() { echo ""; echo "❌ yocto_build_each FAILED: $1"; exit 1; }

echo "========================================="
echo "  yocto_build_each: build every component INDIVIDUALLY"
echo "  versions manifest: ${VERSIONS}"
echo "  (fresh sysroot per component; output removed between)"
echo "========================================="

# --- stage the Binder SDK once (shared, read-only) ---
if [ ! -f "${REPO_ROOT}/out/target/.sdk_ready" ]; then
    ./build_binder.sh > "${ROOT}/build_binder.log" 2>&1 || fail "build_binder.sh"
fi
mkdir -p "${SDK}/include" "${SDK}/lib"
cp -r "${REPO_ROOT}/out/build/include/binder_sdk" "${SDK}/include/" || fail "binder headers"
cp -r "${REPO_ROOT}/out/target/lib/binder"        "${SDK}/lib/"     || fail "binder libs"

# build_into <stage> <comp> <ver> : build one snapshot against the SDK + whatever
# is already in <stage>, installing its lib + versioned headers into <stage>.
build_into() {
    local stage="$1" comp="$2" ver="$3"
    local bdir="${ROOT}/obj/${comp}-${ver}"   # separate line: use the locals above
    mkdir -p "${bdir}"
    cmake -S "${REPO_ROOT}/${comp}/${ver}" -B "${bdir}" \
        -DBINDER_SDK_DIR="${SDK}" -DBINDER_SDK_INCLUDE_DIR="${SDK}" \
        -DHALIF_LIB_DIR="${stage}/lib/halif" -DHALIF_INCLUDE_DIR="${stage}/include/halif" \
        > "${bdir}.cfg.log" 2>&1 || return 1
    cmake --build "${bdir}" -j"$(nproc 2>/dev/null || echo 4)" > "${bdir}.bld.log" 2>&1 || return 1
    install -d "${stage}/lib/halif" "${stage}/include/halif/${comp}/${ver}"
    install -m 0755 "${bdir}/lib${comp}-v${ver}-cpp.so" "${stage}/lib/halif/" || return 1
    cp -r "${REPO_ROOT}/${comp}/${ver}/include" "${stage}/include/halif/${comp}/${ver}/" || return 1
    return 0
}

# every component at the manifest's versions
mapfile -t PAIRS < <("${REPO_ROOT}/scripts/halif_plan.py" --versions "${VERSIONS}")
echo ""
echo "Building ${#PAIRS[@]} components individually:"
echo ""

pass=0; failed=""
for pair in "${PAIRS[@]}"; do
    comp="${pair%% *}"; ver="${pair##* }"
    [ -z "${comp}" ] && continue
    stage="${ROOT}/stage/usr"
    # this component's dependency closure (dependencies first, component last)
    cplan="$("${REPO_ROOT}/scripts/halif_plan.py" --closure --versions "${VERSIONS}" "${comp}")" \
        || { echo "  ✗ ${comp}@${ver}  (could not resolve closure)"; failed="${failed} ${comp}"; continue; }
    nclosure=$(printf '%s\n' "${cplan}" | grep -c .)
    ok=true
    while read -r c v; do
        [ -z "${c}" ] && continue
        build_into "${stage}" "${c}" "${v}" || { ok=false; break; }
    done <<< "${cplan}"
    if ${ok} && [ -f "${stage}/lib/halif/lib${comp}-v${ver}-cpp.so" ]; then
        echo "  ✓ ${comp}@${ver}  (built individually; closure of ${nclosure})"
        pass=$((pass + 1))
    else
        echo "  ✗ ${comp}@${ver}  FAILED"
        [ "${ok}" = false ] && tail -12 "${ROOT}/obj/${comp}-${ver}".*.log 2>/dev/null | sed 's/^/        /'
        failed="${failed} ${comp}"
    fi
    # remove this component's output before the next one
    rm -rf "${ROOT}/stage" "${ROOT}/obj"
done

echo ""
echo "========================================="
if [ -z "${failed}" ]; then
    echo "✅ yocto_build_each: all ${pass}/${#PAIRS[@]} components build individually"
    echo "   (from $(basename "${VERSIONS}"), each in a fresh sysroot)"
    echo "========================================="
    exit 0
fi
echo "❌ yocto_build_each: ${pass}/${#PAIRS[@]} passed; FAILED:${failed}"
echo "========================================="
exit 1

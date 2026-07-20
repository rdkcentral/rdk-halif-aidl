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
# yocto_artifact_check.sh [<versions-manifest>]
#
# Inspect the produced libraries, not just whether they built.
#
# WHY THIS EXISTS: every other test here proves the HAL *builds* - configure,
# compile, link, correct filename. A library can pass all of that and still be
# unshippable. That gap let a real defect reach an integrator: every .so carried
# an RPATH holding the absolute build directory, and Yocto's do_package_qa
# rejected the package. We never saw it because nothing looked inside the binary.
#
# We cannot run do_package_qa (no BitBake), so this asserts the artifact-level
# invariants it would enforce:
#
#   1. no RPATH/RUNPATH             - a build path baked into a shipped library
#                                     fails do_package_qa (and is meaningless on
#                                     the target anyway)
#   2. SONAME is versioned          - lib<comp>-v<ver>-cpp.so, so two versions can
#                                     coexist on one rootfs
#   3. binder deps recorded         - DT_NEEDED still lists libbinder/libutils;
#                                     dropping RPATH must not drop the deps
#
#   ./tests/yocto/ci/yocto_artifact_check.sh
#
# tests/yocto/ci/ is OUR harness, not consumption material.
#
set -uo pipefail

REPO_ROOT="$(cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")/../../.." && pwd)"
cd "${REPO_ROOT}"

VERSIONS="${1:-${REPO_ROOT}/versions_released.yaml}"
WORK="$(mktemp -d "${TMPDIR:-/tmp}/yocto-artifact.XXXXXX")"
# yocto_build.sh installs to <DEST>/<mount>/rdk-halif-aidl, where DEST is the rootfs
# root (the mount is a sibling of /usr, not under it).
DEST="${WORK}/image"
trap 'rm -rf "${WORK}"' EXIT

echo "========================================="
echo "  yocto: artifact check (shippability)"
echo "========================================="
echo ""
echo "[build] full HAL from $(basename "${VERSIONS}") ..."
if ! DEST="${DEST}" "${REPO_ROOT}/tests/yocto/ci/yocto_build.sh" vendor "${VERSIONS}" > "${WORK}/build.log" 2>&1; then
    echo "❌ build failed"; tail -15 "${WORK}/build.log" | sed 's/^/    /'; exit 1
fi

command -v readelf >/dev/null || { echo "⚠️  readelf unavailable - skipping"; exit 0; }

fail=0 n=0
for so in "${DEST}"/vendor/rdk-halif-aidl/*.so; do
    [ -f "${so}" ] || continue
    n=$((n + 1))
    base="$(basename "${so}")"
    dyn="$(readelf -d "${so}" 2>/dev/null)"

    # 1. no build paths embedded as RPATH/RUNPATH
    if rp=$(printf '%s\n' "${dyn}" | grep -E "RPATH|RUNPATH"); then
        echo "  ❌ ${base}: carries $(printf '%s' "${rp}" | sed 's/^ *//')"
        fail=$((fail + 1))
    fi

    # 2. versioned SONAME, so versions can coexist on a rootfs
    if ! printf '%s\n' "${dyn}" | grep -q "SONAME.*${base}"; then
        echo "  ❌ ${base}: SONAME is not the versioned library name"
        fail=$((fail + 1))
    fi

    # 3. binder runtime deps still recorded
    if ! printf '%s\n' "${dyn}" | grep -q "NEEDED.*libbinder"; then
        echo "  ❌ ${base}: does not record libbinder in DT_NEEDED"
        fail=$((fail + 1))
    fi
done

echo ""
echo "  libraries inspected: ${n}"
if [ "${n}" -eq 0 ]; then
    echo "❌ no libraries produced"; exit 1
fi
if [ "${fail}" -ne 0 ]; then
    echo ""; echo "❌ artifact check FAILED (${fail} problem(s))"; exit 1
fi
echo ""
echo "========================================="
echo "✅ artifact check: ${n} libraries are shippable"
echo "   (no RPATH/RUNPATH, versioned SONAME, binder deps recorded)"
echo "========================================="
exit 0

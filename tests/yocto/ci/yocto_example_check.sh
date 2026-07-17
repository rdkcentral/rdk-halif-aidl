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
# yocto_example_check.sh
#
# The meta-vendor / meta-mw layers ship EXAMPLE consumer recipes. Reference code
# is worthless if it does not compile - and it silently rots, because nothing
# builds it. This compiles and links every example against the REAL staged HAL,
# using the exact -I/-L/-l flags the example's own .bb declares (extracted from
# it, not reimplemented). So if an example's include path, link flag or C++ is
# wrong, this fails - which is how it should be found HERE, not by an integrator.
#
#   ./tests/yocto/ci/yocto_example_check.sh
#
# tests/yocto/ci/ is OUR harness, not consumption material.
#
set -uo pipefail

REPO_ROOT="$(cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")/../../.." && pwd)"
cd "${REPO_ROOT}"

WORK="$(mktemp -d "${TMPDIR:-/tmp}/yocto-example.XXXXXX")"
STAGE="${WORK}/sysroot/usr"     # mirrors the consumer's recipe-sysroot
trap 'rm -rf "${WORK}"' EXIT
fail() { echo ""; echo "❌ yocto_example_check FAILED: $1"; exit 1; }

echo "========================================="
echo "  yocto: example recipes must compile"
echo "========================================="

# --- stage the full HAL into a sysroot, exactly as DEPENDS='rdk-halif-aidl' would
echo ""
echo "[stage] building the HAL into a sysroot ..."
DEST="${STAGE}" "${REPO_ROOT}/tests/yocto/ci/yocto_build.sh" vendor \
    > "${WORK}/stage.log" 2>&1 || { tail -20 "${WORK}/stage.log" | sed 's/^/    /'; fail "staging the HAL"; }

# the Binder SDK the interface libraries link against
SDK_INC="${REPO_ROOT}/out/build/include/binder_sdk"
SDK_LIB="${REPO_ROOT}/out/target/lib/binder"
[ -d "${SDK_INC}" ] || fail "Binder SDK headers missing (run build_binder.sh)"

CXX="${CXX:-g++}"

# extract_flags <example.bb> <var> : print CXXFLAGS/LDFLAGS from the .bb with the
# bitbake vars it references resolved to this sysroot. We consume the recipe's
# OWN flags so the test tracks what integrators are told to use.
extract_flags() {
    python3 - "$1" "$2" "${STAGE}" <<'PY'
import re, sys
bb, want, stage = sys.argv[1], sys.argv[2], sys.argv[3]
text = open(bb).read()
# HALIF_*_VER ?= "x"  ->  version vars the flag lines interpolate
vers = dict(re.findall(r'(HALIF_\w+_VER)\s*\?\?=\s*"([^"]+)"', text)
            + re.findall(r'(HALIF_\w+_VER)\s*\?=\s*"([^"]+)"', text))
# VAR += "....."  (join line-continuations)
m = re.search(r'%s\s*\+=\s*"((?:[^"\\]|\\.)*)"' % re.escape(want), text, re.S)
if not m:
    sys.exit(0)
val = m.group(1).replace("\\\n", " ")
val = val.replace("${STAGING_INCDIR}", stage + "/include")
val = val.replace("${STAGING_LIBDIR}", stage + "/lib")
for k, v in vers.items():
    val = val.replace("${%s}" % k, v)
print(" ".join(val.split()))
PY
}

check_example() {
    local role="$1" name="$2"
    local dir="${REPO_ROOT}/tests/yocto/meta-${role}/recipes-example/${name}"
    local bb src
    bb="$(find "${dir}" -maxdepth 1 -name '*.bb' | head -1)"
    src="$(find "${dir}/files" -maxdepth 1 -name '*.cpp' | head -1)"
    [ -f "${bb}" ] && [ -f "${src}" ] || fail "example ${name}: .bb or .cpp missing"

    local cxxflags ldflags
    cxxflags="$(extract_flags "${bb}" CXXFLAGS)"
    ldflags="$(extract_flags "${bb}" LDFLAGS)"
    [ -n "${cxxflags}" ] || fail "${name}: no CXXFLAGS found in the recipe"

    echo ""
    echo "[${name}] compile + link with the recipe's own flags ..."
    # shellcheck disable=SC2086
    if "${CXX}" -std=c++17 "${src}" -o "${WORK}/${name}" \
            -I "${SDK_INC}" ${cxxflags} \
            -L "${SDK_LIB}" -Wl,-rpath-link,"${SDK_LIB}" ${ldflags} \
            > "${WORK}/${name}.log" 2>&1; then
        echo "    ✓ ${name} builds against the staged HAL"
    else
        grep -iE "error:|undefined reference|cannot find -l" "${WORK}/${name}.log" | head -15 | sed 's/^/    /'
        fail "${name} did not build"
    fi
}

check_example vendor vendor-halif-example
check_example mw     mw-halif-example

echo ""
echo "========================================="
echo "✅ example recipes compile + link against the staged HAL"
echo "========================================="
exit 0

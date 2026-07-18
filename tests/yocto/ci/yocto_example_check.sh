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
SYSROOT="${WORK}/sysroot"       # the consumer's recipe-sysroot ROOT. The role mounts
                                # are siblings of /usr, so the sysroot is the root
                                # (${STAGING_DIR_HOST}), not /usr.
trap 'rm -rf "${WORK}"' EXIT
fail() { echo ""; echo "❌ yocto_example_check FAILED: $1"; exit 1; }

echo "========================================="
echo "  yocto: example recipes must compile"
echo "========================================="

# --- stage the HAL for BOTH roles into one sysroot, exactly as DEPENDS=
#     'rdk-halif-aidl' would: each role installs to its own mount, so the vendor
#     and mw examples each resolve against their own (${SYSROOT}/vendor/rdk-halif-aidl,
#     ${SYSROOT}/mw/rdk-halif-aidl).
echo ""
for role in vendor mw; do
    echo "[stage] building the ${role} HAL into ${SYSROOT}/${role}/rdk-halif-aidl ..."
    DEST="${SYSROOT}" "${REPO_ROOT}/tests/yocto/ci/yocto_build.sh" "${role}" \
        > "${WORK}/stage-${role}.log" 2>&1 \
        || { tail -20 "${WORK}/stage-${role}.log" | sed 's/^/    /'; fail "staging the ${role} HAL"; }
done

# --- linux-binder: stage the Binder SDK into the sysroot at the non-standard
#     subdirs the interface headers/libs use (include/binder_sdk, lib/binder), so
#     the example's own ${STAGING_INCDIR}/binder_sdk + ${STAGING_LIBDIR}/binder resolve.
SDK_INC="${REPO_ROOT}/out/build/include/binder_sdk"
SDK_LIB="${REPO_ROOT}/out/target/lib/binder"
[ -d "${SDK_INC}" ] || fail "Binder SDK headers missing (run build_binder.sh)"
install -d "${SYSROOT}/usr/include" "${SYSROOT}/usr/lib"
cp -r "${SDK_INC}" "${SYSROOT}/usr/include/binder_sdk"
cp -r "${SDK_LIB}" "${SYSROOT}/usr/lib/binder"

CXX="${CXX:-g++}"

# extract_flags <example.bb> <var> : print CXXFLAGS/LDFLAGS from the .bb with the
# bitbake vars it references resolved to this sysroot. We consume the recipe's OWN
# flags - including its derived vars (HALIF_MOUNT_POINT, HALIF_STAGED, BINDER_*) -
# so the test tracks exactly what integrators are told to use.
extract_flags() {
    python3 - "$1" "$2" "${SYSROOT}" <<'PY'
import re, sys
bb, want, root = sys.argv[1], sys.argv[2], sys.argv[3]
text = open(bb).read()
# Every scalar assignment in the recipe: NAME (??=|?=|=) "value". First one wins,
# which matches ?= semantics closely enough for these recipes. Skips NAME:append.
vars = {}
for name, val in re.findall(
        r'^[ \t]*([A-Za-z_][A-Za-z0-9_]*)[ \t]*(?:\?\?=|\?=|=)[ \t]*"((?:[^"\\]|\\.)*)"',
        text, re.M):
    vars.setdefault(name, val)
# Staging vars bitbake would set; the mounts are siblings of /usr under the root.
vars['STAGING_DIR_HOST'] = root
vars['STAGING_INCDIR']   = root + '/usr/include'
vars['STAGING_LIBDIR']   = root + '/usr/lib'
# The wanted flag var (concatenate its += lines, join continuations).
parts = re.findall(r'%s[ \t]*\+=[ \t]*"((?:[^"\\]|\\.)*)"' % re.escape(want), text, re.S)
if not parts:
    sys.exit(0)
val = ' '.join(p.replace('\\\n', ' ') for p in parts)
# Iteratively expand ${VAR} until stable: HALIF_STAGED -> ${STAGING_DIR_HOST}
# ${HALIF_MOUNT_POINT}/... -> the concrete sysroot path.
for _ in range(25):
    new = re.sub(r'\$\{([A-Za-z_][A-Za-z0-9_]*)\}',
                 lambda m: vars.get(m.group(1), m.group(0)), val)
    if new == val:
        break
    val = new
print(' '.join(val.split()))
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
    # Source first, then the recipe's own -I/-L/-l (which now name the HAL mount AND
    # the Binder SDK). rpath-link lets ld follow libbinder.so's NEEDED siblings
    # (libbase/liblog/libcutils) in the same dir. Host g++ + host-built SDK share an
    # ABI, so this is a FULL link - no undefined-symbol relaxation needed.
    # shellcheck disable=SC2086
    if "${CXX}" -std=c++17 "${src}" -o "${WORK}/${name}" \
            ${cxxflags} \
            ${ldflags} -Wl,-rpath-link,"${SYSROOT}/usr/lib/binder" \
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

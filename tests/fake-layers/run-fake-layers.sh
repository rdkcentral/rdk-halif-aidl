#!/usr/bin/env bash
#/**
# * Copyright 2026 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
# * SPDX-License-Identifier: Apache-2.0
# */
#
# Layer-aggregation test + demo. Emulates the read-only-layer deployment model
# from vsi/filesystem/current/docs/directory_and_dynamic_linking_specification.md
# — independently-mounted /mw and /vendor layers, each exposing its modules
# through aggregation directories (lib/, ld.so.conf.d/) of symlinks, wired for
# dynamic linking via /etc/ld.so.conf.d/<layer>.conf + ldconfig.
#
# Unlike tests/fake-yocto (a single flat sysroot), this models the layered
# filesystem and proves a consumer resolves libraries ACROSS layers through the
# ld.so.conf.d aggregation — the MW layer provides the binder runtime + HAL
# interface libs, and a vendor-layer library links a HAL lib from the MW layer.
#
# No root/mount needed: layers are emulated in a work dir with absolute paths,
# and resolution is validated with ldconfig (registration) + ldd (cross-layer).
#
# Usage:
#   ./tests/fake-layers/run-fake-layers.sh          # run the test / demo
#   ./tests/fake-layers/run-fake-layers.sh --keep   # keep the work dir to inspect
set -uo pipefail

HERE="$(cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")" && pwd)"
REPO_ROOT="$(cd "${HERE}/../.." && pwd)"
KEEP=false; [ "${1:-}" = "--keep" ] && KEEP=true

PASS=0; FAIL=0
pass() { echo "  PASS  $1"; PASS=$((PASS + 1)); }
fail() { echo "  FAIL  $1"; FAIL=$((FAIL + 1)); }
skip() { echo "  SKIP  fake-layers — $1"; exit 0; }

command -v ldconfig >/dev/null 2>&1 || skip "ldconfig not available"
command -v ldd      >/dev/null 2>&1 || skip "ldd not available"
CXX="${CXX:-g++}"; command -v "${CXX}" >/dev/null 2>&1 || skip "${CXX} not available"

# ---- Build the MW payload: binder SDK + HAL interface libs ------------------
if [ ! -f "${REPO_ROOT}/out/target/.sdk_ready" ]; then
    echo "building binder SDK (build_binder.sh) ..."
    (cd "${REPO_ROOT}" && ./build_binder.sh) >/dev/null 2>&1 || fail "build_binder.sh failed"
fi
SDK_LIB="${REPO_ROOT}/out/target/lib/binder"
HALIF_LIB="${REPO_ROOT}/out/target/lib/halif"
if [ ! -f "${HALIF_LIB}/libcommon-vcurrent-cpp.so" ]; then
    echo "building a HAL interface lib (build_modules.sh common) ..."
    (cd "${REPO_ROOT}" && ./build_modules.sh common) >/dev/null 2>&1 || fail "build_modules.sh common failed"
fi
[ -d "${SDK_LIB}" ] && [ -f "${HALIF_LIB}/libcommon-vcurrent-cpp.so" ] || skip "binder SDK / HAL libs not built"
[ "${FAIL}" -eq 0 ] || exit 1

WORK="$(mktemp -d "${TMPDIR:-/tmp}/fake-layers.XXXXXX")"
cleanup() { [ "${KEEP}" = true ] || rm -rf "${WORK}"; }
trap cleanup EXIT
ROOT="${WORK}/rootfs"; MW="${ROOT}/mw"; VENDOR="${ROOT}/vendor"

# aggregate_layer <layer_dir> — build /<layer>/{lib,ld.so.conf.d} symlink
# aggregation from every /<layer>/<module>/{lib,ld.so.conf.d} present.
aggregate_layer() {
    local layer="$1" name; name="$(basename "${layer}")"
    mkdir -p "${layer}/lib" "${layer}/ld.so.conf.d"
    local mod
    for mod in "${layer}"/*/; do
        [ -d "${mod}lib" ] || continue
        local so
        for so in "${mod}lib/"*.so*; do
            [ -e "${so}" ] && ln -sf "${so}" "${layer}/lib/$(basename "${so}")"
        done
        local cf
        for cf in "${mod}ld.so.conf.d/"*.conf; do
            [ -e "${cf}" ] && ln -sf "${cf}" "${layer}/ld.so.conf.d/$(basename "${cf}")"
        done
    done
    # The layer's own aggregated linker config points at its lib/ dir; the
    # rootfs links /etc/ld.so.conf.d/<layer>.conf -> here.
    echo "${layer}/lib" > "${layer}/ld.so.conf.d/${name}.conf"
}

echo "=== staging /mw layer (binder + halif modules) ==="
# MW module: binder runtime
mkdir -p "${MW}/binder/lib" "${MW}/binder/ld.so.conf.d"
cp -a "${SDK_LIB}/." "${MW}/binder/lib/"
echo "${MW}/binder/lib" > "${MW}/binder/ld.so.conf.d/mw-binder.conf"
# MW module: HAL interface libs
mkdir -p "${MW}/halif/lib" "${MW}/halif/ld.so.conf.d"
cp -a "${HALIF_LIB}/." "${MW}/halif/lib/" 2>/dev/null || true
echo "${MW}/halif/lib" > "${MW}/halif/ld.so.conf.d/mw-halif.conf"
aggregate_layer "${MW}"

echo "=== staging /vendor layer (a module that links an MW-provided HAL lib) ==="
# A vendor library with a NEEDED on an MW HAL lib — the cross-layer dependency.
# Link against the MW layer's *aggregation* dir (${MW}/lib), not the module-
# private ${MW}/halif/lib — that is the path a real vendor consumes, so it also
# proves the aggregation symlinks are usable.
mkdir -p "${VENDOR}/demovendor/lib" "${VENDOR}/demovendor/ld.so.conf.d"
echo 'extern "C" int demovendor_probe(){ return 0; }' > "${WORK}/demovendor.cpp"
"${CXX}" -shared -fPIC "${WORK}/demovendor.cpp" \
    -L"${MW}/lib" -Wl,--no-as-needed -lcommon-vcurrent-cpp \
    -o "${VENDOR}/demovendor/lib/libdemovendor.so" 2>"${WORK}/vlink.err" \
    || { sed 's/^/    /' "${WORK}/vlink.err" >&2; fail "vendor lib failed to link an MW HAL lib via the aggregation dir"; }
echo "${VENDOR}/demovendor/lib" > "${VENDOR}/demovendor/ld.so.conf.d/vendor-demo.conf"
aggregate_layer "${VENDOR}"

# ---- Rootfs integration: /etc/ld.so.conf.d/<layer>.conf + ldconfig ---------
echo "=== wiring /etc/ld.so.conf.d + running ldconfig ==="
mkdir -p "${ROOT}/etc/ld.so.conf.d"
ln -sf "${MW}/ld.so.conf.d/mw.conf"         "${ROOT}/etc/ld.so.conf.d/mw.conf"
ln -sf "${VENDOR}/ld.so.conf.d/vendor.conf" "${ROOT}/etc/ld.so.conf.d/vendor.conf"
{ echo "include ${ROOT}/etc/ld.so.conf.d/*.conf"; } > "${ROOT}/etc/ld.so.conf"
CACHE="${ROOT}/etc/ld.so.cache"
ldconfig -f "${ROOT}/etc/ld.so.conf" -C "${CACHE}" -X 2>/dev/null || fail "ldconfig failed"

# ---- Assertions ------------------------------------------------------------
echo ""
echo "=== assertions ==="
# 1. Aggregation symlinks resolve to module files.
[ -L "${MW}/lib/libbinder.so" ] && [ -e "${MW}/lib/libbinder.so" ] \
    && pass "MW aggregation: /mw/lib/libbinder.so -> module" \
    || fail "MW aggregation symlink missing/broken"
[ -L "${MW}/lib/libcommon-vcurrent-cpp.so" ] && [ -e "${MW}/lib/libcommon-vcurrent-cpp.so" ] \
    && pass "MW aggregation: HAL lib symlinked" || fail "MW HAL aggregation symlink missing"

# 2. ldconfig registered the layer libs into the cache (the ld.so.conf.d path).
if ldconfig -p -C "${CACHE}" 2>/dev/null | grep -q 'libbinder.so' \
   && ldconfig -p -C "${CACHE}" 2>/dev/null | grep -q 'libcommon-vcurrent-cpp.so'; then
    pass "ldconfig registered binder + HAL libs via aggregated ld.so.conf.d"
else
    fail "ldconfig cache missing binder/HAL libs"
fi

# 3. Cross-layer resolution: the vendor lib's MW-provided dependency resolves
#    when the layer lib dirs are on the search path (nothing 'not found').
LDPATH="${MW}/lib:${VENDOR}/lib"
if LD_LIBRARY_PATH="${LDPATH}" ldd "${VENDOR}/demovendor/lib/libdemovendor.so" 2>/dev/null | grep -q 'libcommon-vcurrent-cpp.so => '; then
    if LD_LIBRARY_PATH="${LDPATH}" ldd "${VENDOR}/demovendor/lib/libdemovendor.so" 2>/dev/null | grep -q 'not found'; then
        fail "cross-layer: some deps 'not found' — see: ldd ${VENDOR}/demovendor/lib/libdemovendor.so"
    else
        pass "cross-layer: /vendor libdemovendor.so resolves libcommon from /mw via aggregation"
    fi
else
    fail "cross-layer: libdemovendor did not resolve the MW HAL lib"
fi

# ---- Demo: print the emulated layer tree -----------------------------------
echo ""
echo "=== emulated layer tree (demo) ==="
( cd "${ROOT}" && find mw vendor etc -maxdepth 3 \( -type l -o -name '*.so' -o -name '*.conf' \) 2>/dev/null \
    | sort | sed 's|^|  /|' | head -40 )

echo ""
echo "========================================="
echo "  fake-layers: ${PASS} passed, ${FAIL} failed"
[ "${KEEP}" = true ] && echo "  work dir kept: ${WORK}"
echo "========================================="
[ "${FAIL}" -eq 0 ]

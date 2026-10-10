#!/usr/bin/env bash
# tests/manifest/test_install.sh — build, install, and consume.
#
# Builds the two-commons fixture (common@0.1.0.0 and common@0.2.0.0 side by
# side), installs to a staging prefix, checks the versioned layout, then builds
# and links the consumer three ways: find_package(CONFIG), pkg-config, and an
# EXACT-version selection of both commons. common is built as both .so and
# .a (HALIF_LIBRARY_TYPE_common=BOTH); every other component as the default .so.
#
# Needs the Binder SDK:
#   BINDER_SDK_DIR          default <repo>/out/target   (lib/binder/libbinder.so)
#   BINDER_SDK_INCLUDE_DIR  default <repo>/out/build    (include/binder_sdk/binder/Binder.h)
# Build it with ./build_binder.sh, or point the variables at a staged sysroot.
set -euo pipefail

ROOT=$(cd "$(dirname "$0")/../.." && pwd)
WORK=${WORK:-$(mktemp -d)}
mkdir -p "$WORK"
STAGE="$WORK/stage"
SDK_ARGS=(
    -DBINDER_SDK_DIR="${BINDER_SDK_DIR:-$ROOT/out/target}"
    -DBINDER_SDK_INCLUDE_DIR="${BINDER_SDK_INCLUDE_DIR:-$ROOT/out/build}"
)
fail=0
check() { if [[ -e "$STAGE/$1" ]]; then echo "ok   $1"; else echo "MISSING $1"; fail=$((fail+1)); fi; }
check_absent() { if [[ ! -e "$STAGE/$1" ]]; then echo "ok   no $1"; else echo "UNEXPECTED $1"; fail=$((fail+1)); fi; }

echo "== build + install (two-commons fixture) =="
cmake -S "$ROOT" -B "$WORK/build" "${SDK_ARGS[@]}" \
    -DHALIF_VERSIONS_FILE="$ROOT/tests/manifest/fixtures/two-commons.yaml" \
    -DHALIF_LIBRARY_TYPE_common=BOTH
cmake --build "$WORK/build" -j "$(nproc 2>/dev/null || sysctl -n hw.ncpu)"
cmake --install "$WORK/build" --prefix "$STAGE" > /dev/null

echo "== installed layout: every path carries the version =="
for f in \
    lib/libcommon-v0.1.0.0-cpp.so lib/libcommon-v0.2.0.0-cpp.so \
    lib/libcommon-v0.1.0.0-cpp.a  lib/libcommon-v0.2.0.0-cpp.a \
    lib/libaudiodecoder-v0.1.0.0-cpp.so lib/libhdmicec-v0.1.0.0-cpp.so \
    include/rdk-halif-aidl/common/0.1.0.0/com/rdk/hal \
    include/rdk-halif-aidl/common/0.2.0.0/com/rdk/hal \
    include/rdk-halif-aidl/hdmicec/0.1.0.0/com/rdk/hal/hdmicec/IHdmiCec.h \
    src/rdk-halif-aidl/hdmicec/0.1.0.0/com/rdk/hal/hdmicec/IHdmiCec.aidl \
    src/rdk-halif-aidl/hdmicec/0.1.0.0/src \
    src/rdk-halif-aidl/hdmicec/0.1.0.0/interface.yaml \
    src/rdk-halif-aidl/hdmicec/0.1.0.0/.hash \
    lib/cmake/RdkHalifAidlCommon-0.1.0.0/RdkHalifAidlCommonConfig.cmake \
    lib/cmake/RdkHalifAidlCommon-0.1.0.0/RdkHalifAidlCommonConfigVersion.cmake \
    lib/cmake/RdkHalifAidlCommon-0.1.0.0/RdkHalifAidlCommonTargets.cmake \
    lib/cmake/RdkHalifAidlCommon-0.2.0.0/RdkHalifAidlCommonConfig.cmake \
    lib/cmake/RdkHalifAidlHdmicec-0.1.0.0/RdkHalifAidlHdmicecConfig.cmake \
    lib/cmake/rdk-halif-aidl/FindBinder.cmake \
    lib/cmake/rdk-halif-aidl/FindAndroidUtils.cmake \
    lib/pkgconfig/rdk-halif-aidl-common-0.1.0.0.pc \
    lib/pkgconfig/rdk-halif-aidl-common-0.2.0.0.pc \
    lib/pkgconfig/rdk-halif-aidl-hdmicec-0.1.0.0.pc
do check "$f"; done
echo "== library type is per component: hdmicec is .so only =="
check_absent lib/libhdmicec-v0.1.0.0-cpp.a

echo "== pkg-config resolves the module and its dependency =="
export PKG_CONFIG_PATH="$STAGE/lib/pkgconfig"
pkg-config --validate rdk-halif-aidl-hdmicec-0.1.0.0
pkg-config --exists --print-errors "rdk-halif-aidl-hdmicec-0.1.0.0 = 0.1.0.0"
pkg-config --cflags --libs rdk-halif-aidl-hdmicec-0.1.0.0 | grep -q -- "-lcommon-v0.2.0.0-cpp" \
    && echo "ok   Requires pulls common-v0.2.0.0" || { echo "FAIL pkg-config Requires"; fail=$((fail+1)); }

consumer() { # name, extra cmake args...
    local n=$1; shift
    rm -rf "${WORK:?}/${n:?}"
    cmake -S "$ROOT/tests/manifest/consumer" -B "$WORK/$n" -DCMAKE_PREFIX_PATH="$STAGE" "${SDK_ARGS[@]}" "$@" > "$WORK/$n.log" 2>&1 \
        && cmake --build "$WORK/$n" >> "$WORK/$n.log" 2>&1 \
        && echo "ok   consumer:$n" || { echo "FAIL consumer:$n"; tail -20 "$WORK/$n.log"; fail=$((fail+1)); }
}
echo "== consumers =="
consumer via_cmake     -DHALIF_CONSUMER_VIA=cmake
consumer via_pkgconfig -DHALIF_CONSUMER_VIA=pkgconfig
consumer via_versions  -DHALIF_CONSUMER_VIA=versions

echo
[[ $fail -eq 0 ]] && echo "all passed (work: $WORK)" || { echo "$fail failure(s) (work: $WORK)"; exit 1; }

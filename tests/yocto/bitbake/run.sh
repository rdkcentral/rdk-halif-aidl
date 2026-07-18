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
# run.sh - run REAL bitbake on the rdk-halif-aidl recipe, in docker, and ASSERT
# the packaging is correct.
#
# This is the only test that exercises the recipe's bitbake packaging for real
# (do_install, do_package, the PACKAGES/FILES split, -dbg). Everything else under
# tests/yocto/ci/ is an offline emulation and cannot see packaging bugs - this is
# the one that found the -dbg mis-split.
#
# It uses:
#   crops/poky            an image with bitbake + host tools
#   poky (kirkstone)      the base layers (cloned once, cached in .work/)
#   meta-halif-ci         a stub linux-binder (stages the prebuilt Binder SDK) and
#                         a bbappend that fetches the branch under test
#   the public sstate mirror, so the first build pulls prebuilt native/cross
#   artifacts where it can; the local toolchain is cached after the first run.
#
# PREREQS:
#   - docker
#   - the Binder SDK already built (./build_binder.sh -> out/)
#   - fs.inotify.max_user_instances high enough for bitbake (Yocto requirement);
#     this script raises it if it can (passwordless sudo), else it tells you the
#     one command to run.
#
# Usage:
#   ./tests/yocto/bitbake/run.sh                  # build + assert packaging
#   HALIF_BB_CLEAN=1 ./tests/yocto/bitbake/run.sh # force a clean re-fetch/rebuild
#   HALIF_BB_WORK=/big/disk ./tests/yocto/bitbake/run.sh   # relocate the build tree
#   HALIF_TEST_BRANCH=my-branch ./tests/yocto/bitbake/run.sh
#
set -uo pipefail

HARNESS_DIR="$(cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")" && pwd)"
REPO_ROOT="$(cd "${HARNESS_DIR}/../../.." && pwd)"
WORK="${HALIF_BB_WORK:-${HARNESS_DIR}/.work}"
IMAGE="${HALIF_BB_IMAGE:-crops/poky:ubuntu-22.04}"
BRANCH="${HALIF_TEST_BRANCH:-feature/661-yocto-per-component-recipes}"
TARGET="rdk-halif-aidl"
# Optional: build only a chosen subset instead of the full cohort. The planner
# adds each named component's dependency closure, so "hdmicec" pulls in common,
# and "audiodecoder:0.1.0.0 hdmicec:0.1.0.0" pulls in BOTH common versions.
COMPONENTS="${HALIF_BB_COMPONENTS:-}"

echo "========================================="
echo "  bitbake packaging test: ${TARGET}"
echo "  branch:     ${BRANCH}"
echo "  components: ${COMPONENTS:-<all released>}"
echo "  work dir:   ${WORK}"
echo "========================================="

fail() { echo ""; echo "❌ $1"; exit 1; }

command -v docker >/dev/null || fail "docker not found"
[ -d "${REPO_ROOT}/out/build/include/binder_sdk" ] && [ -d "${REPO_ROOT}/out/target/lib/binder" ] \
    || fail "Binder SDK not built - run ./build_binder.sh first"

# --- inotify: a documented Yocto requirement; bitbake's parser dies without it ---
NEED_INST=512
HAVE_INST="$(cat /proc/sys/fs/inotify/max_user_instances 2>/dev/null || echo 0)"
if [ "${HAVE_INST}" -lt "${NEED_INST}" ]; then
    if sudo -n sysctl -w "fs.inotify.max_user_instances=${NEED_INST}" >/dev/null 2>&1; then
        echo "[inotify] raised max_user_instances -> ${NEED_INST}"
    else
        fail "fs.inotify.max_user_instances is ${HAVE_INST} (bitbake needs >= ${NEED_INST}).
    Run:  sudo sysctl -w fs.inotify.max_user_instances=${NEED_INST}
    (persist in /etc/sysctl.d/60-inotify.conf). This is a standard Yocto prereq."
    fi
fi

mkdir -p "${WORK}"

# --- poky (kirkstone), cached across runs -----------------------------------
if [ ! -d "${WORK}/poky" ]; then
    echo "[poky] cloning kirkstone (once) ..."
    git clone -q -b kirkstone --depth 1 https://git.yoctoproject.org/poky "${WORK}/poky" \
        || fail "cloning poky"
fi

# --- tarball the prebuilt Binder SDK for the stub recipe --------------------
echo "[binder] packaging the prebuilt SDK for the stub recipe ..."
STAGE="$(mktemp -d)"; trap 'rm -rf "${STAGE}"' EXIT
mkdir -p "${STAGE}/binder-sdk/lib" "${STAGE}/binder-sdk/include"
cp -a "${REPO_ROOT}/out/target/lib/binder"        "${STAGE}/binder-sdk/lib/"
cp -a "${REPO_ROOT}/out/build/include/binder_sdk" "${STAGE}/binder-sdk/include/"
mkdir -p "${HARNESS_DIR}/meta-halif-ci/recipes-binder/linux-binder/files"
tar -C "${STAGE}" -czf \
    "${HARNESS_DIR}/meta-halif-ci/recipes-binder/linux-binder/files/binder-sdk.tar.gz" binder-sdk

CLEAN_STEP=""
[ "${HALIF_BB_CLEAN:-0}" = "1" ] && CLEAN_STEP="bitbake ${TARGET} -c cleanall 2>&1 | tail -1"

# --- bitbake, inside the container ------------------------------------------
echo "[bitbake] building + packaging ${TARGET} (first run builds the toolchain) ..."
docker run --rm \
    -v "${REPO_ROOT}":"${REPO_ROOT}" \
    -v "${WORK}":"${WORK}" \
    --workdir="${WORK}" \
    "${IMAGE}" --workdir="${WORK}" -- bash -c "
set -e
source poky/oe-init-build-env build >/dev/null
bitbake-layers add-layer '${REPO_ROOT}/tests/yocto/meta-rdk-halif-aidl' 2>/dev/null || true
bitbake-layers add-layer '${REPO_ROOT}/tests/yocto/meta-vendor' 2>/dev/null || true
bitbake-layers add-layer '${HARNESS_DIR}/meta-halif-ci' 2>/dev/null || true
if ! grep -q 'halif-ci-config' conf/local.conf; then
cat >> conf/local.conf <<EOF

# --- halif-ci-config ---
MACHINE = 'qemux86-64'
HALIF_TEST_BRANCH = '${BRANCH}'
BB_SIGNATURE_HANDLER = 'OEEquivHash'
BB_HASHSERVE = 'auto'
INSANE_SKIP:${TARGET} += 'arch'
EOF
fi
# Refresh the component selection every run (a subset build, or the default cohort
# when HALIF_BB_COMPONENTS is unset). Kept out of the guarded block so it can change
# between runs without re-seeding the whole config.
sed -i '/^HALIF_COMPONENTS /d' conf/local.conf
[ -n '${COMPONENTS}' ] && echo \"HALIF_COMPONENTS = '${COMPONENTS}'\" >> conf/local.conf
${CLEAN_STEP}
# -f: force do_package to actually run (not restore from sstate), so the
# packages-split tree exists for the assertions below.
bitbake ${TARGET} -c package -f
# Build a REAL consumer against the staged HAL. vendor-halif-example has
# DEPENDS = 'rdk-halif-aidl' and links -lhdmicec/-lcommon from the role mount, so
# this only succeeds if SYSROOT_DIRS staged the role mount into its sysroot. It is
# the regression guard for the staging path - a broken stage fails do_compile here.
bitbake vendor-halif-example
"
[ $? -eq 0 ] || fail "bitbake failed (HAL package or consumer link - see log above)"

# --- ASSERT the packaging on the host (packages-split is under WORK) --------
PS="$(find "${WORK}/build/tmp/work" -maxdepth 5 -type d -name packages-split 2>/dev/null | grep "/${TARGET}/" | head -1)"
[ -d "${PS}" ] || fail "packages-split not found"

echo ""
echo "[assert] inspecting ${PS}"
# runtime component packages: the .so NOT under a .debug dir (those belong to
# the single -dbg package, not to a runtime component).
libmount="$(find "${PS}" -type f -name 'lib*-v*-cpp.so' -not -path '*/.debug/*' 2>/dev/null | sed -E 's|.*/(rdk-halif-aidl-[a-z]+)/.*|\1|' | sort -u)"
ncomp="$(echo "${libmount}" | grep -c .)"
[ "${ncomp}" -ge 1 ] || fail "no runtime component packages produced"

errs=0
# total runtime libraries across all component packages. A component may ship
# SEVERAL versions (e.g. common at two versions in a multi-version build), so this
# can exceed the number of packages.
nlibs="$(find "${PS}" -type f -name 'lib*-v*-cpp.so' -not -path '*/.debug/*' 2>/dev/null | wc -l)"
# 1. each runtime package holds >=1 versioned .so, and every one is on a role mount
for pkg in ${libmount}; do
    so="$(find "${PS}/${pkg}" -name 'lib*-v*-cpp.so' -not -path '*/.debug/*' 2>/dev/null)"
    n="$(echo "${so}" | grep -c .)"
    [ "${n}" -ge 1 ] || { echo "  ❌ ${pkg}: no versioned library"; errs=$((errs+1)); }
    echo "${so}" | grep -qv '/vendor/rdk-halif-aidl/\|/mw/rdk-halif-aidl/' \
        && { echo "  ❌ ${pkg}: a .so is not on a role mount: ${so}"; errs=$((errs+1)); }
    # 2. matching -dev holds headers
    [ -n "$(find "${PS}/${pkg}-dev" -name '*.h' 2>/dev/null | head -1)" ] \
        || { echo "  ❌ ${pkg}-dev: no headers"; errs=$((errs+1)); }
done
# 3. exactly one -dbg, holding one debug library per runtime .so (none missing)
ndbg="$(find "${PS}" -maxdepth 1 -type d -name '*-dbg' | wc -l)"
[ "${ndbg}" = 1 ] || { echo "  ❌ ${ndbg} -dbg packages (expected 1 single ${TARGET}-dbg)"; errs=$((errs+1)); }
dbgn="$(find "${PS}/${TARGET}-dbg" -path '*/.debug/*' -name 'lib*-cpp.so' 2>/dev/null | wc -l)"
[ "${dbgn}" = "${nlibs}" ] || { echo "  ❌ ${TARGET}-dbg holds ${dbgn} debug files (expected ${nlibs} - one per runtime .so)"; errs=$((errs+1)); }

# 4. headers ship in the -dev packages, under the role mount's include/ subdir
devh="$(find "${PS}" -path '*-dev/*/rdk-halif-aidl/include/*' -name '*.h' 2>/dev/null | head -1)"
[ -n "${devh}" ] || { echo "  ❌ no -dev headers under a role mount's include/ (staging layout wrong)"; errs=$((errs+1)); }

# 5. THE STAGING PROOF: a real consumer (vendor-halif-example) linked against the
# staged HAL. If SYSROOT_DIRS did not stage the role mount, its do_compile could
# not have found -lhdmicec/-lcommon and bitbake above would have failed. Confirm
# the linked binary actually exists.
consumer="$(find "${WORK}/build/tmp/work" -type f -name vendor-halif-example -path '*/image/*' 2>/dev/null | head -1)"
[ -z "${consumer}" ] && consumer="$(find "${WORK}/build/tmp/work" -type f -name vendor-halif-example -perm -u+x 2>/dev/null | grep -v '\.debug' | head -1)"
[ -n "${consumer}" ] || { echo "  ❌ vendor-halif-example binary not found - consumer did not link against the staged HAL"; errs=$((errs+1)); }

echo ""
if [ "${errs}" -ne 0 ]; then
    fail "assertions failed (${errs})"
fi
echo "========================================="
echo "✅ ${TARGET} packages correctly (real bitbake do_package):"
echo "   ${ncomp} component packages holding ${nlibs} versioned libraries (on the role mount)"
echo "   + ${ncomp} -dev (headers) + one ${TARGET}-dbg holding all ${nlibs} debug libraries"
echo "✅ staging proven: vendor-halif-example linked against the staged role mount"
echo "   consumer binary: ${consumer}"
echo "   packages:        ${PS}"
echo "========================================="
exit 0

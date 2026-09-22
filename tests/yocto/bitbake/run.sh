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
#   poky (kirkstone)      the base layers (cloned once, cached in build/bitbake/)
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
#   ./tests/yocto/bitbake/run.sh                  # build + assert the full cohort
#   HALIF_BB_EACH=1 ./tests/yocto/bitbake/run.sh  # sweep: each component on its own
#   HALIF_BB_COMPONENTS="hdmicec" ./tests/yocto/bitbake/run.sh   # build a subset (+ closure)
#   HALIF_BB_CLEAN=1 ./tests/yocto/bitbake/run.sh # force a clean re-fetch/rebuild
#   HALIF_BB_WORK=/big/disk ./tests/yocto/bitbake/run.sh   # relocate the build tree
#   HALIF_TEST_BRANCH=my-branch ./tests/yocto/bitbake/run.sh
#
set -uo pipefail

HARNESS_DIR="$(cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")" && pwd)"
REPO_ROOT="$(cd "${HARNESS_DIR}/../../.." && pwd)"
# The bitbake work tree (poky + toolchain + build, ~12GB) lives under the repo's
# standard build/ dir - visible, gitignored, and NEVER committed. It is a build
# output, not source, so it must never sit among the interface sources. Override
# with HALIF_BB_WORK.
WORK="${HALIF_BB_WORK:-${REPO_ROOT}/build/bitbake}"
IMAGE="${HALIF_BB_IMAGE:-crops/poky:ubuntu-22.04}"
TARGET="rdk-halif-aidl"
# Test the branch + commit currently checked out - resolved from git, never
# hardcoded. bitbake fetches from the remote, so the commit must be PUSHED.
# Override with HALIF_TEST_BRANCH / HALIF_TEST_SRCREV.
BRANCH="${HALIF_TEST_BRANCH:-$(git -C "${REPO_ROOT}" rev-parse --abbrev-ref HEAD 2>/dev/null)}"
SRCREV="${HALIF_TEST_SRCREV:-$(git -C "${REPO_ROOT}" rev-parse HEAD 2>/dev/null)}"
# Optional: build only a chosen subset instead of the full cohort. The planner
# adds each named component's dependency closure, so "hdmicec" pulls in common,
# and "audiodecoder:0.1.0.0 hdmicec:0.1.0.0" pulls in BOTH common versions.
COMPONENTS="${HALIF_BB_COMPONENTS:-}"

echo "========================================="
echo "  bitbake packaging test: ${TARGET}"
echo "  branch:     ${BRANCH}"
echo "  commit:     ${SRCREV}"
echo "  components: ${COMPONENTS:-<all released>}"
echo "  work dir:   ${WORK}"
echo "========================================="

fail() { echo ""; echo "❌ $1"; exit 1; }
[ -n "${BRANCH}" ] && [ -n "${SRCREV}" ] || fail "could not resolve branch/commit from git (run inside the repo)"

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

# --- per-component sweep (HALIF_BB_EACH=1) ----------------------------------
# Build each component (with its dependency closure) through REAL bitbake, one at
# a time, to prove every component packages on its own - not just the full cohort.
# Only the rdk-halif-aidl recipe is cleaned between components (bitbake -c clean),
# so the cross toolchain, the Binder SDK and the downloads (the expensive, first-
# run parts) are built ONCE and reused. The first component is therefore slow (it
# builds the toolchain); the rest are quick.
if [ "${HALIF_BB_EACH:-0}" = "1" ]; then
    INC="${REPO_ROOT}/tests/yocto/meta-rdk-halif-aidl/recipes-halif/rdk-halif-aidl/halif-components.inc"
    ALL_COMPS="$(sed -nE 's/.*HALIF_COMPONENTS[^"]*"([^"]*)".*/\1/p' "${INC}")"
    [ -n "${ALL_COMPS}" ] || fail "could not read the component list from ${INC}"
    echo "[each] sweeping $(echo ${ALL_COMPS} | wc -w) components one at a time"
    echo "       (the FIRST build is long - it builds the cross toolchain once)"

    # The sweep body is written to a file (mounted via WORK) rather than passed as
    # an escaped bash -c string, so the container-side loop stays readable.
    SWEEP="${WORK}/each-sweep.sh"
    cat > "${SWEEP}" <<SWEEPEOF
source poky/oe-init-build-env build >/dev/null
bitbake-layers add-layer '${REPO_ROOT}/tests/yocto/meta-rdk-halif-aidl' 2>/dev/null || true
bitbake-layers add-layer '${HARNESS_DIR}/meta-halif-ci' 2>/dev/null || true
# Strip any prior halif-ci-config block and write a fresh one: BRANCH/SRCREV are
# resolved per run, so this must never be skipped - a stale block from an earlier
# run (different branch/commit) would silently build the wrong source.
sed -i '/# --- halif-ci-config ---/,\$d' conf/local.conf
cat >> conf/local.conf <<CONF

# --- halif-ci-config ---
MACHINE = 'qemux86-64'
# Fetch the branch + commit under test (run.sh resolves these from git). These
# pn- overrides keep the real recipe unmodified - no bbappend needed.
SRC_URI:pn-${TARGET} = 'git://github.com/rdkcentral/rdk-halif-aidl.git;protocol=https;branch=${BRANCH}'
SRCREV:pn-${TARGET} = '${SRCREV}'
BB_SIGNATURE_HANDLER = 'OEEquivHash'
BB_HASHSERVE = 'auto'
# 'arch': the interface libs carry no machine-specific code, so the ELF arch check
# is not meaningful here. (Ownership is handled in the recipe: do_install chowns to
# root, so there is no host-user contamination to skip.)
INSANE_SKIP:${TARGET} += 'arch'
CONF
fails=0; n=0; total=\$(echo ${ALL_COMPS} | wc -w)
for comp in ${ALL_COMPS}; do
    n=\$((n + 1))
    sed -i '/^HALIF_COMPONENTS /d' conf/local.conf
    echo "HALIF_COMPONENTS = '\${comp}'" >> conf/local.conf
    echo "[each] (\${n}/\${total}) build \${comp} + closure ..."
    if bitbake ${TARGET} -c package -f > "/tmp/each-\${comp}.log" 2>&1; then
        ps=\$(find tmp/work -maxdepth 5 -type d -name packages-split 2>/dev/null | grep '/${TARGET}/' | head -1)
        so=\$(find "\${ps}/${TARGET}-\${comp}" -name "lib\${comp}-v*-cpp.so" -not -path '*/.debug/*' 2>/dev/null | head -1)
        if [ -n "\${so}" ] && echo "\${so}" | grep -q '/vendor/rdk-halif-aidl/'; then
            echo "    ok: \${comp} -> \$(basename "\${so}") on the mount"
        else
            echo "    FAIL: \${comp} produced no lib\${comp}-*.so on the mount"; fails=\$((fails + 1))
        fi
    else
        echo "    FAIL: \${comp} bitbake do_package failed"; tail -6 "/tmp/each-\${comp}.log" | sed 's/^/        /'; fails=\$((fails + 1))
    fi
    # clean ONLY this recipe (keep toolchain / binder / downloads)
    bitbake ${TARGET} -c clean > /dev/null 2>&1 || true
done
echo ""
[ "\${fails}" -eq 0 ] && echo "SWEEP-OK all \${total} components package individually" && exit 0
echo "SWEEP-FAIL \${fails}/\${total} component(s) failed"; exit 1
SWEEPEOF

    docker run --rm \
        -v "${REPO_ROOT}":"${REPO_ROOT}" \
        -v "${WORK}":"${WORK}" \
        --workdir="${WORK}" \
        "${IMAGE}" --workdir="${WORK}" -- bash "${SWEEP}"
    [ $? -eq 0 ] || fail "per-component bitbake sweep failed (see log above)"
    echo "========================================="
    echo "✅ per-component sweep: every component packages on its own (real bitbake)"
    echo "========================================="
    exit 0
fi

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
bitbake-layers add-layer '${HARNESS_DIR}/meta-halif-ci' 2>/dev/null || true
# Strip any prior halif-ci-config block and write a fresh one: BRANCH/SRCREV are
# resolved per run, so this must never be skipped - a stale block from an earlier
# run (different branch/commit) would silently build the wrong source.
sed -i '/# --- halif-ci-config ---/,\$d' conf/local.conf
cat >> conf/local.conf <<EOF

# --- halif-ci-config ---
MACHINE = 'qemux86-64'
# Fetch the branch + commit under test (run.sh resolves these from git). These
# pn- overrides keep the real recipe unmodified - no bbappend needed.
SRC_URI:pn-${TARGET} = 'git://github.com/rdkcentral/rdk-halif-aidl.git;protocol=https;branch=${BRANCH}'
SRCREV:pn-${TARGET} = '${SRCREV}'
BB_SIGNATURE_HANDLER = 'OEEquivHash'
BB_HASHSERVE = 'auto'
# 'arch': the interface libs carry no machine-specific code, so the ELF arch check
# is not meaningful here. (Ownership is handled in the recipe: do_install chowns to
# root, so there is no host-user contamination to skip.)
INSANE_SKIP:${TARGET} += 'arch'
EOF
# Refresh the component selection every run (a subset build, or the default cohort
# when HALIF_BB_COMPONENTS is unset). Kept out of the guarded block so it can change
# between runs without re-seeding the whole config.
sed -i '/^HALIF_COMPONENTS /d' conf/local.conf
[ -n '${COMPONENTS}' ] && echo \"HALIF_COMPONENTS = '${COMPONENTS}'\" >> conf/local.conf
${CLEAN_STEP}
# -f: force do_package to actually run (not restore from sstate), so the
# packages-split tree exists for the assertions below.
bitbake ${TARGET} -c package -f
"
[ $? -eq 0 ] || fail "bitbake ${TARGET} -c package failed (see log above)"

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

echo ""
if [ "${errs}" -ne 0 ]; then
    fail "assertions failed (${errs})"
fi
echo "========================================="
echo "✅ ${TARGET} packages correctly (real bitbake do_package):"
echo "   ${ncomp} component packages holding ${nlibs} versioned libraries (on the role mount)"
echo "   + ${ncomp} -dev (headers) + one ${TARGET}-dbg holding all ${nlibs} debug libraries"
echo "   packages:        ${PS}"
echo "========================================="
exit 0

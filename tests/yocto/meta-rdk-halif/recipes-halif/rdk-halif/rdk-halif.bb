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

# rdk-halif - build a chosen set of RDK HAL AIDL interface libraries from their
# committed, pre-generated C++, and split the output into one package per
# component (rdk-halif-<comp>). No AIDL / codegen toolchain required.
#
# A build configuration controls this with variables (typically injected by a
# generated include, see scripts/gen_team_conf.py):
#   HALIF_COMPONENTS        components to build   (default: all, from the .inc)
#   HALIF_VERSION_<comp>    version per component (default: the latest snapshot)
#   HALIF_ROLE              vendor | mw           (labels who is building)
#   HALIF_LIBDIR/INCDIR     install destinations  (default: ${libdir}/halif etc.)
#
# The offline contract test tests/yocto/run-yocto-roles.sh exercises the same
# build loop without BitBake. This is reference material - adapt SRCREV and the
# toolchain to your project.

SUMMARY = "RDK HAL AIDL interface libraries"
HOMEPAGE = "https://github.com/rdkcentral/rdk-halif-aidl"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"

SRC_URI = "git://github.com/rdkcentral/rdk-halif-aidl.git;protocol=https;branch=develop"
SRCREV = "${AUTOREV}"
S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

# The Binder SDK (libbinder/libutils + headers) is provided by the linux-binder
# recipe and staged into the recipe sysroot.
DEPENDS = "linux-binder"

# Default component set (every released component). A build configuration subsets
# HALIF_COMPONENTS and pins HALIF_VERSION_<comp> in its own include.
require ${THISDIR}/halif-components.inc

HALIF_ROLE ??= "vendor"
HALIF_LIBDIR ??= "${libdir}/halif"
HALIF_INCDIR ??= "${includedir}/halif"

# comp[:ver] arguments for scripts/halif_plan.py, assembled from the selected
# components and any per-component version overrides.
HALIF_PLAN_ARGS = "${@ ' '.join((c + ':' + d.getVar('HALIF_VERSION_' + c)) if d.getVar('HALIF_VERSION_' + c) else c for c in (d.getVar('HALIF_COMPONENTS') or '').split()) }"

inherit cmake

# One CMake project per component, so skip the single-project configure and drive
# cmake per component in do_compile (reusing the cmake class' cross toolchain).
do_configure[noexec] = "1"

do_compile() {
    cmake_do_generate_toolchain_file

    # Resolve the topological build order (dependencies first).
    "${S}/scripts/halif_plan.py" ${HALIF_PLAN_ARGS} > "${B}/plan.txt" \
        || bbfatal "halif_plan.py failed to resolve a build order"

    # Sibling libs/headers built earlier in the plan are staged here so later
    # components link them; the Binder SDK comes from the recipe sysroot.
    install -d "${B}/staged/lib/halif" "${B}/staged/include/halif"

    while read comp ver; do
        bbnote "rdk-halif: building ${comp}@${ver}"
        cmake -S "${S}/${comp}/${ver}" -B "${B}/obj/${comp}" \
            -DCMAKE_TOOLCHAIN_FILE="${WORKDIR}/toolchain.cmake" \
            -DBINDER_SDK_DIR="${STAGING_DIR_HOST}${prefix}" \
            -DBINDER_SDK_INCLUDE_DIR="${STAGING_DIR_HOST}${prefix}" \
            -DHALIF_LIB_DIR="${B}/staged/lib/halif" \
            -DHALIF_INCLUDE_DIR="${B}/staged/include/halif"
        cmake --build "${B}/obj/${comp}"
        install -m 0755 "${B}/obj/${comp}/lib${comp}-v${ver}-cpp.so" "${B}/staged/lib/halif/"
        install -d "${B}/staged/include/halif/${comp}/${ver}"
        cp -R "${S}/${comp}/${ver}/include" "${B}/staged/include/halif/${comp}/${ver}/"
    done < "${B}/plan.txt"
}

do_install() {
    install -d "${D}${HALIF_LIBDIR}" "${D}${HALIF_INCDIR}"
    cp -a "${B}/staged/lib/halif/." "${D}${HALIF_LIBDIR}/"
    cp -a "${B}/staged/include/halif/." "${D}${HALIF_INCDIR}/"
}

# Split the output into one package per component: rdk-halif-<comp> (the .so) and
# rdk-halif-<comp>-dev (its headers). Built at parse time from HALIF_COMPONENTS.
python () {
    comps = (d.getVar('HALIF_COMPONENTS') or '').split()
    libdir = d.getVar('HALIF_LIBDIR')
    incdir = d.getVar('HALIF_INCDIR')
    pkgs = []
    for c in comps:
        main, dev = 'rdk-halif-' + c, 'rdk-halif-%s-dev' % c
        pkgs += [dev, main]
        d.setVar('SUMMARY:' + main, 'RDK HAL AIDL interface library: %s' % c)
        d.setVar('FILES:' + main, '%s/lib%s-v*-cpp.so' % (libdir, c))
        d.setVar('FILES:' + dev, '%s/%s' % (incdir, c))
        d.setVar('INSANE_SKIP:' + main, 'dev-so')
    d.setVar('PACKAGES', ' '.join(pkgs))
}

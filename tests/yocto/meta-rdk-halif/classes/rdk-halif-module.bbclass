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

# rdk-halif-module.bbclass - shared build logic for one released RDK HAL AIDL
# interface snapshot. A generated recipe sets HALIF_MODULE + HALIF_VERSION and
# inherits this class; DEPENDS is generated from the sibling libraries the
# snapshot links. A parent build configuration (meta-vendor / meta-mw) sets
# HALIF_ROLE, selects component versions via PREFERRED_VERSION_rdk-halif-<comp>,
# and may override the install destinations below. This mirrors, task for task,
# the contract verified offline by tests/yocto/run-yocto-per-component.sh - no
# codegen, no AIDL toolchain, no .sdk_ready marker.

LICENSE ?= "Apache-2.0"
LIC_FILES_CHKSUM ?= "file://LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"
HOMEPAGE ?= "https://github.com/rdkcentral/rdk-halif-aidl"

# One shared checkout of rdk-halif-aidl; each recipe builds its own snapshot
# subdir. Pin SRCREV to the released tag's commit for reproducible builds.
SRC_URI ?= "git://github.com/rdkcentral/rdk-halif-aidl.git;protocol=https;branch=develop"
SRCREV ?= "${AUTOREV}"
S = "${WORKDIR}/git"

# The Binder SDK (libbinder/libutils + headers) is provided by the linux-binder
# recipe and staged flat into the recipe sysroot.
DEPENDS:prepend = "linux-binder "

inherit cmake

# ---------------------------------------------------------------------------
# Consumer picture and destinations (a parent layer / build config sets these).
#
# HALIF_ROLE names who is building, so it is clear who owns what: the "vendor"
# layer that implements the HAL, or the "mw" middleware that calls it. It is a
# label; what actually differs is the destination, so a parent layer overrides
# the two paths below to match its partition / sysroot layout.
# ---------------------------------------------------------------------------
HALIF_ROLE ??= "vendor"

# Install + stage destination for this component's interface library and its
# committed headers. Dependents find headers under
# ${HALIF_INCDIR}/<comp>/<ver>/include and the .so under ${HALIF_LIBDIR}.
HALIF_LIBDIR ??= "${libdir}/halif"
HALIF_INCDIR ??= "${includedir}/halif"

# Build the snapshot's self-contained CMakeLists - it compiles the committed,
# pre-generated C++; the top-level (codegen) CMake is not used.
OECMAKE_SOURCEPATH = "${S}/${HALIF_MODULE}/${HALIF_VERSION}"
B = "${WORKDIR}/build"

EXTRA_OECMAKE = " \
    -DBINDER_SDK_DIR=${STAGING_DIR_HOST}${prefix} \
    -DBINDER_SDK_INCLUDE_DIR=${STAGING_DIR_HOST}${prefix} \
    -DHALIF_LIB_DIR=${STAGING_DIR_HOST}${HALIF_LIBDIR} \
    -DHALIF_INCLUDE_DIR=${STAGING_DIR_HOST}${HALIF_INCDIR} \
"

# Install the built interface library and the snapshot's committed headers to
# the configured destinations. This overrides the cmake class' do_install so the
# .so destination is decoupled from the module CMakeLists' hard-coded lib/halif.
do_install() {
    install -d ${D}${HALIF_LIBDIR}
    install -m 0755 ${B}/lib${HALIF_MODULE}-v${HALIF_VERSION}-cpp.so ${D}${HALIF_LIBDIR}/
    install -d ${D}${HALIF_INCDIR}/${HALIF_MODULE}/${HALIF_VERSION}
    cp -R ${S}/${HALIF_MODULE}/${HALIF_VERSION}/include \
          ${D}${HALIF_INCDIR}/${HALIF_MODULE}/${HALIF_VERSION}/
}

# Interface libraries are linked by exact name and loaded at runtime; the .so
# lives in the main package (there is no soname/dev split). Headers are staged
# so dependent HAL recipes resolve them at build time.
FILES:${PN} += "${HALIF_LIBDIR}/*.so"
FILES:${PN}-dev += "${HALIF_INCDIR}"
INSANE_SKIP:${PN} += "dev-so"
SYSROOT_DIRS += "${HALIF_LIBDIR} ${HALIF_INCDIR}"

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
# inherits this class; DEPENDS is generated from the snapshot's interface.yaml
# `imports:`. This mirrors, task for task, the contract verified offline by
# tests/fake-yocto/run-fake-yocto-per-component.sh - no codegen, no AIDL
# toolchain, no .sdk_ready marker.

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

# Build the snapshot's self-contained CMakeLists directly - it compiles the
# committed, pre-generated C++; the top-level CMake (codegen path) is not used.
OECMAKE_SOURCEPATH = "${S}/${HALIF_MODULE}/${HALIF_VERSION}"
B = "${WORKDIR}/build"

# Flat staged SDK: headers and libraries share one prefix. HALIF_* point at the
# halif staging layout that dependency recipes populate (do_install, below).
EXTRA_OECMAKE = " \
    -DBINDER_SDK_DIR=${STAGING_DIR_HOST}${prefix} \
    -DBINDER_SDK_INCLUDE_DIR=${STAGING_DIR_HOST}${prefix} \
    -DHALIF_LIB_DIR=${STAGING_LIBDIR}/halif \
    -DHALIF_INCLUDE_DIR=${STAGING_INCDIR}/halif \
"

# The module install() rule stages only the .so (into ${libdir}/halif). Stage
# the snapshot's committed headers too, preserving the <comp>/<ver>/include
# layout dependents resolve via ${HALIF_INCLUDE_DIR}/<comp>/<ver>/include.
do_install:append() {
    install -d ${D}${includedir}/halif/${HALIF_MODULE}/${HALIF_VERSION}
    cp -r ${S}/${HALIF_MODULE}/${HALIF_VERSION}/include \
          ${D}${includedir}/halif/${HALIF_MODULE}/${HALIF_VERSION}/
}

# Interface libraries are linked by exact name and loaded at runtime; the .so
# lives in the main package (there is no soname/dev split).
FILES:${PN} += "${libdir}/halif/*.so"
FILES:${PN}-dev += "${includedir}/halif/${HALIF_MODULE}/${HALIF_VERSION}"
INSANE_SKIP:${PN} += "dev-so"

# Stage lib + headers into the sysroot so dependent HAL recipes resolve them at
# build time (both are under the default SYSROOT_DIRS prefixes; listed for
# clarity).
SYSROOT_DIRS += "${libdir}/halif ${includedir}/halif"

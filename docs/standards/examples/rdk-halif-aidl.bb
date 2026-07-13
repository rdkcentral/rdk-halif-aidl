# SUPERSEDED - for production Yocto builds use the meta-rdk-halif layer.
#
#   BBLAYERS += "${TOPDIR}/../rdk-halif-aidl/meta-rdk-halif"
#   IMAGE_INSTALL:append = " rdk-halif-<component>"
#
# This single recipe drives the TOP-LEVEL CMakeLists.txt, which runs the AIDL
# codegen toolchain (aidl_ops.py) at configure time and therefore requires the
# linux_binder_idl source and Python - it is the developer / integrated build,
# NOT a no-toolchain production path (#661). The per-component meta-rdk-halif
# recipes build the committed C++ from each self-contained
# <module>/<version>/CMakeLists.txt with no toolchain, and derive inter-component
# DEPENDS from interface.yaml. See docs/standards/build_integration.md.
#
# Kept only as a reference for a developer superbuild that already has the
# toolchain present.

SUMMARY = "RDK HAL AIDL interface libraries (Polaris HAL)"
HOMEPAGE = "https://github.com/rdkcentral/rdk-halif-aidl"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"

SRC_URI = "git://github.com/rdkcentral/rdk-halif-aidl.git;protocol=https;branch=develop"
# For reproducible builds, pin to a released tag. SRCREV must be a git commit
# SHA (a tag *name* is not a valid SRCREV) — reference the tag in SRC_URI and
# set SRCREV to that tag's commit, e.g.:
#   SRC_URI = "git://github.com/rdkcentral/rdk-halif-aidl.git;protocol=https;tag=0.21.0"
#   SRCREV  = "<commit-sha-of-tag-0.21.0>"
SRCREV = "${AUTOREV}"
PV = "1.0+git${SRCPV}"
S = "${WORKDIR}/git"

# The Binder SDK (libbinder/libutils + headers) is provided by the linux-binder
# recipe and staged into the recipe sysroot.
DEPENDS = "linux-binder"

inherit cmake

# Let the cmake class run configure / compile / install — do not override the
# tasks. The install() rules place the libraries under <prefix>/lib/halif, so
# the class' install step puts them in the right place.
#
# A staged SDK is flat, so headers and libraries share one prefix — point both
# BINDER_SDK_DIR and BINDER_SDK_INCLUDE_DIR at it.
EXTRA_OECMAKE = " \
    -DINTERFACE_TARGET=all \
    -DBINDER_SDK_DIR=${STAGING_DIR}${prefix} \
    -DBINDER_SDK_INCLUDE_DIR=${STAGING_DIR}${prefix} \
"

FILES:${PN} += "${libdir}/halif/*.so"

# REFERENCE BitBake recipe for the RDK HAL AIDL interface libraries.
#
# This is a copy-me template, NOT a recipe consumed by this repository. Drop it
# into your meta-layer, pin SRCREV/branch to a released tag, and adjust as
# needed. It builds the committed, pre-generated C++ via direct CMake — no AIDL
# compiler or Python is required on the build host (see
# docs/standards/build_integration.md for the full contract).

SUMMARY = "RDK HAL AIDL interface libraries (Polaris HAL)"
HOMEPAGE = "https://github.com/rdkcentral/rdk-halif-aidl"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"

SRC_URI = "git://github.com/rdkcentral/rdk-halif-aidl.git;protocol=https;branch=develop"
# Pin to a released tag for reproducible builds, e.g.:
#   SRCREV = "0.21.0"
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

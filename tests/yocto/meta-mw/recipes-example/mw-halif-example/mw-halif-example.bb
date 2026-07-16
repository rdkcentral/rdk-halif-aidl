# EXAMPLE - a middleware component that CONSUMES an RDK HAL AIDL interface (the
# client side: it looks up the service a vendor implementation registered and
# calls it).
#
# Reference material: copy the SHAPE, not the file. Note this is nearly identical
# to meta-vendor/recipes-example/vendor-halif-example.bb - client and server link
# the SAME interface library. The role difference is what the code does with it,
# not how it builds.
#
#
# WHAT THE HAL STAGES INTO YOUR SYSROOT  (given DEPENDS = "rdk-halif-aidl")
# -----------------------------------------------------------------------------
#   ${STAGING_LIBDIR}/rdk-halif-aidl/lib<comp>-v<ver>-cpp.so
#   ${STAGING_INCDIR}/rdk-halif-aidl/<comp>/<ver>/include/com/rdk/hal/...
#
#   The version is in the library NAME (and SONAME) -> link an exact version:
#       -lavclock-v0.2.0.1-cpp
#   Headers have no version in the filename -> the version is in the PATH:
#       -I${STAGING_INCDIR}/rdk-halif-aidl/avclock/0.2.0.1/include
#       #include <com/rdk/hal/avclock/IAVClock.h>
#
#   Everything is named -aidl so it never collides with the legacy C HAL
#   (rdk-halif-*) on a rootfs carrying both during migration.
#
#   Client/server compatibility is a RUNTIME concern as well as a link-time one:
#   gate newer calls on getInterfaceVersion() rather than assuming the server is
#   as new as the headers you compiled against. See docs/standards/client-patterns.md.

SUMMARY = "EXAMPLE middleware client of an RDK HAL AIDL interface"
HOMEPAGE = "https://github.com/rdkcentral/rdk-halif-aidl"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

SRC_URI = "file://mw-halif-example.cpp"
S = "${WORKDIR}"

# Build-time: stages the interface libraries + their headers into our sysroot.
DEPENDS = "rdk-halif-aidl linux-binder"

# Runtime: the interface libraries this binary loads.
RDEPENDS:${PN} = "rdk-halif-aidl-avclock rdk-halif-aidl-common"

# The versions you build against. Keep these in step with the cohort the
# rdk-halif-aidl recipe built - the .so you link must be the one on the rootfs.
HALIF_AVCLOCK_VER ?= "0.2.0.1"
HALIF_COMMON_VER  ?= "0.2.0.0"

CXXFLAGS += "-I${STAGING_INCDIR}/rdk-halif-aidl/avclock/${HALIF_AVCLOCK_VER}/include \
             -I${STAGING_INCDIR}/rdk-halif-aidl/common/${HALIF_COMMON_VER}/include"

LDFLAGS += "-L${STAGING_LIBDIR}/rdk-halif-aidl \
            -lavclock-v${HALIF_AVCLOCK_VER}-cpp \
            -lcommon-v${HALIF_COMMON_VER}-cpp \
            -lbinder -lutils"

do_compile() {
    ${CXX} ${CXXFLAGS} ${LDFLAGS} \
        "${S}/mw-halif-example.cpp" -o "${B}/mw-halif-example"
}

do_install() {
    install -d "${D}${bindir}"
    install -m 0755 "${B}/mw-halif-example" "${D}${bindir}/"
}

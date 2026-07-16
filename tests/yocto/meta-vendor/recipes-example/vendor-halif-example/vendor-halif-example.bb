# EXAMPLE - a vendor component that IMPLEMENTS an RDK HAL AIDL interface (the
# server side: it registers a service that middleware calls).
#
# Reference material: copy the SHAPE, not the file. Consuming the HAL needs only
# three things - a build dependency, the include/link flags, and a runtime
# dependency on the packages you actually use.
#
#
# WHAT THE HAL STAGES INTO YOUR SYSROOT  (given DEPENDS = "rdk-halif-aidl")
# -----------------------------------------------------------------------------
#   ${STAGING_LIBDIR}/rdk-halif-aidl/lib<comp>-v<ver>-cpp.so
#   ${STAGING_INCDIR}/rdk-halif-aidl/<comp>/<ver>/include/com/rdk/hal/...
#
#   e.g. for hdmicec@0.1.0.0, which imports common@0.2.0.0:
#     ${STAGING_LIBDIR}/rdk-halif-aidl/libhdmicec-v0.1.0.0-cpp.so
#     ${STAGING_LIBDIR}/rdk-halif-aidl/libcommon-v0.2.0.0-cpp.so
#     ${STAGING_INCDIR}/rdk-halif-aidl/hdmicec/0.1.0.0/include/com/rdk/hal/hdmicec/
#     ${STAGING_INCDIR}/rdk-halif-aidl/common/0.2.0.0/include/com/rdk/hal/
#
#   The version is in the library NAME (and its SONAME), so libraries for several
#   versions sit side by side in one flat directory and you link an exact one:
#       -lhdmicec-v0.1.0.0-cpp
#   Headers have no version in the filename (BnPropertyValue.h is identical in
#   every version), so for headers the version is in the PATH instead:
#       -I${STAGING_INCDIR}/rdk-halif-aidl/hdmicec/0.1.0.0/include
#   ...after which you include by the AIDL namespace:
#       #include <com/rdk/hal/hdmicec/IHdmiCec.h>
#
#   Everything is named -aidl so it never collides with the legacy C HAL
#   (rdk-halif-*) on a rootfs carrying both during migration.

SUMMARY = "EXAMPLE vendor implementation of an RDK HAL AIDL interface"
HOMEPAGE = "https://github.com/rdkcentral/rdk-halif-aidl"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

SRC_URI = "file://vendor-halif-example.cpp"
S = "${WORKDIR}"

# Build-time: stages the interface libraries + their headers into our sysroot.
# linux-binder provides libbinder/libutils, which the interface libraries link.
DEPENDS = "rdk-halif-aidl linux-binder"

# Runtime: the interface libraries this binary loads. One package per component -
# name only what you use, so the image carries only that.
RDEPENDS:${PN} = "rdk-halif-aidl-hdmicec rdk-halif-aidl-common"

# The versions you build against. Keep these in step with the cohort the
# rdk-halif-aidl recipe built (its HALIF_VERSIONS_FILE, default
# versions_released.yaml) - the .so you link must be the one on the rootfs.
HALIF_HDMICEC_VER ?= "0.1.0.0"
HALIF_COMMON_VER  ?= "0.2.0.0"

CXXFLAGS += "-I${STAGING_INCDIR}/rdk-halif-aidl/hdmicec/${HALIF_HDMICEC_VER}/include \
             -I${STAGING_INCDIR}/rdk-halif-aidl/common/${HALIF_COMMON_VER}/include"

LDFLAGS += "-L${STAGING_LIBDIR}/rdk-halif-aidl \
            -lhdmicec-v${HALIF_HDMICEC_VER}-cpp \
            -lcommon-v${HALIF_COMMON_VER}-cpp \
            -lbinder -lutils"

do_compile() {
    ${CXX} ${CXXFLAGS} ${LDFLAGS} \
        "${S}/vendor-halif-example.cpp" -o "${B}/vendor-halif-example"
}

do_install() {
    install -d "${D}${bindir}"
    install -m 0755 "${B}/vendor-halif-example" "${D}${bindir}/"
}

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
#   Everything is rooted at the ROLE MOUNT the HAL was built for - vendor here, so
#   /vendor/rdk-halif-aidl. Staging and target share this mount; vendor and mw stage
#   to different mounts, so their differing library versions never share a path.
#
#   ${STAGING_DIR_HOST}/vendor/rdk-halif-aidl/lib<comp>-v<ver>-cpp.so
#   ${STAGING_DIR_HOST}/vendor/rdk-halif-aidl/include/<comp>/<ver>/include/com/rdk/hal/...
#
#   e.g. for hdmicec@0.1.0.0, which imports common@0.2.0.0:
#     ${STAGING_DIR_HOST}/vendor/rdk-halif-aidl/libhdmicec-v0.1.0.0-cpp.so
#     ${STAGING_DIR_HOST}/vendor/rdk-halif-aidl/libcommon-v0.2.0.0-cpp.so
#     ${STAGING_DIR_HOST}/vendor/rdk-halif-aidl/include/hdmicec/0.1.0.0/include/com/rdk/hal/hdmicec/
#     ${STAGING_DIR_HOST}/vendor/rdk-halif-aidl/include/common/0.2.0.0/include/com/rdk/hal/
#
#   The version is in the library NAME (and its SONAME), so libraries for several
#   versions sit side by side in one flat directory and you link an exact one:
#       -lhdmicec-v0.1.0.0-cpp
#   Headers have no version in the filename (BnPropertyValue.h is identical in
#   every version), so for headers the version is in the PATH instead:
#       -I.../vendor/rdk-halif-aidl/include/hdmicec/0.1.0.0/include
#   ...after which you include by the AIDL namespace:
#       #include <com/rdk/hal/hdmicec/IHdmiCec.h>
#
#   Everything is named -aidl so it never collides with the legacy C HAL
#   (rdk-halif-*) on a rootfs carrying both during migration.
#
#
# WHAT REACHES THE TARGET  (given RDEPENDS / IMAGE_INSTALL)
# -----------------------------------------------------------------------------
#   The device rootfs carries libraries only, on the SAME role mount:
#
#     /vendor/rdk-halif-aidl/
#     |-- libhdmicec-v0.1.0.0-cpp.so     <- pkg rdk-halif-aidl-hdmicec
#     `-- libcommon-v0.2.0.0-cpp.so      <- pkg rdk-halif-aidl-common
#     /usr/bin/
#     `-- vendor-halif-example           <- this recipe
#
#   Libraries ONLY - no headers on the target. Headers live in the include/ subdir
#   of the mount and are packaged into rdk-halif-aidl-<comp>-dev, a build-time
#   (staging) package that is not installed into a normal image. That is why
#   RDEPENDS below names the runtime packages and never the -dev ones.
#
#   The libraries carry no RPATH, so the loader resolves libbinder/libutils from
#   the image's standard paths - keep them installed.

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

# The mount point this consumer builds against. It must match the one the
# rdk-halif-aidl recipe was built with (/vendor here), because that mount is what
# the HAL stages into our sysroot.
HALIF_MOUNT_POINT ?= "/vendor"
HALIF_STAGED       = "${STAGING_DIR_HOST}${HALIF_MOUNT_POINT}/rdk-halif-aidl"

# The Binder SDK, staged by linux-binder at NON-standard subdirs (headers under
# include/binder_sdk, libs under lib/binder). Every HAL consumer needs it: the
# generated Bn/Bp interface headers #include <binder/IInterface.h>, and the
# interface libraries link libbinder/libutils.
BINDER_INCDIR = "${STAGING_INCDIR}/binder_sdk"
BINDER_LIBDIR = "${STAGING_LIBDIR}/binder"

CXXFLAGS += "-I${HALIF_STAGED}/include/hdmicec/${HALIF_HDMICEC_VER}/include \
             -I${HALIF_STAGED}/include/common/${HALIF_COMMON_VER}/include \
             -I${BINDER_INCDIR}"

LDFLAGS += "-L${HALIF_STAGED} \
            -lhdmicec-v${HALIF_HDMICEC_VER}-cpp \
            -lcommon-v${HALIF_COMMON_VER}-cpp \
            -L${BINDER_LIBDIR} -lbinder -lutils"

do_compile() {
    # Source BEFORE the libraries: the default LDFLAGS carry -Wl,--as-needed, which
    # drops any -l whose symbols are not yet referenced. The translation unit must
    # appear first so its references keep the interface + binder libraries linked.
    # Library order is dependents-before-dependencies (hdmicec -> common -> binder/utils).
    ${CXX} ${CXXFLAGS} \
        "${S}/vendor-halif-example.cpp" \
        ${LDFLAGS} -o "${B}/vendor-halif-example"
}

do_install() {
    install -d "${D}${bindir}"
    install -m 0755 "${B}/vendor-halif-example" "${D}${bindir}/"
}

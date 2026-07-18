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
#   Everything is rooted at the ROLE MOUNT the HAL was built for - mw here, so
#   /mw/rdk-halif-aidl. Staging and target share this mount; vendor and mw stage to
#   different mounts, so their differing library versions never share a path.
#
#   ${STAGING_DIR_HOST}/mw/rdk-halif-aidl/lib<comp>-v<ver>-cpp.so
#   ${STAGING_DIR_HOST}/mw/rdk-halif-aidl/include/<comp>/<ver>/include/com/rdk/hal/...
#
#   The version is in the library NAME (and SONAME) -> link an exact version:
#       -lavclock-v0.2.0.1-cpp
#   Headers have no version in the filename -> the version is in the PATH:
#       -I.../mw/rdk-halif-aidl/include/avclock/0.2.0.1/include
#       #include <com/rdk/hal/avclock/IAVClock.h>
#
#   Everything is named -aidl so it never collides with the legacy C HAL
#   (rdk-halif-*) on a rootfs carrying both during migration.
#
#
# WHAT REACHES THE TARGET  (given RDEPENDS / IMAGE_INSTALL)
# -----------------------------------------------------------------------------
#   The device rootfs carries libraries only, on the SAME role mount:
#
#     /mw/rdk-halif-aidl/
#     |-- libavclock-v0.2.0.1-cpp.so     <- pkg rdk-halif-aidl-avclock
#     `-- libcommon-v0.2.0.0-cpp.so      <- pkg rdk-halif-aidl-common
#     /usr/bin/
#     `-- mw-halif-example               <- this recipe
#
#   Libraries ONLY - no headers on the target. Headers live in the include/ subdir
#   of the mount and are packaged into rdk-halif-aidl-<comp>-dev, a build-time
#   (staging) package that is not installed into a normal image. That is why
#   RDEPENDS below names the runtime packages and never the -dev ones.
#
#   The libraries carry no RPATH, so the loader resolves libbinder/libutils from
#   the image's standard paths - keep them installed. The vendor implementation
#   must also be on the rootfs and running, or the service lookup below returns
#   null.
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

# The mount point this consumer builds against. It must match the one the
# rdk-halif-aidl recipe was built with (/mw here), because that mount is what the
# HAL stages into our sysroot.
HALIF_MOUNT_POINT ?= "/mw"
HALIF_STAGED       = "${STAGING_DIR_HOST}${HALIF_MOUNT_POINT}/rdk-halif-aidl"

# The Binder SDK, staged by linux-binder at NON-standard subdirs (headers under
# include/binder_sdk, libs under lib/binder). Every HAL consumer needs it: the
# generated Bn/Bp interface headers #include <binder/IInterface.h>, and the
# interface libraries link libbinder/libutils.
BINDER_INCDIR = "${STAGING_INCDIR}/binder_sdk"
BINDER_LIBDIR = "${STAGING_LIBDIR}/binder"

CXXFLAGS += "-I${HALIF_STAGED}/include/avclock/${HALIF_AVCLOCK_VER}/include \
             -I${HALIF_STAGED}/include/common/${HALIF_COMMON_VER}/include \
             -I${BINDER_INCDIR}"

LDFLAGS += "-L${HALIF_STAGED} \
            -lavclock-v${HALIF_AVCLOCK_VER}-cpp \
            -lcommon-v${HALIF_COMMON_VER}-cpp \
            -L${BINDER_LIBDIR} -lbinder -lutils"

do_compile() {
    # Source BEFORE the libraries: the default LDFLAGS carry -Wl,--as-needed, which
    # drops any -l whose symbols are not yet referenced. The translation unit must
    # appear first so its references keep the interface + binder libraries linked.
    # Library order is dependents-before-dependencies (avclock -> common -> binder/utils).
    ${CXX} ${CXXFLAGS} \
        "${S}/mw-halif-example.cpp" \
        ${LDFLAGS} -o "${B}/mw-halif-example"
}

do_install() {
    install -d "${D}${bindir}"
    install -m 0755 "${B}/mw-halif-example" "${D}${bindir}/"
}

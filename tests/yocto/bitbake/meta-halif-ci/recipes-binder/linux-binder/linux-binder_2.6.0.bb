# CI STUB - not the real linux-binder recipe.
#
# rdk-halif-aidl has DEPENDS = "linux-binder"; the real provider lives in the RDK
# layer stack, which we do not reproduce here. To let CI exercise the rdk-halif-aidl
# recipe's real do_install / do_package (where the packaging bugs live), this stub
# stages a PREBUILT Binder SDK into the sysroot in the exact layout the recipe's
# build expects:
#
#   ${STAGING_DIR_HOST}${prefix}/lib/binder/libbinder.so, libutils.so, ...
#   ${STAGING_DIR_HOST}${prefix}/include/binder_sdk/...
#
# The tarball is produced by tests/yocto/bitbake/run.sh from the SDK already built
# in out/ (via build_binder.sh), so this recipe never compiles anything.

SUMMARY = "CI stub providing a prebuilt Binder SDK for rdk-halif-aidl"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

SRC_URI = "file://binder-sdk.tar.gz"
S = "${WORKDIR}/binder-sdk"

PROVIDES = "linux-binder"

# Prebuilt binaries: do not try to compile, strip, or debug-split them.
do_configure[noexec] = "1"
do_compile[noexec] = "1"
INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
INHIBIT_SYSROOT_STRIP = "1"
INSANE_SKIP:${PN} = "already-stripped ldflags textrel arch libdir staticdev"

do_install() {
    install -d "${D}${libdir}/binder" "${D}${includedir}/binder_sdk"
    # -R not -a: the prebuilt files carry the host build uid, and do_package
    # rejects files owned by a uid with no target user ("host contamination").
    cp -R "${S}/lib/binder/." "${D}${libdir}/binder/"
    cp -R "${S}/include/binder_sdk/." "${D}${includedir}/binder_sdk/"
    chown -R root:root "${D}${libdir}/binder" "${D}${includedir}/binder_sdk"
    # the prebuilt header tree contains a dangling symlink; drop broken links.
    find "${D}${includedir}/binder_sdk" -xtype l -delete
}

FILES:${PN} = "${libdir}/binder ${includedir}/binder_sdk"

# Stage the non-standard lib/binder subdir into dependent recipes' sysroots.
SYSROOT_DIRS += "${libdir}/binder"

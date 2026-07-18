# EXAMPLE build-configuration include for the vendor build. Require it from your
# local.conf / distro:
#   require ${TOPDIR}/../rdk-halif-aidl/tests/yocto/meta-vendor/conf/halif-vendor.inc

# The mount point is a real partition, not a label - the rootfs mounts a partition
# per layer. Setting it to /vendor puts the libraries on the vendor mount:
#
#   /vendor/rdk-halif-aidl/lib<comp>-v<ver>-cpp.so
#
# HALIF_LIBDIR derives from this (${HALIF_MOUNT_POINT}/rdk-halif-aidl), so it is
# deliberately NOT set here. Override it only if this platform's vendor mount is
# somewhere else.
HALIF_MOUNT_POINT = "/vendor"

# HALIF_COMPONENTS is left at its default (the full component list) and
# HALIF_VERSIONS_FILE defaults to the source's versions_released.yaml, so this
# configuration builds EVERY HAL at its released version. To build a different
# cohort, point HALIF_VERSIONS_FILE at another manifest (components: {comp: ver});
# unpinned components build their latest. Pinning an older base component (e.g.
# common) constrains the build to that version's closure.

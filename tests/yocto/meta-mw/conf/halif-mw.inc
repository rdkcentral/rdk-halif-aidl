# EXAMPLE build-configuration include for the middleware build. Require it from
# your local.conf / distro:
#   require ${TOPDIR}/../rdk-halif-aidl/tests/yocto/meta-mw/conf/halif-mw.inc

# The mount point is a real partition, not a label - the rootfs mounts a partition
# per layer. Setting it to /mw puts the libraries on the middleware mount:
#
#   /mw/rdk-halif-aidl/lib<comp>-v<ver>-cpp.so
#
# This is the ONLY difference from the vendor configuration: same components, same
# versions, a different mount. HALIF_LIBDIR derives from the mount point
# (${HALIF_MOUNT_POINT}/rdk-halif-aidl), so it is deliberately NOT set here. Override
# it only if this platform's middleware mount is somewhere else.
HALIF_MOUNT_POINT = "/mw"

# HALIF_COMPONENTS is left at its default (the full component list) and
# HALIF_VERSIONS_FILE defaults to the source's versions_released.yaml, so this
# configuration builds EVERY HAL at its released version. Point HALIF_VERSIONS_FILE
# at another manifest to build a different cohort.

# EXAMPLE build-configuration include for the vendor build. Require it from your
# local.conf / distro:
#   require ${TOPDIR}/../rdk-halif-aidl/tests/yocto/meta-vendor/conf/halif-vendor.inc

HALIF_ROLE = "vendor"
HALIF_LIBDIR = "${libdir}/halif"
HALIF_INCDIR = "${includedir}/halif"

# HALIF_COMPONENTS is left at its default (the full component list) and
# HALIF_VERSIONS_FILE defaults to the source's versions_released.yaml, so this
# configuration builds EVERY HAL at its released version. To build a different
# cohort, point HALIF_VERSIONS_FILE at another manifest (components: {comp: ver});
# unpinned components build their latest. Pinning an older base component (e.g.
# common) constrains the build to that version's closure.

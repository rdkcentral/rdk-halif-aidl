# EXAMPLE build-configuration include for the middleware build. Require it from
# your local.conf / distro:
#   require ${TOPDIR}/../rdk-halif-aidl/tests/yocto/meta-mw/conf/halif-mw.inc

HALIF_ROLE = "mw"
HALIF_LIBDIR = "${libdir}/halif"
HALIF_INCDIR = "${includedir}/halif"

# HALIF_COMPONENTS is left at its default (the full component list) and
# HALIF_VERSIONS_FILE defaults to the source's versions_released.yaml, so this
# configuration builds EVERY HAL at its released version - identical to the
# vendor build but installed to the MW destination. Point HALIF_VERSIONS_FILE at
# another manifest to build a different cohort.

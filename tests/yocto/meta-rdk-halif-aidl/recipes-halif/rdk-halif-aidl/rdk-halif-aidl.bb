# rdk-halif-aidl - build a chosen set of RDK HAL AIDL interface libraries from
# their committed, pre-generated C++, and split the output into one package per
# component (rdk-halif-aidl-<comp>). No AIDL / codegen toolchain required.
#
# Named -aidl throughout (layer, recipe, packages, install paths) so it is never
# confused with the legacy C HAL (rdk-halif-*), which it coexists with during
# migration.
#
#
# WHAT IT READS - the source tree (${S}; one SRC_URI, one SRCREV)
# -----------------------------------------------------------------------------
#   rdk-halif-aidl/
#   |-- versions_released.yaml          the released cohort: {comp: ver}
#   |-- <comp>/<ver>/                   a committed snapshot. Several versions of
#   |   |                               the SAME component coexist here, e.g.
#   |   |                               avclock/{0.1.0.0,0.2.0.0,0.2.0.1}
#   |   |-- CMakeLists.txt              builds lib<comp>-v<ver>-cpp.so
#   |   |-- include/com/rdk/hal/...     generated headers (the AIDL namespace)
#   |   |-- src/...                     generated C++
#   |   `-- interface.yaml              imports: [<dep>@<ver>]
#   `-- tests/yocto/
#       |-- meta-rdk-halif-aidl/        this layer (+ halif_plan/gen_recipes)
#       |-- meta-vendor/, meta-mw/      example role layers + consumer examples
#       `-- ci/                         our offline tests - NOT consumption
#
#   HALIF_VERSIONS_FILE selects WHICH version of each component is built; every
#   snapshot is present in the checkout regardless of what is selected.
#
#
# WHAT IT BUILDS - private, inside ${B}
# -----------------------------------------------------------------------------
#   ${B}/plan.txt                       topological build order (halif_plan.py)
#   ${B}/obj/<comp>/<ver>/              one CMake build dir per comp AND version.
#                                       Versioned because ${B} persists across
#                                       rebuilds: reusing obj/<comp> after
#                                       HALIF_VERSIONS_FILE changes trips CMake's
#                                       "source does not match the cache" error.
#   ${B}/staged/lib/rdk-halif-aidl/     built siblings, so components later in
#   ${B}/staged/include/rdk-halif-aidl/ the plan can link/include them
#
#
# WHAT IT SHIPS - the consumption surface
# -----------------------------------------------------------------------------
#   ${libdir}/rdk-halif-aidl/lib<comp>-v<ver>-cpp.so
#                                       -> package rdk-halif-aidl-<comp>
#   ${includedir}/rdk-halif-aidl/<comp>/<ver>/include/com/rdk/hal/...
#                                       -> package rdk-halif-aidl-<comp>-dev
#
#   The version is in the .so NAME (and its SONAME), so libraries for several
#   versions sit side by side in one flat directory. Headers have no version in
#   their filename (BnPropertyValue.h is the same name in every version), so for
#   them the version has to live in the PATH.
#
#
# WHAT A CONSUMER DOES
# -----------------------------------------------------------------------------
#   DEPENDS        = "rdk-halif-aidl"              # stages libs + headers
#   RDEPENDS:${PN} = "rdk-halif-aidl-hdmicec rdk-halif-aidl-common"
#
#   CXXFLAGS += "-I${STAGING_INCDIR}/rdk-halif-aidl/hdmicec/0.1.0.0/include"
#   LDFLAGS  += "-L${STAGING_LIBDIR}/rdk-halif-aidl -lhdmicec-v0.1.0.0-cpp"
#
#   #include <com/rdk/hal/hdmicec/IHdmiCec.h>
#
#   Worked examples: meta-vendor/ and meta-mw/ recipes-example/.
#
#
# A build configuration controls this with variables (see the meta-vendor /
# meta-mw example includes):
#   HALIF_COMPONENTS        components to build   (default: all, from the .inc)
#   HALIF_VERSIONS_FILE     versions manifest     (default: versions_released.yaml)
#   HALIF_ROLE              vendor | mw           (labels who is building)
#   HALIF_LIBDIR/INCDIR     install destinations  (default: ${libdir}/rdk-halif-aidl)
#
# The offline contract tests tests/yocto/ci/*.sh exercise the same build loop
# without BitBake. This is reference material - adapt SRCREV and the toolchain to
# your project.

SUMMARY = "RDK HAL AIDL interface libraries"
HOMEPAGE = "https://github.com/rdkcentral/rdk-halif-aidl"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"

SRC_URI = "git://github.com/rdkcentral/rdk-halif-aidl.git;protocol=https;branch=develop"
SRCREV = "${AUTOREV}"
S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

# The Binder SDK (libbinder/libutils + headers) is provided by the linux-binder
# recipe and staged into the recipe sysroot.
DEPENDS = "linux-binder"

# Default component set (every released component). A build configuration may
# subset HALIF_COMPONENTS and set HALIF_VERSIONS_FILE in its own include.
require ${THISDIR}/halif-components.inc

HALIF_ROLE ??= "vendor"
HALIF_LIBDIR ??= "${libdir}/rdk-halif-aidl"
HALIF_INCDIR ??= "${includedir}/rdk-halif-aidl"

# Versions manifest (components: {comp: ver}), consumed directly. Defaults to the
# source's own versions_released.yaml - the released cohort - so a plain build
# produces the released versions. A configuration may point this at another
# manifest; components it does not pin build their latest snapshot. Set it empty
# to build every component at latest.
HALIF_VERSIONS_FILE ??= "${S}/versions_released.yaml"

inherit cmake

# One CMake project per component, so skip the single-project configure and drive
# cmake per component in do_compile (reusing the cmake class' cross toolchain).
do_configure[noexec] = "1"

do_compile() {
    cmake_do_generate_toolchain_file

    # An explicitly empty HALIF_COMPONENTS is a misconfiguration: halif_plan.py
    # with no component list would build every component while PACKAGES (below,
    # from the same variable) would be empty - so fail fast instead.
    if [ -z "${HALIF_COMPONENTS}" ]; then
        bbfatal "HALIF_COMPONENTS is empty - set the components to build (default: all, from halif-components.inc)"
    fi

    # Resolve the topological build order (dependencies first), pinning versions
    # from the configuration's manifest if one is set. The planner ships with
    # this layer and is fetched with the source.
    versions=""
    [ -n "${HALIF_VERSIONS_FILE}" ] && versions="--versions ${HALIF_VERSIONS_FILE}"
    "${S}/tests/yocto/meta-rdk-halif-aidl/halif_plan.py" ${versions} ${HALIF_COMPONENTS} > "${B}/plan.txt" \
        || bbfatal "halif_plan.py failed to resolve a build order"

    # Sibling libs/headers built earlier in the plan are staged here so later
    # components link them; the Binder SDK comes from the recipe sysroot. Start
    # clean so a changed HALIF_VERSIONS_FILE can't leave stale per-version libs.
    rm -rf "${B}/staged"
    install -d "${B}/staged/lib/rdk-halif-aidl" "${B}/staged/include/rdk-halif-aidl"

    while read comp ver; do
        bbnote "rdk-halif-aidl: building ${comp}@${ver}"
        # Build dir keyed by component AND version, so an incremental rebuild
        # after HALIF_VERSIONS_FILE changes cannot hit a stale CMake cache.
        cmake -S "${S}/${comp}/${ver}" -B "${B}/obj/${comp}/${ver}" \
            -G "${OECMAKE_GENERATOR}" \
            -DCMAKE_TOOLCHAIN_FILE="${WORKDIR}/toolchain.cmake" \
            -DBINDER_SDK_DIR="${STAGING_DIR_HOST}${prefix}" \
            -DBINDER_SDK_INCLUDE_DIR="${STAGING_DIR_HOST}${prefix}" \
            -DHALIF_LIB_DIR="${B}/staged/lib/rdk-halif-aidl" \
            -DHALIF_INCLUDE_DIR="${B}/staged/include/rdk-halif-aidl"
        cmake --build "${B}/obj/${comp}/${ver}" -- ${PARALLEL_MAKE}
        install -m 0755 "${B}/obj/${comp}/${ver}/lib${comp}-v${ver}-cpp.so" "${B}/staged/lib/rdk-halif-aidl/"
        install -d "${B}/staged/include/rdk-halif-aidl/${comp}/${ver}"
        cp -R "${S}/${comp}/${ver}/include" "${B}/staged/include/rdk-halif-aidl/${comp}/${ver}/"
    done < "${B}/plan.txt"
}

do_install() {
    install -d "${D}${HALIF_LIBDIR}" "${D}${HALIF_INCDIR}"
    cp -a "${B}/staged/lib/rdk-halif-aidl/." "${D}${HALIF_LIBDIR}/"
    cp -a "${B}/staged/include/rdk-halif-aidl/." "${D}${HALIF_INCDIR}/"
}

# Split the output into one package per component: rdk-halif-aidl-<comp> (the .so)
# and rdk-halif-aidl-<comp>-dev (its headers). The -aidl in the package name keeps
# these distinct from the legacy C HAL's rdk-halif-* packages on the same rootfs.
# Built at parse time from HALIF_COMPONENTS.
python () {
    comps = (d.getVar('HALIF_COMPONENTS') or '').split()
    libdir = d.getVar('HALIF_LIBDIR')
    incdir = d.getVar('HALIF_INCDIR')
    pkgs = []
    for c in comps:
        main, dev = 'rdk-halif-aidl-' + c, 'rdk-halif-aidl-%s-dev' % c
        pkgs += [dev, main]
        d.setVar('SUMMARY:' + main, 'RDK HAL AIDL interface library: %s' % c)
        d.setVar('FILES:' + main, '%s/lib%s-v*-cpp.so' % (libdir, c))
        d.setVar('FILES:' + dev, '%s/%s' % (incdir, c))
        d.setVar('INSANE_SKIP:' + main, 'dev-so')
    d.setVar('PACKAGES', ' '.join(pkgs))
}

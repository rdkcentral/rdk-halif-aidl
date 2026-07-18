# Third-Party Build Integration

This guide defines how a production or third-party build system (Yocto/BitBake,
buildroot, or a bespoke CMake superbuild) consumes **rdk-halif-aidl**.

The deliverable is two build stages, run in order:

| Stage | Source | Produces | Toolchain |
| ----- | ------ | -------- | --------- |
| 1 — Binder SDK | `linux_binder_idl` (the `linux-binder` recipe) | `libbinder.so`, `libutils.so`, `servicemanager`, headers | Target cross-toolchain |
| 2 — HAL interface libraries | each `<module>/<version>/` snapshot | `lib<module>-v<version>-cpp.so` | Target cross-toolchain |

A production build compiles the **committed, pre-generated C++** in each released
`<module>/<version>/` snapshot. The AIDL compiler regenerates that C++ offline
for the architecture team; the **AIDL / codegen toolchain is never required on a
build host or target** for a released snapshot. (BitBake and the layer's helper
scripts are Python, so the build host has Python — it just never runs codegen.)

!!! warning "Build per component; the top-level CMake is a developer path"
    The top-level `CMakeLists.txt` runs the AIDL codegen toolchain
    (`aidl_ops.py`) at configure time and therefore requires the
    `linux_binder_idl` source and Python — it is the developer / integrated
    build, **not** the production path. Likewise the wrapper scripts
    (`build_binder.sh`, `build_modules.sh`, `build_interfaces.sh`) require a
    native host toolchain and abort in a cross/OpenEmbedded environment. A
    production build consumes each released snapshot **per component** from its
    self-contained `<module>/<version>/CMakeLists.txt`.

## Stage 1 — Binder SDK

The Binder SDK (libbinder/libutils + headers) is delivered by the `linux-binder`
recipe and staged into the recipe sysroot. Configure it with
`-DBUILD_HOST_AIDL=OFF` — the host AIDL tool runs on the build host and is not
part of a target image. See the
[linux_binder_idl BUILD guide](https://github.com/rdkcentral/linux_binder_idl/blob/develop/BUILD.md)
for cross-compilation flags and runtime/systemd setup. The essential line:

```bitbake
EXTRA_OECMAKE = "-DBUILD_HOST_AIDL=OFF"
```

## Stage 2 — HAL interface libraries (per component)

Each released snapshot builds from its own `<module>/<version>/CMakeLists.txt`,
which compiles the committed C++ into `lib<module>-v<version>-cpp.so`. A snapshot
that references sibling interfaces (e.g. `hdmicec` uses `common`) links their
libraries and includes their headers; those dependencies are declared in the
snapshot's `interface.yaml` `imports:` and must be built and staged first.

### CMake variables (per-component build)

| Variable                 | Purpose                                                     | Required |
| ------------------------ | ----------------------------------------------------------- | -------- |
| `BINDER_SDK_DIR`         | Staged Binder SDK prefix (`lib/binder` + headers)           | Yes      |
| `BINDER_SDK_INCLUDE_DIR` | Staged Binder SDK headers prefix (flat sysroot: same value) | Yes      |
| `HALIF_LIB_DIR`          | Directory holding dependency `lib<dep>-v<ver>-cpp.so`       | If deps  |
| `HALIF_INCLUDE_DIR`      | Root under which `<dep>/<ver>/include` resolves             | If deps  |

The direct invocation for one snapshot:

```bash
cmake -S <module>/<version> -B build/<module> \
    -DBINDER_SDK_DIR=<sysroot> -DBINDER_SDK_INCLUDE_DIR=<sysroot> \
    -DHALIF_LIB_DIR=<sysroot>/lib/rdk-halif-aidl \
    -DHALIF_INCLUDE_DIR=<sysroot>/include/rdk-halif-aidl
cmake --build build/<module>
cmake --install build/<module> --prefix <sysroot>   # stages lib<module>-v<ver>-cpp.so to lib/rdk-halif-aidl
```

The module `install()` rule stages the `.so` under `lib/rdk-halif-aidl`. A dependent also
needs the dependency's **headers**, so a complete stage additionally copies the
snapshot's `include/` tree to `<sysroot>/include/rdk-halif-aidl/<module>/<version>/
include`. `tests/yocto/ci/yocto_staging_check.sh` exercises this exact
contract offline (build `common` → stage → build `hdmicec` against it) and is the
executable reference for a recipe.

## Yocto integration — you own your recipes

The integration team controls its own recipes. What rdk-halif-aidl guarantees is
the per-component build **contract** above: the CMake variables, the lib +
header staging, and the inter-component dependency graph declared in each
snapshot's `interface.yaml` `imports:`. Any `.bb` that honours that contract
works; the shape of your recipes is yours to decide.

As a starting point and a CI-tested reference, the repo ships a layer at
`tests/yocto/meta-rdk-halif-aidl/` with a single `rdk-halif-aidl` recipe. Use it
directly:

```bitbake
BBLAYERS += "${TOPDIR}/../rdk-halif-aidl/tests/yocto/meta-rdk-halif-aidl"
IMAGE_INSTALL:append = " rdk-halif-aidl-common rdk-halif-aidl-avclock"   # the components you need
```

…or copy the recipe into your own layer and adapt it. The recipe builds the
selected components in dependency order and stages each one's lib + headers
before building its dependents, so the failure a hand-rolled single recipe hits —
a dependency not yet staged when a dependent links — does not arise.

The recipe is reference material and is validated in CI (`test.sh` Test 12) — if
you adopt it, pin `SRCREV` to the released tag's commit for reproducible builds.
Its install destination is overridable: `HALIF_MOUNT_POINT` (the partition mount,
`/vendor` | `/mw`), from which `HALIF_LIBDIR` (where the `.so` installs *and*
stages) and `HALIF_INCDIR` (headers, under the mount) derive. A build
configuration sets these to its partition layout.

## Non-Yocto build systems

Drive the same per-component CMake invocation shown above, in dependency order
(`scripts/halif_plan.py` prints the topological order for a set of components),
staging each component's lib + headers into a shared prefix before building its
dependents. `build_modules.sh` implements the same ordering for the developer
tree, and the `rdk-halif-aidl` recipe's `do_compile` does it for BitBake.

## Component selection, versions, and the vendor / middleware split

The interface libraries are consumed by two build configurations — the **vendor**
layer that implements the HAL, and the **middleware (MW)** that calls it. Both
build from the *same* `rdk-halif-aidl` recipe, to their own mounts, via two
knobs:

- **Which components** — `HALIF_COMPONENTS`, defaulting to the full list from the
  generated `halif-components.inc` (every buildable released component;
  `broadcast` is absent because it has no released snapshot). Leave it at the
  default to build **every HAL**, or set a subset — you name only what you want,
  and `halif_plan.py` adds each component's dependency closure automatically, so
  `common` need never be listed. The recipe splits the output into one package
  per component (`rdk-halif-aidl-<comp>`).
- **Which version** — every component builds its **latest** released snapshot by
  default; point `HALIF_VERSIONS_FILE` at a manifest (`components: {comp: ver}`,
  same schema as `versions_released.yaml`) to pin the top-level components. Each
  dependency follows the exact version its dependent links, and because the
  closure is keyed by (component, version), **different versions of one dependency
  coexist** in a single build — one consumer's `common@0.1.0.0` and another's
  `common@0.2.0.0` are both built and shipped, side by side in the
  `rdk-halif-aidl-common` package.

There is no generated per-config include — a build configuration just sets the
mount point and (optionally) a versions manifest:

```bitbake
# meta-vendor/conf/halif-vendor.inc, required from local.conf / distro
HALIF_MOUNT_POINT = "/vendor"
# HALIF_LIBDIR derives as ${HALIF_MOUNT_POINT}/rdk-halif-aidl
# HALIF_COMPONENTS + HALIF_VERSIONS_FILE left at default →
# builds every HAL from the source's versions_released.yaml (the released cohort).
```

The `tests/yocto/meta-vendor` and `meta-mw` examples both build the full HAL from
`versions_released.yaml`, differing only by mount point. The offline example
builds `tests/yocto/ci/yocto_build_vendor.sh` and `yocto_build_mw.sh` (wrappers
over `yocto_build.sh <role> [manifest]`) do the same without BitBake — each takes
the versions manifest as an argument, defaulting to the repo's
`versions_released.yaml`.

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
    -DHALIF_LIB_DIR=<sysroot>/lib/halif \
    -DHALIF_INCLUDE_DIR=<sysroot>/include/halif
cmake --build build/<module>
cmake --install build/<module> --prefix <sysroot>   # stages lib<module>-v<ver>-cpp.so to lib/halif
```

The module `install()` rule stages the `.so` under `lib/halif`. A dependent also
needs the dependency's **headers**, so a complete stage additionally copies the
snapshot's `include/` tree to `<sysroot>/include/halif/<module>/<version>/
include`. `tests/yocto/run-yocto-per-component.sh` exercises this exact
contract offline (build `common` → stage → build `hdmicec` against it) and is the
executable reference for a recipe.

## Yocto integration — you own your recipes

The integration team controls its own recipes. What rdk-halif-aidl guarantees is
the per-component build **contract** above: the CMake variables, the lib +
header staging, and the inter-component dependency graph declared in each
snapshot's `interface.yaml` `imports:`. Any `.bb` that honours that contract
works; the shape of your recipes is yours to decide.

As a starting point and a CI-tested reference, the repo ships a layer at
`tests/yocto/meta-rdk-halif/` with a single `rdk-halif` recipe. Use it directly:

```bitbake
BBLAYERS += "${TOPDIR}/../rdk-halif-aidl/tests/yocto/meta-rdk-halif"
IMAGE_INSTALL:append = " rdk-halif-common rdk-halif-avclock"   # the components you need
```

…or copy the recipe into your own layer and adapt it. The recipe builds the
selected components in dependency order and stages each one's lib + headers
before building its dependents, so the failure a hand-rolled single recipe hits —
a dependency not yet staged when a dependent links — does not arise.

The recipe is reference material and is validated in CI (`test.sh` Test 12) — if
you adopt it, pin `SRCREV` to the released tag's commit for reproducible builds.
Its install destination is overridable: `HALIF_LIBDIR` (where the `.so` installs)
and `HALIF_INCDIR` (where headers stage), plus `HALIF_ROLE` (`vendor` | `mw`) to
label who is building. A build configuration sets these to its partition layout.

## Non-Yocto build systems

Drive the same per-component CMake invocation shown above, in dependency order
(`scripts/halif_plan.py` prints the topological order for a set of components),
staging each component's lib + headers into a shared prefix before building its
dependents. `build_modules.sh` implements the same ordering for the developer
tree, and the `rdk-halif` recipe's `do_compile` does it for BitBake.

## Component selection, versions, and the vendor / middleware split

The interface libraries are consumed by two build configurations — the **vendor**
layer that implements the HAL, and the **middleware (MW)** that calls it. Both
build from the *same* `rdk-halif` recipe, to their own destinations, via two
knobs:

- **Which components** — `HALIF_COMPONENTS`, defaulting to the full list from the
  generated `halif-components.inc` (every buildable released component;
  `broadcast` is absent because it has no released snapshot). Leave it at the
  default to build **every HAL**, or set a subset. The recipe splits the output
  into one package per component (`rdk-halif-<comp>`).
- **Which version** — every component builds its **latest** released snapshot by
  default. To pin specific versions, point `HALIF_VERSIONS_FILE` at a manifest
  (`components: {comp: ver}`, same schema as `versions_released.yaml`); the recipe
  **consumes it directly**. `halif_plan.py` resolves the build order and rejects
  an inconsistent set — a component's linked dependencies must be pinned at the
  exact linked version, so pinning an older *base* component (e.g. `common`)
  constrains the build to that version's closure.

There is no generated per-config include — a build configuration just sets the
role, the destinations, and (optionally) a versions manifest:

```bitbake
# meta-vendor/conf/halif-vendor.inc, required from local.conf / distro
HALIF_ROLE = "vendor"
HALIF_LIBDIR = "${libdir}/halif"
# HALIF_COMPONENTS left at default → builds every HAL at latest.
# To pin instead: HALIF_VERSIONS_FILE = "${THISDIR}/versions_vendor.yaml"
```

The `tests/yocto/meta-vendor` and `meta-mw` examples both build the full HAL set
at latest, differing only by role + destination; `versions_vendor.yaml` shows the
pinning-manifest format. `tests/yocto/run-yocto-roles.sh` builds the full cohort
offline, installs it to each role's destination, and exercises version pinning.

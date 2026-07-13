# Third-Party Build Integration

This guide defines how a production or third-party build system (Yocto/BitBake,
buildroot, or a bespoke CMake superbuild) consumes **rdk-halif-aidl**.

The deliverable is two build stages, run in order:

| Stage | Source | Produces | Toolchain |
| ----- | ------ | -------- | --------- |
| 1 — Binder SDK | `linux_binder_idl` (the `linux-binder` recipe) | `libbinder.so`, `libutils.so`, `servicemanager`, headers | Target cross-toolchain |
| 2 — HAL interface libraries | each `<module>/<version>/` snapshot | `lib<module>-v<version>-cpp.so` | Target cross-toolchain |

A production build compiles the **committed, pre-generated C++** in each released
`<module>/<version>/` snapshot. The AIDL compiler and Python are used offline by
the architecture team to regenerate that C++; **they are never required on a
build host or target** for a released snapshot.

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
include`. `tests/fake-yocto/run-fake-yocto-per-component.sh` exercises this exact
contract offline (build `common` → stage → build `hdmicec` against it) and is the
executable reference for a recipe.

## Yocto integration — you own your recipes

The integration team controls its own recipes. What rdk-halif-aidl guarantees is
the per-component build **contract** above: the CMake variables, the lib +
header staging, and the inter-component dependency graph declared in each
snapshot's `interface.yaml` `imports:`. Any `.bb` that honours that contract
works; the shape of your recipes is yours to decide.

As a starting point and a CI-tested reference, the repo ships `meta-rdk-halif/` —
a layer whose recipes are generated from `interface.yaml`. Use it directly:

```bitbake
BBLAYERS += "${TOPDIR}/../rdk-halif-aidl/meta-rdk-halif"
IMAGE_INSTALL:append = " rdk-halif-hdmicec"    # pulls rdk-halif-common via DEPENDS
```

…or copy `classes/rdk-halif-module.bbclass` and a recipe into your own layer and
adapt them. Either way BitBake derives inter-component `DEPENDS` from
`interface.yaml`, so the dependency-ordering failure a hand-rolled single recipe
hits — a dependency not yet staged when a dependent links — does not arise.

The reference recipes are generated by `scripts/gen_recipes.py` (one per
component, latest released version) and validated in CI (`test.sh` Test 12) so
they never drift from `interface.yaml`. They are reference material — if you
adopt them, pin `SRCREV` to the released tag's commit for reproducible builds.

## Non-Yocto build systems

Drive the same per-component CMake invocation shown above, in dependency order
(topologically sort each snapshot's `interface.yaml` `imports:`), staging each
component's lib + headers into a shared prefix before building its dependents.
`build_modules.sh` implements this ordering for the developer tree and is the
reference algorithm; `meta-rdk-halif/classes/rdk-halif-module.bbclass` implements
the per-recipe half.

## Version selection

`versions_released.yaml` pins every component to its latest released snapshot
(the cohort a release ships). The generator emits recipes for the latest version
per component; to build a specific historical snapshot, add its recipe and set
`PREFERRED_VERSION:pn-rdk-halif-<component>`.

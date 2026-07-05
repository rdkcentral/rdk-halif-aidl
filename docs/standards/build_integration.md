# Third-Party Build Integration

This guide defines how a production or third-party build system (Yocto/BitBake,
buildroot, or a bespoke CMake superbuild) consumes **rdk-halif-aidl**.

!!! warning "Build the artifacts with CMake directly"
    The repository's wrapper scripts — `build_binder.sh`, `build_modules.sh`,
    `build_interfaces.sh` — are developer and architecture-team convenience tools
    that **require a native host toolchain**. Production and cross builds **must
    invoke CMake directly** with the variables below. The scripts detect a
    cross/OpenEmbedded environment and abort, because running them there silently
    produces broken or empty output.

## What an integrator builds

The deliverable is two CMake builds, run in order:

| Stage | Source | Produces | Toolchain |
| ----- | ------ | -------- | --------- |
| 1 — Binder SDK | `linux_binder_idl` (the `linux-binder` recipe) | `libbinder.so`, `libutils.so`, `servicemanager`, headers | Target cross-toolchain |
| 2 — HAL interface libraries | each `<module>/<version>/` | `lib<module>-v<version>-cpp.so` | Target cross-toolchain |

The HAL libraries are compiled from **committed, pre-generated C++**. The AIDL
compiler and Python are used offline by the architecture team to regenerate that
C++; they are **never required on a build host or target**.

## Requirements

1. **Toolchain via the environment.** Provide `CC`, `CXX`, `CFLAGS`, `CXXFLAGS`,
   and `LDFLAGS` through the cross environment. BitBake sets these automatically;
   CMake consumes them.
2. **Binder SDK: runtime only.** Configure the `linux_binder_idl` build with
   `-DBUILD_HOST_AIDL=OFF`. The host AIDL tool runs on the build host and is not
   part of a target image. The binder CMake also auto-enables its Yocto profile
   (disabling host-only install rules) when `OECORE_*_SYSROOT` is present — this
   is correct and requires no action.
3. **HAL modules: point at the staged SDK.** Configure the top-level CMake with
   the staged Binder SDK location. A staged SDK is flat, so headers and libraries
   share one prefix — set both `BINDER_SDK_DIR` and `BINDER_SDK_INCLUDE_DIR` to it.
4. **Select the version on the CMake command line.** `INTERFACE_TARGET` picks
   the module(s) and `AIDL_SRC_VERSION` picks the version (`current` or a
   released `X.Y.Z.W`). The top-level CMake builds one target/version per
   invocation. `versions_released.yaml` is a convenience manifest consumed by
   `build_modules.sh` — **not** by CMake — so a build system that wants a whole
   released cohort iterates the versions itself (one CMake invocation each).

### CMake variables (Stage 2 — HAL modules)

| Variable                 | Purpose                                                      | Required |
| ------------------------ | ------------------------------------------------------------ | -------- |
| `INTERFACE_TARGET`       | Module(s) to build; `all` or a name (default `all`)          | No       |
| `AIDL_SRC_VERSION`       | Version to build; `current` or `X.Y.Z.W` (default `current`) | No       |
| `BINDER_SDK_DIR`         | Staged Binder SDK libraries prefix                           | Yes      |
| `BINDER_SDK_INCLUDE_DIR` | Staged Binder SDK headers prefix                             | Yes      |
| `OUT_DIR`                | Output directory (default `out`)                             | No       |

## Reference recipes

Copy-me starting templates (not consumed by this repo) live under `examples/`:

- [`rdk-halif-aidl.bb`](examples/rdk-halif-aidl.bb) — BitBake recipe.
- [`rdk-halif-aidl.yaml`](examples/rdk-halif-aidl.yaml) — [Bob Build Tool](https://bobbuildtool.dev/) recipe.

Both are thin wrappers over the same direct-CMake invocation, so the build is
build-system-agnostic — porting to another build system means calling the same
CMake with the same variables. The recipes are reference material and are not
CI-verified here; pin them to a released tag and adapt the toolchain/sysroot to
your project.

## Recipe pattern (BitBake)

**Stage 1 — Binder SDK** is delivered by the `linux-binder` recipe. See the
[linux_binder_idl BUILD guide](https://github.com/rdkcentral/linux_binder_idl/blob/develop/BUILD.md)
for the full recipe, cross-compilation flags, and runtime/systemd setup. The
essential line:

```bitbake
EXTRA_OECMAKE = "-DBUILD_HOST_AIDL=OFF"
```

**Stage 2 — HAL interface libraries** depend on the staged SDK:

```bitbake
DEPENDS = "linux-binder"
inherit cmake

# Let the cmake class run configure / compile / install — don't override the
# tasks. Pass build options via EXTRA_OECMAKE. The CMake install() rules place
# the libraries under <prefix>/lib/halif, so the class' install step
# (cmake --install ${B} --prefix ${D}${prefix}) puts them in the right place.
EXTRA_OECMAKE = " \
    -DINTERFACE_TARGET=all \
    -DBINDER_SDK_DIR=${STAGING_DIR}${prefix} \
    -DBINDER_SDK_INCLUDE_DIR=${STAGING_DIR}${prefix} \
"

FILES:${PN} += "${libdir}/halif/*.so"
```

## Why not the wrapper scripts

The scripts assume a developer's native host:

- They build the host AIDL compiler. Under a cross `CC` that tool is compiled for
  the target and cannot execute on the build host, failing configuration.
- The binder CMake auto-enables its Yocto profile from `OECORE_*_SYSROOT`, which
  disables the host-only install rules the scripts rely on — so a script run
  inside an OpenEmbedded shell appears to succeed but stages nothing.

Both are correct behaviours for a production build invoked **directly through
CMake**, and both are wrong for the developer scripts — which is why the scripts
refuse to run in a cross/OE environment. An integrator never needs them.

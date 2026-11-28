# Third-Party Build Integration

This guide defines how a production or third-party build system (Yocto/BitBake,
buildroot, or a bespoke CMake superbuild) consumes **rdk-halif-aidl**.

The deliverable is two build stages, run in order:

| Stage | Source | Produces | Toolchain |
| ----- | ------ | -------- | --------- |
| 1 — Binder SDK | `linux_binder_idl` (the `linux-binder` recipe) | `libbinder.so`, `libutils.so`, `servicemanager`, headers | Target cross-toolchain |
| 2 — HAL interface libraries | this repository, selected by a version manifest | one library per interface and version, plus headers, a CMake package and a pkg-config file | Target cross-toolchain |

A production build compiles the **committed, pre-generated C++** in each released
`<module>/<version>/` snapshot. The AIDL compiler regenerates that C++ offline
for the architecture team; the **AIDL compiler is never required on a build host
or target** for a released snapshot.

!!! warning "Production builds call CMake directly"
    The wrapper scripts (`build_binder.sh`, `build_modules.sh`,
    `build_interfaces.sh`) are developer tools. They require a native host
    toolchain and abort in a cross/OpenEmbedded environment. A production build
    configures the top-level `CMakeLists.txt` directly, as described in
    [Stage 2](#stage-2-hal-interface-libraries). Only the `current` versions are
    generated from AIDL at build time, and they need the `aidl` executable; the
    released snapshots in the default manifest do not.

## Stage 1 — Binder SDK

The Binder SDK (libbinder/libutils + headers) is delivered by the `linux-binder`
recipe and staged into the recipe sysroot. Two switches configure it, and a
recipe states both explicitly rather than inheriting a default:

| Switch | Value to pass | Why |
| ------ | ------------- | --- |
| `BUILD_HOST_AIDL` | `OFF`, on every platform | the host AIDL tool runs on the build host and is not part of a target image |
| `BINDER_PROTOCOL` | `8` — or the kernel's protocol, if a legacy platform is still in the fleet | libbinder compares protocol versions for exact equality when it opens the driver |

**The ELF class is not a switch.** It follows `CC`/`CXX`, and nothing in the
Binder SDK can change it — point the build at the right cross-compiler and a
32-bit toolchain produces a 32-bit `libbinder.so`. `TARGET_BITNESS=32|64` exists
only as an optional assertion, for a build that should *stop* if the toolchain
is not what was expected.

State both rather than relying on a default: a recipe that says what it wants
does not change meaning when a default does.

An older recipe may pass `BINDER_IPC_32BIT` or the
`TARGET_LIB32_VERSION` / `TARGET_LIB64_VERSION` pair. Those spellings are
deprecated — the Binder SDK still honours them, so such a recipe keeps building,
but a new one writes `BINDER_PROTOCOL` and `TARGET_BITNESS`.

### The three platform configurations

Bitness is a property of the role; the wire protocol is a property of the
platform. There is one kernel, so it serves one protocol, and every role on the
device speaks that one.

| | The kernel it matches | Switches |
| --- | ------ | -------- |
| **A** — legacy all-32-bit | a 32-bit kernel whose resolved config has `CONFIG_ANDROID_BINDER_IPC_32BIT=y` | `-DBINDER_PROTOCOL=7`, built with a 32-bit toolchain |
| **B** — 32-bit userspace on a protocol-8 kernel | every other 32-bit userspace: a 32-bit kernel with that symbol unset or absent, and 32-bit middleware on a 64-bit kernel | `-DBINDER_PROTOCOL=8`, built with a 32-bit toolchain |
| **C** — 64-bit userspace | any 64-bit kernel | `-DBINDER_PROTOCOL=8`, built with a 64-bit toolchain |

**The kernel version does not decide the row — its config does.** Being 32-bit
at 4.17 or older is what makes protocol 7 *possible*; it is not what makes it
apply. Two devices on the same silicon and the same kernel version can sit in
different rows.

Determining which protocol a kernel serves, and reading its resolved `.config`
to find out, is covered in
[`PROTOCOL.md`](https://github.com/rdkcentral/linux_binder_idl/blob/develop/PROTOCOL.md).
A build that needs it derived rather than stated can use
`example/yocto/binder-protocol-from-kernel.inc` from the same repository.

**Row A is the one that must state its switch.** `BINDER_PROTOCOL` defaults to
`8` on every toolchain, so rows B and C are what a build inherits without
asking; a legacy platform is the exception and states `-DBINDER_PROTOCOL=7`.
Being 32-bit does not imply protocol 7 — row B is 32-bit throughout and runs
protocol 8. Protocol 8 carries 64-bit wire *fields*, which a 32-bit process
fills by zero-extension — it is the mixed-capable protocol, not the 64-bit one.
Protocol 7 is the legacy-compat option, and its 32-bit fields cannot hold a
64-bit pointer, which is why the kernel option is `depends on !64BIT` and why a
protocol-7 platform is all-32-bit throughout.

**On a 64-bit kernel two SDKs ship** — a 32-bit one for the middleware and a
64-bit one for the vendor: different ELF classes, both protocol 8, because both
talk to the same kernel.

A protocol mismatch is not caught at build time. It surfaces on the device,
where every binder process terminates at startup.

```bitbake
# Row B — 32-bit userspace on a protocol-8 kernel. The 32-bit ELF class comes
# from the cross-toolchain, so it is not stated here.
EXTRA_OECMAKE = " \
    -DBUILD_HOST_AIDL=OFF \
    -DBINDER_PROTOCOL=8 \
"
```

`BUILD_HOST_AIDL` is fixed at `OFF`. `BINDER_PROTOCOL` is the platform-dependent
one, and a recipe can derive it from the kernel's resolved `.config` instead of
declaring it, so nothing is hand-maintained per platform. See
[`PROTOCOL.md`](https://github.com/rdkcentral/linux_binder_idl/blob/develop/PROTOCOL.md)
for that derivation, the full switch matrix and the verification steps, and the
[linux_binder_idl BUILD guide](https://github.com/rdkcentral/linux_binder_idl/blob/develop/BUILD.md)
for cross-compilation flags and runtime/systemd setup.

## Stage 2 — HAL interface libraries

### Build process

CMake drives the build. It consumes a YAML manifest that lists every interface
and the version to build, by default `versions_released.yaml`. From this list
CMake generates the build graph, builds each listed interface together with the
interfaces it imports, and installs everything into a single install directory,
using version-tagged file names or directories where needed. The same interface
can be built in several versions at once, since each version has its own
library, headers and package files.

| Variable                 | Purpose                                                             | Default                  |
| ------------------------ | ------------------------------------------------------------------- | ------------------------ |
| `INTERFACE_RELEASE_FILE` | Version manifest; the build fails if the file does not exist        | `versions_released.yaml` |
| `INTERFACE_TARGET`       | Build only this module (and its dependencies) instead of the manifest | unset                    |
| `INTERFACE_VERSION`      | Version of `INTERFACE_TARGET`                                       | `current`                |
| `CMAKE_PREFIX_PATH`      | Prefix of the staged Binder SDK (see below)                         | CMake default            |
| `CMAKE_INSTALL_PREFIX`   | Install prefix; `CMAKE_INSTALL_LIBDIR` etc. follow GNUInstallDirs   | CMake default            |
| `BUILD_SHARED_LIBS`      | Build shared instead of static libraries                            | `OFF`                    |
| `AIDL_EXECUTABLE`        | `aidl` compiler; only needed for `current` versions                 | found in `PATH`          |

The Binder SDK is found with `pkg-config` and the standard CMake search
variables, so a staged SDK needs nothing beyond `CMAKE_PREFIX_PATH` (or the
build system's usual sysroot settings). Compiler and flags come from the usual
`CC`, `CXX`, `CFLAGS`, `CXXFLAGS` and `LDFLAGS` environment variables, which
Yocto sets.

```bash
CC="${CC}" CXX="${CXX}" CFLAGS="${CFLAGS}" CXXFLAGS="${CXXFLAGS}" LDFLAGS="${LDFLAGS}" \
cmake -S . -B build \
    -DCMAKE_INSTALL_PREFIX=<prefix> \
    -DCMAKE_PREFIX_PATH=<binder-sdk-prefix> \
    -DINTERFACE_RELEASE_FILE=<manifest>        # optional
cmake --build build
DESTDIR=<image-dir> cmake --install build
```

When building locally, outside a meta build system, the helper scripts
`build_binder.sh` and `build_modules.sh` install the dependencies and set up the
environment for you. Within a meta build system, the build finds everything it
needs automatically, provided the well-known paths are in place.

### Packaging

For each interface and version, the install step provides:

- a CMake target `RdkHalifAidl::Interfacename-v0.1.0.0`, available after
  `find_package(RdkHalifAidlInterfacename 0.1.0.0 EXACT REQUIRED IMPORTED_TARGET)`;
- a pkg-config file, for example
  `/usr/lib/pkgconfig/rdk-halif-aidl-interfacename-0.1.0.0.pc`, whose `Name` is
  `rdk-halif-aidl-interfacename-0.1.0.0`;
- the library `lib<interface>-v<version>-cpp`, the headers under
  `include/<interface>/<version>/` and the sources under
  `src/<interface>/<version>/`.

Packaging the install directory into consumable artefacts is the meta build
system's job; see [Yocto Integration](yocto_integration.md) for the Yocto
recipe and its package split.

## Consuming the interfaces

There are three ways to link against an installed interface, in order of
preference.

**CMake** — the preferred approach. Call
`find_package(RdkHalifAidlInterfacename 0.1.0.0 EXACT REQUIRED IMPORTED_TARGET)`
and link the target:

```cmake
find_package(RdkHalifAidlIndicator 0.1.0.0 EXACT REQUIRED CONFIG)
target_link_libraries(indicator-hal-service PRIVATE RdkHalifAidl::Indicator-v0.1.0.0)
```

`SameMinorVersion` can replace `EXACT` to allow patch version updates. Because
the versions carry a leading `0`, though, `SameMinorVersion` behaves like
`SameMajorVersion` here.

**pkg-config** — where CMake is unavailable. `pkg-config --cflags
rdk-halif-aidl-interfacename-0.1.0.0` returns the include paths and
`pkg-config --libs rdk-halif-aidl-interfacename-0.1.0.0` the link flags. This
avoids hard-coding paths and is an acceptable alternative to CMake:

```make
CFLAGS += $(shell pkg-config --cflags rdk-halif-aidl-indicator-0.1.0.0)
LDFLAGS += $(shell pkg-config --libs rdk-halif-aidl-indicator-0.1.0.0)
```

**Source and header variables** — a fallback for legacy consumers. The CMake
package configuration exposes `RDK_HALIF_AIDL_INTERFACENAME_SRC_FILES` and
`RDK_HALIF_AIDL_INTERFACENAME_HEADER_FILES`, which let a consumer build the
interface code itself. Use this only as a last resort, since it leads to
unnecessary rebuilds and potential ABI mismatches.

As a temporary measure, the installed files also include `FindBinder.cmake` and
`FindAndroidUtils.cmake`, along with `binder.pc` and `utils.pc`. The generated
CMake targets use the former transitively, and the generated pkg-config files use the
latter. These files should eventually be delivered by the components that
provide Binder and Android Utils, but this project provides them for now.

Tools that call `build_modules.sh` directly, such as
[`rdkcentral/rdk-halif-aidl-unified-vts`](https://github.com/rdkcentral/rdk-halif-aidl-unified-vts),
need no changes. We encourage them to switch to a CMake-based (or at least
`pkg-config`-based) build instead of relying on hard-coded paths.

## Other build systems

Drive the same CMake invocation as shown under Stage 2 with the build system's
own toolchain and install it into a staging directory; consumers then use CMake
or pkg-config as described above.

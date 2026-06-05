# RDK HAL Aidl Interface

**RDK-HALIF-AIDL** is an open-source framework that standardizes hardware
abstraction layers using Android AIDL. It provides a structured, IPC-driven
interface for seamless communication between system components and hardware
devices.

Designed for embedded platforms, **RDK-HALIF-AIDL** ensures efficient hardware
interaction, modular development, and interoperability with Android-based
ecosystems.

Complete documentation: [https://rdkcentral.github.io/rdk-halif-aidl/](https://rdkcentral.github.io/rdk-halif-aidl/)

## Architecture

```mermaid
graph TB
    subgraph "Stage 1: Binder SDK"
        A[linux_binder_idl] -->|cmake install| B[out/target/]
        B --> C[libbinder.so<br/>libutils.so<br/>AIDL compiler]
    end

    subgraph "Stage 2: HAL Modules (module-local)"
        D["&lt;module&gt;/current/<br/>AIDL + generated C++"] -->|cmake build| F[Module Libraries]
        C -->|links against| F
        F --> G[out/target/lib/halif/]
    end

    B -.->|SDK dependency| F

    style B fill:#e1f5e1
    style G fill:#e1f5e1
```

**Stage 1 (Binder SDK)**: The `linux_binder_idl` project in `build-tools/` is an independent Android Binder port built as a separate Yocto recipe (linux-binder). See [build-tools/linux_binder_idl/BUILD.md](build-tools/linux_binder_idl/BUILD.md) for Yocto recipe integration and runtime setup.

### Directory Structure

Each component is **self-contained**: its AIDL, generated C++, docs and build
configuration all live within the component directory. A component has a
`current/` (in-development) directory and one directory per **released
version**. There is no central `stable/` tree.

```text
rdk-halif-aidl/
├── build-tools/
│   └── linux_binder_idl/     # Android Binder SDK (independent project)
├── out/
│   └── target/               # Complete deployment SDK
│       ├── lib/
│       │   ├── binder/       # Binder runtime libraries
│       │   └── halif/        # HAL interface libraries (lib<module>-vcurrent-cpp.so)
│       ├── bin/              # AIDL compiler
│       └── .sdk_ready        # Completion marker
├── versions.yaml             # Which version of each component to build
└── <module>/                 # HAL component directory (boot, videodecoder, ...)
    ├── metadata.yaml         # Component identity, version, RAG status
    ├── current/              # In-development version
    │   ├── interface.yaml    # AIDL interface definition (layout: module-local)
    │   ├── CMakeLists.txt    # Component build configuration
    │   ├── hfp-*.yaml        # HAL Feature Profile
    │   ├── com/rdk/hal/      # AIDL source files
    │   ├── include/ src/     # Generated C++ (committed)
    │   └── docs/             # Component documentation
    └── <version>/            # A released snapshot (e.g. 0.1.0.0) — same layout
        └── .hash             # Integrity hash of the released AIDL contract
```

A **release** is a plain copy of `current/` into a `<version>/` directory
(`./release.sh`), where `<version>` is the component's `metadata.yaml`
`version:`. Released directories are controlled, immutable snapshots.

## Quick Start

### Development workflow (interface authors)

**Purpose**: modify AIDL interfaces, regenerate C++, build the libraries.

```bash
# 1. Build the Binder SDK (once)
./build_binder.sh

# 2. Edit AIDL in a component's current/ directory
vim bootreason/current/com/rdk/hal/bootreason/IBootReason.aidl

# 3. Build — regenerates the module-local C++ and compiles the library
./build_modules.sh bootreason          # one component
./build_modules.sh all           # every component

# 4. Commit — AIDL and generated C++ live together in the component
git add bootreason/current/
git commit -m "Update boot interface"
```

Generated C++ is written into `bootreason/current/{include,src}/` and committed, so a
production build needs no Python or AIDL toolchain.

### Releasing a component

A release snapshots `current/` into a versioned directory, taking the version
from the component's `metadata.yaml`:

```bash
./release.sh bootreason     # snapshot bootreason/current/ -> bootreason/<version>/
./release.sh          # release every component not yet released
```

### Production build (Yocto/BitBake)

```bash
# linux_binder SDK is staged by the Yocto dependency system (DEPENDS = "linux-binder").
# A staged SDK is flat, so headers and libs share one prefix — pass both
# BINDER_SDK_DIR and BINDER_SDK_INCLUDE_DIR (they differ only in the local dev tree).
cmake -S . -B build -DINTERFACE_TARGET=all \
      -DBINDER_SDK_DIR=${STAGING_DIR}/usr \
      -DBINDER_SDK_INCLUDE_DIR=${STAGING_DIR}/usr
cmake --build build
cmake --install build
```

Compiles the committed module-local C++ into `lib<module>-vcurrent-cpp.so` and
installs to `${OUT_DIR}/target/lib/halif/`. Requires only CMake, a C++ compiler
and the linux_binder SDK — no Python, no AIDL compiler.

### Version manifest (`versions.yaml`)

`versions.yaml` is the manifest of which version of each component to build —
`current` (the in-development interface) or a released `<version>/` snapshot.
`./build_modules.sh manifest` builds the set it lists:

```bash
./build_modules.sh manifest               # build everything in versions.yaml
./build_modules.sh manifest --file alt.yaml
```

A component absent from the manifest falls back to its `default:` entry.

## Scripts

| Script | Role |
| ------ | ---- |
| `build_binder.sh` | **Stage 1** — clone, build and install the Binder SDK into `out/target/`. |
| `build_modules.sh` | **Stage 3** — compile the HAL libraries (`.so`) from each component's generated C++. The CMake configure step regenerates any missing sources. `build_modules.sh manifest` builds the set in `versions.yaml`. |
| `build_interfaces.sh` | **Admin / orchestration** — stages the Binder SDK then delegates the build to `build_modules.sh`; also test/clean helpers. |
| `release.sh` | Snapshot a component's `current/` into a versioned, controlled release directory (`<module>/<version>/`). |
| `check_aidl_changes.sh` | Hash-based detection of AIDL source changes. |
| `docs/build_docs.sh` | Build or serve the documentation site (mkdocs). |
| `freeze_interface.sh` | Legacy AIDL-freeze tooling — retained for reference, not used by the module-local release model. |

---

### Yocto Recipe Pattern

```bitbake
# Yocto dependency: linux-binder recipe provides SDK automatically
DEPENDS = "linux-binder"

do_configure() {
    # Compiler and flags are passed via environment variables
    # CMake will automatically use CC, CXX, CFLAGS, CXXFLAGS, LDFLAGS
    CC="${CC}" CXX="${CXX}" \
    CFLAGS="${CFLAGS}" CXXFLAGS="${CXXFLAGS}" LDFLAGS="${LDFLAGS}" \
    cmake -S ${S} -B ${B} \
          -DINTERFACE_TARGET=all \
          -DBINDER_SDK_DIR=${STAGING_DIR}${prefix} \
          -DBINDER_SDK_INCLUDE_DIR=${STAGING_DIR}${prefix}
}

do_compile() {
    cmake --build ${B} -j ${PARALLEL_MAKE}
}

do_install() {
    install -d ${D}${libdir}
    install -m 0755 ${B}/out/target/lib/halif/*.so ${D}${libdir}/

    # Note: Headers not needed on target (runtime only)
    # For development packages, create separate -dev recipe
}
```

**Compiler Configuration**:

The build system respects externally-defined compiler and flags through environment variables:

- **`CC`** - C compiler (e.g., `arm-linux-gnueabihf-gcc`)
- **`CXX`** - C++ compiler (e.g., `arm-linux-gnueabihf-g++`)
- **`CFLAGS`** - C compiler flags (e.g., `-O2 -march=armv7-a`)
- **`CXXFLAGS`** - C++ compiler flags (e.g., `-O2 -march=armv7-a -std=c++17`)
- **`LDFLAGS`** - Linker flags (e.g., `-Wl,--hash-style=gnu`)

These variables are automatically detected and applied by CMake when set in the environment.
Yocto's build system automatically provides these variables with appropriate cross-compilation settings.

## Configuration

### Production Build Variables (CMake)

Used when building HAL libraries for deployment:

| Variable                 | Purpose                           | Default      | Required |
|--------------------------|-----------------------------------|--------------|----------|
| `INTERFACE_TARGET`       | Module(s) to build                | `all`        | No       |
| `AIDL_SRC_VERSION`       | Version to build                  | `current`    | No       |
| `BINDER_SDK_DIR`         | linux_binder SDK libs location    | `out/target` | **Yes**  |
| `BINDER_SDK_INCLUDE_DIR` | linux_binder SDK headers location | `out/build`  | Yocto    |
| `OUT_DIR`                | Output directory                  | `out`        | No       |

`BINDER_SDK_DIR` and `BINDER_SDK_INCLUDE_DIR` differ only in the local dev
tree (libs in `out/target`, headers in `out/build`). A Yocto-staged SDK is
flat, so set both to the same staging prefix.

**Example**:

```bash
cmake -B build \
      -DINTERFACE_TARGET=boot \
      -DBINDER_SDK_DIR=/usr
```

### Development Build Variables (Scripts)

Used by `build_binder.sh` and `build_interfaces.sh` only:

| Variable            | Purpose                     | Default                 |
|---------------------|-----------------------------|-------------------------|
| `BINDER_SDK_DIR`    | Where to install SDK        | `out/target`            |
| `BINDER_SOURCE_DIR` | Existing binder source      | `build-tools/linux_...` |

**Not used in production Yocto builds**.

See [TWO_STAGE_BUILD.md](TWO_STAGE_BUILD.md) for detailed workflows.

## Additional Documentation

- **[build-tools/linux_binder_idl/BUILD.md](build-tools/linux_binder_idl/BUILD.md)** - Binder SDK recipe build guide
  - Yocto/BitBake recipe examples for linux-binder SDK
  - Cross-compilation configuration for ARM targets (aarch64, armhf)
  - Kernel configuration and runtime setup
  - Systemd service configuration
  - 32-bit userspace on 64-bit kernel support

- **[TWO_STAGE_BUILD.md](TWO_STAGE_BUILD.md)** - Detailed build workflows for both development and production

- **[tests/README.md](tests/README.md)** - On-demand build verification
  - `tests/smoke_test.sh` - exercises the `all`, `manifest` and per-version build paths
  - `tests/fake-yocto/` - emulates the Yocto production build offline

## Copyright and License

**RDK-HALIF-AIDL** is Copyright 2024 RDK Management and licensed under the
Apache License, Version 2.0. See the LICENSE and NOTICE files in the top-level
directory for further details.

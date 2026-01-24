# Linux Binder IDL — AI Agent Instructions

## Project Architecture

- **Purpose:** Port Android 13 Binder IPC (AOSP tag `android-13.0.0_r74`) to Linux for embedded/IoT, with strict separation between *target runtime* (for devices) and *host tools* (for codegen, never shipped).
- **Major outputs:**
  - `out/target/`: Binder runtime SDK (libs in `lib/`, binaries in `bin/`)
  - `out/build/include/`: SDK headers for building binder clients/services
  - `out/host/`: AIDL compiler tools (`aidl`, `aidl-cpp`) for x86_64 build host
  - `build-target/`: CMake build artifacts (temporary, not part of SDK)
- **AIDL codegen is *offline only*:** Architecture team generates C++ from `.aidl` using host tools, commits generated code. *Production builds never run codegen or ship host tools.*
- **Two-phase build design:** Core SDK (Android libs + servicemanager) is built once; AIDL compiler reuses these libs instead of rebuilding them.
- **Source management:** AOSP sources in `android/` cloned by `clone-android-binder-repo.sh`, patched via `patches/*.patch` - **never manually edit `android/` contents**.

## Build & Workflow Patterns

### Developer/Architecture Team (Wrapper Scripts)

- `build-linux-binder-aidl.sh`: Build target runtime (default: 64-bit, override with `TARGET_LIB32_VERSION=ON`)
  - Also builds host AIDL by default; use `no-host-aidl` to skip if already available
  - Respects Yocto environment: `CC`, `CXX`, `CFLAGS`, `CXXFLAGS`, `LDFLAGS`
  - Automatically passes these to CMake as `CMAKE_C_COMPILER`, `CMAKE_CXX_COMPILER`, `CMAKE_C_FLAGS`, etc.
- `build-aidl-generator-tool.sh`: Build host AIDL compiler (for codegen only)
- `build-binder-example.sh`: Build and test FWManager IPC example
- All scripts support both command styles: `clean` or `--clean`, `help` or `--help`

### Production/Yocto (Direct CMake)

**Critical:** *Never* use wrapper scripts in Yocto/BitBake recipes. Call CMake directly:

```bash
cmake -S . -B build-target \
  -DCMAKE_C_COMPILER=arm-linux-gnueabihf-gcc \
  -DCMAKE_CXX_COMPILER=arm-linux-gnueabihf-g++ \
  -DBUILD_HOST_AIDL=OFF \
  -DTARGET_LIB32_VERSION=ON \
  -DCMAKE_INSTALL_PREFIX=/usr/local
```

Required variables: `BUILD_HOST_AIDL=OFF`, and **one of** `TARGET_LIB64_VERSION=ON` or `TARGET_LIB32_VERSION=ON`.

### AIDL Code Generation Workflow

1. Architecture team builds AIDL compiler: `./build-aidl-generator-tool.sh`
2. Generate C++ from `.aidl`: `cd example && ./generate_cpp.sh` (use `clean` to regenerate)
3. Generated files are placed in `example/stable/generated/FWManager/` but **NOT committed** (gitignored)
4. Each developer must run `generate_cpp.sh` locally to create stubs/proxies
5. Production builds use pre-generated stubs from `binder_aidl_gen/` for Core SDK interfaces

### API Versioning & Dependencies

- **Python tools in `host/`** manage AIDL interface versions and dependencies:
  - `aidl_ops.py`: Main CLI for versioning operations (use `--help` for full options)
  - `aidl_interface.py`: Core interface version management logic
  - `aidl_api.py`: API snapshot comparison and validation
  - `interface-update.py`: Batch interface updates across multiple interfaces
- **Common operations:**
  - Update API: `./host/aidl_ops.py -u <interface-name>` - snapshot current API state
  - Freeze API: `./host/aidl_ops.py -f <interface-name>` - create new stable version
  - Generate sources: `./host/aidl_ops.py -g <interface-name>` - create C++ stubs/proxies
  - Dependency tree: `./host/aidl_ops.py -a` - analyze interface dependencies for build ordering
  - Specify roots: `-r "/path1;/path2"` - semicolon-separated interface root directories
  - Custom output: `-o /path/to/out` - override build/intermediate file directory
- **Interface definitions:** Each interface directory must contain:
  - `interface.yaml` or `interface.json` - version metadata and dependencies
  - `aidl/` subdirectory - `.aidl` source files
  - `aidl_api/<name>/` - frozen API snapshots (versioned directories)
- **Workflow example:**
  1. Modify `.aidl` files in `MyInterface/aidl/`
  2. Update API: `./host/aidl_ops.py -u MyInterface` (detect changes)
  3. Freeze version: `./host/aidl_ops.py -f MyInterface` (create v2, v3, etc.)
  4. Generate code: `./host/aidl_ops.py -g MyInterface -v 2` (specific version)
  5. Commit generated files to `stable/generated/` for production builds

## Key Conventions & Patterns

### CMake & Build System

- **No system headers:** CMake uses only Android headers from `android/` - system headers not needed
- **AOSP warning suppression:** All AOSP code warnings suppressed via `-w` and specific `-Wno-*` flags (lines 116–145 in CMakeLists.txt)
- **Separate build trees:** `build-host/` for AIDL compiler, `build-target/` for runtime libs (never mix)
- **AidlGenerator macro:** CMakeLists.txt defines macro for generating stubs/proxies (line 246+); used by examples but not production
- **Default architecture:** 64-bit auto-detected unless `TARGET_LIB32_VERSION=ON` explicitly set
- **Android source auto-clone:** CMake runs `clone-android-binder-repo.sh` if `android/` missing (lines 228–232)
- **Install rules:** Always enabled in CMakeLists.txt - Yocto/BitBake recipes handle installation via `do_install()`, not CMake install rules

### Source Code Management

- **AOSP sources:** Cloned by `clone-android-binder-repo.sh` from Google repos with tag `android-13.0.0_r74`
- **Patches applied automatically:** `patches/*.patch` files modify AOSP code during clone (aidl.patch, core.patch, libbase.patch, logging.patch, native.patch)
- **Never edit `android/` directly:** All modifications must go through patches; `android/` directory is gitignored
- **Re-clone to update patches:** Run `./clone-android-binder-repo.sh` again to apply new patch changes

### File Organization

- `android/`: AOSP sources (aidl, core, native, libbase, logging, fmtlib, googletest) - cloned, never modified directly
- `patches/*.patch`: Local changes to AOSP code, applied during `clone-android-binder-repo.sh`
- `setup-env.sh`: Shared environment variables and helper functions for all scripts
  - Defines core paths: `OUT_DIR`, `TARGET_SDK_DIR`, `SDK_INCLUDE_DIR`, `HOST_OUT_DIR`
  - Logging functions: `LOGI`, `LOGW`, `LOGE` (color-coded output)
  - Tool wrappers: `CMAKE`, `MAKE`, `GIT`, `TAR_BIN`
- `host/`: Python tooling for interface versioning (architecture team only)
  - `aidl_ops.py`: Main CLI for update-api, freeze-api, generate-source operations
  - `aidl_interface.py`, `aidl_api.py`: Interface version management
  - `interface-update.py`: Batch interface updates
- `example/FWManager/`: Reference IPC example with `.aidl` sources and generated C++
  - `FWManager/aidl/`: Source `.aidl` files
  - `stable/generated/FWManager/`: Committed generated code (production builds use this)
    - **Note:** `stable/generated/` is gitignored - generated files are NOT committed
    - Each project must run `generate_cpp.sh` to create stubs/proxies locally
  - `generate_cpp.sh`: Script showing AIDL invocation patterns
- `out/target/`: Installed target libraries/binaries
  - `lib/`: Shared libraries (`libbinder.so`, `libutils.so`, etc.)
  - `bin/`: Executables (`servicemanager`, example clients/services)
- `out/build/include/`: SDK headers (binder/, utils/, log/, android/, etc.) - used by downstream projects
- `out/host/`: Installed AIDL compiler tools
- `build-*/generated/`: Temporary generated files (gitignored, not committed)
- `build-target/`: CMake build directory for target SDK (temporary build artifacts)
- `build-host/`: CMake build directory for host AIDL tools (temporary build artifacts)
- `tools/`: Utility programs
  - `BinderDevice.c`: C program for creating binder device nodes
- `binder_aidl_gen/`: Pre-generated stubs for Core SDK binder (android/os/IServiceManager.aidl, etc.)
  - Used when `BUILD_HOST_AIDL=OFF` or in Yocto/production builds
  - Avoids circular dependency: Core SDK needs these stubs, but AIDL compiler needs Core SDK libs

### Kernel & Runtime Requirements

- **Kernel version:** 5.16+ with `CONFIG_ANDROID_BINDER_IPC=y`
- **32-bit userspace on 64-bit kernel:** Common in embedded; requires `CONFIG_ANDROID_BINDER_IPC_32BIT=y` in kernel
- **Binder device:** `/dev/binder` must exist (via binderfs or static device node)
- **Servicemanager:** Must run before any binder clients start; use systemd service in production
- **Systemd service:** `SYSTEMD_AUTO_ENABLE=enable` in Yocto ensures auto-start on boot

### Cross-Compilation & Architecture

- **Native builds (no env vars):** Script auto-detects system GCC - just run `./build-linux-binder-aidl.sh`
- **Cross-compilation (Yocto/embedded):** Set environment variables before invoking scripts:
  ```bash
  export CC=arm-linux-gnueabihf-gcc
  export CXX=arm-linux-gnueabihf-g++
  export CFLAGS="--sysroot=/path/to/sysroot -march=armv7-a"
  export CXXFLAGS="--sysroot=/path/to/sysroot -march=armv7-a"
  export LDFLAGS="--sysroot=/path/to/sysroot"
  export TARGET_LIB32_VERSION=ON
  ./build-linux-binder-aidl.sh
  ```
- **RDK sc docker build (production):** For RDK Kirkstone ARM builds:
  ```bash
  sc docker run rdk-kirkstone ". /opt/toolchains/rdk-glibc-x86_64-arm-toolchain/environment-setup-armv7vet2hf-neon-oe-linux-gnueabi; build_modules.sh sdk; build_modules.sh all"
  ```
  - This sources the RDK ARM toolchain and builds SDK + all modules
  - Output validates with ARM compiler: check `.so` files with `file` or `readelf -h` for ARM architecture
- **Direct CMake:** Pass compiler and flags explicitly (see Production/Yocto section above)
- `TARGET_LIB32_VERSION=ON` for 32-bit ARM/i686 targets
- `TARGET_LIB64_VERSION=ON` for 64-bit aarch64/x86_64 targets (default auto-detected)
- Never set both 32-bit and 64-bit flags simultaneously
- **32-bit userspace on 64-bit kernel:** Common in embedded systems for memory efficiency
  - Build with `TARGET_LIB32_VERSION=ON` even if kernel is 64-bit
  - Requires kernel config `CONFIG_ANDROID_BINDER_IPC_32BIT=y`
  - Match build to *userspace* architecture, not kernel architecture

## Testing & Validation

- **Quick validation:** `./test.sh` (~5-10 min) - comprehensive test suite with all validation
  - Supports selective testing: `--from ID`, `--to ID`, `--only ID[,ID...]`, `--list`
  - Example: `./test.sh --only 3,6,9` runs specific test IDs only
  - Example: `./test.sh --from 5 --to 8` runs tests 5 through 8
  - Use `--list` to see all available test IDs and descriptions
  - Covers: source cloning, builds, CMake direct builds, production builds, ARM cross-compilation validation
  - Test 11 validates ARM cross-compilation: verifies `out/` directory contains objects and `.so` files built with ARM compiler
  - Zero warnings/errors policy enforcement
  - **Toolchain management:** After any `clean_build_state()`, host AIDL tools are automatically rebuilt with host compiler (x86_64)
    - `ensure_host_aidl_tools()` saves/restores cross-compiler environment variables
    - Host tools (aidl/aidl-cpp) are always built with native host compiler, never cross-compiled
    - Production builds (test_8, test_9, test_10, test_11) use pre-generated code, don't need tools
    - Development builds (test_5, test_6, test_7) ensure tools are available before building
- **Build audit:** `./audit_build.sh` - verifies toolchain integrity and deployment readiness
  - Hermetic dependency check: ensures libs link locally, not against system `/usr/lib`
  - Orphan detection: identifies unused .so files in `lib/` directory
  - Deployment footprint: calculates stripped library sizes for embedded targets
  - Override SDK location: `BINDER_SDK_DIR=/custom/path ./audit_build.sh`
  - Essential for validating cross-compiled builds before deployment
- **Example IPC test:** `./build-binder-example.sh` - builds FWManager service/client, tests binder IPC
- **Clean builds:** Add `clean` to any build script (e.g., `./build-linux-binder-aidl.sh clean`)
- **Runtime testing:** Requires Linux 5.16+ with binder; see BUILD.md §"Testing" for Vagrant/KVM setup

## Common Pitfalls

- **Never** build or ship host AIDL tools in production Yocto builds (`BUILD_HOST_AIDL=OFF`)
- **Never** use wrapper scripts in BitBake recipes (use direct CMake invocation per BUILD.md)
- **Never** use both `TARGET_LIB32_VERSION` and `TARGET_LIB64_VERSION` simultaneously
- **Never** manually edit files in `android/` directory - use patches in `patches/*.patch` instead
- **Never** commit generated files to `stable/generated/` - these are gitignored and must be regenerated locally
- **Always** run `./example/generate_cpp.sh` before building examples (generates stubs/proxies from .aidl)
- **Always** set `CC`/`CXX`/`CFLAGS`/`CXXFLAGS`/`LDFLAGS` for cross-compilation (Yocto sets these automatically)
- **Always** ensure CFLAGS/CXXFLAGS/LDFLAGS include sysroot when cross-compiling
- **Native builds:** Leave CC/CXX unset to use system GCC (CMake auto-detects from build-essential)
- **Remember** servicemanager must start before binder clients (systemd dependency ordering - see BUILD.md §"Runtime Setup")
- **Remember** to re-run `./clone-android-binder-repo.sh` after modifying any `.patch` files in `patches/`
- **Remember** host AIDL tools (aidl/aidl-cpp) are always built with host compiler, never cross-compiled (test suite handles this automatically)
- **Debugging builds:** Use `BUILD_TYPE=Debug` environment variable, examine CMake logs in `build-*/CMakeCache.txt`
- **Architecture confusion:** Match build to *userspace* architecture, not kernel (32-bit userspace on 64-bit kernel is common in embedded)

## Reference Files

- [BUILD.md](../BUILD.md): Authoritative build guide - Yocto integration, CMake variables, runtime setup
- [README.md](../README.md): Quick start, build commands, output structure
- [example/generate_cpp.sh](../example/generate_cpp.sh): AIDL codegen workflow reference
- [host/aidl_ops.py](../host/aidl_ops.py): Interface versioning CLI (run with `--help`)
- [CMakeLists.txt](../CMakeLists.txt): Core build logic - see lines 116–145 (warnings), 246+ (AidlGenerator macro)
- [clone-android-binder-repo.sh](../clone-android-binder-repo.sh): AOSP source management and patching
- [setup-env.sh](../setup-env.sh): Shared environment setup for all build scripts
- [build-linux-binder-aidl.sh](../build-linux-binder-aidl.sh): Canonical target build script - supports native and cross-compilation
- [test.sh](../test.sh): Fast validation test suite with selective test execution
- [CHANGELOG.md](../CHANGELOG.md): Version history - latest is 1.1.0 with AIDL versioning support

---
**AI agents:** Follow these conventions strictly. When in doubt:
1. Check [BUILD.md](../BUILD.md) for build system and Yocto integration
2. Check [README.md](../README.md) for quick start and workflow
3. Read script `--help` output for usage patterns
4. Never modify `android/` contents directly - use patches in `patches/` directory

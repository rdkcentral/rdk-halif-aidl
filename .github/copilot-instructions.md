out/
# Linux Binder IDL — AI Agent Instructions

## Project Architecture

- **Purpose:** Port Android 13 Binder IPC to Linux for embedded/IoT, with strict separation between *target runtime* (for devices) and *host tools* (for codegen, never shipped).
- **Major outputs:**
  - `out/target/`: Binder runtime libraries (e.g., `libbinder.so`, `servicemanager`) for ARM/embedded
  - `out/host/`: AIDL compiler tools (`aidl`, `aidl-cpp`) for x86_64 build host
- **AIDL codegen is *offline only*:** Architecture team generates C++ from `.aidl` using host tools, commits generated code. *Production builds never run codegen or ship host tools.*
- **Two-phase build design:** Core SDK (Android libs + servicemanager) is built once; AIDL compiler reuses these libs instead of rebuilding them.

## Build & Workflow Patterns

### Developer/Architecture Team (Wrapper Scripts)

- `build-linux-binder-aidl.sh`: Build target runtime (default: 64-bit, override with `TARGET_LIB32_VERSION=ON`)
- `build-aidl-generator-tool.sh`: Build host AIDL compiler (for codegen only)
- `build-binder-example.sh`: Build and test FWManager IPC example
- All scripts support `--clean` and `--help` flags

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
2. Generate C++ from `.aidl`: `cd example && ./generate_cpp.sh` (see this script for invocation patterns)
3. Commit generated `.cpp`/`.h` files to `example/stable/generated/FWManager/`
4. Production builds compile pre-generated C++ only (no runtime codegen)

### API Versioning & Dependencies

- Python tools in `host/` manage interface versions: `aidl_ops.py`, `aidl_interface.py`, `aidl_api.py`
- Usage: `./host/aidl_ops.py -u|-f|-g <interface-name>` (update-api, freeze-api, generate-source)
- Dependency tree generation: `./host/aidl_ops.py -a` (for build ordering)
- Interface definitions: `interface.yaml` or `interface.json` in interface directories

## Key Conventions & Patterns

### CMake & Build System

- **No system headers:** CMake explicitly disables `/usr/include` (lines 140+ in CMakeLists.txt); only uses Android headers from `android/`
- **AOSP warning suppression:** All AOSP code warnings suppressed via `-w` and specific `-Wno-*` flags (lines 90–110)
- **Separate build trees:** `build-host/` for AIDL compiler, `build-target/` for runtime libs (never mix)
- **AidlGenerator macro:** CMakeLists.txt defines macro for generating stubs/proxies (line 242+); used by examples but not production

### File Organization

- `android/`: AOSP sources (aidl, core, native, libbase, logging, fmtlib, googletest) - cloned, never modified
- `patches/*.patch`: Local changes to AOSP code, applied during `clone-android-binder-repo.sh`
- `host/`: Python tooling for interface versioning (architecture team only)
- `example/FWManager/`: Reference IPC example with `.aidl` sources and generated C++
- `example/stable/generated/`: Committed generated code (production builds use this)
- `out/target/`: Installed target libraries/binaries
- `out/host/`: Installed AIDL compiler tools
- `build-*/generated/`: Temporary generated files (gitignored, not committed)

### Kernel & Runtime Requirements

- **Kernel version:** 5.16+ with `CONFIG_ANDROID_BINDER_IPC=y`
- **32-bit userspace on 64-bit kernel:** Common in embedded; requires `CONFIG_ANDROID_BINDER_IPC_32BIT=y` in kernel
- **Binder device:** `/dev/binder` must exist (via binderfs or static device node)
- **Servicemanager:** Must run before any binder clients start; use systemd service in production
- **Systemd service:** `SYSTEMD_AUTO_ENABLE=enable` in Yocto ensures auto-start on boot

### Cross-Compilation & Architecture

- Set `CC`/`CXX` environment variables for target compiler (e.g., `arm-linux-gnueabihf-gcc`)
- `TARGET_LIB32_VERSION=ON` for 32-bit ARM/i686 targets
- `TARGET_LIB64_VERSION=ON` for 64-bit aarch64/x86_64 targets (default auto-detected)
- Never set both 32-bit and 64-bit flags simultaneously

## Testing & Validation

- **Quick validation:** `./quick_test.sh` (~5-10 min) - validates clone, build, outputs
- **Comprehensive test:** `./test_build.sh` (~10-20 min) - full validation suite with zero-warnings check
- **Example IPC test:** `./build-binder-example.sh` - builds FWManager service/client, tests binder IPC
- **Runtime testing:** Requires Linux 5.16+ with binder; see BUILD.md §"Testing" for Vagrant/KVM setup

## Common Pitfalls

- **Never** build or ship host AIDL tools in production Yocto builds
- **Never** use wrapper scripts in BitBake recipes (use direct CMake invocation)
- **Never** use both `TARGET_LIB32_VERSION` and `TARGET_LIB64_VERSION` simultaneously
- **Never** allow `/usr/include` in compile commands (CMake explicitly disables this)
- **Always** commit AIDL-generated C++ to `stable/generated/`; never generate at production build time
- **Always** set `CC`/`CXX` for target architecture, not host (host AIDL compiler uses system default)
- **Remember** servicemanager must start before binder clients (systemd dependency ordering)

## Reference Files

- [BUILD.md](../BUILD.md): Authoritative build guide - Yocto integration, CMake variables, runtime setup
- [README.md](../README.md): Quick start, build commands, output structure
- [example/generate_cpp.sh](../example/generate_cpp.sh): AIDL codegen workflow reference
- [host/aidl_ops.py](../host/aidl_ops.py): Interface versioning CLI (run with `--help`)
- [CMakeLists.txt](../CMakeLists.txt): Core build logic - see lines 90–110 (warnings), 240+ (AidlGenerator)
- [clone-android-binder-repo.sh](../clone-android-binder-repo.sh): AOSP source management and patching

---
**AI agents:** Follow these conventions strictly. When in doubt:
1. Check [BUILD.md](../BUILD.md) for build system and Yocto integration
2. Check [README.md](../README.md) for quick start and workflow
3. Read script `--help` output for usage patterns

out/
# Linux Binder IDL — AI Agent Instructions

## Project Architecture

- **Purpose:** Port Android 13 Binder IPC to Linux for embedded/IoT, with strict separation between *target runtime* (for devices) and *host tools* (for codegen, never shipped).
- **Major outputs:**
  - `out/target/`: Binder runtime libraries (e.g., `libbinder.so`, `servicemanager`) for ARM/embedded
  - `out/host/`: AIDL compiler tools (`aidl`, `aidl-cpp`) for x86_64 build host
- **AIDL codegen is *offline only*:** Architecture team generates C++ from `.aidl` using host tools, commits generated code. *Production builds never run codegen or ship host tools.*

## Build & Workflow Patterns

- **Wrapper scripts:**
  - `build-linux-binder-aidl.sh`: Build target runtime (default: 64-bit, override with `TARGET_LIB32_VERSION=ON`)
  - `build-aidl-generator-tool.sh`: Build host AIDL compiler (for codegen only)
  - `build-binder-example.sh`: Build and test FWManager IPC example
- **Production/Yocto:** *Never* use wrapper scripts; call CMake directly with `BUILD_CORE_SDK=ON`, `BUILD_HOST_AIDL=OFF`, and set one of `TARGET_LIB64_VERSION`/`TARGET_LIB32_VERSION`.
- **AIDL codegen:** See `example/generate_cpp.sh` for how to invoke `aidl` and where to place generated files. Generated C++ must be committed.
- **API versioning:** Python tools in `host/` (e.g., `aidl_ops`, `aidl_interface.py`) manage interface versioning and dependency graphs. See comments in those files for usage.

## Key Conventions & Patterns

- **No system headers:** CMake disables `/usr/include` and uses only Android headers from `android/` (see `CMakeLists.txt` and `clone-android-binder-repo.sh`).
- **Suppress AOSP warnings:** All Android code warnings are suppressed in CMake (see lines 90–110 of `CMakeLists.txt`).
- **Patches:** All AOSP code is unmodified; local changes are in `patches/*.patch` and applied at clone time.
- **File layout:**
  - `android/`: AOSP sources (aidl, core, native, etc.)
  - `host/`: Python versioning tools
  - `example/`: FWManager reference, with `.aidl` and generated C++
  - `out/`: Build outputs

## Testing & Validation

- **Quick test:** `./quick_test.sh` validates clone, build, and outputs
- **Example test:** `./build-binder-example.sh` builds and runs FWManager IPC demo
- **Runtime:** Requires Linux 5.16+ with binder enabled; see [BUILD.md](../BUILD.md) for kernel/device setup

## Common Pitfalls

- Never build or ship host AIDL tools in production
- Never use both `TARGET_LIB32_VERSION` and `TARGET_LIB64_VERSION` at once
- Never allow `/usr/include` in compile commands (see CMake flags)
- Always commit generated C++ from AIDL; never generate at build time
- For cross-compilation, set `CC`/`CXX` for target, not host

## Reference Files

- [README.md](../README.md): Quick start, build, and test
- [BUILD.md](../BUILD.md): Full build, Yocto, and runtime details
- [example/generate_cpp.sh](../example/generate_cpp.sh): AIDL codegen workflow
- [host/aidl_ops.py](../host/aidl_ops.py): API versioning CLI

---
**AI agents:** Follow these conventions strictly. If unsure, prefer reading [BUILD.md](../BUILD.md) and [README.md](../README.md) for authoritative project rules.


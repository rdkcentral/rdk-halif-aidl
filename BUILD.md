# Linux Binder Build Guide

## Build Structure

This repository provides **two separate builds**:

1. **Host Tools** (`out/host/`) - AIDL compiler tools for code generation
2. **Target Libraries** (`out/target/`) - Binder runtime libraries for embedded devices

```bash
out/
├── host/              # Host tools (x86_64 build machine)
│   └── bin/
│       ├── aidl       # AIDL compiler
│       └── aidl-cpp   # C++ AIDL compiler
└── target/            # Target libraries (ARM/device architecture)
    ├── bin/
    │   └── servicemanager
    ├── lib/
    │   ├── libbinder.so
    │   ├── liblog.so
    │   └── ...
    └── include/       # Binder headers
```

## Prerequisites

- Ubuntu 22.04 LTS (or similar)
- CMake 3.22.1 or later
- GCC 11.2.0 or later (GCC 9.4.0 minimum)
- For cross-compilation: ARM toolchain (e.g., `arm-linux-gnueabihf-gcc`)

## Building Host Tools

Host tools run on your **build machine** (typically x86_64) to generate code from AIDL interfaces.

```bash
./build-aidl-generator-tool.sh

# Clean build (removes build-host/ and out/host/ first)
./build-aidl-generator-tool.sh --clean

# Show help
./build-aidl-generator-tool.sh --help
```

**Output:**

- `out/host/bin/aidl` - AIDL compiler
- `out/host/bin/aidl-cpp` - C++ AIDL compiler

**Compiler Selection:**
Uses system default `gcc/g++`. Override if needed:

```bash
export CC=gcc-11
export CXX=g++-11
./build-aidl-generator-tool.sh
```

## Building Target Libraries

Target libraries run on your **embedded device** (typically ARM).

### Native Build (x86_64 target)

For local testing or x86_64 targets:

```bash
./build-linux-binder-aidl.sh

# Clean build (removes build-target/ and out/target/ first)
./build-linux-binder-aidl.sh --clean

# Show help
./build-linux-binder-aidl.sh --help
```

### Cross-Compilation (ARM target)

For ARM embedded devices:

```bash
export CC=arm-linux-gnueabihf-gcc
export CXX=arm-linux-gnueabihf-g++
export TARGET_LIB32_VERSION=ON  # For 32-bit ARM
./build-linux-binder-aidl.sh
```

**Output:**

- `out/target/lib/libbinder.so` - Core binder library
- `out/target/lib/liblog.so`, `libbase.so`, etc. - Support libraries
- `out/target/bin/servicemanager` - Binder service manager
- `out/target/include/` - Headers for building binder clients/services

## Build Options

### Environment Variables

| Variable | Description | Default |
|----------|-------------|---------|
| `CC` | C compiler | System default |
| `CXX` | C++ compiler | System default |
| `BUILD_TYPE` | `Debug` or `Release` | `Release` |
| `TARGET_LIB32_VERSION` | Build 32-bit target | `OFF` |

### Examples

**Debug build for host tools:**

```bash
BUILD_TYPE=Debug ./build-aidl-generator-tool.sh
```

**32-bit ARM target:**

```bash
export CC=arm-linux-gnueabihf-gcc
export CXX=arm-linux-gnueabihf-g++
export TARGET_LIB32_VERSION=ON
./build-linux-binder-aidl.sh
```

## Integration with Yocto/Bitbake

### Production Build (CMake Direct)

For Yocto/BitBake recipes, call CMake directly with appropriate variables. The wrapper scripts are for manual/development builds only.

**Production builds only require TARGET libraries** - the AIDL compiler is used offline by the architecture team to generate interface code, which is then committed to the repository.

**BitBake Recipe Example:**

```bitbake
inherit cmake

# Production recipe - build binder runtime libraries only
DEPENDS = ""

EXTRA_OECMAKE = " \
    -DBUILD_CORE_SDK=ON \
    -DBUILD_HOST_AIDL=OFF \
    -DTARGET_LIB64_VERSION=${@bb.utils.contains('TUNE_FEATURES', 'aarch64', 'ON', 'OFF', d)} \
"

do_install() {
    cmake --install ${B} --prefix ${D}${prefix}
}

FILES_${PN} += "${libdir}/lib*.so*"
FILES_${PN}-dev += "${includedir}/*"
```

**Key Points:**

- **Production builds**: Only build target runtime libraries (`BUILD_CORE_SDK=ON`, `BUILD_HOST_AIDL=OFF`)
- **No AIDL compiler needed**: Architecture team generates C++ code offline using AIDL compiler
- **Pre-generated code committed**: All AIDL-generated C++ files are in source control
- **No code generation at build time**: Production builds compile pre-generated C++ only

### CMake Variables Reference

| Variable | Description | Default | Production Value |
|----------|-------------|---------|------------------|
| `BUILD_CORE_SDK` | Build target binder libraries | `ON` | `ON` |
| `BUILD_HOST_AIDL` | Build host AIDL compiler (architecture team only) | `ON` | `OFF` |
| `TARGET_LIB64_VERSION` | Build 64-bit libraries | Auto-detect | Per architecture |
| `TARGET_LIB32_VERSION` | Build 32-bit libraries | `ON` | Per architecture |
| `CMAKE_INSTALL_PREFIX` | Installation root | `/usr/local` | Yocto staging path |

**Note:** `BUILD_HOST_AIDL=ON` is only used by the architecture team for offline interface generation. Production builds always use `BUILD_HOST_AIDL=OFF`.

### Manual/Development Build (Wrapper Scripts)

For developers building manually, convenience scripts are provided:

**Host tools:**

```bash
./build-aidl-generator-tool.sh
```

**Target libraries:**

```bash
./build-linux-binder-aidl.sh

# Cross-compile for ARM
CC=arm-linux-gnueabihf-gcc CXX=arm-linux-gnueabihf-g++ \
    ./build-linux-binder-aidl.sh
```

These wrapper scripts simply invoke CMake with appropriate defaults.

## Clean Builds

Both build scripts support the `--clean` flag:

```bash
# Clean and rebuild host tools
./build-aidl-generator-tool.sh --clean

# Clean and rebuild target libraries
./build-linux-binder-aidl.sh --clean

# Or manually clean specific components:
rm -rf build-host out/host/      # Clean host only
rm -rf build-target out/target/  # Clean target only
rm -rf build-host build-target out/  # Clean everything
```

## Troubleshooting

### Missing kernel headers

The repository includes Android kernel headers in `android/bionic/libc/kernel/`.
If you see "binder.h not found", the CMake configuration is incorrect.

### Cross-compilation fails

Ensure your cross-compiler toolchain is properly configured:

```bash
${CC} --version
${CXX} --version
```

### Libraries not found during linking

The CMake build should be self-contained. If you see missing library errors,
ensure you're building with `BUILD_CORE_SDK=ON` (default in both scripts).

## Architecture Notes

- **Host tools are architecture-independent** - They generate code, not run on target
- **Target libraries must match device architecture** - ARM, x86_64, etc.
- **No mixing** - Host and target use separate build directories
- **Kernel headers included** - Self-contained build, no system dependencies

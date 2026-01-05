# Linux Binder Build Guide

## Build Structure

This repository provides **two separate builds**:

1. **Host Tools** (`out/host/`) - AIDL compiler tools for code generation
2. **Target Libraries** (`out/target/`) - Binder runtime libraries for embedded devices

```
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

When building through Yocto, the build system will:

1. **Set compilers automatically:**
   - `CC` and `CXX` point to cross-compiler
   - Sysroot and flags configured by Yocto

2. **Build host tools first** (native):
   ```bash
   do_compile_prepend() {
       # Build host tools with native compiler
       ./build-aidl-generator-tool.sh
   }
   ```

3. **Build target libraries** (cross-compiled):
   ```bash
   do_compile() {
       # CC/CXX already set by Yocto
       ./build-linux-binder-aidl.sh
   }
   ```

4. **Install appropriately:**
   - Host tools → `${STAGING_BINDIR_NATIVE}/`
   - Target libs → `${D}${libdir}/`
   - Headers → `${D}${includedir}/`

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

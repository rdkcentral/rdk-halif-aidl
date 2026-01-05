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

## Runtime Setup and Installation

### Prerequisites for Target Device

#### Kernel Requirements

The target device kernel must have Binder support enabled. Required kernel config:

```kconfig
CONFIG_ANDROID=y
CONFIG_ANDROID_BINDER_IPC=y
CONFIG_ANDROID_BINDER_DEVICES="binder,hwbinder,vndbinder"
CONFIG_ANDROID_BINDER_IPC_32BIT=y       # For 32-bit systems
# CONFIG_ANDROID_BINDER_IPC_SELFTEST is not set
CONFIG_ASHMEM=y
CONFIG_ANDROID_BINDERFS=y               # Required for Ubuntu/desktop Linux
```

**Note:** Some Ubuntu kernels (5.16.20) have SELinux context issues with binder. A patch may be required for `drivers/android/binder.c`.

Refer to: <https://www.kernel.org/doc/html/latest/admin-guide/binderfs.html>

#### Creating Binder Device Nodes

On systems using `binderfs`:

```bash
# Mount binderfs (typically done at boot)
mkdir -p /dev/binderfs
mount -t binder binder /dev/binderfs

# Create binder device
echo binder > /dev/binderfs/binder-control

# Set permissions
chmod 0666 /dev/binderfs/binder

# Create legacy symlink for compatibility
ln -sf /dev/binderfs/binder /dev/binder
```

For systems with static binder device:

```bash
# Device node should exist at /dev/binder
ls -l /dev/binder
# Expected: crw-rw-rw- 1 root root 10, 57 ...
```

### Installing Built Libraries

After building, install to target filesystem:

```bash
# Install to system directories (requires root)
sudo cmake --install build-target --prefix /usr/local

# Or install to staging directory for packaging
cmake --install build-target --prefix ${STAGING_DIR}/usr
```

Installed files:

- Libraries: `/usr/local/lib/lib{binder,utils,log,base,cutils}.so`
- Binaries: `/usr/local/bin/servicemanager`
- Headers: `/usr/local/include/{binder,utils,log,cutils}/`

### Systemd Service Configuration

The Binder `servicemanager` should run as a system service. Create `/etc/systemd/system/servicemanager.service`:

```ini
[Unit]
Description=Android Binder Service Manager
Documentation=https://source.android.com/docs/core/architecture/hidl/binder-ipc
After=local-fs.target
Before=basic.target

[Service]
Type=simple
ExecStart=/usr/local/bin/servicemanager
Restart=on-failure
RestartSec=5
StandardOutput=journal
StandardError=journal
# Ensure binder device is available
DeviceAllow=/dev/binder rw
DeviceAllow=/dev/binderfs/binder rw

[Install]
WantedBy=multi-user.target
```

Enable and start the service:

```bash
sudo systemctl daemon-reload
sudo systemctl enable servicemanager.service
sudo systemctl start servicemanager.service
sudo systemctl status servicemanager.service
```

### Runtime Library Path

Client applications need to find binder libraries at runtime:

**Option 1: System library path (recommended for production)**

```bash
# Libraries installed to /usr/local/lib are automatically found
sudo ldconfig
```

**Option 2: LD_LIBRARY_PATH (development only)**

```bash
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
```

**Option 3: Yocto/BitBake (handled automatically)**

- Libraries installed to `${libdir}` are in the standard search path

### Verification

Test the installation:

```bash
# Check servicemanager is running
systemctl status servicemanager.service

# Check binder device
ls -l /dev/binder

# List registered services (requires binder client tools)
# servicemanager should show empty list initially
```

## Yocto/BitBake Recipe Migration

### Updated Recipe Template

Here's the modernized BitBake recipe for the current build system:

```bitbake
DESCRIPTION = "Android Binder IPC for Linux"
SECTION = "libs"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

# Source repository
SRC_URI = "git://github.com/your-org/linux_binder_idl.git;protocol=https;branch=main"
SRC_URI += "file://servicemanager.service"

SRCREV = "${AUTOREV}"
S = "${WORKDIR}/git"

# Build dependencies
DEPENDS = ""

# Use CMake
inherit cmake systemd

# CMake configuration - production target build only
EXTRA_OECMAKE = " \
    -DBUILD_CORE_SDK=ON \
    -DBUILD_HOST_AIDL=OFF \
    -DTARGET_LIB64_VERSION=${@bb.utils.contains('TUNE_FEATURES', 'aarch64', 'ON', 'OFF', d)} \
    -DTARGET_LIB32_VERSION=${@bb.utils.contains('TUNE_FEATURES', 'aarch64', 'OFF', 'ON', d)} \
    -DCMAKE_INSTALL_PREFIX=${prefix} \
"

# Clone Android sources before CMake configuration
do_configure:prepend() {
    cd ${S}
    ${S}/clone-android-binder-repo.sh
}

# Install systemd service
do_install:append() {
    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/servicemanager.service ${D}${systemd_unitdir}/system/
}

# Systemd integration
SYSTEMD_SERVICE:${PN} = "servicemanager.service"
SYSTEMD_AUTO_ENABLE:${PN} = "enable"

# Package files
FILES:${PN} = " \
    ${libdir}/lib*.so* \
    ${bindir}/servicemanager \
    ${systemd_unitdir}/system/servicemanager.service \
"

FILES:${PN}-dev = " \
    ${includedir}/* \
"

# Allow shared libraries in main package
FILES_SOLIBSDEV = ""

# Skip dev-elf checks (expected for binder libraries)
INSANE_SKIP:${PN} = "dev-deps"
INSANE_SKIP:${PN}-dev = "dev-elf"
```

### Key Changes from Legacy Recipe

**Removed:**

- ❌ `setup-env.sh` sourcing
- ❌ Manual `clone_android_binder_repo` function call
- ❌ `BUILD_ENV_YOCTO` flag (no longer exists)

**Added:**

- ✅ `BUILD_CORE_SDK=ON` / `BUILD_HOST_AIDL=OFF` flags
- ✅ `clone-android-binder-repo.sh` script invocation
- ✅ `TARGET_LIB64_VERSION` / `TARGET_LIB32_VERSION` based on architecture
- ✅ `SYSTEMD_AUTO_ENABLE` for automatic service enablement

**Unchanged:**

- CMake inheritance
- Systemd service installation
- Package file lists

### Creating the Systemd Service File

Create `files/servicemanager.service`:

```ini
[Unit]
Description=Android Binder Service Manager
Documentation=https://source.android.com/docs/core/architecture/hidl/binder-ipc
After=local-fs.target
Before=basic.target
Requires=dev-binder.device
After=dev-binder.device

[Service]
Type=simple
ExecStart=/usr/bin/servicemanager
Restart=on-failure
RestartSec=5
StandardOutput=journal
StandardError=journal
SyslogIdentifier=servicemanager

# Security hardening
NoNewPrivileges=true
PrivateTmp=true
ProtectSystem=strict
ProtectHome=true
ReadWritePaths=/dev/binder /dev/binderfs

# Device access
DeviceAllow=/dev/binder rw
DeviceAllow=/dev/binderfs/binder rw

[Install]
WantedBy=multi-user.target
```

### Testing the Yocto Build

```bash
# Build the recipe
bitbake linux-binder-idl

# Check installed files
oe-pkgdata-util list-pkg-files linux-binder-idl

# Test on target device
ssh root@target
systemctl status servicemanager
ls -l /dev/binder
ldd /usr/bin/servicemanager
```

### Native Recipe (Architecture Team Only)

If you need the AIDL compiler for code generation:

```bitbake
DESCRIPTION = "AIDL Compiler for Android Binder"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"

SRC_URI = "git://github.com/your-org/linux_binder_idl.git;protocol=https;branch=main"
SRCREV = "${AUTOREV}"
S = "${WORKDIR}/git"

inherit cmake native

# Build AIDL compiler only (host tools)
EXTRA_OECMAKE = " \
    -DBUILD_CORE_SDK=OFF \
    -DBUILD_HOST_AIDL=ON \
"

do_configure:prepend() {
    ${S}/clone-android-binder-repo.sh
}

BBCLASSEXTEND = "native"
```

This native recipe produces `aidl` and `aidl-cpp` compilers for the build host.

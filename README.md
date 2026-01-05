# Linux Binder IDL

This project aims to build and test the Android Binder for the Linux desktop environment.
The Android 13 AOSP source code is cloned from `Google's` repositories. The Android tag
 is __*android-13.0.0_r74*__, and the code has been modified to make it compatible with Linux.
The project is primarily designed to build the binder runtime libraries for embedded devices.
It also provides the `aidl` compiler for the architecture team to generate interface code offline.
The default binder libraries generated are 64-bit, but this can be overridden using CMake variables.

**For comprehensive build documentation, see [BUILD.md](BUILD.md).**

---

# Revision History

 |Date        |Component       |Version                       |Description                                             |
 |------------|----------------|------------------------------|--------------------------------------------------------|
 |22/11/2023  |AOSP            |android-13.0.0_r74            |AOSP tag android-13.0.0_r74 checkout out from Google    |
 |22/11/2023  |Binder          |android-13.0.0_r74+1.0.0      |Initial version of linux binder                         |

---

# Table of Contents

- [Prerequisites](#prerequisites)
    - [Enable Binder Support in Kernel](#enable-binder-support-in-kernel)
- [Build Steps](#build-steps)
    - [Build Binder Framework](#build-binder-framework)
    - [Build Binder Example](#build-binder-example)
    - [Build AIDL generator tool](#build-aidl-generator-tool)
        - [AIDL Generator Tool Usage](#aidl-generator-tool-usage)
- [Build Options](#build-options)
    - [Quick Build Commands](#quick-build-commands)
    - [CMake Build Variables](#cmake-build-variables)
    - [Clean Builds](#clean-builds)
- [Output](#output)
- [Testing](#testing)
    - [Using Vagrant Box](#using-vagrant-box)
    - [Using KVM](#using-kvm)

---

# Prerequisites

- Ubuntu 22.04 LTS machine
- Linux Kernel 5.16.x with binder enabled (Tested with 5.16.20)
- CMake is used as a build system. CMake Version 3.22.1.
- GCC Version 11.2.0 (minimum required GCC Version is 9.4.0)

## Enable Binder Support in Kernel

Linux kernel's Binder must be enabled. Please refer https://www.kernel.org/doc/html/latest/admin-guide/binderfs.html for more infromation .

```
CONFIG_ANDROID=y
CONFIG_ANDROID_BINDER_IPC=y
CONFIG_ANDROID_BINDER_DEVICES="binder,hwbinder,vndbinder"
CONFIG_ANDROID_BINDER_IPC_32BIT=y (if only supports 32bit binder)
# CONFIG_ANDROID_BINDER_IPC_SELFTEST is not set
CONFIG_ASHMEM=y
CONFIG_ANDROID_BINDERFS=y (only needed for ubuntu)
```

Note : In Ubuntu-22.04 5.16.20 kernel, observed binder driver security context access issue while binder client trying to communicate with the binder Service. 
To fix this, patched the drivers/android/binder.c file.

---

# Build Steps

Following are the build steps to build the binder framework, binder examples and aidl generator tool.


## Build Binder Framework

### Run below command to generate binder libs, header files and servicemanager.
```bash
$ ./build-linux-binder-aidl.sh
```

#### Following are the generated files as part of the binder framework (in `out/target/`):

    out/target/
    ├── bin/
    │   └── servicemanager
    ├── include/
    │   └── *.h
    └── lib/
        ├── libbase.so
        ├── libbinder.so
        ├── libcutils.so
        ├── libcutils_sockets.so
        ├── liblog.so
        └── libutils.so

## Build Binder Example

Following are the build steps to build the binder examples. This builds the binder framework first and the binder examples.

### Run below command to build binder example
```bash
$ ./build-binder-example.sh
```

#### Following are the libraries and binaries generated as part of binder example (in `out/target/`):

    out/target/
    ├── bin/
    │   ├── FWManagerService
    │   └── FWManagerClient
    └── lib/
        └── libfwmanager.so

## Build AIDL generator tool

**Note:** The AIDL compiler is only used by the architecture team for offline interface code generation. Production builds do NOT require building or installing the AIDL compiler.

### Run below command to build aidl generator tool
```bash
$ ./build-aidl-generator-tool.sh
```

#### Following are the generated files (in `out/host/`):

    out/host/
    ├── bin/
    │   ├── aidl
    │   └── aidl-cpp
    └── tarball/
        └── aidl-gen-tool-android-13.0.0_r74+1.0.0.tar.bz2

Note: The AIDL generator tool is built and tested only on x86 machines. The tarball version can be updated using `${AIDL_GENERATOR_TARBALL}`.

The Google prebuilt AIDL generator tool for host machine is available at: <https://android.googlesource.com/platform/prebuilts/build-tools>


### AIDL Generator Tool Usage

An example to generate the `stubs and proxies` from an `.aidl` file using `aidl` generator tool

```
aidl --lang=cpp -I${WORKDIR} "${WORKDIR}/${SRC_DIR}" --header_out ${GEN_DIR}/${AIDL_NAME}/include -o ${GEN_DIR}/${AIDL_NAME}

FWManager Example:

$ aidl --lang=cpp -I. com/test/IFirmwareUpdateStateListener.aidl --header_out gen/FWManager/include -o gen/FWManager
$ aidl --lang=cpp -I. com/test/FirmwareStatus.aidl --header_out gen/FWManager/include -o gen/FWManager
$ aidl --lang=cpp -I. com/test/IFWManager.aidl --header_out gen/FWManager/include -o gen/FWManager

The stubs and proxies are generated in gen/FWManager and gen/FWManager/include
```
---

# Build Options

The build system uses CMake and provides wrapper scripts for convenience during development.

## Quick Build Commands

All wrapper scripts support `--help` and `--clean` options:

```bash
# Build target SDK (libraries + servicemanager)
$ ./build-linux-binder-aidl.sh [--clean]

# Build examples (includes SDK build)
$ ./build-binder-example.sh [--clean] [--clean-aidl]

# Build AIDL compiler (architecture team only)
$ ./build-aidl-generator-tool.sh [--clean]
```

**For production Yocto/BitBake integration, see [BUILD.md](BUILD.md).**

## CMake Build Variables

**For production Yocto/BitBake usage, see [BUILD.md](BUILD.md) for complete documentation.**

### Core Build Options

| Variable | Description | Default | Values |
|----------|-------------|---------|--------|
| `BUILD_CORE_SDK` | Build target binder runtime libraries | `ON` | `ON`/`OFF` |
| `BUILD_HOST_AIDL` | Build AIDL compiler (architecture team only) | `ON` | `ON`/`OFF` |
| `TARGET_LIB64_VERSION` | Build 64-bit libraries | Auto-detect | `ON`/`OFF` |
| `TARGET_LIB32_VERSION` | Build 32-bit libraries | `ON` | `ON`/`OFF` |
| `CMAKE_INSTALL_PREFIX` | Installation root | `out/target/` | Path |

### Additional Options

- `BUILD_SHARED_LIB` - Build shared libraries (default: `ON`)
- `BUILD_STATIC_LIB` - Build static libraries (default: `OFF`)
- `USE_PREBUILT_GEN_FILES` - Use pre-generated AIDL stubs for examples
- `BUILD_USING_AIDL_UTILITY` - Generate AIDL code at build time
- `BUILD_BINDER_DEVICE_UTILITY` - Build binder-device utility for Ubuntu

### Example CMake Usage

```bash
# Standard production build (target libraries only)
cmake -DBUILD_CORE_SDK=ON -DBUILD_HOST_AIDL=OFF .
make
make install

# Architecture team: build AIDL compiler only
cmake -DBUILD_CORE_SDK=OFF -DBUILD_HOST_AIDL=ON .
make
make install
```

## Clean Builds

All wrapper scripts support the `--clean` flag:

```bash
# Clean and rebuild SDK
$ ./build-linux-binder-aidl.sh --clean

# Clean and rebuild examples (with optional AIDL regeneration)
$ ./build-binder-example.sh --clean --clean-aidl

# Clean and rebuild AIDL compiler
$ ./build-aidl-generator-tool.sh --clean
```

Manual cleanup:
```bash
# Clean target build only
rm -rf out/target/ build-target/

# Clean host AIDL build only
rm -rf out/host/ build-host/

# Clean everything
rm -rf out/ build-target/ build-host/
```

---

# Output

The default generated binder libs are 64-bit. This can be modified using `TARGET_LIB64_VERSION` or `TARGET_LIB32_VERSION` CMake variables.

**Target SDK** (libraries for embedded devices) are installed to `out/target/`:

    out/target/
        ├── bin/
        │   ├── servicemanager
        │   ├── FWManagerService
        │   ├── FWManagerClient
        │   └── binder-device
        ├── include/
        │   └── *.h
        └── lib/
            ├── libbinder.so
            ├── libcutils.so
            ├── libcutils_sockets.so
            ├── libutils.so
            ├── liblog.so
            └── libfwmanager.so

**Host AIDL Compiler** (architecture team only) is installed to `out/host/`:

    out/host/
        └── bin/
            ├── aidl
            └── aidl-cpp

Refer to [OUTPUT.md](OUTPUT.md) for a complete list of installed files.


---

# Testing

## Using Vagrant Box
Refer : https://www.vagrantup.com/

#### 1. Download and use the android binder enabled Vagrant box

##### Download Vagrant Box from Vagrant Cloud
* Use [__rahulraas/ubuntu-binder-22.04__](https://app.vagrantup.com/rahulraas/boxes/ubuntu-binder-22.04) directly from Vagrant cloud (https://app.vagrantup.com/boxes/search)
* __Vagrantfile__
```
Vagrant.configure("2") do |config|
  config.vm.box = "rahulraas/ubuntu-binder-22.04"
  config.vm.box_version = "1.0.0"
end
```

####  OR

##### Download Vagrant Box from Pre Shared Location

* Download __ubuntu-binder-22.04.box__ from a shared location
* Add the __ubuntu-binder-22.04__ box to Vagrant
```
$ vagrant box add ubuntu-binder-22.04 ubuntu-binder-22.04.box
```
* Create the Vagrant Environment with binder Vagrant box
```
$ vagrant init ubuntu-binder-22.04

OR

Create a Vagrantfile with binder Vagrant box
--------------------------------------------------
config.vm.box = "ubuntu-binder-22.04"

# Set the machine name (optional)
config.vm.define "ubuntu-binder-22.04"
--------------------------------------------------
```

#### 2. Launch and Access the Virtual Machine
```
$ vagrant up
$ vagrant ssh
```

#### 3. Build the binder libs and example bins
```
$ sudo bash (need to be a super user to access /dev/binder)
$ ./build-binder-example.sh
```
<a name="3-build-the-binder-libs-and-example-bins"></a>
#### 4. Move to the bin directory and update the LD_LIBRARY_PATH with binder libs
```bash
$ cd out/target/bin
$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/../lib
```

#### 5. Run the servicemanager
```
$ ./servicemanager &
```

#### 6. Run example service
```
$ ./FWManagerService &
```

#### 7. Run example client
```
$ ./FWManagerClient
```
<a name="7.-run-example-client"></a>
## Using KVM

#### 1. Create an Ubuntu 22.04 LTS KVM with Kernel 5.16.20
* Refer : https://ubuntu.com/download/kvm#:~:text=Install%20KVM&text=This%20is%20the%20best%20outcome,hardware%20acceleration%20in%20your%20CPU.

#### 2. Create binder device node if not exists
```
$ ./binder-device /dev/binderfs/binder-control /dev/binderfs/binder
$ chmod 0755 /dev/binderfs/binder
$ ln -sf /dev/binderfs/binder /dev/binder
```

#### 3. Build the binder libs and run the servicemanager and example server and client.
Run [Step 3](#3-build-the-binder-libs-and-example-bins) to [Step 7](#7-run-example-client) in the [Vagrant Box](#using-vagrant-box) section.

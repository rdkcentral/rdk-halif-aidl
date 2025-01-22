# Linux Binder IDL

This project aims to build and test the Android Binder for the Linux desktop environment.
The Android 13 AOSP source code is cloned from `Google's` repositories. The Android tag
 is __*android-13.0.0_r74*__, and the code has been modified to make it compatible with Linux.
The project is primarily designed to build the binder libraries and an example module for the
 host machine (by default). It also builds the `aidl` utility for the host machine, which
 generates the stubs and proxies from the `*.aidl` file. The default binder libraries generated are
 64-bit, but this can be overridden using the build override flags (refer to the
 [Build Overrides](#build-overrides) section below).

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
    - [Individual Steps in Binder Build](#individual-steps-in-binder-build)
    - [Build Overrides](#build-overrides)
    - [Additional Build Options](#additional-build-options)
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
```
$ ./build-linux-binder-aidl.sh
```

#### Following are the generated files as part of the binder framework.

    ├── bin
    │   └── servicemanager
    ├── include
    │   └── *.h
    └── lib
        ├── libbase.so
        ├── libbinder.so
        ├── libcutils.so
        ├── libcutils_sockets.so
        ├── liblog.so
        └── libutils.so

## Build Binder Example

Following are the build steps to build the binder examples. This builds the binder framework first and the binder examples.

### Run below command to build binder example
```
$ ./build-binder-example.sh
```

#### Following are the libraries and binaries generated as part of binder example (along with binder framework).

    ├── bin
    │   ├── FWManagerService
    │   └── FWManagerClient
    └── lib
        └── libfwmanager.so

## Build AIDL generator tool

### Run below command to build aidl generator tool
```
$ ./build-aidl-generator-tool.sh
```

#### Following are the libraries, binaries and tarball generated as part of the aidl generator tool. tar ball having the aidl , libbase.so and liblog.so

    ├── aidl-gen-tool-android-13.0.0_r74+1.0.0.tar.bz2
    └── bin
        └── aidl

Note : The AIDL generator tool is build and tested only in x86 machine. The aidl generator tool tarball version can be updated using `${AIDL_GENERATOR_TARBALL}`.

The Google prebuilt AIDL generator tool for host machine is available in https://android.googlesource.com/platform/prebuilts/build-tools google repo.


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

Following are the build overrides and apis available in the build system to build, debug and test individual components.

## Individual Steps in Binder Build

#### Setup environment
```
$ source setup-env.sh <Target lib arch version> <Install directory path>
```
- Argument1 : Target lib ARCH version. The values are `"32"` or `"64"`. The default target lib version is `"64"` bit.
- Argument2 : CMake install directory. The default CMake installation path is "${PWD}/local".

#### Clone all android repos and apply patches
```
$ clone_android_binder_repo
```

#### Build binder for Linux
```
$ build_linux_binder
```

#### Build binder example
```
$ build_binder_examples
```

#### Build aidl generator tool
```
$ build_aidl_generator_tool
```

## Build Overrides

The `setup-env.sh` is basically written to build the binder and example modules for host machine.
But the `CMakeLists.txt`, is written in a way that it will build the `32bit` binder and dependend
libraries and servicemanager for `YOCTO` build system.

#### setup-env.sh Overrides

- TARGET_LIB_VERSION :- Binder lib ARCH version. The values are `"32"` or `"64"`. The default target lib version is `"64"` bit

- INSTALL_DIR :- CMake install directory. The default installation path is `"${PWD}/local"`.

#### CMake Overrides

- CMAKE_INSTALL_PREFIX :- CMake install directory. Usage: `$ cmake -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}`.

- BUILD_ENV_HOST :- Use it to specify the build environment as `HOST Machine`. Usage: `$ cmake -DBUILD_ENV_HOST=ON`.

- BUILD_ENV_YOCTO :- Used it to specify the build environment as `YOCTO`. Usage: `$ cmake -DBUILD_ENV_YOCTO=ON`.

- BUILD_SHARED_LIB :- Used it to specify to build `SHARED` libs. Default generated libs are `SHARED`. Usage: `$ cmake -DBUILD_SHARED_LIB=ON`.

- BUILD_STATIC_LIB :- Used it to specify to build `STATIC` libs. Usage: `$ cmake -DBUILD_STATIC_LIB=ON`.
  Note: libbinder will be shared but the depend libraries will be static.

- TARGET_LIB64_VERSION :- Target binder lib ARCH version as `64bit`. Usage: `$ cmake -DTARGET_LIB64_VERSION=ON`.

- USE_PREBUILT_GEN_FILES :- Switch to use the pre-generated stubs and proxies from the prebuilts directory for binder example.
Usage: `$ cmake -DUSE_PREBUILT_GEN_FILES=ON`.

- BUILD_USING_AIDL_UTILITY :- Switch to use the aidl utility to generate stubs and proxies for the binder example.
Usage: `$ cmake -DBUILD_USING_AIDL_UTILITY=ON`.

- BUILD_BINDER_DEVICE_UTILITY:- Switch to build the binder-device utility to create binder node in `Ubuntu`.
Usage: `$ cmake -DBUILD_BINDER_DEVICE_UTILITY=ON`.

## Additional Build Options

Following are the additional build options provided by setup-env.sh

| Function/API Name                | Description                                                     |
|----------------------------------|-----------------------------------------------------------------|
| clone_android_binder_repo        | Clones all android repos and apply patches                      |
| clone_android_liblog_repo        | Clones all android liblog repo and apply patches                |
| build_linux_binder               | Build binder for Linux                                          |
| build_binder_examples            | Build binder example code for Linux                             |
| build_aidl_generator_tool        | Build aidl generator tool                                       |
| build_binder_device_tool         | Build linux binder-device tool to create binder node            |
| clean_android_build              | Clean android build directory                                   |
| clean_example_build              | Clean example build directory                                   |
| clean_aidl_generator_build       | Clean aidl generator build directory                            |
| clean_android_clone              | Clean android cloned code                                       |
| clean_build_all                  | Clean android and example build directory                       |
| clean_all                        | Clean android and example build directory and clone directory   |
| build_liblog                     | Build android liblog library                                    |
| build_libbase                    | Build libbase library                                           |
| build_libcutils                  | Build libcutils library                                         |
| build_libutils                   | Build libutils library                                          |
| build_libbinder                  | Build binder library                                            |
| build_servicemanager             | Build servicemanager                                            |

---

# Output

The default generated binder libs are 64 bits. This can be modified by setting the `${TARGET_LIB_VERSION}` in
setup-env.sh. The generated binaries and libraries are copied into `${WORK_DIR}/local`. This can be modified
by setting the `${INSTALL_DIR}` in setup-env.sh. Please refer [OUTPUT](OUTPUT.md) to see all the installed files.

    local/
        ├── bin
        │   ├── servicemanager
        │   ├── FWManagerService
        │   ├── FWManagerClient
        │   └── binder-device
        ├── include
        │   ├── *.h
        └── lib
            ├── libbinder.so
            ├── libcutils.so
            ├── libcutils_sockets.so
            ├── libutils.so
            ├── liblog.so
            └── libfwmanager.so


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
```
$ cd ${WORK_DIR}/local/bin (suppose we haven't modified the default INSTALL_PATH)
$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${WORK_DIR}/local/lib/
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

# HAL Interface Generation

This document describes how to generate Hardware Abstraction Layer (HAL) interface definitions using the Android Interface Definition Language (AIDL).

## Prerequisites

Building this repository requires the AIDL compiler (`aidl`).  This can be obtained by building the `linux_binder_idl` project, available on GitHub: [github.com/rdkcentral/linux_binder_idl.git](https://github.com/rdkcentral/linux_binder_idl). Alternatively, you can use a Docker image that includes `aidl`, such as `rdk-dunfell` or the recommended `rdk-kirkstone`.

## Building `aidl` from `linux_binder_idl`

**Minimum Required GCC Version:** 9.4.0

Using the `rdk-kirkstone` Docker image is highly recommended.

**Clone the `linux_binder_idl` repository:**

```bash
git clone git@github.com:rdkcentral/linux_binder_idl.git
cd linux_binder_idl
```

**Build `aidl`:**

```bash
# Optional: Run inside the Docker container
sc docker run rdk-kirkstone /bin/bash
```

Then build the aidl tool.

```bash
./build-aidl-generator-tool.sh
```

**Locate the `aidl` binary:**

The compiled `aidl` binary will be located in the `local/bin` directory within the `linux_binder_idl` project.  The full path might resemble:

```bash
linux_binder_idl/local/bin/aidl
```

For more detailed information, refer to the [github.com/rdkcentral/linux_binder_idl.git](https://github.com/rdkcentral/linux_binder_idl) repository.

## Generating AIDL Proxy and Native Interfaces

**Clone the `hal` repository:**

```bash
git clone git@github.com:rdkcentral/rdk-halif-aidl.git
```

**Generate the AIDL proxy and native interfaces:**

The following example demonstrates generating interfaces for the `audiodecoder` module. Adapt the
`INTERFACE_TARGET` CMake variable for other modules.

```bash
cd hal

# Optional: Run inside the Docker container
sc docker run rdk-kirkstone /bin/bash

# Optional: Set AIDL binary path if not in system PATH.  Replace with the actual path from the previous step.
export PATH=$PATH:/path/to/linux_binder_idl/local/bin

cmake -S . -B build -DINTERFACE_TARGET=audiodecoder
cmake --build build
```

!!! warning
    CMake *must* be run from the root directory of the `hal` repository, not within a specific module directory.

**Locate the generated files:**

Generated proxy and interface files for a current module are written beside
the AIDL source during the build. The generated `src` and `include`
directories are ignored by Git and are not committed. For example:

```
hal/audiodecoder/current/src/com/rdk/hal/audiodecoder/...      (C++ files)
hal/audiodecoder/current/include/com/rdk/hal/audiodecoder/...  (Header files)
hal/audiodecoder/current/com/rdk/hal/audiodecoder/...          (AIDL source files)
```

## Example CMake Commands

```bash
# Use a custom path to the `aidl` binary
cmake -S . -B build -DINTERFACE_TARGET=audiodecoder \
    -DAIDL_EXECUTABLE=/home/example/bin/aidl

# Specify a released AIDL interface version
cmake -S . -B build -DINTERFACE_TARGET=audiodecoder \
    -DINTERFACE_VERSION=0.3.0.0

# Build all versions selected by an alternate manifest
cmake -S . -B build \
    -DINTERFACE_RELEASE_FILE=versions_current.yaml
```

## CMake Variables

| Variable                 | Description |
|--------------------------|-------------|
| `AIDL_EXECUTABLE`        | *Optional*. Path to the `aidl` executable. CMake locates it when a current interface needs generation. |
| `INTERFACE_TARGET`       | *Optional*. Module to build. When unset, CMake builds every component selected by the versions manifest. |
| `INTERFACE_VERSION`      | *Optional*. Version of `INTERFACE_TARGET`. Default: `current`. |
| `INTERFACE_RELEASE_FILE` | *Optional*. Component version manifest. Default: `versions_released.yaml`. |

For a single-module build, `<module>/<version>/interface.yaml` is the module
manifest: its `imports` select the complete dependency version set. For a
multi-module build, `INTERFACE_RELEASE_FILE` selects the top-level module
versions, and each selected module's `interface.yaml` supplies its dependency
closure.

## Notes

The `Broadcast` module is currently disabled because its `demux` submodule depends on the Android framework.

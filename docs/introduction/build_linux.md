## RDK-E HAL Interface Generation

This document describes how to generate Hardware Abstraction Layer (HAL) interface definitions for RDK-E using the Android Interface Definition Language (AIDL).

### Prerequisites

Building this repository requires the AIDL compiler (`aidl`).  This can be obtained by building the `linux_binder_idl` project, available on GitHub: [linux_binder_idl](https://github.com/rdk-e/linux_binder_idl). Alternatively, you can use a Docker image that includes `aidl`, such as `rdk-dunfell` or the recommended `rdk-kirkstone`.

### Building `aidl` from `linux_binder_idl`

**Minimum Required GCC Version:** 9.4.0

Using the `rdk-kirkstone` Docker image is highly recommended.

1. **Clone the `linux_binder_idl` repository:**

```bash
git clone -b main https://github.com/rdk-e/linux_binder_idl.git
```

2. **Build `aidl`:**

```bash
cd linux_binder_idl

# Optional: Run inside the Docker container
sc docker run rdk-kirkstone /bin/bash

./build-aidl-generator-tool.sh
```

3. **Locate the `aidl` binary:**

The compiled `aidl` binary will be located in the `local/bin` directory within the `linux_binder_idl` project.  The full path might resemble:

```
linux_binder_idl/local/bin/aidl
```

For more detailed information, refer to the [linux_binder_idl](https://github.com/rdk-e/linux_binder_idl) repository.

### Generating AIDL Proxy and Native Interfaces

1. **Clone the `hal` repository:**

```bash
git clone -b develop https://github.com/rdk-e/hal.git
```

2. **Generate the AIDL proxy and native interfaces:**

The following example demonstrates generating interfaces for the `audiodecoder` module. Adapt the `AIDL_TARGET` CMake variable for other modules.

```bash
cd hal

# Optional: Run inside the Docker container
sc docker run rdk-kirkstone /bin/bash

# Optional: Set AIDL binary path if not in system PATH.  Replace with the actual path from the previous step.
export PATH=$PATH:/path/to/linux_binder_idl/local/bin

cmake -DAIDL_TARGET=audiodecoder .
```

!!! warning
CMake *must* be run from the root directory of the `hal` repository, not within a specific module directory.
!!!

3. **Locate the generated files:**

The generated proxy and interface files will be placed under `audiodecoder/gen/<version>`.  For example:

```
hal/audiodecoder/gen/current/cpp/com/rdk/hal/audiodecoder/...  (C++ files)
hal/audiodecoder/gen/current/h/com/rdk/hal/audiodecoder/...   (Header files)
hal/audiodecoder/current/com/rdk/hal/audiodecoder/...        (AIDL files)
```

### Example CMake Commands

```bash
# Use a custom path to the `aidl` binary
cmake -DAIDL_TARGET=audiodecoder -DAIDL_BIN=/home/example/bin/aidl .

# Specify a specific AIDL interface version (e.g., version 2)
cmake -DAIDL_TARGET=audiodecoder -DAIDL_SRC_VERSION=2 .

# Specify a custom output directory for generated files
cmake -DAIDL_TARGET=audiodecoder -DAIDL_GEN_DIR=/home/example/example_out .
```

### CMake Variables

| Variable        | Description                                                              |
|-----------------|--------------------------------------------------------------------------|
| `AIDL_BIN`      | *Optional*. Path to the `aidl` executable. If not set, CMake will attempt to locate it. |
| `AIDL_GEN_DIR`  | *Optional*. Output directory for generated files. Default: `<module>/gen/<version>`. |
| `AIDL_SRC_VERSION` | *Optional*. Version of the AIDL interface to generate. Default: `current`.     |
| `AIDL_TARGET`   | *Mandatory*. Name of the module for which to generate interfaces.         |

### Notes

The `Broadcast` module is currently disabled because its `demux` submodule depends on the Android framework.

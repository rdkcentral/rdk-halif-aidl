# RDK-E HALs
This repo contains the HAL interface definitions for RDK-E.

## Prerequisite

Requires AIDL compiler `aidl`, can be built from `linux_binder_idl` from
https://github.com/rdk-e/linux_binder_idl/tree/main or run in docker image
that has `aidl`, e.g. `rdk-dunfell`

### Build from `linux_binder_idl`
Minimum required GCC Version: **9.4.0**

If build using docker, it is recommended to use image `rdk-kirkstone`

1. Clone the `linux_binder_idl` repository
```
git clone -b main https://github.com/rdk-e/linux_binder_idl.git
```

2. Build `aidl`
```
cd linux_binder_idl

# Optional, depending on the build machine you are using
sc docker run rdk-kirkstone /bin/bash

./build-aidl-generator-tool.sh
```

The `aidl` binary is located in `local/`

```
local/
├── aidl-gen-tool-android-13.0.0_r74+1.0.0.tar.bz2
└── bin
    └── aidl
```

For more details refer: https://github.com/rdk-e/linux_binder_idl/tree/main

## Generating AIDL Proxy and Native Interfaces

1. Clone this repository
```
git clone -b develop https://github.com/rdk-e/hal.git
```

2. Generate AIDL proxy and native interface. Using "audiodecoder" module as an example

```
cd hal

# Optional if the `aidl` is not built in docker, or using `aidl` outside of docker
# If `aidl` is built in `rdk-kirkstone`, you have to run the build process in the same
# docker image
sc docker run rdk-kirkstone /bin/bash

# Optional if `aidl` is not in your path, or you prefer supply using CMake variable,
# e.g. -DAIDL_BIN=/home/example/bin/aidl
# If your `aidl` binary is at `/home/example/bin/aidl`
export PATH=$PATH:/home/example/bin

cmake -DAIDL_TARGET=audiodecoder .
```

The generated proxy and interface will be in directory `audiodecoder/gen/<version>`,
e.g. `audiodecoder/gen/current` in the following example

```
├── audiodecoder
│   ├── current
│   │   └── com
│   │       └── rdk
│   │           └── hal
│   │               └── audiodecoder
│   │                   ├── Capabilities.aidl
│   │                   ├── ChannelType.aidl
             ............................
│   ├── gen
│   │   └── current
│   │       ├── cpp
│   │       │   └── com
│   │       │       └── rdk
│   │       │           └── hal
│   │       │               ├── audiodecoder
│   │       │               │   ├── Capabilities.cpp
│   │       │               │   ├── ChannelType.cpp
             ............................
│   │       └── h
│   │           └── com
│   │               └── rdk
│   │                   └── hal
│   │                       ├── audiodecoder
│   │                       │   ├── BnAudioDecoderController.h
│   │                       │   ├── BnAudioDecoderControllerListener.h
             ............................
├── README.md
             ............................
```

> [!IMPORTANT]
> CMake should be ran on the root level of the project, not inside the module directory.

More examples:
```
# Generate proxy and native interface using `aidl` binary from /home/example/bin/aidl
cmake -DAIDL_TARGET=audiodecoder -DAIDL_BIN=/home/example/bin/aidl .

# Using audiodecoder version `2` instead of `current`
cmake -DAIDL_TARGET=audiodecoder -DAIDL_SRC_VERSION=2 .

# Output the proxy and native interface in `/home/example/example_out` instead of `audiodecoder/gen/<version>`
cmake -DAIDL_TARGET=audiodecoder -DAIDL_GEN_DIR=/home/example/example_out .
```

### CMake variables
````
# Optional. Path of the `aidl` program.
# Default cmake will find `aidl` from system PATH and cmake configuraing using `find_program()`
AIDL_BIN

# Optional. Path where the output will be generated
# Default is output to `<module>/gen/<version>`
AIDL_GEN_DIR

# Optional. Specify which version of the aidl target module interface definition to use.
# Default is using `current`.
AIDL_SRC_VERSION

# Mandatory. Specify what module to generate.
AIDL_TARGET
````

## Note
Module `Broadcast` is temporary disabled because the submodule `demux` is still depending on Android framework.

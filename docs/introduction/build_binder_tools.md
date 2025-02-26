# Building and Using Binder Tools

## Overview

This document provides step-by-step instructions on how to clone, build, and use the Binder tools from the Android source repository.

## Prerequisites

Before proceeding, ensure that you have the following dependencies installed on your Linux system:

```sh
sudo apt update && sudo apt install -y git build-essential clang cmake
```

## Cloning the Repository

To get the source code for the Binder tools, use the following command:

```sh
git clone https://android.googlesource.com/platform/prebuilts/build-tools
cd build-tools
```

## Using Prebuilt Binder Tools

If you prefer to use the prebuilt Binder tools instead of building them from source, follow these steps:

1. Ensure you have the necessary permissions to execute the prebuilt binaries.
2. Navigate to the directory containing the prebuilt tools:

   ```sh
   cd build-tools/prebuilt/linux-x86_64/bin
   ```

3. Add the directory to your system `PATH` to use the tools globally:

   ```sh
   export PATH=$(pwd):$PATH
   ```

4. Verify the installation by checking the available commands:

   ```sh
   binder --help
   ```

## Building the Binder Tools

1. Navigate to the `build-tools` directory:

   ```sh
   cd build-tools
   ```

2. If the repository includes a `CMakeLists.txt` file, use CMake to build:

   ```sh
   mkdir -p build && cd build
   cmake ..
   make -j$(nproc)
   ```

3. Alternatively, if a standard `Makefile` is present, simply run:

   ```sh
   make -j$(nproc)
   ```

## Installing the Built Tools

Once the build is complete, install the tools system-wide (if required):

```sh
sudo make install
```

## Using Binder Tools

After installation, you can use the tools directly. Some commonly used commands include:

```sh
binder --help   # Display help menu
binder <options>  # Run the tool with required options
```

If the tool is not found in the system path, you can run it from the build directory:

```sh
./binder <options>
```

## Troubleshooting

- If the build fails due to missing dependencies, install them using:
  
  ```sh
  sudo apt install -y additional-dependency
  ```

- If the command is not found, ensure the binary is in your `PATH`:
  
  ```sh
  export PATH=$(pwd)/build:$PATH
  ```

For more details, refer to the [official Android source documentation](https://source.android.com/).

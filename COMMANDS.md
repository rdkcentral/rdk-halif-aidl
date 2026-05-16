# RDK HAL AIDL - Command Reference

Quick reference for all build scripts in this repository.

## Setup

### Build Toolchain
```bash
./build_binder.sh
# or
source ./build_binder.sh  # Updates PATH in current shell
```

Builds Android Binder AIDL toolchain (aidl compiler, binder libraries).
Run `./build_binder.sh --help` for details.

---

## Development Workflow

### 1. Build Interface
```bash
./build_interfaces.sh <module>
```

Examples:
```bash
./build_interfaces.sh boot
./build_interfaces.sh videodecoder
./build_interfaces.sh all
```

This copies `<module>/current/` to `stable/<module>/current/`, generates C++ code, and builds libraries.

### 2. Build with Debug Symbols
```bash
CC="gcc -g" CXX="g++ -g" ./build_interfaces.sh <module>
```

Use CC/CXX environment variables to control compiler flags.

### 3. Cross-Compile for Target
```bash
CC=arm-linux-gnueabihf-gcc CXX=arm-linux-gnueabihf-g++ ./build_interfaces.sh <module>
```

### 4. Freeze Interface (Create Version)
```bash
./freeze_interface.sh <module>
```

Creates a frozen version (v1, v2, etc.) from the current working copy.
Output: `stable/<module>/v1/<module>-api/` and `stable/generated/<module>/v1/`

---

## All Available Commands

| Script | Purpose | Example |
|--------|---------|---------|
| `./build_binder.sh` | Build AIDL toolchain | `source ./build_binder.sh` |
| `./build_interfaces.sh` | Build interfaces | `./build_interfaces.sh boot` |
| `./freeze_interface.sh` | Freeze interface version | `./freeze_interface.sh boot` |

---

## Common Workflows

### Edit and Test Interface
```bash
# 1. Edit source files
vim boot/current/com/rdk/hal/boot/IBoot.aidl

# 2. Build and test
./build_interfaces.sh boot

# 3. Repeat until satisfied
```

### Create Stable Release
```bash
# 1. Ensure current version is working
./build_interfaces.sh <module>

# 2. Freeze to create versioned release
./freeze_interface.sh <module>

# 3. Build frozen version
./build_interfaces.sh <module> --version v1

# 4. Commit frozen version
git add stable/<module>/v1/
git commit -m "Freeze <module> v1"
```

### Build All Modules
```bash
./build_interfaces.sh all
```

### Debug Build
```bash
CC="gcc -g -O0" CXX="g++ -g -O0" ./build_interfaces.sh <module>
```

---

## Output Directory Structure

After build, everything needed for deployment is in `out/`:

```
out/
├── include/    # All header files (.h)
└── lib/        # All shared libraries (.so)
```

**Deploy to target:**
```bash
# Copy to target device
scp -r out/* root@target:/usr/local/
```

---

## Source Directory Structure

```
<module>/current/              # Working source files (edit here)
stable/
  <module>/current/            # Copied AIDL sources
  <module>/v1/                 # Frozen version 1
  generated/<module>/current/  # Generated C++ code
  generated/<module>/v1/       # Generated code (frozen)
build/
  current/                     # CMake build artifacts
out/
  include/                     # Headers for deployment
  lib/                         # Libraries for deployment
```

---

## Help Text

All scripts support `--help`:
```bash
./build_binder.sh --help
./build_interfaces.sh --help
./freeze_interface.sh --help
```

---

## Tips

- Use `CC` and `CXX` environment variables to control compiler and flags
- The `out/` directory contains everything needed for target deployment
- **Only freeze ONE interface at a time** - freezing creates permanent API versions
- Always build and test thoroughly before freezing
- Commit frozen versions immediately after creation
- Use `--version` flag to build and test frozen versions before committing


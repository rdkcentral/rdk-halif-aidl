# RDK HAL AIDL Copilot Instructions

This codebase defines **RDK Hardware Abstraction Layer interfaces using Android AIDL** for embedded platforms. Each HAL module exposes hardware functionality via IPC using Android Binder for Linux.

## ⚠️ Critical Rules - Read First

**NEVER:**
- Run CMake directly in module subdirectories (always use root with `-DINTERFACE_TARGET=<module>`)
- Use `@return` in Doxygen comments (always use `@returns`)
- Introduce custom logging frameworks (only use syslog-ng macros)
- Make breaking changes to existing interfaces (only backward-compatible additions allowed)
- Omit `@VintfStability` annotation on AIDL interfaces
- Use development scripts (`build_binder.sh`, `build_interfaces.sh`) in production/Yocto builds
- Use British English alternatives to UK English spelling in documentation

**ALWAYS:**
- Annotate all AIDL interfaces with `@VintfStability`
- Use UK English spelling in comments and documentation
- Validate compatibility before committing AIDL changes (`./build_interfaces.sh <module>`)
- Commit both AIDL source and generated C++ code in `stable/` directory
- Include `serviceName` constant in main AIDL interfaces
- Use lowercase with dots for service names (`"boot"`, `"sensor.motion"`)

## Quick Reference Commands

```bash
# First-time setup (development only)
./build_binder.sh                    # Build Binder SDK (one-time)

# Development workflow (interface authors)
./build_interfaces.sh boot           # Build + validate specific module
./build_interfaces.sh all            # Build all modules
./build_interfaces.sh clean          # Clean build outputs
./build_interfaces.sh cleanstable    # Remove generated code
./freeze_interface.sh boot           # Freeze as versioned release (v1, v2, etc.)

# Production build (Yocto/BitBake - uses pre-generated code)
cmake -S . -B build -DINTERFACE_TARGET=all -DBINDER_SDK_DIR=${STAGING_DIR}/usr
cmake --build build
cmake --install build

# Validation & testing
./build_interfaces.sh test           # Quick validation test
./build_interfaces.sh test-validation # Test compatibility checks
```

## Project Overview

- **RDK-HALIF-AIDL** standardizes hardware abstraction layers (HALs) using Android AIDL and Binder IPC for embedded platforms
- The codebase is organized by hardware domain (e.g., `audiodecoder`, `deviceinfo`, `hdmioutput`), each with a `current/` versioned subdirectory
- All HAL interfaces are defined in `.aidl` files and built into C++ code using the AIDL compiler
- **Client-Server Model**: Clients interact with HAL services via AIDL-generated proxies; services implement AIDL skeletons. Communication is via Binder IPC

## Architecture Overview

### Module Organization

- **HAL Modules**: Each directory (`boot/`, `videodecoder/`, `audiosink/`, etc.) contains one HAL component
- **Versioning**: All modules use `current/` directory for the active interface version. New versions are added as new subdirectories (e.g., `current/`, `2/`)
- **Package Structure**: All AIDL interfaces use `com.rdk.hal.*` package namespace
- **Service Registration**: Each HAL registers with AIDL Service Manager using predefined `serviceName` constants
- **@VintfStability**: All AIDL interfaces MUST be annotated with `@VintfStability` for vendor interface stability

### Service Boundaries

Each hardware domain is a separate service/module. See `docs/introduction/aidl_and_binder.md` and `docs/introduction/the_software_stack.md` for diagrams and details.

## Module Structure Pattern

Every HAL module follows this exact structure:

```
{module}/
├── current/                    # Current interface version
│   ├── CMakeLists.txt         # Module build configuration (3 lines!)
│   ├── hfp-{module}.yaml      # HAL Feature Profile (capabilities)
│   ├── interface.yaml         # Module metadata (optional)
│   └── com/rdk/hal/{module}/  # AIDL interface definitions
│       ├── I{Module}Manager.aidl  # Manager interface (complex modules)
│       ├── I{Module}.aidl         # Main interface (stateless for simple)
│       ├── Capabilities.aidl      # Runtime capability discovery
│       └── *.aidl                 # Supporting types/enums/listeners
└── gen/                       # Generated code (gitignored)
    └── {version}/
        ├── cpp/               # C++ implementation files
        └── h/                 # C++ header files
```

**Generated Code Location (committed to repo):**
```
stable/
├── aidl/{module}/current/     # Copied AIDL files (source of truth)
└── generated/{module}/current/ # Pre-generated C++ code
    ├── cpp/                    # Implementation files
    └── h/                      # Header files
```

## Key Development Patterns

### AIDL Interface Design

- **Main Interface**: `I{Module}.aidl` with `serviceName` constant for binder registration
- **Manager Pattern**: Complex modules may use `I{Module}Manager.aidl` to manage multiple resource instances
- **Stateless**: Simple interfaces have no open/close lifecycle - each call is independent
- **Capabilities Pattern**: `getCapabilities()` method returns supported features at runtime
- **Error Handling**: Use AIDL exceptions, not return codes
- **@VintfStability**: MUST be present on all AIDL interfaces

### Service Names & Packages

**Service Naming Convention:**
- Format: `{module}` or `{category}.{module}` (typically lowercase with dot separators)
- Simple modules: `"boot"`, `"cec"`, `"panel"` (some modules may use `"Boot"` - check existing implementation)
- Categorized modules: `"sensor.motion"`, `"sensor.thermal"`, `"broadcast.tuner"`
- Use the module directory path with dots instead of slashes
- **Important**: Match the existing convention in the module you're working with

```aidl
// Standard pattern in main interfaces
package com.rdk.hal.boot;

@VintfStability
interface IBoot {
    const @utf8InCpp String serviceName = "Boot";  // Note: Check module's existing convention
    // ...
}

// Categorized module example
package com.rdk.hal.sensor.motion;

@VintfStability
interface IMotionSensorManager {
    const @utf8InCpp String serviceName = "sensor.motion";
    // ...
}
```

### HAL Feature Profile (HFP)

Each `hfp-{module}.yaml` declares static capabilities:

```yaml
{Module}:
  interfaceVersion: current
  supported{Features}:    # Maps to runtime Capabilities
    - FEATURE_ONE
    - FEATURE_TWO
```

**Notes**:
- HFP defines the maximum capabilities of the module from the API definition
- Capabilities will be tailored per platform later
- HFP Service naming `{Module}` is preferred across all HAL Feature Profiles
- HFP Validation Schema will be added beside the best case HFP files

## Build System

### Two-Stage Architecture

**Stage 1 (Development Only)**: Binder SDK setup
- Run `./build_binder.sh` to build Android Binder SDK (libbinder, AIDL compiler)
- Installs to `out/target/` with `.sdk_ready` marker
- Only needed for interface authors modifying AIDL files
- **NOT used in production builds** (Yocto provides SDK via `linux-binder` recipe)

**Stage 2 (Development & Production)**: HAL module compilation
- Development: `./build_interfaces.sh <module>` - generates C++ from AIDL + compiles
- Production: CMake directly - compiles pre-generated C++ code from `stable/generated/`

### Development Workflow (Interface Authors)

**Quick Start:**
```bash
# 1. One-time setup: Build Binder SDK
./build_binder.sh

# 2. Modify AIDL interfaces in {module}/current/
vim boot/current/com/rdk/hal/boot/IBoot.aidl

# 3. Build and validate (generates C++, validates compatibility, compiles)
./build_interfaces.sh boot

# 4. Commit generated code
git add stable/
git commit -m "Update boot interface"
```

**What `build_interfaces.sh` does:**
1. Copies `{module}/current/*.aidl` → `stable/aidl/{module}/current/`
2. Validates compatibility with existing `stable/aidl/{module}/current/` (if exists)
3. Generates C++ code → `stable/generated/{module}/current/`
4. Compiles to `out/target/lib/halif/lib{module}-vcurrent-cpp.so`

**Common Commands:**
```bash
./build_interfaces.sh all                    # Build all modules
./build_interfaces.sh boot                   # Build specific module
./build_interfaces.sh boot --version v1      # Build frozen version
./build_interfaces.sh clean                  # Remove out/ directory
./build_interfaces.sh cleanstable            # Remove stable/ (generated code)
./build_interfaces.sh test                   # Quick validation test
./freeze_interface.sh boot                   # Freeze as v1, v2, etc.
```

### Production Workflow (Yocto/BitBake)

**Prerequisites:**
- Binder SDK from Yocto recipe: `DEPENDS = "linux-binder"`
- Pre-generated C++ code in `stable/generated/` (committed to repo)

**Build Pattern:**
```bash
# Compiler and flags MUST be passed via environment variables
CC="${CC}" CXX="${CXX}" \
CFLAGS="${CFLAGS}" CXXFLAGS="${CXXFLAGS}" LDFLAGS="${LDFLAGS}" \
cmake -S . -B build \
      -DINTERFACE_TARGET=all \
      -DAIDL_SRC_VERSION=current \
      -DBINDER_SDK_DIR=${STAGING_DIR}/usr

cmake --build build
cmake --install build
```

**Output:** `out/target/lib/halif/*.so` and `out/build/include/*`

**Key Difference:** Production NEVER runs AIDL compiler - only compiles pre-generated C++

**Compiler Configuration:**

The build system **requires** compiler and flags to be specified via environment variables for cross-compilation:

- **`CC`** - C compiler (mandatory for cross-compilation)
- **`CXX`** - C++ compiler (mandatory for cross-compilation)
- **`CFLAGS`** - C compiler flags (e.g., `-O2 -march=armv7-a`)
- **`CXXFLAGS`** - C++ compiler flags (e.g., `-O2 -std=c++17`)
- **`LDFLAGS`** - Linker flags (e.g., `-Wl,--hash-style=gnu`)

CMake automatically detects and applies these variables. Yocto provides them automatically.

### Required CMake Variables

- `INTERFACE_TARGET` (required): Module to build (e.g., "boot", "videodecoder") - set in module's CMakeLists.txt
- `INTERFACE_VERSION`: Version directory (default: "current") - set in module's CMakeLists.txt
- `AIDL_SRC_VERSION`: Version directory override (command-line, optional)
- `AIDL_GEN_DIR`: Output directory (defaults to `gen/{module}/{version}`)
- `AIDL_BIN`: Path to AIDL compiler (from linux_binder_idl tools, auto-detected if in PATH)

### Default AIDL Compiler Flags

Set in `CMakeModules/CompileAidl.cmake`:
- `--min_sdk_version=33`
- `--structured`
- `--stability=vintf`

### Module CMakeLists.txt Pattern

```cmake
# Standard module build structure (3 lines!)
set(INTERFACE_TARGET boot)
set(INTERFACE_VERSION current)
target_build_interfaces_libraries()
```

**Note:** The `target_build_interfaces_libraries()` function (defined in root CMakeLists) handles:
- Running `aidl_ops` to generate C++ code (development workflow)
- Finding generated files in `stable/generated/{module}/{version}/`
- Creating library target `lib{module}-v{version}-cpp.so`
- Setting up include paths and dependencies

### Production Build (Yocto/BitBake)

**Purpose**: Build HAL interface libraries for deployment on embedded devices.

**Key Differences from Development Build**:
- **NO interface generation**: Uses pre-generated C++ code from `stable/generated/`
- **NO AIDL compiler needed**: Only requires C++ compiler and CMake
- **Binder SDK dependency**: `DEPENDS = "linux-binder"` in Yocto recipe

**Binder SDK Dependency**:
- The `linux-binder` Yocto recipe builds `build-tools/linux_binder_idl/`
- Provides: `libbinder.so`, `libutils.so`, `liblog.so`, headers
- Automatically staged to `${STAGING_DIR}/usr` by Yocto dependency system
- See `build-tools/linux_binder_idl/BUILD.md` for complete recipe documentation

**Production Build Example**:
```bitbake
DEPENDS = "linux-binder"

do_configure() {
    cmake -S ${S} -B ${B} \
          -DINTERFACE_TARGET=all \
          -DBINDER_SDK_DIR=${STAGING_DIR}${prefix}
}
```

**Important**: Development scripts (`build_binder.sh`, wrapper scripts) are NOT used in production. Production uses direct CMake with Yocto dependency management.

**Binder SDK Production Build Requirements**:
- When building `linux-binder` (Binder SDK) with `BUILD_HOST_AIDL=OFF` (production mode):
  - Pre-generated binder AIDL stubs exist in `binder_aidl_gen/` (already committed)
  - CMakeLists.txt automatically uses pre-generated code when `BUILD_HOST_AIDL=OFF`
  - **No AIDL compiler needed** - build uses committed C++ code
- For cross-compilation: Use standard Yocto toolchain variables (`CC`, `CXX`, `CFLAGS`, etc.)

## Cross-Module Dependencies

### Common Types

Import shared types from `common/current/com/rdk/hal/`:
- `State.aidl`: Generic component states - **will be deprecated** in preference of each module defining its own State enum
- `HALError.aidl`: Standard error codes - **will be deprecated** in favour of module-specific error handling
- `PropertyValue.aidl`: Key-value property types
- `AVSource.aidl`: Audio/video source definitions

### Module Interdependencies

Complex modules reference each other via CMake:

```cmake
# Example from avbuffer/current/CMakeLists.txt
set(AUDIO_DECODER_VERSION "current")
set(VIDEO_DECODER_VERSION "current")
set(COMMON_VERSION "current")
```

## Logging & Diagnostics

### Logging Policy

- All interface and wrapper layers **MUST** use the platform's `syslog-ng` via the standard POSIX `syslog()` API
- Use macros from a shared logging header for consistent log levels (see `docs/vsi/filesystem/current/logging_system.md`):
  - `LOG_CRIT`, `LOG_ERR`, `LOG_WARNING`, `LOG_NOTICE` (always enabled)
  - `LOG_INFO`, `LOG_DEBUG` (controlled by `ENABLE_LOG_INFO`, `ENABLE_LOG_DEBUG` build flags)
- Log verbosity is controlled by build flags. Production builds log NOTICE and above; debug builds enable INFO/DEBUG
- **NO custom logging frameworks**: Do not introduce new logging systems; use syslog-ng macros only
- Vendor implementations may use their own internal logging, but wrapper layers **MUST** use syslog-ng

### Logging Best Practices

- Log at appropriate levels (CRIT for critical failures, ERR for errors, WARNING for warnings, etc.)
- Include module/component context in log messages
- Avoid excessive DEBUG logging in hot paths
- See `docs/vsi/filesystem/current/logging_system.md` for detailed patterns

## Documentation Structure

- **Interface Docs**: `docs/halif/{module}/current/` contains detailed HAL specifications
- **Generated Docs**: MkDocs site at `https://rdkcentral.github.io/rdk-halif-aidl/`
- **Requirements**: Each HAL doc includes numbered requirements (e.g., `HAL.{Module}.1`)
- **Architecture**: `docs/introduction/aidl_and_binder.md` – IPC and AIDL architecture
- **Build Workflow**: `docs/introduction/interface_generation.md` – Build/generation workflow
- **Software Stack**: `docs/introduction/the_software_stack.md` – Software stack overview
- **Naming Standards**: `docs/halif/key_concepts/hal/hal_naming_conventions.md`

## Doxygen Documentation Standards

### Comment Tags

- **@brief**: One-line summary of the function/type
- **@param**: Document each parameter (use `@param[in]` or `@param[out]` for clarity)
- **@returns**: Overview description of what is returned (general statement). **ALWAYS use @returns, NEVER @return** (a function "returns" not "return")
- **@retval**: Document each specific return value (e.g., `@retval true Success`, `@retval false Failure`)
- **@exception**: Document exceptions that may be thrown

**Note:** Never use `@details` - any text after `@brief` is automatically considered detailed description.

### Return Value Documentation Pattern

For boolean returns or enums with multiple possible values:

```aidl
/**
 * @brief Enable feature X.
 * @param enabled True to enable, false to disable.
 * @returns Success flag indicating configuration status.
 * @retval true Feature enabled successfully.
 * @retval false Feature not supported or invalid state.
 * @exception binder::Status EX_ILLEGAL_STATE if not in valid state.
 */
boolean enableFeature(in boolean enabled);
```

For simple returns:

```aidl
/**
 * @brief Get the current state.
 * @returns Current state (e.g. STARTED, STOPPED, ERROR).
 */
State getState();
```

### General Guidelines

- **ALWAYS use @returns** (never @return): Functions "returns" values, not "return" values
- Use **@returns** for overview + **@retval** for each specific value when multiple outcomes exist
- Use **@returns** alone for simple single-value returns (no @retval needed)
- Always document exceptions with **@exception**
- Keep descriptions concise but complete
- Avoid redundant type names in @returns descriptions (e.g., avoid "@returns State Current state" - just "@returns Current state")

## Development Workflow

1. **Create New HAL**: Copy existing module structure, update package names
2. **Design AIDL**: Start with main interface, add supporting types
3. **Add @VintfStability**: Ensure all interfaces have `@VintfStability` annotation
4. **Update HFP**: Define static capabilities in `hfp-{module}.yaml` (this is the max capabilities of the module from the API definition, and will be tailored per platform later)
5. **Build**: Use root-level CMake with `INTERFACE_TARGET` set to your module (in module's CMakeLists.txt)
6. **Document**: Follow established documentation patterns in `docs/halif/`
7. **Add Logging**: Use syslog-ng macros for all logging

## Testing & Validation

### Testing Levels (L1-L4)

- **Level 1 (L1)**: Component Function Testing - API function testing of individual components
- **Level 2 (L2)**: Component Unit Testing - Focused testing of individual modules in a component
- **Level 3 (L3)**: Component Stimulus Testing - Pre-commit testing using external stimuli
- **Level 4 (L4)**: System Interface Testing (VSI) - Validate interactions with external interfaces and devices

### Implementation Requirements

- HAL implementations must support capabilities declared in HFP
- Use `getCapabilities()` to validate runtime vs. static capability alignment
- Each interface should handle invalid inputs gracefully via AIDL exceptions
- VTS Testing for all modules L1-L4 is defined through documentation and external to this workspace
- HFP Validation Schema: validate against HFP - HFP Schema will be added beside the best case HFP files

## Project Conventions

- **No direct module CMake**: Never run CMake in a module subdir; always use the root
- **No custom logging**: Do not introduce new logging frameworks; use syslog-ng macros only
- **Versioning**: New interface versions go in new subdirectories (e.g., `current/`, `2/`)
- **Naming**:
  - Use lowercase with underscores for docs/files (`audio_decoder`)
  - PascalCase for AIDL interfaces (`IAudioDecoder`)
  - Lowercase with dots for service names (`"boot"`, `"sensor.motion"`)
  - Systemd services follow `hal-{module}.service` pattern
- **Documentation**: All build and interface docs are in `docs/` and linked from the main `README.md`
- **UK English**: Use British English spelling in all documentation and comments
- **@VintfStability**: Always annotate AIDL interfaces with `@VintfStability`

## Common Pitfalls

- **Service Names**: Must match exactly between `serviceName` constant and registration (check existing module convention - some use lowercase, some use PascalCase)
- **Package Paths**: AIDL package must align with file directory structure
- **Dependencies**: Module CMakeLists.txt must declare version variables for imported modules
- **Versioning**: Always use "current" for active development until interface stabilizes
- **Missing @VintfStability**: All AIDL interfaces MUST have `@VintfStability` annotation
- **Custom Logging**: Never introduce custom logging - always use syslog-ng macros

## Key References

- `docs/introduction/aidl_and_binder.md` – IPC and AIDL architecture
- `docs/introduction/interface_generation.md` – Build/generation workflow
- `docs/introduction/the_software_stack.md` – Software stack overview
- `docs/vsi/filesystem/current/logging_system.md` – Logging policy
- `docs/halif/key_concepts/hal/hal_naming_conventions.md` – Naming standards
- `CMakeModules/CompileAidl.cmake` – AIDL build integration
- `build-tools/linux_binder_idl/BUILD.md` – Binder SDK production build guide (Yocto recipes, cross-compilation, runtime setup)
- Example modules: `audiodecoder/current/`, `deviceinfo/current/`, `boot/current/`

## Versioning & Compatibility

### Core Versioning Principles

- **Backward Compatibility is Mandatory**: All version increments (v1→v2→v3) MUST be fully backward-compatible
- **Version Numbers are Incremental**: Each version includes ALL features from previous versions
- **No Breaking Changes**: Breaking changes require creating a completely new interface (e.g., `IBootNew`)
- **First Freeze Special Case**: When creating version 1, compatibility validation is automatically skipped

### Compatibility Rules

**✅ Allowed Changes (Backward-Compatible):**
- ADD new methods at the END of an interface
- ADD new fields at the END of a parcelable/struct
- ADD new enum values (with fallback handling)
- ADD new optional parameters with defaults

**❌ Prohibited Changes (Breaking):**
- Remove methods or fields
- Change method signatures or field types
- Reorder methods or fields
- Rename methods or fields

### Pre-Copy Validation

The build system validates compatibility **BEFORE** copying source changes to `stable/aidl/`:

```bash
./build_interfaces.sh boot
# If incompatible changes detected:
# ❌ Pre-validation FAILED: Source changes are incompatible with existing stable API
# Breaking changes are NOT allowed - create new interface (IBootNew) instead
```

**Validation workflow:**
1. First update: No validation (no existing `stable/aidl/{module}/current/`)
2. Subsequent updates: Compares source against existing `stable/aidl/{module}/current/`
3. Freezing v1: Skips validation (no frozen versions to compare against)
4. Freezing v2+: Validates v2 is compatible with v1

### Versioning Workflow

```bash
# 1. Develop in module/current/ (complete freedom before first freeze)
vim boot/current/com/rdk/hal/boot/IBoot.aidl

# 2. Build and validate
./build_interfaces.sh boot

# 3. When ready, freeze as v1
./freeze_interface.sh boot
# Creates: stable/aidl/boot/1/, lib boot-v1-cpp.so

# 4. Continue development for v2 in boot/current/
# (Only backward-compatible additions allowed now)

# 5. Build validates compatibility automatically
./build_interfaces.sh boot
# ✅ Pre-validation passed: source changes are backward-compatible

# 6. Freeze v2 when ready
./freeze_interface.sh boot
```

### Client Version Discovery

Clients should check server version and adapt behavior:

```cpp
int32_t serverVersion;
bootService->getInterfaceVersion(&serverVersion);

if (serverVersion >= 2) {
    bootService->newV2Method();  // Use v2 feature
} else {
    bootService->oldV1Method();  // Fallback
}
```

### Documentation

- **Versioning Guide**: [docs/halif/versioning-guide.md](docs/halif/versioning-guide.md) - Complete versioning strategy and workflow
- **Client Patterns**: [docs/halif/client-patterns.md](docs/halif/client-patterns.md) - Version discovery and graceful degradation patterns
- **Migration Guide**: [docs/halif/migration-guide.md](docs/halif/migration-guide.md) - Step-by-step migration instructions
- **Examples**: [examples/aidl_versioning/](examples/aidl_versioning/) - Working multi-version examples

### Testing Versioning

```bash
# Test validation logic
./build_interfaces.sh test-validation

# Tests verify:
# ✅ First update succeeds (no prior version)
# ✅ Adding methods succeeds (compatible)
# ✅ Removing methods fails (incompatible)
# ✅ Changing signatures fails (incompatible)
```

## Workflow Decision Tree

**I need to...**

### Modify an existing AIDL interface
1. Edit `{module}/current/com/rdk/hal/{module}/*.aidl`
2. Run `./build_interfaces.sh {module}` (validates compatibility automatically)
3. If validation fails: Only backward-compatible changes allowed (add methods at end, add fields at end)
4. Commit both source and generated code: `git add {module}/current stable/`

### Create a new HAL module
1. Copy structure from existing module (e.g., `boot/current/`)
2. Update package names in AIDL files (`com.rdk.hal.{newmodule}`)
3. Create `hfp-{module}.yaml` with capabilities
4. Add `CMakeLists.txt` (3 lines: `INTERFACE_TARGET`, `INTERFACE_VERSION`, `target_build_interfaces_libraries()`)
5. Build: `./build_interfaces.sh {module}`

### Prepare for production release (freeze interface)
1. Ensure interface is stable and tested
2. Run `./freeze_interface.sh {module}` (creates v1, v2, etc.)
3. Future changes to `{module}/current/` must remain backward-compatible with frozen version

### Cross-compile for embedded target (Yocto)
- **DO NOT** use `build_interfaces.sh` or `build_binder.sh`
- Use direct CMake with Yocto-provided compilers and SDK
- See "Production Workflow (Yocto/BitBake)" section above

### Debug build failures
```bash
# Check if Binder SDK is built
ls out/target/.sdk_ready  # Should exist for development builds

# Verify AIDL compiler
which aidl  # Should be in PATH after build_binder.sh

# Clean rebuild
./build_interfaces.sh cleanall
./build_binder.sh
./build_interfaces.sh {module}

# Check compatibility validation logs
./build_interfaces.sh {module} 2>&1 | grep -A 10 "compatibility\|validation"
```

## Common Error Messages

| Error | Cause | Solution |
|-------|-------|----------|
| `aidl: command not found` | Binder SDK not built | Run `./build_binder.sh` |
| `Pre-validation FAILED: incompatible changes` | Breaking AIDL changes | Only add methods/fields at end, don't remove/reorder |
| `Package path mismatch` | AIDL package doesn't match directory | Ensure `package com.rdk.hal.X` matches `com/rdk/hal/X/` path |
| `serviceName not found` | Missing service name constant | Add `const @utf8InCpp String serviceName = "module"` to main interface |
| `@VintfStability missing` | Annotation missing | Add `@VintfStability` above interface declaration |
| Binder SDK ARM build: "uses VFP register arguments" linker error | Yocto toolchain file conflicts with CFLAGS | Ensure CMAKE_TOOLCHAIN_FILE is unset or compatible with manual CFLAGS/LDFLAGS |
| Binder SDK build: "No shared libraries found" | CMake configure or build failed | Check CMake output for compilation/linking errors; script now fails loudly |

## Contribution Guidelines

- **English Dictionary**: Use UK English spelling in comments and documentation
- **Code Style**: Follow existing code patterns for consistency
- **Pull Requests**: Target `develop` branch with descriptive titles and linked issues
- **Reviews**: Ensure at least one approval from a core maintainer before merging
- **Testing**: VTS Testing for all modules L1-L4 is defined through documentation and external to this workspace

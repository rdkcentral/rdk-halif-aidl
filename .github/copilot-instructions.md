# RDK HAL AIDL Copilot Instructions

This codebase defines **RDK Hardware Abstraction Layer interfaces using Android AIDL** for embedded platforms. Each HAL module exposes hardware functionality via IPC using Android Binder for Linux.

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
│   ├── CMakeLists.txt         # Module build configuration
│   ├── hfp-{module}.yaml      # HAL Feature Profile (capabilities)
│   └── com/rdk/hal/{module}/  # AIDL interface definitions
│       ├── I{Module}Manager.aidl  # Manager interface (typical pattern for complex modules)
│       ├── I{Module}.aidl         # Main/Resource interface (stateless for simple modules)
│       ├── Capabilities.aidl      # Runtime capability discovery
│       └── *.aidl                 # Supporting types/enums/listeners
└── gen/                       # Generated code (not in git)
    └── {version}/
        ├── cpp/               # C++ implementation files
        └── h/                 # C++ header files
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
- Format: `{module}` or `{category}.{module}` (lowercase with dot separators)
- Simple modules: `"boot"`, `"cec"`, `"panel"`
- Categorized modules: `"sensor.motion"`, `"sensor.thermal"`, `"broadcast.tuner"`
- Use the module directory path with dots instead of slashes

```aidl
// Standard pattern in main interfaces
package com.rdk.hal.boot;

@VintfStability
interface IBoot {
    const @utf8InCpp String serviceName = "boot";
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

### Prerequisites

1. Install binder tools: `./install_binder.sh` (downloads linux_binder_idl into `build-tools/`)
2. Ensure kernel binder support is enabled
3. Add binder tools to PATH

### Root Level Build

**IMPORTANT**: Always invoke CMake from the repo root, not module subdirectories.

```bash
# Generate AIDL code for specific module
cmake -DAIDL_TARGET={module} -DAIDL_SRC_VERSION=current .
make
```

### Required CMake Variables

- `AIDL_TARGET` (required): Module to build (e.g., "boot", "videodecoder")
- `AIDL_SRC_VERSION`: Version directory (default: "current")
- `AIDL_GEN_DIR`: Output directory (defaults to `gen/{module}/{version}`)
- `AIDL_BIN`: Path to AIDL compiler (from linux_binder_idl tools, auto-detected if in PATH)

### Default AIDL Compiler Flags

Set in `CMakeModules/CompileAidl.cmake`:
- `--min_sdk_version=33`
- `--structured`
- `--stability=vintf`

### Module CMakeLists.txt Pattern

```cmake
# Standard module build structure
set(SRC_DIR com/rdk/hal/{module})
set(SRC
    ${SRC_DIR}/I{Module}.aidl
    ${SRC_DIR}/Capabilities.aidl
    # ... other AIDL files
)
set(INCLUDE_DIRECTORY .)
```

### AIDL Code Generation

Use the custom `compile_aidl()` CMake function from `CMakeModules/CompileAidl.cmake`:

```cmake
compile_aidl(${SRC}
    INCLUDE_DIRECTORY ${INCLUDE_DIRECTORY}
    TARGET_DIRECTORY ${AIDL_GEN_DIR}
    # Additional flags as needed
)
```

### Generated Output

- C++: `{module}/gen/{version}/cpp/com/rdk/hal/{module}/...`
- Headers: `{module}/gen/{version}/h/com/rdk/hal/{module}/...`

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
5. **Build**: Use root-level CMake with `AIDL_TARGET` set to your module
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

- **Service Names**: Must match exactly between `serviceName` constant and registration (use lowercase with dots)
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
- Example modules: `audiodecoder/current/`, `deviceinfo/current/`, `boot/current/`

## Contribution Guidelines

- **English Dictionary**: Use UK English spelling in comments and documentation
- **Code Style**: Follow existing code patterns for consistency
- **Pull Requests**: Target `develop` branch with descriptive titles and linked issues
- **Reviews**: Ensure at least one approval from a core maintainer before merging
- **Testing**: VTS Testing for all modules L1-L4 is defined through documentation and external to this workspace

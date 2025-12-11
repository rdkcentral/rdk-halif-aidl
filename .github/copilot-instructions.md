# RDK HAL AIDL Copilot Instructions

This codebase defines **RDK Hardware Abstraction Layer interfaces using Android AIDL** for embedded platforms. Each HAL module exposes hardware functionality via IPC using Android Binder for Linux.

## Architecture Overview

- **HAL Modules**: Each directory (`boot/`, `videodecoder/`, `audiosink/`, etc.) contains one HAL component
- **Versioning**: All modules use `current/` directory for the active interface version
- **Package Structure**: All AIDL interfaces use `com.rdk.hal.*` package namespace
- **Service Registration**: Each HAL registers with AIDL Service Manager using predefined `serviceName` constants

## Module Structure Pattern

Every HAL module follows this exact structure:
```
{module}/
├── current/                    # Current interface version
│   ├── CMakeLists.txt         # Module build configuration  
│   ├── hfp-{module}.yaml      # HAL Feature Profile (capabilities)
│   └── com/rdk/hal/{module}/  # AIDL interface definitions
│       ├── I{Module}.aidl     # Main interface (stateless)
│       ├── Capabilities.aidl  # Runtime capability discovery
│       └── *.aidl             # Supporting types/enums
```

## Key Development Patterns

### AIDL Interface Design
- **Main Interface**: `I{Module}.aidl` with `serviceName` constant for binder registration
- **Stateless**: No open/close lifecycle - each call is independent
- **Capabilities Pattern**: `getCapabilities()` method returns supported features at runtime
- **Error Handling**: Use AIDL exceptions, not return codes

### Service Names & Packages
```aidl
// Standard pattern in main interfaces
package com.rdk.hal.boot;
interface IBoot {
    const @utf8InCpp String serviceName = "Boot";
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

## Build System

### Root Level Build
```bash
# Generate AIDL code for specific module
cmake -DAIDL_TARGET={module} -DAIDL_SRC_VERSION=current .
make
```

### Required CMake Variables
- `AIDL_TARGET`: Module to build (e.g., "boot", "videodecoder")  
- `AIDL_SRC_VERSION`: Version directory (typically "current")
- `AIDL_GEN_DIR`: Output directory (defaults to `gen/{module}/{version}`)
- `AIDL_BIN`: Path to AIDL compiler (from linux_binder_idl tools)

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

## Linux Binder Setup

### Prerequisites
1. Install binder tools: `./install_binder.sh` (downloads linux_binder_idl)
2. Ensure kernel binder support is enabled
3. Add binder tools to PATH

### AIDL Code Generation
Use the custom `compile_aidl()` CMake function from `CMakeModules/CompileAidl.cmake`:
```cmake
compile_aidl(${SRC}
    INCLUDE_DIRECTORY ${INCLUDE_DIRECTORY}  
    TARGET_DIRECTORY ${AIDL_GEN_DIR}
    # Additional flags as needed
)
```

## Cross-Module Dependencies

### Common Types
Import shared types from `common/current/com/rdk/hal/`:
- `State.aidl`: Generic component states - this will be deprecated in preference of each module defining its own State enum.
- `HALError.aidl`: Standard error codes - this will also be deprecated in favour of module-specific error handling.
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

## Documentation Structure

- **Interface Docs**: `docs/halif/{module}/current/` contains detailed HAL specifications
- **Generated Docs**: MkDocs site at `https://rdkcentral.github.io/rdk-halif-aidl/`
- **Requirements**: Each HAL doc includes numbered requirements (e.g., `HAL.{Module}.1`)

## Development Workflow

1. **Create New HAL**: Copy existing module structure, update package names
2. **Design AIDL**: Start with main interface, add supporting types  
3. **Update HFP**: Define static capabilities in `hfp-{module}.yaml`, this is the max caps of the module from the API definition, and will be tailored per platform later.
4. **Build**: Use root-level CMake with `AIDL_TARGET` set to your module
5. **Document**: Follow established documentation patterns in `docs/halif/`

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
- HFP Validation Schema: validate against HFP - HFP Schema will be added beside the best case hfp files.
- HFP Service naming {Module} is preferred across all HAL Feature Profiles.

## Common Pitfalls

- **Service Names**: Must match exactly between `serviceName` constant and registration
- **Package Paths**: AIDL package must align with file directory structure  
- **Dependencies**: Module CMakeLists.txt must declare version variables for imported modules
- **Versioning**: Always use "current" for active development until interface stabilizes

## Contribution Guidelines  

- **English Dictionary**: Use UK English spelling in comments and documentation
- **Code Style**: Follow existing code patterns for consistency
- **Pull Requests**: Target `develop` branch with descriptive titles and linked issues
- **Reviews**: Ensure at least one approval from a core maintainer before merging
- **Testing**: VTS Testing for All modules L1-L4 is defined through documentation and external to this workspace



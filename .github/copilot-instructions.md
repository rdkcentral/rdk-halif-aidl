# Copilot Instructions for RDK-HALIF-AIDL

## Project Overview
- **RDK-HALIF-AIDL** standardizes hardware abstraction layers (HALs) using Android AIDL and Binder IPC for embedded platforms.
- The codebase is organized by hardware domain (e.g., `audiodecoder`, `deviceinfo`, `hdmioutput`), each with a `current/` versioned subdirectory.
- All HAL interfaces are defined in `.aidl` files and built into C++ code using the AIDL compiler with flags: `--min_sdk_version=33 --structured --stability=vintf`.

## Architecture & Data Flow
- **Client–Server Model:** Clients interact with HAL services via AIDL-generated proxies; services implement AIDL skeletons. Communication is via Binder IPC.
- **Service Boundaries:** Each hardware domain is a separate service/module. See `../docs/introduction/aidl_and_binder.md` and `../docs/introduction/the_software_stack.md` for diagrams and details.
- **Versioning:** Each module supports versioned interfaces (e.g., `current/`). New versions are added as new subdirectories.
- **@VintfStability:** All AIDL interfaces MUST be annotated with `@VintfStability` for vendor interface stability.

## Module Structure Pattern
Every HAL module follows this structure:
```
{module}/
├── current/                    # Current interface version
│   ├── CMakeLists.txt         # Module build configuration
│   ├── hfp-{module}.yaml      # HAL Feature Profile (capabilities)
│   └── com/rdk/hal/{module}/  # AIDL interface definitions
│       ├── I{Module}Manager.aidl  # Manager interface (typical pattern)
│       ├── I{Module}.aidl         # Resource interface
│       ├── Capabilities.aidl      # Runtime capability discovery
│       └── *.aidl                 # Supporting types/enums/listeners
└── gen/                       # Generated code (not in git)
    └── {version}/
        ├── cpp/               # C++ implementation files
        └── h/                 # C++ header files
```

## Build & Generation Workflow
- **AIDL Compiler:** Use the `aidl` tool (see `../docs/introduction/interface_generation.md`).
- **Install Script:** Run `./install_binder.sh` from repo root to clone `linux_binder_idl` tools into `build-tools/`.
- **CMake:** Always invoke CMake from the repo root, not module subdirs. Example:
  ```bash
  cmake -DAIDL_TARGET=audiodecoder .
  make
  ```
- **CMake Variables:**
  - `AIDL_TARGET` (required): Module to build (e.g., `audiodecoder`).
  - `AIDL_BIN`: Path to `aidl` binary (optional, auto-detected if in PATH).
  - `AIDL_SRC_VERSION`: Interface version (default: `current`).
  - `AIDL_GEN_DIR`: Output directory for generated files (default: `gen/{module}/{version}`).
- **Generated Output:**
  - C++: `{module}/gen/{version}/cpp/com/rdk/hal/{module}/...`
  - Headers: `{module}/gen/{version}/h/com/rdk/hal/{module}/...`
- **Default AIDL Flags:** `--min_sdk_version=33 --structured --stability=vintf` (set in `CMakeModules/CompileAidl.cmake`).

## Logging & Diagnostics
- All interface and wrapper layers must use the platform's `syslog-ng` via the standard POSIX `syslog()` API.
- Use macros from a shared logging header for consistent log levels (see `../docs/vsi/filesystem/current/logging_system.md` for patterns):
  - `LOG_CRIT`, `LOG_ERR`, `LOG_WARNING`, `LOG_NOTICE` (always enabled)
  - `LOG_INFO`, `LOG_DEBUG` (controlled by `ENABLE_LOG_INFO`, `ENABLE_LOG_DEBUG` build flags)
- Log verbosity is controlled by build flags. Production builds log NOTICE and above; debug builds enable INFO/DEBUG.
- **No custom logging frameworks:** Do not introduce new logging systems; use syslog-ng macros only.
- Vendor implementations may use their own internal logging, but wrapper layers MUST use syslog-ng.

## Project Conventions
- **No direct module CMake:** Never run CMake in a module subdir; always use the root.
- **No custom logging:** Do not introduce new logging frameworks; use syslog-ng macros only.
- **Versioning:** New interface versions go in new subdirectories (e.g., `current/`, `2/`).
- **Naming:** Use lowercase with underscores for docs/files (`audio_decoder`), PascalCase for AIDL interfaces (`IAudioDecoder`), and systemd services follow `hal-{module}.service` pattern.
- **Documentation:** All build and interface docs are in `docs/` and linked from the main `README.md`.
- **UK English:** Use British English spelling in all documentation and comments.

## Key References
- `../docs/introduction/aidl_and_binder.md` – IPC and AIDL architecture
- `../docs/introduction/interface_generation.md` – Build/generation workflow
- `../docs/vsi/filesystem/current/logging_system.md` – Logging policy
- `../docs/halif/key_concepts/hal/hal_naming_conventions.md` – Naming standards
- `CMakeModules/CompileAidl.cmake` – AIDL build integration
- `audiodecoder/current/`, `deviceinfo/current/`, etc. – Example modules

---
For more, see the [online documentation](https://rdkcentral.github.io/rdk-halif-aidl/).

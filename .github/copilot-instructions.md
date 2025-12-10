# Copilot Instructions for RDK-HALIF-AIDL

## Project Overview
- **RDK-HALIF-AIDL** standardizes hardware abstraction layers (HALs) using Android AIDL and Binder IPC for embedded platforms.
- The codebase is organized by hardware domain (e.g., `audiodecoder`, `deviceinfo`, `hdmioutput`), each with a `current/` versioned subdirectory.
- All HAL interfaces are defined in `.aidl` files and built into C++ code using the AIDL compiler.

## Architecture & Data Flow
- **Client–Server Model:** Clients interact with HAL services via AIDL-generated proxies; services implement AIDL skeletons. Communication is via Binder IPC.
- **Service Boundaries:** Each hardware domain is a separate service/module. See `docs/introduction/aidl_and_binder.md` and `docs/introduction/the_software_stack.md` for diagrams and details.
- **Versioning:** Each module supports versioned interfaces (e.g., `current/`). New versions are added as new subdirectories.

## Build & Generation Workflow
- **AIDL Compiler:** Use the `aidl` tool (see `docs/introduction/interface_generation.md`).
- **CMake:** Always invoke CMake from the repo root, not module subdirs. Example:
  ```bash
  cmake -DAIDL_TARGET=audiodecoder .
  ```
- **CMake Variables:**
  - `AIDL_TARGET` (required): Module to build (e.g., `audiodecoder`).
  - `AIDL_BIN`: Path to `aidl` binary (optional).
  - `AIDL_SRC_VERSION`: Interface version (default: `current`).
  - `AIDL_GEN_DIR`: Output directory for generated files.
- **Generated Output:**
  - C++: `<module>/gen/<version>/cpp/com/rdk/hal/<module>/...`
  - Headers: `<module>/gen/<version>/h/com/rdk/hal/<module>/...`

## Logging & Diagnostics
- All interface and wrapper layers must use the platform's `syslog-ng` via the standard POSIX `syslog()` API.
- Use macros from the shared `rdk_logging.h` header for consistent log levels (`LOGF_CRITICAL`, `LOGF_ERROR`, etc.).
- Log verbosity is controlled by build flags (`ENABLE_LOG_INFO`, `ENABLE_LOG_DEBUG`). Production builds log NOTICE and above; debug builds enable INFO/DEBUG.
- See `docs/vsi/filesystem/current/logging_system.md` for policy and macro details.

## Project Conventions
- **No direct module CMake:** Never run CMake in a module subdir; always use the root.
- **No custom logging:** Do not introduce new logging frameworks; use syslog-ng macros only.
- **Versioning:** New interface versions go in new subdirectories (e.g., `current/`, `2/`).
- **Documentation:** All build and interface docs are in `docs/` and linked from the main `README.md`.

## Key References
- `docs/introduction/aidl_and_binder.md` – IPC and AIDL architecture
- `docs/introduction/interface_generation.md` – Build/generation workflow
- `docs/vsi/filesystem/current/logging_system.md` – Logging policy
- `CMakeModules/CompileAidl.cmake` – AIDL build integration
- `audiodecoder/current/`, `deviceinfo/current/`, etc. – Example modules

---
For more, see the [online documentation](https://rdkcentral.github.io/rdk-halif-aidl/).

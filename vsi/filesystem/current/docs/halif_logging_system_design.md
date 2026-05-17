# HALIF Logging System Design

This document defines the architecture and API design for the HALIF logging system. It provides a modular, per-instance logging framework aligned with syslog semantics, and supports runtime configuration and status code interpretation.

## Document History

|Date|Author|Comments|
|----|------|--------|
|04 June 2025|G.Weatherup|Draft Revision|

## Related Pages

!!! tip "Related Pages"
    - [Directory And Dynamic Linking Specification](directory_and_dynamic_linking_specification.md)

## 1. Overview

The HALIF logging system is intended for use within vendor modules. It abstracts syslog interaction, enforces log level filtering, supports dynamic configuration via a specified config file, and allows structured status reporting using module-specific lookup tables.

## 2. Logging Handle Structure

Each component that needs to log must initialize a `halif_log_handle_t`. This handle encapsulates the logging tag (typically the module name), current log level, and optional status code lookup table.

Internally, this struct includes:

* `const char* tag`: Module identifier used in log prefixes.
* `halif_log_level_t level`: Current effective log level.
* `halif_status_lookup_t* status_table`: Optional pointer to user-defined status strings.
* `const char* config_path`: Path to the module's loglevel config file.
* Timestamp or flag for monitoring config reload.

## 3. Log Levels

Log levels are aligned with syslog constants to support integration with the platform logging system:

* `HALIF_LOG_FATAL`   = LOG_CRIT
* `HALIF_LOG_ERROR`   = LOG_ERR
* `HALIF_LOG_WARN`    = LOG_WARNING
* `HALIF_LOG_INFO`    = LOG_INFO
* `HALIF_LOG_DEBUG`   = LOG_DEBUG

## 4. Core API

### halif_log_open

Initializes a log handle for a given module.

```c
halif_log_handle_t* halif_log_open(const char* logShortPrefix, const char* configPath);
```

Loads the initial log level from the config file and prepares the handle for use.

### halif_log_close

Releases any resources held by the logging handle.

```c
void halif_log_close(halif_log_handle_t* handle);
```

### halif_log_write

Logs a formatted message at a given severity level. Filtering is handled internally by the logging system.

```c
void halif_log_write(halif_log_handle_t* handle, halif_log_level_t level, const char* fmt, ...);
```

## 5. Logging Macros

To simplify use, macros are provided for each log level. These macros delegate directly to `halif_log_write()` and automatically include the function name and line number:

* `#define HALIF_LOG_FATAL(log_instance, fmt, ...) halif_log_write(log_instance, HALIF_LOG_FATAL, "[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)`
* `#define HALIF_LOG_ERROR(log_instance, fmt, ...) halif_log_write(log_instance, HALIF_LOG_ERROR, "[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)`
* `#define HALIF_LOG_WARN(log_instance, fmt, ...) halif_log_write(log_instance, HALIF_LOG_WARN, "[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)`
* `#define HALIF_LOG_INFO(log_instance, fmt, ...) halif_log_write(log_instance, HALIF_LOG_INFO, "[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)`
* `#define HALIF_LOG_DEBUG(log_instance, fmt, ...) halif_log_write(log_instance, HALIF_LOG_DEBUG, "[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)`

## 6. Runtime Configuration

Each handle loads its log level from a config file, typically located at:

```bash
/vendor/<module>/log/loglevel.conf
```

The format of the file is:

```bash
loglevel=error
```

The HALIF system may monitor this file using `inotify` or polling to support runtime log level updates.

### halif_log_set_level

Allows the caller to override the current log level manually at runtime.

```c
void halif_log_set_level(halif_log_handle_t* handle, halif_log_level_t level);
```

## 7. Status Code Logging

### halif_log_set_status_table

Registers a lookup table of numeric status codes to human-readable strings with a logging handle.

```c
void halif_log_set_status_table(halif_log_handle_t* handle, const halif_status_lookup_t* lookup);
```

### halif_log_status

Logs a function return code using the registered status table. If the code is recognized, it is logged by name and value; otherwise, it logs the numeric value with an "unknown" label.

```c
void halif_log_status(halif_log_handle_t* handle, const char* function, uint32_t status_code);
```

### HALIF_LOG_STATUS Macro

```c
#define HALIF_LOG_STATUS(handle, status_code) \
    halif_log_status(handle, __func__, status_code)
```

## 8. Example Usage

```c
const const char *module_status_strs[] =
{
    "STATUS_OK",
    "STATUS_INVALID_INSTANCE",
    "STATUS_INVALID_PARAM",
    "STATUS_NOT_FOUND",
    "STATUS_MAX"
};

halif_log_handle_t *module_log_instance = halif_log_open("MODULE", "/vendor/module/log/loglevel.conf");
const char *resultString;

halif_log_set_status_table(module_log_instance, module_status_strs);

HALIF_LOG_RESULT(module_log_instance, &resultString, STATUS_NOT_FOUND);
HALIF_LOG_INFO(module_log_instance, "Initialization complete Status: [%s]", resultString);
```

* Example Output

```c
Jun  4 15:35:01:MODULE[PID]:[some_function_name:123]:Initialization complete Status: [STATUS_NOT_FOUND (3)]
```

## 9. Legacy Printf Fallback Support

To support incremental mitigation from legacy `printf()`-based logging, the HALIF system provides a fallback mechanism.

### Static Handle

Each module implicitly declares:

```c
static halif_log_handle_t* log_instance;
```

This handle is automatically scoped to the module, ensuring no cross-module conflicts.

### Printf Macro Override

To convert `printf` to HALIF log module, users should add a macro such as:

```c
static halif_log_handle_t* printfLogHandle;
#define printf(fmt, ...) \
    do { \
        if (printfLogHandle) \
            halif_log_write(printfLogHandle, HALIF_LOG_INFO, fmt, ##__VA_ARGS__); \
    } while (0)
...
    printfLogHandle = halif_log_open("MODULE", "/vendor/module/log/loglevel.conf");
```

This allows existing `printf()` calls to be captured and routed through HALIF without requiring immediate code changes.

### Migration Path

1. Each module includes `halif_log.h`.
2. The static `log_instance` is initialized via `halif_log_open()`.
3. Legacy `printf()` calls automatically use HALIF.
4. Developers incrementally replace `printf()` with `HALIF_LOG_*` macros.
5. Once fully migrated, the `printf` macro override can be removed.

### Example

```c
#include "halif_log.h"

void module_init() 
{
    printfLogHandle = halif_log_open("MODULE", "/vendor/module/log/loglevel.conf");
    printf("Initializing module...\n"); // Routed through HALIF
}

void module_deinit() 
{
    halif_log_close(printfLogHandle);
    printfLogHandle = NULL;
}
```

This fallback strategy enables a controlled and reversible transition to structured logging.

## 10. Utility Macros

### HALIF_MODULE_CONFIG_PATH

Optional macro to create a module config path:

```c
#define HALIF_MODULE_CONFIG_PATH(module) "/vendor/" module "/log/loglevel.conf"
```

Usage:

```c
halif_log_handle_t* log_instance;

    log_instance = halif_log_open("MOD", HALIF_MODULE_CONFIG_PATH("module"));
```

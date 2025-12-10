# Logging System

This document defines how modules should use the **syslog-ng** service provided by the vendor layer for all runtime logging. It establishes a **common logging framework**, build-time verbosity controls, and clear usage policy for log levels in production and debug environments.

The design removes the need for a custom logging subsystem — all modules interact with syslog-ng directly through the standard POSIX `syslog()` API.

---

## Document History

| Date        | Author             | Comments                                              |
| ----------- | ------------------ | ----------------------------------------------------- |
| 25 Sept 2025 | G. Weatherup | Upgraded to full syslog-ng concepts |

---

!!! tip "Related Pages"
    - [Directory And Dynamic Linking Specification](directory_and_dynamic_linking_specification.md)

## Overview

The logging system defines how RDK HAL interface layers and associated wrapper components use the **syslog-ng–based system logging infrastructure** provided by the platform.

This implementation provides a **common and consistent logging method** for HAL interface layers to:

- Use standardized severity levels (`LOG_CRIT`, `LOG_ERR`, `LOG_WARNING`, etc.).
- Maintain uniform formatting and verbosity control across all HAL and vendor integrations.
- Ensure log output integrates seamlessly with the platform’s existing **syslog-ng** pipeline and vendor log management tools.

!!! note "Integration with vendor implementations"
    In many environments, **vendors already implement their own logging systems** or frameworks within their deliveries.
    The purpose of this logging design is **not to replace or redefine vendor logging systems**, but rather to:

    - Provide a **consistent logging mechanism** for the *wrapper and interface layers* that sit between the RDK HAL Interface (HAL IF) and the vendor implementation.
    - Ensure messages from these wrapper layers conform to common RDK syslog-ng formatting and severity conventions.
    - Allow smooth coexistence with existing vendor logging — for example, a HAL wrapper may log both via syslog-ng (for system-wide visibility) and via the vendor’s internal mechanism (for component diagnostics).

    Vendors are **not required to adopt** the syslog-ng–based logging macros within their proprietary HAL implementations. Instead, they may continue to use their preferred internal frameworks, provided that the **interface layers exposed to RDK** follow this standardized logging structure.

### Key Principles

| Category               | Description                                                                  |
| ---------------------- | ---------------------------------------------------------------------------- |
| **Interface**          | Modules call `syslog()` directly. No wrapper.                                |
| **Control**            | Verbosity controlled by build flags (`ENABLE_LOG_INFO`, `ENABLE_LOG_DEBUG`). |
| **Routing**            | Syslog-ng filters and routes based on `program()` and `level()`.             |
| **Production Policy**  | NOTICE and above are enabled; INFO and DEBUG are disabled.                   |
| **Engineering Builds** | Enable INFO and DEBUG for diagnostics and component-level tracing.           |

---

## Log Levels

Log levels are aligned with syslog-ng priority semantics. The table defines when each level should be used and whether it is enabled in production.

| Syslog Level  | Enabled by Default | Controlled By      | Purpose                                                                 |
| ------------- | ------------------ | ------------------ | ----------------------------------------------------------------------- |
| `LOG_CRIT`    | ✅ Always           | N/A                | Unrecoverable error; requires restart or recovery action.               |
| `LOG_ERR`     | ✅ Always           | N/A                | Runtime failure; user-visible fault.                                    |
| `LOG_WARNING` | ✅ Always           | N/A                | Recoverable condition; degraded operation.                              |
| `LOG_NOTICE`  | ✅ Always           | N/A                | **System milestone** (e.g., initialization complete, start/stop event). |
| `LOG_INFO`    | ⚙️ Optional        | `ENABLE_LOG_INFO`  | Routine operational information; enabled in debug builds only.          |
| `LOG_DEBUG`   | ⚙️ Optional        | `ENABLE_LOG_DEBUG` | Detailed trace-level diagnostics; for engineering builds.               |

**Policy Summary:**

- Production images log **NOTICE and above** only.
- Debug builds add INFO-level detail.
- Engineering builds enable DEBUG-level traces for selected components.

---

## Common Logging Framework for Module Inclusion

A shared header provides consistent macros for all modules.
This header does **not** redefine syslog constants or handle initialization — each module still calls `openlog()`/`closelog()` locally.

> File: `rdk_logging.h`

```c
#pragma once
#include <syslog.h>

/* ---- Always-on severities ---- */
#define LOGF_CRITICAL(fmt, ...) syslog(LOG_CRIT,    fmt, ##__VA_ARGS__)
#define LOGF_ERROR(fmt, ...)    syslog(LOG_ERR,     fmt, ##__VA_ARGS__)
#define LOGF_WARNING(fmt, ...)  syslog(LOG_WARNING, fmt, ##__VA_ARGS__)
#define LOGF_NOTICE(fmt, ...)   syslog(LOG_NOTICE,  fmt, ##__VA_ARGS__)

/* ---- Optional severities (build controlled) ---- */
#ifdef ENABLE_LOG_INFO
  #define LOGF_INFO(fmt, ...)   syslog(LOG_INFO, fmt, ##__VA_ARGS__)
#else
  #define LOGF_INFO(fmt, ...)   do {} while (0)
#endif

#ifdef ENABLE_LOG_DEBUG
  #define LOGF_DEBUG(fmt, ...)  syslog(LOG_DEBUG, "[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#else
  #define LOGF_DEBUG(fmt, ...)  do {} while (0)
#endif
```

### Characteristics

- **Compile-time filtering:** Disabled levels are compiled out (no runtime cost).
- **Consistent semantics:** All modules log through identical macros.
- **No local `#ifdef` guards:** Macros automatically include/exclude the correct levels.

---

## Build-Time Configuration

Verbosity is determined by compiler defines set in the vendor build system.

**Example build configuration:**

```make
# Production build (default)
# Includes CRITICAL, ERROR, WARNING, NOTICE
# No flags required.

# Debug build (adds INFO)
CFLAGS += -DENABLE_LOG_INFO

# Engineering build (adds INFO + DEBUG)
CFLAGS += -DENABLE_LOG_INFO -DENABLE_LOG_DEBUG
```

### Resulting Behavior

| Build Type      | Enabled Levels             | Typical Use                           |
| --------------- | -------------------------- | ------------------------------------- |
| **Production**  | CRIT, ERR, WARNING, NOTICE | Deployed images.                      |
| **Debug**       | + INFO                     | Internal debugging, QA testing.       |
| **Engineering** | + DEBUG                    | Developer tracing at component level. |

---

## Example Module Usage

```c
#include <syslog.h>
#include "rdk_logging.h"

int tuner_init(void)
{
    openlog("TUNER_HAL", LOG_PID, LOG_USER);

    LOGF_NOTICE("Tuner HAL initialization complete");
    LOGF_WARNING("Using fallback configuration");

    LOGF_INFO("DSP firmware version %s", dsp_version());
    LOGF_DEBUG("PLL lock value=0x%x bias=%d", read_pll(), read_bias());

    closelog();
    return 0;
}

void tuner_deinit(void)
{
    LOGF_NOTICE("Tuner HAL shutdown");
}
```

### Example Output (Production)

```log
Oct 25 10:44:02 TUNER_HAL[1021]: Tuner HAL initialization complete
Oct 25 10:44:02 TUNER_HAL[1021]: Using fallback configuration
Oct 25 10:45:11 TUNER_HAL[1021]: Tuner HAL shutdown
```

### Example Output (Engineering Build)

```log
Oct 25 10:44:02 TUNER_HAL[1021]: DSP firmware version 1.02.07
Oct 25 10:44:02 TUNER_HAL[1021]: [tuner_init:47] PLL lock value=0x32 bias=9
```

---

## Runtime Configuration (syslog-ng Filtering)

The vendor’s syslog-ng configuration handles message routing based on `program()` and `level()`:

```syslog
source s_sys { system(); internal(); };

# Filter and routing example
filter f_tuner { program("TUNER_HAL"); };
filter f_runtime { level(notice..emerg); };  # production
filter f_debug   { level(debug..emerg);  };  # debug/engineering

destination d_tuner_file { file("/var/log/TUNER_HAL.log" create-dirs(yes)); };

log { source(s_sys); filter(f_tuner); filter(f_runtime); destination(d_tuner_file); };
```

!!! warning "Filtering / Routing Control"
    Modules **do not modify syslog-ng** configuration; any routing or filtering changes are handled by the vendor integration layer. Although these can be overriden (but must never be commited), during development.

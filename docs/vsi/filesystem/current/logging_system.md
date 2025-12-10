# Logging System

## Document History

| Date        | Author             | Comments                                              |
| ----------- | ------------------ | ----------------------------------------------------- |
| 25 Sept 2025 | G. Weatherup | Upgraded to full syslog-ng concepts |

---

This document defines how modules should use the **syslog-ng** service provided by the vendor layer for all runtime logging. It establishes a **common logging framework**, build-time verbosity controls, and clear usage policy for log levels in production and debug environments.

The design removes the need for a custom logging subsystem — all modules interact with syslog-ng directly through the standard POSIX `syslog()` API.

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

!!! note "**Governance**"
    - The logging interface, conventions, and requirements described here are managed at the system level, with governance and rules discussed and agreed globally across the RDK ecosystem. These are not per-vendor or per-component decisions, but are established as part of the platform-wide architecture.

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

## Systemd Startup and Ordering Requirements

The syslog-ng service **must be started by systemd at the `early` target**, before any vendor layer or component is initialized. This ensures that all logging from RDK HAL interface layers and wrappers is available from the earliest point in system startup.

System-wide logging will be capped by file size and data throughput. The detailed policy for log rotation, file size limits, and throughput constraints is **TBD** and will be defined in a future revision.

## Example Logging Macros for Module Inclusion

The following is provided as a **conceptual example** for engineers. It illustrates how you can use macros to control logging output in your module. Each module should still call `openlog()`/`closelog()` and may consider to adapt these macros as needed.

```c
#include <syslog.h>

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

### Build-Time Disabling of INFO/DEBUG

If you want to **disable INFO and DEBUG logging at build time** (to reduce binary size or runtime overhead in production), you can use compiler flags to exclude these macros. For example:

```make
# Production build (default)
# Only CRITICAL, ERROR, WARNING, NOTICE are included
# No flags required.

# Debug Engineering build (adds INFO + DEBUG)
CFLAGS += -DENABLE_LOG_INFO -DENABLE_LOG_DEBUG
```

This approach ensures that INFO and DEBUG logging code is compiled out of production binaries, while always-on severities (CRITICAL, ERROR, WARNING, NOTICE) remain available for essential diagnostics.

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

## Integration with 3rd Party Logging Systems

For 3rd party HALs or external code, integration with the RDK logging system should be achieved by **simple redirection** methods, without modifying the 3rd party system itself. Recommended approaches include:

- Capturing output from `printf` or similar functions and redirecting it to a file or socket monitored by syslog-ng.
- Re-sourcing or redirecting standard error (stderr) to syslog-ng using system-level configuration.
- Using syslog-ng's file or program source to ingest external logs and route them according to severity and program name.

Direct modification of 3rd party code (such as replacing its logging system) is discouraged. Instead, use non-invasive filtering or forwarding to ensure relevant logs are pushed into syslog-ng for unified system-wide visibility and diagnostics.

This approach ensures that all critical, error, and diagnostic information from 3rd party components is available through the standard RDK logging pipeline, supporting consistent monitoring and troubleshooting, while preserving the integrity of external systems.

---

## Example Module Usage

```c
#include <syslog.h>
#include "rdk_logging.h"

int tuner_init(void)
{
    openlog("TUNER_HAL", LOG_PID, LOG_USER);

    syslog(LOG_NOTICE,"Tuner HAL initialization complete");
    syslog(LOG_WARNING,"Using fallback configuration");

    LOGF_INFO("DSP firmware version %s", dsp_version());
    LOGF_DEBUG("PLL lock value=0x%x bias=%d", read_pll(), read_bias());

    closelog();
    return 0;
}

void tuner_deinit(void)
{
    syslog(LOG_NOTICE,"Tuner HAL shutdown");
}
```

### Example Output (Production)

```syslog
Oct 25 10:44:02 TUNER_HAL[1021]: Tuner HAL initialization complete
Oct 25 10:44:02 TUNER_HAL[1021]: Using fallback configuration
Oct 25 10:45:11 TUNER_HAL[1021]: Tuner HAL shutdown
```

On engineering builds extra information is output

```syslog
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
    Modules **do not modify syslog-ng** configuration; any routing or filtering changes are expected to controlled at a system level. Although these can be overriden during development.

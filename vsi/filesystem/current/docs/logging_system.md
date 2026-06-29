# Logging System

## Document History

| Date        | Author             | Comments                                              |
| ----------- | ------------------ | ----------------------------------------------------- |
| 25 Sept 2025 | G. Weatherup | Upgraded to full syslog-ng concepts |
| 29 June 2026 | G. Weatherup | Transport via journald native API (`sd_journal_send()`) |

---

This document defines how modules emit runtime logs into the platform logging pipeline. It establishes a **common logging framework**, build-time verbosity controls, and clear usage policy for log levels in production and debug environments.

The design removes the need for a custom logging subsystem — modules write directly to **journald** through the native `sd_journal_send()` API. `journald` is the primary collector on the platform and forwards entries to **syslog-ng**, which filters, routes, and writes the log files.

---

!!! tip "Related Pages"
    - [Directory And Dynamic Linking Specification](directory_and_dynamic_linking_specification.md)

## Overview

The logging system defines how RDK HAL interface layers and associated wrapper components emit logs into the platform's **journald + syslog-ng** logging infrastructure.

This implementation provides a **common and consistent logging method** for HAL interface layers to:

- Use standardized severity levels (`LOG_CRIT`, `LOG_ERR`, `LOG_WARNING`, etc.).
- Maintain uniform formatting and verbosity control across all HAL and vendor integrations.
- Ensure log output integrates seamlessly with the platform’s existing **journald → syslog-ng** pipeline and vendor log management tools.

### Logging Pipeline

HALIF / vendor-layer macros write directly to `journald` using the native `sd_journal_send()` API. `journald` is the primary collector and forwards entries to `syslog-ng`, which applies filtering/routing and writes the files:

```text
HALIF_LOG_* → sd_journal_send() → journald → syslog-ng → files
```

Using the journald native API gives the most direct path to the primary collector and avoids the cyclic-loop risk that arises when logs are submitted via `/dev/log` while `journald` is configured to forward to `syslog-ng`. `syslog-ng` sources from journald (`source(s_journald)`) and remains the single downstream transport for filtering, routing, rotation, and file output.

The framework is a thin set of compile-time macros over `sd_journal_send()`. Its only runtime dependency is `libsystemd` (already present on the platform); it introduces no logging backend framework, no runtime backend selection, no RDK Logger dependency, and no log4c dependency, keeping the vendor layer independent of middleware logging.

!!! note "Integration with vendor implementations"
    In many environments, **vendors already implement their own logging systems** or frameworks within their deliveries.
    The purpose of this logging design is **not to replace or redefine vendor logging systems**, but rather to:

    - Provide a **consistent logging mechanism** for the *wrapper and interface layers* that sit between the RDK HAL Interface (HAL IF) and the vendor implementation.
    - Ensure messages from these wrapper layers conform to common RDK formatting and severity conventions in the journald → syslog-ng pipeline.
    - Allow smooth coexistence with existing vendor logging — for example, a HAL wrapper may log both via journald (for system-wide visibility) and via the vendor’s internal mechanism (for component diagnostics).

    Vendors are **not required to adopt** the HALIF logging macros within their proprietary HAL implementations. Instead, they may continue to use their preferred internal frameworks, provided that the **interface layers exposed to RDK** follow this standardized logging structure.

!!! note "**Governance**"
    - The logging interface, conventions, and requirements described here are managed at the system level, with governance and rules discussed and agreed globally across the RDK ecosystem. These are not per-vendor or per-component decisions, but are established as part of the platform-wide architecture.

### Key Principles

| Category               | Description                                                                  |
| ---------------------- | ---------------------------------------------------------------------------- |
| **Interface**          | Modules call `sd_journal_send()` directly. No runtime backend.               |
| **Control**            | Verbosity controlled by build flags (`ENABLE_LOG_INFO`, `ENABLE_LOG_DEBUG`). |
| **Routing**            | Syslog-ng sources from journald; routes on identifier and `level()`.         |
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
| `LOG_NOTICE`  | ✅ Always           | N/A                | **System milestone** (e.g., initialisation complete, start/stop event). |
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

The following is provided as a **conceptual example** for engineers. It illustrates how you can use macros to control logging output in your module. Messages are submitted to `journald` via `sd_journal_send()`, tagging each entry with `PRIORITY=` (the syslog severity) and a `SYSLOG_IDENTIFIER=` so that `syslog-ng` can filter and route by program name.

!!! note "`fmt` must be a string literal"
    These macros build the journald field with the string-literal concatenation `"MESSAGE=" fmt`, so `fmt` must be a compile-time string literal. To log a runtime `char*`, use `"MESSAGE=%s"` and pass the pointer as an argument (e.g. `LOGF(LOG_INFO, "%s", msg)`).

```c
#include <syslog.h>          /* LOG_* severity constants */
#include <systemd/sd-journal.h>

#define MODULE_TAG "TUNER_HAL"

/* ---- Always-on severities ---- */
#define LOGF(prio, fmt, ...) \
    sd_journal_send("PRIORITY=%d", (prio), \
                    "SYSLOG_IDENTIFIER=%s", MODULE_TAG, \
                    "MESSAGE=" fmt, ##__VA_ARGS__, NULL)

/* ---- Optional severities (build controlled) ---- */
#ifdef ENABLE_LOG_INFO
  #define LOGF_INFO(fmt, ...)   LOGF(LOG_INFO, fmt, ##__VA_ARGS__)
#else
  #define LOGF_INFO(fmt, ...)   do {} while (0)
#endif

#ifdef ENABLE_LOG_DEBUG
  #define LOGF_DEBUG(fmt, ...)  sd_journal_send("PRIORITY=%d", LOG_DEBUG, \
                                  "SYSLOG_IDENTIFIER=%s", MODULE_TAG, \
                                  "CODE_FILE=%s", __FILE__, "CODE_LINE=%d", __LINE__, \
                                  "MESSAGE=" fmt, ##__VA_ARGS__, NULL)
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
#include <syslog.h>          /* LOG_* severity constants */
#include <systemd/sd-journal.h>

#define MODULE_TAG "TUNER_HAL"

#define LOGF(prio, fmt, ...) \
    sd_journal_send("PRIORITY=%d", (prio), \
                    "SYSLOG_IDENTIFIER=%s", MODULE_TAG, \
                    "MESSAGE=" fmt, ##__VA_ARGS__, NULL)

/* ---- Optional severities (build controlled) ---- */
#ifdef ENABLE_LOG_INFO
  #define LOGF_INFO(fmt, ...)   LOGF(LOG_INFO, fmt, ##__VA_ARGS__)
#else
  #define LOGF_INFO(fmt, ...)   do {} while (0)
#endif

#ifdef ENABLE_LOG_DEBUG
  #define LOGF_DEBUG(fmt, ...)  sd_journal_send("PRIORITY=%d", LOG_DEBUG, \
                                  "SYSLOG_IDENTIFIER=%s", MODULE_TAG, \
                                  "CODE_FILE=%s", __FILE__, "CODE_LINE=%d", __LINE__, \
                                  "MESSAGE=" fmt, ##__VA_ARGS__, NULL)
#else
  #define LOGF_DEBUG(fmt, ...)  do {} while (0)
#endif

int tuner_init(void)
{
    LOGF(LOG_NOTICE,  "Tuner HAL initialisation complete");
    LOGF(LOG_WARNING, "Using fallback configuration");

    LOGF_INFO("DSP firmware version %s", dsp_version());
    LOGF_DEBUG("PLL lock value=0x%x bias=%d", read_pll(), read_bias());

    return 0;
}

void tuner_deinit(void)
{
    LOGF(LOG_NOTICE, "Tuner HAL shutdown");
}
```

### Example Output (Production)

```syslog
Oct 25 10:44:02 TUNER_HAL[1021]: Tuner HAL initialisation complete
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

The vendor’s syslog-ng configuration sources entries from journald and routes them based on identifier and `level()`. The `SYSLOG_IDENTIFIER=` set by `sd_journal_send()` is matched with `program()`:

```syslog
source s_journald { systemd-journal(); };

# Filter and routing example
filter f_tuner { program("TUNER_HAL"); };
filter f_runtime { level(notice..emerg); };  # production
filter f_debug   { level(debug..emerg);  };  # debug/engineering

destination d_tuner_file { file("/var/log/TUNER_HAL.log" create-dirs(yes)); };

log { source(s_journald); filter(f_tuner); filter(f_runtime); destination(d_tuner_file); };
```

!!! warning "Filtering / Routing Control"
    Modules **do not modify syslog-ng** configuration; any routing or filtering changes are expected to be controlled at a system level. Although these can be overridden during development and engineering builds.

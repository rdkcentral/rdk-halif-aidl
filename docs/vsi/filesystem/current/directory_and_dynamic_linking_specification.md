# Directory and Dynamic Linking Specification

## Document History

|Date|Author|Comments|
|----|------|--------|
|2025-05-21|G.Weatherup|Draft Revision|
|2024-12-12|G.Weatherup|Updated for multi-layer architecture|

## Related Pages

!!! tip "Related Pages"
    - [File System](file_system.md)
    - [HALIF Logging System Design](halif_logging_system_design.md)
    - [Logging System](logging_system.md)

## Purpose

This document defines the file placement and dynamic linking policies for the **layered file system architecture**. It ensures modularity, maintainability, and reliable integration of components across multiple layers.

Applicable to all modules, libraries, executables, and configuration files delivered in the `/vendor`, `/mw`, `/product`, and `/apps` layers.

!!! note "Multi-Layer Architecture"
    This specification now covers all system layers, not just `/vendor`. Each layer (`/vendor`, `/mw`, `/product`, `/apps`) follows the same structural conventions while maintaining independence. For architectural overview, see [File System](file_system.md).

## Design Principles

* **Self-contained Modules**: Each module resides within its own directory under `/<layer>/<module>/` (e.g., `/vendor/<module>/`, `/mw/<module>/`).
* **Layer Isolation**: Each layer (`/vendor`, `/mw`, `/product`, `/apps`) is an independent mount point, allowing separate updates, versioning, and integrity checks.
* **No Global Path Pollution**: Avoids modifying system-level directories like `/etc` or `/lib`, unless explicitly structured via symlinks.
* **Independent OSS Management**: Each layer manages its own Open Source Software components consumed exclusively from its mount point.

## Directory Layout

Each module in any layer should follow the directory convention:

```bash
/<layer>/<module>/              # Where <layer> is vendor, mw, product, or apps
├── bin/          # Executables specific to the module
├── lib/          # Shared/static libraries used by the module
├── etc/          # Configuration files for the module
│   └── manifest.json          # Module metadata and dependencies
├── data/         # Optional runtime or persistent module data
├── app_armor/    # Optional AppArmor profiles for the module
├── systemd/      # Optional systemd service files
├── memory/       # Static guide to resource usage declarations
│   └── usage.conf             # Memory footprint declarations
├── logs/ -> /var/log/<layer>/<module>/   # Writable logs symlink
├── ld.so.conf.d/ # Optional linker path configuration for symlink
├── VERSION       # Module version and build information (recommended)
```

### Examples by Layer

**Vendor Layer** (`/vendor/<module>/`):
```bash
/vendor/hdmi/
├── bin/hdmi-daemon
├── lib/libhdmi.so.1.0
├── etc/hdmi.conf
└── VERSION
```

**Middleware Layer** (`/mw/<module>/`):
```bash
/mw/streaming/
├── bin/stream-manager
├── lib/libstreaming.so.2.0
├── etc/streaming.conf
└── VERSION
```

**Product Layer** (`/product/<module>/`):
```bash
/product/branding/
├── data/logo.png
├── etc/theme.conf
└── VERSION
```

**Apps Layer** (`/apps/<app>/`):
```bash
/apps/netflix/
├── bin/netflix
├── lib/libnetflix.so
└── VERSION
```

## Integration Requirements

* Executables must be invoked using absolute paths (e.g., `/vendor/<module>/bin/daemon`, `/mw/<module>/bin/service`).
* Any module requiring dynamic libraries must either:
  * Embed RPATH during linking (`-Wl,-rpath,/<layer>/<module>/lib`), or
  * Rely on linker cache updates via `/etc/ld.so.conf.d/` configuration.
* Environment variables (e.g., `LD_LIBRARY_PATH`) must not be relied upon at runtime.
* Cross-layer dependencies must be declared in the module's `etc/manifest.json` file.
* Each layer maintains independence — libraries from one layer should not directly link against internal libraries of another layer unless through well-defined interfaces.

## Dynamic Linking and `dlopen()` Support

**Requirement: Module libraries must be made visible to the system linker via configuration files in `/etc/ld.so.conf.d/` to support standard dynamic linking and `dlopen()` usage.**

Each module in any layer must provide a configuration file:

```bash
/<layer>/<module>/ld.so.conf.d/<layer>-<module>.conf
```

During image creation, a symbolic link must be created:

```bash
/etc/ld.so.conf.d/<layer>-<module>.conf -> /<layer>/<module>/ld.so.conf.d/<layer>-<module>.conf
```

### Examples by Layer

**Vendor Module**:
```bash
# File: /vendor/input/ld.so.conf.d/vendor-input.conf
/vendor/input/lib

# Symlink: /etc/ld.so.conf.d/vendor-input.conf -> /vendor/input/ld.so.conf.d/vendor-input.conf
```

**Middleware Module**:
```bash
# File: /mw/streaming/ld.so.conf.d/mw-streaming.conf
/mw/streaming/lib

# Symlink: /etc/ld.so.conf.d/mw-streaming.conf -> /mw/streaming/ld.so.conf.d/mw-streaming.conf
```

**Post-Install Action:** The system must execute `ldconfig` after installation or image build to regenerate the dynamic linker cache.

## AppArmor Integration and Permissions

To maintain security boundaries and prevent privilege escalation, each module integrated into any layer must be governed by an AppArmor profile.

### AppArmor Profile Structure

Each module will include its AppArmor profile in:

```bash
/<layer>/<module>/app_armor/<layer>-<module>.profile
```

To activate the profile, a symbolic link will be created at install time:

```bash
/etc/apparmor.d/<layer>-<module>.profile -> /<layer>/<module>/app_armor/<layer>-<module>.profile
```

### Examples by Layer

**Vendor Module**:
```bash
/etc/apparmor.d/vendor-hdmi.profile -> /vendor/hdmi/app_armor/vendor-hdmi.profile
```

**Middleware Module**:
```bash
/etc/apparmor.d/mw-streaming.profile -> /mw/streaming/app_armor/mw-streaming.profile
```

### Enforcement Policy

* Profiles must be in enforced mode to provide real confinement.
* Profiles are activated via systemd unit or application launcher.
* Install scripts must create appropriate symlinks into `/etc/apparmor.d/`.
* System integrators must validate that all paths used by the module are declared.

## Update and Runtime Policy

* All layers (`/vendor`, `/mw`, `/product`, `/apps`) are treated as **read-only** at runtime.
* Writable runtime data for modules should be stored under `/var/<layer>/<module>/`.
* Updates to modules must not affect global system directories outside of `/etc/ld.so.conf.d/` and `/etc/apparmor.d/` symlinks.
* AppArmor profiles should be validated against updated module paths post-deployment.
* **Layer Independence**: Updates to one layer (e.g., `/mw`) must not require rebuilding other layers (e.g., `/vendor`), provided interface contracts are maintained.
* **Version Pinning**: Cross-layer dependencies must specify version requirements in manifest files to ensure compatibility.

## Operational Considerations

### Filesystem Access Policy

* All layers (`/vendor`, `/mw`, `/product`, `/apps`) are **read-only** at runtime.
* `/<layer>/<module>/log` is the designated **writable** path for runtime data, logs, and override configurations; this is a symbolic link from `/var/log/<layer>/<module>/`
* Modules must not write to `/etc`, `/usr`, or other immutable parts of the root filesystem.
* Each layer maintains isolated writable storage under `/var/<layer>/` to prevent cross-contamination.

### Memory Footprint Declarations

* Each module must include a `memory/usage.conf` file declaring expected heap, stack, and static memory usage.

* Format:

  ```bash
  heap=4MB
  stack=512KB
  static=1MB
  ```

* This allows the system to pre-allocate or validate resource claims during module startup.

### Systemd Service Integration

* Each module may include its own `.service` file in `/<layer>/<module>/systemd/`.
* Post-install, symlinks must be created in `/etc/systemd/system/`:

  ```bash
  /etc/systemd/system/<layer>-<module>.service -> /<layer>/<module>/systemd/<layer>-<module>.service
  ```

* Services must declare dependencies using `After=`, `Requires=`, and optionally `WatchdogSec=` for health monitoring.
* **Layer Boundaries**: Lower-layer services (e.g., vendor) should define milestone targets for upper layers to depend on, but must not directly reference upper-layer services.

### Examples by Layer

**Vendor Service**:
```bash
/etc/systemd/system/vendor-hdmi.service -> /vendor/hdmi/systemd/vendor-hdmi.service
```

**Middleware Service** (depending on vendor milestone):
```bash
# /mw/streaming/systemd/mw-streaming.service
[Unit]
Description=Streaming Middleware Service
After=vendor-layer.target
Requires=vendor-hdmi.service

[Service]
ExecStart=/mw/streaming/bin/stream-manager
```

### Log Management

* Logs must be written to:

`/<layer>/<module>/log/`

* This path must be a symbolic link to:

`/var/log/<layer>/<module>/`

Logs will be written to `/<layer>/<module>/log/`, which redirects to the writable `/var/log/<layer>/<module>/` location.

### Examples by Layer

**Vendor Module**:
```bash
/vendor/hdmi/log/ -> /var/log/vendor/hdmi/
```

**Middleware Module**:
```bash
/mw/streaming/log/ -> /var/log/mw/streaming/
```

#### Log File Rotation Integration

Each module may provide a standard logrotate config file:

```bash
/<layer>/<module>/etc/logrotation.conf
```

This file can be symlinked to `/etc/logrotate.d/<layer>-<module>` from `/<layer>/<module>/etc/logrotation.conf` to integrate with the system logrotate process.

```bash
/<layer>/<module>/log/<module>.log { 
  size 100k
  rotate 5
  compress
  delaycompress
  missingok
  notifempty
  copytruncate
}
```

This configuration ensures:

Logs are rotated once they exceed 100 KB.

Up to 5 old logs are kept.

Old logs are compressed to save space.

Logging continues uninterrupted via copytruncate.

### Log Configuration

Build-time log level configuration is defined in:

`/<layer>/<module>/etc/loglevel.conf`

Format:

`loglevel=error`

The default log level must be set to error.

### Startup Configuration Application:

During system startup, each layer's platform components are responsible for applying syslog configuration settings for their modules.

This is platform-specific and may involve setting log levels in drivers, kernel modules, or components using platform-appropriate mechanisms.

Each layer team ensures this file is parsed and its value applied according to the SoC’s logging configuration method.

At runtime, a copy of the configuration is made to a writable location:

`/<layer>/<module>/log/loglevel.conf`

Wrapper modules will read the log level from the runtime configuration file to support dynamic log level adjustments without requiring a reboot or rebuild.

Supported log levels (ordered by severity, highest to lowest):

* **fatal** – Critical errors causing immediate termination.
* **error** – Operational failures requiring attention.
* **warn** – Recoverable anomalies or warnings.
* **info** – General informational messages.
* **debug** – Development-level diagnostics.
* **trace** – Highly granular tracing for deep debugging.

### Logging Mechanism

### Syslog Usage:-

Vendor modules are expected to use syslog for log message emission wherever platform support allows.

This ensures logs are centrally accessible and manageable through standard tools (e.g., logread, journalctl, or remote syslog sinks).

Wrapper Requirement:

Direct usage of `syslog()` is not permitted.

Vendors are expected to use the logging wrapper APIs provided by the HAL (Hardware Abstraction Layer).

These wrappers:

Read and cache the active log level (as configured by the platform during startup).

Filter messages based on severity.

Format and dispatch logs appropriately to syslog or other targets.

### Version Declaration (Recommended)

* Each module should include a file `/<layer>/<module>/VERSION` with contents akin to:

  ```bash
  version=MAJOR.MINOR.PATCH
  build_date=YYYY-MM-DD HH:MM:SS UTC
  build_sha=sha256:<commit-hash>
  layer=vendor|mw|product|apps
  dependencies=<comma-separated list>
  ```

* Version should follow Semantic Versioning (SemVer).
* The `layer` field identifies which layer the module belongs to.
* The `dependencies` field lists runtime dependencies on other modules.

## Appendix: Example Integration

This section provides concrete examples of how modules can integrate with the multi-layer architecture in compliance with the directory and dynamic linking policies described above.

### Example 1: Vendor Layer Module Integration

This example shows how a vendor module integrates with the `/vendor/sysint/${sysconfdir}` structure.

### Overview

This module is installed under the path `/vendor/sysint`, with all configuration, systemd, logging, versioning, and dynamic linker artifacts scoped within this directory. Integration points such as AppArmor and ld.so.conf.d use symbolic links into `/etc/` to preserve system-wide access.

### Directory Structure

```bash
/vendor/sysint/
├── etc/
│   ├── partners_defaults_device.json
│   ├── device-vendor.properties
│   ├── rfcdefaults/
│   └── logrotation.conf
├── lib/rdk/
│   └── ...
├── systemd/
│   └── start-up-scripts.service
├── app_armor/
│   └── vendor-sysint.profile
├── ld.so.conf.d/
│   └── vendor-sysint.conf
└── VERSION
```

### Installation Snippet (Yocto-style `do_install()`)

```bash
INSTALL_ROOT="/vendor/sysint"
install -d ${D}${INSTALL_ROOT}${sysconfdir}
install -d ${D}${INSTALL_ROOT}${sysconfdir}/rfcdefaults
install -d ${D}${INSTALL_ROOT}${base_libdir}/rdk
install -d ${D}${INSTALL_ROOT}${systemd_unitdir}/system
install -d ${D}/etc/ld.so.conf.d
install -d ${D}/etc/apparmor.d
install -d ${D}/etc/systemd/system
install -d ${D}/etc/logrotate.d

# Config and Binary Placement
install -m 0644 ${S}/etc/partners_defaults_device.json ${D}${INSTALL_ROOT}${sysconfdir}
install -m 0755 ${S}/etc/device-vendor.properties ${D}${INSTALL_ROOT}${sysconfdir}
install -m 0755 ${S}/lib/rdk/* ${D}${INSTALL_ROOT}${base_libdir}/rdk
install -m 0644 ${S}/systemd_units/start-up-scripts.service ${D}${INSTALL_ROOT}${systemd_unitdir}/system

# Clean Up Pre-existing Keys
for key in MODEL_NUM FW_VERSION_TAG1 FW_VERSION_TAG2 MANUFACTURE FRIENDLY_ID USB_POWER_GPIO_NUMBER USB_A_POWER_GPIO_NUMBER MFG_NAME; do
  sed -i "/$key/d" ${D}${INSTALL_ROOT}${sysconfdir}/device-vendor.properties
  echo "$key=<default_or_variable_value>" >> ${D}${INSTALL_ROOT}${sysconfdir}/device-vendor.properties
done

# AppArmor
install -d ${D}${INSTALL_ROOT}/app_armor
install -m 0644 ${S}/etc/apparmor/vendor-sysint.profile ${D}${INSTALL_ROOT}/app_armor/
ln -sf ${INSTALL_ROOT}/app_armor/vendor-sysint.profile ${D}/etc/apparmor.d/vendor-sysint.profile

# Dynamic Linker Configuration
install -d ${D}${INSTALL_ROOT}/ld.so.conf.d
echo "${INSTALL_ROOT}/lib" > ${D}${INSTALL_ROOT}/ld.so.conf.d/vendor-sysint.conf
ln -sf ${INSTALL_ROOT}/ld.so.conf.d/vendor-sysint.conf ${D}/etc/ld.so.conf.d/vendor-sysint.conf

# Logrotate
install -m 0644 ${S}/etc/module_logrotate.conf ${D}${INSTALL_ROOT}${sysconfdir}/logrotation.conf
ln -sf ${INSTALL_ROOT}${sysconfdir}/logrotation.conf ${D}/etc/logrotate.d/sysint

# Systemd
ln -sf ${INSTALL_ROOT}${systemd_unitdir}/system/start-up-scripts.service ${D}/etc/systemd/system/vendor-sysint.service

# Version Metadata
mkdir -p ${D}${INSTALL_ROOT}
echo "src_version=$(cd ${S} && git describe --tags --always || echo unknown)" > ${D}${INSTALL_ROOT}/VERSION
echo "build_date=$(TZ=UTC date '+%Y-%m-%d %H:%M:%S UTC')" >> ${D}${INSTALL_ROOT}/VERSION

# This version reflects the git-describe version of the recipe itself (.bb file)
echo "recipe_version=$(cd $(dirname ${BBPATH})/../.. && git describe --tags --always 2>/dev/null || echo unknown)" >> ${D}${INSTALL_ROOT}/VERSION

# If other includes are referenced (e.g., sysint-oem.inc), optionally record their version too:
echo "sysint-oem.inc_version=$(cd ${LAYERDIR}/recipes-extended/sysint && git describe --tags --always sysint-oem.inc 2>/dev/null || echo unknown)" >> ${D}${INSTALL_ROOT}/VERSION
```

### Example `VERSION` File

```ini
src_version=2.5.0-123-gabcde12
build_date=2025-06-20 14:45:30 UTC
recipe_version=2.5.0-123-gabcde12
sysint-oem.inc_version=sysint-oem-1.3.2-45-gabcdef1
```

### Compliance Notes (Vendor Example)

* All artifacts are scoped to the module directory under `/vendor/sysint`.
* Global system directories are only modified via symlinks into expected locations.
* The `VERSION` file provides build provenance including Git tag of the recipe and any referenced include.
* This supports modular updates and ensures the system remains maintainable, verifiable, and secure.

### Example 2: Middleware Layer Module Integration

This example shows how a middleware module integrates with the `/mw/<module>/` structure.

#### Directory Structure

```bash
/mw/streaming/
├── bin/
│   └── stream-manager
├── lib/
│   └── libstreaming.so.2.0
├── etc/
│   ├── streaming.conf
│   ├── manifest.json
│   └── loglevel.conf
├── systemd/
│   └── mw-streaming.service
├── app_armor/
│   └── mw-streaming.profile
├── ld.so.conf.d/
│   └── mw-streaming.conf
├── memory/
│   └── usage.conf
├── logs/ -> /var/log/mw/streaming/
└── VERSION
```

#### Example manifest.json

```json
{
  "module": "streaming",
  "version": "3.1.0",
  "layer": "mw",
  "dependencies": {
    "runtime": [
      "vendor-hdmi:2.5.0",
      "vendor-audio:1.3.0"
    ],
    "build": [
      "toolchain:11.0"
    ]
  },
  "provides": [
    "libstreaming.so.2",
    "stream-manager"
  ],
  "conflicts": [],
  "oss_components": [
    {"name": "gstreamer", "version": "1.20.3", "license": "LGPL-2.1"},
    {"name": "ffmpeg", "version": "5.1.2", "license": "LGPL-2.1"}
  ]
}
```

#### Integration Snippet (Yocto-style do_install())

```bash
INSTALL_ROOT="/mw/streaming"

# Create directory structure
install -d ${D}${INSTALL_ROOT}/{bin,lib,etc,systemd,app_armor,ld.so.conf.d,memory}
install -d ${D}/etc/{ld.so.conf.d,apparmor.d,systemd/system,logrotate.d}
install -d ${D}/var/log/mw/streaming

# Install binaries and libraries
install -m 0755 ${S}/bin/stream-manager ${D}${INSTALL_ROOT}/bin/
install -m 0644 ${S}/lib/libstreaming.so.2.0 ${D}${INSTALL_ROOT}/lib/
ln -sf libstreaming.so.2.0 ${D}${INSTALL_ROOT}/lib/libstreaming.so.2

# Install configuration
install -m 0644 ${S}/etc/streaming.conf ${D}${INSTALL_ROOT}/etc/
install -m 0644 ${S}/etc/manifest.json ${D}${INSTALL_ROOT}/etc/
echo "loglevel=error" > ${D}${INSTALL_ROOT}/etc/loglevel.conf

# Memory declarations
echo "heap=8MB" > ${D}${INSTALL_ROOT}/memory/usage.conf
echo "stack=1MB" >> ${D}${INSTALL_ROOT}/memory/usage.conf
echo "static=2MB" >> ${D}${INSTALL_ROOT}/memory/usage.conf

# Dynamic linker configuration
echo "${INSTALL_ROOT}/lib" > ${D}${INSTALL_ROOT}/ld.so.conf.d/mw-streaming.conf
ln -sf ${INSTALL_ROOT}/ld.so.conf.d/mw-streaming.conf ${D}/etc/ld.so.conf.d/mw-streaming.conf

# AppArmor profile
install -m 0644 ${S}/apparmor/mw-streaming.profile ${D}${INSTALL_ROOT}/app_armor/
ln -sf ${INSTALL_ROOT}/app_armor/mw-streaming.profile ${D}/etc/apparmor.d/mw-streaming.profile

# Systemd service
install -m 0644 ${S}/systemd/mw-streaming.service ${D}${INSTALL_ROOT}/systemd/
ln -sf ${INSTALL_ROOT}/systemd/mw-streaming.service ${D}/etc/systemd/system/mw-streaming.service

# Log directory symlink
ln -sf /var/log/mw/streaming ${D}${INSTALL_ROOT}/logs

# Version file (using YYYY-MM-DD HH:MM:SS UTC format)
echo "version=3.1.0" > ${D}${INSTALL_ROOT}/VERSION
echo "build_date=$(TZ=UTC date '+%Y-%m-%d %H:%M:%S UTC')" >> ${D}${INSTALL_ROOT}/VERSION
echo "layer=mw" >> ${D}${INSTALL_ROOT}/VERSION
echo "dependencies=vendor-hdmi:2.5.0,vendor-audio:1.3.0" >> ${D}${INSTALL_ROOT}/VERSION
```

#### Example Systemd Service File

```ini
[Unit]
Description=RDK Streaming Middleware Service
After=vendor-layer.target vendor-hdmi.service vendor-audio.service
Requires=vendor-hdmi.service

[Service]
Type=notify
ExecStart=/mw/streaming/bin/stream-manager
Restart=on-failure
RestartSec=5s
WatchdogSec=30s

[Install]
WantedBy=multi-user.target
```

### Compliance Notes (Middleware Example)

* All artifacts are scoped to `/mw/streaming/`.
* Cross-layer dependencies are explicitly declared in `manifest.json`.
* The systemd service depends on vendor-layer services but does not hard-code specific vendor module paths.
* Independent OSS components (GStreamer, FFmpeg) are consumed from `/mw` mount points.
* Supports independent updates of the middleware layer without rebuilding vendor layer.

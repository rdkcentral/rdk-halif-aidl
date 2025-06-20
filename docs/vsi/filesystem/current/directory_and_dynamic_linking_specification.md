# Directory and Dynamic Linking Specification

## Document History

|Date|Author|Comments|
|----|------|--------|
|21 May 2025|G.Weatherup|Draft Revision|

## Related Pages

!!! tip Related Pages
    - [HALIF Logging System Design](halif_logging_system_design.md)

## Purpose

This document defines the file placement and dynamic linking policies. It ensures modularity, maintainability, and reliable integration of vendor and third-party components.

Applicable to all vendor-provided modules, libraries, executables, and configuration files delivered in the `/vendor` partition.

## Design Principles

* **Self-contained Modules**: Each vendor module resides within its own directory under `/vendor/<module>/`.
* **Mount Isolation**: `/vendor` is treated as an independent mount point, allowing separate updates and integrity checks.
* **No Global Path Pollution**: Avoids modifying system-level directories like `/etc` or `/lib`, unless explicitly structured.

## Directory Layout

Each vendor module should follow the directory convention:

```bash
/vendor/<module>/
├── bin/          # Executables specific to the module
├── lib/          # Shared/static libraries used by the module
├── etc/          # Configuration files for the module
├── data/         # Optional runtime or persistent module data
├── app_armor/    # Optional AppArmor profiles for the module
├── systemd/      # Optional systemd service files
├── memory/       # Static guide to resource usage declarations
├── logs/ -> /var/log/vendor/<module>/   # Writable logs symlink
├── ld.so.conf.d/ # Optional linker path configuration for symlink
├── VERSION       # Optional module version information
```

## Integration Requirements

* Executables must be invoked using absolute paths.
* Any module requiring dynamic libraries must either:
  * Embed RPATH during linking (`-Wl,-rpath,/vendor/<module>/lib`), or
  * Rely on linker cache updates (see Section 6).
* Environment variables (e.g., `LD_LIBRARY_PATH`) must not be relied upon at runtime.

## Dynamic Linking and `dlopen()` Support

**Requirement: Vendor module libraries must be made visible to the system linker via configuration files in `/etc/ld.so.conf.d/` to support standard dynamic linking and `dlopen()` usage.**

Each vendor module must provide a configuration file:

```bash
/vendor/<module>/ld.so.conf.d/vendor-<module>.conf
```

During image creation, a symbolic link must be created:

```bash
/etc/ld.so.conf.d/vendor-<module>.conf -> /vendor/<module>/ld.so.conf.d/vendor-<module>.conf
```

Example content:

```bash
/vendor/input/lib
```

**Post-Install Action:** The system must execute `ldconfig` after installation or image build to regenerate the dynamic linker cache.

## AppArmor Integration and Permissions

To maintain security boundaries and prevent privilege escalation, each vendor module integrated into the `/vendor/<module>/` structure must be governed by an AppArmor profile.

### AppArmor Profile Structure

Each module will include its AppArmor profile in:

```bash
/vendor/<module>/app_armor/
```

To activate the profile, a symbolic link will be created at install time:

```bash
/etc/apparmor.d/vendor-<module>.profile -> /vendor/<module>/app_armor/vendor-<module>.profile
```

### Enforcement Policy

* Profiles must be in enforced mode to provide real confinement.
* Profiles are activated via systemd unit or application launcher.
* Install scripts must create appropriate symlinks into `/etc/apparmor.d/`.
* System integrators must validate that all paths used by the module are declared.

## Update and Runtime Policy

* `/vendor` is treated as read-only at runtime.
* Writable runtime data for modules should be stored under `/var/vendor/<module>/`.
* Updates to modules must not affect global system directories outside of `/etc/ld.so.conf.d/` and `/etc/apparmor.d/` symlinks.
* AppArmor profiles should be validated against updated module paths post-deployment.

## Operational Considerations

### Filesystem Access Policy

* `/vendor` is **read-only** at runtime.
* `/vendor/<module>/log` is the designated **writable** path for runtime data, logs, and override configurations, this is a symbolic link from `/var/log/vendor/<module>/`
* Vendor modules must not write to `/etc`, `/usr`, or other immutable parts of the root filesystem.

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

* Each module may include its own `.service` file in `/vendor/<module>/systemd/`.
* Post-install, symlinks must be created in `/etc/systemd/system/`:

  ```bash
  /etc/systemd/system/vendor-<module>.service -> /vendor/<module>/systemd/vendor-<module>.service
  ```

* Services must declare dependencies using `After=`, `Requires=`, and optionally `WatchdogSec=` for health monitoring. **The vendor layer does not specify modules to be installed `After=` but milestone points to refer too.**

### Log Management

* Logs must be written to:

`/vendor/<module>/log/`

* This path must be a symbolic link to:

`/var/log/vendor/<module>/`

Logs will be written too `/vendor/<module>/log/`.

#### Log File Rotation Integration

Each module may provide a standard logrotate config file:

```c
/vendor/<module>/etc/logrotation.conf
```

This file can be symlinked to or copied too `/etc/logrotate.d/<module>` from `/vendor/<module>/etc/module_logrotate.conf` to integrate with the system logrotate process.

```c
/vendor/<module>/log/<module>.log { 
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

`/vendor/<module>/etc/loglevel.conf`

Format:

`loglevel=error`

The default log level must be set to error.

### Startup Configuration Application:

During system startup, the vendor platform layer is responsible for applying this syslog configuration settings for each of the modules.

This is platform-specific and may involve setting log levels in drivers, kernel modules, or components using platform-appropriate mechanisms.

The vendor layer team ensures this file is parsed and its value applied according to the SoC’s logging configuration method.

At runtime, a copy of the configuration is made to a writable location:

`/vendor/<module>/log/loglevel.conf`

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

### Version Declaration (Optional)

* Each module may include a file `/vendor/<module>/VERSION` with contents akin to:

  ```bash
  version=MAJOR.MINOR.PATCH
  build_date=YYYYMMDD
  build_sha=sha256:<value>
  ```

* Version should be Semantic Versioning (SemVer).

## Appendix: Example Integration with Alternate Install Root

This section provides a concrete example of how a vendor module can integrate with the `/vendor/sysint/${sysconfdir}` structure in compliance with the directory and dynamic linking policies described above.

## Appendix: Example Integration with Alternate Install Root

This section provides a concrete example of how a vendor module can integrate with the `/vendor/sysint/${sysconfdir}` structure in compliance with the directory and dynamic linking policies described above.

## Example: `sysinit` Vendor Module

### Overview

This module is installed under the path `/vendor/sysint`, with all configuration, systemd, logging, and dynamic linker artifacts scoped within this directory. Integration points such as AppArmor and ld.so.conf.d use symbolic links into `/etc/` to preserve system-wide access.

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
do_install() {
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
  sed -i '/MODEL_NUM/d' ${D}${INSTALL_ROOT}${sysconfdir}/device-vendor.properties
  sed -i '/FW_VERSION_TAG1/d' ${D}${INSTALL_ROOT}${sysconfdir}/device-vendor.properties
  sed -i '/FW_VERSION_TAG2/d' ${D}${INSTALL_ROOT}${sysconfdir}/device-vendor.properties
  sed -i '/MANUFACTURE/d' ${D}${INSTALL_ROOT}${sysconfdir}/device-vendor.properties
  sed -i '/FRIENDLY_ID/d' ${D}${INSTALL_ROOT}${sysconfdir}/device-vendor.properties
  sed -i '/USB_POWER_GPIO_NUMBER/d' ${D}${INSTALL_ROOT}${sysconfdir}/device-vendor.properties
  sed -i '/USB_A_POWER_GPIO_NUMBER/d' ${D}${INSTALL_ROOT}${sysconfdir}/device-vendor.properties
  sed -i '/MFG_NAME/d' ${D}${INSTALL_ROOT}${sysconfdir}/device-vendor.properties

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
}
```

### Compliance Notes

* All artifacts are scoped to the module directory under `/vendor/sysint`.
* Global system directories are only modified via symlinks into expected locations.
* This supports modular updates and ensures the system remains maintainable, verifiable, and secure.

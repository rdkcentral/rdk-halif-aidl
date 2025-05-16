# Directory and Dynamic Linking Specification

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
├── memory/       # Static resource usage declarations
├── logs/ -> /var/log/vendor/<module>/   # Writable logs symlink
├── ld.so.conf.d/ # Optional linker path configuration for symlink
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
* `/vendor/<module>/log` is the designated **writable** path for runtime data, logs, and override configurations, this is a symlogic link from `/var/log/vendor/<module>/`
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

* Services must declare dependencies using `After=`, `Requires=`, and optionally `WatchdogSec=` for health monitoring.

### Log Management

* A symbolic link must be created from:

  ```bash
  /vendor/<module>/log -> /var/log/vendor/<module>/
  ```

* All logs must be written to `/vendor/<module>/log/`.
* Each module may include a log rotation policy file at:

  ```bash
  /vendor/<module>/etc/logrotation.conf
  ```

* This file is not part of standard Linux logrotate. A platform-specific log manager must parse and enforce these rules.
* Example format:

  ````bash
  max_size=10MB
  max_files=5
  compress=true
  /vendor/<module>/etc/logrotation.conf
  ````

* This file is not part of standard Linux logrotate. A platform-specific log manager must parse and enforce these rules.
* Example format:

  ```bash
  max_size=10MB
  max_files=5
  compress=true
  ```

* The system must use this policy to govern log file rotation, retention, and compression.

### Logging Configuration

* Build time Logging level is configured via:

  ```bash
  /vendor/<module>/etc/loglevel.conf
  ```

* Format:

  ```bash
  loglevel=info
  ```

* This is copied at runtime into `/vendor/<module>/log/loglevel.conf`.

* Modules must read from this writable file at runtime to allow dynamic log level adjustment.

  ```bash
  /vendor/<module>/log/loglevel.conf
  ```

* Format:

  ```bash
  loglevel=info
  ```

### Version Declaration (Optional)

* Each module may include a file `/vendor/<module>/VERSION` with contents akin to:

  ```bash
  version=1.2.3
  build=20250101
  hash=sha256:<value>
  ```

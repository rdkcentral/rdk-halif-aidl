# HAL Versions Overview

The HAL interfaces provide the API contract between the RDK middleware and vendor layer containing the HAL implementation.

Both the RDK middleware and the Vendor Test Suite can sit above the HAL interfaces, which have been designed to use completely generic code with no platform/vendor specific code.

```mermaid
block-beta
  columns 3
  A("RDK Middleware / Vendor Test Suite"):3
  block:Vendor:2
    columns 1
    B("HAL Interfaces")
    D("HAL Implementation")
    E("Vendor Platform Drivers")
  end
  C("Kernel")

  style A fill:#0066cc,stroke:#000,color:#fff;
  style B fill:#d0d9c4,stroke:#000,color:#000;
  style C fill:#007000,stroke:#000,color:#fff;
  style D fill:#007000,stroke:#000,color:#fff;
  style E fill:#007000,stroke:#000,color:#fff;
```

**TBC: Static Image**

![Vendor Layer](./Vendor%20Layer.drawio.svg)

## Semantic Versioning

Each HAL release follows **Semantic Versioning (SemVer)** principles and is versioned using the `major.minor.bugfix/doc` format, which applies to HAL services and components.

The version should increment as follows:

- **Major:** Increased when making incompatible API changes.
- **Minor:** Increased when adding functionality in a backwards-compatible manner.
- **Bugfix/Doc:** Increased when making backwards-compatible bug fixes or documentation updates. Since the documentation defines semantic operation, it is as important as an interface header definition change but remains backward compatible.

For more details, refer to [SemVer](https://www.semver.org).

## HAL Service Interfaces

Most of the HAL interfaces are implemented as services across a client-server architecture which uses process separation and provides backwards compatibility with older versions of the API.

The interface definitions are provided in AIDL files, which generate C++ sources for both the client and server processes. HAL API calls are made across Binder.

## In-Process HALs

A small number of HALs exist as libraries which are dynamically linked to RDK middleware processes.

- Graphics: EGL, OpenGL ES, Vulkan graphics drivers
- Wi-Fi: wpa\_supplicant
- Bluetooth: BlueZ
- CDM: Content Decryption Modules for DRM

## Device Profiles

The HAL supports device profiles for TV and STB which mandates which of the HAL services should be supported in the vendor layer.

At runtime the RDK middleware can access the DeviceInfo HAL service to get the device profile for the HAL.


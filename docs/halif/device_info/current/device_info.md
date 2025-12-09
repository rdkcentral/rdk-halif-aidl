# DeviceInfo HAL

## Overview

The `DeviceInfo` HAL provides platform-independent access to key persistent identity and configuration properties of the device, such as manufacturer, model name, serial number, MAC addresses, and image metadata. It abstracts device-specific storage mechanisms (e.g., NVM, EEPROM, secure flash) and exposes a read/write interface to the middleware or management layers.

The HAL is primarily used for boot-time introspection, provisioning, and diagnostic queries. Write access is typically restricted to factory or trusted services. All values are exposed as strings, with strict formatting requirements (e.g., MAC addresses must be upper case and colon-separated).

---

!!! info "References"
    |                              |                                                                                                  |
    | ---------------------------- | ------------------------------------------------------------------------------------------------ |
    | **Interface Definition**     | [com/rdk/hal/deviceinfo](../../../../deviceinfo/current/) |
    | **API Documentation**        | TBD                                                                                              |
    | **HAL Interface Type**       | [AIDL and Binder](../../../introduction/aidl_and_binder.md)                                      |
    | **Initialization Unit**      | [systemd service](../../../vsi/systemd/current/systemd.md)                                       |
    | **VTS Tests**                | TBD                                                                                              |
    | **Reference Implementation** | TBD                                                                                              |

---

!!! tip "Related Pages"
    * [HAL Feature Profile](../../key_concepts/hal/hal_feature_profiles.md)
    * [HAL Interface Overview](../../key_concepts/hal/hal_interfaces.md)
    * [Other HALs or Framework Components](../../key_concepts/hal/hal_interfaces.md)

---

## Functional Overview

This HAL provides an interface for reading the persistent device properties. It is typically used by:

* Boot-time services for provisioning and validation
* Middleware for branding, platform, or locale setup
* Debugging and diagnostic interfaces
* Factory provisioning tools

All property accesses are string-based, and property keys are pre-defined by the specific platform configuration. The HAL internally validates, normalises, and may persist values across reboots. The data is read-only and if required would expected to be cached and overriden if required by the upper layers.

---

## Implementation Requirements

| #                | Requirement                                                              | Comments                           |
| ---------------- | ------------------------------------------------------------------------ | ---------------------------------- |
| **HAL.DeviceInfo.1** | The service shall expose a binder interface named `"DeviceInfo"`         | Defined via `serviceName` constant |
| **HAL.DeviceInfo.2** | The service shall support the properties listed in `supportedProperties` | Validated via `getCapabilities()`  |
| **HAL.DeviceInfo.3** | All MAC addresses must follow `XX:XX:XX:XX:XX:XX` format and are not zero-terminated | Enforced in getProperty           |
| **HAL.DeviceInfo.4** | All hex strings must be uppercase                                        | Applies to OUI and similar fields  |
| **HAL.DeviceInfo.5** | All properties are read-only and returned as strings, but may not be zero termined | Data is Read-Only                  |
| **HAL.DeviceInfo.6** | Each property defines its format, max size, and zero-termination status  | See HAL Feature Profile and YAML   |
| **HAL.DeviceInfo.7** | ISO3166 and ISO639 codes are 2 bytes and not zero-terminated            | Enforced in getProperty            |
| **HAL.DeviceInfo.8** | The HAL shall enforce max size and zero-termination as specified         | Validation in implementation       |
| **HAL.DeviceInfo.9** | Property types are defined in the HAL as `PropertyType` enum             | See PropertyType.aidl              |

---

## Interface Definitions

| AIDL File                | Description                                         |
| ------------------------ | --------------------------------------------------- |
| `IDeviceInfo.aidl`       | Main control interface for property access          |
| `Capabilities.aidl`      | Lists supported property keys                       |
| `HALVersion.aidl`        | Encodes interface version (major.minor.doc)         |
| `SetPropertyResult.aidl` | Return codes for `setProperty()`                    |
| `Property.aidl`          | Parcelable for device information property metadata |
| `PropertyType.aidl`      | Enum of supported property types                    |

---

## Initialization

The HAL service is registered at system boot via a systemd unit. It must register with the AIDL Service Manager under the name `"DeviceInfo"`. Initialization may involve reading from NVM, flash, or platform-specific storage.

---

## Product Customization

* Property support is declared via `Capabilities.supportedProperties`
* Platform-specific fields (e.g., Wi-Fi MAC, WPS PIN) are optional
* Additional vendor fields may be added via OEM-specific keys or future extensions of `Property.aidl`
* Default values and access modes are described in the HAL Feature Profile

---

## System Context

```mermaid
flowchart TD
  Client -->|getProperty/setProperty| DeviceInfoHAL
  DeviceInfoHAL -->|backed by| NVM[Flash/NVM]

  FactoryTools -->|setProperty| DeviceInfoHAL

  classDef background fill:#121212,stroke:none,color:#E0E0E0;
  classDef blue fill:#1565C0,stroke:#E0E0E0,stroke-width:2px,color:#E0E0E0;
  classDef lightGrey fill:#616161,stroke:#E0E0E0,stroke-width:2px,color:#FFFFFF;
  classDef wheat fill:#FFB74D,stroke:#424242,stroke-width:2px,color:#000000;
  classDef green fill:#4CAF50,stroke:#E0E0E0,stroke-width:2px,color:#FFFFFF;
  classDef default fill:#1E1E1E,stroke:#E0E0E0,stroke-width:1px,color:#E0E0E0;

  Client:::blue
  FactoryTools:::blue
  DeviceInfoHAL:::wheat
  NVM:::green
```

---

## Resource Management

No resource handles are needed. The HAL is stateless between calls. There is no `open()` or `close()` lifecycle. Errors are returned directly through `SetPropertyResult` or `null` (for reads).

---

## Operation and Data Flow

* `getProperty(Property)` returns a string or `null`
* `setProperty(Property, String)` returns a `SetPropertyResult`
* `getCapabilities()` returns the full list of supported properties
* `getHALVersion()` reports the major.minor.doc version of the interface

---

## Modes of Operation

No distinct modes are defined. Implementations may choose to restrict write access depending on build variants (e.g., factory vs. production).

---

## Event Handling

This HAL is synchronous and does not emit events or use listeners.

---

## State Machine / Lifecycle

This HAL does not manage internal state or resource handles. Each method call is independent and stateless. The interface is always available after service registration, and there is no explicit lifecycle 

---

## Data Format / Protocol Support


The supported data formats correspond to the property types defined in `PropertyType.aidl`:

| PropertyType      | Format/Example         | Use Case                | Support Level |
|-------------------|-----------------------|-------------------------|--------------|
| STRING            | "RDK Inc."            | Generic string values   | Mandatory    |
| MAC               | "00:11:22:33:44:55"   | MAC address format      | Mandatory    |
| NUMERIC           | "12345670"            | WPS PIN, numeric fields | Mandatory    |
| ISO3166           | "US"                  | Country code            | Mandatory    |
| ISO639            | "en"                  | Language code           | Mandatory    |
| UPPERCASEHEX      | "A1B2C3D4"            | Hexadecimal string      | Mandatory    |
| SEMANTICVERSION   | "1.0.0"               | HAL version             | Mandatory    |

See `PropertyType.aidl` for the authoritative list of supported property types and their definitions.

## Platform Capabilities

Example Configuration (YAML style)

```yaml
IDeviceInfo:
  properties:
    - HAL_VERSION:
        value: "1.0.0"
        format: SemanticVersion
        max_size: 32
        zero_terminated: true
    - MANUFACTURER:
        value: "RDK Inc."
        format: String
        max_size: 32
        zero_terminated: true
    - MANUFACTURER_OUI:
        value: "AA:BB:CC"
        format: MAC_OUI
        max_size: 8
        zero_terminated: true
    - MODELNAME:
        value: "RDK-STB-200"
        format: String
        max_size: 32
        zero_terminated: true
    - PRODUCTCLASS:
        value: "STB"
        format: String
        max_size: 16
        zero_terminated: true
    - SERIALNUMBER:
        value: "RDK123456789"
        format: String
        max_size: 32
        zero_terminated: true
    - WIFIMAC:
        value: "00:11:22:33:44:55"
        format: MAC
        max_size: 16
        zero_terminated: false
    - BLUETOOTHMAC:
        value: "11:22:33:44:55:66"
        format: MAC
        max_size: 16
        zero_terminated: false
    - WPSPIN:
        value: "12345670"
        format: Numeric
        max_size: 8
        zero_terminated: true
    - ETHERNETMAC:
        value: "AA:BB:CC:DD:EE:FF"
        format: MAC
        max_size: 16
        zero_terminated: false
    - RF4CEMAC:
        value: "22:33:44:55:66:77"
        format: MAC
        max_size: 16
        zero_terminated: false
    - IMAGENAME:
        value: "rdk-main"
        format: String
        max_size: 32
        zero_terminated: true
    - IMAGETYPE:
        value: "release"
        format: String
        max_size: 16
        zero_terminated: true
    - COUNTRYCODE:
        value: "US"
        format: ISO3166
        max_size: 2
        zero_terminated: false
    - LANGUAGECODE:
        value: "en"
        format: ISO639
        max_size: 2
        zero_terminated: false
    - MANUFACTURERDATA:
        value: "OEM_TAG_1234"
        format: String
        max_size: 64
        zero_terminated: true
```

This example matches the current HAL Feature Profile YAML structure, showing all required fields for each property.

---

## End-of-Stream and Error Handling

* `getProperty()` returns `null` for unsupported keys
* `setProperty()` returns granular errors (e.g., `ERROR_WRITE_FLASH_FAILED`)
* CRC and flash verification errors are explicitly reported

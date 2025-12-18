# HAL Indicator

## Overview

The **Indicator** interface abstracts control of persistent device indicator states—typically backed by hardware elements such as LEDs or front-panel displays. It allows higher-level components, such as middleware and system services, to reflect the system's current status to the user using a set of standardised states.

The abstraction hides all platform-specific details. Each vendor is responsible for implementing these states in a manner consistent with their product design. The HAL implementation must reflect each state via hardware-controlled visual indicators (e.g., colours, blink patterns, panel brightness), but **upper layers remain unaware of any physical wiring, LED models, or mapping logic.**

This decoupling ensures consistency across devices while allowing flexibility for OEM-specific behaviour.

The interface supports:

* A **manager-based multi-instance architecture** for flexible indicator control
* Discovery of available indicator instances via `IIndicatorManager.getIndicatorIds()`
* **String-based state representation** for extensibility and platform flexibility
* A **single active state** per indicator at any time, managed via `set(String)` and read via `get()`
* Discovery of supported states via `getCapabilities()`, aligned with the HFP file
* **No support for transient triggers** like momentary LED flashes; these are handled independently

For RDK reference implementations, the indicator is designed to reflect the global state of the device, with a single indicator instance provided. However, the interface architecture supports multi-instance configurations for third-party vendors who may require independent indicator control (e.g., per-zone indicators).

---

## References

!!! info References
      |                     |                                                                                                          |
      | ---------------------------- | ----------------------------------------------------------------------------------------------------------------- |
      | **Interface Definition**     | [indicator/current](https://github.com/rdkcentral/rdk-halif-aidl/tree/main/indicator/current)                     |
      | **API Documentation**        | TBD                                                                                                               |
      | **HAL Interface Type**       | [AIDL and Binder](../../../introduction/aidl_and_binder.md)                                                       |
      | **Initialization Unit**      | [systemd service](../../../vsi/systemd/current/systemd.md)                                                        |
      | **VTS Tests**                | TBD                                                                                                               |
      | **Reference Implementation** | TBD                                                                                                               |
      | **HAL Feature Profile**      | [hfp-indicator.yaml](https://github.com/rdkcentral/rdk-halif-aidl/tree/main/indicator/current/hfp-indicator.yaml) |

## Related Pages

!!! tip "Related Pages"
      - [HAL Feature Profile](../../key_concepts/hal/hal_feature_profiles.md)
      - [HAL Interface Overview](../../key_concepts/hal/hal_interfaces.md)
      - [Other HALs or Framework Components](link)

---

## Functional Overview

The Indicator HAL defines a discrete and flexible set of **persistent system states** represented as strings. Each state represents an observable operational condition (e.g., `"ACTIVE"`, `"WPS_CONNECTING"`, `"SOFTWARE_DOWNLOAD_ERROR"`). These are:

* **Long-lived**: The state persists until explicitly changed
* **Mutually exclusive**: Only one state can be active at a time per indicator instance
* **User-visible**: Each state should correspond to a user-facing behaviour (e.g., LED colour/pattern)
* **Extensible**: Platforms can define custom states beyond the standard set

The interface follows a manager-based architecture:

1. `IIndicatorManager` provides platform-wide discovery and capabilities
2. `IIndicatorManager.getIndicatorIds()` retrieves available indicator instances
3. `IIndicatorManager.getIndicator(id)` obtains an `IIndicator` instance interface
4. `IIndicator.getCapabilities()` retrieves supported states for that specific instance
5. `IIndicator.set(String)` sets a new persistent indicator state
6. `IIndicator.get()` retrieves the currently active state string

Standard state strings include:
* General: `"BOOT"`, `"ACTIVE"`, `"STANDBY"`, `"OFF"`, `"DEEP_SLEEP"`
* WPS: `"WPS_CONNECTING"`, `"WPS_CONNECTED"`, `"WPS_ERROR"`, `"WPS_SES_OVERLAP"`
* Network: `"WIFI_ERROR"`, `"IP_ACQUIRED"`, `"NO_IP"`
* System: `"FULL_SYSTEM_RESET"`, `"USB_UPGRADE"`, `"SOFTWARE_DOWNLOAD_ERROR"`, `"PSU_FAILURE"`

The interface is expected to set the "BOOT" state on boot until changed by the set() function.
It is up to the implementation to set the first state. In the case of RDK Comcast method, it's a "BOOT" state.

---

## Implementation Requirements

| #               | Requirement                                                       | Comments                                   |
| --------------- | ----------------------------------------------------------------- | ------------------------------------------ |
| **HAL.INDICATOR.1** | The manager shall expose available indicator instances via `getIndicatorIds()` | RDK reference provides single global instance |
| **HAL.INDICATOR.2** | Each indicator instance shall expose a single active state using `set(String)` | Only one state is active at a time per instance |
| **HAL.INDICATOR.3** | Each indicator instance shall return the current state via `get()` | Must reflect latest successfully set value |
| **HAL.INDICATOR.4** | The platform shall advertise supported states via `Capabilities` | Validated against `hfp-indicator.yaml` |
| **HAL.INDICATOR.5** | States not listed in `Capabilities` shall not be settable | Invalid `set()` calls must fail gracefully |
| **HAL.INDICATOR.6** | The interface shall support multi-instance capability | Architecture allows multiple independent indicators |
| **HAL.INDICATOR.7** | `"BOOT"` is the expected initial state on system boot | Set by implementation until changed by client |

---

## Interface Definitions

| AIDL File               | Description                                              |
| ----------------------- | -------------------------------------------------------- |
| `IIndicatorManager.aidl` | Manager interface for discovery and multi-instance support |
| `IIndicator.aidl`        | Instance interface for querying and setting state        |
| `Capabilities.aidl`      | Parcelable describing supported states (as strings)      |

**Note**: The State.aidl enum has been removed in favour of string-based state representation for improved flexibility and extensibility.

---

## Platform Capabilities

The platform-specific file `hfp-indicator.yaml` defines the supported states and multi-instance configuration for each device. This must be kept in sync with the runtime implementation and used for:

* Runtime validation (`getCapabilities()`)
* Automated testing (VTS test case selection)
* Middleware introspection

### Multi-Instance Support

The interface supports multi-instance configurations through the `IIndicatorManager` interface. The HFP file declares:

* `multiInstance`: Boolean flag indicating multi-instance capability
* `instances`: Array of indicator instance definitions with ID, name, and description

For RDK reference implementations, a single global indicator instance (ID: 0) is provided that reflects the overall device state. Third-party vendors may define additional instances as needed for their platform architecture.

### State String Definitions

States are now represented as strings rather than enum values, providing greater flexibility for platform-specific extensions. The standard state strings correspond to the previous enum value names:

| Category      | State Strings                                                   |
| ------------- | --------------------------------------------------------------- |
| General       | `"BOOT"`, `"ACTIVE"`, `"STANDBY"`, `"OFF"`, `"DEEP_SLEEP"`     |
| WPS           | `"WPS_CONNECTING"`, `"WPS_CONNECTED"`, `"WPS_ERROR"`, `"WPS_SES_OVERLAP"` |
| Network       | `"WIFI_ERROR"`, `"IP_ACQUIRED"`, `"NO_IP"`                     |
| System Events | `"FULL_SYSTEM_RESET"`, `"USB_UPGRADE"`, `"SOFTWARE_DOWNLOAD_ERROR"`, `"PSU_FAILURE"` |

Platforms may define additional custom state strings as needed, which must be documented in the HFP file.

---

### Supported State Subset (Example)

```yaml
Indicator:
  interfaceVersion: current
  multiInstance: true
  instances:
    - id: 0
      name: "global"
      description: "Global device state indicator"
  supportedStates:
    - "BOOT"
    - "ACTIVE"
    - "STANDBY"
    - "OFF"
    - "WPS_CONNECTING"
    - "WPS_CONNECTED"
    - "WPS_ERROR"
    - "WIFI_ERROR"
    - "IP_ACQUIRED"
    - "FULL_SYSTEM_RESET"
    - "PSU_FAILURE"
```

---

### Platform-Specific Extensions

Platforms may define new persistent states as custom strings beyond the standard set. These must:

* Follow the same semantics (persistent, exclusive, not transient)
* Be defined in the HFP YAML under `supportedStates`
* Be documented for test coverage and integration
* Use clear, descriptive naming conventions

For example, a vendor might add:
* `"VOICE_MODE_ACTIVE"` for voice assistant functionality
* `"SETUP_MODE"` for device configuration state
* `"CUSTOM_BRANDING_STATE"` for special marketing modes

---

## Error Handling

| Condition                      | Expected Behaviour                          |
| ------------------------------ | ------------------------------------------- |
| Invalid `set(String)` call     | Must fail cleanly and leave state unchanged |
| Unsupported state string       | Rejected if not listed in `Capabilities`    |
| `get()` before any `set()`     | Returns initial state (typically `"BOOT"`)  |
| Invalid indicator ID           | `getIndicator()` returns null               |



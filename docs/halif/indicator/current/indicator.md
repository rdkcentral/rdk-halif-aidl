# HAL Indicator

## Overview

The **Indicator** interface abstracts control of persistent device indicator states—typically backed by hardware elements such as LEDs or front-panel displays. It allows higher-level components, such as middleware and system services, to reflect the system's current status to the user using a set of standardised states.

The abstraction hides all platform-specific details. Each vendor is responsible for implementing these states in a manner consistent with their product design. The HAL implementation must reflect each state via hardware-controlled visual indicators (e.g., colours, blink patterns, panel brightness), but **upper layers remain unaware of any physical wiring, LED models, or mapping logic.**

This decoupling ensures consistency across devices while allowing flexibility for OEM-specific behaviour.

The interface supports:

* A **single active state** at any time, managed via `set(State)` and read via `get()`
* Discovery of supported states via `getCapabilities()`, aligned with the HFP file
* **No support for transient triggers** like momentary LED flashes; these are handled independently

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

The Indicator HAL defines a discrete and finite set of **persistent system states**, each representing an observable operational condition (e.g., `ACTIVE`, `WPS_CONNECTING`, `SOFTWARE_DOWNLOAD_ERROR`). These are:

* **Long-lived**: The state persists until explicitly changed
* **Mutually exclusive**: Only one state can be active at a time
* **User-visible**: Each state should correspond to a user-facing behaviour (e.g., LED colour/pattern)

Clients interact using the following flow:

1. `getCapabilities()` to retrieve the list of supported states
2. `set(State)` to enter a new persistent indicator state
3. `get()` to retrieve the currently active state

---

## Implementation Requirements

| #               | Requirement                                                       | Comments                                   |
| --------------- | ----------------------------------------------------------------- | ------------------------------------------ |
| **HAL.INDICATOR.1** | The service shall expose a single active state using `set(State)` | Only one state is active at a time         |
| **HAL.INDICATOR.2** | The service shall return the current state via `get()`            | Must reflect latest successfully set value |
| **HAL.INDICATOR.3** | The platform shall advertise supported states via `Capabilities`  | Validated against `hfp-indicator.yaml`     |
| **HAL.INDICATOR.4** | States not listed in `Capabilities` shall not be settable         | Invalid `set()` calls must fail gracefully |
| **HAL.INDICATOR.5** | `ERROR_UNKNOWN` and `BOOT` must be read-only states               | `BOOT` is platform-initialised only        |

---

## Interface Definitions

| AIDL File           | Description                                      |
| ------------------- | ------------------------------------------------ |
| `IIndicator.aidl`   | Primary interface for querying and setting state |
| `Capabilities.aidl` | Parcelable describing supported states           |
| `State.aidl`        | Enum of valid indicator states                   |

---

## Platform Capabilities

The platform-specific file `hfp-indicator.yaml` defines the subset of states supported by each device. This must be kept in sync with the runtime implementation and used for:

* Runtime validation (`getCapabilities()`)
* Automated testing (VTS test case selection)
* Middleware introspection

### Enum Value Groupings

The `State` enum uses **explicit, grouped integer values** to simplify vendor extension and downstream parsing. For example:

| Group         | Value Range | Examples                      |
| ------------- | ----------- | ----------------------------- |
| General       | 0–99        | `BOOT`, `ACTIVE`, `OFF`       |
| WPS           | 100–199     | `WPS_CONNECTING`, `WPS_ERROR` |
| Network       | 200–299     | `IP_ACQUIRED`, `NO_IP`        |
| System Events | 300–399     | `USB_UPGRADE`, `PSU_FAILURE`  |
| Vendor        | 1000+       | `USER_DEFINED_*`              |

These ranges are not enforced by the interface but are recommended for clarity and HFP alignment.

---

### Supported State Subset (Example)

```yaml
supportedStates:
  - BOOT
  - ACTIVE
  - STANDBY
  - OFF
  - WPS_CONNECTING
  - WPS_CONNECTED
  - WPS_ERROR
  - WIFI_ERROR
  - IP_ACQUIRED
  - FULL_SYSTEM_RESET
  - PSU_FAILURE
```

---

### Platform-Specific Extensions

Platforms may define new persistent states beginning at `USER_DEFINED_BASE = 1000`. These must:

* Follow the same semantics (persistent, exclusive, not transient)
* Be defined in the HFP YAML under `supportedStates`
* Be documented for test coverage and integration

---

## Error Handling

| Condition                  | Expected Behaviour                          |
| -------------------------- | ------------------------------------------- |
| Invalid `set(State)` call  | Must fail cleanly and leave state unchanged |
| `set()` on read-only state | Rejected (`BOOT`, `ERROR_UNKNOWN`)          |
| Unsupported enum value     | Rejected if not listed in `Capabilities`    |
| `get()` before any `set()` | Returns `ERROR_UNKNOWN`                     |


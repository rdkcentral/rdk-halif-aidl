# HAL Interface Name

## Overview

Describe the role of this HAL service. Outline its responsibilities, how it abstracts platform-specific functionality, and its interaction with higher-level RDK components. Mention any excluded modes or operations.

---

## References

!!! info "References"

    | | |
    |-|-|
    |**Interface Definition**|[path-to-aidl-version](link)|
    |**API Documentation**| TBD |
    |**HAL Interface Type**| [AIDL and Binder](../introduction/aidl_and_binder.md) |
    |**Initialization Unit**| [systemd service](../vsi/systemd/current/systemd.md) |
    |**VTS Tests**| TBD |
    |**Reference Implementation**| TBD |

---

## Related Pages

!!! tip "Related Pages"

    - [HAL Feature Profile](../key_concepts/hal/hal_feature_profiles.md)
    - [HAL Interface Overview](../key_concepts/hal/hal_interfaces.md)
    - [Other HALs or Framework Components](link)

---

## Functional Overview

Explain the main responsibilities of this interface, such as managing resources, processing buffers, handling events, or controlling hardware. Clarify its positioning in the system architecture.

---

## Implementation Requirements

| #                 | Requirement          | Comments           |
| ----------------- | -------------------- | ------------------ |
| HAL.<INTERFACE>.1 | The service shall... | Notes or rationale |

---

## Interface Definitions

| AIDL File                | Description                                              |
| ------------------------ | -------------------------------------------------------- |
| I<Interface>.aidl        | Main resource control interface                          |
| I<Interface>Manager.aidl | Interface for service discovery and resource enumeration |
| Capabilities.aidl        | Parcelable describing feature set                        |
| ErrorCode.aidl           | Enum of failure conditions                               |

---

## Initialization

Describe startup behaviour, service registration, dependencies, and order of operation (e.g., Service Manager registration).

---

## Product Customization

Explain:

* How resources are uniquely identified and enumerated
* What `Capabilities` or properties clients can query
* If the platform can offer multiple simultaneous instances

---

## System Context

Include a Mermaid flowchart or textual description showing:

* Client-side interface use
* Resource control paths
* Event listener connections
* Any shared data buffer interaction

---

## Resource Management

Detail the lifecycle:

* How clients `open()` or `acquire()` resource handles
* Restrictions (e.g., single controller vs. multiple listeners)
* Cleanup behavior when a client exits

---

## Threading Model

State:

* Which calls block and which return before the work completes
* The thread on which listener callbacks are delivered, and whether a client may call back into the service from a callback
* Which calls may be made concurrently from more than one client thread, and which must be serialised
* Binder thread pool sizing the service needs, if it differs from the default

---

## Memory Model

State:

* Who allocates and who frees each buffer that crosses the interface, and when ownership transfers
* How large data is carried (shared memory, file descriptors or parcelled copies) and the lifetime of each handle
* Limits on buffer count and size, with units
* What happens to in-flight buffers when a client exits or the service restarts

---

## Operation and Data Flow

General description of:

* How input/output flows through the HAL
* Handling of any buffer queues, frame handles, or metadata
* Conditions for back pressure or resource stalls

---

## Modes of Operation

Describe configurable or runtime modes and how they affect client interaction or output.

---

## Event Handling

Document:

* Events emitted (e.g., `onStateChanged`, `onError`, `onResourceAvailable`)
* Listener types
* Timing guarantees or event ordering rules

---

## State Machine / Lifecycle

Describe the typical session flow:

* States like `CLOSED`, `READY`, `STARTED`, `FLUSHING`
* Sequence diagrams or state transition tables
* Expected order of calls and callbacks

---

## Data Format / Protocol Support (if applicable)

| Format  | Use Case         | Support Level |
| ------- | ---------------- | ------------- |
| FormatX | Application data | Optional      |

---

## Platform Capabilities

Outline expected feature support—parameter ranges, configuration values, or mode toggles exposed through `PlatformCapabilities`.

---

## End-of-Stream and Error Handling

Explain how the interface handles:

* Completion signals
* Error propagation and recovery
* Discontinuities or out-of-band resets

---

## Open Issues / TODOs

Track:

* Unspecified behaviour
* Items pending AIDL changes or implementation
* Gaps in validation/test coverage

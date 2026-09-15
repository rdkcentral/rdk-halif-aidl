# Broadcast

## References

!!! info References
    |||
    |-|-|
    |**Interface Definition**|[AIDL source](https://github.com/rdkcentral/rdk-halif-aidl/tree/main/broadcast/current)|
    |**Interface Version**|`current`|
    |**API Documentation**| *TBD* |
    |**HAL Interface Type**|[AIDL and Binder](../introduction/aidl_and_binder.md)|
    |**VTS Tests**| TBC |
    |**Reference Implementation - vComponent**|**TBD**|

## Related Pages

!!! tip "Related Pages"
    - [Ring Buffer](../ringbuffer/ringbuffer.md)
    - [AV Buffer](../avbuffer/av_buffer.md)
    - [HAL Feature Profiles](../key_concepts/hal/hal_feature_profiles.md)

## Overview

The Broadcast HAL exposes the platform's broadcast reception resources without exposing platform-specific pipeline
details or driver handles. `IBroadcastManager` is the discovery root. It provides access to persistent frontend,
demultiplexer, and Conditional Access (CA) slot resources. Clients compose a reception pipeline by obtaining temporary
control objects from those resources and passing Binder interfaces between them.

The API separates discovery, exclusive control of finite resources, source-to-demultiplexer connection, and transport
of high-volume stream data through the Ring Buffer HAL. Possessing an interface for a physical resource does not
necessarily grant control of that resource, and controlling one stage does not implicitly reserve the other pipeline
stages.

## Implementation Requirements

Requirements a conforming service implementation must satisfy. Each is intended to be independently verifiable; the
Comments column names the interface element or capability field against which it is checked.

TODO: Validate that all requirements are independently verifiable and that the Comments column accurately references the relevant interface elements or capability fields.

### Discovery and Service Identity

| # | Requirement | Comments |
|---|-------------|----------|
| **HAL.BROADCAST.1** | The service shall publish a Binder interface under the name given by `IBroadcastManager.serviceName`. | `"BroadcastManager"`. |
| **HAL.BROADCAST.2** | Resource IDs returned by `getFrontendIds()`, `getDemuxIds()` and `getCaSlotIds()` shall remain stable for the lifetime of the service instance. | IDs are opaque; clients must not infer meaning from their values. |
| **HAL.BROADCAST.3** | `getFrontend()`, `getDemux()` and `getCaSlot()` shall throw `EX_ILLEGAL_ARGUMENT` for an ID not returned by the corresponding list method. | |
| **HAL.BROADCAST.4** | `getImplementationVersion()` shall return a semantic implementation version and a stable implementation name, independent of the AIDL interface version. | `ImplementationVersion.aidl`. |

### Exclusive Access and Client Lifetime

| # | Requirement | Comments |
|---|-------------|----------|
| **HAL.BROADCAST.5** | Each exclusive resource shall be granted to at most one client at a time. | Frontend controller, LNB controller, demultiplexer controller, data provider, software input. |
| **HAL.BROADCAST.6** | An acquiring call shall reject a null token, or a token that is not a remote Binder hosted by the caller, with `EX_ILLEGAL_ARGUMENT`. | A locally hosted token would bind the claim to the wrong process lifetime. |
| **HAL.BROADCAST.7** | An acquiring call shall return `null` when the resource is already claimed, and shall not throw for that condition. | See *Failure Signalling*. |
| **HAL.BROADCAST.8** | The service shall release every claim made with a client token when the process hosting that token terminates, by any means. | Verified by killing a client holding a claim. |
| **HAL.BROADCAST.9** | Release on client death shall cascade downstream to upstream, so that one client's death frees the entire pipeline it held. | Filters before demultiplexer; provider before frontend. |
| **HAL.BROADCAST.10** | Teardown shall be idempotent: an explicit release racing a death notification shall release hardware once. | |
| **HAL.BROADCAST.11** | After release, the resource shall be immediately reacquirable and `isOpen()`/`isConnected()` shall report it free. | No lingering reservation. |
| **HAL.BROADCAST.12** | A release or close method shall throw `EX_ILLEGAL_ARGUMENT` when passed an object that did not originate from the same resource instance. | Provenance checking on `close()`, `closeLnb()`, `disconnect()`, `closeFilter()`, `releaseDataProvider()`, `releaseSoftwareInput()`. |

### Frontend and Tuning

| # | Requirement | Comments |
|---|-------------|----------|
| **HAL.BROADCAST.13** | `getFrontendTypes()` shall report every carrier type the frontend can tune. | `FrontendType.aidl`. |
| **HAL.BROADCAST.14** | `getCapabilities()` shall throw `EX_ILLEGAL_ARGUMENT` for a type not reported by `getFrontendTypes()`. | |
| **HAL.BROADCAST.15** | The active member of the returned `FrontendCapabilities.specifics` shall match the requested `FrontendType`. | ATSC→`atsc`, DVB_C→`dvbC`, DVB_S→`dvbS`, DVB_T→`dvbT`. |
| **HAL.BROADCAST.16** | `tune()` shall return once the request is accepted, not on signal lock, and shall place the frontend in `TUNING`. | Asynchronous by contract. |
| **HAL.BROADCAST.17** | `tune()` shall accept a new request while `TUNING` or `LOCKED`, abandoning the previous one, without requiring `stopTune()` first. | |
| **HAL.BROADCAST.18** | `tune()` shall throw `EX_UNSUPPORTED_OPERATION` when the active `TuneParameters` member names a carrier type the frontend does not support. | |
| **HAL.BROADCAST.19** | A frontend reporting `DvbTStandard.T2` shall honour `DvbTTuneParameters.plpId`, including `FrontendConstants.AUTO_PLP_ID`. | PLP selection is mandatory for DVB-T2; no capability flag exists. |
| **HAL.BROADCAST.20** | A tune parameter outside the range advertised by the corresponding capability field shall be rejected with `EX_ILLEGAL_ARGUMENT`, leaving the frontend state unchanged. | Frequency, symbol rate, and enumerated values. |
| **HAL.BROADCAST.21** | An `AUTO` enumeration value shall be advertised in a capability list only where the frontend performs genuine auto-detection. | Trying one value and failing does not qualify. |
| **HAL.BROADCAST.22** | `getSignalInfo()` shall return one entry per requested property, in the requested order, each carrying a `Readiness` value. | Unsupported properties report `UNSUPPORTED` rather than throwing. |
| **HAL.BROADCAST.23** | `getTuneStatus()` and `getSignalInfo()` shall be callable at any time without altering tuning state. | Polling is the only observation mechanism. |

### LNB Control

| # | Requirement | Comments |
|---|-------------|----------|
| **HAL.BROADCAST.24** | `openLnb()` shall throw `EX_UNSUPPORTED_OPERATION` on a frontend without LNB control. | |
| **HAL.BROADCAST.25** | `sendDiseqc()` shall block until the command has been transmitted. | EUTELSAT Bus Functional Specification 4.2. |
| **HAL.BROADCAST.26** | `sendDiseqc()` shall reject an empty or malformed command, and may reject one longer than 6 bytes, with `EX_ILLEGAL_ARGUMENT`. | Implementations must validate rather than forward untrusted input to hardware. |

### Demultiplexer and Filters

| # | Requirement | Comments |
|---|-------------|----------|
| **HAL.BROADCAST.27** | A demultiplexer shall be connected to at most one data provider, and a provider to at most one demultiplexer. | |
| **HAL.BROADCAST.28** | `disconnect()` shall return the same provider instance that was passed to `connect()`. | Enables release at the originating source. |
| **HAL.BROADCAST.29** | The active member of the returned `Filter` shall correspond to the active member of the supplied `FilterParameters`. | |
| **HAL.BROADCAST.30** | Filter allocation shall respect `DemuxCapabilities.supportedFilters[].maxInstances`, returning `null` once exhausted. | |
| **HAL.BROADCAST.31** | `setPids()` shall reject a list exceeding `getMaxPids()` or containing an invalid PID, leaving the filter state unchanged. | Valid PID range is 0 to 0x1FFF. |
| **HAL.BROADCAST.32** | No filtered data shall be made available before the first successful `setPids()` or `setAllPids()` call. | Prevents delivery of data predating client configuration. |
| **HAL.BROADCAST.33** | Closing a filter shall stop it and invalidate the contained Binder interface. | |
| **HAL.BROADCAST.34** | Tearing down a parent shall release any child resources still held, so leaked children cannot hold hardware capacity. | Demultiplexer teardown releases filters. |

### Software Input

| # | Requirement | Comments |
|---|-------------|----------|
| **HAL.BROADCAST.35** | `createSoftwareInput()` shall throw `EX_UNSUPPORTED_OPERATION` on a demultiplexer that reports `acceptsDataFromSoftware` as false. | |
| **HAL.BROADCAST.36** | A software-input ID shall remain valid while no client holds the interface, and shall be invalidated only by `destroySoftwareInput()`. | Creation, acquisition and destruction are distinct stages. |
| **HAL.BROADCAST.37** | `destroySoftwareInput()` shall throw `EX_ILLEGAL_STATE` while the input is still acquired. | |
| **HAL.BROADCAST.38** | Data written through a software input shall be processed by the demultiplexer's filters as if received from a hardware source. | |
| **HAL.BROADCAST.39** | The ring buffer returned by `openForWriting()` shall be non-overflowing: when full, the producer's `acquire()` shall return `null` rather than overwrite unread data. | Back-pressure, not data loss; a replayed stream must not be corrupted. |

### Conditional Access

| # | Requirement | Comments |
|---|-------------|----------|
| **HAL.BROADCAST.40** | `setPower()` shall throw `EX_UNSUPPORTED_OPERATION` when `CaCapabilities.powerControl` is `NONE`. | |
| **HAL.BROADCAST.41** | A slot reporting `SHARED` power control shall document the components with which the line is shared. | Platform-specific; affects client power sequencing. |

---

## General Design Principles

The following principles apply across the frontend, demultiplexer, software-input, and CA APIs.

### Discovery Is Non-exclusive

The interfaces returned by `IBroadcastManager.getFrontend()`, `getDemux()`, and `getCaSlot()` identify persistent
platform resources. More than one client may hold these interfaces and query resource information at the same time.
Holding one confers no exclusive claim.

Exclusive operations use separate interfaces. `IFrontend.open()` returns an `IFrontendController`, `IDemux.connect()`
returns an `IDemuxController`, and `IFrontend.openLnb()` returns an `ILnbController`. Only one such controller is made
available for the corresponding exclusive resource at a time. Each of these acquisitions takes the caller's
`IBroadcastClientToken` as its first argument, which is what binds the resulting claim to the client's lifetime; see
[Detecting Client Death](#detecting-client-death).

The `isOpen()` and `isConnected()` methods provide snapshots for diagnostics and resource selection. They do not reserve
a resource. Another client can change the state between the query and a subsequent `open()` or `connect()` call.
Clients therefore have to use the acquisition result, rather than a preceding state query, as the authoritative outcome.

### Interfaces Express Ownership and Provenance

Once an object has been created or acquired, the API normally passes its Binder interface directly instead of
converting it to an integer handle. The interface identifies both the object and the service instance that created it.
This preserves type information and allows the service to validate object provenance.

The factory that creates an interface is also responsible for invalidating it:

- a frontend consumes its own `IFrontendController` in `close()`;
- a frontend consumes its own `ILnbController` in `closeLnb()`;
- a demultiplexer consumes its own `IDemuxController` in `disconnect()`;
- a demultiplexer controller consumes a `Filter` returned by its own `openFilter()` in `closeFilter()`;
- a software input consumes its own `IRingBufferSink` in `closeForWriting()`; and
- a data filter consumes its own `IRingBufferSource` in `unregisterConsumer()`.

Provenance answers *which object came from where*. It does not answer *who owns the claim*, which is why the
acquiring calls additionally take an `IBroadcastClientToken`: the returned controller identifies the resource, while
the token identifies the client entitled to release it.
### Failure Signalling: `null` vs Exception

Methods that hand out a resource (`open()`, `openLnb()`, `connect()`, `createSoftwareInput()`, `openFilter()`) are
`@nullable` and use two distinct mechanisms. Exactly one applies to any given failure, never both:

1. **`null` — resource contention or exhaustion.** The request was well-formed and the operation is supported, but the
   resource is unavailable right now: already held by another client, or the implementation has no more instances of
   that type. This is an expected runtime outcome and every client must handle it. A client may reasonably retry later.
2. **Binder exception — programming error or unsupported capability.** The request can never succeed as issued:
   `EX_ILLEGAL_ARGUMENT` for an invalid or already-in-use argument, `EX_UNSUPPORTED_OPERATION` for a capability the
   hardware does not have. Retrying the same call is pointless.

The practical consequence is that a client checks the `Status` first, and only then checks the returned interface for
`null`. A condition documented as returning `null` will never also throw, and vice versa.

Strings are generally avoided both for arguments and return values, for obvious reasons.

Clients need to return the exact object to the factory from which it originated. An equivalent ID or an interface
obtained from another resource is not interchangeable. Services need to reject foreign or stale objects with
`EX_ILLEGAL_ARGUMENT` and prevent further operations after an object has been invalidated.

### IDs Are Opaque Resource Names

Type-safe IDs are used for discovery and for resources that have a created lifetime independent of a currently acquired
interface. Clients should treat the numeric value inside an ID as opaque. They should not infer hardware topology,
capabilities, or ordering from it, and should not pass an ID to a different resource type or service instance.

Frontend, demultiplexer, and CA slot IDs come from the manager's enumeration methods. A software-input ID comes from
`IDemux.createSoftwareInput()` and is valid only for that demultiplexer until `destroySoftwareInput()` succeeds.
Retaining an ID does not retain an acquired controller or guarantee that the underlying resource is currently free.

### Capabilities Are the Runtime Contract

The AIDL enums describe the complete vocabulary of the interface, not the features of every platform resource. Clients
need to query the capabilities of the specific frontend, demultiplexer, or CA slot before selecting parameters or
assuming an operation is supported.

A frontend can support more than one broadcast standard. `getFrontendTypes()` reports the available standards, and
`getCapabilities()` returns the ranges and standard-specific values for one of them. The active member of
`FrontendCapabilities.specifics` corresponds to the requested type. Similarly, the active member of `TuneParameters`
selects both the tuning standard and the parameter structure used for that request.

An `AUTO` enum member is a real capability, not permission for the service to try arbitrary values. A service should
advertise `AUTO` only where the underlying implementation performs automatic detection as defined by the relevant
capability type. Clients should otherwise select an explicitly advertised value.

Demultiplexer capabilities describe accepted source classes, supported filter types, and finite instance counts.
Clients should use them when constructing a pipeline, but still handle resource exhaustion because another client may
acquire capacity after the capability query.

### Types and Value Validation

Primitive types are used for frequently transferred scalar values to keep Binder overhead low. This creates a deliberate
trade-off between wire efficiency and type safety. Both sides need to apply the semantic constraints documented for
each value:

1. A value that is semantically unsigned is invalid when negative, unless a documented negative sentinel is used.
2. A value with a fixed range, such as an MPEG-2 Transport Stream packet identifier (PID), is invalid outside that
   range.
3. A value with a resource-specific range, such as a frequency or symbol rate, is invalid outside the capabilities
   reported by that resource.
4. An enum argument has to be a defined member of that enum. `UNDEFINED` is an initialisation value and is not a valid
   operational choice.

Services should validate the complete request before changing hardware state. Invalid input is reported with
`EX_ILLEGAL_ARGUMENT`; it should not be clamped, partially applied, or silently replaced with a default. Clients should
validate against the reported capabilities before making the call, while still checking the Binder status in case the
request is rejected.

Strings are avoided on operational paths. Structured parcelables and enums carry values with stable semantics, while
type-safe parcelable IDs are retained where identity is more important than the cost of an additional object.

### Binder Status Is the Operation Result

Mutating methods generally return `void`. Success or failure is communicated through the Binder status rather than a
second Boolean result. Query methods return Boolean values only when the Boolean is itself the requested state, such as
`isOpen()`, `isConnected()`, or `isOverloaded()`.

Clients need to inspect the status of every Binder transaction before using its return values. Services should use
specific exception categories consistently:

- `EX_ILLEGAL_ARGUMENT` for invalid values or objects from the wrong factory;
- `EX_ILLEGAL_STATE` when the resource lifecycle does not permit the operation; and
- `EX_UNSUPPORTED_OPERATION` when the resource does not implement an optional capability.

A nullable result represents an expected acquisition failure for methods that explicitly define it, for example when an
exclusive resource is already held or finite capacity has been exhausted. It does not remove the need to check the
Binder status.

### Interface and Implementation Versions Have Different Purposes

The stable AIDL interface version describes wire compatibility. `getImplementationVersion()` identifies a particular
service implementation and its release. The implementation version is useful for diagnostics and defect tracking, but
it is not a substitute for interface-version checks or runtime capability queries. Client behaviour should not depend
on parsing the implementation name or assigning undocumented meaning to its semantic version.

`ParcelableHolder` fields are extension points for later or implementation-specific data. Portable clients should
continue to operate when an extension is empty or contains data they do not understand. An extension should not change
the meaning of base fields or be used as an implicit replacement for capability negotiation.

## Reception Pipeline

A complete reception pipeline is composed explicitly from independently managed source, demultiplexer, and output
resources. This makes the API usable for both hardware reception and software-fed playback without embedding
platform-specific connection details in the client.

### Frontend Tuning and LNB Control

`IFrontend` is a shared description of a physical frontend. Its controller is the exclusive tuning lease. A client may
share that controller inside its own process, but it then owns the synchronisation of all tune, stop, status, and signal
queries made through it.

Tuning is asynchronous. A successful `tune()` call means that the request was accepted, not that signal lock was
obtained. A later `tune()` supersedes an earlier request, including one that is still in progress. Clients should treat
the most recently accepted request as authoritative and should not assume that they will observe every intermediate
status.

LNB control is a separate exclusive lease. Opening a frontend controller does not implicitly open the LNB controller,
and opening the LNB controller does not tune the frontend. Satellite clients need to coordinate these two objects in the
order required by their equipment. Services need to serialise access to shared frontend and LNB hardware where one
operation can affect the other.

`open()`, `openLnb()` and `acquireDataProvider()` each take the client token first. A client normally passes the same
token to all three, so that losing the client releases the tuning lease, the LNB lease and the provider together.

### The Data Provider Is an Opaque Connection Endpoint

`IDemuxDataProvider` is intentionally empty. It is an opaque Binder object that represents a source endpoint which can
be connected to a demultiplexer. A frontend or software input creates the provider, and the demultiplexer consumes it
when establishing the connection.

The empty public interface keeps platform details out of clients. A service can attach private state to its
implementation, such as routing information, driver handles, or a reference to an internal stream endpoint. Clients
must not cast the provider to a vendor interface, call implementation-specific methods on it, or attempt to construct
one themselves.

A provider is a leased connection endpoint, and is distinct from the `IBroadcastClientToken` that identifies the
owning client:

1. The client acquires it from exactly one source, passing its client token.
2. The client passes it to `IDemux.connect()`, again with its client token.
3. `IDemux.disconnect()` returns the same provider.
4. The client releases it to the source that created it.

The source and demultiplexer validate each transition. A provider cannot be connected to more than one demultiplexer,
and a demultiplexer cannot be connected to more than one provider. Returning the provider from `disconnect()` makes the
handover explicit and gives the client the object required to complete release at the source.

### Demultiplexer Control and Filters

`IDemux` is the shared resource interface. Connecting a provider creates the exclusive `IDemuxController` used to
allocate filters. The source lease and demultiplexer lease are distinct: acquiring a provider does not reserve a
demultiplexer, and querying a demultiplexer does not reserve a source.

Filter creation is type-driven. The active member of `FilterParameters` selects the concrete filter type and carries its
initial parameters. The returned `Filter` union contains the matching concrete Binder interface. Clients should use the
union discriminator rather than relying on enum ordinals or assumptions about which member a service returned. Services
should ensure the returned filter type matches the requested parameter member.

Data filters and tunnel filters have intentionally different roles. `IMpeg2TsDataFilter` exposes opaque transport-stream
data to a software consumer through an `IRingBufferSource`. The clock, video, audio, and supplementary-audio interfaces
are opaque endpoints for a tunneled platform pipeline. Their empty interfaces represent identity and connection
eligibility; they do not imply that elementary-stream data is available to the client process.

Closing a filter through its demultiplexer controller stops it and invalidates the contained Binder interface. A client
should unregister a data consumer before closing its data filter and should close all filters before disconnecting the
demultiplexer. The service should also make parent teardown clean up any remaining child resources so that leaked
filters cannot keep hardware capacity allocated indefinitely.

Filter reconfiguration can leave previously produced data in the output ring buffer. In particular, changing the PID
selection does not flush data automatically. Clients that require a strict discontinuity boundary need to account for
buffered data and use the Ring Buffer HAL's flush mechanism where appropriate.

### Software Input

A software input allows recorded or network data to enter the same demultiplexer path as a hardware source. Its
lifecycle has separate creation, acquisition, writing, and destruction operations:

- `createSoftwareInput()` creates a demultiplexer-owned resource and returns its ID;
- `acquireSoftwareInput()` obtains the interface for that created resource, taking the client token first;
- `openForWriting()` provides the producer side of a ring buffer;
- `acquireDataProvider()` exposes the input as a source endpoint for demultiplexer connection;
- the corresponding close and release methods end each temporary lease; and
- `destroySoftwareInput()` removes the created resource after all acquisitions have ended.

Creation and destruction are not themselves exclusive claims and so carry no token; the acquisition between them is.

These stages should not be collapsed into the lifetime of one local object. A software-input ID can remain valid while
no client has the interface acquired, and releasing the interface does not destroy the resource. Clients need to retain
the originating demultiplexer and ID until destruction is complete.

### Ring Buffers Form the Bulk-data Plane

Binder carries control operations and object references; transport-stream bytes are exchanged through the Ring Buffer
HAL. A software-input client is the producer and receives an `IRingBufferSink`. A client consuming
`IMpeg2TsDataFilter` output is the consumer and receives an `IRingBufferSource`.

The ring buffer behind a software input is **non-overflowing**. A software input replays a stream the client already
holds — a recording, or a network feed it is buffering — so when the demultiplexer falls behind, the right answer is to
stall the writer rather than to overwrite transport packets it has not yet read. `acquire()` returns `null` when the
buffer is full and the client waits for `onSpaceAvailable()`. Discarding packets here would corrupt the stream being
replayed, and nothing in this interface would let the client detect or repair the damage.

## Observation and Polling

The frontend control API deliberately uses polling instead of callbacks. This keeps callback ordering and thread
management out of the tuning interface and lets each client choose a polling rate suitable for its latency and resource
constraints.

`getTuneStatus()` is the authoritative view of tune progress and subsequent loss of lock. Clients waiting for completion
need to poll until `LOCKED` or `NO_SIGNAL`, and clients that care about later signal loss need to continue polling after
lock. Polling should be bounded; a tight loop creates unnecessary Binder and hardware traffic, while an excessively long
interval delays reaction to state changes.

Signal information uses a property/value protocol. The client requests properties advertised by
`FrontendCapabilities.signalInfoProperties`, and the service returns values in the same order. Each
`SignalInfoValue` union member corresponds to one `SignalInfoProperty`, so the service needs to return the matching
union discriminator for every position.

The readiness value is as important as the signal value:

- `UNSUPPORTED` means that the property is not available for this frontend or tune type;
- `UNAVAILABLE` means that it is supported but cannot currently be measured;
- `UNSTABLE` identifies a provisional reading; and
- `STABLE` identifies a reliable reading.

Clients should not interpret a default value as a measurement unless readiness permits it. Services should express
availability through readiness rather than inventing sentinel measurements, and should return a coherent snapshot of
the requested properties as far as the hardware allows.

## Conditional Access Slots

The CA part of this API models platform slot discovery, capabilities, and basic slot power control. It does not model a
complete conditional-access session, module protocol, entitlement exchange, or demultiplexer descrambling pipeline.
Those concerns remain outside this interface for now.

`ICaSlot` represents a persistent physical slot and does not expose a separate exclusive controller. Clients need to
check `CaCapabilities` before using optional power control. `PowerControl.SHARED` also means that the power line affects
components outside the slot. The service must serialise hardware operations, while higher layers need to coordinate
policy for changes that are visible to other slot users or components.

## Concurrency, Teardown, and Recovery

Broadcast resources are finite and are often backed by hardware whose operations continue after a Binder call returns.
Implementations therefore need explicit synchronisation and failure handling at every resource boundary.

Services should serialise state-changing calls per resource while allowing independent resources to progress
concurrently. They need to protect acquisition checks and state changes as one operation, not as separate checks around
hardware work. Clients that share an exclusive controller across threads or components need to provide equivalent
serialisation on their side.

### Thread Safety

Every interface in this HAL is **thread-safe on the service side**. A client may call concurrently from several threads
without corrupting service state; the implementation serialises what it must. This is a guarantee about integrity, not
about ordering — concurrent calls may interleave in any order, so a client that needs a specific sequence must impose
it itself. That is why `IFrontendController` tells the client to synchronise internal sharing: the risk is its own
logic observing a half-applied sequence, not a broken service.

Calls are **synchronous and may block** for the duration of the underlying hardware operation. A tune request returns
once the operation has been accepted, not once the signal is locked — lock progress is observed by polling
`getTuneStatus()`. Clients should not issue blocking HAL calls from a thread that must stay responsive.

Listener callbacks, where a sub-interface defines them, are delivered on a Binder thread and not on the caller's
thread. A client must not assume a callback arrives on the thread that registered it.

### Access Policy

`BroadcastManager` controls shared tuner hardware and, on DVB-S platforms, LNB power. Binder access is therefore
expected to be restricted by platform policy — SELinux or an equivalent mechanism — to the middleware components that
legitimately need it, rather than left open to any process that can reach the service manager.

The specific policy is a platform integration concern and is deliberately not specified here: the set of permitted
clients differs by product. What the interface does assume is that such a restriction exists. The exclusivity rules in
this document defend against accidental contention between cooperating components; they are not a security boundary,
and they would not stop a hostile process from taking a frontend and holding it.

An orderly hardware-source teardown proceeds from downstream to upstream:

1. unregister ring-buffer consumers;
2. close filters through the demultiplexer controller;
3. disconnect the demultiplexer and recover the data provider;
4. release the provider to the frontend;
5. close the frontend and LNB controllers as applicable; and
6. discard all invalidated local Binder references and memory mappings.

For a software source, the client additionally closes the producer ring buffer, releases the software-input interface,
and destroys the software-input ID when it is no longer needed. Each step should be attempted only with an object
obtained from the corresponding factory.

Binder death must not leave an exclusive controller, provider, filter, or ring-buffer registration permanently
allocated. Services should associate temporary resources with the owning client and apply the same effective cleanup
when that client dies as during an explicit close sequence. Cleanup needs to be idempotent internally because Binder
death can race with a normal release.

### Detecting Client Death

Polling was adopted in preference to listeners, so there is no callback object the service could use to identify the
owner of a claim. Ownership is instead carried by an explicit `IBroadcastClientToken`.

The token is an empty interface **implemented and hosted by the client**. That is the whole point: the service
receives a remote Binder proxy, and a remote proxy is the only kind of Binder on which `linkToDeath()` is supported —
a service cannot link to death on an object it hosts itself. A client creates one token and passes the same instance,
always as the first argument, to every acquiring call it makes:

- `IFrontend.open()`, `IFrontend.openLnb()` and `IFrontend.acquireDataProvider()`;
- `IDemux.connect()` and `IDemux.acquireSoftwareInput()`.

Claims made further down the pipeline do not repeat the token, because they are already reachable only through an
object that carries one. Filters belong to the demultiplexer controller obtained from `connect()`, and the software
input's data provider belongs to the input obtained from `acquireSoftwareInput()`; both are released when the parent
claim is released. `IDemuxSoftwareInput.openForWriting()` and `IMpeg2TsDataFilter.registerConsumer()` likewise need no
token, as each already receives a client-hosted ring-buffer listener.

On acquisition the service links to the token's death and retains a strong reference to it, so the link stays valid
for the lifetime of the claim. The token must be validated before use, since it arrives from another process: a null
token, or one that is not a remote Binder hosted by the caller, is rejected with `EX_ILLEGAL_ARGUMENT`. Rejecting
locally hosted tokens matters because such a token would tie the claim to the wrong process lifetime.

When the owning client terminates — cleanly, by crash, or by being killed — the death notification releases every
claim made with that token, unwinding downstream to upstream in the order given above, so one death recovers the
entire pipeline rather than a single object. On an explicit close the service unlinks and drops its reference to the
token instead.

Because an explicit release can race the death notification, each resource needs a single "already torn down"
decision taken under the same lock that serialises its state changes; whichever path arrives second must become a
no-op rather than releasing hardware twice. Once teardown has completed the resource is immediately available:
`isOpen()` and `isConnected()` report it free, and another client may acquire it with no lingering reservation.

The token also gives the service an identity to check against. A client that holds a controller proxy but does not
own the claim can be rejected, which the interface could not otherwise express.

Binder reference counting on the returned objects remains a useful backstop — a service that retains only weak
references to the controllers it hands out will destroy them when the last remote reference goes, whether released or
dropped by a dying process — but the token is the mechanism that guarantees release, and is what implementations
should build on.

Clients should treat service death as invalidating the complete object graph obtained from that service instance.
Recovery means releasing local file descriptors and mappings, reconnecting to `IBroadcastManager`, rediscovering
resource IDs, reacquiring every controller and provider, and rebuilding the pipeline. Old IDs and Binder objects should
not be reused across reconnection, even if their numeric values appear unchanged.

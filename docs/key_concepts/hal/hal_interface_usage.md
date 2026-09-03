# HAL Interface Usage

How a HAL component is used by the two processes either side of it: which code
each one compiles, which direction the calls run, and how each selects the
version it builds against.

## Two processes, one contract

A HAL component is a contract between two processes built and delivered by
different organisations:

- the **vendor HAL** implements it and registers it with the service manager — the **server**;
- the **middleware** binds to that service and calls it — the **client**.

The generated C++ gives each side its half: the implementer derives from a `Bn`
stub, the caller holds a `Bp` proxy. Neither side writes it by hand.

```mermaid
flowchart LR
    SM(["service manager"])

    subgraph MW["Middleware process — client"]
        direction TB
        MWA["application code"]
        MWP["BpAudioDecoder<br/>proxy — calls out"]
        MWS["BnAudioDecoderEventListener<br/>stub — receives callbacks"]
        MWA --- MWP
        MWA --- MWS
    end

    subgraph HAL["Vendor HAL process — server"]
        direction TB
        HALI["hardware implementation"]
        HALS["BnAudioDecoder<br/>stub — serves calls"]
        HALP["BpAudioDecoderEventListener<br/>proxy — calls back"]
        HALI --- HALS
        HALI --- HALP
    end

    HALS -. registers .-> SM
    SM -. discovers .-> MWP
    MWP ==>|"open · getState · getCapabilities"| HALS
    HALP ==>|"onEvent"| MWS
```

Both processes contain a `Bp` proxy *and* a `Bn` stub. That is not an artefact
of the diagram — it is the shape of every component.

## The roles invert inside a single component

The interfaces are not one-directional. Listeners run the other way:

```aidl
IAudioDecoder.Id[] getAudioDecoderIds();                       // client calls
@nullable IAudioDecoder getAudioDecoder(in IAudioDecoder.Id);  // client calls

@nullable IAudioDecoderController open(
    in Codec codec, in boolean secure,
    in IAudioDecoderControllerListener listener);              // client SUPPLIES an implementation
boolean registerEventListener(
    in IAudioDecoderEventListener listener);                   // client SUPPLIES an implementation
```

A listener is passed *into* the HAL, so the **middleware implements `Bn`** for
it and the **vendor HAL calls it through `Bp`**. 56 of the 152 interfaces in the
released tree are `*Listener` callbacks.

```mermaid
sequenceDiagram
    autonumber
    participant MW as Middleware — client
    participant SM as Service manager
    participant HAL as Vendor HAL — server

    HAL->>SM: register audiodecoder service
    MW->>SM: getService IAudioDecoderManager
    SM-->>MW: proxy
    MW->>HAL: getAudioDecoderIds()
    HAL-->>MW: Id list
    MW->>HAL: getAudioDecoder(id)
    HAL-->>MW: IAudioDecoder proxy
    MW->>HAL: registerEventListener(listener)
    Note over MW,HAL: the listener is implemented BY the middleware
    MW->>HAL: open(codec, secure, controllerListener)
    HAL-->>MW: IAudioDecoderController proxy
    HAL->>MW: onEvent(...)
    Note over MW,HAL: the HAL is now the caller — the roles have inverted
```

So neither process is purely a client or purely a server. Each is a client of
some interfaces in a component and a server of others, and the two are mirrors
of one another.

## What each process builds

Both compile the same generated code, for every component and version they use.
The client/server split runs *per interface*, not per process, so neither side
can drop a half.

The consequence matters for everything downstream: **the unit a consumer selects
is (component, version), never (component, role).**

## Version selection

Each layer pins its own set of versions and builds against it. Middleware and
vendor are built and delivered separately, and need not agree.

Compatibility is checked at runtime rather than assumed, so a client and a
server built from different versions can meet, and the client adapts or
declines. The client-side helpers and the era rules they apply are documented in
[Client Usage of Stable AIDL](../../whitepapers/client_usage_of_stable_aidl.md).

```mermaid
flowchart LR
    subgraph SNAP["Released snapshots — keyed by component and version"]
        direction TB
        S1["audiodecoder/0.2.0.0"]
        S2["audiodecoder/0.1.0.0"]
        S3["common/0.2.0.0"]
    end

    MWM["middleware manifest<br/>audiodecoder: 0.2.0.0"] -->|selects| S1
    VM["vendor manifest<br/>audiodecoder: 0.2.0.0"] -->|selects| S1

    S1 --> MWB["middleware build<br/>Bp for IAudioDecoder<br/>Bn for its listeners"]
    S1 --> VB["vendor build<br/>Bn for IAudioDecoder<br/>Bp for its listeners"]
```

The two layers select independently. Nothing requires them to choose the same
row — which is what makes the snapshot tree the shared artefact and the version
choice a per-consumer one.

Pinning per *layer* assumes one client per HAL. Where two consumers need
different versions of the same component, a per-layer choice cannot express it;
what a release must provide to support that is the subject of
[HLA: What a Released HAL Snapshot Contains](../../architecture/hla-released-snapshot-contents.md).

# Metrics

## Overview

The **Metrics HAL** service carries named numeric values from whoever measures them to whoever consumes them. It serves the **`av` domain**: the playback-quality figures a streaming partner certifies against.

Values are organised into **domains**, and a domain is the unit of extension — one added later is added without touching `av` or this interface. That is why every name is domain-qualified rather than assuming its subject.

Playback-quality metrics are a certification requirement across streaming partners — frames dropped and repeated, decode errors, underflow episodes with durations, A/V-sync excursions — with defined freshness and atomicity. Each SoC exposes these ad-hoc today (debug procfs, per-element properties, or not at all), so middleware cannot read them portably and cannot meet the accuracy contracts the certifications state. This HAL is the single vendor pull transport for them.

Middleware is the only client. It polls each source at the declared cadence, caches, and fans out to its own consumers; the HAL is not called per consumer.

---

## References

!!! info References
    |||
    |-|-|
    |**Interface Definition**|[metrics/current](https://github.com/rdkcentral/rdk-halif-aidl/tree/main/metrics/current)|
    |**Interface Version**|`current`|
    | **API Documentation** | *TBD - Doxygen* |
    |**HAL Interface Type**|[AIDL and Binder](../introduction/aidl_and_binder.md)|
    |**VTS Tests**| TBC |
    |**Reference Implementation - vComponent**|**TBD**|

---

## Related Pages

!!! tip "Related Pages"
    - [HAL Interface Overview](../key_concepts/hal/hal_interfaces.md)
    - [HAL Feature Profile](../key_concepts/hal/hal_feature_profiles.md)
    - [Video Decoder](../videodecoder/video_decoder.md)
    - [Video Sink](../videosink/video_sink.md)
    - [Audio Decoder](../audiodecoder/audio_decoder.md)
    - [Audio Sink](../audiosink/audio_sink.md)
    - [AV Clock](../avclock/av_clock.md)

---

## Versioning

| Version | Notes |
|---|---|
| `0.1.0.0` | Initial baseline. |

---

## Functional Overview

The Metrics HAL is responsible for:

- Publishing a **catalog** of every domain, element and field the product serves, with a schema identity a consumer can cache-key against.
- Enumerating the **sources** that are live now, and reporting them appearing and disappearing.
- Serving a **coherent snapshot** of every value a source holds, at a declared freshness.
- Serving the **most recent occurrence** of each episodic condition — underflow, decode error, first frame — as ordinary fields alongside the counter that totals them.
- Accepting writes to the fields declared writable: configuration, tunables and test injection.

Three properties shape the interface:

- **Every name is a declared string.** There are no key enums, no compiled-in metric list and no value union.
- **Every value is a signed 64-bit integer.** Counters use the positive range; a signed field such as `sync_offset_ms` uses the sign.
- **The metric set is not part of the ABI.** Adding a field, an element or a whole domain is a declaration change — no interface freeze, no version bump, no coordinated consumer rebuild. This is what lets the metric set track the partner certification set, which moves every year, without the HAL moving with it.

---

## The Feature Profile is the contract

`hfp-metrics.yaml` states the interface data a vendor must implement and return, and it is what the test suites validate a device against. **A field is defined there and nowhere else** — its meaning and this product's declaration of it are the same statement, so there is no separate dictionary to agree with.

Each field carries what a vendor needs to implement it and what a test needs to assert against it:

```yaml
- name: frames_decoded
  unit: frames
  kind: counter
  id: 0x63c81c7efbe7e743        # generated
  provider: Driver
  description: >
    Compressed frames the decoder has decoded and emitted at its output
    (post-decode, pre-sink). +1 per emitted frame. Counted from instance
    creation; never reset on flush/seek.
```

Everything else is generated from it by `scripts/generate.py`, which takes no arguments:

```text
hfp-metrics.yaml                     authored - the contract
    │
    ├─→ id: on each field             computed and written back in
    ├─→ docs/field_dictionary.md      human-readable reference
    └─→ docs/metrics_requirements.md  the assertions a test makes, one per field
```

It regenerates, verifies the result is stable, checks the profile, and exits non-zero if anything is wrong.

### One profile per layer

This profile is the **HAL layer's** — what a SoC vendor owes. A layer above the HAL keeps its own profile in its own repository: the middleware that owns the session state machine declares its figures there, not here, and a vendor is never asked to serve them.

`getCapabilities()` returns the union of every profile live on the device, which composes without translation only because each follows the same shape. **A layer never declares another layer's fields** — that is what keeps "who owes this figure" answerable from the file it appears in.

Because a consumer above reads the union, the top layer publishes a **combined field dictionary**: every field a caller can see, across every layer that declares one, with the layer that produces each. That document is the top layer's to publish, from its own repository — `scripts/generate.py` produces it here when a working copy of an upper layer's unique fields is present, and produces nothing extra when there is not.

Contract ids are computed identically at every layer, from `path|unit|kind`, so an id means the same thing across the union without anything having to co-ordinate.

### Field contract id

Every field carries an id derived from the contract that governs how it may be read:

```text
id = first 8 bytes of SHA-256("<domain>.<element>.<field>|<unit>|<kind>")
```

Those 8 bytes are carried big-endian as the bit pattern of `MetricFieldInfo.id`. Roughly half of all ids have the top bit set and so arrive as a negative `long`; a consumer compares the 64 bits, never the signed magnitude. The declaration writes the same value as an unsigned `0x`-prefixed 16-digit literal.

Nothing allocates it, so there is no registry to consult and nothing to resolve when two people add a field on separate branches.

It buys a check no key can make alone. A key — a name or an ordinal — stays valid while the meaning underneath it changes: a product that declares `decode_latency_sum_us` but populates milliseconds still matches by name, and its consumer reports figures a thousand times wrong; a `current` sample reclassified as a `counter` gets differenced into nonsense. Because `unit` and `kind` are hashed, both change the id, so a consumer comparing against the id it was built with sees a hard mismatch rather than a wrong number.

The id is not compiled into the interface. It reaches a client at runtime on `MetricFieldInfo`:

1. **Resolve once.** `getFields()` returns every field a source serves — every key its declaration carries, including the id. The client keeps the ones it understands and caches `name → id`.
2. **Read many.** `getAll()` returns `MetricKVPair{name, value}` and nothing else. The id does not ride the poll path, because it cannot change between resolutions and the client already holds it.
3. **Re-resolve on change.** `Capabilities.schemaId` changing is the signal that the declared set moved. An id that changed under a name the client already knew means the meaning moved, and the client stops trusting that field rather than reporting it wrongly.

### Two contracts, one declaration

A profile states a field once, and two audiences read that statement.

| | Read by | Where it lives | Keys |
|---|---|---|---|
| **Declaration** | The vendor implementing the field, the test suite asserting it, a reviewer | The profile and the reference generated from it | `provider`, `description`, `derivedFrom`, `from` |
| **Runtime** | A consumer reading a value | `MetricFieldInfo` and its parents | `name`, `unit`, `kind`, `writable`, `id`, and the domain's `derived` |

The runtime set is the smaller one deliberately. Field data is returned per field, per source, so a device declaring 45 fields would carry roughly 8 KB of prose on every source to say something fixed that no consumer computes with. The test for a key is not whether it is true, but whether a consumer's arithmetic changes when it does not know it.

Provenance splits on exactly that test. Whether a figure is measured or computed **does** change what a consumer may do — differencing a computed value as though it were an instrument reading yields a number nothing measured — so it is carried, as `MetricDomainInfo.derived`, once per domain. Which inputs produced it does not change how it is read, and stays in the profile.

### No SoC-private namespace

A figure only one SoC can produce still gets a profile entry with a full description. A private range would let a vendor ship a name nothing defines, and every consumer of it would grow per-SoC code.

## Metric Naming

Every metric name is four segments, fully qualified. There is no short form.

```text
<domain>.<element>.<instance>.<field>

av.video_decoder.0.frames_decoded
av.video_sink.1.frames_dropped_late
av.clock.0.sync_offset_ms
av.audio_sink.0.underflowed
```

| Segment | Meaning |
|---|---|
| **domain** | The subject area, and the unit of extension — a new domain touches nothing that exists |
| **element** | The thing within that domain which produces figures |
| **instance** | Which one. Always present, `0` where the element is a singleton |
| **field** | The metric |

The first three segments address a **source**; the fourth selects a field within it. `getSource("av.video_decoder.0")` returns one `IMetricsSource`, and one read of it is one coherent snapshot — the atomicity boundary is therefore visible in the name.

**A name given to a source is bare; a name returned in a value is fully qualified.** The source already fixes the first three segments, so `getFieldsByName(["frames_decoded"])` feeds back exactly what `getFields()` returned, and asking one source for another's field cannot be expressed. A value, by contrast, outlives the call that produced it — in a log line, a merged set or a bug report, `frames_decoded` alone says nothing about which source produced it, so `MetricKVPair.name` carries the whole path.

The path **is** the identity. There is no source-id parcelable, because modelling it a second time only creates a way for the two to disagree.

Names are by **subject, not producer**. Which block sources a figure differs per SoC, and for some fields it is middleware rather than the SoC at all, so a producer-shaped name would move between products for the same metric.

---

## Implementation Requirements

|#| Requirement | Comments |
|--|---|---|
| **HAL.METRICS.1** | Every metric name shall be the fully-qualified four-segment path `<domain>.<element>.<instance>.<field>`. | A bare field name is ambiguous once merged: `frames_decoded` from `av.video_decoder.0` and `av.audio_decoder.0` are the same string. |
| **HAL.METRICS.2** | Every metric value shall be a signed 64-bit integer. | AIDL `long`. Counters use the positive range and never the sign; a signed field such as `sync_offset_ms` uses it; a boolean-shaped field is 0 or 1. |
| **HAL.METRICS.3** | All values returned by one `getAll()` or `getFieldsByName()` call shall be sampled at a single instant. | An obligation on the implementation, not a property to be discovered — a source spanning two hardware blocks shall latch both. Paired counters must never yield an impossible ratio. |
| **HAL.METRICS.4** | Counters shall be cumulative since source creation and shall not reset on flush or seek. High-water fields shall be monotone non-decreasing. | Consumers compute deltas. |
| **HAL.METRICS.5** | A read shall reflect events no older than the element's declared `pollCadenceMs`, which shall not exceed 50 ms. | A maximum staleness, not a rate to poll at. An element may guarantee tighter; never looser. Freshness is a partner-facing promise. |
| **HAL.METRICS.5a** | A read shall never be rejected, rate-limited or throttled for arriving sooner than `pollCadenceMs`. | It bounds what is worth reading, not what is allowed. A consumer polling faster reads the same values again, because nothing refreshed them in between. |
| **HAL.METRICS.6** | A field the implementation cannot measure shall be left undeclared and omitted from reads. | It shall never be served as `0`. "Cannot measure it" and "measured zero" are different facts. |
| **HAL.METRICS.7** | Every field returned shall be declared in `hfp-metrics.yaml` with `unit`, `kind` and `writable`, and every name used shall exist in that domain's dictionary at the declared `dictionaryVersion`. | There is no SoC-private namespace: a figure only one SoC can produce still gets a dictionary entry, so no consumer grows per-SoC code. |
| **HAL.METRICS.8** | Every episodic condition shall be reported as a `counter` totalling occurrences, and where a consumer needs per-occurrence detail, `current` fields describing the most recent one. | A poll cannot recover an occurrence it did not sample, so the count is what makes the occurrence visible and the `last_*` fields are what make it diagnosable. |
| **HAL.METRICS.9** | Where a consumer requires exact PTS, a `*_pts_ms` field shall be within ±1 frame interval of the occurrence it describes. Where genuinely underivable it shall be left undeclared. | Never a sentinel value. |
| **HAL.METRICS.10** | `MetricElementInfo.instances` shall state how many of the element the hardware supports, and shall agree with the owning HAL's own feature profile. | The ceiling, not the live count. No source index `>= instances` shall ever appear. |
| **HAL.METRICS.11** | The implementation shall hold no per-caller state. | Every read is a snapshot of what the source holds now. Any consumer reads at any cadence without affecting another; fan-out is a middleware concern. |
| **HAL.METRICS.12** | Values shall be presented in canonical units and semantics regardless of the SoC's raw representation. | The provider is an adapter, not a passthrough. A transform normalises representation; it cannot manufacture information, so where a SoC reports only a combined figure the finer-grained fields stay undeclared rather than derived by guesswork. |
| **HAL.METRICS.13** | Every field returned shall carry the `id` its `<domain>.<element>.<field>`, `unit` and `kind` hash to. | Nothing allocates it, so it needs no registry. A product that serves a name in the wrong unit, or with the wrong kind, becomes a hard mismatch at the consumer rather than a silently wrong number. |

---

## Interface Definitions

| Interface Definition File | Description |
|---|---|
| `IMetricsManager.aidl` | Metrics Manager HAL interface — catalog and live source enumeration. |
| `IMetricsSource.aidl` | Metrics HAL interface for a single source (`<domain>.<element>.<instance>`). |
| `IMetricsManagerEventListener.aidl` | Listener callbacks to clients from the `IMetricsManager` for sources appearing and disappearing. |
| `Capabilities.aidl` | The catalog — every profile live on this product, with the schema identity. |
| `MetricProfileInfo.aidl` | One layer's declaration — its interface and schema versions, and its domains. |
| `MetricDomainInfo.aidl` | One domain and its elements, with the dictionary revision it was written against and whether it is derived. |
| `MetricElementInfo.aidl` | One element — its fields, instance count and cadence. |
| `MetricFieldInfo.aidl` | One declared field — its identity, unit, kind, writability and id. |
| `MetricUnit.aidl` | Enum of the units a field's value may carry. |
| `MetricKind.aidl` | Enum of how a field's value behaves over time. |
| `MetricKVPair.aidl` | One metric value, keyed by its fully-qualified name. |

---

## Initialization

The [systemd](../vsi/systemd/current/systemd.md) `hal-metrics_manager.service` unit file is provided by the vendor layer to start the service, and should include [Wants](https://www.freedesktop.org/software/systemd/man/latest/systemd.unit.html#Wants=) or [Requires](https://www.freedesktop.org/software/systemd/man/latest/systemd.unit.html#Requires=) directives to start any platform driver services it depends upon.

At startup:

1. The service process is launched by systemd.
2. The `IMetricsManager` implementation registers itself with the AIDL Service Manager under the service name `MetricsManager` (matching `IMetricsManager.serviceName`).
3. The implementation builds its catalog from `hfp-metrics.yaml` and derives `Capabilities.schemaId` from it.

Once registered, the service remains available for the lifetime of the system. Sources come and go beneath it as the elements they measure are created and destroyed.

---

## Product Customization

The metric set a product serves is **declared data**, not code. `hfp-metrics.yaml`, validated by `hfp-metrics-schema.yaml`, declares per element: its fields, `instances` and `pollCadenceMs`. `getCapabilities()` returns the runtime truth built from that declaration.

Two conventions to follow when filling one in:

- **Declare the whole dictionary and comment out what you cannot serve**, one line each, with `# NOT SUPPORTED — <reason>` on the same line. The file then reads as a checklist against the dictionary, so a reviewer sees what the SoC does not do rather than having to notice something missing.
- **`instances` is the ceiling.** It makes capability checkable before the product boots, lets a test assert that no source index `>= instances` ever appears, and gives CI a cross-check against the owning HAL's own feature profile. The live set comes from `getSourcePaths()`, because it is dynamic — a picture-in-picture decoder exists only while the second session does.

---

## System Context

```mermaid
flowchart TD
    Client[Middleware] -->|getCapabilities / getSourcePaths / getSource| MGR[IMetricsManager]
    Client -->|getFields / getAll / getFieldsByName| SRC[IMetricsSource]
    MGR -->|onSourceAdded / onSourceRemoved| Client
    MGR -->|builds catalog from| HFP[hfp-metrics.yaml]
    SRC -->|latches| HW[SoC Counters and Registers]

    classDef blue fill:#1565C0,stroke:#E0E0E0,stroke-width:2px,color:#E0E0E0;
    classDef wheat fill:#FFB74D,stroke:#424242,stroke-width:2px,color:#000000;
    classDef green fill:#4CAF50,stroke:#E0E0E0,stroke-width:2px,color:#FFFFFF;
    classDef default fill:#1E1E1E,stroke:#E0E0E0,stroke-width:1px,color:#E0E0E0;

    Client:::blue
    MGR:::wheat
    SRC:::wheat
    HFP:::green
    HW:::green
```

- **Middleware**: the single client. It polls, caches, and fans out to its own consumers.
- **IMetricsManager**: the catalog and the live source registry.
- **IMetricsSource**: one `<domain>.<element>.<instance>`, and the atomicity boundary for a read.
- **hfp-metrics.yaml**: the vendor declaration the catalog is built from.
- **SoC counters and registers**: where the figures come from.

---

## Resource Management

Sources are discovered, not opened. `getSourcePaths()` returns those live now; `IMetricsManagerEventListener` reports them appearing and disappearing within the scope the client registered for, so a client attaches at source start rather than polling, and hears nothing from a domain it does not read.

Reading a source acquires nothing and blocks nothing — there is no open, no controller, and no single-writer ownership, because a metrics read is side-effect free. `setField()` is the exception and applies only to fields declared `writable` (configuration, tunables and test injection).

A client that exits leaves no state behind to clean up; listener registrations are dropped when the binder link dies.

---

## Operation and Data Flow

1. **Resolve the catalog once.** `getCapabilities()` returns every domain, element and field the product serves. A consumer keeps the names it understands, ignores the rest, and cache-keys its resolved name map on `Capabilities.schemaId` — re-reading only when that value changes.
2. **Attach to the live sources.** `getSourcePaths()` gives those live now, and `registerEventListener(pathPrefix, listener)` reports later arrivals and departures **within a scope**:

   | `pathPrefix` | Reports |
   |---|---|
   | `""` | every source on the device |
   | `"av"` | one domain |
   | `"av.video_decoder"` | one element, every instance of it |
   | `"av.video_decoder.0"` | one source |

   A consumer that reads everything registers on `"av"`; one that only drives the decode path registers on `"av.video_decoder"` and is not woken for the sink or the clock. Matching is by whole segment, so `"av.video"` selects nothing — a string prefix would otherwise capture `av.video_decoder` and `av.video_sink` together and deliver sources the consumer never asked for.
3. **Poll each source.** `getAll()` returns every declared field of that source under one coherent snapshot; `getFieldsByName()` reads a subset under the same guarantee. Unknown names are omitted rather than raising an error, so a newer consumer degrades cleanly on an older product.
4. **Compute deltas.** Counters are cumulative since source creation, so rates and episode counts are the consumer's subtraction. A counter that advanced between two polls says an episode occurred; the matching `last_*` fields describe the most recent one.

`getField()` exists for diagnostics and one-off reads. It is not the poll path — a per-field loop gives up the single-snapshot guarantee that makes paired counters comparable.

---

## Episodic Conditions

Underflows, decode errors and first-frame timing are episodic — they happen at an instant rather than describing a level. They are reported as ordinary fields, in two parts:

| Part | Kind | Answers |
|---|---|---|
| `underflowed`, `decode_errors`, `freeze_event_count` | `counter` | How many have happened |
| `last_underflow_duration_ms`, `last_decode_error_pts_ms`, `last_decode_error_reason` | `current` | What the most recent one was |

A counter that advanced between two polls is what makes the occurrence visible; the `last_*` fields are what make it diagnosable. Both arrive in the same `getAll()` snapshot as every other field, so an occurrence and the counters around it are always mutually consistent.

**What this trades.** Several occurrences within one poll interval advance the counter by several and leave `last_*` describing only the newest. Rates and totals are exact; the intermediate occurrences of a burst are not individually described. This is deliberate — it removes per-source retention, sequence numbering, cursor state and overwrite accounting from every vendor implementation, and no consumer requirement asks for the middle of a burst.

`last_decode_error_reason` is the closed classification a consumer acts on; `last_decode_error_vendor_code` is the SoC's own value for the same fault, carried through uninterpreted. A vendor supplies both — the first makes the fault comparable across platforms, the second makes it debuggable on this one.

A PTS the SoC cannot derive leaves the field **undeclared**, never served as `-1`. "No PTS available" and "the PTS is minus one" must not be the same value on the wire.

---

## Platform Capabilities

`getCapabilities()` returns the catalog:

```aidl
parcelable Capabilities {
    String schemaId;
    MetricDomainInfo[] domains;
}
```

- `schemaId` is an opaque identity of this product's declared set — stable while the declaration is unchanged, different the moment anything in it changes. A bug report needs only this value to pin exactly what the device was serving.
- `domains` carries, per domain, the dictionary revision it was written against and its elements. Each element carries its fields, `instances` and `pollCadenceMs`.

### Example hfp-metrics.yaml

```yaml
metrics:
  interfaceVersion: "0.1.0.0"
  schemaVersion: "0.1.0"
  domains:
    - domain: av
      dictionaryVersion: "1.1"
      elements:
        - element: video_decoder
          instances: 2            # ceiling - must agree with hfp-videodecoder.yaml
          pollCadenceMs: 20
          fields:

            # frames_decoded: Compressed frames the decoder has decoded and emitted at its
            #                 output (post-decode, pre-sink). +1 per emitted frame. Counted
            #                 from instance creation; never reset on flush/seek.
            - { name: frames_decoded, unit: frames, kind: counter, id: 0x63c81c7efbe7e743 }

          # - { name: frames_corrupted, unit: frames, kind: counter }   # NOT SUPPORTED - no
          #                                                             # per-frame integrity
          #                                                             # signal on this SoC
```

Descriptions and ids are generated by `scripts/generate.py` from the field dictionary at the pinned `dictionaryVersion`; neither is hand-edited. A product that cannot serve a field comments the entry out in place with a reason on the same line, so the file reads as a checklist against the dictionary rather than going silent.

---

## Error Handling

| Condition | Behaviour |
|---|---|
| Path not live | `getSource()` returns `null`. |
| Unknown name in `getFieldsByName()` | Omitted from the result, so a newer consumer degrades cleanly on an older product. |
| Unknown name in `getField()` | Returns `false`. |
| `setField()` on a read-only field | `EX_UNSUPPORTED_OPERATION`. |
| `setField()` on an undeclared name | `EX_ILLEGAL_ARGUMENT`. |
| Field the product cannot measure | Undeclared, and omitted from every read. Never served as `0`. |
| Consumer polls slower than episodes occur | Counters stay exact; `last_*` fields describe the newest occurrence only. Rates and totals are unaffected. |

---

## Metrics Collection Sequence

```mermaid
sequenceDiagram
    participant Client as Middleware
    participant MGR as IMetricsManager
    participant SRC as IMetricsSource

    Client->>MGR: getCapabilities()
    note over Client: Resolve once. Cache-key the name map<br>on Capabilities.schemaId.
    Client->>MGR: registerEventListener(listener)
    Client->>MGR: getSourcePaths()
    MGR-->>Client: ["av.video_decoder.0", "av.video_sink.0", ...]
    Client->>MGR: getSource("av.video_decoder.0")
    MGR-->>Client: IMetricsSource

    loop Per poll tick, per source
        Client->>SRC: getAll()
        SRC-->>Client: fully-qualified name/value pairs, one coherent snapshot
        note over Client: Counters advanced -> an episode occurred.<br/>last_* fields in the same snapshot describe the newest one.
    end

    note over MGR,Client: A second session starts.
    MGR-->>Client: onSourceAdded("av.video_decoder.1")
    note over Client: Attach without polling getSourcePaths().
    MGR-->>Client: onSourceRemoved("av.video_decoder.1")
```

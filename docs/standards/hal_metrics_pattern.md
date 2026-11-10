# HAL Metrics Pattern

A HAL component that produces a figure worth measuring serves it itself, from its own interface, with its own types. This page is the pattern to copy when adding metrics to a component, by hand or with an AI assistant. The worked example is [Video Sink](../videosink/video_sink.md#metrics).

```mermaid
sequenceDiagram
    participant C as Client
    participant H as HAL component
    C->>H: getMetrics([FRAMES_RENDERED, FRAMES_DROPPED])
    Note over H: latch time and values together
    H-->>C: MetricSnapshot {timestampNs, values[]}
    Note over H: a frame arrives late and is dropped
    H-)C: onFrameDropEvent(FrameDropEvent)
    Note over H: queue empty when a frame is due
    H-)C: onUnderflowStarted(UnderflowStartedEvent)
    Note over H: next frame presented
    H-)C: onUnderflowResolved(UnderflowResolvedEvent)
```

## Rules

| # | Rule |
|---|---|
| M1 | The component that produces a figure serves it. No shared metrics module, no shared metric types and no generated identifiers: every type below lives in the component's own package. |
| M2 | Metrics are a `Metric` enum, `@VintfStability`, `@Backing(type = "int")`, numbered from 0 and append-only. A member is never renumbered or reused. |
| M3 | A value is a `long` in the unit its member documents. Time is in nanoseconds and the member name ends `_NS`. |
| M4 | A metric is a counter or a gauge. A counter starts at zero when the service initialises and only rises; no call resets it. Each resource instance keeps its own figures, across every session opened on it. A gauge is the level at the instant of the read. |
| M5 | `getMetrics(in Metric[] metrics)` returns a `MetricSnapshot`. The service latches `timestampNs` (`CLOCK_MONOTONIC_RAW`, nanoseconds) and every value at one instant, at the start of the read, before copying any out. An empty array asks for every supported metric. |
| M6 | Each `MetricValue` carries its `Metric` id. A metric that is not supported, or has no value at present, has no entry in the snapshot; there is no sentinel value and no status field. |
| M7 | `getMetric(in Metric metric)` returns one value. It throws `EX_UNSUPPORTED_OPERATION` for a metric the product does not support and `EX_ILLEGAL_STATE` for one that has no value at present. |
| M8 | Both accessors are callable in any state. |
| M9 | The metrics a product serves are listed once, as `supportedMetrics` under the component in its HAL Feature Profile, and apply to every resource instance. |
| M10 | A countable occurrence has an event: one callback on the component's event listener, with its own parcelable. An episode, something with a start and an end, has a pair: `on<Thing>Started` and `on<Thing>Resolved`. |
| M11 | Every event parcelable carries `timestampNs`, the `CLOCK_MONOTONIC_RAW` time the service detected the event, and the values that belong to it: presentation time (`-1` where the frame carried none), and for a resolved event the duration and any count. |
| M12 | A figure is counted where it is experienced. Where a decoder and a sink could both report something, the component whose figure describes what the audience saw or heard serves it, and the other does not duplicate it. |
| M13 | Deliberate behaviour is excluded: frames discarded by a flush, a seek, a reconfiguration, a stop, end of stream or pacing are not drops, and repeats made by frame rate conversion are not freezes. |
| M14 | Metrics from two components are two reads, latched separately. Document any pairing a client is likely to make as approximate. |

## Files

| File | Content |
|---|---|
| `Metric.aidl` | The enum. |
| `MetricValue.aidl` | `{ Metric id; long value; }` |
| `MetricSnapshot.aidl` | `{ long timestampNs; MetricValue[] values; }` |
| `<Thing>Event.aidl`, `<Thing>StartedEvent.aidl`, `<Thing>ResolvedEvent.aidl` | One parcelable per callback. |
| `I<Component>.aidl` | `getMetrics()` and `getMetric()`, appended after the existing methods. |
| `I<Component>EventListener.aidl` | The event callbacks, appended after the existing methods. |
| `hfp-<component>.yaml` | `supportedMetrics`. |
| `docs/<component>.md` | A `Metrics` section, the requirement rows and the new files in the interface table. |

## Metric documentation

Every `Metric` member carries the same six paragraphs, in this order. A reader must be able to implement the metric, and use it, from the member's comment alone.

| Paragraph | Says |
|---|---|
| `@brief` | The figure in one line. |
| `Measures:` | What is counted, and the point in the component where it is counted. |
| `Excludes:` | What is deliberately left out, and which metric counts it instead. |
| `Used for:` | The question the figure answers. |
| `How to use:` | The calculation: what to difference, what to divide by, which event carries the detail. |
| `Unit:` / `Kind:` | The unit, and counter or gauge. |

```aidl
    /**
     * @brief Frames discarded because they arrived too late.
     *
     * Measures: frames queued to the sink and discarded without being
     * presented because their presentation time had passed, counted at the
     * sink.
     *
     * Excludes: frames discarded on purpose by flush(), a seek, a stream
     * reconfiguration, stop() or end of stream, frames removed by frame rate
     * conversion or pacing, and frames the decoder never output
     * (com.rdk.hal.videodecoder.Metric::FRAMES_DROPPED).
     *
     * Used for: measuring stutter the viewer saw.
     *
     * How to use: rate = delta FRAMES_DROPPED / (delta FRAMES_RENDERED + delta
     * FRAMES_DROPPED), from one getMetrics() call per snapshot. Each drop also
     * raises onFrameDropEvent().
     *
     * Unit: frames. Kind: counter.
     */
    FRAMES_DROPPED = 1,
```

## Submission checklist

- [ ] Every type is in the component's own package; nothing is imported from another component for metrics.
- [ ] `Metric` is `@VintfStability`, `@Backing(type = "int")`, numbered from 0, with new members appended.
- [ ] Every member has the six paragraphs of [metric-documentation](#metric-documentation).
- [ ] Every member names its unit; every time value is in nanoseconds and its name ends `_NS`.
- [ ] No member has a sentinel value, and `MetricValue` has no status field.
- [ ] `getMetrics()` and `getMetric()` are the last methods of the main interface, with the exceptions of rule M7.
- [ ] Every counter that marks an occurrence has an event; every episode has a started and a resolved event.
- [ ] Every event has its own parcelable, with `timestampNs` first.
- [ ] New callbacks are appended to the event listener; no existing method or callback is changed or removed.
- [ ] `supportedMetrics` in `hfp-<component>.yaml` lists members of the enum by name.
- [ ] The component document has a `Metrics` section, a requirement for the accessors and one for the events.
- [ ] Any property or callback the metrics replace is marked `@deprecated` under the [HAL API Deprecation Governance](../key_concepts/hal/hal_api_deprecation_governance.md) process.
- [ ] `./build_interfaces.sh <component>` passes, and the PR carries the `Minor Change` label.

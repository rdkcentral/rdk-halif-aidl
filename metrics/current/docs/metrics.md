# Metrics

## Overview

The `metrics` module defines the envelope every measuring HAL serves its figures through. It carries types only — no interface, no controller, no resource — so a component imports it to describe what it measures, never to reach a metrics service.

Every metric is served by the component that produces it. `videodecoder` answers for the video decoder's figures, `videosink` for the video sink's, and so on down. A component's `Metric` enum lists the figures it serves, and its metrics page gives their units and meaning; this document states the requirements it serves them under.

---

!!! info "References"
    |||
    |-|-|
    |**Interface Definition**|[metrics/current](https://github.com/rdkcentral/rdk-halif-aidl/tree/main/metrics/current)|
    |**Interface Version**|`current`|
    |**HAL Interface Type**|[AIDL and Binder](../introduction/aidl_and_binder.md)|

---

## Versioning

`metrics` imports no other HAL module, so its generation moves independently of `common/`. A `common` generation bump moves no measuring component's pin on `metrics`, and a `metrics` revision moves no component that does not measure.

The envelope is fixed so the contents are free. A new figure is a member appended to the producing component's `Metric` enum, so it reaches a consumer without a change here.

## The envelope

A metric is an enum value, a number and a status.

| Type | Carries |
|---|---|
| `MetricStatus` | Whether a figure is served, unmeasurable on this product, or underivable at this instant |
| `MetricValue` | One figure: its identifier, its 64-bit signed value, its status |
| `MetricGroup` | One element instance's reading: the element, the instance, its values |
| `MetricSnapshot` | One or more groups latched at a single monotonic instant |
| `MetricEvent` | One occurrence: when it was detected, what kind it was, which instance raised it, its attributes and values |

An event's `attributes` and `values` are separate arrays because they are different things. A value is a measurement and carries aggregation semantics — `counter`, `current`, `high_water`, `config`. An attribute dimensions the occurrence and carries none: `DECODE_ERROR_REASON` on a decode fault is a classification, and `DECODE_ERROR_PTS_MS` is where the fault was. Which array a field sits in states this, so no field carries a tag saying it.

One `MetricValue` serves reads and events, so a consumer extracts a field from an event exactly as it extracts one from a snapshot.

## Identity

Each measuring component defines its own enums, backed by `long`, and the envelope's identifier fields carry their values:

| Field | Enum |
|---|---|
| `MetricGroup.id` | `MetricElement` |
| `MetricValue.id` in a read | `Metric` |
| `MetricEvent.eventId` | `MetricEventKind` |
| `MetricValue.id` in an event | `MetricEventAttribute` |

Values run sequentially from 0 and are append-only. They are scoped to the component, so a number means something only alongside the component it was read from.

A figure with a closed set of values, such as `MetricDecodeErrorReason`, has its own enum, carried in `MetricValue.value`.

Each member's documentation states its unit and kind, and the component's metrics page lists them together.

## Accessors

Each measuring component's resource interface carries:

```aidl
MetricSnapshot getMetrics(in @nullable Metric[] metricIds);
```

`drm` names it `getDeclaredMetrics()`, because `IDrmPlugin.getMetrics()` is already taken by its vendor-defined figures.

Null asks for every metric the product serves. A list asks for those figures, and each comes back with its status — `NOT_SUPPORTED` for one the product cannot measure or does not know.

Each event-raising component's event listener carries:

```aidl
void onMetricEvent(in MetricEvent event);
```

## Implementation Requirements

|#| Requirement | Comments |
|--|---|---|
| **HAL.METRICS.1** | Every figure shall be a member of the producing component's `Metric` enum. | `Metric::FRAMES_DECODED` in `videodecoder` and in `audiodecoder` are different figures; a consumer knows which from the component it read. |
| **HAL.METRICS.2** | Every value shall be a signed 64-bit integer. | AIDL `long`. Counters use the positive range; a signed field such as `SYNC_OFFSET_MS` uses the sign; a boolean-shaped field is 0 or 1. |
| **HAL.METRICS.3** | All values returned by one `getMetrics()` call shall be sampled at a single instant and stamped with one `timestampNs`, taken from `CLOCK_MONOTONIC`. | An obligation on the implementation, not a property to be discovered. A component spanning two hardware blocks shall latch both. Paired counters shall never yield an impossible ratio, and a snapshot's age shall always be computable. |
| **HAL.METRICS.4** | Counters shall be monotonic from resource creation and shall not reset on `open()`, `flush()`, `stop()` or seek. High-water fields shall be monotone non-decreasing. | Consumers difference from a baseline of their own. |
| **HAL.METRICS.5** | A read shall reflect events no older than the element's declared `captureCadenceMs`, which shall not exceed 50 ms. | A maximum staleness, not a rate to capture at. An element may guarantee tighter, never looser. Freshness is a partner-facing promise. |
| **HAL.METRICS.6** | A field the implementation cannot measure shall be reported `NOT_SUPPORTED`, and a field not derivable at the sampling instant `NOT_AVAILABLE`. | Never `0` and never `-1`. "Cannot measure it" and "measured zero" are different facts, and on a signed field such as `SYNC_OFFSET_MS` a `-1` sentinel is indistinguishable from a legitimate one-millisecond offset. |
| **HAL.METRICS.7** | Every field returned shall be a member of the producing component's enums, documented with its unit and kind. | There is no SoC-private namespace: a figure only one SoC produces still gets an entry, so no consumer grows per-SoC code. |
| **HAL.METRICS.8** | Every episodic condition shall be reported as a `counter` totalling occurrences, and where a consumer needs per-occurrence detail, `current` fields describing the most recent one. | A capture cannot recover an occurrence it did not sample, so the count is what makes the occurrence visible and the `LAST_*` fields are what make it diagnosable. |
| **HAL.METRICS.9** | Where a consumer requires exact PTS, a `*_pts_ms` field shall be within ±1 frame interval of the occurrence it describes, and shall be `NOT_AVAILABLE` where underivable. | Never a sentinel value. |
| **HAL.METRICS.10** | Each read group shall carry the instance it reports in `MetricGroup.instance`, and the component shall serve one group per instance its hardware has, for the life of the service, agreeing with its feature profile. | An idle resource is still served, so the set is static. |
| **HAL.METRICS.11** | The implementation shall hold no per-caller state. | Every read is a snapshot of what the component holds now. Any consumer reads at any cadence without affecting another; fan-out is a middleware concern. |
| **HAL.METRICS.12** | Values shall be presented in canonical units and semantics regardless of the SoC's raw representation. | The implementation is an adapter, not a passthrough. A transform normalises representation; it cannot manufacture information, so where a SoC reports only a combined figure the finer-grained fields are `NOT_SUPPORTED` rather than derived by guesswork. |
| **HAL.METRICS.13** | Every field returned shall carry the value of its enum member as its `id`. | A consumer matches on `id`, never on position. |
| **HAL.METRICS.14** | A read shall never be rejected, rate-limited or throttled for arriving sooner than `captureCadenceMs`. | It bounds what is worth reading, not what is allowed. A consumer capturing faster reads the same values again, because nothing refreshed them in between. |
| **HAL.METRICS.15** | Every declared field's values shall behave as its `kind` states, and shall carry the meaning its enum member documents. | That documentation is the definition a test asserts against. `counter` and `high_water` behaviour is HAL.METRICS.4; `current` is a live sample re-read each capture, absolute and never summed; `config` is the present value of a tunable. |
| **HAL.METRICS.16** | Every event kind an element declares shall be raised at the instant its trigger states, stamped with `CLOCK_MONOTONIC` at detection rather than at delivery, pushed to every listener registered on that component, and shall carry the payload the declaration names. | A burst collapses in the counters; the push is what makes each occurrence individually visible. A payload field the product never serves is absent from the array; one it could not derive at that instant is `NOT_AVAILABLE`. |
| **HAL.METRICS.17** | Event delivery shall hold no buffer, sequence number or per-caller cursor, and the counters and `LAST_*` fields shall move whether or not a listener is registered. | The callback is the delivery. A consumer that registers late, or misses a call, still has the totals. |
| **HAL.METRICS.18** | An event shall be declared only for a discrete occurrence with an instant, and every element declaring one shall declare a `counter` totalling those occurrences. | A `current` level, a `config` setting and a `high_water` maximum happen at no moment and cannot be pushed. A counter of routine throughput would push a firehose saying nothing the counter does not. |

## Adding a figure

A new figure is a new member appended to the component's `Metric` enum and a row on its metrics page, which is a Minor Change on that component. A caller built against a newer enum than a product serves is answered `NOT_SUPPORTED` for the figures the product does not have.

## Error handling

A read never fails for a figure it cannot serve. Absence is carried in the value's `MetricStatus`, so a consumer asking for a figure this product does not measure receives it with `NOT_SUPPORTED` rather than an error, and a request naming several figures returns every one of them.

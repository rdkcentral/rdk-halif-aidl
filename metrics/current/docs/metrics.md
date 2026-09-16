# Metrics

## Overview

The `metrics` module defines the envelope every measuring HAL serves its figures through. It carries types only — no interface, no controller, no resource — so a component imports it to describe what it measures, never to reach a metrics service.

Every metric is served by the component that produces it. `videodecoder` answers for `av.video_decoder.*`, `videosink` for `av.video_sink.*`, and so on down. A component's Key Value Contract declares the keys it serves; this document states the requirements it serves them under.

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

The envelope is fixed so the contents are free. A new figure is an element in an array and a member appended to the producing component's `Metric` enum, so it reaches a consumer without a change here.

## The envelope

A metric is an identifier, a set of attributes and a set of values.

| Type | Carries |
|---|---|
| `MetricStatus` | Whether a figure is served, unmeasurable on this product, or underivable at this instant |
| `MetricValue` | One figure: its identifier, its 64-bit signed value, its status |
| `MetricGroup` | One element's reading: the element identifier, its attributes, its values |
| `MetricSnapshot` | One or more groups latched at a single monotonic instant |
| `MetricEvent` | One occurrence: when it was detected, what kind it was, its attributes and values |

`attributes` and `values` are separate arrays because they are different things. A value is a measurement and carries aggregation semantics — `counter`, `current`, `high_water`, `config`. An attribute dimensions the occurrence and carries none: `reason` on a decode fault is a classification, and `pts_ms` is where the fault was. Which array a field sits in states this, so no field carries a tag saying it.

One `MetricValue` serves reads and events, so a consumer extracts a field from an event exactly as it extracts one from a snapshot.

## Identity

Every identifier is the first 8 bytes of SHA-256 over the composed terms:

```
value      SHA-256("<domain>.<element>.<field>|<unit>|<kind>")
attribute  SHA-256("<domain>.<element>.<field>|<unit>")
event      SHA-256("<domain>.<element>.<event_kind>")
```

An attribute takes no `kind` term because it has no aggregation semantics to state.

Unit and kind are part of a key's identity. A product declaring a field in microseconds and populating milliseconds yields a different identifier, so a consumer sees a mismatch rather than a figure a thousand times wrong.

The identifier is 64-bit. A 32-bit space puts a birthday collision in the tens of thousands of keys, and a collision here is two measurements answering to one identifier.

Instance is runtime, not contract: a group carries `instance` in its attributes and no identifier composes with it.

Each measuring component declares a `Metric` enum backed by `long` whose member values are the generated identifiers. Position in the enum carries no meaning, so a member is added anywhere and two products that added members in different orders agree on every value.

## Accessors

Each measuring component's resource interface carries:

```aidl
MetricSnapshot getMetric(in Metric metric);
MetricSnapshot getMetrics(in Metric[] metrics);
MetricSnapshot getAllMetrics();
boolean        setMetric(in Metric metric, in long value);
```

Each event-raising component's event listener carries:

```aidl
void onMetricEvent(in MetricEvent event);
```

## Implementation Requirements

|#| Requirement | Comments |
|--|---|---|
| **HAL.METRICS.1** | Every key shall be the three-segment path `<domain>.<element>.<field>`, declared in the producing component's Key Value Contract. | A bare field name is ambiguous once merged: `frames_decoded` from `av.video_decoder` and `av.audio_decoder` are the same string. |
| **HAL.METRICS.2** | Every value shall be a signed 64-bit integer. | AIDL `long`. Counters use the positive range; a signed field such as `sync_offset_ms` uses the sign; a boolean-shaped field is 0 or 1. |
| **HAL.METRICS.3** | All values returned by one `getMetric()`, `getMetrics()` or `getAllMetrics()` call shall be sampled at a single instant and stamped with one `timestampNs`, taken from `CLOCK_MONOTONIC`. | An obligation on the implementation, not a property to be discovered. A component spanning two hardware blocks shall latch both. Paired counters shall never yield an impossible ratio, and a snapshot's age shall always be computable. |
| **HAL.METRICS.4** | Counters shall be monotonic from resource creation and shall not reset on `open()`, `flush()`, `stop()` or seek. High-water fields shall be monotone non-decreasing between writes, and where declared writable shall accept a write of 0. | Consumers difference from a baseline of their own; a maximum cannot be recovered by subtraction, so the reader zeros it instead. |
| **HAL.METRICS.5** | A read shall reflect events no older than the element's declared `captureCadenceMs`, which shall not exceed 50 ms. | A maximum staleness, not a rate to capture at. An element may guarantee tighter, never looser. Freshness is a partner-facing promise. |
| **HAL.METRICS.6** | A field the implementation cannot measure shall be reported `NOT_SUPPORTED`, and a field not derivable at the sampling instant `NOT_AVAILABLE`. | Never `0` and never `-1`. "Cannot measure it" and "measured zero" are different facts, and on a signed field such as `sync_offset_ms` a `-1` sentinel is indistinguishable from a legitimate one-millisecond offset. |
| **HAL.METRICS.7** | Every field returned shall be declared in the producing component's Key Value Contract with `unit` and `kind`. | There is no SoC-private namespace: a figure only one SoC produces still gets an entry, so no consumer grows per-SoC code. |
| **HAL.METRICS.8** | Every episodic condition shall be reported as a `counter` totalling occurrences, and where a consumer needs per-occurrence detail, `current` fields describing the most recent one. | A capture cannot recover an occurrence it did not sample, so the count is what makes the occurrence visible and the `last_*` fields are what make it diagnosable. |
| **HAL.METRICS.9** | Where a consumer requires exact PTS, a `*_pts_ms` field shall be within ±1 frame interval of the occurrence it describes, and shall be `NOT_AVAILABLE` where underivable. | Never a sentinel value. |
| **HAL.METRICS.10** | Each read group shall carry the instance it reports as an `instance` attribute, and the component shall serve one group per instance its hardware has, for the life of the service, agreeing with the `instances` its Key Value Contract declares. | An idle resource is still served, so the set is static. |
| **HAL.METRICS.11** | The implementation shall hold no per-caller state. | Every read is a snapshot of what the component holds now. Any consumer reads at any cadence without affecting another; fan-out is a middleware concern. |
| **HAL.METRICS.12** | Values shall be presented in canonical units and semantics regardless of the SoC's raw representation. | The implementation is an adapter, not a passthrough. A transform normalises representation; it cannot manufacture information, so where a SoC reports only a combined figure the finer-grained fields are `NOT_SUPPORTED` rather than derived by guesswork. |
| **HAL.METRICS.13** | Every field returned shall carry the `id` its composed terms hash to. | Nothing allocates it, so it needs no registry. A product serving a name in the wrong unit or with the wrong kind becomes a hard mismatch at the consumer rather than a silently wrong number. |
| **HAL.METRICS.14** | A read shall never be rejected, rate-limited or throttled for arriving sooner than `captureCadenceMs`. | It bounds what is worth reading, not what is allowed. A consumer capturing faster reads the same values again, because nothing refreshed them in between. |
| **HAL.METRICS.15** | Every declared field's values shall behave as its `kind` states, and shall carry the meaning its Key Value Contract gives that key. | The contract is the definition a test asserts against. `counter` and `high_water` behaviour is HAL.METRICS.4; `current` is a live sample re-read each capture, absolute and never summed; `config` is the present value of a tunable. |
| **HAL.METRICS.16** | Every event kind an element declares shall be raised at the instant its trigger states, stamped with `CLOCK_MONOTONIC` at detection rather than at delivery, pushed to every listener registered on that component, and shall carry the payload the declaration names. | A burst collapses in the counters; the push is what makes each occurrence individually visible. A payload field the product never serves is absent from the array; one it could not derive at that instant is `NOT_AVAILABLE`. |
| **HAL.METRICS.17** | Event delivery shall hold no buffer, sequence number or per-caller cursor, and the counters and `last_*` fields shall move whether or not a listener is registered. | The callback is the delivery. A consumer that registers late, or misses a call, still has the totals. |
| **HAL.METRICS.18** | An event shall be declared only for a discrete occurrence with an instant, and every element declaring one shall declare a `counter` totalling those occurrences. | A `current` level, a `config` setting and a `high_water` maximum happen at no moment and cannot be pushed. A counter of routine throughput would push a firehose saying nothing the counter does not. |
| **HAL.METRICS.19** | `setMetric` shall serve declared writable fields only. A `high_water` field shall accept `0` and reject every other value; a `config` field shall accept the range its Key Value Contract declares. | A maximum over a window cannot be recovered by differencing two maxima, so the reader zeros the high-water mark where its reporting window begins. |

## The Key Value Contract

A component's keys are declared in `<component>/kvc/<revision>/<component>.kvc`, beside the interface versions and never inside one. Publishing a revision touches no interface directory and moves no frozen hash.

An interface names the vocabulary revision it requires as a floor rather than a pin, because adding a key is compatible by construction. An interface frozen against `1.0` keeps serving when the vocabulary reaches `1.2`, and a caller built from the later revision is answered `NOT_SUPPORTED` for keys this one does not have.

`scripts/kvcc.py` derives every identifier from a contract, writes the AIDL enums, and fails where two keys collide or a key carries no description.

## Error handling

A read never fails for a figure it cannot serve. Absence is carried in the value's `MetricStatus`, so a consumer asking for a key this product does not measure receives that key with `NOT_SUPPORTED` rather than an error, and a request naming several keys returns every one of them.

`setMetric` returns `false` where the field is not writable or the value is outside what the contract declares.

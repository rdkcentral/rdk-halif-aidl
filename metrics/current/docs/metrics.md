# Metrics

AIDL interface for device metrics. See the `.aidl` files under
[current/com/rdk/hal/metrics/](current/com/rdk/hal/metrics/) for the full interface,
and [current/hfp-metrics.yaml](current/hfp-metrics.yaml) for the declaration a product ships.

**This is a general device metrics interface, not an A/V one.** It carries named
numeric values from whoever measures them to whoever consumes them, organised
into **domains**. A/V playback is the `av` domain; `cpu` and `memory` are domains
a platform may add later without touching it or this interface.

## Naming

Every metric name is four segments, fully qualified. There is no short form.

```text
<domain>.<element>.<instance>.<field>

av.video_decoder.0.frames_decoded
av.video_sink.1.frames_dropped_late
av.clock.0.sync_offset_ms
cpu.core.3.utilisation_pct
```

| Segment | What it is |
|---|---|
| **domain** | The subject area, and the unit of extension — a new domain touches nothing that exists |
| **element** | The thing within that domain which produces figures |
| **instance** | Which one. Always present, `0` where the element is a singleton |
| **field** | The metric |

The first three segments address a **source**; the fourth selects a field within
it. `getSource("av.video_decoder.0")` returns one `IMetricsSource`, and **one read
of it is one coherent snapshot** — so the atomicity boundary is visible in the name.

**The path is the identity.** There is no source-id parcelable: modelling it a
second time as a struct only creates a way for the two to disagree.

Names are by **subject, not producer**. Which block sources a figure differs per
SoC, and for some fields it is middleware rather than the SoC at all, so a
producer-shaped name would move between products for the same metric.
`av.video_sink.0.frames_dropped_late` means the same thing whoever measured it.

## What a consumer never does

Switch on an enum, index a struct member, or assume a field exists.

```cpp
// Once, at bind.
Capabilities caps;
manager->getCapabilities(&caps);
mSchemaId = caps.schemaId;               // re-resolve only when this changes

// Per tick, per source: one round-trip, one coherent snapshot.
std::vector<MetricKVPair> values;
bool ok = false;
manager->getSource("av.video_decoder.0")->getAll(&values, &ok);
for (const auto &kv : values)
    publish(kv.name, kv.value);          // kv.name is already fully qualified
```

A consumer matches the names it understands and ignores the rest, so a product
that declares more simply delivers more.

## Three properties

**Every name is a declared string.** No enums for keys, no compiled-in metric
list, no value union. A product declares what it serves; a consumer asks what is
present.

**Every value is int64** (AIDL `long`). A metric is a count, a duration, a byte
figure or an offset — all signed 64-bit. Counters use the positive range and
never the sign; a signed field such as `sync_offset_ms` uses it.

**The metric set is not part of the ABI.** Adding a field, an element or a whole
domain is a declaration change: no interface freeze, no version bump, no
coordinated consumer rebuild. That is what lets the metric set track the partner
certification set, which moves every year, without the HAL moving with it.

## Absence is absence

A field a product cannot measure is **left undeclared and omitted from reads** —
never served as `0`. "This SoC cannot measure it" and "it measured zero" are
different facts, and the interface keeps them different. The same rule applies to
event values: a PTS that cannot be derived is omitted, not sent as `-1`.

There is **no SoC-private namespace**. Every name is defined in its domain
dictionary, whatever produces it, so no consumer ever grows per-SoC code. A
figure only one SoC can produce still gets one dictionary entry, and simply goes
undeclared everywhere else.

## Events

```text
{ seq, tsUnixMs, kind, values[] }
```

`kind` is a declared string **scoped by its source**, so it carries no media
prefix: `underflow` from `av.video_sink` is a video starvation, and the same kind
from `av.audio_sink` is an audio one. Each kind declares the values it carries
(`duration_ms`, `pts_ms`, `trigger`, `code`), so a new kind never widens a
parcelable to hold a field only it uses.

The per-source buffer exists to **bridge one poll interval** — default 32,
sized from the worst-case burst within an interval rather than from a rate. An
element that out-runs its buffer needs a tighter cadence; the buffer is not
where that is fixed. Middleware is the only reader, so it holds the cursor:
pass the highest `seq` you have seen. Loss is counted, not hidden.

## Declaring a product

[current/hfp-metrics.yaml](current/hfp-metrics.yaml), validated by
[current/hfp-metrics-schema.yaml](current/hfp-metrics-schema.yaml), declares per
element: its fields (`name`, `unit`, `kind`, `writable`), its event kinds and
each kind's values, `instances`, `pollCadenceMs` and `eventBufferCapacity`.

Two conventions worth reading before filling one in:

- **Declare the whole dictionary; comment out what you cannot serve**, one line
  each, with `# NOT SUPPORTED — <reason>` on the same line. The file then reads
  as a checklist, so a reviewer sees what the SoC does not do rather than having
  to notice something missing.
- **`instances` is the ceiling, not the live count.** It makes capability
  checkable before the product boots, lets a test assert that no source index
  `>= instances` ever appears, and must agree with the owning HAL's own feature
  profile — a cross-check CI can make.

## Contract

| Contract | What the implementation commits to |
|---|---|
| **Snapshot freshness** | Any read reflects events at most as old as the element's declared cadence, floor 50 ms. An element may declare tighter, never looser |
| **Atomicity** | Every value of one `getAll()` is sampled at a single instant. An obligation on the implementation, not a property to be discovered — a source spanning two hardware blocks latches both |
| **Monotonicity** | Counters cumulative since source creation, no reset on flush or seek; high-water marks monotone non-decreasing |
| **Declaration completeness** | Every field a source returns is declared with unit, kind and writability |
| **Event PTS** | Within ±1 frame interval where a consumer requires exact PTS; **omitted** where genuinely underivable — never a sentinel |

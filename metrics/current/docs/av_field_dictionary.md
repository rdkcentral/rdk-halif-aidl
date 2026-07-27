# AV Domain Field Dictionary

The normative field set for the **`av` domain** of `com.rdk.hal.metrics`. A name means the same thing on every product that declares it; this document is what it means.

A declaration (`hfp-metrics.yaml`) states *which* of these a product serves. This dictionary states *what each one is*. A product may not declare a name that is not defined here, and may not redefine one that is — that is what keeps the interface common across SoCs, and it is why there is no SoC-private namespace.

## Relationship to concrete metric interfaces

Other interfaces already describe some of these figures as **fixed members** — a struct or a method per metric. This one deliberately does not.

A concrete interface fixes its metric set at design time, so every later addition is an interface change: a new field means a new revision, a coordinated rebuild, and a negotiation with everyone implementing against it. A declared set moves the metric list out of the contract. The interface fixes the *shape* of a metric — a name, a unit, a kind, an int64 value — and a declaration states which ones a product serves.

The practical difference is what happens when a certification adds a figure next year. Against a concrete interface, that is a version bump. Here it is a dictionary entry and a line in a declaration, with no interface change and no consumer rebuild — and a consumer written before the field existed keeps working, because it matches the names it knows and ignores the rest.

## Reading a field

Every metric is named `<domain>.<element>.<instance>.<field>` and every value is **int64**.

Each field declares a **kind**, which governs the arithmetic a consumer may do:

| Kind | Meaning | Consumer may |
|---|---|---|
| `counter` | Cumulative since source creation. Monotonically non-decreasing; never reset on flush or seek | difference it; sum deltas |
| `current` | A live sample, re-read each poll. Absolute | read it; **never sum it** |
| `high_water` | Monotone max since source creation. Absolute | read it; compare it |
| `config` | A tunable's present value. Absolute | read it; write it where `writable` |

**A field a product cannot measure is undeclared**, and is therefore absent from a read — never returned as `0`. "This SoC cannot measure it" and "it measured zero" are different facts and the interface keeps them apart.

**Provider** records the expected source. It is a per-product outcome, not a fixed property of a field: where a driver declares a field its value is used, and where it does not, middleware may serve it if it can observe an equivalent. A consumer cannot tell which, and does not need to.

**A transform normalises representation; it cannot manufacture information.** Where a SoC reports only a combined figure, the finer-grained fields stay undeclared rather than being derived by guesswork — an aggregate drop count must not be split into a guessed late-vs-FRC breakdown.

## Fields

### `av.video_decoder`

| Field | Type · unit · kind | Provider | Event | Definition and population rule |
|---|---|---|---|---|
| `frames_decoded` | int64 · frames · `counter` | **Driver** | — | Compressed frames the decoder has decoded and emitted at its output (post-decode, pre-sink). +1 per emitted frame. Counted from instance creation; never reset on flush/seek. |
| `frames_dropped` | int64 · frames · `counter` | **Driver** | `quality_threshold_crossed` (`metric` = `frames_dropped`) | Frames the decoder discarded **before output** — undecodable (corruption / unsupported) or shed under decode overload. **Excludes** presentation-side drops (Section 3.2). A frame here is not also in `frames_decoded`. |
| `decode_errors` | int64 · events · `counter` | **Driver** | `decode_error` — per occurrence, with stream PTS at detection | Decode-error occurrences (bitstream/NAL parse failure, codec fault). Decoder-internal. A **distinct axis** from `frames_dropped`: an error need not drop a frame, and a drop need not be an error. |
| `decode_latency_sum_us` | int64 · µs · `counter` | **Driver** | — | Running sum of per-frame decode latency = *(decoder emits frame at output)* − *(compressed access unit queued to decoder input)*. Needs the decoder's internal input/output timestamps. Mean = `decode_latency_sum_us / frames_decoded`. |

### `av.video_sink`

| Field | Type · unit · kind | Provider | Event | Definition and population rule |
|---|---|---|---|---|
| `frames_received` | int64 · frames · `counter` | **Driver** | — | Decoded frames received to be presented from the decoder. |
| `frames_presented` | int64 · frames · `counter` | **Driver** | — | Frames handed to display scanout for presentation — one per successful render. |
| `frames_dropped_late` | int64 · frames · `counter` | **Driver** | `quality_threshold_crossed` (`metric` = `frames_dropped`) | Frames dropped because their PTS deadline (vs the render clock) had passed by **> one display frame-interval** at the sink render check — too late to show. Sink render-decision internal. |
| `frames_dropped_frc` | int64 · frames · `counter` | **Driver** | `quality_threshold_crossed` (`metric` = `frames_dropped`) | Frames dropped by **frame-rate conversion** when source rate > display rate (cadence decimation) — *not* because they were late. FRC-internal. |
| `frames_repeated_frc` | int64 · frames · `counter` | **Driver** | `quality_threshold_crossed` (`metric` = `frames_repeated`) | Frames repeated (held > 1 display interval) by **FRC** when source rate < display rate (cadence up-conversion). Normal content cadence — **not** a freeze. FRC-internal. |
| `frames_repeated_missing_frame` | int64 · frames · `counter` | **Driver** | `quality_threshold_crossed` (`metric` = `frames_repeated`) | Frames repeated **to cover a missing next frame** — the sink had no new decoded frame ready at render time (starvation cover). Feeds `freeze_duration_ms`. Sink-internal. |
| `underflowed` | int64 · episodes · `counter` | **Driver** | `underflow` — +1 per episode start; `trigger` classifies the cause | Count of video buffer-underflow **episodes**. +1 at each episode **start** (no frame to present at render time); ends when a new frame is presented. |
| `underflow_duration_ms` | int64 · ms · `counter` | **Driver** | `underflow_end` — `duration_ms` carries the episode period | Cumulative wall-clock time across all video-underflow episodes (Σ of each episode's start→clear). Paired with `underflowed`. An underflow episode manifests on screen as a freeze. |
| `freeze_duration_ms` | int64 · ms · `counter` | **Driver** | — | Cumulative on-screen time the same frame was held due to **repeated-to-cover-missing-frame** (customer-visible freeze) — the time integral of `frames_repeated_missing_frame`. Excludes FRC cadence repeats. Derived from a Driver figure. |
| `freeze_event_count` | int64 · events · `counter` | **Driver** | — | Count of freeze episodes — +1 per episode start. Paired with `freeze_duration_ms`: mean freeze length = `freeze_duration_ms` / `freeze_event_count`. |
| `max_freeze_duration_ms` | int64 · ms · `high_water` | **Driver** | — | Longest single freeze episode observed since instance creation. Monotone non-decreasing high-water mark. |
| `render_latency_sum_us` | int64 · µs · `counter` | **Driver** | — | Running sum of per-frame render latency = *(frame presented to scanout)* − *(frame received at sink input)*. Needs the sink's internal present timestamp. Paired with `frames_presented`. |
| `buffer_depth_ms` | int64 · ms · `current` | **Driver** | — | Buffered decoded media ahead of the present position **now** — Σ presentation-durations of frames queued but not yet presented. Live sample re-read each poll; **not** cumulative. **Warning:** SoC- and use-case-specific. |

### `av.audio_decoder`

| Field | Type · unit · kind | Provider | Event | Definition and population rule |
|---|---|---|---|---|
| `frames_decoded` | int64 · frames · `counter` | **Driver** | — | Audio access units decoded and emitted at the decoder output. +1 per emitted access unit. Counted from instance creation; never reset on flush/seek. |
| `frames_dropped` | int64 · frames · `counter` | **Driver** | — | Audio frames discarded before output (xruns / undecodable). Decoder-internal. Excludes `frames_decoded`. |
| `decode_errors` | int64 · events · `counter` | **Driver** | `decode_error` — per occurrence, with stream PTS at detection | Audio decode-error occurrences (distinct axis from `frames_dropped`, as Section 3.1). Decoder-internal. |
| `decode_latency_sum_us` | int64 · µs · `counter` | **Driver** | — | Σ per-frame audio decode latency *(output-emitted − input-queued)*. Needs decoder-internal timestamps. Paired with `frames_decoded`. |
| `underflow_duration_ms` | int64 · ms · `counter` | **Driver** | `underflow` at episode start; `underflow_end` carrying `duration_ms` | Cumulative time the audio path was starved of decoded data (Σ episode start→clear). |
| `silence_duration_ms` | int64 · ms · `counter` | **Driver** | `silence` — `duration_ms` carries the completed period | Cumulative emitted **digital silence** at or above the HFP-declared threshold (default 500 ms minimum episode). Digital-silence detection is in the audio path. Distinguishes unexpected absence of audio output from starvation (`underflow_duration_ms`). |
| `buffer_depth_ms` | int64 · ms · `current` | **Driver** | — | Buffered decoded audio ahead of the play position now. Live sample; not cumulative. **Warning:** SoC- and use-case-specific. |
| `silence_event_count` | int64 · events · `counter` | **Driver** | `silence` — +1 per completed period | Count of completed digital-silence periods at or above the HFP-declared threshold. Paired with `silence_duration_ms`: mean silence length = `silence_duration_ms` / `silence_event_count`. |

### `av.clock`

| Field | Type · unit · kind | Provider | Event | Definition and population rule |
|---|---|---|---|---|
| `av_sync_offset_ms` | int64 signed · ms · `current` | **Driver** | — | The driver's predicted current audio-vs-video presentation offset. **Sign:** audio leads → **positive**, video leads → **negative**. Live sample, not cumulative. |
| `av_sync_max_abs_offset_ms` | int64 · ms · `high_water` | **Driver** | — | Largest `abs(av_sync_offset_ms)` observed since instance creation. Monotone non-decreasing high-water mark — derived. |
| `av_sync_time_over_threshold_ms` | int64 · ms · `counter` | **Driver** | — | Cumulative time `abs(av_sync_offset_ms)` exceeded the **HFP-declared A/V-sync threshold** — time integral of out-of-sync operation. Derived from the Driver offset. |
| `av_resync_count` | int64 · events · `counter` | **Driver** | — | Count of A/V-sync **corrections** the clock applied — each discrete realignment to re-align audio and video. +1 per applied correction. |
| `av_resync_magnitude_sum_ms` | int64 · ms · `counter` | **Driver** | — | Σ of the **absolute magnitude** (ms) of each resync correction. Clock-internal. Paired with `av_resync_count`: mean correction size = `av_resync_magnitude_sum_ms / av_resync_count`. **Warning:** may not be available from all SoCs. |

### `av.session`

| Field | Type · unit · kind | Provider | Event | Definition and population rule |
|---|---|---|---|---|
| `time_playing_ms` | int64 · ms · `counter` | **Rialto** | — | Cumulative wall-clock time the session spent in `PLAYING`. The denominator every rate and ratio is computed against — without it a consumer cannot turn a drop count into a drop rate. Accumulated by the session state machine. |
| `time_buffering_ms` | int64 · ms · `counter` | **Rialto** | — | Cumulative time the session was stalled awaiting data, as the state machine observed it — distinct from `av.video_sink.underflow_duration_ms`, which is the sink's view of starvation. |
| `preroll_ms` | int64 · ms · `current` | **Rialto** | — | Time from `play()` to the pipeline reaching `PLAYING`, per playback start. With driver-sourced `first_frame_presented` this splits TTFF into the part Rialto owns and the part the hardware owns. |
| `seek_count` | int64 · events · `counter` | **Rialto** | — | Completed seek/flush cycles. The denominator for post-seek recovery figures, and the context that tells a consumer why `first_frame_presented` fired again. |
| `denied_count` | int64 · events · `counter` | **Rialto** | `admission_denied` — carries `event.admission/resource` | `canCreateSession()` calls that returned unsatisfiable. Lets a QoE consumer distinguish **"playback never started"** from **"playback started and then failed"** — two very different customer experiences that are indistinguishable from playback counters alone. |
| `reclaim_count` | int64 · events · `counter` | **Rialto** | — | Times this session's resources were reclaimed for another admitted consumer . Explains an otherwise-inexplicable teardown in a QoE trace. |
| `poll_period_ms` | int64 · ms · `current` | **Rialto** | — | The vendor-poll loop's **actual** most-recent period, against the HFP-declared floor . Declared cadence is an intention; this is the measurement. |
| `poll_overrun_count` | int64 · events · `counter` | **Rialto** | — | Poll cycles that exceeded the declared floor. Direct evidence for or against the ≤50 ms freshness contract. |
| `state_age_ms` | int64 · ms · `current` | **Rialto** | — | Age of the canonical state at the moment this read was served — how stale the numbers in this snapshot are. Lets a consumer reason about freshness instead of assuming it. |
| `events_missed` | int64 · events · `counter` | **Rialto** | — | Ring entries overwritten before **this cursor** read them. Per-cursor, so one slow consumer's loss is never reported to another. Read together with `poll_period_ms` and `state_age_ms` it becomes diagnosable: whether the consumer read too slowly, or the platform failed its cadence. |

## Events

An event is `{seq, tsUnixMs, kind, values[]}`. The **kind is scoped by the source that raised it**, so it carries no media prefix: `underflow` from `av.video_sink` is a video starvation, and the same kind from `av.audio_sink` is an audio one.

An event value is a bare name — the kind already scopes it — and carries a unit only. The `counter` / `current` classification describes behaviour over time, which is meaningless for the payload of a single occurrence.

| Kind | Raised by | Values | Meaning |
|---|---|---|---|
| `underflow` | `video_sink`, `audio_sink` | `trigger` | Starvation began. `trigger` records the context: startup prefill, mid-stream, seek recovery, trickplay recovery, content boundary |
| `underflow_end` | `video_sink`, `audio_sink` | `duration_ms` | Starvation cleared; carries the period it closes |
| `silence` | `audio_sink` | `duration_ms` | A completed digital-silence period at or above the declared threshold |
| `quality_threshold_crossed` | `video_sink` | `metric`, `count`, `pts_ms` | A quality metric crossed its threshold. `metric` says which — only the sink knows whether it shed or repeated |
| `decode_error` | `video_decoder`, `audio_decoder` | `pts_ms`, `code` | A decode error occurred. `code` is the implementation's error code |
| `pts_error` | `video_decoder` | `pts_ms` | A timestamp inconsistency was detected in the stream |
| `first_frame_presented` | `video_sink` | `pts_ms` | The first frame reached presentation — at session start, and again after each seek or flush |

**Not every element raises events.** An A/V clock reports samples and has nothing episodic to report, so it declares no kinds and never fires. An element's declared kinds are in `MetricElementInfo.events`; where that list is empty, registering a listener on it is accepted but permanently idle.

**A value the implementation cannot supply is omitted, not defaulted.** A PTS that cannot be derived is absent from `values[]`, never sent as `-1` — "no PTS available for this drop" and "the PTS is minus one" are different facts.

## Accuracy

| | |
|---|---|
| **Counter accuracy** | Within ±0.2 %. Every drop and every presentation counted — no quiet gaps between samples |
| **Event PTS** | Within ±1 frame interval of the actual event, where a consumer requires exact PTS |
| **Snapshot freshness** | No older than the element's declared `pollCadenceMs`, floor 50 ms |
| **Atomicity** | Every value of one read sampled at a single instant, so paired counters never produce an impossible ratio |

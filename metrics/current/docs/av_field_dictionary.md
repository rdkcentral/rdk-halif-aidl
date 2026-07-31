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

## Field identity

Every field carries an id derived from the contract that governs how it may be read:

```text
id = first 8 bytes of SHA-256("<domain>.<element>.<field>|<unit>|<kind>")
```

Nothing allocates it. There is no registry to consult, no counter to advance and nothing to resolve when two people add a field on separate branches — anyone computes it offline from this document.

It buys a check the name alone cannot make. A product that declares `decode_latency_sum_us` but populates milliseconds still matches by name, and the consumer reports figures a thousand times wrong. A `current` sample reclassified as a `counter` gets differenced and produces nonsense. Both change the id, so a client comparing against the id it was built with sees a hard mismatch instead of a wrong number.

Two rules an allocated id would need policing to hold are properties of this encoding instead: an id is never reused, because the same id means the same name, unit and kind — the same field; and `unit` and `kind` cannot change under a stable id, because changing either produces a different id.

The instance segment is not hashed (`.0` and `.1` are the same field on different sources), nor is `writable` (a per-product permission, not the field's meaning), nor this prose (a typo fix must not churn the id), nor the dictionary revision (every id would churn on every revision).

`scripts/dictionary-ids.py` writes the id into each declaration entry and checks it in CI. Deleting an id regenerates it on the next `--sync`, so a rename or a unit change flows through.

## Fields

### `av.video_decoder`

| Field | Type · unit · kind | Provider | Definition and population rule |
|---|---|---|---|
| `frames_decoded` | int64 · frames · `counter` | **Driver** | Compressed frames the decoder has decoded and emitted at its output (post-decode, pre-sink). +1 per emitted frame. Counted from instance creation; never reset on flush/seek. |
| `frames_dropped` | int64 · frames · `counter` | **Driver** | Frames the decoder discarded **before output** — undecodable (corruption / unsupported) or shed under decode overload. **Excludes** presentation-side drops, which are `av.video_sink`'s. A frame here is not also in `frames_decoded`. |
| `decode_errors` | int64 · events · `counter` | **Driver** | Decode-error occurrences (bitstream/NAL parse failure, codec fault). Decoder-internal. A **distinct axis** from `frames_dropped`: an error need not drop a frame, and a drop need not be an error. |
| `decode_latency_sum_us` | int64 · µs · `counter` | **Driver** | Running sum of per-frame decode latency = *(decoder emits frame at output)* − *(compressed access unit queued to decoder input)*. Needs the decoder's internal input/output timestamps. Mean = `decode_latency_sum_us / frames_decoded`. |
| `last_decode_error_pts_ms` | int64 · ms · `current` | **Driver** | Stream PTS at detection of the **most recent** decode error, within ±1 frame interval. Read with `decode_errors`: the counter says how many, this says where the newest one was. Left undeclared where the SoC cannot derive a PTS — never served as `-1`. |
| `last_decode_error_reason` | int64 · none · `current` | **Driver** | Closed-vocabulary classification of the most recent decode error. This is the value a consumer branches on, and it is what makes the fault comparable across SoCs. |
| `last_decode_error_vendor_code` | int64 · none · `current` | **Driver** | The SoC's own error code for the same fault, carried through uninterpreted. For vendor diagnosis; never branched on. |

### `av.video_sink`

| Field | Type · unit · kind | Provider | Definition and population rule |
|---|---|---|---|
| `frames_received` | int64 · frames · `counter` | **Driver** | Decoded frames received to be presented from the decoder. |
| `frames_presented` | int64 · frames · `counter` | **Driver** | Frames handed to display scanout for presentation — one per successful render. |
| `frames_dropped_late` | int64 · frames · `counter` | **Driver** | Frames dropped because their PTS deadline (vs the render clock) had passed by **> one display frame-interval** at the sink render check — too late to show. Sink render-decision internal. |
| `frames_dropped_frc` | int64 · frames · `counter` | **Driver** | Frames dropped by **frame-rate conversion** when source rate > display rate (cadence decimation) — *not* because they were late. FRC-internal. |
| `frames_repeated_frc` | int64 · frames · `counter` | **Driver** | Frames repeated (held > 1 display interval) by **FRC** when source rate < display rate (cadence up-conversion). Normal content cadence — **not** a freeze. FRC-internal. |
| `frames_repeated_missing_frame` | int64 · frames · `counter` | **Driver** | Frames repeated **to cover a missing next frame** — the sink had no new decoded frame ready at render time (starvation cover). Feeds `freeze_duration_ms`. Sink-internal. |
| `underflowed` | int64 · episodes · `counter` | **Driver** | Count of video buffer-underflow **episodes**. +1 at each episode **start** (no frame to present at render time); ends when a new frame is presented. |
| `underflow_duration_ms` | int64 · ms · `counter` | **Driver** | Cumulative wall-clock time across all video-underflow episodes (Σ of each episode's start→clear). Paired with `underflowed`. An underflow episode manifests on screen as a freeze. |
| `freeze_duration_ms` | int64 · ms · `counter` | **Driver** | Cumulative on-screen time the same frame was held due to **repeated-to-cover-missing-frame** (customer-visible freeze) — the time integral of `frames_repeated_missing_frame`. Excludes FRC cadence repeats. Derived from a Driver figure. |
| `freeze_event_count` | int64 · events · `counter` | **Driver** | Count of freeze episodes — +1 per episode start. Paired with `freeze_duration_ms`: mean freeze length = `freeze_duration_ms` / `freeze_event_count`. |
| `max_freeze_duration_ms` | int64 · ms · `high_water` | **Driver** | Longest single freeze episode observed since instance creation. Monotone non-decreasing high-water mark. |
| `render_latency_sum_us` | int64 · µs · `counter` | **Driver** | Running sum of per-frame render latency = *(frame presented to scanout)* − *(frame received at sink input)*. Needs the sink's internal present timestamp. Paired with `frames_presented`. |
| `buffer_depth_ms` | int64 · ms · `current` | **Driver** | Buffered decoded media ahead of the present position **now** — Σ presentation-durations of frames queued but not yet presented. Live sample re-read each poll; **not** cumulative. **Warning:** SoC- and use-case-specific. |
| `last_underflow_trigger` | int64 · none · `current` | **Driver** | Closed-vocabulary cause of the most recent underflow episode: startup prefill, mid-stream, seek recovery, trickplay recovery, content boundary. Distinguishes an expected starvation from a defect. |
| `last_underflow_duration_ms` | int64 · ms · `current` | **Driver** | Length of the most recent **completed** underflow episode. Read with `underflowed` and `underflow_duration_ms`, which give the count and the total. |
| `last_dropped_frame_pts_ms` | int64 · ms · `current` | **Driver** | Stream PTS of the most recently dropped frame, within ±1 frame interval, whatever the drop axis. Turns a drop count into a locatable defect. Left undeclared where no PTS is derivable. |
| `first_frame_presented_pts_ms` | int64 · ms · `current` | **Driver** | PTS of the first frame to reach presentation — set at session start and re-set after each seek or flush. With `av.session.preroll_ms` this splits time-to-first-frame into the part middleware owns and the part the hardware owns. |

### `av.audio_decoder`

| Field | Type · unit · kind | Provider | Definition and population rule |
|---|---|---|---|
| `frames_decoded` | int64 · frames · `counter` | **Driver** | Audio access units decoded and emitted at the decoder output. +1 per emitted access unit. Counted from instance creation; never reset on flush/seek. |
| `frames_dropped` | int64 · frames · `counter` | **Driver** | Audio frames discarded before output (xruns / undecodable). Decoder-internal. Excludes `frames_decoded`. |
| `decode_errors` | int64 · events · `counter` | **Driver** | Audio decode-error occurrences — a **distinct axis** from `frames_dropped`, exactly as on `av.video_decoder`: an error need not drop a frame, and a drop need not be an error. Decoder-internal. |
| `decode_latency_sum_us` | int64 · µs · `counter` | **Driver** | Σ per-frame audio decode latency *(output-emitted − input-queued)*. Needs decoder-internal timestamps. Paired with `frames_decoded`. |
| `last_decode_error_pts_ms` | int64 · ms · `current` | **Driver** | Stream PTS at detection of the most recent audio decode error, within ±1 frame interval. Read with `decode_errors`. Left undeclared where no PTS is derivable — never served as `-1`. |
| `last_decode_error_reason` | int64 · none · `current` | **Driver** | Closed-vocabulary classification of the most recent audio decode error. The value a consumer branches on. |
| `last_decode_error_vendor_code` | int64 · none · `current` | **Driver** | The SoC's own code for the same fault, carried through uninterpreted. For vendor diagnosis; never branched on. |

### `av.audio_sink`

Audio presentation, distinct from audio decode — as `av.video_sink` is distinct from `av.video_decoder`. Starvation, silence and buffer occupancy are properties of the output path, not of the decoder that feeds it.

| Field | Type · unit · kind | Provider | Definition and population rule |
|---|---|---|---|
| `underflowed` | int64 · episodes · `counter` | **Driver** | Count of audio buffer-underflow **episodes**. +1 at each episode start (no decoded audio to present); ends when output resumes. Counterpart of `av.video_sink.underflowed` — without it an audio underflow rate cannot be computed at all. |
| `underflow_duration_ms` | int64 · ms · `counter` | **Driver** | Cumulative time the audio path was starved of decoded data (Σ of each episode start→clear). Paired with `underflowed`: mean episode length = `underflow_duration_ms` / `underflowed`. |
| `silence_duration_ms` | int64 · ms · `counter` | **Driver** | Cumulative emitted **digital silence** at or above the HFP-declared threshold (default 500 ms minimum episode). Digital-silence detection is in the audio path. Distinguishes unexpected absence of audio output from starvation (`underflow_duration_ms`). |
| `silence_event_count` | int64 · events · `counter` | **Driver** | Count of completed digital-silence periods at or above the HFP-declared threshold. Paired with `silence_duration_ms`: mean silence length = `silence_duration_ms` / `silence_event_count`. |
| `buffer_depth_ms` | int64 · ms · `current` | **Driver** | Buffered decoded audio ahead of the play position **now**. Live sample re-read each poll; **not** cumulative. **Warning:** SoC- and use-case-specific. |
| `last_underflow_trigger` | int64 · none · `current` | **Driver** | Closed-vocabulary cause of the most recent audio underflow episode, same vocabulary as `av.video_sink.last_underflow_trigger`. |
| `last_underflow_duration_ms` | int64 · ms · `current` | **Driver** | Length of the most recent **completed** audio underflow episode. Read with `underflowed` and `underflow_duration_ms`, which give the count and the total. |
| `last_silence_duration_ms` | int64 · ms · `current` | **Driver** | Length of the most recent completed digital-silence period. Read with `silence_event_count` and `silence_duration_ms`. |

### `av.clock`

Leaf names carry no `av_` prefix — the element already says `av.clock`, and no other element repeats its own context in the leaf.

| Field | Type · unit · kind | Provider | Definition and population rule |
|---|---|---|---|
| `sync_offset_ms` | int64 signed · ms · `current` | **Driver** | The driver's predicted current audio-vs-video presentation offset. **Sign:** audio leads → **positive**, video leads → **negative**. Live sample, not cumulative. |
| `sync_max_abs_offset_ms` | int64 · ms · `high_water` | **Driver** | Largest `abs(sync_offset_ms)` observed since instance creation. Monotone non-decreasing high-water mark — derived from `sync_offset_ms`. |
| `sync_time_over_threshold_ms` | int64 · ms · `counter` | **Driver** | Cumulative time `abs(sync_offset_ms)` exceeded `sync_threshold_ms` — the time integral of out-of-sync operation. Derived from `sync_offset_ms` and `sync_threshold_ms`. |
| `sync_threshold_ms` | int64 · ms · `config` · **writable** | **Driver** | The offset magnitude beyond which playback counts as out of sync. The threshold `sync_time_over_threshold_ms` integrates against and `sync_max_abs_offset_ms` is judged by — declaring those two without this leaves both uninterpretable. Writable so an integrator can tighten it per product. |
| `resync_count` | int64 · events · `counter` | **Driver** | Count of A/V-sync **corrections** the clock applied — each discrete realignment to re-align audio and video. +1 per applied correction. |
| `resync_magnitude_sum_ms` | int64 · ms · `counter` | **Driver** | Σ of the **absolute magnitude** (ms) of each resync correction. Clock-internal. Paired with `resync_count`: mean correction size = `resync_magnitude_sum_ms / resync_count`. |

### `av.session`

| Field | Type · unit · kind | Provider | Definition and population rule |
|---|---|---|---|
| `time_playing_ms` | int64 · ms · `counter` | **Middleware** | Cumulative wall-clock time the session spent in `PLAYING`. The denominator every rate and ratio is computed against — without it a consumer cannot turn a drop count into a drop rate. Accumulated by the session state machine. |
| `time_buffering_ms` | int64 · ms · `counter` | **Middleware** | Cumulative time the session was stalled awaiting data, as the state machine observed it — distinct from `av.video_sink.underflow_duration_ms`, which is the sink's view of starvation. |
| `preroll_ms` | int64 · ms · `current` | **Middleware** | Time from `play()` to the pipeline reaching `PLAYING`, per playback start. With the driver-sourced `av.video_sink.first_frame_presented_pts_ms` this splits time-to-first-frame into the part middleware owns and the part the hardware owns. |
| `seek_count` | int64 · events · `counter` | **Middleware** | Completed seek/flush cycles. The denominator for post-seek recovery figures, and the context that explains why first-frame timing was re-set. |

### `av.admission`

Whether a session was allowed to exist at all. Separate from `av.session`, which describes a session that does — these figures are the record of the ones that did not, and a session element cannot carry them because there is no session to carry them.

| Field | Type · unit · kind | Provider | Definition and population rule |
|---|---|---|---|
| `denied_count` | int64 · events · `counter` | **Middleware** | Session-creation requests refused as unsatisfiable. Lets a consumer distinguish **"playback never started"** from **"playback started and then failed"** — two very different customer experiences, indistinguishable from playback counters alone. |
| `reclaim_count` | int64 · events · `counter` | **Middleware** | Times a session's resources were reclaimed for another admitted consumer. Explains an otherwise inexplicable teardown. |

## `health` domain

Not an `av` element — a separate domain, because an A/V dictionary cannot define how a poll loop is behaving, and because it is declared **per declaring party**. Each party that runs a poll loop declares its own, so "are these numbers fresh?" is answerable per source of numbers rather than as one device-wide figure that averages away the loop actually struggling.

### `health.poll`

| Field | Type · unit · kind | Provider | Definition and population rule |
|---|---|---|---|
| `poll_period_ms` | int64 · ms · `current` | **Declaring party** | The poll loop's **actual** most-recent period, against the declared cadence floor. A declared cadence is an intention; this is the measurement. |
| `poll_overrun_count` | int64 · events · `counter` | **Declaring party** | Poll cycles that exceeded the declared floor. Direct evidence for or against the ≤50 ms freshness contract. |
| `state_age_ms` | int64 · ms · `current` | **Declaring party** | Age of the canonical state at the moment this read was served — how stale the numbers in this snapshot are. Lets a consumer reason about freshness instead of assuming it. |

## Episodic Conditions

Underflows, decode errors, silence periods and first-frame timing happen at an instant rather than describing a level. Each is reported in two parts, both ordinary fields arriving in the same snapshot as everything else:

| Part | Kind | Answers |
|---|---|---|
| `underflowed`, `decode_errors`, `freeze_event_count`, `silence_event_count` | `counter` | How many have occurred |
| `last_underflow_duration_ms`, `last_decode_error_pts_ms`, `last_decode_error_reason`, … | `current` | What the most recent one was |

A counter that advanced between two polls is what makes the occurrence visible; the `last_*` fields are what make it diagnosable. Because both arrive in one `getAll()` snapshot, an occurrence and the counters around it are always mutually consistent.

**What this trades.** Several occurrences inside one poll interval advance the counter by several and leave the `last_*` fields describing the newest only. Rates and totals stay exact; the intermediate occurrences of a burst are not individually described. That is the deliberate cost of holding no per-source retention, sequence numbering or cursor state in the vendor implementation.

**Not every element has episodic conditions.** An A/V clock reports samples and has nothing episodic to report, so it declares no `last_*` fields. Absence from the declaration is the answer — there is nothing to subscribe to and nothing to poll for.

**A value the implementation cannot supply is left undeclared, not defaulted.** A PTS that cannot be derived is absent from the declaration, never served as `-1` — "no PTS available for this drop" and "the PTS is minus one" are different facts.

## Retired

A field is retired here rather than deleted, so a later author cannot resurrect the name with different semantics without seeing that it once meant something else. Retiring is a deliberate act with a diff.

| Field | Retired | Reason |
|---|---|---|
| — | — | Nothing retired yet. |

Because ids are content-derived, a retired name reused with the same unit and kind resolves to the same id and **is** the same field. Reused with a different unit or kind it resolves to a different id, so no consumer can mistake one for the other.

## Accuracy

| | |
|---|---|
| **Counter accuracy** | Within ±0.2 %. Every drop and every presentation counted — no quiet gaps between samples |
| **Occurrence PTS** | A `*_pts_ms` field within ±1 frame interval of the occurrence it describes, where a consumer requires exact PTS |
| **Snapshot freshness** | No older than the element's declared `pollCadenceMs`, floor 50 ms |
| **Atomicity** | Every value of one read sampled at a single instant, so paired counters never produce an impossible ratio |

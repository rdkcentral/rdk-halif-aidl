# AV Domain Field Dictionary

The normative field set for the **`av` domain** of `com.rdk.hal.metrics`. A name means the same thing on every product that declares it; this document is what it means.

A declaration (`hfp-metrics.yaml`) states *which* of these a product serves. This dictionary states *what each one is*. A product may not declare a name that is not defined here, and may not redefine one that is — that is what keeps the interface common across SoCs, and it is why there is no SoC-private namespace.

## What a declared field must do

This dictionary is what `HAL.METRICS.15` asserts against: a declared field's values behave as its `kind` states and carry the meaning its definition below gives.

A product is held to that only for the fields it declares in `hfp-metrics.yaml`. A field it does not declare is absent at runtime rather than served as zero — "this SoC cannot measure it" and "it measured zero" stay distinct.

The four kinds:

| `kind` | Values shall be |
|---|---|
| `counter` | cumulative since source creation, monotonically non-decreasing, and never reset on flush or seek |
| `current` | a live sample re-read each poll, absolute, and never summed |
| `high_water` | a monotone maximum since source creation, absolute |
| `config` | the present value of a tunable, absolute |

A field marked **writable** additionally accepts `setField()`; every other field rejects it.

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

`scripts/generate.py` writes the id into each declaration entry and checks it. Deleting an id restores it on the next run, so a rename or a unit change flows through.

<!-- Field tables: GENERATED from hfp-metrics.yaml by scripts/generate.py. Do not hand-edit. -->

## Versions

The dictionary revision pins the set of names; a field's `id` pins its unit and kind. Cite both when stating what a device was asked to serve.

| | Version |
|---|---|
| `av` dictionary | 1.2 |
| Interface | 0.1.0.0 |
| Schema | 0.1.0 |

## Fields

### `av.video_decoder`

| Field | Type · unit · kind | Provider | id | Definition and population rule |
|---|---|---|---|---|
| `frames_decoded` | int64 · frames · `counter` | **Driver** | `0x63c81c7efbe7e743` | Compressed frames the decoder has decoded and emitted at its output (post-decode, pre-sink). +1 per emitted frame. Counted from instance creation; never reset on flush/seek. |
| `frames_dropped` | int64 · frames · `counter` | **Driver** | `0x2c67d98cc76e6fb7` | Frames the decoder discarded **before output** — undecodable (corruption / unsupported) or shed under decode overload. **Excludes** presentation-side drops, which are `av.video_sink`'s. A frame here is not also in `frames_decoded`. |
| `decode_errors` | int64 · events · `counter` | **Driver** | `0x070bb5fa11ef497b` | Decode-error occurrences (bitstream/NAL parse failure, codec fault). Decoder-internal. A **distinct axis** from `frames_dropped`: an error need not drop a frame, and a drop need not be an error. |
| `decode_latency_sum_us` | int64 · us · `counter` | **Driver** | `0x4e69bac967d540b7` | Running sum of per-frame decode latency = *(decoder emits frame at output)* − *(compressed access unit queued to decoder input)*. Needs the decoder's internal input/output timestamps. Mean = `decode_latency_sum_us / frames_decoded`. |
| `last_decode_error_pts_ms` | int64 · ms · `current` | **Driver** | `0x14debdd0bbd63a14` | Stream PTS at detection of the **most recent** decode error, within ±1 frame interval. Read with `decode_errors`: the counter says how many, this says where the newest one was. Left undeclared where the SoC cannot derive a PTS — never served as `-1`. |
| `last_decode_error_reason` | int64 · none · `current` | **Driver** | `0x4fda2a3cf3d7dc09` | Closed-vocabulary classification of the most recent decode error. This is the value a consumer branches on, and it is what makes the fault comparable across SoCs. |
| `last_decode_error_vendor_code` | int64 · none · `current` | **Driver** | `0x26d18e085c02dfd4` | The SoC's own error code for the same fault, carried through uninterpreted. For vendor diagnosis; never branched on. |

### `av.video_sink`

| Field | Type · unit · kind | Provider | id | Definition and population rule |
|---|---|---|---|---|
| `frames_received` | int64 · frames · `counter` | **Driver** | `0x524c81ef37d81082` | Decoded frames received to be presented from the decoder. |
| `frames_presented` | int64 · frames · `counter` | **Driver** | `0x7f36b75533d5db3a` | Frames handed to display scanout for presentation — one per successful render. |
| `frames_dropped_late` | int64 · frames · `counter` | **Driver** | `0x7682bfb371ecc4d5` | Frames dropped because their PTS deadline (vs the render clock) had passed by **> one display frame-interval** at the sink render check — too late to show. Sink render-decision internal. |
| `frames_dropped_frc` | int64 · frames · `counter` | **Driver** | `0x6c43fb5584823d18` | Frames dropped by **frame-rate conversion** when source rate > display rate (cadence decimation) — *not* because they were late. FRC-internal. |
| `frames_repeated_frc` | int64 · frames · `counter` | **Driver** | `0x72b9db4bfce6f2ab` | Frames repeated (held > 1 display interval) by **FRC** when source rate < display rate (cadence up-conversion). Normal content cadence — **not** a freeze. FRC-internal. |
| `frames_repeated_missing_frame` | int64 · frames · `counter` | **Driver** | `0x5a652c2dcf72deac` | Frames repeated **to cover a missing next frame** — the sink had no new decoded frame ready at render time (starvation cover). Feeds `freeze_duration_ms`. Sink-internal. |
| `underflowed` | int64 · episodes · `counter` | **Driver** | `0x6804c05ae6533181` | Count of video buffer-underflow **episodes**. +1 at each episode **start** (no frame to present at render time); ends when a new frame is presented. |
| `underflow_duration_ms` | int64 · ms · `counter` | **Driver** | `0x23e55a88f5bbbd94` | Cumulative wall-clock time across all video-underflow episodes (Σ of each episode's start→clear). Paired with `underflowed`. An underflow episode manifests on screen as a freeze. |
| `freeze_duration_ms` | int64 · ms · `counter` | **Driver** | `0x1c86c5dfa4db5108` | Cumulative on-screen time the same frame was held due to **repeated-to-cover-missing-frame** (customer-visible freeze) — the time integral of `frames_repeated_missing_frame`. Excludes FRC cadence repeats. Derived from a Driver figure. |
| `freeze_event_count` | int64 · events · `counter` | **Driver** | `0x5196f6826e91a801` | Count of freeze episodes — +1 per episode start. Paired with `freeze_duration_ms`: mean freeze length = `freeze_duration_ms` / `freeze_event_count`. |
| `max_freeze_duration_ms` | int64 · ms · `high_water` | **Driver** | `0x088d619c00c1c539` | Longest single freeze episode observed since instance creation. Monotone non-decreasing high-water mark. |
| `render_latency_sum_us` | int64 · us · `counter` | **Driver** | `0x75f862796424b00d` | Running sum of per-frame render latency = *(frame presented to scanout)* − *(frame received at sink input)*. Needs the sink's internal present timestamp. Paired with `frames_presented`. |
| `buffer_depth_ms` | int64 · ms · `current` | **Driver** | `0x111d82c20cb9e693` | Buffered decoded media ahead of the present position **now** — Σ presentation-durations of frames queued but not yet presented. Live sample re-read each poll; **not** cumulative. **Warning:** SoC- and use-case-specific. |
| `last_underflow_trigger` | int64 · none · `current` | **Driver** | `0x03210d8159685756` | Closed-vocabulary cause of the most recent underflow episode: startup prefill, mid-stream, seek recovery, trickplay recovery, content boundary. Distinguishes an expected starvation from a defect. |
| `last_underflow_duration_ms` | int64 · ms · `current` | **Driver** | `0x7b1ed4a908e8ef1b` | Length of the most recent **completed** underflow episode. Read with `underflowed` and `underflow_duration_ms`, which give the count and the total. |
| `last_dropped_frame_pts_ms` | int64 · ms · `current` | **Driver** | `0x0e6d081eed2918dd` | Stream PTS of the most recently dropped frame, within ±1 frame interval, whatever the drop axis. Turns a drop count into a locatable defect. Left undeclared where no PTS is derivable. |
| `last_freeze_pts_ms` | int64 · ms · `current` | **Driver** | `0x42cfffc003874fd4` | Stream PTS at which the most recent freeze episode began, within ±1 frame interval. Does the same for a freeze as `last_dropped_frame_pts_ms` does for a drop — turns a count into a locatable defect. Left undeclared where no PTS is derivable. |
| `last_freeze_duration_ms` | int64 · ms · `current` | **Driver** | `0x3e53a4af6a16f1ce` | Length of the most recent **completed** freeze episode. Read with `freeze_event_count` and `freeze_duration_ms`, which give the count and the total, and with `max_freeze_duration_ms`, which gives the worst. |
| `first_frame_presented_pts_ms` | int64 · ms · `current` | **Driver** | `0x56eaeb10709bcdd8` | PTS of the first frame to reach presentation — set at session start and re-set after each seek or flush. This is the hardware's contribution to time-to-first-frame; whatever elapsed above the HAL before decode began is observed by the party that started the session. |

### `av.audio_decoder`

| Field | Type · unit · kind | Provider | id | Definition and population rule |
|---|---|---|---|---|
| `frames_decoded` | int64 · frames · `counter` | **Driver** | `0x23c94a86f7865005` | Audio access units decoded and emitted at the decoder output. +1 per emitted access unit. Counted from instance creation; never reset on flush/seek. |
| `frames_dropped` | int64 · frames · `counter` | **Driver** | `0x748c7fd20b15139d` | Audio frames discarded before output (xruns / undecodable). Decoder-internal. Excludes `frames_decoded`. |
| `decode_errors` | int64 · events · `counter` | **Driver** | `0x577de621243f5a94` | Audio decode-error occurrences — a **distinct axis** from `frames_dropped`, exactly as on `av.video_decoder`: an error need not drop a frame, and a drop need not be an error. Decoder-internal. |
| `decode_latency_sum_us` | int64 · us · `counter` | **Driver** | `0x1b3e9a9b42d47872` | Σ per-frame audio decode latency *(output-emitted − input-queued)*. Needs decoder-internal timestamps. Paired with `frames_decoded`. |
| `last_decode_error_pts_ms` | int64 · ms · `current` | **Driver** | `0x5d4a1b8bfa10cbbe` | Stream PTS at detection of the most recent audio decode error, within ±1 frame interval. Read with `decode_errors`. Left undeclared where no PTS is derivable — never served as `-1`. |
| `last_decode_error_reason` | int64 · none · `current` | **Driver** | `0x10596fb80be50427` | Closed-vocabulary classification of the most recent audio decode error. The value a consumer branches on. |
| `last_decode_error_vendor_code` | int64 · none · `current` | **Driver** | `0x7129e447242c26d5` | The SoC's own code for the same fault, carried through uninterpreted. For vendor diagnosis; never branched on. |

### `av.audio_sink`

| Field | Type · unit · kind | Provider | id | Definition and population rule |
|---|---|---|---|---|
| `underflowed` | int64 · episodes · `counter` | **Driver** | `0x142f899619c8c4a9` | Count of audio buffer-underflow **episodes**. +1 at each episode start (no decoded audio to present); ends when output resumes. Counterpart of `av.video_sink.underflowed` — without it an audio underflow rate cannot be computed at all. |
| `underflow_duration_ms` | int64 · ms · `counter` | **Driver** | `0x4ce68288bc2f93b2` | Cumulative time the audio path was starved of decoded data (Σ of each episode start→clear). Paired with `underflowed`: mean episode length = `underflow_duration_ms` / `underflowed`. |
| `silence_duration_ms` | int64 · ms · `counter` | **Driver** | `0x09fdcdf6715ef048` | Cumulative emitted **digital silence** at or above the HFP-declared threshold (default 500 ms minimum episode). Digital-silence detection is in the audio path. Distinguishes unexpected absence of audio output from starvation (`underflow_duration_ms`). |
| `silence_event_count` | int64 · events · `counter` | **Driver** | `0x357a57be2601412e` | Count of completed digital-silence periods at or above the HFP-declared threshold. Paired with `silence_duration_ms`: mean silence length = `silence_duration_ms` / `silence_event_count`. |
| `buffer_depth_ms` | int64 · ms · `current` | **Driver** | `0x1aea4fc8a27262b7` | Buffered decoded audio ahead of the play position **now**. Live sample re-read each poll; **not** cumulative. **Warning:** SoC- and use-case-specific. |
| `last_underflow_trigger` | int64 · none · `current` | **Driver** | `0x40771a4a2b2ee087` | Closed-vocabulary cause of the most recent audio underflow episode, same vocabulary as `av.video_sink.last_underflow_trigger`. |
| `last_underflow_duration_ms` | int64 · ms · `current` | **Driver** | `0x638f410fc657c525` | Length of the most recent **completed** audio underflow episode. Read with `underflowed` and `underflow_duration_ms`, which give the count and the total. |
| `last_silence_duration_ms` | int64 · ms · `current` | **Driver** | `0x1cf88c9352312e83` | Length of the most recent completed digital-silence period. Read with `silence_event_count` and `silence_duration_ms`. |

### `av.clock`

| Field | Type · unit · kind | Provider | id | Definition and population rule |
|---|---|---|---|---|
| `sync_offset_ms` | int64 · ms · `current` | **Driver** | `0x0853e5868c5f2bd8` | The driver's predicted current audio-vs-video presentation offset. **Sign:** audio leads → **positive**, video leads → **negative**. Live sample, not cumulative. |
| `sync_max_abs_offset_ms` | int64 · ms · `high_water` | **Driver** | `0x20d08f573aeb1229` | Largest `abs(sync_offset_ms)` observed since instance creation. Monotone non-decreasing high-water mark — derived from `sync_offset_ms`. |
| `sync_time_over_threshold_ms` | int64 · ms · `counter` | **Driver** | `0x323c3766c9e3638c` | Cumulative time `abs(sync_offset_ms)` exceeded `sync_threshold_ms` — the time integral of out-of-sync operation. Derived from `sync_offset_ms` and `sync_threshold_ms`. |
| `sync_threshold_ms` | int64 · ms · `config` · **writable** | **Driver** | `0x4c981a6fd5bbf977` | The offset magnitude beyond which playback counts as out of sync. The threshold `sync_time_over_threshold_ms` integrates against and `sync_max_abs_offset_ms` is judged by — declaring those two without this leaves both uninterpretable. Writable so an integrator can tighten it per product. |
| `resync_count` | int64 · events · `counter` | **Driver** | `0x1e11b09c212e1a59` | Count of A/V-sync **corrections** the clock applied — each discrete realignment to re-align audio and video. +1 per applied correction. |
| `resync_magnitude_sum_ms` | int64 · ms · `counter` | **Driver** | `0x7be51ba179aa2379` | Σ of the **absolute magnitude** (ms) of each resync correction. Clock-internal. Paired with `resync_count`: mean correction size = `resync_magnitude_sum_ms / resync_count`. |

### `av.drm`

| Field | Type · unit · kind | Provider | id | Definition and population rule |
|---|---|---|---|---|
| `decrypt_count` | int64 · operations · `counter` | **Driver** | `0x01c6bee68b39b413` | Decrypt operations completed, summed across the key sessions this media session holds. The denominator for mean decrypt latency. |
| `decrypt_errors` | int64 · events · `counter` | **Driver** | `0x5db0ea33fec21035` | Decrypt operations that failed on a key already held. Distinct from a licence that was never obtained, which is not vendor-observable. |
| `decrypt_latency_sum_us` | int64 · us · `counter` | **Driver** | `0x6663f481e5048044` | Σ of decrypt operation latency. Paired with `decrypt_count`: mean decrypt latency = `decrypt_latency_sum_us` / `decrypt_count`. |

## Episodic Conditions

An underflow, a freeze, a decode error, a silence period and a first frame happen at an instant rather than describing a level. Each is reported as ordinary fields arriving in the same snapshot as everything else: **counters** say how many have occurred, **`last_*` fields** say what the most recent one was.

A counter that advanced between two polls is what makes the occurrence visible; the `last_*` fields are what make it diagnosable. Because both arrive in one `getAll()` snapshot, an occurrence and the counters around it are always mutually consistent.

The tables below are the implementation checklist. For each occurrence: every field it moves, and the instant it moves. A field is written at the instant stated and not re-derived at poll time.

### Underflow — `av.video_sink`, `av.audio_sink`

Starts when there is nothing to present at render time. Ends when presentation resumes.

| Field | Kind | Written |
|---|---|---|
| `underflowed` | `counter` | **+1 at episode start** |
| `last_underflow_trigger` | `current` | **at episode start** — why it began, from the closed vocabulary |
| `underflow_duration_ms` | `counter` | **+= this episode's length, at episode end** |
| `last_underflow_duration_ms` | `current` | **= this episode's length, at episode end** |

An episode in progress has already moved `underflowed` and `last_underflow_trigger`; it has not yet moved either duration. A consumer seeing the count advance with the total unchanged is reading a live episode, which is the intended signal rather than a gap.

### Freeze — `av.video_sink`

The same frame held on screen because no new one was ready. Distinct from underflow: an underflow is the buffer state, a freeze is what the viewer sees.

| Field | Kind | Written |
|---|---|---|
| `frames_repeated_missing_frame` | `counter` | **+1 per repeated frame**, throughout the episode |
| `freeze_event_count` | `counter` | **+1 at episode start** |
| `last_freeze_pts_ms` | `current` | **at episode start** — stream PTS where it began |
| `freeze_duration_ms` | `counter` | **+= this episode's length, at episode end** |
| `last_freeze_duration_ms` | `current` | **= this episode's length, at episode end** |
| `max_freeze_duration_ms` | `high_water` | **at episode end**, if this episode was the longest so far |

FRC cadence repeats are **not** a freeze. `frames_repeated_frc` counts those separately and moves none of the fields above — repeating a frame to convert 24 fps to a 60 Hz display is correct behaviour, not a defect.

### Decode error — `av.video_decoder`, `av.audio_decoder`

| Field | Kind | Written |
|---|---|---|
| `decode_errors` | `counter` | **+1 at detection** |
| `last_decode_error_pts_ms` | `current` | **at detection** — stream PTS of the fault |
| `last_decode_error_reason` | `current` | **at detection** — the closed-vocabulary class a consumer branches on |
| `last_decode_error_vendor_code` | `current` | **at detection** — the SoC's own code, uninterpreted |

An error is a point occurrence, so all four are written together and there is no end instant. A decode error need not drop a frame and a dropped frame need not be an error: `decode_errors` and `frames_dropped` are separate axes and an implementation moves each on its own trigger.

### Dropped frame — `av.video_sink`

| Field | Kind | Written |
|---|---|---|
| `frames_dropped_late` | `counter` | **+1** when a frame missed its deadline by more than one display interval |
| `frames_dropped_frc` | `counter` | **+1** when frame-rate conversion decimated a frame |
| `last_dropped_frame_pts_ms` | `current` | **at either drop above** — stream PTS of the frame dropped |

`last_dropped_frame_pts_ms` covers both drop axes. Which axis dropped it is answered by whichever counter advanced.

### Digital silence — `av.audio_sink`

A period of emitted digital silence at or above the declared threshold. Counted only once complete, since the threshold cannot be tested until the period ends.

| Field | Kind | Written |
|---|---|---|
| `silence_event_count` | `counter` | **+1 at period end**, if it met the threshold |
| `silence_duration_ms` | `counter` | **+= the period's length, at period end** |
| `last_silence_duration_ms` | `current` | **= the period's length, at period end** |

### First frame — `av.video_sink`

| Field | Kind | Written |
|---|---|---|
| `first_frame_presented_pts_ms` | `current` | **when the first frame reaches presentation** — at session start, and again after each seek or flush |

Not an episode and has no counter: it is re-set each time playback restarts, so a consumer reads the current session's value rather than a history.

### What this trades

Several occurrences inside one poll interval advance the counter by several and leave the `last_*` fields describing the newest only. Rates and totals stay exact; the intermediate occurrences of a burst are not individually described. That is the deliberate cost of holding no per-source retention, sequence numbering or cursor state in the vendor implementation.

**Not every element has episodic conditions.** An A/V clock reports samples and has nothing episodic to report, so it declares no `last_*` fields. Absence from the declaration is the answer.

**A value the implementation cannot supply is left undeclared, not defaulted.** A PTS that cannot be derived is absent from the declaration, never served as `-1` — "no PTS available for this drop" and "the PTS is minus one" are different facts.

## Accuracy

| | |
|---|---|
| **Counter accuracy** | Within ±0.2 %. Every drop and every presentation counted — no quiet gaps between samples |
| **Occurrence PTS** | A `*_pts_ms` field within ±1 frame interval of the occurrence it describes, where a consumer requires exact PTS |
| **Snapshot freshness** | No older than the element's declared `pollCadenceMs`, floor 50 ms |
| **Atomicity** | Every value of one read sampled at a single instant, so paired counters never produce an impossible ratio |

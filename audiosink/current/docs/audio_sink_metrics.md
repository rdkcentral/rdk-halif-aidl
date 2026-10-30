# Audio Sink Metrics

The figures `audiosink` serves through `getMetrics()` and raises through `onMetricEvent()`. Each figure is a member of the component's `Metric` enum, and each occurrence a member of `MetricEventKind`.

|||
|-|-|
|**Element**|`MetricElement::AUDIO_SINK`|
|**Instances**|1|

## Figures

| Member | Unit | Kind | Access | Definition |
|---|---|---|---|---|
| `UNDERFLOWED` | episodes | counter | read | Count of audio buffer-underflow episodes, one per episode start, where an episode starts when there is no decoded audio to present and ends when output resumes. The counterpart of `videosink`'s `UNDERFLOWED` — without it an audio underflow rate cannot be computed at all. |
| `UNDERFLOW_DURATION_MS` | ms | counter | read | Cumulative time the audio path was starved of decoded data. Paired with underflowed, so the mean episode length is this divided by that. |
| `SILENCE_DURATION_MS` | ms | counter | read | Cumulative emitted digital silence, counting only periods that reached SILENCE_THRESHOLD_MS. Distinguishes an unexpected absence of audio output from starvation, which is UNDERFLOW_DURATION_MS. |
| `SILENCE_EVENT_COUNT` | events | counter | read | Count of completed digital-silence periods that reached SILENCE_THRESHOLD_MS. Paired with SILENCE_DURATION_MS, so the mean silence length is that divided by this. |
| `BUFFER_DEPTH_MS` | ms | current | read | Buffered decoded audio ahead of the play position now. A live sample re-read each capture rather than a cumulative figure. This is SoC- and use-case-specific, so compare it against itself over time rather than across products. |
| `LAST_UNDERFLOW_TRIGGER` | none | current | read | Cause of the most recent audio underflow episode, with the same values as `videosink`'s `LAST_UNDERFLOW_TRIGGER`. |
| `LAST_UNDERFLOW_DURATION_MS` | ms | current | read | Length of the most recent completed audio underflow episode. Read with underflowed and UNDERFLOW_DURATION_MS, which give the count and the total. |
| `LAST_SILENCE_DURATION_MS` | ms | current | read | Length of the most recent completed digital-silence period. Read with SILENCE_EVENT_COUNT and SILENCE_DURATION_MS. |
| `SILENCE_THRESHOLD_MS` | ms | config | read | Shortest digital-silence period that counts as one. Silence is normal output — a gap between programmes, a muted stream, a silent passage — so this is the line between that and a fault worth reporting. Default 500 ms, and set by product configuration rather than over this interface. Reading it is what the key is for: SILENCE_DURATION_MS and SILENCE_EVENT_COUNT count only periods that reached it, so neither is interpretable without it. |

**`last_underflow_trigger` takes a `MetricUnderflowTrigger` value**

| Name | Value | Meaning |
|---|---|---|
| `NONE` | 0 | No underflow episode has been recorded. |
| `STARTUP_PREFILL` | 1 | The pipeline had not yet filled at the start of presentation. Expected. |
| `MID_STREAM` | 2 | Starvation during steady-state playback, with no seek, trickplay or content boundary to explain it. This is the one that indicates a defect. |
| `SEEK_RECOVERY` | 3 | The pipeline was refilling after a seek. Expected. |
| `TRICKPLAY_RECOVERY` | 4 | The pipeline was refilling after a trickplay rate change. Expected. |
| `CONTENT_BOUNDARY` | 5 | The stream crossed a discontinuity such as a period or advert boundary. Expected. |

## Events

### `UNDERFLOW`

Raised at the START of a starvation episode, the instant there is nothing to present at render time. Exactly one UNDERFLOW_END closes it.

| Member | Unit | Definition |
|---|---|---|
| `UNDERFLOW_TRIGGER` | none | What caused this episode, which is what distinguishes an expected starvation from a defect. |

`trigger` takes a `MetricUnderflowTrigger` value, listed above.

### `UNDERFLOW_END`

Raised when presentation resumes, closing the episode the preceding underflow opened.

| Member | Unit | Kind | Definition |
|---|---|---|---|
| `UNDERFLOW_END_DURATION_MS` | ms | current | Length of the episode this closes, from start to resume. Not cumulative — UNDERFLOW_DURATION_MS carries the running total. |

### `SILENCE`

Raised when digital silence has continued for SILENCE_THRESHOLD_MS, NOT when it began. Silence is ordinary output, so the threshold is what separates a gap between programmes from a fault, and below it nothing is raised. Raising at the crossing rather than at the close is what makes a silence that is still going reportable while it is still going.

| Member | Unit | Kind | Definition |
|---|---|---|---|
| `SILENCE_ELAPSED_MS` | ms | current | Silence already elapsed at the crossing, which is SILENCE_THRESHOLD_MS within one detection interval. Present so a consumer need not assume the threshold it was configured with is the one in force. |

### `SILENCE_END`

Raised when audio resumes, closing the period the preceding silence opened. A period that never crossed the threshold raises neither.

| Member | Unit | Kind | Definition |
|---|---|---|---|
| `SILENCE_END_DURATION_MS` | ms | current | Length of the whole period this closes, from the onset of silence rather than from the crossing. Not cumulative — SILENCE_DURATION_MS carries the running total. |

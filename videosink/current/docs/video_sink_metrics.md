# Video Sink Metrics

The figures `videosink` serves through `getMetrics()` and raises through `onMetricEvent()`. Each figure is a member of the component's `Metric` enum, and each occurrence a member of `MetricEventKind`.

|||
|-|-|
|**Element**|`MetricElement::VIDEO_SINK`|
|**Instances**|2|

## Figures

| Member | Unit | Kind | Access | Definition |
|---|---|---|---|---|
| `FRAMES_RECEIVED` | frames | counter | read | Decoded frames received from the decoder to be presented. |
| `FRAMES_PRESENTED` | frames | counter | read | Frames handed to display scanout for presentation, one per successful render. |
| `FRAMES_DROPPED_LATE` | frames | counter | read | Frames dropped because their PTS deadline against the render clock had passed by more than one display frame interval at the sink render check — too late to show. Sink render-decision internal. |
| `FRAMES_DROPPED_FRC` | frames | counter | read | Frames dropped by frame-rate conversion when the source rate exceeds the display rate, which is cadence decimation rather than lateness. |
| `FRAMES_REPEATED_FRC` | frames | counter | read | Frames held for more than one display interval by frame-rate conversion when the source rate is below the display rate. Normal content cadence, and not a freeze. |
| `FRAMES_REPEATED_MISSING_FRAME` | frames | counter | read | Frames repeated to cover a missing next frame — the sink had no new decoded frame ready at render time. This is starvation cover, and it is what FREEZE_DURATION_MS integrates. |
| `UNDERFLOWED` | episodes | counter | read | Count of video buffer-underflow episodes. One per episode start, where an episode starts when there is no frame to present at render time and ends when a new frame is presented. |
| `UNDERFLOW_DURATION_MS` | ms | counter | read | Cumulative wall-clock time across all video underflow episodes. Paired with underflowed, so the mean episode length is this divided by that. An underflow episode manifests on screen as a freeze. |
| `FREEZE_DURATION_MS` | ms | counter | read | Cumulative on-screen time the same frame was held to cover a missing frame, which is the customer-visible freeze — the time integral of FRAMES_REPEATED_MISSING_FRAME. Excludes frame-rate-conversion cadence repeats, which are not freezes. |
| `FREEZE_EVENT_COUNT` | events | counter | read | Count of freeze episodes, one per episode start. Paired with FREEZE_DURATION_MS, so the mean freeze length is that divided by this. |
| `MAX_FREEZE_DURATION_MS` | ms | high_water | read | Longest single freeze episode observed. A monotone non-decreasing high-water mark over the life of the resource, and read-only: a maximum cannot be recovered by differencing two maxima, so a consumer wanting the worst freeze within its own reporting window tracks that itself from LAST_FREEZE_DURATION_MS rather than resetting a figure other readers share. |
| `RENDER_LATENCY_SUM_US` | us | counter | read | Running sum of per-frame render latency, from a frame arriving at the sink input to being presented to scanout. Paired with FRAMES_PRESENTED. |
| `BUFFER_DEPTH_MS` | ms | current | read | Buffered decoded media ahead of the present position now — the sum of presentation durations of frames queued but not yet presented. A live sample re-read each capture rather than a cumulative figure. This is SoC- and use-case-specific, so compare it against itself over time rather than across products. |
| `LAST_UNDERFLOW_TRIGGER` | none | current | read | Cause of the most recent underflow episode, which is what distinguishes an expected starvation from a defect. |
| `LAST_UNDERFLOW_DURATION_MS` | ms | current | read | Length of the most recent completed underflow episode. Read with underflowed and UNDERFLOW_DURATION_MS, which give the count and the total. |
| `LAST_DROPPED_FRAME_PTS_MS` | ms | current | read | Stream PTS of the most recently dropped frame, within one frame interval, whichever drop axis it fell on. This is what turns a drop count into a locatable defect. Left undeclared where no PTS is derivable. |
| `LAST_FREEZE_PTS_MS` | ms | current | read | Stream PTS at which the most recent freeze episode began, within one frame interval. Does for a freeze what LAST_DROPPED_FRAME_PTS_MS does for a drop. Left undeclared where no PTS is derivable. |
| `LAST_FREEZE_DURATION_MS` | ms | current | read | Length of the most recent completed freeze episode. Read with FREEZE_EVENT_COUNT and FREEZE_DURATION_MS for the count and the total, and with MAX_FREEZE_DURATION_MS for the worst. |
| `FIRST_FRAME_PRESENTED_PTS_MS` | ms | current | read | PTS of the first frame to reach presentation, set at session start and re-set after each seek or flush. This is the hardware's contribution to time-to-first-frame; whatever elapsed above the HAL before decode began is observed by the party that started the session. |

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

### `FIRST_FRAME_PRESENTED`

Raised when the first frame reaches presentation, once at session start and again after each seek or flush.

| Member | Unit | Definition |
|---|---|---|
| `FIRST_FRAME_PRESENTED_PTS_MS` | ms | PTS of the frame that reached presentation. Absent where the SoC cannot derive a PTS. |

### `QUALITY_THRESHOLD_CROSSED`

Raised when a quality counter crosses its declared threshold. Only the sink knows whether it shed a frame or repeated one, so which counter moved is carried rather than inferred.

| Member | Unit | Definition |
|---|---|---|
| `QUALITY_THRESHOLD_CROSSED_METRIC` | none | Which counter crossed its threshold. |
| `QUALITY_THRESHOLD_CROSSED_PTS_MS` | ms | Stream PTS at the crossing. Absent where no PTS is derivable. |

| Member | Unit | Kind | Definition |
|---|---|---|---|
| `QUALITY_THRESHOLD_CROSSED_COUNT` | frames | current | How many frames the crossing covered. |

**`metric` takes a `MetricQualityFigure` value**

| Name | Value | Meaning |
|---|---|---|
| `FRAMES_DROPPED` | 1 | A drop counter crossed. |
| `FRAMES_REPEATED` | 2 | A repeat counter crossed. |

# Video Decoder Metrics

The figures `videodecoder` serves through `getMetrics()` and raises through `onMetricEvent()`. Each figure is a member of the component's `Metric` enum, and each occurrence a member of `MetricEventKind`.

|||
|-|-|
|**Element**|`MetricElement::VIDEO_DECODER`|
|**Instances**|2|
|**Capture cadence**|no slower than 20 ms|

## Figures

| Member | Unit | Kind | Access | Definition |
|---|---|---|---|---|
| `FRAMES_DECODED` | frames | counter | read | Compressed frames the decoder has decoded and emitted at its output, post-decode and pre-sink. One per emitted frame, counted from instance creation and never reset on flush or seek. |
| `FRAMES_DROPPED` | frames | counter | read | Frames the decoder discarded before output — undecodable through corruption or unsupported format, or shed under decode overload. Excludes presentation-side drops, which belong to the video sink. A frame counted here is not also in FRAMES_DECODED. |
| `DECODE_ERRORS` | events | counter | read | Decode-error occurrences such as a bitstream or NAL parse failure or a codec fault. Decoder-internal, and a distinct axis from FRAMES_DROPPED: an error need not drop a frame, and a drop need not be an error. |
| `DECODE_LATENCY_SUM_US` | us | counter | read | Running sum of per-frame decode latency, measured from the compressed access unit being queued to the decoder input until the frame is emitted at its output. Mean latency is this divided by FRAMES_DECODED. |
| `LAST_DECODE_ERROR_PTS_MS` | ms | current | read | Stream PTS at detection of the most recent decode error, within one frame interval. Read with DECODE_ERRORS, which says how many there were while this says where the newest one was. Left undeclared where the SoC cannot derive a PTS, and never served as -1. |
| `LAST_DECODE_ERROR_REASON` | none | current | read | Classification of the most recent decode error. This is the value a consumer branches on, and what makes the fault comparable across SoCs. |
| `LAST_DECODE_ERROR_VENDOR_CODE` | none | current | read | The SoC's own error code for the same fault, carried through uninterpreted. For vendor diagnosis, and never branched on. |

**`last_decode_error_reason` takes a `MetricDecodeErrorReason` value**

| Name | Value | Meaning |
|---|---|---|
| `NONE` | 0 | No decode error has been recorded. |
| `BITSTREAM_ERROR` | 1 | The coded bitstream was malformed or failed to parse. |
| `UNSUPPORTED_FORMAT` | 2 | The stream is well formed but uses a tool, profile or level this decoder does not implement. |
| `DECODER_FAULT` | 3 | The decoder failed internally on a stream it should have been able to decode. |
| `RESOURCE_LOST` | 4 | A resource the decode depended on was withdrawn, such as a secure buffer or a hardware context reclaimed under pressure. |
| `HARDWARE_FAULT` | 5 | The decode hardware reported a fault. |

## Events

### `DECODE_ERROR`

Raised at detection of a decode fault, once per fault. A fault that also discards a frame raises this and advances FRAMES_DROPPED; a fault that does not raises this alone. The two are separate axes.

| Member | Unit | Definition |
|---|---|---|
| `DECODE_ERROR_REASON` | none | Classification of this fault, with the same values as LAST_DECODE_ERROR_REASON. The value a consumer branches on. |
| `DECODE_ERROR_VENDOR_CODE` | none | The SoC's own error code for this fault, carried through uninterpreted. For vendor diagnosis, and never branched on. |
| `DECODE_ERROR_PTS_MS` | ms | Stream PTS at detection, within one frame interval. Absent where the SoC cannot derive a PTS at all, and NOT_AVAILABLE where it can but could not at this instant. Never sent as -1. |

`reason` takes a `MetricDecodeErrorReason` value, listed above.

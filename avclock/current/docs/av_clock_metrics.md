# AV Clock Metrics

The figures `avclock` serves through `getMetrics()`. Each figure is a member of the component's `Metric` enum.

|||
|-|-|
|**Element**|`MetricElement::CLOCK`|
|**Instances**|1|
|**Capture cadence**|no slower than 50 ms|

## Figures

| Member | Unit | Kind | Access | Definition |
|---|---|---|---|---|
| `SYNC_OFFSET_MS` | ms | current | read | The driver's predicted current audio-versus-video presentation offset. Positive when audio leads, negative when video leads. A live sample rather than a cumulative figure. |
| `SYNC_MAX_ABS_OFFSET_MS` | ms | high_water | read | Largest absolute SYNC_OFFSET_MS observed. A monotone non-decreasing high-water mark over the life of the resource, and read-only: a maximum cannot be recovered by differencing two maxima, so a consumer wanting the worst excursion within its own reporting window tracks that itself from SYNC_OFFSET_MS rather than resetting a figure other readers share. |
| `SYNC_TIME_OVER_THRESHOLD_MS` | ms | counter | read | Cumulative time the absolute SYNC_OFFSET_MS exceeded SYNC_THRESHOLD_MS — the time integral of out-of-sync operation. |
| `SYNC_THRESHOLD_MS` | ms | config | read | The offset magnitude beyond which playback counts as out of sync. This is the threshold SYNC_TIME_OVER_THRESHOLD_MS integrates against and SYNC_MAX_ABS_OFFSET_MS is judged by, so declaring either of those without this leaves both uninterpretable — reading it is what the key is for. The value is set by product configuration rather than over this interface, so a consumer never has to assume the threshold it was built against is the one in force. |
| `RESYNC_COUNT` | events | counter | read | Count of A/V-sync corrections the clock applied, one per discrete realignment of audio and video. |
| `RESYNC_MAGNITUDE_SUM_MS` | ms | counter | read | Sum of the absolute magnitude of each resync correction. Clock-internal, and paired with RESYNC_COUNT so the mean correction size is this divided by that. |

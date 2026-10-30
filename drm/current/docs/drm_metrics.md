# DRM Metrics

The figures `drm` serves through `getDeclaredMetrics()`. Each figure is a member of the component's `Metric` enum.

|||
|-|-|
|**Element**|`MetricElement::DRM`|
|**Instances**|2|
|**Capture cadence**|no slower than 50 ms|

## Figures

| Member | Unit | Kind | Access | Definition |
|---|---|---|---|---|
| `DECRYPT_COUNT` | operations | counter | read | Decrypt operations completed, summed across the key sessions this media session holds. The denominator for mean decrypt latency. |
| `DECRYPT_ERRORS` | events | counter | read | Decrypt operations that failed on a key already held. Distinct from a licence that was never obtained, which is not vendor-observable and is not counted here. |
| `DECRYPT_LATENCY_SUM_US` | us | counter | read | Sum of decrypt operation latency. Paired with DECRYPT_COUNT, so the mean decrypt latency is this divided by that. |

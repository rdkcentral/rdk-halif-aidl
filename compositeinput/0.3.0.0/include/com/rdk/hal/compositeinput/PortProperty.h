#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
// @aidl-doc
/**
 * @brief Composite input port property keys used in get/set functions.
 *
 * Port-scoped runtime state and telemetry keys for a composite input port.
 * Used by ICompositeInputPort.getProperty() / getPropertyMulti() for reads
 * and ICompositeInputController.setProperty() / setPropertyMulti() for writes.
 *
 * Keys are declared per port by the platform in hfp-compositeinput.yaml
 * under ports[].supportedProperties and surfaced through
 * PortCapabilities.supportedProperties.
 *
 * Numeric slots are sparse so additions never renumber existing values:
 * - 0..999    runtime status keys
 * - 1000+     telemetry metric counters (reset by ICompositeInputController.resetMetrics())
 *
 * Metrics are first-class property keys. There is no separate metrics
 * parcelable — metrics are read with the same get/getMulti methods
 * used for status, matching the convention used by videodecoder,
 * videosink, hdmiinput and hdmioutput.
 *
 * @author Gerald Weatherup
 */
enum class PortProperty : int32_t {
  // @aidl-doc
  /**
   * Signal strength of the composite input, in dBm.
   *
   * Type: Long
   * Access: Read-only.
   */
  SIGNAL_STRENGTH = 0,
  // @aidl-doc
  /**
   * Aggregated signal quality score.
   *
   * Overall signal-health percentage used for UI indicators and adaptive
   * behaviour. Implementation-defined weighting of strength, lock stability,
   * and error rates.
   *
   * Type: Integer (0..100)
   *   0         No signal or very poor quality
   *   1..30     Poor quality (unstable, artifacts expected)
   *   31..70    Fair quality (acceptable but not optimal)
   *   71..90    Good quality (stable, clear picture)
   *   91..100   Excellent quality (optimal signal)
   * Access: Read-only.
   */
  SIGNAL_QUALITY = 1,
  // @aidl-doc
  /**
   * Average time taken for the composite input to achieve signal lock,
   * in milliseconds.
   *
   * Type: Long
   * Access: Read-only.
   * Reset by ICompositeInputController.resetMetrics().
   */
  METRIC_SIGNAL_LOCK_TIME = 1000,
  // @aidl-doc
  /**
   * Total count of signal drops (lock-loss events) observed on the
   * composite input since the last call to resetMetrics().
   *
   * Type: Long
   * Access: Read-only.
   * Reset by ICompositeInputController.resetMetrics().
   */
  METRIC_SIGNAL_DROPS = 1001,
  // @aidl-doc
  /**
   * Total uptime of the composite input since the last call to
   * resetMetrics(), in milliseconds.
   *
   * Type: Long
   * Access: Read-only.
   * Reset by ICompositeInputController.resetMetrics().
   */
  METRIC_UPTIME = 1002,
  // @aidl-doc
  /**
   * Total count of successful signal lock acquisitions since the last
   * call to resetMetrics().
   *
   * Type: Long
   * Access: Read-only.
   * Reset by ICompositeInputController.resetMetrics().
   */
  METRIC_SIGNAL_LOCK_COUNT = 1003,
  // @aidl-doc
  /**
   * Most recent signal lock time, in milliseconds.
   *
   * The time the most recent successful lock acquisition took.
   *
   * Type: Long
   * Access: Read-only.
   * Reset by ICompositeInputController.resetMetrics().
   */
  METRIC_LAST_SIGNAL_LOCK_TIME = 1004,
  // @aidl-doc
  /**
   * Timestamp when metrics were last reset, in milliseconds since epoch.
   *
   * Set to the current wall-clock time by ICompositeInputController.resetMetrics().
   *
   * Type: Long
   * Access: Read-only.
   */
  METRIC_LAST_RESET_TIMESTAMP = 1005,
};
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
[[nodiscard]] static inline std::string toString(PortProperty val) {
  switch(val) {
  case PortProperty::SIGNAL_STRENGTH:
    return "SIGNAL_STRENGTH";
  case PortProperty::SIGNAL_QUALITY:
    return "SIGNAL_QUALITY";
  case PortProperty::METRIC_SIGNAL_LOCK_TIME:
    return "METRIC_SIGNAL_LOCK_TIME";
  case PortProperty::METRIC_SIGNAL_DROPS:
    return "METRIC_SIGNAL_DROPS";
  case PortProperty::METRIC_UPTIME:
    return "METRIC_UPTIME";
  case PortProperty::METRIC_SIGNAL_LOCK_COUNT:
    return "METRIC_SIGNAL_LOCK_COUNT";
  case PortProperty::METRIC_LAST_SIGNAL_LOCK_TIME:
    return "METRIC_LAST_SIGNAL_LOCK_TIME";
  case PortProperty::METRIC_LAST_RESET_TIMESTAMP:
    return "METRIC_LAST_RESET_TIMESTAMP";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::compositeinput::PortProperty, 8> enum_values<::com::rdk::hal::compositeinput::PortProperty> = {
  ::com::rdk::hal::compositeinput::PortProperty::SIGNAL_STRENGTH,
  ::com::rdk::hal::compositeinput::PortProperty::SIGNAL_QUALITY,
  ::com::rdk::hal::compositeinput::PortProperty::METRIC_SIGNAL_LOCK_TIME,
  ::com::rdk::hal::compositeinput::PortProperty::METRIC_SIGNAL_DROPS,
  ::com::rdk::hal::compositeinput::PortProperty::METRIC_UPTIME,
  ::com::rdk::hal::compositeinput::PortProperty::METRIC_SIGNAL_LOCK_COUNT,
  ::com::rdk::hal::compositeinput::PortProperty::METRIC_LAST_SIGNAL_LOCK_TIME,
  ::com::rdk::hal::compositeinput::PortProperty::METRIC_LAST_RESET_TIMESTAMP,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

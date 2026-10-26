#pragma once
// @aidl-doc
/**
 * @file ActionEvent.h
 * @brief Event payload delivered to thermal event listeners.
 *
 * @details
 * Provides context for a thermal state change event, including:
 *  - New thermal state
 *  - Monotonic event timestamp
 *  - Temperature reading with vendor metadata
 */

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/sensor/thermal/State.h>
#include <com/rdk/hal/sensor/thermal/TemperatureReading.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace thermal {
class ActionEvent : public ::android::Parcelable {
public:
  // @aidl-doc
  /** @brief The sensor's new thermal state. */
  ::com::rdk::hal::sensor::thermal::State state = ::com::rdk::hal::sensor::thermal::State(0);
  // @aidl-doc
  /**
   * @brief Monotonic timestamp (ms) when the state change occurred.
   * @details Use monotonic time for event ordering; not wall-clock time.
   */
  int64_t timestampMonotonicMs = 0L;
  // @aidl-doc
  /**
   * @brief Temperature reading of the sensor whose state changed.
   * @details Set on every event; identifies the sensor. For a sensor that
   * reports no temperature, temperatureCelsius is the sensor's HFP threshold
   * for the state entered: critical_temperature_recovered_celsius for NORMAL,
   * critical_temperature_exceeded_celsius for CRITICAL_TEMPERATURE_EXCEEDED,
   * entering_critical_shutdown_celsius for CRITICAL_SHUTDOWN_IMMINENT.
   * The HAL never passes null; the annotation remains because the field is
   * in the frozen 0.1.0.0 and 0.2.0.0 interfaces.
   */
  ::std::optional<::com::rdk::hal::sensor::thermal::TemperatureReading> temperatureReading;
  inline bool operator!=(const ActionEvent& rhs) const {
    return std::tie(state, timestampMonotonicMs, temperatureReading) != std::tie(rhs.state, rhs.timestampMonotonicMs, rhs.temperatureReading);
  }
  inline bool operator<(const ActionEvent& rhs) const {
    return std::tie(state, timestampMonotonicMs, temperatureReading) < std::tie(rhs.state, rhs.timestampMonotonicMs, rhs.temperatureReading);
  }
  inline bool operator<=(const ActionEvent& rhs) const {
    return std::tie(state, timestampMonotonicMs, temperatureReading) <= std::tie(rhs.state, rhs.timestampMonotonicMs, rhs.temperatureReading);
  }
  inline bool operator==(const ActionEvent& rhs) const {
    return std::tie(state, timestampMonotonicMs, temperatureReading) == std::tie(rhs.state, rhs.timestampMonotonicMs, rhs.temperatureReading);
  }
  inline bool operator>(const ActionEvent& rhs) const {
    return std::tie(state, timestampMonotonicMs, temperatureReading) > std::tie(rhs.state, rhs.timestampMonotonicMs, rhs.temperatureReading);
  }
  inline bool operator>=(const ActionEvent& rhs) const {
    return std::tie(state, timestampMonotonicMs, temperatureReading) >= std::tie(rhs.state, rhs.timestampMonotonicMs, rhs.temperatureReading);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.sensor.thermal.ActionEvent");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "ActionEvent{";
    os << "state: " << ::android::internal::ToString(state);
    os << ", timestampMonotonicMs: " << ::android::internal::ToString(timestampMonotonicMs);
    os << ", temperatureReading: " << ::android::internal::ToString(temperatureReading);
    os << "}";
    return os.str();
  }
};  // class ActionEvent
}  // namespace thermal
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com

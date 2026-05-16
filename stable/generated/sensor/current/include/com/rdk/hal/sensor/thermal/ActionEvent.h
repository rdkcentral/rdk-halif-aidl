#pragma once

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
  ::com::rdk::hal::sensor::thermal::State state = ::com::rdk::hal::sensor::thermal::State(0);
  int64_t timestampMonotonicMs = 0L;
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

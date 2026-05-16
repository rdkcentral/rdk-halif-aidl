#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
class TimeWindow : public ::android::Parcelable {
public:
  int32_t startTimeOfDaySeconds = 0;
  int32_t endTimeOfDaySeconds = 0;
  inline bool operator!=(const TimeWindow& rhs) const {
    return std::tie(startTimeOfDaySeconds, endTimeOfDaySeconds) != std::tie(rhs.startTimeOfDaySeconds, rhs.endTimeOfDaySeconds);
  }
  inline bool operator<(const TimeWindow& rhs) const {
    return std::tie(startTimeOfDaySeconds, endTimeOfDaySeconds) < std::tie(rhs.startTimeOfDaySeconds, rhs.endTimeOfDaySeconds);
  }
  inline bool operator<=(const TimeWindow& rhs) const {
    return std::tie(startTimeOfDaySeconds, endTimeOfDaySeconds) <= std::tie(rhs.startTimeOfDaySeconds, rhs.endTimeOfDaySeconds);
  }
  inline bool operator==(const TimeWindow& rhs) const {
    return std::tie(startTimeOfDaySeconds, endTimeOfDaySeconds) == std::tie(rhs.startTimeOfDaySeconds, rhs.endTimeOfDaySeconds);
  }
  inline bool operator>(const TimeWindow& rhs) const {
    return std::tie(startTimeOfDaySeconds, endTimeOfDaySeconds) > std::tie(rhs.startTimeOfDaySeconds, rhs.endTimeOfDaySeconds);
  }
  inline bool operator>=(const TimeWindow& rhs) const {
    return std::tie(startTimeOfDaySeconds, endTimeOfDaySeconds) >= std::tie(rhs.startTimeOfDaySeconds, rhs.endTimeOfDaySeconds);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.sensor.motion.TimeWindow");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "TimeWindow{";
    os << "startTimeOfDaySeconds: " << ::android::internal::ToString(startTimeOfDaySeconds);
    os << ", endTimeOfDaySeconds: " << ::android::internal::ToString(endTimeOfDaySeconds);
    os << "}";
    return os.str();
  }
};  // class TimeWindow
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com

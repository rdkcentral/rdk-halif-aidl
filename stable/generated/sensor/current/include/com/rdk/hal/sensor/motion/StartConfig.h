#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/sensor/motion/OperationalMode.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
class StartConfig : public ::android::Parcelable {
public:
  ::com::rdk::hal::sensor::motion::OperationalMode operationalMode = ::com::rdk::hal::sensor::motion::OperationalMode(0);
  int32_t noMotionSeconds = 0;
  int32_t activeStartSeconds = 0;
  int32_t activeStopSeconds = 0;
  inline bool operator!=(const StartConfig& rhs) const {
    return std::tie(operationalMode, noMotionSeconds, activeStartSeconds, activeStopSeconds) != std::tie(rhs.operationalMode, rhs.noMotionSeconds, rhs.activeStartSeconds, rhs.activeStopSeconds);
  }
  inline bool operator<(const StartConfig& rhs) const {
    return std::tie(operationalMode, noMotionSeconds, activeStartSeconds, activeStopSeconds) < std::tie(rhs.operationalMode, rhs.noMotionSeconds, rhs.activeStartSeconds, rhs.activeStopSeconds);
  }
  inline bool operator<=(const StartConfig& rhs) const {
    return std::tie(operationalMode, noMotionSeconds, activeStartSeconds, activeStopSeconds) <= std::tie(rhs.operationalMode, rhs.noMotionSeconds, rhs.activeStartSeconds, rhs.activeStopSeconds);
  }
  inline bool operator==(const StartConfig& rhs) const {
    return std::tie(operationalMode, noMotionSeconds, activeStartSeconds, activeStopSeconds) == std::tie(rhs.operationalMode, rhs.noMotionSeconds, rhs.activeStartSeconds, rhs.activeStopSeconds);
  }
  inline bool operator>(const StartConfig& rhs) const {
    return std::tie(operationalMode, noMotionSeconds, activeStartSeconds, activeStopSeconds) > std::tie(rhs.operationalMode, rhs.noMotionSeconds, rhs.activeStartSeconds, rhs.activeStopSeconds);
  }
  inline bool operator>=(const StartConfig& rhs) const {
    return std::tie(operationalMode, noMotionSeconds, activeStartSeconds, activeStopSeconds) >= std::tie(rhs.operationalMode, rhs.noMotionSeconds, rhs.activeStartSeconds, rhs.activeStopSeconds);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.sensor.motion.StartConfig");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "StartConfig{";
    os << "operationalMode: " << ::android::internal::ToString(operationalMode);
    os << ", noMotionSeconds: " << ::android::internal::ToString(noMotionSeconds);
    os << ", activeStartSeconds: " << ::android::internal::ToString(activeStartSeconds);
    os << ", activeStopSeconds: " << ::android::internal::ToString(activeStopSeconds);
    os << "}";
    return os.str();
  }
};  // class StartConfig
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com

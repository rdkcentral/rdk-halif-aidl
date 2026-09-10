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
class Capabilities : public ::android::Parcelable {
public:
  ::android::String16 sensorName;
  int32_t minSensitivity = 0;
  int32_t maxSensitivity = 0;
  bool supportsDeepSleepAutonomy = false;
  inline bool operator!=(const Capabilities& rhs) const {
    return std::tie(sensorName, minSensitivity, maxSensitivity, supportsDeepSleepAutonomy) != std::tie(rhs.sensorName, rhs.minSensitivity, rhs.maxSensitivity, rhs.supportsDeepSleepAutonomy);
  }
  inline bool operator<(const Capabilities& rhs) const {
    return std::tie(sensorName, minSensitivity, maxSensitivity, supportsDeepSleepAutonomy) < std::tie(rhs.sensorName, rhs.minSensitivity, rhs.maxSensitivity, rhs.supportsDeepSleepAutonomy);
  }
  inline bool operator<=(const Capabilities& rhs) const {
    return std::tie(sensorName, minSensitivity, maxSensitivity, supportsDeepSleepAutonomy) <= std::tie(rhs.sensorName, rhs.minSensitivity, rhs.maxSensitivity, rhs.supportsDeepSleepAutonomy);
  }
  inline bool operator==(const Capabilities& rhs) const {
    return std::tie(sensorName, minSensitivity, maxSensitivity, supportsDeepSleepAutonomy) == std::tie(rhs.sensorName, rhs.minSensitivity, rhs.maxSensitivity, rhs.supportsDeepSleepAutonomy);
  }
  inline bool operator>(const Capabilities& rhs) const {
    return std::tie(sensorName, minSensitivity, maxSensitivity, supportsDeepSleepAutonomy) > std::tie(rhs.sensorName, rhs.minSensitivity, rhs.maxSensitivity, rhs.supportsDeepSleepAutonomy);
  }
  inline bool operator>=(const Capabilities& rhs) const {
    return std::tie(sensorName, minSensitivity, maxSensitivity, supportsDeepSleepAutonomy) >= std::tie(rhs.sensorName, rhs.minSensitivity, rhs.maxSensitivity, rhs.supportsDeepSleepAutonomy);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.sensor.motion.Capabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Capabilities{";
    os << "sensorName: " << ::android::internal::ToString(sensorName);
    os << ", minSensitivity: " << ::android::internal::ToString(minSensitivity);
    os << ", maxSensitivity: " << ::android::internal::ToString(maxSensitivity);
    os << ", supportsDeepSleepAutonomy: " << ::android::internal::ToString(supportsDeepSleepAutonomy);
    os << "}";
    return os.str();
  }
};  // class Capabilities
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com

#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace demo {
namespace hal {
namespace common {
class SpeedStatus : public ::android::Parcelable {
public:
  float currentSpeed = 0.000000f;
  float maxSpeed = 0.000000f;
  inline bool operator!=(const SpeedStatus& rhs) const {
    return std::tie(currentSpeed, maxSpeed) != std::tie(rhs.currentSpeed, rhs.maxSpeed);
  }
  inline bool operator<(const SpeedStatus& rhs) const {
    return std::tie(currentSpeed, maxSpeed) < std::tie(rhs.currentSpeed, rhs.maxSpeed);
  }
  inline bool operator<=(const SpeedStatus& rhs) const {
    return std::tie(currentSpeed, maxSpeed) <= std::tie(rhs.currentSpeed, rhs.maxSpeed);
  }
  inline bool operator==(const SpeedStatus& rhs) const {
    return std::tie(currentSpeed, maxSpeed) == std::tie(rhs.currentSpeed, rhs.maxSpeed);
  }
  inline bool operator>(const SpeedStatus& rhs) const {
    return std::tie(currentSpeed, maxSpeed) > std::tie(rhs.currentSpeed, rhs.maxSpeed);
  }
  inline bool operator>=(const SpeedStatus& rhs) const {
    return std::tie(currentSpeed, maxSpeed) >= std::tie(rhs.currentSpeed, rhs.maxSpeed);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.demo.hal.common.SpeedStatus");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "SpeedStatus{";
    os << "currentSpeed: " << ::android::internal::ToString(currentSpeed);
    os << ", maxSpeed: " << ::android::internal::ToString(maxSpeed);
    os << "}";
    return os.str();
  }
};  // class SpeedStatus
}  // namespace common
}  // namespace hal
}  // namespace demo
}  // namespace com

#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace demo {
namespace hal {
namespace vehicle {
class VehicleStatus : public ::android::Parcelable {
public:
  bool isMoving = false;
  bool engineOn = false;
  inline bool operator!=(const VehicleStatus& rhs) const {
    return std::tie(isMoving, engineOn) != std::tie(rhs.isMoving, rhs.engineOn);
  }
  inline bool operator<(const VehicleStatus& rhs) const {
    return std::tie(isMoving, engineOn) < std::tie(rhs.isMoving, rhs.engineOn);
  }
  inline bool operator<=(const VehicleStatus& rhs) const {
    return std::tie(isMoving, engineOn) <= std::tie(rhs.isMoving, rhs.engineOn);
  }
  inline bool operator==(const VehicleStatus& rhs) const {
    return std::tie(isMoving, engineOn) == std::tie(rhs.isMoving, rhs.engineOn);
  }
  inline bool operator>(const VehicleStatus& rhs) const {
    return std::tie(isMoving, engineOn) > std::tie(rhs.isMoving, rhs.engineOn);
  }
  inline bool operator>=(const VehicleStatus& rhs) const {
    return std::tie(isMoving, engineOn) >= std::tie(rhs.isMoving, rhs.engineOn);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.demo.hal.vehicle.VehicleStatus");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "VehicleStatus{";
    os << "isMoving: " << ::android::internal::ToString(isMoving);
    os << ", engineOn: " << ::android::internal::ToString(engineOn);
    os << "}";
    return os.str();
  }
};  // class VehicleStatus
}  // namespace vehicle
}  // namespace hal
}  // namespace demo
}  // namespace com

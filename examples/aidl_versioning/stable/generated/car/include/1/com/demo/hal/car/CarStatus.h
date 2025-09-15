#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/demo/hal/vehicle/VehicleStatus.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace demo {
namespace hal {
namespace car {
class CarStatus : public ::android::Parcelable {
public:
  ::com::demo::hal::vehicle::VehicleStatus vehicleStatus;
  inline bool operator!=(const CarStatus& rhs) const {
    return std::tie(vehicleStatus) != std::tie(rhs.vehicleStatus);
  }
  inline bool operator<(const CarStatus& rhs) const {
    return std::tie(vehicleStatus) < std::tie(rhs.vehicleStatus);
  }
  inline bool operator<=(const CarStatus& rhs) const {
    return std::tie(vehicleStatus) <= std::tie(rhs.vehicleStatus);
  }
  inline bool operator==(const CarStatus& rhs) const {
    return std::tie(vehicleStatus) == std::tie(rhs.vehicleStatus);
  }
  inline bool operator>(const CarStatus& rhs) const {
    return std::tie(vehicleStatus) > std::tie(rhs.vehicleStatus);
  }
  inline bool operator>=(const CarStatus& rhs) const {
    return std::tie(vehicleStatus) >= std::tie(rhs.vehicleStatus);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.demo.hal.car.CarStatus");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "CarStatus{";
    os << "vehicleStatus: " << ::android::internal::ToString(vehicleStatus);
    os << "}";
    return os.str();
  }
};  // class CarStatus
}  // namespace car
}  // namespace hal
}  // namespace demo
}  // namespace com

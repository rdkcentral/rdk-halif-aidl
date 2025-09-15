#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/demo/hal/common/FuelStatus.h>
#include <com/demo/hal/vehicle/VehicleStatus.h>
#include <optional>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace demo {
namespace hal {
namespace car {
class CarStatus : public ::android::Parcelable {
public:
  ::com::demo::hal::vehicle::VehicleStatus vehicleStatus;
  ::std::optional<::com::demo::hal::common::FuelStatus> fuelStatus;
  inline bool operator!=(const CarStatus& rhs) const {
    return std::tie(vehicleStatus, fuelStatus) != std::tie(rhs.vehicleStatus, rhs.fuelStatus);
  }
  inline bool operator<(const CarStatus& rhs) const {
    return std::tie(vehicleStatus, fuelStatus) < std::tie(rhs.vehicleStatus, rhs.fuelStatus);
  }
  inline bool operator<=(const CarStatus& rhs) const {
    return std::tie(vehicleStatus, fuelStatus) <= std::tie(rhs.vehicleStatus, rhs.fuelStatus);
  }
  inline bool operator==(const CarStatus& rhs) const {
    return std::tie(vehicleStatus, fuelStatus) == std::tie(rhs.vehicleStatus, rhs.fuelStatus);
  }
  inline bool operator>(const CarStatus& rhs) const {
    return std::tie(vehicleStatus, fuelStatus) > std::tie(rhs.vehicleStatus, rhs.fuelStatus);
  }
  inline bool operator>=(const CarStatus& rhs) const {
    return std::tie(vehicleStatus, fuelStatus) >= std::tie(rhs.vehicleStatus, rhs.fuelStatus);
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
    os << ", fuelStatus: " << ::android::internal::ToString(fuelStatus);
    os << "}";
    return os.str();
  }
};  // class CarStatus
}  // namespace car
}  // namespace hal
}  // namespace demo
}  // namespace com

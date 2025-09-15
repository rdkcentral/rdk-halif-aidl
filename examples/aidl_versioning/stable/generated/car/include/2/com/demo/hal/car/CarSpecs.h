#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/demo/hal/vehicle/VehicleSpecs.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace demo {
namespace hal {
namespace car {
class CarSpecs : public ::android::Parcelable {
public:
  ::com::demo::hal::vehicle::VehicleSpecs vehicleSpecs;
  int32_t numberOfDoors = 0;
  bool hasSunroof = false;
  bool isElectric = false;
  inline bool operator!=(const CarSpecs& rhs) const {
    return std::tie(vehicleSpecs, numberOfDoors, hasSunroof, isElectric) != std::tie(rhs.vehicleSpecs, rhs.numberOfDoors, rhs.hasSunroof, rhs.isElectric);
  }
  inline bool operator<(const CarSpecs& rhs) const {
    return std::tie(vehicleSpecs, numberOfDoors, hasSunroof, isElectric) < std::tie(rhs.vehicleSpecs, rhs.numberOfDoors, rhs.hasSunroof, rhs.isElectric);
  }
  inline bool operator<=(const CarSpecs& rhs) const {
    return std::tie(vehicleSpecs, numberOfDoors, hasSunroof, isElectric) <= std::tie(rhs.vehicleSpecs, rhs.numberOfDoors, rhs.hasSunroof, rhs.isElectric);
  }
  inline bool operator==(const CarSpecs& rhs) const {
    return std::tie(vehicleSpecs, numberOfDoors, hasSunroof, isElectric) == std::tie(rhs.vehicleSpecs, rhs.numberOfDoors, rhs.hasSunroof, rhs.isElectric);
  }
  inline bool operator>(const CarSpecs& rhs) const {
    return std::tie(vehicleSpecs, numberOfDoors, hasSunroof, isElectric) > std::tie(rhs.vehicleSpecs, rhs.numberOfDoors, rhs.hasSunroof, rhs.isElectric);
  }
  inline bool operator>=(const CarSpecs& rhs) const {
    return std::tie(vehicleSpecs, numberOfDoors, hasSunroof, isElectric) >= std::tie(rhs.vehicleSpecs, rhs.numberOfDoors, rhs.hasSunroof, rhs.isElectric);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.demo.hal.car.CarSpecs");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "CarSpecs{";
    os << "vehicleSpecs: " << ::android::internal::ToString(vehicleSpecs);
    os << ", numberOfDoors: " << ::android::internal::ToString(numberOfDoors);
    os << ", hasSunroof: " << ::android::internal::ToString(hasSunroof);
    os << ", isElectric: " << ::android::internal::ToString(isElectric);
    os << "}";
    return os.str();
  }
};  // class CarSpecs
}  // namespace car
}  // namespace hal
}  // namespace demo
}  // namespace com

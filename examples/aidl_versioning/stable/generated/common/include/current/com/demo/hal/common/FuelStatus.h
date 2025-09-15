#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/demo/hal/common/FuelType.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace demo {
namespace hal {
namespace common {
class FuelStatus : public ::android::Parcelable {
public:
  ::com::demo::hal::common::FuelType fuelType = ::com::demo::hal::common::FuelType(0);
  float fuelLevel = 0.000000f;
  float fuelConsumptionRate = 0.000000f;
  inline bool operator!=(const FuelStatus& rhs) const {
    return std::tie(fuelType, fuelLevel, fuelConsumptionRate) != std::tie(rhs.fuelType, rhs.fuelLevel, rhs.fuelConsumptionRate);
  }
  inline bool operator<(const FuelStatus& rhs) const {
    return std::tie(fuelType, fuelLevel, fuelConsumptionRate) < std::tie(rhs.fuelType, rhs.fuelLevel, rhs.fuelConsumptionRate);
  }
  inline bool operator<=(const FuelStatus& rhs) const {
    return std::tie(fuelType, fuelLevel, fuelConsumptionRate) <= std::tie(rhs.fuelType, rhs.fuelLevel, rhs.fuelConsumptionRate);
  }
  inline bool operator==(const FuelStatus& rhs) const {
    return std::tie(fuelType, fuelLevel, fuelConsumptionRate) == std::tie(rhs.fuelType, rhs.fuelLevel, rhs.fuelConsumptionRate);
  }
  inline bool operator>(const FuelStatus& rhs) const {
    return std::tie(fuelType, fuelLevel, fuelConsumptionRate) > std::tie(rhs.fuelType, rhs.fuelLevel, rhs.fuelConsumptionRate);
  }
  inline bool operator>=(const FuelStatus& rhs) const {
    return std::tie(fuelType, fuelLevel, fuelConsumptionRate) >= std::tie(rhs.fuelType, rhs.fuelLevel, rhs.fuelConsumptionRate);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.demo.hal.common.FuelStatus");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "FuelStatus{";
    os << "fuelType: " << ::android::internal::ToString(fuelType);
    os << ", fuelLevel: " << ::android::internal::ToString(fuelLevel);
    os << ", fuelConsumptionRate: " << ::android::internal::ToString(fuelConsumptionRate);
    os << "}";
    return os.str();
  }
};  // class FuelStatus
}  // namespace common
}  // namespace hal
}  // namespace demo
}  // namespace com

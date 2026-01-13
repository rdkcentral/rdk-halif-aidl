#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/demo/hal/common/EngineType.h>
#include <com/demo/hal/common/FuelType.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace demo {
namespace hal {
namespace common {
class EngineSpecs : public ::android::Parcelable {
public:
  ::com::demo::hal::common::EngineType engineType = ::com::demo::hal::common::EngineType(0);
  int32_t horsepower = 0;
  ::com::demo::hal::common::FuelType fuelType = ::com::demo::hal::common::FuelType(0);
  inline bool operator!=(const EngineSpecs& rhs) const {
    return std::tie(engineType, horsepower, fuelType) != std::tie(rhs.engineType, rhs.horsepower, rhs.fuelType);
  }
  inline bool operator<(const EngineSpecs& rhs) const {
    return std::tie(engineType, horsepower, fuelType) < std::tie(rhs.engineType, rhs.horsepower, rhs.fuelType);
  }
  inline bool operator<=(const EngineSpecs& rhs) const {
    return std::tie(engineType, horsepower, fuelType) <= std::tie(rhs.engineType, rhs.horsepower, rhs.fuelType);
  }
  inline bool operator==(const EngineSpecs& rhs) const {
    return std::tie(engineType, horsepower, fuelType) == std::tie(rhs.engineType, rhs.horsepower, rhs.fuelType);
  }
  inline bool operator>(const EngineSpecs& rhs) const {
    return std::tie(engineType, horsepower, fuelType) > std::tie(rhs.engineType, rhs.horsepower, rhs.fuelType);
  }
  inline bool operator>=(const EngineSpecs& rhs) const {
    return std::tie(engineType, horsepower, fuelType) >= std::tie(rhs.engineType, rhs.horsepower, rhs.fuelType);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.demo.hal.common.EngineSpecs");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "EngineSpecs{";
    os << "engineType: " << ::android::internal::ToString(engineType);
    os << ", horsepower: " << ::android::internal::ToString(horsepower);
    os << ", fuelType: " << ::android::internal::ToString(fuelType);
    os << "}";
    return os.str();
  }
};  // class EngineSpecs
}  // namespace common
}  // namespace hal
}  // namespace demo
}  // namespace com

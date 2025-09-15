#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/demo/hal/common/EngineSpecs.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace demo {
namespace hal {
namespace vehicle {
class VehicleSpecs : public ::android::Parcelable {
public:
  ::com::demo::hal::common::EngineSpecs engineSpecs;
  int32_t numberOfWheels = 0;
  float length = 0.000000f;
  float width = 0.000000f;
  float height = 0.000000f;
  inline bool operator!=(const VehicleSpecs& rhs) const {
    return std::tie(engineSpecs, numberOfWheels, length, width, height) != std::tie(rhs.engineSpecs, rhs.numberOfWheels, rhs.length, rhs.width, rhs.height);
  }
  inline bool operator<(const VehicleSpecs& rhs) const {
    return std::tie(engineSpecs, numberOfWheels, length, width, height) < std::tie(rhs.engineSpecs, rhs.numberOfWheels, rhs.length, rhs.width, rhs.height);
  }
  inline bool operator<=(const VehicleSpecs& rhs) const {
    return std::tie(engineSpecs, numberOfWheels, length, width, height) <= std::tie(rhs.engineSpecs, rhs.numberOfWheels, rhs.length, rhs.width, rhs.height);
  }
  inline bool operator==(const VehicleSpecs& rhs) const {
    return std::tie(engineSpecs, numberOfWheels, length, width, height) == std::tie(rhs.engineSpecs, rhs.numberOfWheels, rhs.length, rhs.width, rhs.height);
  }
  inline bool operator>(const VehicleSpecs& rhs) const {
    return std::tie(engineSpecs, numberOfWheels, length, width, height) > std::tie(rhs.engineSpecs, rhs.numberOfWheels, rhs.length, rhs.width, rhs.height);
  }
  inline bool operator>=(const VehicleSpecs& rhs) const {
    return std::tie(engineSpecs, numberOfWheels, length, width, height) >= std::tie(rhs.engineSpecs, rhs.numberOfWheels, rhs.length, rhs.width, rhs.height);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.demo.hal.vehicle.VehicleSpecs");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "VehicleSpecs{";
    os << "engineSpecs: " << ::android::internal::ToString(engineSpecs);
    os << ", numberOfWheels: " << ::android::internal::ToString(numberOfWheels);
    os << ", length: " << ::android::internal::ToString(length);
    os << ", width: " << ::android::internal::ToString(width);
    os << ", height: " << ::android::internal::ToString(height);
    os << "}";
    return os.str();
  }
};  // class VehicleSpecs
}  // namespace vehicle
}  // namespace hal
}  // namespace demo
}  // namespace com

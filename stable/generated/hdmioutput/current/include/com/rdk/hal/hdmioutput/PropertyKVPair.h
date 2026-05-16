#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/hdmioutput/Property.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
class PropertyKVPair : public ::android::Parcelable {
public:
  ::com::rdk::hal::hdmioutput::Property property = ::com::rdk::hal::hdmioutput::Property(0);
  ::com::rdk::hal::PropertyValue propertyValue;
  inline bool operator!=(const PropertyKVPair& rhs) const {
    return std::tie(property, propertyValue) != std::tie(rhs.property, rhs.propertyValue);
  }
  inline bool operator<(const PropertyKVPair& rhs) const {
    return std::tie(property, propertyValue) < std::tie(rhs.property, rhs.propertyValue);
  }
  inline bool operator<=(const PropertyKVPair& rhs) const {
    return std::tie(property, propertyValue) <= std::tie(rhs.property, rhs.propertyValue);
  }
  inline bool operator==(const PropertyKVPair& rhs) const {
    return std::tie(property, propertyValue) == std::tie(rhs.property, rhs.propertyValue);
  }
  inline bool operator>(const PropertyKVPair& rhs) const {
    return std::tie(property, propertyValue) > std::tie(rhs.property, rhs.propertyValue);
  }
  inline bool operator>=(const PropertyKVPair& rhs) const {
    return std::tie(property, propertyValue) >= std::tie(rhs.property, rhs.propertyValue);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.hdmioutput.PropertyKVPair");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PropertyKVPair{";
    os << "property: " << ::android::internal::ToString(property);
    os << ", propertyValue: " << ::android::internal::ToString(propertyValue);
    os << "}";
    return os.str();
  }
};  // class PropertyKVPair
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com

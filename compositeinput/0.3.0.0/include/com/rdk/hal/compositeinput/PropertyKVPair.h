#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/compositeinput/PortProperty.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
// @aidl-doc
/**
 * @brief Key-value pair for composite input port properties.
 *
 * Used by ICompositeInputPort.getPropertyMulti() and
 * ICompositeInputController.setPropertyMulti() for batch operations.
 */
class PropertyKVPair : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * Property key (from the PortProperty enum).
   *
   * Must be one of the values declared in the platform HFP under
   * ports[].supportedProperties and discoverable via
   * PortCapabilities.supportedProperties.
   */
  ::com::rdk::hal::compositeinput::PortProperty property = ::com::rdk::hal::compositeinput::PortProperty(0);
  // @aidl-doc
  /**
   * Property value.
   *
   * - For getPropertyMulti(), this field is populated by the HAL on return.
   * - For setPropertyMulti(), this field must be pre-filled by the caller.
   *
   * The appropriate union field must match PropertyMetadata.type:
   * - booleanValue for BOOLEAN properties
   * - intValue for INTEGER/enum properties
   * - longValue for LONG properties (e.g., SIGNAL_STRENGTH, metrics)
   * - floatValue for FLOAT properties
   * - doubleValue for DOUBLE properties
   * - stringValue for STRING properties
   */
  ::com::rdk::hal::PropertyValue value;
  inline bool operator!=(const PropertyKVPair& rhs) const {
    return std::tie(property, value) != std::tie(rhs.property, rhs.value);
  }
  inline bool operator<(const PropertyKVPair& rhs) const {
    return std::tie(property, value) < std::tie(rhs.property, rhs.value);
  }
  inline bool operator<=(const PropertyKVPair& rhs) const {
    return std::tie(property, value) <= std::tie(rhs.property, rhs.value);
  }
  inline bool operator==(const PropertyKVPair& rhs) const {
    return std::tie(property, value) == std::tie(rhs.property, rhs.value);
  }
  inline bool operator>(const PropertyKVPair& rhs) const {
    return std::tie(property, value) > std::tie(rhs.property, rhs.value);
  }
  inline bool operator>=(const PropertyKVPair& rhs) const {
    return std::tie(property, value) >= std::tie(rhs.property, rhs.value);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.compositeinput.PropertyKVPair");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PropertyKVPair{";
    os << "property: " << ::android::internal::ToString(property);
    os << ", value: " << ::android::internal::ToString(value);
    os << "}";
    return os.str();
  }
};  // class PropertyKVPair
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com

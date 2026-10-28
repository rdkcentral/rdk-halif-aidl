#pragma once

#include <android/binder_to_string.h>
#include <array>
#include <binder/Enums.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/compositeinput/PortProperty.h>
#include <com/rdk/hal/compositeinput/PropertyMetadata.h>
#include <cstdint>
#include <string>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
// @aidl-doc
/**
 * @brief Metadata describing a composite input property.
 *
 * Provides type information and access flags for properties,
 * enabling runtime discovery and validation. Property keys and
 * metadata are defined in the HFP YAML configuration.
 */
class PropertyMetadata : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * @brief Property value type enumeration.
   *
   * Indicates which field of PropertyValue union should be used.
   */
  enum class PropertyType : int32_t {
    // @aidl-doc
    /** Boolean value - maps to PropertyValue.booleanValue */
    BOOLEAN = 0,
    // @aidl-doc
    /** Integer value - maps to PropertyValue.intValue (often used for enums) */
    INTEGER = 1,
    // @aidl-doc
    /** Long value - maps to PropertyValue.longValue */
    LONG = 2,
    // @aidl-doc
    /** Float value - maps to PropertyValue.floatValue */
    FLOAT = 3,
    // @aidl-doc
    /** Double value - maps to PropertyValue.doubleValue */
    DOUBLE = 4,
    // @aidl-doc
    /** String value - maps to PropertyValue.stringValue */
    STRING = 5,
  };
  // @aidl-doc
  /** Property key (from the PortProperty enum). */
  ::com::rdk::hal::compositeinput::PortProperty key = ::com::rdk::hal::compositeinput::PortProperty(0);
  // @aidl-doc
  /** Data type of the property value. */
  ::com::rdk::hal::compositeinput::PropertyMetadata::PropertyType type = ::com::rdk::hal::compositeinput::PropertyMetadata::PropertyType(0);
  // @aidl-doc
  /** True if property is read-only. */
  bool readOnly = false;
  // @aidl-doc
  /** True if property is a metric (for categorization). */
  bool isMetric = false;
  // @aidl-doc
  /** Human-readable description of the property. */
  ::std::string description;
  inline bool operator!=(const PropertyMetadata& rhs) const {
    return std::tie(key, type, readOnly, isMetric, description) != std::tie(rhs.key, rhs.type, rhs.readOnly, rhs.isMetric, rhs.description);
  }
  inline bool operator<(const PropertyMetadata& rhs) const {
    return std::tie(key, type, readOnly, isMetric, description) < std::tie(rhs.key, rhs.type, rhs.readOnly, rhs.isMetric, rhs.description);
  }
  inline bool operator<=(const PropertyMetadata& rhs) const {
    return std::tie(key, type, readOnly, isMetric, description) <= std::tie(rhs.key, rhs.type, rhs.readOnly, rhs.isMetric, rhs.description);
  }
  inline bool operator==(const PropertyMetadata& rhs) const {
    return std::tie(key, type, readOnly, isMetric, description) == std::tie(rhs.key, rhs.type, rhs.readOnly, rhs.isMetric, rhs.description);
  }
  inline bool operator>(const PropertyMetadata& rhs) const {
    return std::tie(key, type, readOnly, isMetric, description) > std::tie(rhs.key, rhs.type, rhs.readOnly, rhs.isMetric, rhs.description);
  }
  inline bool operator>=(const PropertyMetadata& rhs) const {
    return std::tie(key, type, readOnly, isMetric, description) >= std::tie(rhs.key, rhs.type, rhs.readOnly, rhs.isMetric, rhs.description);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.compositeinput.PropertyMetadata");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PropertyMetadata{";
    os << "key: " << ::android::internal::ToString(key);
    os << ", type: " << ::android::internal::ToString(type);
    os << ", readOnly: " << ::android::internal::ToString(readOnly);
    os << ", isMetric: " << ::android::internal::ToString(isMetric);
    os << ", description: " << ::android::internal::ToString(description);
    os << "}";
    return os.str();
  }
};  // class PropertyMetadata
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
[[nodiscard]] static inline std::string toString(PropertyMetadata::PropertyType val) {
  switch(val) {
  case PropertyMetadata::PropertyType::BOOLEAN:
    return "BOOLEAN";
  case PropertyMetadata::PropertyType::INTEGER:
    return "INTEGER";
  case PropertyMetadata::PropertyType::LONG:
    return "LONG";
  case PropertyMetadata::PropertyType::FLOAT:
    return "FLOAT";
  case PropertyMetadata::PropertyType::DOUBLE:
    return "DOUBLE";
  case PropertyMetadata::PropertyType::STRING:
    return "STRING";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::compositeinput::PropertyMetadata::PropertyType, 6> enum_values<::com::rdk::hal::compositeinput::PropertyMetadata::PropertyType> = {
  ::com::rdk::hal::compositeinput::PropertyMetadata::PropertyType::BOOLEAN,
  ::com::rdk::hal::compositeinput::PropertyMetadata::PropertyType::INTEGER,
  ::com::rdk::hal::compositeinput::PropertyMetadata::PropertyType::LONG,
  ::com::rdk::hal::compositeinput::PropertyMetadata::PropertyType::FLOAT,
  ::com::rdk::hal::compositeinput::PropertyMetadata::PropertyType::DOUBLE,
  ::com::rdk::hal::compositeinput::PropertyMetadata::PropertyType::STRING,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

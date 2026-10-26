#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/compositeinput/PortProperty.h>
#include <com/rdk/hal/compositeinput/PropertyMetadata.h>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
// @aidl-doc
/**
 * @brief Port-specific capabilities.
 *
 * Describes the capabilities of an individual composite input port,
 * which may differ from platform capabilities if ports have varying features.
 */
class PortCapabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * Array of PortProperty enum values supported by this port.
   *
   * Includes both runtime status keys (e.g. SIGNAL_STRENGTH) and telemetry
   * metric keys (METRIC_*). May be a subset of PlatformCapabilities.supportedProperties
   * when ports differ. Values correspond to entries declared in the platform
   * HFP under ports[].supportedProperties.
   *
   * A port supports metrics if this array contains any METRIC_* key.
   */
  ::std::vector<::com::rdk::hal::compositeinput::PortProperty> supportedProperties;
  // @aidl-doc
  /**
   * Property metadata for this port's supported properties (optional).
   *
   * Array indices correspond to supportedProperties array.
   * May be null if metadata is not available.
   */
  ::std::optional<::std::vector<::std::optional<::com::rdk::hal::compositeinput::PropertyMetadata>>> propertyMetadata;
  inline bool operator!=(const PortCapabilities& rhs) const {
    return std::tie(supportedProperties, propertyMetadata) != std::tie(rhs.supportedProperties, rhs.propertyMetadata);
  }
  inline bool operator<(const PortCapabilities& rhs) const {
    return std::tie(supportedProperties, propertyMetadata) < std::tie(rhs.supportedProperties, rhs.propertyMetadata);
  }
  inline bool operator<=(const PortCapabilities& rhs) const {
    return std::tie(supportedProperties, propertyMetadata) <= std::tie(rhs.supportedProperties, rhs.propertyMetadata);
  }
  inline bool operator==(const PortCapabilities& rhs) const {
    return std::tie(supportedProperties, propertyMetadata) == std::tie(rhs.supportedProperties, rhs.propertyMetadata);
  }
  inline bool operator>(const PortCapabilities& rhs) const {
    return std::tie(supportedProperties, propertyMetadata) > std::tie(rhs.supportedProperties, rhs.propertyMetadata);
  }
  inline bool operator>=(const PortCapabilities& rhs) const {
    return std::tie(supportedProperties, propertyMetadata) >= std::tie(rhs.supportedProperties, rhs.propertyMetadata);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.compositeinput.PortCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PortCapabilities{";
    os << "supportedProperties: " << ::android::internal::ToString(supportedProperties);
    os << ", propertyMetadata: " << ::android::internal::ToString(propertyMetadata);
    os << "}";
    return os.str();
  }
};  // class PortCapabilities
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com

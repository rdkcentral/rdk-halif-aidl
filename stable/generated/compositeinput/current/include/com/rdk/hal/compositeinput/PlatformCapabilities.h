#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/compositeinput/PlatformCapabilities.h>
#include <com/rdk/hal/compositeinput/PortProperty.h>
#include <com/rdk/hal/compositeinput/PropertyMetadata.h>
#include <cstdint>
#include <optional>
#include <string>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
class PlatformCapabilities : public ::android::Parcelable {
public:
  class FeatureFlags : public ::android::Parcelable {
  public:
    bool macrovisionDetectionSupported = false;
    inline bool operator!=(const FeatureFlags& rhs) const {
      return std::tie(macrovisionDetectionSupported) != std::tie(rhs.macrovisionDetectionSupported);
    }
    inline bool operator<(const FeatureFlags& rhs) const {
      return std::tie(macrovisionDetectionSupported) < std::tie(rhs.macrovisionDetectionSupported);
    }
    inline bool operator<=(const FeatureFlags& rhs) const {
      return std::tie(macrovisionDetectionSupported) <= std::tie(rhs.macrovisionDetectionSupported);
    }
    inline bool operator==(const FeatureFlags& rhs) const {
      return std::tie(macrovisionDetectionSupported) == std::tie(rhs.macrovisionDetectionSupported);
    }
    inline bool operator>(const FeatureFlags& rhs) const {
      return std::tie(macrovisionDetectionSupported) > std::tie(rhs.macrovisionDetectionSupported);
    }
    inline bool operator>=(const FeatureFlags& rhs) const {
      return std::tie(macrovisionDetectionSupported) >= std::tie(rhs.macrovisionDetectionSupported);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.compositeinput.PlatformCapabilities.FeatureFlags");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "FeatureFlags{";
      os << "macrovisionDetectionSupported: " << ::android::internal::ToString(macrovisionDetectionSupported);
      os << "}";
      return os.str();
    }
  };  // class FeatureFlags
  ::std::string halVersion;
  int8_t maxPorts = 0;
  int32_t maximumConcurrentStartedPorts = 0;
  ::std::vector<::com::rdk::hal::compositeinput::PortProperty> supportedProperties;
  ::std::optional<::std::vector<::std::optional<::com::rdk::hal::compositeinput::PropertyMetadata>>> propertyMetadata;
  ::com::rdk::hal::compositeinput::PlatformCapabilities::FeatureFlags features;
  inline bool operator!=(const PlatformCapabilities& rhs) const {
    return std::tie(halVersion, maxPorts, maximumConcurrentStartedPorts, supportedProperties, propertyMetadata, features) != std::tie(rhs.halVersion, rhs.maxPorts, rhs.maximumConcurrentStartedPorts, rhs.supportedProperties, rhs.propertyMetadata, rhs.features);
  }
  inline bool operator<(const PlatformCapabilities& rhs) const {
    return std::tie(halVersion, maxPorts, maximumConcurrentStartedPorts, supportedProperties, propertyMetadata, features) < std::tie(rhs.halVersion, rhs.maxPorts, rhs.maximumConcurrentStartedPorts, rhs.supportedProperties, rhs.propertyMetadata, rhs.features);
  }
  inline bool operator<=(const PlatformCapabilities& rhs) const {
    return std::tie(halVersion, maxPorts, maximumConcurrentStartedPorts, supportedProperties, propertyMetadata, features) <= std::tie(rhs.halVersion, rhs.maxPorts, rhs.maximumConcurrentStartedPorts, rhs.supportedProperties, rhs.propertyMetadata, rhs.features);
  }
  inline bool operator==(const PlatformCapabilities& rhs) const {
    return std::tie(halVersion, maxPorts, maximumConcurrentStartedPorts, supportedProperties, propertyMetadata, features) == std::tie(rhs.halVersion, rhs.maxPorts, rhs.maximumConcurrentStartedPorts, rhs.supportedProperties, rhs.propertyMetadata, rhs.features);
  }
  inline bool operator>(const PlatformCapabilities& rhs) const {
    return std::tie(halVersion, maxPorts, maximumConcurrentStartedPorts, supportedProperties, propertyMetadata, features) > std::tie(rhs.halVersion, rhs.maxPorts, rhs.maximumConcurrentStartedPorts, rhs.supportedProperties, rhs.propertyMetadata, rhs.features);
  }
  inline bool operator>=(const PlatformCapabilities& rhs) const {
    return std::tie(halVersion, maxPorts, maximumConcurrentStartedPorts, supportedProperties, propertyMetadata, features) >= std::tie(rhs.halVersion, rhs.maxPorts, rhs.maximumConcurrentStartedPorts, rhs.supportedProperties, rhs.propertyMetadata, rhs.features);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.compositeinput.PlatformCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PlatformCapabilities{";
    os << "halVersion: " << ::android::internal::ToString(halVersion);
    os << ", maxPorts: " << ::android::internal::ToString(maxPorts);
    os << ", maximumConcurrentStartedPorts: " << ::android::internal::ToString(maximumConcurrentStartedPorts);
    os << ", supportedProperties: " << ::android::internal::ToString(supportedProperties);
    os << ", propertyMetadata: " << ::android::internal::ToString(propertyMetadata);
    os << ", features: " << ::android::internal::ToString(features);
    os << "}";
    return os.str();
  }
};  // class PlatformCapabilities
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com

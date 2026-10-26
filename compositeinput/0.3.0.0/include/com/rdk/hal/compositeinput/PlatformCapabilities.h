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
// @aidl-doc
/**
 * @brief Platform-wide capabilities for composite input.
 *
 * Describes the overall capabilities of the composite input subsystem,
 * including supported features, video standards, and available ports.
 */
class PlatformCapabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /** @brief Feature flags for optional functionality. */
  class FeatureFlags : public ::android::Parcelable {
  public:
    // @aidl-doc
    /** True if Macrovision copy protection detection is supported. */
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
  // @aidl-doc
  /** HAL version (semantic versioning, e.g., "1.0.0"). */
  ::std::string halVersion;
  // @aidl-doc
  /** Maximum number of ports supported. */
  int8_t maxPorts = 0;
  // @aidl-doc
  /**
   * Maximum number of ports that may be in STARTED state simultaneously.
   *
   * Declared by the platform in the HFP. Most platforms will set this to 1
   * (single active port). ICompositeInputController.start() throws
   * EX_ILLEGAL_STATE if this limit would be exceeded.
   */
  int32_t maximumConcurrentStartedPorts = 0;
  // @aidl-doc
  /**
   * Array of PortProperty enum values supported across the platform.
   *
   * Declared in the platform HFP. Includes both runtime status keys and
   * telemetry metric keys. Individual ports may support a subset (see
   * PortCapabilities.supportedProperties).
   */
  ::std::vector<::com::rdk::hal::compositeinput::PortProperty> supportedProperties;
  // @aidl-doc
  /**
   * Property metadata for all supported properties (optional).
   *
   * Provides type information and access flags for each property.
   * Array indices correspond to supportedProperties array.
   * May be null if metadata is not available.
   */
  ::std::optional<::std::vector<::std::optional<::com::rdk::hal::compositeinput::PropertyMetadata>>> propertyMetadata;
  // @aidl-doc
  /** Feature flags indicating optional capabilities. */
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

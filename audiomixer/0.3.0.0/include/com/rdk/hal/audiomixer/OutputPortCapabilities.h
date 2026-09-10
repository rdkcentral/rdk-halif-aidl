#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/AQProcessor.h>
#include <com/rdk/hal/audiomixer/OutputFormat.h>
#include <com/rdk/hal/audiomixer/OutputPortProperty.h>
#include <com/rdk/hal/audiomixer/OutputPortType.h>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class OutputPortCapabilities : public ::android::Parcelable {
public:
  ::android::String16 portName;
  ::com::rdk::hal::audiomixer::OutputPortType portType = ::com::rdk::hal::audiomixer::OutputPortType(0);
  ::std::vector<::com::rdk::hal::audiomixer::OutputPortProperty> supportedProperties;
  ::std::vector<::com::rdk::hal::audiomixer::OutputFormat> supportedOutputFormats;
  ::std::vector<::com::rdk::hal::audiomixer::AQProcessor> supportedAQProcessors;
  ::std::optional<::std::vector<::std::optional<::android::String16>>> dolbyMs12AudioProfiles;
  bool supportsAudioCapture = false;
  inline bool operator!=(const OutputPortCapabilities& rhs) const {
    return std::tie(portName, portType, supportedProperties, supportedOutputFormats, supportedAQProcessors, dolbyMs12AudioProfiles, supportsAudioCapture) != std::tie(rhs.portName, rhs.portType, rhs.supportedProperties, rhs.supportedOutputFormats, rhs.supportedAQProcessors, rhs.dolbyMs12AudioProfiles, rhs.supportsAudioCapture);
  }
  inline bool operator<(const OutputPortCapabilities& rhs) const {
    return std::tie(portName, portType, supportedProperties, supportedOutputFormats, supportedAQProcessors, dolbyMs12AudioProfiles, supportsAudioCapture) < std::tie(rhs.portName, rhs.portType, rhs.supportedProperties, rhs.supportedOutputFormats, rhs.supportedAQProcessors, rhs.dolbyMs12AudioProfiles, rhs.supportsAudioCapture);
  }
  inline bool operator<=(const OutputPortCapabilities& rhs) const {
    return std::tie(portName, portType, supportedProperties, supportedOutputFormats, supportedAQProcessors, dolbyMs12AudioProfiles, supportsAudioCapture) <= std::tie(rhs.portName, rhs.portType, rhs.supportedProperties, rhs.supportedOutputFormats, rhs.supportedAQProcessors, rhs.dolbyMs12AudioProfiles, rhs.supportsAudioCapture);
  }
  inline bool operator==(const OutputPortCapabilities& rhs) const {
    return std::tie(portName, portType, supportedProperties, supportedOutputFormats, supportedAQProcessors, dolbyMs12AudioProfiles, supportsAudioCapture) == std::tie(rhs.portName, rhs.portType, rhs.supportedProperties, rhs.supportedOutputFormats, rhs.supportedAQProcessors, rhs.dolbyMs12AudioProfiles, rhs.supportsAudioCapture);
  }
  inline bool operator>(const OutputPortCapabilities& rhs) const {
    return std::tie(portName, portType, supportedProperties, supportedOutputFormats, supportedAQProcessors, dolbyMs12AudioProfiles, supportsAudioCapture) > std::tie(rhs.portName, rhs.portType, rhs.supportedProperties, rhs.supportedOutputFormats, rhs.supportedAQProcessors, rhs.dolbyMs12AudioProfiles, rhs.supportsAudioCapture);
  }
  inline bool operator>=(const OutputPortCapabilities& rhs) const {
    return std::tie(portName, portType, supportedProperties, supportedOutputFormats, supportedAQProcessors, dolbyMs12AudioProfiles, supportsAudioCapture) >= std::tie(rhs.portName, rhs.portType, rhs.supportedProperties, rhs.supportedOutputFormats, rhs.supportedAQProcessors, rhs.dolbyMs12AudioProfiles, rhs.supportsAudioCapture);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiomixer.OutputPortCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "OutputPortCapabilities{";
    os << "portName: " << ::android::internal::ToString(portName);
    os << ", portType: " << ::android::internal::ToString(portType);
    os << ", supportedProperties: " << ::android::internal::ToString(supportedProperties);
    os << ", supportedOutputFormats: " << ::android::internal::ToString(supportedOutputFormats);
    os << ", supportedAQProcessors: " << ::android::internal::ToString(supportedAQProcessors);
    os << ", dolbyMs12AudioProfiles: " << ::android::internal::ToString(dolbyMs12AudioProfiles);
    os << ", supportsAudioCapture: " << ::android::internal::ToString(supportsAudioCapture);
    os << "}";
    return os.str();
  }
};  // class OutputPortCapabilities
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com

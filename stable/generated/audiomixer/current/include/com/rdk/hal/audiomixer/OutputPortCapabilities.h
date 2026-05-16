#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/AQParameter.h>
#include <com/rdk/hal/audiomixer/AQProcessor.h>
#include <com/rdk/hal/audiomixer/OutputFormat.h>
#include <com/rdk/hal/audiomixer/OutputPortProperty.h>
#include <com/rdk/hal/audiomixer/TranscodeFormat.h>
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
  ::std::optional<::android::String16> portName;
  ::std::vector<::com::rdk::hal::audiomixer::OutputPortProperty> supportedProperties;
  ::std::vector<::com::rdk::hal::audiomixer::OutputFormat> supportedOutputFormats;
  ::std::vector<::com::rdk::hal::audiomixer::TranscodeFormat> supportedTranscodeFormats;
  ::std::vector<::com::rdk::hal::audiomixer::AQProcessor> supportedAQProcessors;
  ::std::vector<::com::rdk::hal::audiomixer::AQParameter> supportedAQ;
  inline bool operator!=(const OutputPortCapabilities& rhs) const {
    return std::tie(portName, supportedProperties, supportedOutputFormats, supportedTranscodeFormats, supportedAQProcessors, supportedAQ) != std::tie(rhs.portName, rhs.supportedProperties, rhs.supportedOutputFormats, rhs.supportedTranscodeFormats, rhs.supportedAQProcessors, rhs.supportedAQ);
  }
  inline bool operator<(const OutputPortCapabilities& rhs) const {
    return std::tie(portName, supportedProperties, supportedOutputFormats, supportedTranscodeFormats, supportedAQProcessors, supportedAQ) < std::tie(rhs.portName, rhs.supportedProperties, rhs.supportedOutputFormats, rhs.supportedTranscodeFormats, rhs.supportedAQProcessors, rhs.supportedAQ);
  }
  inline bool operator<=(const OutputPortCapabilities& rhs) const {
    return std::tie(portName, supportedProperties, supportedOutputFormats, supportedTranscodeFormats, supportedAQProcessors, supportedAQ) <= std::tie(rhs.portName, rhs.supportedProperties, rhs.supportedOutputFormats, rhs.supportedTranscodeFormats, rhs.supportedAQProcessors, rhs.supportedAQ);
  }
  inline bool operator==(const OutputPortCapabilities& rhs) const {
    return std::tie(portName, supportedProperties, supportedOutputFormats, supportedTranscodeFormats, supportedAQProcessors, supportedAQ) == std::tie(rhs.portName, rhs.supportedProperties, rhs.supportedOutputFormats, rhs.supportedTranscodeFormats, rhs.supportedAQProcessors, rhs.supportedAQ);
  }
  inline bool operator>(const OutputPortCapabilities& rhs) const {
    return std::tie(portName, supportedProperties, supportedOutputFormats, supportedTranscodeFormats, supportedAQProcessors, supportedAQ) > std::tie(rhs.portName, rhs.supportedProperties, rhs.supportedOutputFormats, rhs.supportedTranscodeFormats, rhs.supportedAQProcessors, rhs.supportedAQ);
  }
  inline bool operator>=(const OutputPortCapabilities& rhs) const {
    return std::tie(portName, supportedProperties, supportedOutputFormats, supportedTranscodeFormats, supportedAQProcessors, supportedAQ) >= std::tie(rhs.portName, rhs.supportedProperties, rhs.supportedOutputFormats, rhs.supportedTranscodeFormats, rhs.supportedAQProcessors, rhs.supportedAQ);
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
    os << ", supportedProperties: " << ::android::internal::ToString(supportedProperties);
    os << ", supportedOutputFormats: " << ::android::internal::ToString(supportedOutputFormats);
    os << ", supportedTranscodeFormats: " << ::android::internal::ToString(supportedTranscodeFormats);
    os << ", supportedAQProcessors: " << ::android::internal::ToString(supportedAQProcessors);
    os << ", supportedAQ: " << ::android::internal::ToString(supportedAQ);
    os << "}";
    return os.str();
  }
};  // class OutputPortCapabilities
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com

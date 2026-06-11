#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/AudioCapturePcmInfo.h>
#include <com/rdk/hal/audiomixer/OutputFormat.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class AudioCaptureData : public ::android::Parcelable {
public:
  int32_t channels = 0;
  int32_t sampleRateHz = 0;
  int64_t timestampUs = 0L;
  ::com::rdk::hal::audiomixer::OutputFormat format = ::com::rdk::hal::audiomixer::OutputFormat(0);
  ::std::optional<::android::String16> codecName;
  ::std::optional<::com::rdk::hal::audiomixer::AudioCapturePcmInfo> pcmInfo;
  inline bool operator!=(const AudioCaptureData& rhs) const {
    return std::tie(channels, sampleRateHz, timestampUs, format, codecName, pcmInfo) != std::tie(rhs.channels, rhs.sampleRateHz, rhs.timestampUs, rhs.format, rhs.codecName, rhs.pcmInfo);
  }
  inline bool operator<(const AudioCaptureData& rhs) const {
    return std::tie(channels, sampleRateHz, timestampUs, format, codecName, pcmInfo) < std::tie(rhs.channels, rhs.sampleRateHz, rhs.timestampUs, rhs.format, rhs.codecName, rhs.pcmInfo);
  }
  inline bool operator<=(const AudioCaptureData& rhs) const {
    return std::tie(channels, sampleRateHz, timestampUs, format, codecName, pcmInfo) <= std::tie(rhs.channels, rhs.sampleRateHz, rhs.timestampUs, rhs.format, rhs.codecName, rhs.pcmInfo);
  }
  inline bool operator==(const AudioCaptureData& rhs) const {
    return std::tie(channels, sampleRateHz, timestampUs, format, codecName, pcmInfo) == std::tie(rhs.channels, rhs.sampleRateHz, rhs.timestampUs, rhs.format, rhs.codecName, rhs.pcmInfo);
  }
  inline bool operator>(const AudioCaptureData& rhs) const {
    return std::tie(channels, sampleRateHz, timestampUs, format, codecName, pcmInfo) > std::tie(rhs.channels, rhs.sampleRateHz, rhs.timestampUs, rhs.format, rhs.codecName, rhs.pcmInfo);
  }
  inline bool operator>=(const AudioCaptureData& rhs) const {
    return std::tie(channels, sampleRateHz, timestampUs, format, codecName, pcmInfo) >= std::tie(rhs.channels, rhs.sampleRateHz, rhs.timestampUs, rhs.format, rhs.codecName, rhs.pcmInfo);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiomixer.AudioCaptureData");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "AudioCaptureData{";
    os << "channels: " << ::android::internal::ToString(channels);
    os << ", sampleRateHz: " << ::android::internal::ToString(sampleRateHz);
    os << ", timestampUs: " << ::android::internal::ToString(timestampUs);
    os << ", format: " << ::android::internal::ToString(format);
    os << ", codecName: " << ::android::internal::ToString(codecName);
    os << ", pcmInfo: " << ::android::internal::ToString(pcmInfo);
    os << "}";
    return os.str();
  }
};  // class AudioCaptureData
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com

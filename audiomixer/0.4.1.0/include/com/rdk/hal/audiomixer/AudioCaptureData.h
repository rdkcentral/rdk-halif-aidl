#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/AudioCapturePcmInfo.h>
#include <com/rdk/hal/audiomixer/OutputFormat.h>
#include <cstdint>
#include <optional>
#include <string>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
// @aidl-doc
/**
 * @brief Audio capture data frame with metadata.
 * Encapsulates metadata for a single audio frame stored in shared-memory ring buffer.
 *
 * The data captured by the Audio Capture interface is the same as the data output by the port.
 * When a capture port provides a capture interface for a physical output (e.g. HDMI, Speakers, etc.)
 * then the captured data is a copy.
 */
class AudioCaptureData : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Number of audio channels (e.g., 1 for mono, 2 for stereo, 6 for 5.1 surround). */
  int32_t channels = 0;
  // @aidl-doc
  /** Audio sample rate in Hertz (e.g., 48000, 96000). */
  int32_t sampleRateHz = 0;
  // @aidl-doc
  /**
   * Timestamp in microseconds (μs) from the system monotonic clock.
   * This value shall use a single monotonic time base for all implementations and
   * shall not be frame-relative.
   */
  int64_t timestampUs = 0L;
  // @aidl-doc
  /** Format of captured audio. */
  ::com::rdk::hal::audiomixer::OutputFormat format = ::com::rdk::hal::audiomixer::OutputFormat(0);
  // @aidl-doc
  /**
   * Human-readable codec name (e.g., "AC3", "AAC", "PCM", "AAC-LC").
   * Populated only when relevant to the captured format, null otherwise.
   * codecName is purely informative and intended only for diagnostic purposes.
   * Do not rely on the string value for logical operations.
   */
  ::std::optional<::std::string> codecName;
  // @aidl-doc
  /**
   * PCM sample encoding details (bit depth, signedness, byte order).
   * Populated only when format is OutputFormat.PCM_STEREO or
   * OutputFormat.PCM_MULTICHANNEL, null otherwise.
   */
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

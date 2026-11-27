#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/Channel.h>
#include <com/rdk/hal/audiomixer/ImmersiveFormat.h>
#include <com/rdk/hal/audiomixer/OutputFormat.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
// @aidl-doc
/**
 * @brief    The audio an output port is emitting now.
 * @details  Read with IAudioOutputPort.getActiveOutputFormat() and delivered
 *           whole by IAudioOutputPortListener.onActiveOutputFormatChanged().
 *           Every field describes the same instant: one negotiated change is
 *           one event, so a client never sees a mix of old and new values.
 *
 *           The configured value stays in OutputPortProperty.OUTPUT_FORMAT
 *           (which may be AUTO or PASSTHROUGH); this parcelable is what that
 *           configuration resolved to against the current source and sink.
 *
 *           Each output port reports independently. At the same moment HDMI
 *           may carry MAT with Dolby Atmos, SPDIF AC3 5.1 and the speakers
 *           PCM rendered from the same Atmos source.
 *
 * @author    Gerald Weatherup
 * @copyright Copyright 2026 RDK Management
 */
class ActiveOutputFormat : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * The format on the wire. Never AUTO or PASSTHROUGH: a passthrough
   * bitstream reports its own format (e.g. EAC3) with isPassthrough true.
   *
   * A BLUETOOTH port reports the PCM handed to the A2DP encoder
   * (PCM_STEREO or PCM_MULTICHANNEL). The A2DP codec (SBC, AAC, aptX,
   * LDAC) is negotiated on the link and is not an OutputFormat.
   */
  ::com::rdk::hal::audiomixer::OutputFormat format = ::com::rdk::hal::audiomixer::OutputFormat(0);
  // @aidl-doc
  /**
   * True when the source bitstream is sent unchanged; false when the HAL
   * decoded, mixed, transcoded or encoded it.
   */
  bool isPassthrough = false;
  // @aidl-doc
  /** Sample rate in Hz (e.g. 48000). */
  int32_t sampleRateHz = 0;
  // @aidl-doc
  /**
   * Channel positions in frame order. The array length is the channel
   * count, LFE included. For a bitstream format this is the coded bed
   * (e.g. 7.1 for a MAT Atmos stream), not the immersive objects.
   */
  ::std::vector<::com::rdk::hal::audiomixer::Channel> channelMap;
  // @aidl-doc
  /**
   * Immersive content carried or rendered on this port.
   * NONE when a port that cannot carry immersive audio receives it: the
   * HAL emits the channel bed or a downmix, and does not report an error.
   */
  ::com::rdk::hal::audiomixer::ImmersiveFormat immersive = ::com::rdk::hal::audiomixer::ImmersiveFormat(0);
  inline bool operator!=(const ActiveOutputFormat& rhs) const {
    return std::tie(format, isPassthrough, sampleRateHz, channelMap, immersive) != std::tie(rhs.format, rhs.isPassthrough, rhs.sampleRateHz, rhs.channelMap, rhs.immersive);
  }
  inline bool operator<(const ActiveOutputFormat& rhs) const {
    return std::tie(format, isPassthrough, sampleRateHz, channelMap, immersive) < std::tie(rhs.format, rhs.isPassthrough, rhs.sampleRateHz, rhs.channelMap, rhs.immersive);
  }
  inline bool operator<=(const ActiveOutputFormat& rhs) const {
    return std::tie(format, isPassthrough, sampleRateHz, channelMap, immersive) <= std::tie(rhs.format, rhs.isPassthrough, rhs.sampleRateHz, rhs.channelMap, rhs.immersive);
  }
  inline bool operator==(const ActiveOutputFormat& rhs) const {
    return std::tie(format, isPassthrough, sampleRateHz, channelMap, immersive) == std::tie(rhs.format, rhs.isPassthrough, rhs.sampleRateHz, rhs.channelMap, rhs.immersive);
  }
  inline bool operator>(const ActiveOutputFormat& rhs) const {
    return std::tie(format, isPassthrough, sampleRateHz, channelMap, immersive) > std::tie(rhs.format, rhs.isPassthrough, rhs.sampleRateHz, rhs.channelMap, rhs.immersive);
  }
  inline bool operator>=(const ActiveOutputFormat& rhs) const {
    return std::tie(format, isPassthrough, sampleRateHz, channelMap, immersive) >= std::tie(rhs.format, rhs.isPassthrough, rhs.sampleRateHz, rhs.channelMap, rhs.immersive);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiomixer.ActiveOutputFormat");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "ActiveOutputFormat{";
    os << "format: " << ::android::internal::ToString(format);
    os << ", isPassthrough: " << ::android::internal::ToString(isPassthrough);
    os << ", sampleRateHz: " << ::android::internal::ToString(sampleRateHz);
    os << ", channelMap: " << ::android::internal::ToString(channelMap);
    os << ", immersive: " << ::android::internal::ToString(immersive);
    os << "}";
    return os.str();
  }
};  // class ActiveOutputFormat
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com

#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/Channel.h>
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
 * @brief PCM sample format descriptor for captured audio.
 *
 * Describes the binary encoding of PCM samples within an AudioCaptureData frame.
 * Only populated when AudioCaptureData.format is PCM_STEREO or PCM_MULTICHANNEL.
 */
class AudioCapturePcmInfo : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Number of significant bits per PCM sample (e.g., 16, 24, 32). */
  int32_t bitsPerSample = 0;
  // @aidl-doc
  /**
   * Container word size in bits that each sample is packed into (e.g., 32).
   * When equal to bitsPerSample, samples are tightly packed with no padding.
   * When greater (e.g., bitsPerSample=24, containerBitsPerSample=32), each sample
   * occupies a larger container word with the unused bits padded to zero.
   */
  int32_t containerBitsPerSample = 0;
  // @aidl-doc
  /**
   * True if samples are signed integers; false if unsigned.
   * Signed is typical for 16-bit and 32-bit PCM. 8-bit PCM is commonly unsigned.
   */
  bool isSigned = false;
  // @aidl-doc
  /**
   * True if sample bytes are in little-endian order; false for big-endian.
   * Little-endian is standard on x86/ARM platforms.
   */
  bool isLittleEndian = false;
  // @aidl-doc
  /**
   * @brief Channel position map for multi-channel PCM audio.
   *
   * Channel positions in captured PCM frame order.
   * The array index represents the channel number (0-based), and the Channel enum value
   * at that index indicates the physical or logical placement of that channel.
   *
   * Populated when AudioCaptureData.format is PCM_MULTICHANNEL or PCM_STEREO.
   * For PCM_STEREO, this array contains two entries: [CH_FL, CH_FR].
   *
   * Example for 5.1 surround (Left, Right, Centre, LFE, Rear Left, Rear Right):
   * [CH_FL, CH_FR, CH_FC, CH_LFE, CH_RL, CH_RR]
   */
  ::std::vector<::com::rdk::hal::audiomixer::Channel> channelMap;
  inline bool operator!=(const AudioCapturePcmInfo& rhs) const {
    return std::tie(bitsPerSample, containerBitsPerSample, isSigned, isLittleEndian, channelMap) != std::tie(rhs.bitsPerSample, rhs.containerBitsPerSample, rhs.isSigned, rhs.isLittleEndian, rhs.channelMap);
  }
  inline bool operator<(const AudioCapturePcmInfo& rhs) const {
    return std::tie(bitsPerSample, containerBitsPerSample, isSigned, isLittleEndian, channelMap) < std::tie(rhs.bitsPerSample, rhs.containerBitsPerSample, rhs.isSigned, rhs.isLittleEndian, rhs.channelMap);
  }
  inline bool operator<=(const AudioCapturePcmInfo& rhs) const {
    return std::tie(bitsPerSample, containerBitsPerSample, isSigned, isLittleEndian, channelMap) <= std::tie(rhs.bitsPerSample, rhs.containerBitsPerSample, rhs.isSigned, rhs.isLittleEndian, rhs.channelMap);
  }
  inline bool operator==(const AudioCapturePcmInfo& rhs) const {
    return std::tie(bitsPerSample, containerBitsPerSample, isSigned, isLittleEndian, channelMap) == std::tie(rhs.bitsPerSample, rhs.containerBitsPerSample, rhs.isSigned, rhs.isLittleEndian, rhs.channelMap);
  }
  inline bool operator>(const AudioCapturePcmInfo& rhs) const {
    return std::tie(bitsPerSample, containerBitsPerSample, isSigned, isLittleEndian, channelMap) > std::tie(rhs.bitsPerSample, rhs.containerBitsPerSample, rhs.isSigned, rhs.isLittleEndian, rhs.channelMap);
  }
  inline bool operator>=(const AudioCapturePcmInfo& rhs) const {
    return std::tie(bitsPerSample, containerBitsPerSample, isSigned, isLittleEndian, channelMap) >= std::tie(rhs.bitsPerSample, rhs.containerBitsPerSample, rhs.isSigned, rhs.isLittleEndian, rhs.channelMap);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiomixer.AudioCapturePcmInfo");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "AudioCapturePcmInfo{";
    os << "bitsPerSample: " << ::android::internal::ToString(bitsPerSample);
    os << ", containerBitsPerSample: " << ::android::internal::ToString(containerBitsPerSample);
    os << ", isSigned: " << ::android::internal::ToString(isSigned);
    os << ", isLittleEndian: " << ::android::internal::ToString(isLittleEndian);
    os << ", channelMap: " << ::android::internal::ToString(channelMap);
    os << "}";
    return os.str();
  }
};  // class AudioCapturePcmInfo
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com

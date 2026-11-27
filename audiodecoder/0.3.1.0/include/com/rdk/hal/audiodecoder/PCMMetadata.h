#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiodecoder/ChannelType.h>
#include <com/rdk/hal/audiodecoder/PCMFormat.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
// @aidl-doc
/**
 *  @brief     PCM Audio frame metadata.
 *
 *  The format fields on this parcelable - numChannels, channelTypes,
 *  sampleRate, format and planarFormat - describe the frame whose
 *  FrameMetadata carried it, and that format remains in effect for later
 *  frames until new metadata is delivered.
 *
 *  Frame metadata is delivered with the first decoded frame after start(),
 *  the first after flush(), and whenever it changes. Where the decoder
 *  absorbs an in-codec format change mid-stream, the first frame produced
 *  under the new format therefore carries a non-null FrameMetadata whose
 *  `metadata` field holds a PCMMetadata with the updated numChannels /
 *  channelTypes / sampleRate. That delivery is the
 *  only format-change notification: there is no out-of-band signal, and
 *  the client is not required to act before it arrives.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class PCMMetadata : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * Number of audio channels in this frame.
   *
   * Reflects the format of THIS frame. On an in-codec format change the
   * value updates on the first frame produced under the new format,
   * and stays in effect until new metadata is delivered.
   */
  int32_t numChannels = 0;
  // @aidl-doc
  /**
   * Array of ChannelType enum values for this frame.
   * The array size should match the number of channels.
   *
   * Reflects the format of THIS frame. Updates on the first frame
   * produced after an in-codec channel-layout change.
   */
  ::std::vector<::com::rdk::hal::audiodecoder::ChannelType> channelTypes;
  // @aidl-doc
  /**
   * Sample rate in samples/second for this frame.
   *
   * Reflects the format of THIS frame. On an in-codec format change the
   * value updates on the first frame produced under the new format,
   * and stays in effect until new metadata is delivered.
   */
  int32_t sampleRate = 0;
  // @aidl-doc
  /** Format of the output PCM data. */
  ::com::rdk::hal::audiodecoder::PCMFormat format = ::com::rdk::hal::audiodecoder::PCMFormat(0);
  // @aidl-doc
  /**
   * Indicates whether the audio data buffer is in planar format.
   * If false, the data is interleaved with other channels.
   */
  bool planarFormat = false;
  // @aidl-doc
  /** Private extension for future use. */
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const PCMMetadata& rhs) const {
    return std::tie(numChannels, channelTypes, sampleRate, format, planarFormat, extension) != std::tie(rhs.numChannels, rhs.channelTypes, rhs.sampleRate, rhs.format, rhs.planarFormat, rhs.extension);
  }
  inline bool operator<(const PCMMetadata& rhs) const {
    return std::tie(numChannels, channelTypes, sampleRate, format, planarFormat, extension) < std::tie(rhs.numChannels, rhs.channelTypes, rhs.sampleRate, rhs.format, rhs.planarFormat, rhs.extension);
  }
  inline bool operator<=(const PCMMetadata& rhs) const {
    return std::tie(numChannels, channelTypes, sampleRate, format, planarFormat, extension) <= std::tie(rhs.numChannels, rhs.channelTypes, rhs.sampleRate, rhs.format, rhs.planarFormat, rhs.extension);
  }
  inline bool operator==(const PCMMetadata& rhs) const {
    return std::tie(numChannels, channelTypes, sampleRate, format, planarFormat, extension) == std::tie(rhs.numChannels, rhs.channelTypes, rhs.sampleRate, rhs.format, rhs.planarFormat, rhs.extension);
  }
  inline bool operator>(const PCMMetadata& rhs) const {
    return std::tie(numChannels, channelTypes, sampleRate, format, planarFormat, extension) > std::tie(rhs.numChannels, rhs.channelTypes, rhs.sampleRate, rhs.format, rhs.planarFormat, rhs.extension);
  }
  inline bool operator>=(const PCMMetadata& rhs) const {
    return std::tie(numChannels, channelTypes, sampleRate, format, planarFormat, extension) >= std::tie(rhs.numChannels, rhs.channelTypes, rhs.sampleRate, rhs.format, rhs.planarFormat, rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiodecoder.PCMMetadata");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PCMMetadata{";
    os << "numChannels: " << ::android::internal::ToString(numChannels);
    os << ", channelTypes: " << ::android::internal::ToString(channelTypes);
    os << ", sampleRate: " << ::android::internal::ToString(sampleRate);
    os << ", format: " << ::android::internal::ToString(format);
    os << ", planarFormat: " << ::android::internal::ToString(planarFormat);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class PCMMetadata
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com

#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiodecoder/PCMFormat.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
// @aidl-doc
/**
 *  @brief     Audio sink platform capabilities definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class PlatformCapabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Indicates the platform support for low latency audio. */
  bool supportsLowLatency = false;
  // @aidl-doc
  /**
   * Supported PCM input sample rates in Hz.
   * Every listed rate is accepted with every listed format.
   */
  ::std::vector<int32_t> supportedSampleRatesHz;
  // @aidl-doc
  /**
   * Supported PCM input formats.
   * Every listed format is accepted with every listed rate.
   */
  ::std::vector<::com::rdk::hal::audiodecoder::PCMFormat> supportedPCMFormats;
  // @aidl-doc
  /**
   * Indicated support for planar format of audio data buffers
   * where the audio samples for each channel are delivered
   * together in one plane, rather than interleaved with all other channels.
   */
  bool supportsPlanarFormat = false;
  // @aidl-doc
  /**
   * Indicates support for a SoC proprietary audio data format.
   * The Audio decoder can output a completely proprietary audio format that is opaque to the MW.
   * Where this is the case the SoCProprietary boolean will be set in the FrameMeta returned by the Audio decoder
   * and the frames should be queued on the sink with the same metadata flag set.
   * When SoCProprietary is set the Audio decoder HAL passes audio metadata to the Audio sink HAL using proprietary
   * methods. For convenience the SoC HAL implementation can use the SoCPrivate field in the FrameMetadata to pass
   * opaque metadata between decoder and sink.
   *
   * The MW need only pass the AVBuffer to the sink and must assume that the data format is compatible between decoder
   * and sink.
   */
  bool supportsSoCProprietary = false;
  // @aidl-doc
  /** Indicates the maximum number of channels that can be supported by the Audio sink */
  int32_t maxNumChannels = 0;
  // @aidl-doc
  /** Indicates support for Dolby Atmos audio and metadata. */
  bool supportsDolbyAtmos = false;
  inline bool operator!=(const PlatformCapabilities& rhs) const {
    return std::tie(supportsLowLatency, supportedSampleRatesHz, supportedPCMFormats, supportsPlanarFormat, supportsSoCProprietary, maxNumChannels, supportsDolbyAtmos) != std::tie(rhs.supportsLowLatency, rhs.supportedSampleRatesHz, rhs.supportedPCMFormats, rhs.supportsPlanarFormat, rhs.supportsSoCProprietary, rhs.maxNumChannels, rhs.supportsDolbyAtmos);
  }
  inline bool operator<(const PlatformCapabilities& rhs) const {
    return std::tie(supportsLowLatency, supportedSampleRatesHz, supportedPCMFormats, supportsPlanarFormat, supportsSoCProprietary, maxNumChannels, supportsDolbyAtmos) < std::tie(rhs.supportsLowLatency, rhs.supportedSampleRatesHz, rhs.supportedPCMFormats, rhs.supportsPlanarFormat, rhs.supportsSoCProprietary, rhs.maxNumChannels, rhs.supportsDolbyAtmos);
  }
  inline bool operator<=(const PlatformCapabilities& rhs) const {
    return std::tie(supportsLowLatency, supportedSampleRatesHz, supportedPCMFormats, supportsPlanarFormat, supportsSoCProprietary, maxNumChannels, supportsDolbyAtmos) <= std::tie(rhs.supportsLowLatency, rhs.supportedSampleRatesHz, rhs.supportedPCMFormats, rhs.supportsPlanarFormat, rhs.supportsSoCProprietary, rhs.maxNumChannels, rhs.supportsDolbyAtmos);
  }
  inline bool operator==(const PlatformCapabilities& rhs) const {
    return std::tie(supportsLowLatency, supportedSampleRatesHz, supportedPCMFormats, supportsPlanarFormat, supportsSoCProprietary, maxNumChannels, supportsDolbyAtmos) == std::tie(rhs.supportsLowLatency, rhs.supportedSampleRatesHz, rhs.supportedPCMFormats, rhs.supportsPlanarFormat, rhs.supportsSoCProprietary, rhs.maxNumChannels, rhs.supportsDolbyAtmos);
  }
  inline bool operator>(const PlatformCapabilities& rhs) const {
    return std::tie(supportsLowLatency, supportedSampleRatesHz, supportedPCMFormats, supportsPlanarFormat, supportsSoCProprietary, maxNumChannels, supportsDolbyAtmos) > std::tie(rhs.supportsLowLatency, rhs.supportedSampleRatesHz, rhs.supportedPCMFormats, rhs.supportsPlanarFormat, rhs.supportsSoCProprietary, rhs.maxNumChannels, rhs.supportsDolbyAtmos);
  }
  inline bool operator>=(const PlatformCapabilities& rhs) const {
    return std::tie(supportsLowLatency, supportedSampleRatesHz, supportedPCMFormats, supportsPlanarFormat, supportsSoCProprietary, maxNumChannels, supportsDolbyAtmos) >= std::tie(rhs.supportsLowLatency, rhs.supportedSampleRatesHz, rhs.supportedPCMFormats, rhs.supportsPlanarFormat, rhs.supportsSoCProprietary, rhs.maxNumChannels, rhs.supportsDolbyAtmos);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiosink.PlatformCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PlatformCapabilities{";
    os << "supportsLowLatency: " << ::android::internal::ToString(supportsLowLatency);
    os << ", supportedSampleRatesHz: " << ::android::internal::ToString(supportedSampleRatesHz);
    os << ", supportedPCMFormats: " << ::android::internal::ToString(supportedPCMFormats);
    os << ", supportsPlanarFormat: " << ::android::internal::ToString(supportsPlanarFormat);
    os << ", supportsSoCProprietary: " << ::android::internal::ToString(supportsSoCProprietary);
    os << ", maxNumChannels: " << ::android::internal::ToString(maxNumChannels);
    os << ", supportsDolbyAtmos: " << ::android::internal::ToString(supportsDolbyAtmos);
    os << "}";
    return os.str();
  }
};  // class PlatformCapabilities
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com

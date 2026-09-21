#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/videodecoder/Colorimetry.h>
#include <com/rdk/hal/videodecoder/ContentLightLevel.h>
#include <com/rdk/hal/videodecoder/DolbyVisionLayerFlags.h>
#include <com/rdk/hal/videodecoder/Fraction.h>
#include <com/rdk/hal/videodecoder/MasteringDisplayInfo.h>
#include <com/rdk/hal/videodecoder/Resolution.h>
#include <optional>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
class VideoDecoderStreamConfig : public ::android::Parcelable {
public:
  ::std::optional<::com::rdk::hal::videodecoder::Resolution> resolution;
  ::std::optional<::com::rdk::hal::videodecoder::Fraction> frameRate;
  ::std::optional<::com::rdk::hal::videodecoder::Fraction> pixelAspectRatio;
  ::std::optional<::com::rdk::hal::videodecoder::Colorimetry> colorimetry;
  ::std::optional<::com::rdk::hal::videodecoder::MasteringDisplayInfo> masteringDisplayInfo;
  ::std::optional<::com::rdk::hal::videodecoder::ContentLightLevel> contentLightLevel;
  ::std::optional<::com::rdk::hal::videodecoder::DolbyVisionLayerFlags> dolbyVisionLayerFlags;
  inline bool operator!=(const VideoDecoderStreamConfig& rhs) const {
    return std::tie(resolution, frameRate, pixelAspectRatio, colorimetry, masteringDisplayInfo, contentLightLevel, dolbyVisionLayerFlags) != std::tie(rhs.resolution, rhs.frameRate, rhs.pixelAspectRatio, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.dolbyVisionLayerFlags);
  }
  inline bool operator<(const VideoDecoderStreamConfig& rhs) const {
    return std::tie(resolution, frameRate, pixelAspectRatio, colorimetry, masteringDisplayInfo, contentLightLevel, dolbyVisionLayerFlags) < std::tie(rhs.resolution, rhs.frameRate, rhs.pixelAspectRatio, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.dolbyVisionLayerFlags);
  }
  inline bool operator<=(const VideoDecoderStreamConfig& rhs) const {
    return std::tie(resolution, frameRate, pixelAspectRatio, colorimetry, masteringDisplayInfo, contentLightLevel, dolbyVisionLayerFlags) <= std::tie(rhs.resolution, rhs.frameRate, rhs.pixelAspectRatio, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.dolbyVisionLayerFlags);
  }
  inline bool operator==(const VideoDecoderStreamConfig& rhs) const {
    return std::tie(resolution, frameRate, pixelAspectRatio, colorimetry, masteringDisplayInfo, contentLightLevel, dolbyVisionLayerFlags) == std::tie(rhs.resolution, rhs.frameRate, rhs.pixelAspectRatio, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.dolbyVisionLayerFlags);
  }
  inline bool operator>(const VideoDecoderStreamConfig& rhs) const {
    return std::tie(resolution, frameRate, pixelAspectRatio, colorimetry, masteringDisplayInfo, contentLightLevel, dolbyVisionLayerFlags) > std::tie(rhs.resolution, rhs.frameRate, rhs.pixelAspectRatio, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.dolbyVisionLayerFlags);
  }
  inline bool operator>=(const VideoDecoderStreamConfig& rhs) const {
    return std::tie(resolution, frameRate, pixelAspectRatio, colorimetry, masteringDisplayInfo, contentLightLevel, dolbyVisionLayerFlags) >= std::tie(rhs.resolution, rhs.frameRate, rhs.pixelAspectRatio, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.dolbyVisionLayerFlags);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.videodecoder.VideoDecoderStreamConfig");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "VideoDecoderStreamConfig{";
    os << "resolution: " << ::android::internal::ToString(resolution);
    os << ", frameRate: " << ::android::internal::ToString(frameRate);
    os << ", pixelAspectRatio: " << ::android::internal::ToString(pixelAspectRatio);
    os << ", colorimetry: " << ::android::internal::ToString(colorimetry);
    os << ", masteringDisplayInfo: " << ::android::internal::ToString(masteringDisplayInfo);
    os << ", contentLightLevel: " << ::android::internal::ToString(contentLightLevel);
    os << ", dolbyVisionLayerFlags: " << ::android::internal::ToString(dolbyVisionLayerFlags);
    os << "}";
    return os.str();
  }
};  // class VideoDecoderStreamConfig
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com

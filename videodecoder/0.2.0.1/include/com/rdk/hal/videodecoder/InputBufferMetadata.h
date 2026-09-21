#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/videodecoder/Colorimetry.h>
#include <com/rdk/hal/videodecoder/ContentLightLevel.h>
#include <com/rdk/hal/videodecoder/DolbyVisionLayerFlags.h>
#include <com/rdk/hal/videodecoder/Fraction.h>
#include <com/rdk/hal/videodecoder/MasteringDisplayInfo.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
class InputBufferMetadata : public ::android::Parcelable {
public:
  int64_t nsPresentationTime = 0L;
  bool discontinuity = false;
  ::std::optional<::com::rdk::hal::videodecoder::Colorimetry> colorimetry;
  ::std::optional<::com::rdk::hal::videodecoder::MasteringDisplayInfo> masteringDisplayInfo;
  ::std::optional<::com::rdk::hal::videodecoder::ContentLightLevel> contentLightLevel;
  ::std::optional<::com::rdk::hal::videodecoder::DolbyVisionLayerFlags> dolbyVisionLayerFlags;
  ::std::optional<::com::rdk::hal::videodecoder::Fraction> pixelAspectRatio;
  inline bool operator!=(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, discontinuity, colorimetry, masteringDisplayInfo, contentLightLevel, dolbyVisionLayerFlags, pixelAspectRatio) != std::tie(rhs.nsPresentationTime, rhs.discontinuity, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.dolbyVisionLayerFlags, rhs.pixelAspectRatio);
  }
  inline bool operator<(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, discontinuity, colorimetry, masteringDisplayInfo, contentLightLevel, dolbyVisionLayerFlags, pixelAspectRatio) < std::tie(rhs.nsPresentationTime, rhs.discontinuity, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.dolbyVisionLayerFlags, rhs.pixelAspectRatio);
  }
  inline bool operator<=(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, discontinuity, colorimetry, masteringDisplayInfo, contentLightLevel, dolbyVisionLayerFlags, pixelAspectRatio) <= std::tie(rhs.nsPresentationTime, rhs.discontinuity, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.dolbyVisionLayerFlags, rhs.pixelAspectRatio);
  }
  inline bool operator==(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, discontinuity, colorimetry, masteringDisplayInfo, contentLightLevel, dolbyVisionLayerFlags, pixelAspectRatio) == std::tie(rhs.nsPresentationTime, rhs.discontinuity, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.dolbyVisionLayerFlags, rhs.pixelAspectRatio);
  }
  inline bool operator>(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, discontinuity, colorimetry, masteringDisplayInfo, contentLightLevel, dolbyVisionLayerFlags, pixelAspectRatio) > std::tie(rhs.nsPresentationTime, rhs.discontinuity, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.dolbyVisionLayerFlags, rhs.pixelAspectRatio);
  }
  inline bool operator>=(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, discontinuity, colorimetry, masteringDisplayInfo, contentLightLevel, dolbyVisionLayerFlags, pixelAspectRatio) >= std::tie(rhs.nsPresentationTime, rhs.discontinuity, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.dolbyVisionLayerFlags, rhs.pixelAspectRatio);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.videodecoder.InputBufferMetadata");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "InputBufferMetadata{";
    os << "nsPresentationTime: " << ::android::internal::ToString(nsPresentationTime);
    os << ", discontinuity: " << ::android::internal::ToString(discontinuity);
    os << ", colorimetry: " << ::android::internal::ToString(colorimetry);
    os << ", masteringDisplayInfo: " << ::android::internal::ToString(masteringDisplayInfo);
    os << ", contentLightLevel: " << ::android::internal::ToString(contentLightLevel);
    os << ", dolbyVisionLayerFlags: " << ::android::internal::ToString(dolbyVisionLayerFlags);
    os << ", pixelAspectRatio: " << ::android::internal::ToString(pixelAspectRatio);
    os << "}";
    return os.str();
  }
};  // class InputBufferMetadata
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com

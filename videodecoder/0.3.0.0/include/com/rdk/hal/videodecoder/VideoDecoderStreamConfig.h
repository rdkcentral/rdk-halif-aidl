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
// @aidl-doc
/**
 *  @brief     Atomic stream-configuration batch for the video decoder.
 *
 *  Carries the full set of container/manifest-derived stream-description
 *  hints in a single parcelable. Submitted via
 *  `IVideoDecoderController.setStreamConfig()` in `State::READY`, before
 *  decoding starts, as one atomic transaction.
 *
 *  Fields are `@nullable` except `colorimetry`, which carries its own
 *  `UNKNOWN` sentinel because AIDL does not permit `@nullable` on enums.
 *  Semantics:
 *  - non-null (or `colorimetry` ≠ `UNKNOWN`) — apply this value as the hint
 *  - null (or `colorimetry == UNKNOWN`)      — leave the existing hint
 *                                              unchanged (no-op for that field)
 *
 *  The "no change" semantics let clients send partial updates without
 *  having to repeat values they have already configured.
 *
 *  <h3>Hint precedence and persistence</h3>
 *  - Bitstream-derived metadata wins over the hint when both are present;
 *    the hint is the fallback used only when the bitstream is silent.
 *  - The decoder reports the value it actually used in `FrameMetadata`.
 *  - Hints persist across `flush()` and are cleared on `close()`.
 *
 *  <h3>Validation</h3>
 *  - `resolution`        — `width` and `height` MUST be > 0.
 *  - `frameRate`         — `denominator` MUST be > 0 unless `numerator`
 *                          is also 0 (encodes "unknown").
 *  - `pixelAspectRatio`  — both fields MUST be >= 0; the only valid
 *                          "unknown" encoding is 0/0.
 *
 *  @see IVideoDecoderController.setStreamConfig()
 *  @see Resolution
 *  @see Fraction
 *  @see Colorimetry
 *  @see MasteringDisplayInfo
 *  @see ContentLightLevel
 *  @see DolbyVisionLayerFlags
 *
 *  @author    Gerald Weatherup
 */
class VideoDecoderStreamConfig : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * Coded frame dimensions.
   * null = leave existing resolution hint unchanged.
   */
  ::std::optional<::com::rdk::hal::videodecoder::Resolution> resolution;
  // @aidl-doc
  /**
   * Stream frame rate as numerator / denominator.
   * 0/0 encodes "unknown".
   * null = leave existing frame rate hint unchanged.
   */
  ::std::optional<::com::rdk::hal::videodecoder::Fraction> frameRate;
  // @aidl-doc
  /**
   * Pixel aspect ratio as numerator / denominator.
   * 0/0 encodes "unknown".
   * null = leave existing PAR hint unchanged.
   */
  ::std::optional<::com::rdk::hal::videodecoder::Fraction> pixelAspectRatio;
  // @aidl-doc
  /**
   * Colorimetry (range / matrix / transfer / primaries — the four
   * independent axes carried by the bitstream VUI / container).
   * null = leave existing colorimetry hint unchanged. Non-null applies
   * the hint; sub-axes the caller doesn't want to override are left
   * at their `UNKNOWN` sentinel within the non-null parcelable.
   */
  ::std::optional<::com::rdk::hal::videodecoder::Colorimetry> colorimetry;
  // @aidl-doc
  /**
   * Mastering display colour volume metadata (SMPTE ST 2086).
   * null = leave existing mastering display hint unchanged.
   */
  ::std::optional<::com::rdk::hal::videodecoder::MasteringDisplayInfo> masteringDisplayInfo;
  // @aidl-doc
  /**
   * Content light level metadata (CTA-861.3 MaxCLL / MaxFALL).
   * null = leave existing content light level hint unchanged.
   */
  ::std::optional<::com::rdk::hal::videodecoder::ContentLightLevel> contentLightLevel;
  // @aidl-doc
  /**
   * Dolby Vision layer presence flags. Only applicable when the
   * stream DynamicRange is DOLBY_VISION.
   * null = leave existing Dolby Vision layer hint unchanged.
   */
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

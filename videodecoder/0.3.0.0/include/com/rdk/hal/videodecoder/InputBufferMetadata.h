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
// @aidl-doc
/**
 *  @brief     Per-buffer metadata carried with input buffers submitted via
 *             `IVideoDecoderController.decodeBufferWithMetadata()`.
 *
 *  Describes properties of the encoded frame that cannot be derived from the
 *  buffer contents alone, such as its presentation time, plus optional
 *  container-derived metadata overrides that apply from this frame onward.
 *
 *  <h3>Field semantics</h3>
 *  The fields fall into two categories with distinct semantics:
 *
 *  <h4>Non-nullable per-buffer field (`nsPresentationTime`)</h4>
 *  Describes the encoded frame itself. Each `decodeBufferWithMetadata()`
 *  call is self-describing for this field: the HAL MUST NOT carry state
 *  from this parcelable across calls. A subsequent call's value replaces,
 *  it does not preserve, the previous call's value.
 *
 *  <h4>Override fields (`colorimetry`, `masteringDisplayInfo`,
 *  `contentLightLevel`, `dolbyVisionLayerFlags`, `pixelAspectRatio`)</h4>
 *  All five are `@nullable`. For `colorimetry`, sub-axes the caller
 *  doesn't want to override are left at their `UNKNOWN` sentinel within
 *  a non-null parcelable — e.g. setting `colorimetry.matrix` to
 *  `BT2020_NCL` while leaving `range`/`transfer`/`primaries` at
 *  `UNKNOWN` overrides only the matrix axis. (Pass `null` to leave all
 *  four axes unchanged from the prior override / setStreamConfig
 *  state.)
 *  These mirror the matching fields on `VideoDecoderStreamConfig` and let
 *  middleware push container-derived metadata that changes mid-stream
 *  (e.g. ABR per-Period HDR transition, SSAI ad insertion, live→VOD switch).
 *
 *  - non-null                — apply this override from this buffer onward;
 *                              persists for subsequent buffers until a later
 *                              override (or a `setStreamConfig()` call)
 *                              replaces it.
 *  - null                    — no change for this field; the previously
 *                              applied override (or the value set in
 *                              `State::READY` via `setStreamConfig()`)
 *                              remains in effect.
 *
 *  Override precedence and persistence matches the `VideoDecoderStreamConfig`
 *  contract: bitstream-derived metadata still wins over the override;
 *  overrides are the fallback used only when the bitstream is silent.
 *  Overrides persist across `flush()` and are cleared on `close()`.
 *
 *  <h3>Scope</h3>
 *  Bitstream-driven properties (resolution / frame rate) are intentionally
 *  omitted from the override fields — on modern codecs these are signalled
 *  per-SPS in the bitstream and middleware should not override them
 *  mid-stream. Codec or encryption-mode changes are also out of scope and
 *  require a decoder teardown / `IVideoDecoder.open()` cycle.
 *
 *  @see IVideoDecoderController.decodeBufferWithMetadata()
 *  @see IVideoDecoderController.setStreamConfig()
 *  @see VideoDecoderStreamConfig
 *
 *  @author    Gerald Weatherup
 */
class InputBufferMetadata : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Presentation time of the encoded frame in nanoseconds. */
  int64_t nsPresentationTime = 0L;
  // @aidl-doc
  /**
   * Optional colorimetry override applied from this buffer onward.
   * null = no change. Non-null applies the override; sub-axes the
   * caller doesn't want to override are left at their `UNKNOWN`
   * sentinel within the non-null parcelable.
   *
   * @see VideoDecoderStreamConfig.colorimetry, IVideoDecoderController.setStreamConfig()
   */
  ::std::optional<::com::rdk::hal::videodecoder::Colorimetry> colorimetry;
  // @aidl-doc
  /**
   * Optional mastering display colour volume override (SMPTE ST 2086)
   * applied from this buffer onward. null = no change.
   *
   * @see VideoDecoderStreamConfig.masteringDisplayInfo, IVideoDecoderController.setStreamConfig()
   */
  ::std::optional<::com::rdk::hal::videodecoder::MasteringDisplayInfo> masteringDisplayInfo;
  // @aidl-doc
  /**
   * Optional content light level override (CTA-861.3 MaxCLL / MaxFALL)
   * applied from this buffer onward. null = no change.
   *
   * @see VideoDecoderStreamConfig.contentLightLevel, IVideoDecoderController.setStreamConfig()
   */
  ::std::optional<::com::rdk::hal::videodecoder::ContentLightLevel> contentLightLevel;
  // @aidl-doc
  /**
   * Optional Dolby Vision layer-flags override applied from this buffer
   * onward. Only meaningful when the stream DynamicRange is
   * DOLBY_VISION.
   * null = no change.
   *
   * @see VideoDecoderStreamConfig.dolbyVisionLayerFlags, IVideoDecoderController.setStreamConfig()
   */
  ::std::optional<::com::rdk::hal::videodecoder::DolbyVisionLayerFlags> dolbyVisionLayerFlags;
  // @aidl-doc
  /**
   * Optional pixel aspect ratio override applied from this buffer onward.
   * 0/0 encodes "unknown" (matching the
   * `VideoDecoderStreamConfig.pixelAspectRatio` rule).
   * null = no change.
   *
   * @see VideoDecoderStreamConfig.pixelAspectRatio, IVideoDecoderController.setStreamConfig()
   */
  ::std::optional<::com::rdk::hal::videodecoder::Fraction> pixelAspectRatio;
  inline bool operator!=(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, colorimetry, masteringDisplayInfo, contentLightLevel, dolbyVisionLayerFlags, pixelAspectRatio) != std::tie(rhs.nsPresentationTime, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.dolbyVisionLayerFlags, rhs.pixelAspectRatio);
  }
  inline bool operator<(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, colorimetry, masteringDisplayInfo, contentLightLevel, dolbyVisionLayerFlags, pixelAspectRatio) < std::tie(rhs.nsPresentationTime, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.dolbyVisionLayerFlags, rhs.pixelAspectRatio);
  }
  inline bool operator<=(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, colorimetry, masteringDisplayInfo, contentLightLevel, dolbyVisionLayerFlags, pixelAspectRatio) <= std::tie(rhs.nsPresentationTime, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.dolbyVisionLayerFlags, rhs.pixelAspectRatio);
  }
  inline bool operator==(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, colorimetry, masteringDisplayInfo, contentLightLevel, dolbyVisionLayerFlags, pixelAspectRatio) == std::tie(rhs.nsPresentationTime, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.dolbyVisionLayerFlags, rhs.pixelAspectRatio);
  }
  inline bool operator>(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, colorimetry, masteringDisplayInfo, contentLightLevel, dolbyVisionLayerFlags, pixelAspectRatio) > std::tie(rhs.nsPresentationTime, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.dolbyVisionLayerFlags, rhs.pixelAspectRatio);
  }
  inline bool operator>=(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, colorimetry, masteringDisplayInfo, contentLightLevel, dolbyVisionLayerFlags, pixelAspectRatio) >= std::tie(rhs.nsPresentationTime, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.dolbyVisionLayerFlags, rhs.pixelAspectRatio);
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

#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/videodecoder/Codec.h>
#include <com/rdk/hal/videodecoder/PixelFormat.h>
#include <com/rdk/hal/videodecoder/Profile.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
// @aidl-doc
/**
 *  @brief     Codec capability definition.
 *
 *  Each entry describes one codec the decoder supports, the set of
 *  profiles within that codec it can decode (each with its own
 *  `maxLevel` and `maxBitrateInBps`), and the resolution / pixel-format
 *  envelope shared across those profiles.
 *
 *  Shape mirrors `rdk-hpk-documentation/hfp-reference/videodecoder/
 *  hfp-videodecoder.yaml` field-for-field so the HFP YAML reads as a
 *  direct serialisation of the AIDL parcelable.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */
class CodecCapabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Defines the video codec type. */
  ::com::rdk::hal::videodecoder::Codec codec = ::com::rdk::hal::videodecoder::Codec(0);
  // @aidl-doc
  /**
   * Profiles supported for this codec, each with its own `maxLevel`
   * and `maxBitrateInBps`. A single codec can advertise multiple
   * profiles independently (e.g. H.265 supporting MAIN, MAIN_10, and
   * MAIN_10_HDR10 at LEVEL_5_2).
   *
   * All lower profiles for the same codec are NOT implicitly
   * supported — the array enumerates exactly what is supported. (In
   * contrast, lower levels within each `Profile` entry ARE implicitly
   * supported per `Profile.maxLevel` semantics.)
   *
   * @see Profile
   */
  ::std::vector<::com::rdk::hal::videodecoder::Profile> profiles;
  // @aidl-doc
  /**
   * The maximum frame rate (FPS) supported for decode for this Codec.
   * e.g. 25, 30, 50, 60, 120.
   */
  int32_t maxFrameRate = 0;
  // @aidl-doc
  /** The maximum frame width (pixels) supported for decode for this Codec. */
  int32_t maxFrameWidth = 0;
  // @aidl-doc
  /** The maximum frame height (pixels) supported for decode for this Codec. */
  int32_t maxFrameHeight = 0;
  // @aidl-doc
  /**
   * Pixel formats the decoder can produce on its output for this
   * codec/profile/level entry.
   *
   * Captures the chroma format constraint at the level where it physically
   * lives — the decoder. For example, a SoC whose H.264 hardware is profile-
   * locked at silicon and only outputs 4:2:0 advertises
   * `[YCBCR420]` here; a part that decodes the High profile bitstream but
   * downsamples to 4:2:0 on output also advertises `[YCBCR420]`. A SoC
   * supporting both 4:2:0 and 4:4:4 advertises `[YCBCR420, YCBCR444]`.
   *
   * Hardware support typically varies per codec block — a SoC's VP9 path
   * might do 4:4:4 on the same silicon where the H.264 path does not — so
   * the list is per-codec/profile/level entry rather than a single global
   * list on `Capabilities`.
   *
   * Used by the middleware at capability-discovery time to reject
   * incompatible streams before binding the decoder, rather than failing
   * inside `decodeBufferWithMetadata()` after start.
   *
   * @see PixelFormat
   */
  ::std::vector<::com::rdk::hal::videodecoder::PixelFormat> supportedOutputPixelFormats;
  inline bool operator!=(const CodecCapabilities& rhs) const {
    return std::tie(codec, profiles, maxFrameRate, maxFrameWidth, maxFrameHeight, supportedOutputPixelFormats) != std::tie(rhs.codec, rhs.profiles, rhs.maxFrameRate, rhs.maxFrameWidth, rhs.maxFrameHeight, rhs.supportedOutputPixelFormats);
  }
  inline bool operator<(const CodecCapabilities& rhs) const {
    return std::tie(codec, profiles, maxFrameRate, maxFrameWidth, maxFrameHeight, supportedOutputPixelFormats) < std::tie(rhs.codec, rhs.profiles, rhs.maxFrameRate, rhs.maxFrameWidth, rhs.maxFrameHeight, rhs.supportedOutputPixelFormats);
  }
  inline bool operator<=(const CodecCapabilities& rhs) const {
    return std::tie(codec, profiles, maxFrameRate, maxFrameWidth, maxFrameHeight, supportedOutputPixelFormats) <= std::tie(rhs.codec, rhs.profiles, rhs.maxFrameRate, rhs.maxFrameWidth, rhs.maxFrameHeight, rhs.supportedOutputPixelFormats);
  }
  inline bool operator==(const CodecCapabilities& rhs) const {
    return std::tie(codec, profiles, maxFrameRate, maxFrameWidth, maxFrameHeight, supportedOutputPixelFormats) == std::tie(rhs.codec, rhs.profiles, rhs.maxFrameRate, rhs.maxFrameWidth, rhs.maxFrameHeight, rhs.supportedOutputPixelFormats);
  }
  inline bool operator>(const CodecCapabilities& rhs) const {
    return std::tie(codec, profiles, maxFrameRate, maxFrameWidth, maxFrameHeight, supportedOutputPixelFormats) > std::tie(rhs.codec, rhs.profiles, rhs.maxFrameRate, rhs.maxFrameWidth, rhs.maxFrameHeight, rhs.supportedOutputPixelFormats);
  }
  inline bool operator>=(const CodecCapabilities& rhs) const {
    return std::tie(codec, profiles, maxFrameRate, maxFrameWidth, maxFrameHeight, supportedOutputPixelFormats) >= std::tie(rhs.codec, rhs.profiles, rhs.maxFrameRate, rhs.maxFrameWidth, rhs.maxFrameHeight, rhs.supportedOutputPixelFormats);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.videodecoder.CodecCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "CodecCapabilities{";
    os << "codec: " << ::android::internal::ToString(codec);
    os << ", profiles: " << ::android::internal::ToString(profiles);
    os << ", maxFrameRate: " << ::android::internal::ToString(maxFrameRate);
    os << ", maxFrameWidth: " << ::android::internal::ToString(maxFrameWidth);
    os << ", maxFrameHeight: " << ::android::internal::ToString(maxFrameHeight);
    os << ", supportedOutputPixelFormats: " << ::android::internal::ToString(supportedOutputPixelFormats);
    os << "}";
    return os.str();
  }
};  // class CodecCapabilities
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com

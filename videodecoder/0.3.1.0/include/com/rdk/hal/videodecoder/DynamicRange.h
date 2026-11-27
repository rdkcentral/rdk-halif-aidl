#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
// @aidl-doc
/**
 * Enum representing different dynamic range formats supported by video decoders.
 *
 * Dynamic range determines the range of luminance levels in a video.
 * Higher dynamic ranges allow for better contrast, brightness, and color accuracy.
 *
 * @enum DynamicRange
 */
enum class DynamicRange : int32_t {
  // @aidl-doc
  /** Dynamic range is unknown or not reported. */
  UNKNOWN = 0,
  // @aidl-doc
  /**
   * Standard Dynamic Range (SDR).
   * The most common format, typically using BT.709 color space with an 8-bit depth.
   */
  SDR = 1,
  // @aidl-doc
  /**
   * Hybrid Log-Gamma (HLG).
   * Designed for backward compatibility with SDR, used in live broadcasting.
   * @see ITU-R BT.2100
   */
  HLG = 2,
  // @aidl-doc
  /**
   * HDR10 (High Dynamic Range 10).
   * Uses static metadata for HDR and is widely used in streaming and UHD Blu-ray.
   * @see SMPTE ST 2084 (PQ Curve)
   */
  HDR10 = 3,
  // @aidl-doc
  /**
   * HDR10+ (High Dynamic Range 10 Plus).
   * An improved version of HDR10 that uses dynamic metadata for better tone mapping.
   * @see SMPTE ST 2094-40
   */
  HDR10_PLUS = 4,
  // @aidl-doc
  /**
   * Dolby Vision (DV).
   * A premium HDR format supporting dynamic metadata and up to 12-bit color depth.
   * @see Dolby Laboratories Specification
   */
  DOLBY_VISION = 5,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(DynamicRange val) {
  switch(val) {
  case DynamicRange::UNKNOWN:
    return "UNKNOWN";
  case DynamicRange::SDR:
    return "SDR";
  case DynamicRange::HLG:
    return "HLG";
  case DynamicRange::HDR10:
    return "HDR10";
  case DynamicRange::HDR10_PLUS:
    return "HDR10_PLUS";
  case DynamicRange::DOLBY_VISION:
    return "DOLBY_VISION";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::videodecoder::DynamicRange, 6> enum_values<::com::rdk::hal::videodecoder::DynamicRange> = {
  ::com::rdk::hal::videodecoder::DynamicRange::UNKNOWN,
  ::com::rdk::hal::videodecoder::DynamicRange::SDR,
  ::com::rdk::hal::videodecoder::DynamicRange::HLG,
  ::com::rdk::hal::videodecoder::DynamicRange::HDR10,
  ::com::rdk::hal::videodecoder::DynamicRange::HDR10_PLUS,
  ::com::rdk::hal::videodecoder::DynamicRange::DOLBY_VISION,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

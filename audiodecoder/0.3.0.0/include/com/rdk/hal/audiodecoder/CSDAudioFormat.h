#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
// @aidl-doc
/**
 * Enumeration of supported audio codec-specific data formats.
 *
 * These values define the format of initialization data required for certain audio codecs
 * used in DVB, ISDB, HLS, and DASH applications in STB/TV systems.
 */
enum class CSDAudioFormat : int32_t {
  // @aidl-doc
  /**
   * AAC AudioSpecificConfig (ASC) per ISO/IEC 14496-3.
   * Used for AAC-LC, HE-AAC, HE-AAC v2 in MP4/fMP4.
   * Required in encrypted DASH, HLS fMP4, CMAF.
   */
  MP4_AUDIO_SPECIFIC_CONFIG = 0,
  // @aidl-doc
  /**
   * MPEG-4 ALS AudioSpecificConfig (14496-3 subpart 11).
   * Rare, but valid in ISOBMFF with encryption.
   */
  ALS_SPECIFIC_CONFIG = 1,
  // @aidl-doc
  /**
   * Apple Lossless Audio Codec (ALAC), codec_data from 'alac' atom.
   * Used in MP4; decoder expects this for both clear/encrypted tracks.
   */
  ALAC_SPECIFIC_CONFIG = 2,
  // @aidl-doc
  /**
   * Dolby Digital Plus (E-AC-3) with 'dec3' box and possible proprietary config.
   * Used in ISOBMFF with encryption for HLS/DASH and HDMI passthrough.
   */
  EAC3_SPECIFIC_CONFIG = 3,
  // @aidl-doc
  /**
   * Dolby AC-4 with 'dac4' box per ETSI TS 103 190.
   * Used in fMP4 and CMAF for DVB-I and ATSC 3.0 systems.
   */
  AC4_SPECIFIC_CONFIG = 4,
};
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
[[nodiscard]] static inline std::string toString(CSDAudioFormat val) {
  switch(val) {
  case CSDAudioFormat::MP4_AUDIO_SPECIFIC_CONFIG:
    return "MP4_AUDIO_SPECIFIC_CONFIG";
  case CSDAudioFormat::ALS_SPECIFIC_CONFIG:
    return "ALS_SPECIFIC_CONFIG";
  case CSDAudioFormat::ALAC_SPECIFIC_CONFIG:
    return "ALAC_SPECIFIC_CONFIG";
  case CSDAudioFormat::EAC3_SPECIFIC_CONFIG:
    return "EAC3_SPECIFIC_CONFIG";
  case CSDAudioFormat::AC4_SPECIFIC_CONFIG:
    return "AC4_SPECIFIC_CONFIG";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiodecoder::CSDAudioFormat, 5> enum_values<::com::rdk::hal::audiodecoder::CSDAudioFormat> = {
  ::com::rdk::hal::audiodecoder::CSDAudioFormat::MP4_AUDIO_SPECIFIC_CONFIG,
  ::com::rdk::hal::audiodecoder::CSDAudioFormat::ALS_SPECIFIC_CONFIG,
  ::com::rdk::hal::audiodecoder::CSDAudioFormat::ALAC_SPECIFIC_CONFIG,
  ::com::rdk::hal::audiodecoder::CSDAudioFormat::EAC3_SPECIFIC_CONFIG,
  ::com::rdk::hal::audiodecoder::CSDAudioFormat::AC4_SPECIFIC_CONFIG,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

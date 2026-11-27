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
/** @brief Enumeration defining different audio codecs. */
enum class Codec : int32_t {
  // @aidl-doc
  /** Pulse Coded Modulation. */
  PCM = 0,
  // @aidl-doc
  /** Advanced Audio Coding Low Complexity. */
  AAC_LC = 1,
  // @aidl-doc
  /** High Efficiency Advanced Audio Coding. */
  HE_AAC = 2,
  // @aidl-doc
  /** High Efficiency Advanced Audio Coding v2. */
  HE_AAC2 = 3,
  // @aidl-doc
  /** Advanced Audio Coding Enhanced Low Delay. */
  AAC_ELD = 4,
  // @aidl-doc
  /** Dolby AC-3. */
  DOLBY_AC3 = 5,
  // @aidl-doc
  /** Dolby AC-3+ (E-AC-3). */
  DOLBY_AC3_PLUS = 6,
  // @aidl-doc
  /** Dolby AC-3+ (E-AC-3) with Joint Object Coding. */
  DOLBY_AC3_PLUS_JOC = 7,
  // @aidl-doc
  /** Dolby AC-4. */
  DOLBY_AC4 = 8,
  // @aidl-doc
  /** Dolby MAT. */
  DOLBY_MAT = 9,
  // @aidl-doc
  /** Dolby MAT2. */
  DOLBY_MAT2 = 10,
  // @aidl-doc
  /** Dolby TrueHD. */
  DOLBY_TRUEHD = 11,
  // @aidl-doc
  /** MPEG-1/2 audio layer II. */
  MPEG2 = 12,
  // @aidl-doc
  /** MPEG-1/2 audio layer III. */
  MP3 = 13,
  // @aidl-doc
  /** Free Lossless Audio Codec. */
  FLAC = 14,
  // @aidl-doc
  /** Vorbis. */
  VORBIS = 15,
  // @aidl-doc
  /** Digital Theater Systems. */
  DTS = 16,
  // @aidl-doc
  /** Opus. */
  OPUS = 17,
  // @aidl-doc
  /** Windows Media Audio. */
  WMA = 18,
  // @aidl-doc
  /** RealAudio. */
  REALAUDIO = 19,
  // @aidl-doc
  /** Unified Speech and Audio Coding. */
  USAC = 20,
  // @aidl-doc
  /** AAC speech codec. */
  X_HE_AAC = 21,
  // @aidl-doc
  /** SBC Bluetooth codec. */
  SBC = 22,
  // @aidl-doc
  /** Audio Video Standard codec. */
  AVS = 23,
};
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
[[nodiscard]] static inline std::string toString(Codec val) {
  switch(val) {
  case Codec::PCM:
    return "PCM";
  case Codec::AAC_LC:
    return "AAC_LC";
  case Codec::HE_AAC:
    return "HE_AAC";
  case Codec::HE_AAC2:
    return "HE_AAC2";
  case Codec::AAC_ELD:
    return "AAC_ELD";
  case Codec::DOLBY_AC3:
    return "DOLBY_AC3";
  case Codec::DOLBY_AC3_PLUS:
    return "DOLBY_AC3_PLUS";
  case Codec::DOLBY_AC3_PLUS_JOC:
    return "DOLBY_AC3_PLUS_JOC";
  case Codec::DOLBY_AC4:
    return "DOLBY_AC4";
  case Codec::DOLBY_MAT:
    return "DOLBY_MAT";
  case Codec::DOLBY_MAT2:
    return "DOLBY_MAT2";
  case Codec::DOLBY_TRUEHD:
    return "DOLBY_TRUEHD";
  case Codec::MPEG2:
    return "MPEG2";
  case Codec::MP3:
    return "MP3";
  case Codec::FLAC:
    return "FLAC";
  case Codec::VORBIS:
    return "VORBIS";
  case Codec::DTS:
    return "DTS";
  case Codec::OPUS:
    return "OPUS";
  case Codec::WMA:
    return "WMA";
  case Codec::REALAUDIO:
    return "REALAUDIO";
  case Codec::USAC:
    return "USAC";
  case Codec::X_HE_AAC:
    return "X_HE_AAC";
  case Codec::SBC:
    return "SBC";
  case Codec::AVS:
    return "AVS";
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
constexpr inline std::array<::com::rdk::hal::audiodecoder::Codec, 24> enum_values<::com::rdk::hal::audiodecoder::Codec> = {
  ::com::rdk::hal::audiodecoder::Codec::PCM,
  ::com::rdk::hal::audiodecoder::Codec::AAC_LC,
  ::com::rdk::hal::audiodecoder::Codec::HE_AAC,
  ::com::rdk::hal::audiodecoder::Codec::HE_AAC2,
  ::com::rdk::hal::audiodecoder::Codec::AAC_ELD,
  ::com::rdk::hal::audiodecoder::Codec::DOLBY_AC3,
  ::com::rdk::hal::audiodecoder::Codec::DOLBY_AC3_PLUS,
  ::com::rdk::hal::audiodecoder::Codec::DOLBY_AC3_PLUS_JOC,
  ::com::rdk::hal::audiodecoder::Codec::DOLBY_AC4,
  ::com::rdk::hal::audiodecoder::Codec::DOLBY_MAT,
  ::com::rdk::hal::audiodecoder::Codec::DOLBY_MAT2,
  ::com::rdk::hal::audiodecoder::Codec::DOLBY_TRUEHD,
  ::com::rdk::hal::audiodecoder::Codec::MPEG2,
  ::com::rdk::hal::audiodecoder::Codec::MP3,
  ::com::rdk::hal::audiodecoder::Codec::FLAC,
  ::com::rdk::hal::audiodecoder::Codec::VORBIS,
  ::com::rdk::hal::audiodecoder::Codec::DTS,
  ::com::rdk::hal::audiodecoder::Codec::OPUS,
  ::com::rdk::hal::audiodecoder::Codec::WMA,
  ::com::rdk::hal::audiodecoder::Codec::REALAUDIO,
  ::com::rdk::hal::audiodecoder::Codec::USAC,
  ::com::rdk::hal::audiodecoder::Codec::X_HE_AAC,
  ::com::rdk::hal::audiodecoder::Codec::SBC,
  ::com::rdk::hal::audiodecoder::Codec::AVS,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

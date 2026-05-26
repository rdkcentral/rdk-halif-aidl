#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
enum class Codec : int32_t {
  PCM = 0,
  AAC_LC = 1,
  HE_AAC = 2,
  HE_AAC2 = 3,
  AAC_ELD = 4,
  DOLBY_AC3 = 5,
  DOLBY_AC3_PLUS = 6,
  DOLBY_AC3_PLUS_JOC = 7,
  DOLBY_AC4 = 8,
  DOLBY_MAT = 9,
  DOLBY_MAT2 = 10,
  DOLBY_TRUEHD = 11,
  MPEG2 = 12,
  MP3 = 13,
  FLAC = 14,
  VORBIS = 15,
  DTS = 16,
  OPUS = 17,
  WMA = 18,
  REALAUDIO = 19,
  USAC = 20,
  X_HE_AAC = 21,
  SBC = 22,
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

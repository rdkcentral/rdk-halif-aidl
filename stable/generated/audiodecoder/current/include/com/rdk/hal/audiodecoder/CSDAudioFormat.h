#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
enum class CSDAudioFormat : int32_t {
  MP4_AUDIO_SPECIFIC_CONFIG = 0,
  ALS_SPECIFIC_CONFIG = 1,
  ALAC_SPECIFIC_CONFIG = 2,
  EAC3_SPECIFIC_CONFIG = 3,
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

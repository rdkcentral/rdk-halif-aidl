#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
enum class TranscodeFormat : int32_t {
  NONE = 0,
  PCM = 1,
  DOLBY_AC3 = 2,
  DOLBY_AC3_PLUS = 3,
  DOLBY_MAT = 4,
  DOLBY_TRUEHD = 5,
  DTS = 6,
  MPEG2 = 7,
  OTHER = 100,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(TranscodeFormat val) {
  switch(val) {
  case TranscodeFormat::NONE:
    return "NONE";
  case TranscodeFormat::PCM:
    return "PCM";
  case TranscodeFormat::DOLBY_AC3:
    return "DOLBY_AC3";
  case TranscodeFormat::DOLBY_AC3_PLUS:
    return "DOLBY_AC3_PLUS";
  case TranscodeFormat::DOLBY_MAT:
    return "DOLBY_MAT";
  case TranscodeFormat::DOLBY_TRUEHD:
    return "DOLBY_TRUEHD";
  case TranscodeFormat::DTS:
    return "DTS";
  case TranscodeFormat::MPEG2:
    return "MPEG2";
  case TranscodeFormat::OTHER:
    return "OTHER";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiomixer::TranscodeFormat, 9> enum_values<::com::rdk::hal::audiomixer::TranscodeFormat> = {
  ::com::rdk::hal::audiomixer::TranscodeFormat::NONE,
  ::com::rdk::hal::audiomixer::TranscodeFormat::PCM,
  ::com::rdk::hal::audiomixer::TranscodeFormat::DOLBY_AC3,
  ::com::rdk::hal::audiomixer::TranscodeFormat::DOLBY_AC3_PLUS,
  ::com::rdk::hal::audiomixer::TranscodeFormat::DOLBY_MAT,
  ::com::rdk::hal::audiomixer::TranscodeFormat::DOLBY_TRUEHD,
  ::com::rdk::hal::audiomixer::TranscodeFormat::DTS,
  ::com::rdk::hal::audiomixer::TranscodeFormat::MPEG2,
  ::com::rdk::hal::audiomixer::TranscodeFormat::OTHER,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

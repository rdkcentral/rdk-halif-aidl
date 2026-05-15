#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
enum class OutputFormat : int32_t {
  AUTO = 0,
  PASSTHROUGH = 1,
  PCM = 2,
  AC3 = 3,
  EAC3 = 4,
  MAT = 5,
  TRUEHD = 6,
  DTS = 7,
  DTS_HD = 8,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(OutputFormat val) {
  switch(val) {
  case OutputFormat::AUTO:
    return "AUTO";
  case OutputFormat::PASSTHROUGH:
    return "PASSTHROUGH";
  case OutputFormat::PCM:
    return "PCM";
  case OutputFormat::AC3:
    return "AC3";
  case OutputFormat::EAC3:
    return "EAC3";
  case OutputFormat::MAT:
    return "MAT";
  case OutputFormat::TRUEHD:
    return "TRUEHD";
  case OutputFormat::DTS:
    return "DTS";
  case OutputFormat::DTS_HD:
    return "DTS_HD";
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
constexpr inline std::array<::com::rdk::hal::audiomixer::OutputFormat, 9> enum_values<::com::rdk::hal::audiomixer::OutputFormat> = {
  ::com::rdk::hal::audiomixer::OutputFormat::AUTO,
  ::com::rdk::hal::audiomixer::OutputFormat::PASSTHROUGH,
  ::com::rdk::hal::audiomixer::OutputFormat::PCM,
  ::com::rdk::hal::audiomixer::OutputFormat::AC3,
  ::com::rdk::hal::audiomixer::OutputFormat::EAC3,
  ::com::rdk::hal::audiomixer::OutputFormat::MAT,
  ::com::rdk::hal::audiomixer::OutputFormat::TRUEHD,
  ::com::rdk::hal::audiomixer::OutputFormat::DTS,
  ::com::rdk::hal::audiomixer::OutputFormat::DTS_HD,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
enum class HDROutputMode : int32_t {
  AUTO = 0,
  HLG = 1,
  HDR10 = 2,
  HDR10_PLUS = 3,
  DOLBY_VISION = 4,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
[[nodiscard]] static inline std::string toString(HDROutputMode val) {
  switch(val) {
  case HDROutputMode::AUTO:
    return "AUTO";
  case HDROutputMode::HLG:
    return "HLG";
  case HDROutputMode::HDR10:
    return "HDR10";
  case HDROutputMode::HDR10_PLUS:
    return "HDR10_PLUS";
  case HDROutputMode::DOLBY_VISION:
    return "DOLBY_VISION";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::hdmioutput::HDROutputMode, 5> enum_values<::com::rdk::hal::hdmioutput::HDROutputMode> = {
  ::com::rdk::hal::hdmioutput::HDROutputMode::AUTO,
  ::com::rdk::hal::hdmioutput::HDROutputMode::HLG,
  ::com::rdk::hal::hdmioutput::HDROutputMode::HDR10,
  ::com::rdk::hal::hdmioutput::HDROutputMode::HDR10_PLUS,
  ::com::rdk::hal::hdmioutput::HDROutputMode::DOLBY_VISION,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
enum class DolbyMs12_2_6_LevellerMode : int32_t {
  OFF = 0,
  MANUAL = 1,
  AUTO = 2,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(DolbyMs12_2_6_LevellerMode val) {
  switch(val) {
  case DolbyMs12_2_6_LevellerMode::OFF:
    return "OFF";
  case DolbyMs12_2_6_LevellerMode::MANUAL:
    return "MANUAL";
  case DolbyMs12_2_6_LevellerMode::AUTO:
    return "AUTO";
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
constexpr inline std::array<::com::rdk::hal::audiomixer::DolbyMs12_2_6_LevellerMode, 3> enum_values<::com::rdk::hal::audiomixer::DolbyMs12_2_6_LevellerMode> = {
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_LevellerMode::OFF,
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_LevellerMode::MANUAL,
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_LevellerMode::AUTO,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

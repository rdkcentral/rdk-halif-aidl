#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
enum class DolbyMs12_2_6_GeqMode : int32_t {
  OFF = 0,
  OPEN = 1,
  RICH = 2,
  FOCUSED = 3,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(DolbyMs12_2_6_GeqMode val) {
  switch(val) {
  case DolbyMs12_2_6_GeqMode::OFF:
    return "OFF";
  case DolbyMs12_2_6_GeqMode::OPEN:
    return "OPEN";
  case DolbyMs12_2_6_GeqMode::RICH:
    return "RICH";
  case DolbyMs12_2_6_GeqMode::FOCUSED:
    return "FOCUSED";
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
constexpr inline std::array<::com::rdk::hal::audiomixer::DolbyMs12_2_6_GeqMode, 4> enum_values<::com::rdk::hal::audiomixer::DolbyMs12_2_6_GeqMode> = {
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_GeqMode::OFF,
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_GeqMode::OPEN,
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_GeqMode::RICH,
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_GeqMode::FOCUSED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

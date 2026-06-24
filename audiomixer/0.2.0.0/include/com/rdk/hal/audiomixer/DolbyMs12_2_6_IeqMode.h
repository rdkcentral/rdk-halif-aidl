#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
enum class DolbyMs12_2_6_IeqMode : int32_t {
  OFF = 0,
  OPEN = 1,
  RICH = 2,
  FOCUSED = 3,
  BALANCED = 4,
  WARM = 5,
  DETAILED = 6,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(DolbyMs12_2_6_IeqMode val) {
  switch(val) {
  case DolbyMs12_2_6_IeqMode::OFF:
    return "OFF";
  case DolbyMs12_2_6_IeqMode::OPEN:
    return "OPEN";
  case DolbyMs12_2_6_IeqMode::RICH:
    return "RICH";
  case DolbyMs12_2_6_IeqMode::FOCUSED:
    return "FOCUSED";
  case DolbyMs12_2_6_IeqMode::BALANCED:
    return "BALANCED";
  case DolbyMs12_2_6_IeqMode::WARM:
    return "WARM";
  case DolbyMs12_2_6_IeqMode::DETAILED:
    return "DETAILED";
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
constexpr inline std::array<::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode, 7> enum_values<::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode> = {
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode::OFF,
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode::OPEN,
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode::RICH,
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode::FOCUSED,
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode::BALANCED,
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode::WARM,
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode::DETAILED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

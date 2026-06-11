#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
enum class DolbyMs12_2_6_DrcMode : int32_t {
  LINE = 0,
  RF = 1,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(DolbyMs12_2_6_DrcMode val) {
  switch(val) {
  case DolbyMs12_2_6_DrcMode::LINE:
    return "LINE";
  case DolbyMs12_2_6_DrcMode::RF:
    return "RF";
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
constexpr inline std::array<::com::rdk::hal::audiomixer::DolbyMs12_2_6_DrcMode, 2> enum_values<::com::rdk::hal::audiomixer::DolbyMs12_2_6_DrcMode> = {
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_DrcMode::LINE,
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_DrcMode::RF,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

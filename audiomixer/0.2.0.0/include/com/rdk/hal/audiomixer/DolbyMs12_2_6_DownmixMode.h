#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
enum class DolbyMs12_2_6_DownmixMode : int32_t {
  LT_RT = 0,
  LO_RO = 1,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(DolbyMs12_2_6_DownmixMode val) {
  switch(val) {
  case DolbyMs12_2_6_DownmixMode::LT_RT:
    return "LT_RT";
  case DolbyMs12_2_6_DownmixMode::LO_RO:
    return "LO_RO";
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
constexpr inline std::array<::com::rdk::hal::audiomixer::DolbyMs12_2_6_DownmixMode, 2> enum_values<::com::rdk::hal::audiomixer::DolbyMs12_2_6_DownmixMode> = {
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_DownmixMode::LT_RT,
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_DownmixMode::LO_RO,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

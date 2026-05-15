#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
enum class MixingMode : int32_t {
  NORMAL = 0,
  MUTED = 1,
  DUCKED = 2,
  SOLO = 3,
  MIXED_OVERRIDE = 4,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(MixingMode val) {
  switch(val) {
  case MixingMode::NORMAL:
    return "NORMAL";
  case MixingMode::MUTED:
    return "MUTED";
  case MixingMode::DUCKED:
    return "DUCKED";
  case MixingMode::SOLO:
    return "SOLO";
  case MixingMode::MIXED_OVERRIDE:
    return "MIXED_OVERRIDE";
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
constexpr inline std::array<::com::rdk::hal::audiomixer::MixingMode, 5> enum_values<::com::rdk::hal::audiomixer::MixingMode> = {
  ::com::rdk::hal::audiomixer::MixingMode::NORMAL,
  ::com::rdk::hal::audiomixer::MixingMode::MUTED,
  ::com::rdk::hal::audiomixer::MixingMode::DUCKED,
  ::com::rdk::hal::audiomixer::MixingMode::SOLO,
  ::com::rdk::hal::audiomixer::MixingMode::MIXED_OVERRIDE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
// @aidl-doc
/** @brief Local dimming mode. */
enum class DimmingMode : int32_t {
  DIMMING_MODE_INVALID = -1,
  DIMMING_MODE_FIXED = 0,
  DIMMING_MODE_GLOBAL = 1,
  DIMMING_MODE_LOCAL = 2,
};
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace panel {
[[nodiscard]] static inline std::string toString(DimmingMode val) {
  switch(val) {
  case DimmingMode::DIMMING_MODE_INVALID:
    return "DIMMING_MODE_INVALID";
  case DimmingMode::DIMMING_MODE_FIXED:
    return "DIMMING_MODE_FIXED";
  case DimmingMode::DIMMING_MODE_GLOBAL:
    return "DIMMING_MODE_GLOBAL";
  case DimmingMode::DIMMING_MODE_LOCAL:
    return "DIMMING_MODE_LOCAL";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::panel::DimmingMode, 4> enum_values<::com::rdk::hal::panel::DimmingMode> = {
  ::com::rdk::hal::panel::DimmingMode::DIMMING_MODE_INVALID,
  ::com::rdk::hal::panel::DimmingMode::DIMMING_MODE_FIXED,
  ::com::rdk::hal::panel::DimmingMode::DIMMING_MODE_GLOBAL,
  ::com::rdk::hal::panel::DimmingMode::DIMMING_MODE_LOCAL,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

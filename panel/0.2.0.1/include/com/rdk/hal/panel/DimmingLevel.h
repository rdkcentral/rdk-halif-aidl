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
/** @brief Local dimming level. */
enum class DimmingLevel : int32_t {
  // @aidl-doc
  /** Invalid or unset level. */
  DIMMING_LEVEL_INVALID = -1,
  // @aidl-doc
  /** The dimming mode has no selectable levels. */
  DIMMING_LEVEL_NOT_APPLICABLE = 0,
  // @aidl-doc
  /** Low dimming level. */
  DIMMING_LEVEL_LOW = 1,
  // @aidl-doc
  /** Medium dimming level. */
  DIMMING_LEVEL_MEDIUM = 2,
  // @aidl-doc
  /** High dimming level. */
  DIMMING_LEVEL_HIGH = 3,
};
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace panel {
[[nodiscard]] static inline std::string toString(DimmingLevel val) {
  switch(val) {
  case DimmingLevel::DIMMING_LEVEL_INVALID:
    return "DIMMING_LEVEL_INVALID";
  case DimmingLevel::DIMMING_LEVEL_NOT_APPLICABLE:
    return "DIMMING_LEVEL_NOT_APPLICABLE";
  case DimmingLevel::DIMMING_LEVEL_LOW:
    return "DIMMING_LEVEL_LOW";
  case DimmingLevel::DIMMING_LEVEL_MEDIUM:
    return "DIMMING_LEVEL_MEDIUM";
  case DimmingLevel::DIMMING_LEVEL_HIGH:
    return "DIMMING_LEVEL_HIGH";
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
constexpr inline std::array<::com::rdk::hal::panel::DimmingLevel, 5> enum_values<::com::rdk::hal::panel::DimmingLevel> = {
  ::com::rdk::hal::panel::DimmingLevel::DIMMING_LEVEL_INVALID,
  ::com::rdk::hal::panel::DimmingLevel::DIMMING_LEVEL_NOT_APPLICABLE,
  ::com::rdk::hal::panel::DimmingLevel::DIMMING_LEVEL_LOW,
  ::com::rdk::hal::panel::DimmingLevel::DIMMING_LEVEL_MEDIUM,
  ::com::rdk::hal::panel::DimmingLevel::DIMMING_LEVEL_HIGH,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

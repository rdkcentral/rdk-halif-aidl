#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
enum class PanelType : int32_t {
  LCD = 0,
  QLED = 1,
  OLED = 2,
  MINI_LED = 3,
};
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace panel {
[[nodiscard]] static inline std::string toString(PanelType val) {
  switch(val) {
  case PanelType::LCD:
    return "LCD";
  case PanelType::QLED:
    return "QLED";
  case PanelType::OLED:
    return "OLED";
  case PanelType::MINI_LED:
    return "MINI_LED";
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
constexpr inline std::array<::com::rdk::hal::panel::PanelType, 4> enum_values<::com::rdk::hal::panel::PanelType> = {
  ::com::rdk::hal::panel::PanelType::LCD,
  ::com::rdk::hal::panel::PanelType::QLED,
  ::com::rdk::hal::panel::PanelType::OLED,
  ::com::rdk::hal::panel::PanelType::MINI_LED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace demo {
namespace hal {
namespace common {
enum class WarningLevel : int32_t {
  LOW = 0,
  MEDIUM = 1,
  HIGH = 2,
  CRITICAL = 3,
};
}  // namespace common
}  // namespace hal
}  // namespace demo
}  // namespace com
namespace com {
namespace demo {
namespace hal {
namespace common {
[[nodiscard]] static inline std::string toString(WarningLevel val) {
  switch(val) {
  case WarningLevel::LOW:
    return "LOW";
  case WarningLevel::MEDIUM:
    return "MEDIUM";
  case WarningLevel::HIGH:
    return "HIGH";
  case WarningLevel::CRITICAL:
    return "CRITICAL";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace common
}  // namespace hal
}  // namespace demo
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::demo::hal::common::WarningLevel, 4> enum_values<::com::demo::hal::common::WarningLevel> = {
  ::com::demo::hal::common::WarningLevel::LOW,
  ::com::demo::hal::common::WarningLevel::MEDIUM,
  ::com::demo::hal::common::WarningLevel::HIGH,
  ::com::demo::hal::common::WarningLevel::CRITICAL,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

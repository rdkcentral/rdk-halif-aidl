#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace boot {
enum class BootReason : int32_t {
  ERROR_UNKNOWN = -1,
  WATCHDOG = 0,
  MAINTENANCE_REBOOT = 1,
  THERMAL_RESET = 2,
  WARM_RESET = 3,
  COLD_BOOT = 4,
  STR_AUTH_FAILURE = 5,
};
}  // namespace boot
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace boot {
[[nodiscard]] static inline std::string toString(BootReason val) {
  switch(val) {
  case BootReason::ERROR_UNKNOWN:
    return "ERROR_UNKNOWN";
  case BootReason::WATCHDOG:
    return "WATCHDOG";
  case BootReason::MAINTENANCE_REBOOT:
    return "MAINTENANCE_REBOOT";
  case BootReason::THERMAL_RESET:
    return "THERMAL_RESET";
  case BootReason::WARM_RESET:
    return "WARM_RESET";
  case BootReason::COLD_BOOT:
    return "COLD_BOOT";
  case BootReason::STR_AUTH_FAILURE:
    return "STR_AUTH_FAILURE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace boot
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::boot::BootReason, 7> enum_values<::com::rdk::hal::boot::BootReason> = {
  ::com::rdk::hal::boot::BootReason::ERROR_UNKNOWN,
  ::com::rdk::hal::boot::BootReason::WATCHDOG,
  ::com::rdk::hal::boot::BootReason::MAINTENANCE_REBOOT,
  ::com::rdk::hal::boot::BootReason::THERMAL_RESET,
  ::com::rdk::hal::boot::BootReason::WARM_RESET,
  ::com::rdk::hal::boot::BootReason::COLD_BOOT,
  ::com::rdk::hal::boot::BootReason::STR_AUTH_FAILURE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

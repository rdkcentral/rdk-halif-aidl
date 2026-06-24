#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace bootreason {
enum class BootCause : int32_t {
  ERROR_UNKNOWN = -1,
  WATCHDOG = 0,
  MAINTENANCE_REBOOT = 1,
  THERMAL_RESET = 2,
  WARM_RESET = 3,
  COLD_BOOT = 4,
  STR_AUTH_FAILURE = 5,
};
}  // namespace bootreason
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace bootreason {
[[nodiscard]] static inline std::string toString(BootCause val) {
  switch(val) {
  case BootCause::ERROR_UNKNOWN:
    return "ERROR_UNKNOWN";
  case BootCause::WATCHDOG:
    return "WATCHDOG";
  case BootCause::MAINTENANCE_REBOOT:
    return "MAINTENANCE_REBOOT";
  case BootCause::THERMAL_RESET:
    return "THERMAL_RESET";
  case BootCause::WARM_RESET:
    return "WARM_RESET";
  case BootCause::COLD_BOOT:
    return "COLD_BOOT";
  case BootCause::STR_AUTH_FAILURE:
    return "STR_AUTH_FAILURE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace bootreason
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::bootreason::BootCause, 7> enum_values<::com::rdk::hal::bootreason::BootCause> = {
  ::com::rdk::hal::bootreason::BootCause::ERROR_UNKNOWN,
  ::com::rdk::hal::bootreason::BootCause::WATCHDOG,
  ::com::rdk::hal::bootreason::BootCause::MAINTENANCE_REBOOT,
  ::com::rdk::hal::bootreason::BootCause::THERMAL_RESET,
  ::com::rdk::hal::bootreason::BootCause::WARM_RESET,
  ::com::rdk::hal::bootreason::BootCause::COLD_BOOT,
  ::com::rdk::hal::bootreason::BootCause::STR_AUTH_FAILURE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

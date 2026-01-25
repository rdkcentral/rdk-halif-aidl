#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace boot {
enum class ResetType : int32_t {
  FULL_SYSTEM_RESET = 0,
  INVALIDATE_CURRENT_APPLICATION_IMAGE = 1,
  FORCE_DISASTER_RECOVERY = 2,
  MAINTENANCE_REBOOT = 3,
  SOFTWARE_REBOOT = 4,
};
}  // namespace boot
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace boot {
[[nodiscard]] static inline std::string toString(ResetType val) {
  switch(val) {
  case ResetType::FULL_SYSTEM_RESET:
    return "FULL_SYSTEM_RESET";
  case ResetType::INVALIDATE_CURRENT_APPLICATION_IMAGE:
    return "INVALIDATE_CURRENT_APPLICATION_IMAGE";
  case ResetType::FORCE_DISASTER_RECOVERY:
    return "FORCE_DISASTER_RECOVERY";
  case ResetType::MAINTENANCE_REBOOT:
    return "MAINTENANCE_REBOOT";
  case ResetType::SOFTWARE_REBOOT:
    return "SOFTWARE_REBOOT";
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
constexpr inline std::array<::com::rdk::hal::boot::ResetType, 5> enum_values<::com::rdk::hal::boot::ResetType> = {
  ::com::rdk::hal::boot::ResetType::FULL_SYSTEM_RESET,
  ::com::rdk::hal::boot::ResetType::INVALIDATE_CURRENT_APPLICATION_IMAGE,
  ::com::rdk::hal::boot::ResetType::FORCE_DISASTER_RECOVERY,
  ::com::rdk::hal::boot::ResetType::MAINTENANCE_REBOOT,
  ::com::rdk::hal::boot::ResetType::SOFTWARE_REBOOT,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

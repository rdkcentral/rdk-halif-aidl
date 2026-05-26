#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
enum class HDCPStatus : int32_t {
  UNKNOWN = -1,
  UNAUTHENTICATED = 0,
  AUTHENTICATION_IN_PROGRESS = 1,
  AUTHENTICATION_FAILURE = 2,
  AUTHENTICATED = 3,
};
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
[[nodiscard]] static inline std::string toString(HDCPStatus val) {
  switch(val) {
  case HDCPStatus::UNKNOWN:
    return "UNKNOWN";
  case HDCPStatus::UNAUTHENTICATED:
    return "UNAUTHENTICATED";
  case HDCPStatus::AUTHENTICATION_IN_PROGRESS:
    return "AUTHENTICATION_IN_PROGRESS";
  case HDCPStatus::AUTHENTICATION_FAILURE:
    return "AUTHENTICATION_FAILURE";
  case HDCPStatus::AUTHENTICATED:
    return "AUTHENTICATED";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::hdmiinput::HDCPStatus, 5> enum_values<::com::rdk::hal::hdmiinput::HDCPStatus> = {
  ::com::rdk::hal::hdmiinput::HDCPStatus::UNKNOWN,
  ::com::rdk::hal::hdmiinput::HDCPStatus::UNAUTHENTICATED,
  ::com::rdk::hal::hdmiinput::HDCPStatus::AUTHENTICATION_IN_PROGRESS,
  ::com::rdk::hal::hdmiinput::HDCPStatus::AUTHENTICATION_FAILURE,
  ::com::rdk::hal::hdmiinput::HDCPStatus::AUTHENTICATED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

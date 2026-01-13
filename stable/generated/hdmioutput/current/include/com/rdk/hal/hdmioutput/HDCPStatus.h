#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
enum class HDCPStatus : int32_t {
  UNKNOWN = -1,
  UNAUTHENTICATED = 0,
  AUTHENTICATION_IN_PROGRESS = 1,
  AUTHENTICATION_FAILURE = 2,
  AUTHENTICATED = 3,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
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
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::hdmioutput::HDCPStatus, 5> enum_values<::com::rdk::hal::hdmioutput::HDCPStatus> = {
  ::com::rdk::hal::hdmioutput::HDCPStatus::UNKNOWN,
  ::com::rdk::hal::hdmioutput::HDCPStatus::UNAUTHENTICATED,
  ::com::rdk::hal::hdmioutput::HDCPStatus::AUTHENTICATION_IN_PROGRESS,
  ::com::rdk::hal::hdmioutput::HDCPStatus::AUTHENTICATION_FAILURE,
  ::com::rdk::hal::hdmioutput::HDCPStatus::AUTHENTICATED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
enum class FreeSync : int32_t {
  UNSUPPORTED = 0,
  FREESYNC = 1,
  FREESYNC_PREMIUM = 2,
  FREESYNC_PREMIUM_PRO = 3,
};
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
[[nodiscard]] static inline std::string toString(FreeSync val) {
  switch(val) {
  case FreeSync::UNSUPPORTED:
    return "UNSUPPORTED";
  case FreeSync::FREESYNC:
    return "FREESYNC";
  case FreeSync::FREESYNC_PREMIUM:
    return "FREESYNC_PREMIUM";
  case FreeSync::FREESYNC_PREMIUM_PRO:
    return "FREESYNC_PREMIUM_PRO";
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
constexpr inline std::array<::com::rdk::hal::hdmiinput::FreeSync, 4> enum_values<::com::rdk::hal::hdmiinput::FreeSync> = {
  ::com::rdk::hal::hdmiinput::FreeSync::UNSUPPORTED,
  ::com::rdk::hal::hdmiinput::FreeSync::FREESYNC,
  ::com::rdk::hal::hdmiinput::FreeSync::FREESYNC_PREMIUM,
  ::com::rdk::hal::hdmiinput::FreeSync::FREESYNC_PREMIUM_PRO,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

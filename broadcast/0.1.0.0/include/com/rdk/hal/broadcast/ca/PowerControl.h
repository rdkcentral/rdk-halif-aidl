#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace ca {
enum class PowerControl : int32_t {
  UNDEFINED = 0,
  NONE = 1,
  SHARED = 2,
  DEDICATED = 3,
};
}  // namespace ca
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace ca {
[[nodiscard]] static inline std::string toString(PowerControl val) {
  switch(val) {
  case PowerControl::UNDEFINED:
    return "UNDEFINED";
  case PowerControl::NONE:
    return "NONE";
  case PowerControl::SHARED:
    return "SHARED";
  case PowerControl::DEDICATED:
    return "DEDICATED";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace ca
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::broadcast::ca::PowerControl, 4> enum_values<::com::rdk::hal::broadcast::ca::PowerControl> = {
  ::com::rdk::hal::broadcast::ca::PowerControl::UNDEFINED,
  ::com::rdk::hal::broadcast::ca::PowerControl::NONE,
  ::com::rdk::hal::broadcast::ca::PowerControl::SHARED,
  ::com::rdk::hal::broadcast::ca::PowerControl::DEDICATED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

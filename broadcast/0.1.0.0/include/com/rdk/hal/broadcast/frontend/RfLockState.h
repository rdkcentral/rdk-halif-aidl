#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
enum class RfLockState : int32_t {
  UNDEFINED = 0,
  UNLOCKED = 1,
  LOCKED = 2,
};
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
[[nodiscard]] static inline std::string toString(RfLockState val) {
  switch(val) {
  case RfLockState::UNDEFINED:
    return "UNDEFINED";
  case RfLockState::UNLOCKED:
    return "UNLOCKED";
  case RfLockState::LOCKED:
    return "LOCKED";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::RfLockState, 3> enum_values<::com::rdk::hal::broadcast::frontend::RfLockState> = {
  ::com::rdk::hal::broadcast::frontend::RfLockState::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::RfLockState::UNLOCKED,
  ::com::rdk::hal::broadcast::frontend::RfLockState::LOCKED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
enum class SignalState : int32_t {
  UNKNOWN = -1,
  NO_SIGNAL = 0,
  UNSTABLE = 1,
  NOT_SUPPORTED = 2,
  LOCKED = 3,
};
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
[[nodiscard]] static inline std::string toString(SignalState val) {
  switch(val) {
  case SignalState::UNKNOWN:
    return "UNKNOWN";
  case SignalState::NO_SIGNAL:
    return "NO_SIGNAL";
  case SignalState::UNSTABLE:
    return "UNSTABLE";
  case SignalState::NOT_SUPPORTED:
    return "NOT_SUPPORTED";
  case SignalState::LOCKED:
    return "LOCKED";
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
constexpr inline std::array<::com::rdk::hal::hdmiinput::SignalState, 5> enum_values<::com::rdk::hal::hdmiinput::SignalState> = {
  ::com::rdk::hal::hdmiinput::SignalState::UNKNOWN,
  ::com::rdk::hal::hdmiinput::SignalState::NO_SIGNAL,
  ::com::rdk::hal::hdmiinput::SignalState::UNSTABLE,
  ::com::rdk::hal::hdmiinput::SignalState::NOT_SUPPORTED,
  ::com::rdk::hal::hdmiinput::SignalState::LOCKED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

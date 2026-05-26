#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
enum class State : int32_t {
  CLOSED = 0,
  OPENING = 1,
  READY = 2,
  STARTING = 3,
  STARTED = 4,
  STOPPING = 5,
  CLOSING = 6,
};
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
[[nodiscard]] static inline std::string toString(State val) {
  switch(val) {
  case State::CLOSED:
    return "CLOSED";
  case State::OPENING:
    return "OPENING";
  case State::READY:
    return "READY";
  case State::STARTING:
    return "STARTING";
  case State::STARTED:
    return "STARTED";
  case State::STOPPING:
    return "STOPPING";
  case State::CLOSING:
    return "CLOSING";
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
constexpr inline std::array<::com::rdk::hal::hdmiinput::State, 7> enum_values<::com::rdk::hal::hdmiinput::State> = {
  ::com::rdk::hal::hdmiinput::State::CLOSED,
  ::com::rdk::hal::hdmiinput::State::OPENING,
  ::com::rdk::hal::hdmiinput::State::READY,
  ::com::rdk::hal::hdmiinput::State::STARTING,
  ::com::rdk::hal::hdmiinput::State::STARTED,
  ::com::rdk::hal::hdmiinput::State::STOPPING,
  ::com::rdk::hal::hdmiinput::State::CLOSING,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

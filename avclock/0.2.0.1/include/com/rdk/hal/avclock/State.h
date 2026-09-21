#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
enum class State : int32_t {
  UNKNOWN = 0,
  CLOSED = 1,
  OPENING = 2,
  READY = 3,
  STARTING = 4,
  STARTED = 5,
  FLUSHING = 6,
  STOPPING = 7,
  CLOSING = 8,
};
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace avclock {
[[nodiscard]] static inline std::string toString(State val) {
  switch(val) {
  case State::UNKNOWN:
    return "UNKNOWN";
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
  case State::FLUSHING:
    return "FLUSHING";
  case State::STOPPING:
    return "STOPPING";
  case State::CLOSING:
    return "CLOSING";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::avclock::State, 9> enum_values<::com::rdk::hal::avclock::State> = {
  ::com::rdk::hal::avclock::State::UNKNOWN,
  ::com::rdk::hal::avclock::State::CLOSED,
  ::com::rdk::hal::avclock::State::OPENING,
  ::com::rdk::hal::avclock::State::READY,
  ::com::rdk::hal::avclock::State::STARTING,
  ::com::rdk::hal::avclock::State::STARTED,
  ::com::rdk::hal::avclock::State::FLUSHING,
  ::com::rdk::hal::avclock::State::STOPPING,
  ::com::rdk::hal::avclock::State::CLOSING,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

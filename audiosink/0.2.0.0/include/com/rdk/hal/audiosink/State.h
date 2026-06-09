#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
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
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
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
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiosink::State, 9> enum_values<::com::rdk::hal::audiosink::State> = {
  ::com::rdk::hal::audiosink::State::UNKNOWN,
  ::com::rdk::hal::audiosink::State::CLOSED,
  ::com::rdk::hal::audiosink::State::OPENING,
  ::com::rdk::hal::audiosink::State::READY,
  ::com::rdk::hal::audiosink::State::STARTING,
  ::com::rdk::hal::audiosink::State::STARTED,
  ::com::rdk::hal::audiosink::State::FLUSHING,
  ::com::rdk::hal::audiosink::State::STOPPING,
  ::com::rdk::hal::audiosink::State::CLOSING,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

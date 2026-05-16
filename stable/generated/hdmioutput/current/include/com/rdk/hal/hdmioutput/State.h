#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
enum class State : int32_t {
  UNKNOWN = 0,
  CLOSED = 1,
  OPENING = 2,
  READY = 3,
  STARTING = 4,
  STARTED = 5,
  STOPPING = 6,
  CLOSING = 7,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
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
  case State::STOPPING:
    return "STOPPING";
  case State::CLOSING:
    return "CLOSING";
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
constexpr inline std::array<::com::rdk::hal::hdmioutput::State, 8> enum_values<::com::rdk::hal::hdmioutput::State> = {
  ::com::rdk::hal::hdmioutput::State::UNKNOWN,
  ::com::rdk::hal::hdmioutput::State::CLOSED,
  ::com::rdk::hal::hdmioutput::State::OPENING,
  ::com::rdk::hal::hdmioutput::State::READY,
  ::com::rdk::hal::hdmioutput::State::STARTING,
  ::com::rdk::hal::hdmioutput::State::STARTED,
  ::com::rdk::hal::hdmioutput::State::STOPPING,
  ::com::rdk::hal::hdmioutput::State::CLOSING,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
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
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videosink {
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
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::videosink::State, 9> enum_values<::com::rdk::hal::videosink::State> = {
  ::com::rdk::hal::videosink::State::UNKNOWN,
  ::com::rdk::hal::videosink::State::CLOSED,
  ::com::rdk::hal::videosink::State::OPENING,
  ::com::rdk::hal::videosink::State::READY,
  ::com::rdk::hal::videosink::State::STARTING,
  ::com::rdk::hal::videosink::State::STARTED,
  ::com::rdk::hal::videosink::State::FLUSHING,
  ::com::rdk::hal::videosink::State::STOPPING,
  ::com::rdk::hal::videosink::State::CLOSING,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
enum class State : int8_t {
  STOPPED = 0,
  STARTING = 1,
  STARTED = 2,
  STOPPING = 3,
  ERROR = 4,
};
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
[[nodiscard]] static inline std::string toString(State val) {
  switch(val) {
  case State::STOPPED:
    return "STOPPED";
  case State::STARTING:
    return "STARTING";
  case State::STARTED:
    return "STARTED";
  case State::STOPPING:
    return "STOPPING";
  case State::ERROR:
    return "ERROR";
  default:
    return std::to_string(static_cast<int8_t>(val));
  }
}
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::sensor::motion::State, 5> enum_values<::com::rdk::hal::sensor::motion::State> = {
  ::com::rdk::hal::sensor::motion::State::STOPPED,
  ::com::rdk::hal::sensor::motion::State::STARTING,
  ::com::rdk::hal::sensor::motion::State::STARTED,
  ::com::rdk::hal::sensor::motion::State::STOPPING,
  ::com::rdk::hal::sensor::motion::State::ERROR,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

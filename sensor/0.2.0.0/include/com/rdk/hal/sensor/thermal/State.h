#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace thermal {
enum class State : int8_t {
  NORMAL = 0,
  CRITICAL_TEMPERATURE_EXCEEDED = 1,
  CRITICAL_TEMPERATURE_RECOVERED = 2,
  CRITICAL_SHUTDOWN_IMMINENT = 3,
};
}  // namespace thermal
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace thermal {
[[nodiscard]] static inline std::string toString(State val) {
  switch(val) {
  case State::NORMAL:
    return "NORMAL";
  case State::CRITICAL_TEMPERATURE_EXCEEDED:
    return "CRITICAL_TEMPERATURE_EXCEEDED";
  case State::CRITICAL_TEMPERATURE_RECOVERED:
    return "CRITICAL_TEMPERATURE_RECOVERED";
  case State::CRITICAL_SHUTDOWN_IMMINENT:
    return "CRITICAL_SHUTDOWN_IMMINENT";
  default:
    return std::to_string(static_cast<int8_t>(val));
  }
}
}  // namespace thermal
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::sensor::thermal::State, 4> enum_values<::com::rdk::hal::sensor::thermal::State> = {
  ::com::rdk::hal::sensor::thermal::State::NORMAL,
  ::com::rdk::hal::sensor::thermal::State::CRITICAL_TEMPERATURE_EXCEEDED,
  ::com::rdk::hal::sensor::thermal::State::CRITICAL_TEMPERATURE_RECOVERED,
  ::com::rdk::hal::sensor::thermal::State::CRITICAL_SHUTDOWN_IMMINENT,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

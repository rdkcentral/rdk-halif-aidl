#pragma once
// @aidl-doc
/**
 * @file State.h
 * @brief Lifecycle states for a motion sensor instance.
 *
 * Typical transitions:
 *  - STOPPED → STARTING → STARTED
 *  - STARTED → STOPPING → STOPPED
 *  - Any state → ERROR on fault
 */

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
  // @aidl-doc
  /** @brief Sensor is inactive; no monitoring in progress. */
  STOPPED = 0,
  // @aidl-doc
  /** @brief Sensor is initializing (configure, warm-up, timing windows). */
  STARTING = 1,
  // @aidl-doc
  /** @brief Sensor is actively monitoring for motion/no-motion. */
  STARTED = 2,
  // @aidl-doc
  /** @brief Sensor is stopping (tear-down in progress). */
  STOPPING = 3,
  // @aidl-doc
  /** @brief A fault occurred (I/O error, probe failure, etc.). */
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

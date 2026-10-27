#pragma once
// @aidl-doc
/**
 * @file State.h
 * @brief Lifecycle states for a panel output instance.
 */

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
enum class State : int32_t {
  // @aidl-doc
  /** The controller is stopped; start() may be called. */
  STOPPED = 0,
  // @aidl-doc
  /** A start() is in progress. */
  STARTING = 1,
  // @aidl-doc
  /** The panel output is running; control operations are valid. */
  STARTED = 2,
  // @aidl-doc
  /** A stop() is in progress. */
  STOPPING = 3,
  // @aidl-doc
  /** A state transition failed; release the controller with close(). */
  ERROR = 4,
};
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace panel {
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
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::panel::State, 5> enum_values<::com::rdk::hal::panel::State> = {
  ::com::rdk::hal::panel::State::STOPPED,
  ::com::rdk::hal::panel::State::STARTING,
  ::com::rdk::hal::panel::State::STARTED,
  ::com::rdk::hal::panel::State::STOPPING,
  ::com::rdk::hal::panel::State::ERROR,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

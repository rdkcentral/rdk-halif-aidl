#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
// @aidl-doc
/**
 * @brief     HDMI Output component states.
 *
 * Defines the lifecycle states for HDMI output resources.
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 */
enum class State : int32_t {
  // @aidl-doc
  /**
   *  The HAL server component session is initialising, before transitioning to a closed state
   *  or it reflects the state of an unknown HAL resource.
   */
  UNKNOWN = 0,
  // @aidl-doc
  /** Initial state entered when the service connection is established. */
  CLOSED = 1,
  // @aidl-doc
  /** The HAL server component session is transitioning from closed to ready state. */
  OPENING = 2,
  // @aidl-doc
  /** The HAL server component session is open and ready to start, but in a stopped state. */
  READY = 3,
  // @aidl-doc
  /** The HAL server component session is transitioning from ready to started state. */
  STARTING = 4,
  // @aidl-doc
  /** The opened HAL server component session has been started. */
  STARTED = 5,
  // @aidl-doc
  /**
   * The started HAL server component session is stopping.
   * Once stopped, the HAL server component session enters the ready state.
   */
  STOPPING = 6,
  // @aidl-doc
  /** The HAL server component session is transitioning from ready to closed state. */
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

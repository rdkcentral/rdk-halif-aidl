#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
// @aidl-doc
/**
 * @brief     HAL component states for a composite input port.
 *
 * State transitions are driven by open(), close() on ICompositeInputPort
 * and start(), stop() on ICompositeInputController.
 * @author    Gerald Weatherup
 */
enum class State : int32_t {
  // @aidl-doc
  /**
   * Initial state. The port is not open; no controller exists.
   * Entered on service connection or after a successful close().
   */
  CLOSED = 0,
  // @aidl-doc
  /**
   * Transitional state entered immediately after open() is called.
   * The HAL is allocating resources and initialising the port.
   */
  OPENING = 1,
  // @aidl-doc
  /**
   * The port is open and ready to be started.
   * open() completes here; close() may be called from this state.
   */
  READY = 2,
  // @aidl-doc
  /** Transitional state entered immediately after start() is called. */
  STARTING = 3,
  // @aidl-doc
  /**
   * The port is active and presenting video.
   * stop() may be called from this state.
   */
  STARTED = 4,
  // @aidl-doc
  /** Transitional state entered immediately after stop() is called. */
  STOPPING = 5,
  // @aidl-doc
  /** Transitional state entered immediately after close() is called. */
  CLOSING = 6,
};
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
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
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::compositeinput::State, 7> enum_values<::com::rdk::hal::compositeinput::State> = {
  ::com::rdk::hal::compositeinput::State::CLOSED,
  ::com::rdk::hal::compositeinput::State::OPENING,
  ::com::rdk::hal::compositeinput::State::READY,
  ::com::rdk::hal::compositeinput::State::STARTING,
  ::com::rdk::hal::compositeinput::State::STARTED,
  ::com::rdk::hal::compositeinput::State::STOPPING,
  ::com::rdk::hal::compositeinput::State::CLOSING,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

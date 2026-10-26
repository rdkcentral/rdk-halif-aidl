#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
// @aidl-doc
/**
 *  @brief     HDMI Input Signal State enumeration.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 */
enum class SignalState : int32_t {
  // @aidl-doc
  /**
   * Unknown signal state.
   *
   * Indicates the state is not yet determined or the operation is not applicable. Clients should poll or retry later.
   */
  UNKNOWN = -1,
  // @aidl-doc
  /**
   * No signal detected.
   *
   * HDMI source device may be disconnected, powered off or in standby.
   */
  NO_SIGNAL = 0,
  // @aidl-doc
  /**
   * Unstable signal detected.
   *
   * Potential problem with cable, cable connection, port or transitionally during start up.
   */
  UNSTABLE = 1,
  // @aidl-doc
  /**
   * Unsupported signal detected.
   *
   * An aspect of the incoming signal is out of range of the HDMI port capabilities.
   * e.g. resolution, color depth, frame rate.
   */
  NOT_SUPPORTED = 2,
  // @aidl-doc
  /** A stable and supported signal is detected and locked. */
  LOCKED = 3,
};
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
[[nodiscard]] static inline std::string toString(SignalState val) {
  switch(val) {
  case SignalState::UNKNOWN:
    return "UNKNOWN";
  case SignalState::NO_SIGNAL:
    return "NO_SIGNAL";
  case SignalState::UNSTABLE:
    return "UNSTABLE";
  case SignalState::NOT_SUPPORTED:
    return "NOT_SUPPORTED";
  case SignalState::LOCKED:
    return "LOCKED";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::hdmiinput::SignalState, 5> enum_values<::com::rdk::hal::hdmiinput::SignalState> = {
  ::com::rdk::hal::hdmiinput::SignalState::UNKNOWN,
  ::com::rdk::hal::hdmiinput::SignalState::NO_SIGNAL,
  ::com::rdk::hal::hdmiinput::SignalState::UNSTABLE,
  ::com::rdk::hal::hdmiinput::SignalState::NOT_SUPPORTED,
  ::com::rdk::hal::hdmiinput::SignalState::LOCKED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

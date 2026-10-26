#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace deepsleep {
// @aidl-doc
/**
 *  @brief     Deep sleep wake up triggers.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
enum class WakeUpTrigger : int32_t {
  // @aidl-doc
  /**
   * Deep sleep wakeup reason is unknown.
   * This should never be used but is provided if the wake reason cannot be
   * determined due to an internal error.
   */
  ERROR_UNKNOWN = -1,
  // @aidl-doc
  /**
   * Deep sleep wakeup reason is due to IR Remote.
   * The specific IR codes to wake upon are product specific and
   * determined by the vendor layer implementation.
   */
  RCU_IR = 0,
  // @aidl-doc
  /** Deep sleep wakeup reason is due to RCU Bluetooth Remote. */
  RCU_BT = 1,
  // @aidl-doc
  /** Deep sleep wakeup reason is due to RCU RF4CE Remote. */
  RCU_RF4CE = 2,
  // @aidl-doc
  /**
   * Deep sleep wakeup reason is is due to LAN.
   * The standard WOL magic packet is used.
   */
  LAN = 3,
  // @aidl-doc
  /**
   * Deep sleep wakeup reason is is due to Wireless LAN.
   * The standard WOW magic packet is used.
   */
  WLAN = 4,
  // @aidl-doc
  /** Deep sleep wakeup reason is is due to Clock Timer. */
  TIMER = 5,
  // @aidl-doc
  /** Deep sleep wakeup reason is is due to Front Panel Button. */
  FRONT_PANEL = 6,
  // @aidl-doc
  /** Deep sleep wakeup reason is due to HDMI CEC Message. */
  CEC = 7,
  // @aidl-doc
  /** Deep sleep wakeup reason is due to Motion Detection. */
  PRESENCE = 8,
  // @aidl-doc
  /** Deep sleep wakeup reason is due to User Voice. */
  VOICE = 9,
};
}  // namespace deepsleep
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace deepsleep {
[[nodiscard]] static inline std::string toString(WakeUpTrigger val) {
  switch(val) {
  case WakeUpTrigger::ERROR_UNKNOWN:
    return "ERROR_UNKNOWN";
  case WakeUpTrigger::RCU_IR:
    return "RCU_IR";
  case WakeUpTrigger::RCU_BT:
    return "RCU_BT";
  case WakeUpTrigger::RCU_RF4CE:
    return "RCU_RF4CE";
  case WakeUpTrigger::LAN:
    return "LAN";
  case WakeUpTrigger::WLAN:
    return "WLAN";
  case WakeUpTrigger::TIMER:
    return "TIMER";
  case WakeUpTrigger::FRONT_PANEL:
    return "FRONT_PANEL";
  case WakeUpTrigger::CEC:
    return "CEC";
  case WakeUpTrigger::PRESENCE:
    return "PRESENCE";
  case WakeUpTrigger::VOICE:
    return "VOICE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace deepsleep
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::deepsleep::WakeUpTrigger, 11> enum_values<::com::rdk::hal::deepsleep::WakeUpTrigger> = {
  ::com::rdk::hal::deepsleep::WakeUpTrigger::ERROR_UNKNOWN,
  ::com::rdk::hal::deepsleep::WakeUpTrigger::RCU_IR,
  ::com::rdk::hal::deepsleep::WakeUpTrigger::RCU_BT,
  ::com::rdk::hal::deepsleep::WakeUpTrigger::RCU_RF4CE,
  ::com::rdk::hal::deepsleep::WakeUpTrigger::LAN,
  ::com::rdk::hal::deepsleep::WakeUpTrigger::WLAN,
  ::com::rdk::hal::deepsleep::WakeUpTrigger::TIMER,
  ::com::rdk::hal::deepsleep::WakeUpTrigger::FRONT_PANEL,
  ::com::rdk::hal::deepsleep::WakeUpTrigger::CEC,
  ::com::rdk::hal::deepsleep::WakeUpTrigger::PRESENCE,
  ::com::rdk::hal::deepsleep::WakeUpTrigger::VOICE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

#pragma once
// @aidl-doc
/**
 * @file State.h
 * @brief High-level current thermal state for quick health checks.
 *
 * @details
 * Each thermal sensor has its own state. Thresholds named below are that
 * sensor's HFP `triggers` values.
 */

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
  // @aidl-doc
  /**
   * @brief Normal thermal conditions; no mitigation active.
   *
   * Entered at service start when the sensor is below its
   * critical_temperature_exceeded_celsius, and from
   * CRITICAL_TEMPERATURE_EXCEEDED when the sensor falls below its
   * critical_temperature_recovered_celsius.
   */
  NORMAL = 0,
  // @aidl-doc
  /**
   * @brief Temperature has exceeded a critical threshold.
   *  Platform will be in active mitigation if possible.
   *
   * Entered from NORMAL when the sensor reaches its
   * critical_temperature_exceeded_celsius, and at service start when the
   * sensor is at or above its critical_temperature_exceeded_celsius and
   * below its entering_critical_shutdown_celsius.
   */
  CRITICAL_TEMPERATURE_EXCEEDED = 1,
  // @aidl-doc
  /**
   * @brief Temperature has recovered from a critical event.
   *
   * @deprecated Deprecated since 2026-09-25. The HAL does not enter this
   * state: CRITICAL_TEMPERATURE_EXCEEDED returns directly to NORMAL.
   * Reason: recovery timing is product thermal policy, not interface state.
   */
  CRITICAL_TEMPERATURE_RECOVERED __attribute__((deprecated("Deprecated since 2026-09-25. The HAL does not enter this state: CRITICAL_TEMPERATURE_EXCEEDED returns directly to NORMAL. Reason: recovery timing is product thermal policy, not interface state."))) = 2,
  // @aidl-doc
  /**
   * @brief Shutdown is imminent due to critical thermal breach.
   *
   * Entered from NORMAL or CRITICAL_TEMPERATURE_EXCEEDED when the sensor
   * reaches its entering_critical_shutdown_celsius, or at service start
   * when the sensor is already at or above it. Terminal: no transition leaves
   * this state.
   *
   * The HAL thermal policy service initiates the shutdown autonomously.
   * Clients receiving this event via IThermalEventListener should
   * perform only time-critical cleanup (flush caches, persist critical
   * state) and must not attempt to manage the reboot themselves.
   *
   * The thermal HAL records the shutdown reason so that on the next boot
   * it can be reported by the Boot Reason HAL via IBootReason.getBootCause() as
   * BootCause.THERMAL_RESET.
   */
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
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
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
#pragma clang diagnostic pop
}  // namespace thermal
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
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

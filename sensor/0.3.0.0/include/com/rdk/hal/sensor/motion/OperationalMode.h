#pragma once
// @aidl-doc
/**
 * @file OperationalMode.h
 * @brief Operation trigger mode for motion detection.
 *
 * When {@link IMotionSensorController#start(StartConfig)} is called,
 * the sensor fires events only for the mode specified in StartConfig.operationalMode.
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
enum class OperationalMode : int8_t {
  // @aidl-doc
  /** @brief Report an event when motion is detected. */
  MOTION = 0,
  // @aidl-doc
  /** @brief Report an event when a period of no motion is achieved. */
  NO_MOTION = 1,
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
[[nodiscard]] static inline std::string toString(OperationalMode val) {
  switch(val) {
  case OperationalMode::MOTION:
    return "MOTION";
  case OperationalMode::NO_MOTION:
    return "NO_MOTION";
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
constexpr inline std::array<::com::rdk::hal::sensor::motion::OperationalMode, 2> enum_values<::com::rdk::hal::sensor::motion::OperationalMode> = {
  ::com::rdk::hal::sensor::motion::OperationalMode::MOTION,
  ::com::rdk::hal::sensor::motion::OperationalMode::NO_MOTION,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

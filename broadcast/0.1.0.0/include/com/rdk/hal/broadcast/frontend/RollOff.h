#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
enum class RollOff : int32_t {
  UNDEFINED = 0,
  AUTO = 1,
  ROLL_OFF_0_35 = 2,
  ROLL_OFF_0_25 = 3,
  ROLL_OFF_0_20 = 4,
  ROLL_OFF_0_15 = 5,
  ROLL_OFF_0_10 = 6,
  ROLL_OFF_0_05 = 7,
};
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
[[nodiscard]] static inline std::string toString(RollOff val) {
  switch(val) {
  case RollOff::UNDEFINED:
    return "UNDEFINED";
  case RollOff::AUTO:
    return "AUTO";
  case RollOff::ROLL_OFF_0_35:
    return "ROLL_OFF_0_35";
  case RollOff::ROLL_OFF_0_25:
    return "ROLL_OFF_0_25";
  case RollOff::ROLL_OFF_0_20:
    return "ROLL_OFF_0_20";
  case RollOff::ROLL_OFF_0_15:
    return "ROLL_OFF_0_15";
  case RollOff::ROLL_OFF_0_10:
    return "ROLL_OFF_0_10";
  case RollOff::ROLL_OFF_0_05:
    return "ROLL_OFF_0_05";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::RollOff, 8> enum_values<::com::rdk::hal::broadcast::frontend::RollOff> = {
  ::com::rdk::hal::broadcast::frontend::RollOff::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::RollOff::AUTO,
  ::com::rdk::hal::broadcast::frontend::RollOff::ROLL_OFF_0_35,
  ::com::rdk::hal::broadcast::frontend::RollOff::ROLL_OFF_0_25,
  ::com::rdk::hal::broadcast::frontend::RollOff::ROLL_OFF_0_20,
  ::com::rdk::hal::broadcast::frontend::RollOff::ROLL_OFF_0_15,
  ::com::rdk::hal::broadcast::frontend::RollOff::ROLL_OFF_0_10,
  ::com::rdk::hal::broadcast::frontend::RollOff::ROLL_OFF_0_05,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

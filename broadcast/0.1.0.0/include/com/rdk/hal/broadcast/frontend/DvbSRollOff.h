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
// @aidl-doc
/**
 * @brief Roll-off enumeration.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class DvbSRollOff : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** Auto-selected. */
  AUTO = 1,
  // @aidl-doc
  /** Roll off value 0.35 used by DVB-S2 and DVB-S2X. */
  ROLL_OFF_0_35 = 2,
  // @aidl-doc
  /** Roll off value 0.25 used by DVB-S2 and DVB-S2X. */
  ROLL_OFF_0_25 = 3,
  // @aidl-doc
  /** Roll off value 0.20 used by DVB-S2 and DVB-S2X. */
  ROLL_OFF_0_20 = 4,
  // @aidl-doc
  /** Roll off value 0.15 used by DVB-S2X. */
  ROLL_OFF_0_15 = 5,
  // @aidl-doc
  /** Roll off value 0.10 used by DVB-S2X. */
  ROLL_OFF_0_10 = 6,
  // @aidl-doc
  /** Roll off value 0.05 used by DVB-S2X. */
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
[[nodiscard]] static inline std::string toString(DvbSRollOff val) {
  switch(val) {
  case DvbSRollOff::UNDEFINED:
    return "UNDEFINED";
  case DvbSRollOff::AUTO:
    return "AUTO";
  case DvbSRollOff::ROLL_OFF_0_35:
    return "ROLL_OFF_0_35";
  case DvbSRollOff::ROLL_OFF_0_25:
    return "ROLL_OFF_0_25";
  case DvbSRollOff::ROLL_OFF_0_20:
    return "ROLL_OFF_0_20";
  case DvbSRollOff::ROLL_OFF_0_15:
    return "ROLL_OFF_0_15";
  case DvbSRollOff::ROLL_OFF_0_10:
    return "ROLL_OFF_0_10";
  case DvbSRollOff::ROLL_OFF_0_05:
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::DvbSRollOff, 8> enum_values<::com::rdk::hal::broadcast::frontend::DvbSRollOff> = {
  ::com::rdk::hal::broadcast::frontend::DvbSRollOff::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::DvbSRollOff::AUTO,
  ::com::rdk::hal::broadcast::frontend::DvbSRollOff::ROLL_OFF_0_35,
  ::com::rdk::hal::broadcast::frontend::DvbSRollOff::ROLL_OFF_0_25,
  ::com::rdk::hal::broadcast::frontend::DvbSRollOff::ROLL_OFF_0_20,
  ::com::rdk::hal::broadcast::frontend::DvbSRollOff::ROLL_OFF_0_15,
  ::com::rdk::hal::broadcast::frontend::DvbSRollOff::ROLL_OFF_0_10,
  ::com::rdk::hal::broadcast::frontend::DvbSRollOff::ROLL_OFF_0_05,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

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
 * @brief DVB-S2/S2X pilot symbols defined for DVB-S frontend tuning.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class DvbSPilot : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** DVB-S2/S2X pilot symbols are auto-detected. */
  AUTO = 1,
  // @aidl-doc
  /** DVB-S2/S2X pilot symbols are present. */
  ON = 2,
  // @aidl-doc
  /** DVB-S2/S2X pilot symbols are absent. */
  OFF = 3,
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
[[nodiscard]] static inline std::string toString(DvbSPilot val) {
  switch(val) {
  case DvbSPilot::UNDEFINED:
    return "UNDEFINED";
  case DvbSPilot::AUTO:
    return "AUTO";
  case DvbSPilot::ON:
    return "ON";
  case DvbSPilot::OFF:
    return "OFF";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::DvbSPilot, 4> enum_values<::com::rdk::hal::broadcast::frontend::DvbSPilot> = {
  ::com::rdk::hal::broadcast::frontend::DvbSPilot::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::DvbSPilot::AUTO,
  ::com::rdk::hal::broadcast::frontend::DvbSPilot::ON,
  ::com::rdk::hal::broadcast::frontend::DvbSPilot::OFF,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

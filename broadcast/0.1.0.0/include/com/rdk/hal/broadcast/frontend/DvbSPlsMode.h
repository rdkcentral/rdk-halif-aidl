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
 * @brief DVB-S2/S2X physical-layer scrambling sequence (PLS) modes defined for DVB-S frontend tuning.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class DvbSPlsMode : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** Auto-selected. */
  AUTO = 1,
  // @aidl-doc
  /** DVB-S2/S2X root physical-layer scrambling sequence. */
  ROOT = 2,
  // @aidl-doc
  /** DVB-S2/S2X gold physical-layer scrambling sequence. */
  GOLD = 3,
  // @aidl-doc
  /** DVB-S2/S2X combined physical-layer scrambling sequence. */
  COMBO = 4,
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
[[nodiscard]] static inline std::string toString(DvbSPlsMode val) {
  switch(val) {
  case DvbSPlsMode::UNDEFINED:
    return "UNDEFINED";
  case DvbSPlsMode::AUTO:
    return "AUTO";
  case DvbSPlsMode::ROOT:
    return "ROOT";
  case DvbSPlsMode::GOLD:
    return "GOLD";
  case DvbSPlsMode::COMBO:
    return "COMBO";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::DvbSPlsMode, 5> enum_values<::com::rdk::hal::broadcast::frontend::DvbSPlsMode> = {
  ::com::rdk::hal::broadcast::frontend::DvbSPlsMode::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::DvbSPlsMode::AUTO,
  ::com::rdk::hal::broadcast::frontend::DvbSPlsMode::ROOT,
  ::com::rdk::hal::broadcast::frontend::DvbSPlsMode::GOLD,
  ::com::rdk::hal::broadcast::frontend::DvbSPlsMode::COMBO,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

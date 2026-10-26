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
 * @brief DVB-S standard enumeration.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class DvbSStandard : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** Auto-select the standard to use. */
  AUTO = 1,
  // @aidl-doc
  /** Use S only. */
  S = 2,
  // @aidl-doc
  /** Use S2 only. */
  S2 = 3,
  // @aidl-doc
  /** Use S2X only. */
  S2X = 4,
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
[[nodiscard]] static inline std::string toString(DvbSStandard val) {
  switch(val) {
  case DvbSStandard::UNDEFINED:
    return "UNDEFINED";
  case DvbSStandard::AUTO:
    return "AUTO";
  case DvbSStandard::S:
    return "S";
  case DvbSStandard::S2:
    return "S2";
  case DvbSStandard::S2X:
    return "S2X";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::DvbSStandard, 5> enum_values<::com::rdk::hal::broadcast::frontend::DvbSStandard> = {
  ::com::rdk::hal::broadcast::frontend::DvbSStandard::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::DvbSStandard::AUTO,
  ::com::rdk::hal::broadcast::frontend::DvbSStandard::S,
  ::com::rdk::hal::broadcast::frontend::DvbSStandard::S2,
  ::com::rdk::hal::broadcast::frontend::DvbSStandard::S2X,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

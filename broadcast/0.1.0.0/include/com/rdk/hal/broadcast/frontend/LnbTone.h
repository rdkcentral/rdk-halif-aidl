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
 * @brief LNB tone enumeration.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class LnbTone : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** No tone is sent to the Lnb. */
  NONE = 1,
  // @aidl-doc
  /** A continuous tone of 22 kHz is sent to the Lnb. */
  CONTINUOUS = 2,
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
[[nodiscard]] static inline std::string toString(LnbTone val) {
  switch(val) {
  case LnbTone::UNDEFINED:
    return "UNDEFINED";
  case LnbTone::NONE:
    return "NONE";
  case LnbTone::CONTINUOUS:
    return "CONTINUOUS";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::LnbTone, 3> enum_values<::com::rdk::hal::broadcast::frontend::LnbTone> = {
  ::com::rdk::hal::broadcast::frontend::LnbTone::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::LnbTone::NONE,
  ::com::rdk::hal::broadcast::frontend::LnbTone::CONTINUOUS,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

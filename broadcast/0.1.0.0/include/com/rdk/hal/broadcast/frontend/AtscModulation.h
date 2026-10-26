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
 * @brief Available modulations.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class AtscModulation : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** Auto-selected modulation. */
  AUTO = 1,
  // @aidl-doc
  /** VSB_8. */
  VSB_8 = 2,
  // @aidl-doc
  /** VSB_16. */
  VSB_16 = 3,
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
[[nodiscard]] static inline std::string toString(AtscModulation val) {
  switch(val) {
  case AtscModulation::UNDEFINED:
    return "UNDEFINED";
  case AtscModulation::AUTO:
    return "AUTO";
  case AtscModulation::VSB_8:
    return "VSB_8";
  case AtscModulation::VSB_16:
    return "VSB_16";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::AtscModulation, 4> enum_values<::com::rdk::hal::broadcast::frontend::AtscModulation> = {
  ::com::rdk::hal::broadcast::frontend::AtscModulation::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::AtscModulation::AUTO,
  ::com::rdk::hal::broadcast::frontend::AtscModulation::VSB_8,
  ::com::rdk::hal::broadcast::frontend::AtscModulation::VSB_16,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

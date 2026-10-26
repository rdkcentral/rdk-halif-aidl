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
 * @brief LNB voltage enumeration.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class LnbVoltage : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** No voltage on the LNB Controller - The voltage is zero. */
  NONE = 1,
  // @aidl-doc
  /** The voltage is 13 volt. */
  V13 = 13,
  // @aidl-doc
  /** The voltage is 14 volt. */
  V14 = 14,
  // @aidl-doc
  /** The voltage is 15 volt. */
  V15 = 15,
  // @aidl-doc
  /** The voltage is 18 volt. */
  V18 = 18,
  // @aidl-doc
  /** The voltage is 19 volt. */
  V19 = 19,
  // @aidl-doc
  /** The voltage is 20 volt. */
  V20 = 20,
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
[[nodiscard]] static inline std::string toString(LnbVoltage val) {
  switch(val) {
  case LnbVoltage::UNDEFINED:
    return "UNDEFINED";
  case LnbVoltage::NONE:
    return "NONE";
  case LnbVoltage::V13:
    return "V13";
  case LnbVoltage::V14:
    return "V14";
  case LnbVoltage::V15:
    return "V15";
  case LnbVoltage::V18:
    return "V18";
  case LnbVoltage::V19:
    return "V19";
  case LnbVoltage::V20:
    return "V20";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::LnbVoltage, 8> enum_values<::com::rdk::hal::broadcast::frontend::LnbVoltage> = {
  ::com::rdk::hal::broadcast::frontend::LnbVoltage::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::LnbVoltage::NONE,
  ::com::rdk::hal::broadcast::frontend::LnbVoltage::V13,
  ::com::rdk::hal::broadcast::frontend::LnbVoltage::V14,
  ::com::rdk::hal::broadcast::frontend::LnbVoltage::V15,
  ::com::rdk::hal::broadcast::frontend::LnbVoltage::V18,
  ::com::rdk::hal::broadcast::frontend::LnbVoltage::V19,
  ::com::rdk::hal::broadcast::frontend::LnbVoltage::V20,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

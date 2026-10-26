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
 * @brief DVB-C code rate enum.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class DvbCCodeRate : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** The code rate is auto-detected. */
  AUTO = 1,
  // @aidl-doc
  /** CR_1_2 */
  CR_1_2 = 2,
  // @aidl-doc
  /** CR_2_3 */
  CR_2_3 = 3,
  // @aidl-doc
  /** CR_3_4 */
  CR_3_4 = 4,
  // @aidl-doc
  /** CR_3_5 */
  CR_3_5 = 5,
  // @aidl-doc
  /** CR_4_5 */
  CR_4_5 = 6,
  // @aidl-doc
  /** CR_5_6 */
  CR_5_6 = 7,
  // @aidl-doc
  /** CR_6_7 */
  CR_6_7 = 8,
  // @aidl-doc
  /** CR_8_9 */
  CR_8_9 = 9,
  // @aidl-doc
  /** CR_9_10 */
  CR_9_10 = 10,
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
[[nodiscard]] static inline std::string toString(DvbCCodeRate val) {
  switch(val) {
  case DvbCCodeRate::UNDEFINED:
    return "UNDEFINED";
  case DvbCCodeRate::AUTO:
    return "AUTO";
  case DvbCCodeRate::CR_1_2:
    return "CR_1_2";
  case DvbCCodeRate::CR_2_3:
    return "CR_2_3";
  case DvbCCodeRate::CR_3_4:
    return "CR_3_4";
  case DvbCCodeRate::CR_3_5:
    return "CR_3_5";
  case DvbCCodeRate::CR_4_5:
    return "CR_4_5";
  case DvbCCodeRate::CR_5_6:
    return "CR_5_6";
  case DvbCCodeRate::CR_6_7:
    return "CR_6_7";
  case DvbCCodeRate::CR_8_9:
    return "CR_8_9";
  case DvbCCodeRate::CR_9_10:
    return "CR_9_10";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::DvbCCodeRate, 11> enum_values<::com::rdk::hal::broadcast::frontend::DvbCCodeRate> = {
  ::com::rdk::hal::broadcast::frontend::DvbCCodeRate::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::DvbCCodeRate::AUTO,
  ::com::rdk::hal::broadcast::frontend::DvbCCodeRate::CR_1_2,
  ::com::rdk::hal::broadcast::frontend::DvbCCodeRate::CR_2_3,
  ::com::rdk::hal::broadcast::frontend::DvbCCodeRate::CR_3_4,
  ::com::rdk::hal::broadcast::frontend::DvbCCodeRate::CR_3_5,
  ::com::rdk::hal::broadcast::frontend::DvbCCodeRate::CR_4_5,
  ::com::rdk::hal::broadcast::frontend::DvbCCodeRate::CR_5_6,
  ::com::rdk::hal::broadcast::frontend::DvbCCodeRate::CR_6_7,
  ::com::rdk::hal::broadcast::frontend::DvbCCodeRate::CR_8_9,
  ::com::rdk::hal::broadcast::frontend::DvbCCodeRate::CR_9_10,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

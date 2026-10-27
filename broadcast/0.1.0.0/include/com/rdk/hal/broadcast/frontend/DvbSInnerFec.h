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
 * @brief DVB-S, DVB-S2, and DVB-S2X inner FEC enum.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class DvbSInnerFec : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /** The inner FEC code rate is auto-detected. */
  AUTO = 1,
  // @aidl-doc
  /** FEC_1_2 applies to DVB-S, DVB-S2, and DVB-S2X. */
  FEC_1_2 = 2,
  // @aidl-doc
  /** FEC_1_3 applies to DVB-S2 and DVB-S2X. */
  FEC_1_3 = 3,
  // @aidl-doc
  /** FEC_1_4 applies to DVB-S2 and DVB-S2X. */
  FEC_1_4 = 4,
  // @aidl-doc
  /** FEC_1_5 applies to DVB-S2X. */
  FEC_1_5 = 5,
  // @aidl-doc
  /** FEC_2_3 applies to DVB-S, DVB-S2, and DVB-S2X. */
  FEC_2_3 = 6,
  // @aidl-doc
  /** FEC_2_5 applies to DVB-S2 and DVB-S2X. */
  FEC_2_5 = 7,
  // @aidl-doc
  /** FEC_2_9 applies to DVB-S2X. */
  FEC_2_9 = 8,
  // @aidl-doc
  /** FEC_3_4 applies to DVB-S, DVB-S2, and DVB-S2X. */
  FEC_3_4 = 9,
  // @aidl-doc
  /** FEC_3_5 applies to DVB-S2 and DVB-S2X. */
  FEC_3_5 = 10,
  // @aidl-doc
  /** FEC_4_5 applies to DVB-S2 and DVB-S2X. */
  FEC_4_5 = 11,
  // @aidl-doc
  /** FEC_4_15 applies to DVB-S2X. */
  FEC_4_15 = 12,
  // @aidl-doc
  /** FEC_5_6 applies to DVB-S, DVB-S2, and DVB-S2X. */
  FEC_5_6 = 13,
  // @aidl-doc
  /** FEC_7_8 applies to DVB-S. */
  FEC_7_8 = 14,
  // @aidl-doc
  /** FEC_7_9 applies to DVB-S2X. */
  FEC_7_9 = 15,
  // @aidl-doc
  /** FEC_7_10 applies to DVB-S2X. */
  FEC_7_10 = 16,
  // @aidl-doc
  /** FEC_7_15 applies to DVB-S2X. */
  FEC_7_15 = 17,
  // @aidl-doc
  /** FEC_8_9 applies to DVB-S2 and DVB-S2X. */
  FEC_8_9 = 18,
  // @aidl-doc
  /** FEC_8_15 applies to DVB-S2X. */
  FEC_8_15 = 19,
  // @aidl-doc
  /** FEC_9_10 applies to DVB-S2 and DVB-S2X. */
  FEC_9_10 = 20,
  // @aidl-doc
  /** FEC_11_15 applies to DVB-S2X. */
  FEC_11_15 = 21,
  // @aidl-doc
  /** FEC_11_20 applies to DVB-S2X. */
  FEC_11_20 = 22,
  // @aidl-doc
  /** FEC_11_45 applies to DVB-S2X. */
  FEC_11_45 = 23,
  // @aidl-doc
  /** FEC_13_18 applies to DVB-S2X. */
  FEC_13_18 = 24,
  // @aidl-doc
  /** FEC_14_45 applies to DVB-S2X. */
  FEC_14_45 = 25,
  // @aidl-doc
  /** FEC_23_36 applies to DVB-S2X. */
  FEC_23_36 = 26,
  // @aidl-doc
  /** FEC_25_36 applies to DVB-S2X. */
  FEC_25_36 = 27,
  // @aidl-doc
  /** FEC_26_45 applies to DVB-S2X. */
  FEC_26_45 = 28,
  // @aidl-doc
  /** FEC_28_45 applies to DVB-S2X. */
  FEC_28_45 = 29,
  // @aidl-doc
  /** FEC_32_45 applies to DVB-S2X. */
  FEC_32_45 = 30,
  // @aidl-doc
  /** FEC_77_90 applies to DVB-S2X. */
  FEC_77_90 = 31,
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
[[nodiscard]] static inline std::string toString(DvbSInnerFec val) {
  switch(val) {
  case DvbSInnerFec::UNDEFINED:
    return "UNDEFINED";
  case DvbSInnerFec::AUTO:
    return "AUTO";
  case DvbSInnerFec::FEC_1_2:
    return "FEC_1_2";
  case DvbSInnerFec::FEC_1_3:
    return "FEC_1_3";
  case DvbSInnerFec::FEC_1_4:
    return "FEC_1_4";
  case DvbSInnerFec::FEC_1_5:
    return "FEC_1_5";
  case DvbSInnerFec::FEC_2_3:
    return "FEC_2_3";
  case DvbSInnerFec::FEC_2_5:
    return "FEC_2_5";
  case DvbSInnerFec::FEC_2_9:
    return "FEC_2_9";
  case DvbSInnerFec::FEC_3_4:
    return "FEC_3_4";
  case DvbSInnerFec::FEC_3_5:
    return "FEC_3_5";
  case DvbSInnerFec::FEC_4_5:
    return "FEC_4_5";
  case DvbSInnerFec::FEC_4_15:
    return "FEC_4_15";
  case DvbSInnerFec::FEC_5_6:
    return "FEC_5_6";
  case DvbSInnerFec::FEC_7_8:
    return "FEC_7_8";
  case DvbSInnerFec::FEC_7_9:
    return "FEC_7_9";
  case DvbSInnerFec::FEC_7_10:
    return "FEC_7_10";
  case DvbSInnerFec::FEC_7_15:
    return "FEC_7_15";
  case DvbSInnerFec::FEC_8_9:
    return "FEC_8_9";
  case DvbSInnerFec::FEC_8_15:
    return "FEC_8_15";
  case DvbSInnerFec::FEC_9_10:
    return "FEC_9_10";
  case DvbSInnerFec::FEC_11_15:
    return "FEC_11_15";
  case DvbSInnerFec::FEC_11_20:
    return "FEC_11_20";
  case DvbSInnerFec::FEC_11_45:
    return "FEC_11_45";
  case DvbSInnerFec::FEC_13_18:
    return "FEC_13_18";
  case DvbSInnerFec::FEC_14_45:
    return "FEC_14_45";
  case DvbSInnerFec::FEC_23_36:
    return "FEC_23_36";
  case DvbSInnerFec::FEC_25_36:
    return "FEC_25_36";
  case DvbSInnerFec::FEC_26_45:
    return "FEC_26_45";
  case DvbSInnerFec::FEC_28_45:
    return "FEC_28_45";
  case DvbSInnerFec::FEC_32_45:
    return "FEC_32_45";
  case DvbSInnerFec::FEC_77_90:
    return "FEC_77_90";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::DvbSInnerFec, 32> enum_values<::com::rdk::hal::broadcast::frontend::DvbSInnerFec> = {
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::AUTO,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_1_2,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_1_3,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_1_4,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_1_5,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_2_3,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_2_5,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_2_9,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_3_4,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_3_5,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_4_5,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_4_15,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_5_6,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_7_8,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_7_9,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_7_10,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_7_15,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_8_9,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_8_15,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_9_10,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_11_15,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_11_20,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_11_45,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_13_18,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_14_45,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_23_36,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_25_36,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_26_45,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_28_45,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_32_45,
  ::com::rdk::hal::broadcast::frontend::DvbSInnerFec::FEC_77_90,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

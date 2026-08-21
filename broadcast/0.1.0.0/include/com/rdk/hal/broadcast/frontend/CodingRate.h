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
enum class CodingRate : int32_t {
  UNDEFINED = 0,
  AUTO = 1,
  CR_1_2 = 2,
  CR_2_3 = 3,
  CR_3_4 = 4,
  CR_5_6 = 5,
  CR_7_8 = 6,
  CR_8_9 = 7,
  CR_3_5 = 8,
  CR_4_5 = 9,
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
[[nodiscard]] static inline std::string toString(CodingRate val) {
  switch(val) {
  case CodingRate::UNDEFINED:
    return "UNDEFINED";
  case CodingRate::AUTO:
    return "AUTO";
  case CodingRate::CR_1_2:
    return "CR_1_2";
  case CodingRate::CR_2_3:
    return "CR_2_3";
  case CodingRate::CR_3_4:
    return "CR_3_4";
  case CodingRate::CR_5_6:
    return "CR_5_6";
  case CodingRate::CR_7_8:
    return "CR_7_8";
  case CodingRate::CR_8_9:
    return "CR_8_9";
  case CodingRate::CR_3_5:
    return "CR_3_5";
  case CodingRate::CR_4_5:
    return "CR_4_5";
  case CodingRate::CR_9_10:
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::CodingRate, 11> enum_values<::com::rdk::hal::broadcast::frontend::CodingRate> = {
  ::com::rdk::hal::broadcast::frontend::CodingRate::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::CodingRate::AUTO,
  ::com::rdk::hal::broadcast::frontend::CodingRate::CR_1_2,
  ::com::rdk::hal::broadcast::frontend::CodingRate::CR_2_3,
  ::com::rdk::hal::broadcast::frontend::CodingRate::CR_3_4,
  ::com::rdk::hal::broadcast::frontend::CodingRate::CR_5_6,
  ::com::rdk::hal::broadcast::frontend::CodingRate::CR_7_8,
  ::com::rdk::hal::broadcast::frontend::CodingRate::CR_8_9,
  ::com::rdk::hal::broadcast::frontend::CodingRate::CR_3_5,
  ::com::rdk::hal::broadcast::frontend::CodingRate::CR_4_5,
  ::com::rdk::hal::broadcast::frontend::CodingRate::CR_9_10,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

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
enum class Bandwidth : int32_t {
  UNDEFINED = 0,
  AUTO = 1,
  MHZ_1_712 = 2,
  MHZ_5 = 3,
  MHZ_6 = 4,
  MHZ_7 = 5,
  MHZ_8 = 6,
  MHZ_10 = 7,
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
[[nodiscard]] static inline std::string toString(Bandwidth val) {
  switch(val) {
  case Bandwidth::UNDEFINED:
    return "UNDEFINED";
  case Bandwidth::AUTO:
    return "AUTO";
  case Bandwidth::MHZ_1_712:
    return "MHZ_1_712";
  case Bandwidth::MHZ_5:
    return "MHZ_5";
  case Bandwidth::MHZ_6:
    return "MHZ_6";
  case Bandwidth::MHZ_7:
    return "MHZ_7";
  case Bandwidth::MHZ_8:
    return "MHZ_8";
  case Bandwidth::MHZ_10:
    return "MHZ_10";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::Bandwidth, 8> enum_values<::com::rdk::hal::broadcast::frontend::Bandwidth> = {
  ::com::rdk::hal::broadcast::frontend::Bandwidth::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::Bandwidth::AUTO,
  ::com::rdk::hal::broadcast::frontend::Bandwidth::MHZ_1_712,
  ::com::rdk::hal::broadcast::frontend::Bandwidth::MHZ_5,
  ::com::rdk::hal::broadcast::frontend::Bandwidth::MHZ_6,
  ::com::rdk::hal::broadcast::frontend::Bandwidth::MHZ_7,
  ::com::rdk::hal::broadcast::frontend::Bandwidth::MHZ_8,
  ::com::rdk::hal::broadcast::frontend::Bandwidth::MHZ_10,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

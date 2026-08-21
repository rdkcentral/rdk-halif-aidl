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
enum class DvbCAnnex : int32_t {
  UNDEFINED = 0,
  AUTO = 1,
  A = 2,
  B = 3,
  C = 4,
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
[[nodiscard]] static inline std::string toString(DvbCAnnex val) {
  switch(val) {
  case DvbCAnnex::UNDEFINED:
    return "UNDEFINED";
  case DvbCAnnex::AUTO:
    return "AUTO";
  case DvbCAnnex::A:
    return "A";
  case DvbCAnnex::B:
    return "B";
  case DvbCAnnex::C:
    return "C";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::DvbCAnnex, 5> enum_values<::com::rdk::hal::broadcast::frontend::DvbCAnnex> = {
  ::com::rdk::hal::broadcast::frontend::DvbCAnnex::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::DvbCAnnex::AUTO,
  ::com::rdk::hal::broadcast::frontend::DvbCAnnex::A,
  ::com::rdk::hal::broadcast::frontend::DvbCAnnex::B,
  ::com::rdk::hal::broadcast::frontend::DvbCAnnex::C,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

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
enum class DvbSStandard : int32_t {
  UNDEFINED = 0,
  AUTO = 1,
  S = 2,
  S2 = 3,
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

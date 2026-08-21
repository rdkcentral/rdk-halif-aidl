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
enum class GuardInterval : int32_t {
  UNDEFINED = 0,
  AUTO = 1,
  GI_1_4 = 2,
  GI_1_8 = 3,
  GI_1_16 = 4,
  GI_1_32 = 5,
  GI_1_128 = 6,
  GI_19_128 = 7,
  GI_19_256 = 8,
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
[[nodiscard]] static inline std::string toString(GuardInterval val) {
  switch(val) {
  case GuardInterval::UNDEFINED:
    return "UNDEFINED";
  case GuardInterval::AUTO:
    return "AUTO";
  case GuardInterval::GI_1_4:
    return "GI_1_4";
  case GuardInterval::GI_1_8:
    return "GI_1_8";
  case GuardInterval::GI_1_16:
    return "GI_1_16";
  case GuardInterval::GI_1_32:
    return "GI_1_32";
  case GuardInterval::GI_1_128:
    return "GI_1_128";
  case GuardInterval::GI_19_128:
    return "GI_19_128";
  case GuardInterval::GI_19_256:
    return "GI_19_256";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::GuardInterval, 9> enum_values<::com::rdk::hal::broadcast::frontend::GuardInterval> = {
  ::com::rdk::hal::broadcast::frontend::GuardInterval::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::GuardInterval::AUTO,
  ::com::rdk::hal::broadcast::frontend::GuardInterval::GI_1_4,
  ::com::rdk::hal::broadcast::frontend::GuardInterval::GI_1_8,
  ::com::rdk::hal::broadcast::frontend::GuardInterval::GI_1_16,
  ::com::rdk::hal::broadcast::frontend::GuardInterval::GI_1_32,
  ::com::rdk::hal::broadcast::frontend::GuardInterval::GI_1_128,
  ::com::rdk::hal::broadcast::frontend::GuardInterval::GI_19_128,
  ::com::rdk::hal::broadcast::frontend::GuardInterval::GI_19_256,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

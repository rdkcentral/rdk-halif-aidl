#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
enum class OperationalMode : int8_t {
  MOTION = 0,
  NO_MOTION = 1,
};
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
[[nodiscard]] static inline std::string toString(OperationalMode val) {
  switch(val) {
  case OperationalMode::MOTION:
    return "MOTION";
  case OperationalMode::NO_MOTION:
    return "NO_MOTION";
  default:
    return std::to_string(static_cast<int8_t>(val));
  }
}
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::sensor::motion::OperationalMode, 2> enum_values<::com::rdk::hal::sensor::motion::OperationalMode> = {
  ::com::rdk::hal::sensor::motion::OperationalMode::MOTION,
  ::com::rdk::hal::sensor::motion::OperationalMode::NO_MOTION,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

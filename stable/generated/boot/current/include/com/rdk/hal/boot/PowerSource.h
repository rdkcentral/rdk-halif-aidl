#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace boot {
enum class PowerSource : int32_t {
  UNKNOWN = 0,
  PSU = 1,
  USB = 2,
  POE = 3,
};
}  // namespace boot
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace boot {
[[nodiscard]] static inline std::string toString(PowerSource val) {
  switch(val) {
  case PowerSource::UNKNOWN:
    return "UNKNOWN";
  case PowerSource::PSU:
    return "PSU";
  case PowerSource::USB:
    return "USB";
  case PowerSource::POE:
    return "POE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace boot
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::boot::PowerSource, 4> enum_values<::com::rdk::hal::boot::PowerSource> = {
  ::com::rdk::hal::boot::PowerSource::UNKNOWN,
  ::com::rdk::hal::boot::PowerSource::PSU,
  ::com::rdk::hal::boot::PowerSource::USB,
  ::com::rdk::hal::boot::PowerSource::POE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
enum class Property : int32_t {
  LATENCY_MS = 0,
  DEBUG_TAP_ENABLED = 1,
  ACTIVE_AQ_PROFILE = 2,
  MIXING_MODE = 3,
  MUTE = 4,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(Property val) {
  switch(val) {
  case Property::LATENCY_MS:
    return "LATENCY_MS";
  case Property::DEBUG_TAP_ENABLED:
    return "DEBUG_TAP_ENABLED";
  case Property::ACTIVE_AQ_PROFILE:
    return "ACTIVE_AQ_PROFILE";
  case Property::MIXING_MODE:
    return "MIXING_MODE";
  case Property::MUTE:
    return "MUTE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiomixer::Property, 5> enum_values<::com::rdk::hal::audiomixer::Property> = {
  ::com::rdk::hal::audiomixer::Property::LATENCY_MS,
  ::com::rdk::hal::audiomixer::Property::DEBUG_TAP_ENABLED,
  ::com::rdk::hal::audiomixer::Property::ACTIVE_AQ_PROFILE,
  ::com::rdk::hal::audiomixer::Property::MIXING_MODE,
  ::com::rdk::hal::audiomixer::Property::MUTE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

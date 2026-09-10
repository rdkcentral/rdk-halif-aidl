#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
enum class ClockMode : int32_t {
  AUTO = 0,
  PCR = 1,
  AUDIO_MASTER = 2,
  VIDEO_MASTER = 3,
};
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace avclock {
[[nodiscard]] static inline std::string toString(ClockMode val) {
  switch(val) {
  case ClockMode::AUTO:
    return "AUTO";
  case ClockMode::PCR:
    return "PCR";
  case ClockMode::AUDIO_MASTER:
    return "AUDIO_MASTER";
  case ClockMode::VIDEO_MASTER:
    return "VIDEO_MASTER";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::avclock::ClockMode, 4> enum_values<::com::rdk::hal::avclock::ClockMode> = {
  ::com::rdk::hal::avclock::ClockMode::AUTO,
  ::com::rdk::hal::avclock::ClockMode::PCR,
  ::com::rdk::hal::avclock::ClockMode::AUDIO_MASTER,
  ::com::rdk::hal::avclock::ClockMode::VIDEO_MASTER,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
enum class SourceType : int32_t {
  NONE = 0,
  VIDEO_SINK = 1,
  HDMI = 2,
  COMPOSITE = 3,
};
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
[[nodiscard]] static inline std::string toString(SourceType val) {
  switch(val) {
  case SourceType::NONE:
    return "NONE";
  case SourceType::VIDEO_SINK:
    return "VIDEO_SINK";
  case SourceType::HDMI:
    return "HDMI";
  case SourceType::COMPOSITE:
    return "COMPOSITE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::planecontrol::SourceType, 4> enum_values<::com::rdk::hal::planecontrol::SourceType> = {
  ::com::rdk::hal::planecontrol::SourceType::NONE,
  ::com::rdk::hal::planecontrol::SourceType::VIDEO_SINK,
  ::com::rdk::hal::planecontrol::SourceType::HDMI,
  ::com::rdk::hal::planecontrol::SourceType::COMPOSITE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

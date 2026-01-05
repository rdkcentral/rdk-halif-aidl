#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
enum class HDMIVersion : int32_t {
  HDMI_1_3 = 0,
  HDMI_1_4 = 1,
  HDMI_2_0 = 2,
  HDMI_2_1 = 3,
};
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
[[nodiscard]] static inline std::string toString(HDMIVersion val) {
  switch(val) {
  case HDMIVersion::HDMI_1_3:
    return "HDMI_1_3";
  case HDMIVersion::HDMI_1_4:
    return "HDMI_1_4";
  case HDMIVersion::HDMI_2_0:
    return "HDMI_2_0";
  case HDMIVersion::HDMI_2_1:
    return "HDMI_2_1";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::hdmiinput::HDMIVersion, 4> enum_values<::com::rdk::hal::hdmiinput::HDMIVersion> = {
  ::com::rdk::hal::hdmiinput::HDMIVersion::HDMI_1_3,
  ::com::rdk::hal::hdmiinput::HDMIVersion::HDMI_1_4,
  ::com::rdk::hal::hdmiinput::HDMIVersion::HDMI_2_0,
  ::com::rdk::hal::hdmiinput::HDMIVersion::HDMI_2_1,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

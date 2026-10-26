#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
// @aidl-doc
/**
 *  @brief     HDMI standard version.
 *
 *  Represents the major HDMI specification versions supported by a given output.
 *  This helps in feature negotiation, such as available bandwidth and protocol support.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
enum class HDMIVersion : int32_t {
  // @aidl-doc
  /** HDMI version 1.3 or 1.3a. */
  HDMI_1_3 = 0,
  // @aidl-doc
  /** HDMI version 1.4, 1.4a, or 1.4b. */
  HDMI_1_4 = 1,
  // @aidl-doc
  /** HDMI version 2.0, 2.0a, or 2.0b. */
  HDMI_2_0 = 2,
  // @aidl-doc
  /** HDMI version 2.1. */
  HDMI_2_1 = 3,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
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
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::hdmioutput::HDMIVersion, 4> enum_values<::com::rdk::hal::hdmioutput::HDMIVersion> = {
  ::com::rdk::hal::hdmioutput::HDMIVersion::HDMI_1_3,
  ::com::rdk::hal::hdmioutput::HDMIVersion::HDMI_1_4,
  ::com::rdk::hal::hdmioutput::HDMIVersion::HDMI_2_0,
  ::com::rdk::hal::hdmioutput::HDMIVersion::HDMI_2_1,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

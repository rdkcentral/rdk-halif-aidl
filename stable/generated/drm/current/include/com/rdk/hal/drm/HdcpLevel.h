#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
enum class HdcpLevel : int32_t {
  HDCP_UNKNOWN = 0,
  HDCP_NONE = 1,
  HDCP_V1 = 2,
  HDCP_V2 = 3,
  HDCP_V2_1 = 4,
  HDCP_V2_2 = 5,
  HDCP_NO_OUTPUT = 6,
  HDCP_V2_3 = 7,
};
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace drm {
[[nodiscard]] static inline std::string toString(HdcpLevel val) {
  switch(val) {
  case HdcpLevel::HDCP_UNKNOWN:
    return "HDCP_UNKNOWN";
  case HdcpLevel::HDCP_NONE:
    return "HDCP_NONE";
  case HdcpLevel::HDCP_V1:
    return "HDCP_V1";
  case HdcpLevel::HDCP_V2:
    return "HDCP_V2";
  case HdcpLevel::HDCP_V2_1:
    return "HDCP_V2_1";
  case HdcpLevel::HDCP_V2_2:
    return "HDCP_V2_2";
  case HdcpLevel::HDCP_NO_OUTPUT:
    return "HDCP_NO_OUTPUT";
  case HdcpLevel::HDCP_V2_3:
    return "HDCP_V2_3";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::drm::HdcpLevel, 8> enum_values<::com::rdk::hal::drm::HdcpLevel> = {
  ::com::rdk::hal::drm::HdcpLevel::HDCP_UNKNOWN,
  ::com::rdk::hal::drm::HdcpLevel::HDCP_NONE,
  ::com::rdk::hal::drm::HdcpLevel::HDCP_V1,
  ::com::rdk::hal::drm::HdcpLevel::HDCP_V2,
  ::com::rdk::hal::drm::HdcpLevel::HDCP_V2_1,
  ::com::rdk::hal::drm::HdcpLevel::HDCP_V2_2,
  ::com::rdk::hal::drm::HdcpLevel::HDCP_NO_OUTPUT,
  ::com::rdk::hal::drm::HdcpLevel::HDCP_V2_3,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

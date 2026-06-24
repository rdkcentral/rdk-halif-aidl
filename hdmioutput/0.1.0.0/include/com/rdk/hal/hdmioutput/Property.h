#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
enum class Property : int32_t {
  RESOURCE_ID = 0,
  VIC = 1,
  CONTENT_TYPE = 2,
  AFD = 3,
  HDR_OUTPUT_MODE = 4,
  SCAN_INFORMATION = 5,
  METRIC_xxx = 1000,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
[[nodiscard]] static inline std::string toString(Property val) {
  switch(val) {
  case Property::RESOURCE_ID:
    return "RESOURCE_ID";
  case Property::VIC:
    return "VIC";
  case Property::CONTENT_TYPE:
    return "CONTENT_TYPE";
  case Property::AFD:
    return "AFD";
  case Property::HDR_OUTPUT_MODE:
    return "HDR_OUTPUT_MODE";
  case Property::SCAN_INFORMATION:
    return "SCAN_INFORMATION";
  case Property::METRIC_xxx:
    return "METRIC_xxx";
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
constexpr inline std::array<::com::rdk::hal::hdmioutput::Property, 7> enum_values<::com::rdk::hal::hdmioutput::Property> = {
  ::com::rdk::hal::hdmioutput::Property::RESOURCE_ID,
  ::com::rdk::hal::hdmioutput::Property::VIC,
  ::com::rdk::hal::hdmioutput::Property::CONTENT_TYPE,
  ::com::rdk::hal::hdmioutput::Property::AFD,
  ::com::rdk::hal::hdmioutput::Property::HDR_OUTPUT_MODE,
  ::com::rdk::hal::hdmioutput::Property::SCAN_INFORMATION,
  ::com::rdk::hal::hdmioutput::Property::METRIC_xxx,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

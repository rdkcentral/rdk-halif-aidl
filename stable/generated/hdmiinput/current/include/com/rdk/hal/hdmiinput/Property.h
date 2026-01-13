#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
enum class Property : int32_t {
  RESOURCE_ID = 0,
  METRIC_PACKET_ERRORS = 1000,
};
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
[[nodiscard]] static inline std::string toString(Property val) {
  switch(val) {
  case Property::RESOURCE_ID:
    return "RESOURCE_ID";
  case Property::METRIC_PACKET_ERRORS:
    return "METRIC_PACKET_ERRORS";
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
constexpr inline std::array<::com::rdk::hal::hdmiinput::Property, 2> enum_values<::com::rdk::hal::hdmiinput::Property> = {
  ::com::rdk::hal::hdmiinput::Property::RESOURCE_ID,
  ::com::rdk::hal::hdmiinput::Property::METRIC_PACKET_ERRORS,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

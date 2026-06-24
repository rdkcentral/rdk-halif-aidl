#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
enum class Property : int32_t {
  RESOURCE_ID = 0,
  X = 1,
  Y = 2,
  WIDTH = 3,
  HEIGHT = 4,
  ALPHA = 5,
  ZORDER = 6,
  VISIBLE = 7,
  OVERSCAN = 8,
  ASPECT_RATIO = 9,
};
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
[[nodiscard]] static inline std::string toString(Property val) {
  switch(val) {
  case Property::RESOURCE_ID:
    return "RESOURCE_ID";
  case Property::X:
    return "X";
  case Property::Y:
    return "Y";
  case Property::WIDTH:
    return "WIDTH";
  case Property::HEIGHT:
    return "HEIGHT";
  case Property::ALPHA:
    return "ALPHA";
  case Property::ZORDER:
    return "ZORDER";
  case Property::VISIBLE:
    return "VISIBLE";
  case Property::OVERSCAN:
    return "OVERSCAN";
  case Property::ASPECT_RATIO:
    return "ASPECT_RATIO";
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
constexpr inline std::array<::com::rdk::hal::planecontrol::Property, 10> enum_values<::com::rdk::hal::planecontrol::Property> = {
  ::com::rdk::hal::planecontrol::Property::RESOURCE_ID,
  ::com::rdk::hal::planecontrol::Property::X,
  ::com::rdk::hal::planecontrol::Property::Y,
  ::com::rdk::hal::planecontrol::Property::WIDTH,
  ::com::rdk::hal::planecontrol::Property::HEIGHT,
  ::com::rdk::hal::planecontrol::Property::ALPHA,
  ::com::rdk::hal::planecontrol::Property::ZORDER,
  ::com::rdk::hal::planecontrol::Property::VISIBLE,
  ::com::rdk::hal::planecontrol::Property::OVERSCAN,
  ::com::rdk::hal::planecontrol::Property::ASPECT_RATIO,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
enum class ExtendedColorimetry : int32_t {
  XV_YCC_601 = 0,
  XV_YCC_709 = 1,
  S_YCC_601 = 2,
  OP_YCC_601 = 3,
  OP_RGB = 4,
  BT2020_C_YCC = 5,
  BT2020_RGB_YCC = 6,
  ADDITIONAL_COLORIMETRY_EXTENSION = 7,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
[[nodiscard]] static inline std::string toString(ExtendedColorimetry val) {
  switch(val) {
  case ExtendedColorimetry::XV_YCC_601:
    return "XV_YCC_601";
  case ExtendedColorimetry::XV_YCC_709:
    return "XV_YCC_709";
  case ExtendedColorimetry::S_YCC_601:
    return "S_YCC_601";
  case ExtendedColorimetry::OP_YCC_601:
    return "OP_YCC_601";
  case ExtendedColorimetry::OP_RGB:
    return "OP_RGB";
  case ExtendedColorimetry::BT2020_C_YCC:
    return "BT2020_C_YCC";
  case ExtendedColorimetry::BT2020_RGB_YCC:
    return "BT2020_RGB_YCC";
  case ExtendedColorimetry::ADDITIONAL_COLORIMETRY_EXTENSION:
    return "ADDITIONAL_COLORIMETRY_EXTENSION";
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
constexpr inline std::array<::com::rdk::hal::hdmioutput::ExtendedColorimetry, 8> enum_values<::com::rdk::hal::hdmioutput::ExtendedColorimetry> = {
  ::com::rdk::hal::hdmioutput::ExtendedColorimetry::XV_YCC_601,
  ::com::rdk::hal::hdmioutput::ExtendedColorimetry::XV_YCC_709,
  ::com::rdk::hal::hdmioutput::ExtendedColorimetry::S_YCC_601,
  ::com::rdk::hal::hdmioutput::ExtendedColorimetry::OP_YCC_601,
  ::com::rdk::hal::hdmioutput::ExtendedColorimetry::OP_RGB,
  ::com::rdk::hal::hdmioutput::ExtendedColorimetry::BT2020_C_YCC,
  ::com::rdk::hal::hdmioutput::ExtendedColorimetry::BT2020_RGB_YCC,
  ::com::rdk::hal::hdmioutput::ExtendedColorimetry::ADDITIONAL_COLORIMETRY_EXTENSION,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

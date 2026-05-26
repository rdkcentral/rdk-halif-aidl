#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
enum class AdditionalColorimetryExtension : int32_t {
  DCI_P3_RGB_D65 = 0,
  DCI_P3_RGB_THEATER = 1,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
[[nodiscard]] static inline std::string toString(AdditionalColorimetryExtension val) {
  switch(val) {
  case AdditionalColorimetryExtension::DCI_P3_RGB_D65:
    return "DCI_P3_RGB_D65";
  case AdditionalColorimetryExtension::DCI_P3_RGB_THEATER:
    return "DCI_P3_RGB_THEATER";
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
constexpr inline std::array<::com::rdk::hal::hdmioutput::AdditionalColorimetryExtension, 2> enum_values<::com::rdk::hal::hdmioutput::AdditionalColorimetryExtension> = {
  ::com::rdk::hal::hdmioutput::AdditionalColorimetryExtension::DCI_P3_RGB_D65,
  ::com::rdk::hal::hdmioutput::AdditionalColorimetryExtension::DCI_P3_RGB_THEATER,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
enum class ScanInformation : int32_t {
  NO_DATA = 0,
  OVERSCAN = 1,
  UNDERSCAN = 2,
  RESERVED = 3,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
[[nodiscard]] static inline std::string toString(ScanInformation val) {
  switch(val) {
  case ScanInformation::NO_DATA:
    return "NO_DATA";
  case ScanInformation::OVERSCAN:
    return "OVERSCAN";
  case ScanInformation::UNDERSCAN:
    return "UNDERSCAN";
  case ScanInformation::RESERVED:
    return "RESERVED";
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
constexpr inline std::array<::com::rdk::hal::hdmioutput::ScanInformation, 4> enum_values<::com::rdk::hal::hdmioutput::ScanInformation> = {
  ::com::rdk::hal::hdmioutput::ScanInformation::NO_DATA,
  ::com::rdk::hal::hdmioutput::ScanInformation::OVERSCAN,
  ::com::rdk::hal::hdmioutput::ScanInformation::UNDERSCAN,
  ::com::rdk::hal::hdmioutput::ScanInformation::RESERVED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

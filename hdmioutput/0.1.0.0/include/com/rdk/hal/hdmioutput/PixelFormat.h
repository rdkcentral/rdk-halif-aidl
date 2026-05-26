#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
enum class PixelFormat : int32_t {
  RGB_444 = 0,
  YCBCR_422 = 1,
  YCBCR_444 = 2,
  YCBCR_420 = 3,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
[[nodiscard]] static inline std::string toString(PixelFormat val) {
  switch(val) {
  case PixelFormat::RGB_444:
    return "RGB_444";
  case PixelFormat::YCBCR_422:
    return "YCBCR_422";
  case PixelFormat::YCBCR_444:
    return "YCBCR_444";
  case PixelFormat::YCBCR_420:
    return "YCBCR_420";
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
constexpr inline std::array<::com::rdk::hal::hdmioutput::PixelFormat, 4> enum_values<::com::rdk::hal::hdmioutput::PixelFormat> = {
  ::com::rdk::hal::hdmioutput::PixelFormat::RGB_444,
  ::com::rdk::hal::hdmioutput::PixelFormat::YCBCR_422,
  ::com::rdk::hal::hdmioutput::PixelFormat::YCBCR_444,
  ::com::rdk::hal::hdmioutput::PixelFormat::YCBCR_420,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
enum class PixelFormat : int32_t {
  UNKNOWN = 0,
  NV12 = 1,
  I420 = 2,
  P010 = 3,
};
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videosink {
[[nodiscard]] static inline std::string toString(PixelFormat val) {
  switch(val) {
  case PixelFormat::UNKNOWN:
    return "UNKNOWN";
  case PixelFormat::NV12:
    return "NV12";
  case PixelFormat::I420:
    return "I420";
  case PixelFormat::P010:
    return "P010";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::videosink::PixelFormat, 4> enum_values<::com::rdk::hal::videosink::PixelFormat> = {
  ::com::rdk::hal::videosink::PixelFormat::UNKNOWN,
  ::com::rdk::hal::videosink::PixelFormat::NV12,
  ::com::rdk::hal::videosink::PixelFormat::I420,
  ::com::rdk::hal::videosink::PixelFormat::P010,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

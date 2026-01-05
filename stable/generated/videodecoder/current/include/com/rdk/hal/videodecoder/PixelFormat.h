#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
enum class PixelFormat : int32_t {
  YCBCR422 = 1,
  YCBCR444 = 2,
  YCBCR420 = 3,
  RGB = 4,
  NATIVE = 100,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(PixelFormat val) {
  switch(val) {
  case PixelFormat::YCBCR422:
    return "YCBCR422";
  case PixelFormat::YCBCR444:
    return "YCBCR444";
  case PixelFormat::YCBCR420:
    return "YCBCR420";
  case PixelFormat::RGB:
    return "RGB";
  case PixelFormat::NATIVE:
    return "NATIVE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::videodecoder::PixelFormat, 5> enum_values<::com::rdk::hal::videodecoder::PixelFormat> = {
  ::com::rdk::hal::videodecoder::PixelFormat::YCBCR422,
  ::com::rdk::hal::videodecoder::PixelFormat::YCBCR444,
  ::com::rdk::hal::videodecoder::PixelFormat::YCBCR420,
  ::com::rdk::hal::videodecoder::PixelFormat::RGB,
  ::com::rdk::hal::videodecoder::PixelFormat::NATIVE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
enum class ColorRange : int32_t {
  UNKNOWN = -1,
  LIMITED = 0,
  FULL = 1,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(ColorRange val) {
  switch(val) {
  case ColorRange::UNKNOWN:
    return "UNKNOWN";
  case ColorRange::LIMITED:
    return "LIMITED";
  case ColorRange::FULL:
    return "FULL";
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
constexpr inline std::array<::com::rdk::hal::videodecoder::ColorRange, 3> enum_values<::com::rdk::hal::videodecoder::ColorRange> = {
  ::com::rdk::hal::videodecoder::ColorRange::UNKNOWN,
  ::com::rdk::hal::videodecoder::ColorRange::LIMITED,
  ::com::rdk::hal::videodecoder::ColorRange::FULL,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

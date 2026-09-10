#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
enum class OperationalMode : int32_t {
  TUNNELLED = 1,
  NON_TUNNELLED = 2,
  GRAPHICS_TEXTURE = 4,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(OperationalMode val) {
  switch(val) {
  case OperationalMode::TUNNELLED:
    return "TUNNELLED";
  case OperationalMode::NON_TUNNELLED:
    return "NON_TUNNELLED";
  case OperationalMode::GRAPHICS_TEXTURE:
    return "GRAPHICS_TEXTURE";
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
constexpr inline std::array<::com::rdk::hal::videodecoder::OperationalMode, 3> enum_values<::com::rdk::hal::videodecoder::OperationalMode> = {
  ::com::rdk::hal::videodecoder::OperationalMode::TUNNELLED,
  ::com::rdk::hal::videodecoder::OperationalMode::NON_TUNNELLED,
  ::com::rdk::hal::videodecoder::OperationalMode::GRAPHICS_TEXTURE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

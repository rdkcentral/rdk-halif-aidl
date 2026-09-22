#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
enum class ScanType : int32_t {
  PROGRESSIVE_FRAME = 0,
  INTERLACED_FRAME = 1,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(ScanType val) {
  switch(val) {
  case ScanType::PROGRESSIVE_FRAME:
    return "PROGRESSIVE_FRAME";
  case ScanType::INTERLACED_FRAME:
    return "INTERLACED_FRAME";
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
constexpr inline std::array<::com::rdk::hal::videodecoder::ScanType, 2> enum_values<::com::rdk::hal::videodecoder::ScanType> = {
  ::com::rdk::hal::videodecoder::ScanType::PROGRESSIVE_FRAME,
  ::com::rdk::hal::videodecoder::ScanType::INTERLACED_FRAME,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

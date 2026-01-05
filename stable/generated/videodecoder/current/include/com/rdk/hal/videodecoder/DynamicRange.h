#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
enum class DynamicRange : int32_t {
  UNKNOWN = 0,
  SDR = 1,
  HLG = 2,
  HDR10 = 3,
  HDR10PLUS = 4,
  DOLBY_VISION = 5,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(DynamicRange val) {
  switch(val) {
  case DynamicRange::UNKNOWN:
    return "UNKNOWN";
  case DynamicRange::SDR:
    return "SDR";
  case DynamicRange::HLG:
    return "HLG";
  case DynamicRange::HDR10:
    return "HDR10";
  case DynamicRange::HDR10PLUS:
    return "HDR10PLUS";
  case DynamicRange::DOLBY_VISION:
    return "DOLBY_VISION";
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
constexpr inline std::array<::com::rdk::hal::videodecoder::DynamicRange, 6> enum_values<::com::rdk::hal::videodecoder::DynamicRange> = {
  ::com::rdk::hal::videodecoder::DynamicRange::UNKNOWN,
  ::com::rdk::hal::videodecoder::DynamicRange::SDR,
  ::com::rdk::hal::videodecoder::DynamicRange::HLG,
  ::com::rdk::hal::videodecoder::DynamicRange::HDR10,
  ::com::rdk::hal::videodecoder::DynamicRange::HDR10PLUS,
  ::com::rdk::hal::videodecoder::DynamicRange::DOLBY_VISION,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

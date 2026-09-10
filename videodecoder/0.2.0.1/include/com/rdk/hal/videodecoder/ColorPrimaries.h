#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
enum class ColorPrimaries : int32_t {
  UNKNOWN = -1,
  BT709 = 1,
  UNSPECIFIED = 2,
  BT470M = 4,
  BT470BG = 5,
  BT601_525 = 6,
  SMPTE240M = 7,
  FILM = 8,
  BT2020 = 9,
  SMPTE428 = 10,
  DCI_P3_D60 = 11,
  DISPLAY_P3 = 12,
  EBU3213 = 22,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(ColorPrimaries val) {
  switch(val) {
  case ColorPrimaries::UNKNOWN:
    return "UNKNOWN";
  case ColorPrimaries::BT709:
    return "BT709";
  case ColorPrimaries::UNSPECIFIED:
    return "UNSPECIFIED";
  case ColorPrimaries::BT470M:
    return "BT470M";
  case ColorPrimaries::BT470BG:
    return "BT470BG";
  case ColorPrimaries::BT601_525:
    return "BT601_525";
  case ColorPrimaries::SMPTE240M:
    return "SMPTE240M";
  case ColorPrimaries::FILM:
    return "FILM";
  case ColorPrimaries::BT2020:
    return "BT2020";
  case ColorPrimaries::SMPTE428:
    return "SMPTE428";
  case ColorPrimaries::DCI_P3_D60:
    return "DCI_P3_D60";
  case ColorPrimaries::DISPLAY_P3:
    return "DISPLAY_P3";
  case ColorPrimaries::EBU3213:
    return "EBU3213";
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
constexpr inline std::array<::com::rdk::hal::videodecoder::ColorPrimaries, 13> enum_values<::com::rdk::hal::videodecoder::ColorPrimaries> = {
  ::com::rdk::hal::videodecoder::ColorPrimaries::UNKNOWN,
  ::com::rdk::hal::videodecoder::ColorPrimaries::BT709,
  ::com::rdk::hal::videodecoder::ColorPrimaries::UNSPECIFIED,
  ::com::rdk::hal::videodecoder::ColorPrimaries::BT470M,
  ::com::rdk::hal::videodecoder::ColorPrimaries::BT470BG,
  ::com::rdk::hal::videodecoder::ColorPrimaries::BT601_525,
  ::com::rdk::hal::videodecoder::ColorPrimaries::SMPTE240M,
  ::com::rdk::hal::videodecoder::ColorPrimaries::FILM,
  ::com::rdk::hal::videodecoder::ColorPrimaries::BT2020,
  ::com::rdk::hal::videodecoder::ColorPrimaries::SMPTE428,
  ::com::rdk::hal::videodecoder::ColorPrimaries::DCI_P3_D60,
  ::com::rdk::hal::videodecoder::ColorPrimaries::DISPLAY_P3,
  ::com::rdk::hal::videodecoder::ColorPrimaries::EBU3213,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

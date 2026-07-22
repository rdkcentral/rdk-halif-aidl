#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
enum class ColorMatrix : int32_t {
  UNKNOWN = -1,
  IDENTITY = 0,
  BT709 = 1,
  UNSPECIFIED = 2,
  BT601_625 = 5,
  BT601_525 = 6,
  SMPTE240M = 7,
  BT2020_NCL = 9,
  BT2020_CL = 10,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(ColorMatrix val) {
  switch(val) {
  case ColorMatrix::UNKNOWN:
    return "UNKNOWN";
  case ColorMatrix::IDENTITY:
    return "IDENTITY";
  case ColorMatrix::BT709:
    return "BT709";
  case ColorMatrix::UNSPECIFIED:
    return "UNSPECIFIED";
  case ColorMatrix::BT601_625:
    return "BT601_625";
  case ColorMatrix::BT601_525:
    return "BT601_525";
  case ColorMatrix::SMPTE240M:
    return "SMPTE240M";
  case ColorMatrix::BT2020_NCL:
    return "BT2020_NCL";
  case ColorMatrix::BT2020_CL:
    return "BT2020_CL";
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
constexpr inline std::array<::com::rdk::hal::videodecoder::ColorMatrix, 9> enum_values<::com::rdk::hal::videodecoder::ColorMatrix> = {
  ::com::rdk::hal::videodecoder::ColorMatrix::UNKNOWN,
  ::com::rdk::hal::videodecoder::ColorMatrix::IDENTITY,
  ::com::rdk::hal::videodecoder::ColorMatrix::BT709,
  ::com::rdk::hal::videodecoder::ColorMatrix::UNSPECIFIED,
  ::com::rdk::hal::videodecoder::ColorMatrix::BT601_625,
  ::com::rdk::hal::videodecoder::ColorMatrix::BT601_525,
  ::com::rdk::hal::videodecoder::ColorMatrix::SMPTE240M,
  ::com::rdk::hal::videodecoder::ColorMatrix::BT2020_NCL,
  ::com::rdk::hal::videodecoder::ColorMatrix::BT2020_CL,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
enum class Colorimetry : int32_t {
  UNKNOWN = 0,
  BT601_525 = 1,
  BT601_625 = 2,
  BT709 = 3,
  BT2020 = 4,
  BT2020_CL = 5,
  DCI_P3_D65 = 6,
  DCI_P3_D60 = 7,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(Colorimetry val) {
  switch(val) {
  case Colorimetry::UNKNOWN:
    return "UNKNOWN";
  case Colorimetry::BT601_525:
    return "BT601_525";
  case Colorimetry::BT601_625:
    return "BT601_625";
  case Colorimetry::BT709:
    return "BT709";
  case Colorimetry::BT2020:
    return "BT2020";
  case Colorimetry::BT2020_CL:
    return "BT2020_CL";
  case Colorimetry::DCI_P3_D65:
    return "DCI_P3_D65";
  case Colorimetry::DCI_P3_D60:
    return "DCI_P3_D60";
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
constexpr inline std::array<::com::rdk::hal::videodecoder::Colorimetry, 8> enum_values<::com::rdk::hal::videodecoder::Colorimetry> = {
  ::com::rdk::hal::videodecoder::Colorimetry::UNKNOWN,
  ::com::rdk::hal::videodecoder::Colorimetry::BT601_525,
  ::com::rdk::hal::videodecoder::Colorimetry::BT601_625,
  ::com::rdk::hal::videodecoder::Colorimetry::BT709,
  ::com::rdk::hal::videodecoder::Colorimetry::BT2020,
  ::com::rdk::hal::videodecoder::Colorimetry::BT2020_CL,
  ::com::rdk::hal::videodecoder::Colorimetry::DCI_P3_D65,
  ::com::rdk::hal::videodecoder::Colorimetry::DCI_P3_D60,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

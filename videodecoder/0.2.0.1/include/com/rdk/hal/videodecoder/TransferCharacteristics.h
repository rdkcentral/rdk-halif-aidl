#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
enum class TransferCharacteristics : int32_t {
  UNKNOWN = -1,
  BT709 = 1,
  UNSPECIFIED = 2,
  BT470M_GAMMA22 = 4,
  BT470BG_GAMMA28 = 5,
  SMPTE170M = 6,
  SMPTE240M = 7,
  LINEAR = 8,
  LOG_100 = 9,
  LOG_316 = 10,
  IEC61966_2_4 = 11,
  BT1361 = 12,
  SRGB = 13,
  BT2020_10 = 14,
  BT2020_12 = 15,
  SMPTE2084_PQ = 16,
  SMPTE428 = 17,
  ARIB_STD_B67_HLG = 18,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(TransferCharacteristics val) {
  switch(val) {
  case TransferCharacteristics::UNKNOWN:
    return "UNKNOWN";
  case TransferCharacteristics::BT709:
    return "BT709";
  case TransferCharacteristics::UNSPECIFIED:
    return "UNSPECIFIED";
  case TransferCharacteristics::BT470M_GAMMA22:
    return "BT470M_GAMMA22";
  case TransferCharacteristics::BT470BG_GAMMA28:
    return "BT470BG_GAMMA28";
  case TransferCharacteristics::SMPTE170M:
    return "SMPTE170M";
  case TransferCharacteristics::SMPTE240M:
    return "SMPTE240M";
  case TransferCharacteristics::LINEAR:
    return "LINEAR";
  case TransferCharacteristics::LOG_100:
    return "LOG_100";
  case TransferCharacteristics::LOG_316:
    return "LOG_316";
  case TransferCharacteristics::IEC61966_2_4:
    return "IEC61966_2_4";
  case TransferCharacteristics::BT1361:
    return "BT1361";
  case TransferCharacteristics::SRGB:
    return "SRGB";
  case TransferCharacteristics::BT2020_10:
    return "BT2020_10";
  case TransferCharacteristics::BT2020_12:
    return "BT2020_12";
  case TransferCharacteristics::SMPTE2084_PQ:
    return "SMPTE2084_PQ";
  case TransferCharacteristics::SMPTE428:
    return "SMPTE428";
  case TransferCharacteristics::ARIB_STD_B67_HLG:
    return "ARIB_STD_B67_HLG";
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
constexpr inline std::array<::com::rdk::hal::videodecoder::TransferCharacteristics, 18> enum_values<::com::rdk::hal::videodecoder::TransferCharacteristics> = {
  ::com::rdk::hal::videodecoder::TransferCharacteristics::UNKNOWN,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::BT709,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::UNSPECIFIED,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::BT470M_GAMMA22,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::BT470BG_GAMMA28,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::SMPTE170M,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::SMPTE240M,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::LINEAR,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::LOG_100,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::LOG_316,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::IEC61966_2_4,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::BT1361,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::SRGB,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::BT2020_10,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::BT2020_12,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::SMPTE2084_PQ,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::SMPTE428,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::ARIB_STD_B67_HLG,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
enum class PCMFormat : int32_t {
  F64LE = 0,
  F64BE = 1,
  F32LE = 2,
  F32BE = 3,
  S32LE = 4,
  S32BE = 5,
  U32LE = 6,
  U32BE = 7,
  S24_32LE = 8,
  S24_32BE = 9,
  U24_32LE = 10,
  U24_32BE = 11,
  S24LE = 12,
  S24BE = 13,
  U24LE = 14,
  U24BE = 15,
  S20LE = 16,
  S20BE = 17,
  U20LE = 18,
  U20BE = 19,
  S18LE = 20,
  S18BE = 21,
  U18LE = 22,
  U18BE = 23,
  S16LE = 24,
  S16BE = 25,
  U16LE = 26,
  U16BE = 27,
  S8 = 28,
  U8 = 29,
};
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
[[nodiscard]] static inline std::string toString(PCMFormat val) {
  switch(val) {
  case PCMFormat::F64LE:
    return "F64LE";
  case PCMFormat::F64BE:
    return "F64BE";
  case PCMFormat::F32LE:
    return "F32LE";
  case PCMFormat::F32BE:
    return "F32BE";
  case PCMFormat::S32LE:
    return "S32LE";
  case PCMFormat::S32BE:
    return "S32BE";
  case PCMFormat::U32LE:
    return "U32LE";
  case PCMFormat::U32BE:
    return "U32BE";
  case PCMFormat::S24_32LE:
    return "S24_32LE";
  case PCMFormat::S24_32BE:
    return "S24_32BE";
  case PCMFormat::U24_32LE:
    return "U24_32LE";
  case PCMFormat::U24_32BE:
    return "U24_32BE";
  case PCMFormat::S24LE:
    return "S24LE";
  case PCMFormat::S24BE:
    return "S24BE";
  case PCMFormat::U24LE:
    return "U24LE";
  case PCMFormat::U24BE:
    return "U24BE";
  case PCMFormat::S20LE:
    return "S20LE";
  case PCMFormat::S20BE:
    return "S20BE";
  case PCMFormat::U20LE:
    return "U20LE";
  case PCMFormat::U20BE:
    return "U20BE";
  case PCMFormat::S18LE:
    return "S18LE";
  case PCMFormat::S18BE:
    return "S18BE";
  case PCMFormat::U18LE:
    return "U18LE";
  case PCMFormat::U18BE:
    return "U18BE";
  case PCMFormat::S16LE:
    return "S16LE";
  case PCMFormat::S16BE:
    return "S16BE";
  case PCMFormat::U16LE:
    return "U16LE";
  case PCMFormat::U16BE:
    return "U16BE";
  case PCMFormat::S8:
    return "S8";
  case PCMFormat::U8:
    return "U8";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiodecoder::PCMFormat, 30> enum_values<::com::rdk::hal::audiodecoder::PCMFormat> = {
  ::com::rdk::hal::audiodecoder::PCMFormat::F64LE,
  ::com::rdk::hal::audiodecoder::PCMFormat::F64BE,
  ::com::rdk::hal::audiodecoder::PCMFormat::F32LE,
  ::com::rdk::hal::audiodecoder::PCMFormat::F32BE,
  ::com::rdk::hal::audiodecoder::PCMFormat::S32LE,
  ::com::rdk::hal::audiodecoder::PCMFormat::S32BE,
  ::com::rdk::hal::audiodecoder::PCMFormat::U32LE,
  ::com::rdk::hal::audiodecoder::PCMFormat::U32BE,
  ::com::rdk::hal::audiodecoder::PCMFormat::S24_32LE,
  ::com::rdk::hal::audiodecoder::PCMFormat::S24_32BE,
  ::com::rdk::hal::audiodecoder::PCMFormat::U24_32LE,
  ::com::rdk::hal::audiodecoder::PCMFormat::U24_32BE,
  ::com::rdk::hal::audiodecoder::PCMFormat::S24LE,
  ::com::rdk::hal::audiodecoder::PCMFormat::S24BE,
  ::com::rdk::hal::audiodecoder::PCMFormat::U24LE,
  ::com::rdk::hal::audiodecoder::PCMFormat::U24BE,
  ::com::rdk::hal::audiodecoder::PCMFormat::S20LE,
  ::com::rdk::hal::audiodecoder::PCMFormat::S20BE,
  ::com::rdk::hal::audiodecoder::PCMFormat::U20LE,
  ::com::rdk::hal::audiodecoder::PCMFormat::U20BE,
  ::com::rdk::hal::audiodecoder::PCMFormat::S18LE,
  ::com::rdk::hal::audiodecoder::PCMFormat::S18BE,
  ::com::rdk::hal::audiodecoder::PCMFormat::U18LE,
  ::com::rdk::hal::audiodecoder::PCMFormat::U18BE,
  ::com::rdk::hal::audiodecoder::PCMFormat::S16LE,
  ::com::rdk::hal::audiodecoder::PCMFormat::S16BE,
  ::com::rdk::hal::audiodecoder::PCMFormat::U16LE,
  ::com::rdk::hal::audiodecoder::PCMFormat::U16BE,
  ::com::rdk::hal::audiodecoder::PCMFormat::S8,
  ::com::rdk::hal::audiodecoder::PCMFormat::U8,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

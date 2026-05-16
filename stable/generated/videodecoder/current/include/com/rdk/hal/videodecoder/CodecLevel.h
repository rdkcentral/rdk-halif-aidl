#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
enum class CodecLevel : int32_t {
  MPEG2_LEVEL_LOW = 1,
  MPEG2_LEVEL_MAIN = 2,
  MPEG2_LEVEL_HIGH = 3,
  H264_LEVEL_3 = 100,
  H264_LEVEL_3_1 = 101,
  H264_LEVEL_4 = 102,
  H264_LEVEL_4_1 = 103,
  H264_LEVEL_5 = 104,
  H264_LEVEL_5_1 = 105,
  H264_LEVEL_5_2 = 106,
  H265_LEVEL_4 = 200,
  H265_LEVEL_4_1 = 201,
  H265_LEVEL_5 = 202,
  H265_LEVEL_5_1 = 203,
  H265_LEVEL_5_2 = 204,
  H265_LEVEL_6 = 205,
  H265_LEVEL_6_1 = 206,
  H265_LEVEL_6_2 = 207,
  VP9_LEVEL_1 = 300,
  VP9_LEVEL_1_1 = 301,
  VP9_LEVEL_2 = 302,
  VP9_LEVEL_2_1 = 303,
  VP9_LEVEL_3 = 304,
  VP9_LEVEL_3_1 = 305,
  VP9_LEVEL_4 = 306,
  VP9_LEVEL_4_1 = 307,
  VP9_LEVEL_5 = 308,
  VP9_LEVEL_5_1 = 309,
  VP9_LEVEL_5_2 = 310,
  VP9_LEVEL_6 = 311,
  VP9_LEVEL_6_1 = 312,
  VP9_LEVEL_6_2 = 313,
  AV1_LEVEL_4_0 = 400,
  AV1_LEVEL_4_1 = 401,
  AV1_LEVEL_5_0 = 402,
  AV1_LEVEL_5_1 = 403,
  AV1_LEVEL_6_0 = 404,
  AV1_LEVEL_6_1 = 405,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(CodecLevel val) {
  switch(val) {
  case CodecLevel::MPEG2_LEVEL_LOW:
    return "MPEG2_LEVEL_LOW";
  case CodecLevel::MPEG2_LEVEL_MAIN:
    return "MPEG2_LEVEL_MAIN";
  case CodecLevel::MPEG2_LEVEL_HIGH:
    return "MPEG2_LEVEL_HIGH";
  case CodecLevel::H264_LEVEL_3:
    return "H264_LEVEL_3";
  case CodecLevel::H264_LEVEL_3_1:
    return "H264_LEVEL_3_1";
  case CodecLevel::H264_LEVEL_4:
    return "H264_LEVEL_4";
  case CodecLevel::H264_LEVEL_4_1:
    return "H264_LEVEL_4_1";
  case CodecLevel::H264_LEVEL_5:
    return "H264_LEVEL_5";
  case CodecLevel::H264_LEVEL_5_1:
    return "H264_LEVEL_5_1";
  case CodecLevel::H264_LEVEL_5_2:
    return "H264_LEVEL_5_2";
  case CodecLevel::H265_LEVEL_4:
    return "H265_LEVEL_4";
  case CodecLevel::H265_LEVEL_4_1:
    return "H265_LEVEL_4_1";
  case CodecLevel::H265_LEVEL_5:
    return "H265_LEVEL_5";
  case CodecLevel::H265_LEVEL_5_1:
    return "H265_LEVEL_5_1";
  case CodecLevel::H265_LEVEL_5_2:
    return "H265_LEVEL_5_2";
  case CodecLevel::H265_LEVEL_6:
    return "H265_LEVEL_6";
  case CodecLevel::H265_LEVEL_6_1:
    return "H265_LEVEL_6_1";
  case CodecLevel::H265_LEVEL_6_2:
    return "H265_LEVEL_6_2";
  case CodecLevel::VP9_LEVEL_1:
    return "VP9_LEVEL_1";
  case CodecLevel::VP9_LEVEL_1_1:
    return "VP9_LEVEL_1_1";
  case CodecLevel::VP9_LEVEL_2:
    return "VP9_LEVEL_2";
  case CodecLevel::VP9_LEVEL_2_1:
    return "VP9_LEVEL_2_1";
  case CodecLevel::VP9_LEVEL_3:
    return "VP9_LEVEL_3";
  case CodecLevel::VP9_LEVEL_3_1:
    return "VP9_LEVEL_3_1";
  case CodecLevel::VP9_LEVEL_4:
    return "VP9_LEVEL_4";
  case CodecLevel::VP9_LEVEL_4_1:
    return "VP9_LEVEL_4_1";
  case CodecLevel::VP9_LEVEL_5:
    return "VP9_LEVEL_5";
  case CodecLevel::VP9_LEVEL_5_1:
    return "VP9_LEVEL_5_1";
  case CodecLevel::VP9_LEVEL_5_2:
    return "VP9_LEVEL_5_2";
  case CodecLevel::VP9_LEVEL_6:
    return "VP9_LEVEL_6";
  case CodecLevel::VP9_LEVEL_6_1:
    return "VP9_LEVEL_6_1";
  case CodecLevel::VP9_LEVEL_6_2:
    return "VP9_LEVEL_6_2";
  case CodecLevel::AV1_LEVEL_4_0:
    return "AV1_LEVEL_4_0";
  case CodecLevel::AV1_LEVEL_4_1:
    return "AV1_LEVEL_4_1";
  case CodecLevel::AV1_LEVEL_5_0:
    return "AV1_LEVEL_5_0";
  case CodecLevel::AV1_LEVEL_5_1:
    return "AV1_LEVEL_5_1";
  case CodecLevel::AV1_LEVEL_6_0:
    return "AV1_LEVEL_6_0";
  case CodecLevel::AV1_LEVEL_6_1:
    return "AV1_LEVEL_6_1";
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
constexpr inline std::array<::com::rdk::hal::videodecoder::CodecLevel, 38> enum_values<::com::rdk::hal::videodecoder::CodecLevel> = {
  ::com::rdk::hal::videodecoder::CodecLevel::MPEG2_LEVEL_LOW,
  ::com::rdk::hal::videodecoder::CodecLevel::MPEG2_LEVEL_MAIN,
  ::com::rdk::hal::videodecoder::CodecLevel::MPEG2_LEVEL_HIGH,
  ::com::rdk::hal::videodecoder::CodecLevel::H264_LEVEL_3,
  ::com::rdk::hal::videodecoder::CodecLevel::H264_LEVEL_3_1,
  ::com::rdk::hal::videodecoder::CodecLevel::H264_LEVEL_4,
  ::com::rdk::hal::videodecoder::CodecLevel::H264_LEVEL_4_1,
  ::com::rdk::hal::videodecoder::CodecLevel::H264_LEVEL_5,
  ::com::rdk::hal::videodecoder::CodecLevel::H264_LEVEL_5_1,
  ::com::rdk::hal::videodecoder::CodecLevel::H264_LEVEL_5_2,
  ::com::rdk::hal::videodecoder::CodecLevel::H265_LEVEL_4,
  ::com::rdk::hal::videodecoder::CodecLevel::H265_LEVEL_4_1,
  ::com::rdk::hal::videodecoder::CodecLevel::H265_LEVEL_5,
  ::com::rdk::hal::videodecoder::CodecLevel::H265_LEVEL_5_1,
  ::com::rdk::hal::videodecoder::CodecLevel::H265_LEVEL_5_2,
  ::com::rdk::hal::videodecoder::CodecLevel::H265_LEVEL_6,
  ::com::rdk::hal::videodecoder::CodecLevel::H265_LEVEL_6_1,
  ::com::rdk::hal::videodecoder::CodecLevel::H265_LEVEL_6_2,
  ::com::rdk::hal::videodecoder::CodecLevel::VP9_LEVEL_1,
  ::com::rdk::hal::videodecoder::CodecLevel::VP9_LEVEL_1_1,
  ::com::rdk::hal::videodecoder::CodecLevel::VP9_LEVEL_2,
  ::com::rdk::hal::videodecoder::CodecLevel::VP9_LEVEL_2_1,
  ::com::rdk::hal::videodecoder::CodecLevel::VP9_LEVEL_3,
  ::com::rdk::hal::videodecoder::CodecLevel::VP9_LEVEL_3_1,
  ::com::rdk::hal::videodecoder::CodecLevel::VP9_LEVEL_4,
  ::com::rdk::hal::videodecoder::CodecLevel::VP9_LEVEL_4_1,
  ::com::rdk::hal::videodecoder::CodecLevel::VP9_LEVEL_5,
  ::com::rdk::hal::videodecoder::CodecLevel::VP9_LEVEL_5_1,
  ::com::rdk::hal::videodecoder::CodecLevel::VP9_LEVEL_5_2,
  ::com::rdk::hal::videodecoder::CodecLevel::VP9_LEVEL_6,
  ::com::rdk::hal::videodecoder::CodecLevel::VP9_LEVEL_6_1,
  ::com::rdk::hal::videodecoder::CodecLevel::VP9_LEVEL_6_2,
  ::com::rdk::hal::videodecoder::CodecLevel::AV1_LEVEL_4_0,
  ::com::rdk::hal::videodecoder::CodecLevel::AV1_LEVEL_4_1,
  ::com::rdk::hal::videodecoder::CodecLevel::AV1_LEVEL_5_0,
  ::com::rdk::hal::videodecoder::CodecLevel::AV1_LEVEL_5_1,
  ::com::rdk::hal::videodecoder::CodecLevel::AV1_LEVEL_6_0,
  ::com::rdk::hal::videodecoder::CodecLevel::AV1_LEVEL_6_1,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

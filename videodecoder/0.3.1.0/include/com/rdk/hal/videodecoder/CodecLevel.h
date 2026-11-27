#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
// @aidl-doc
/**
 *  @brief     Codec capability definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */
enum class CodecLevel : int32_t {
  // @aidl-doc
  /** MPEG-2 Low Level */
  MPEG2_LEVEL_LOW = 1,
  // @aidl-doc
  /** MPEG-2 Main Level */
  MPEG2_LEVEL_MAIN = 2,
  // @aidl-doc
  /** MPEG-2 High Level */
  MPEG2_LEVEL_HIGH = 3,
  // @aidl-doc
  /** Standard for SD and lower HD resolutions */
  H264_LEVEL_3 = 100,
  // @aidl-doc
  /** Higher bitrate HD support */
  H264_LEVEL_3_1 = 101,
  // @aidl-doc
  /** Supports Full HD (1080p) broadcasting */
  H264_LEVEL_4 = 102,
  // @aidl-doc
  /** Used for Blu-ray and digital TV */
  H264_LEVEL_4_1 = 103,
  // @aidl-doc
  /** Supports 4K broadcasting */
  H264_LEVEL_5 = 104,
  // @aidl-doc
  /** High-bitrate 4K support */
  H264_LEVEL_5_1 = 105,
  // @aidl-doc
  /** Advanced 4K applications */
  H264_LEVEL_5_2 = 106,
  // @aidl-doc
  /** Standard 4K resolution support */
  H265_LEVEL_4 = 200,
  // @aidl-doc
  /** High-bitrate 4K */
  H265_LEVEL_4_1 = 201,
  // @aidl-doc
  /** Supports higher frame rates */
  H265_LEVEL_5 = 202,
  // @aidl-doc
  /** High-efficiency UHD broadcast */
  H265_LEVEL_5_1 = 203,
  // @aidl-doc
  /** Used for high-bitrate 4K HDR */
  H265_LEVEL_5_2 = 204,
  // @aidl-doc
  /** 8K resolution support */
  H265_LEVEL_6 = 205,
  // @aidl-doc
  /** High-bitrate 8K support */
  H265_LEVEL_6_1 = 206,
  // @aidl-doc
  /** Highest efficiency for next-gen broadcasting */
  H265_LEVEL_6_2 = 207,
  // @aidl-doc
  /** VP9 level 1 */
  VP9_LEVEL_1 = 300,
  // @aidl-doc
  /** VP9 level 1.1 */
  VP9_LEVEL_1_1 = 301,
  // @aidl-doc
  /** VP9 level 2 */
  VP9_LEVEL_2 = 302,
  // @aidl-doc
  /** VP9 level 2.1 */
  VP9_LEVEL_2_1 = 303,
  // @aidl-doc
  /** VP9 level 3 */
  VP9_LEVEL_3 = 304,
  // @aidl-doc
  /** VP9 level 3.1 */
  VP9_LEVEL_3_1 = 305,
  // @aidl-doc
  /** Standard for 1080p */
  VP9_LEVEL_4 = 306,
  // @aidl-doc
  /** VP9 level 4.1 */
  VP9_LEVEL_4_1 = 307,
  // @aidl-doc
  /** Standard for 4K UHD */
  VP9_LEVEL_5 = 308,
  // @aidl-doc
  /** VP9 level 5.1 */
  VP9_LEVEL_5_1 = 309,
  // @aidl-doc
  /** High-bitrate 4K HDR */
  VP9_LEVEL_5_2 = 310,
  // @aidl-doc
  /** VP9 level 6 */
  VP9_LEVEL_6 = 311,
  // @aidl-doc
  /** VP9 level 6.1 */
  VP9_LEVEL_6_1 = 312,
  // @aidl-doc
  /** Advanced HDR and 8K */
  VP9_LEVEL_6_2 = 313,
  // @aidl-doc
  /** Standard 4K resolution */
  AV1_LEVEL_4_0 = 400,
  // @aidl-doc
  /** AV1 level 4.1 */
  AV1_LEVEL_4_1 = 401,
  // @aidl-doc
  /** 4K with high efficiency */
  AV1_LEVEL_5_0 = 402,
  // @aidl-doc
  /** High-bitrate 4K HDR */
  AV1_LEVEL_5_1 = 403,
  // @aidl-doc
  /** 8K support */
  AV1_LEVEL_6_0 = 404,
  // @aidl-doc
  /** High-bitrate 8K HDR */
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

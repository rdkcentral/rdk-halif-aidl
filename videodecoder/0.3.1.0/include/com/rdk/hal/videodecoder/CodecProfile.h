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
enum class CodecProfile : int32_t {
  // @aidl-doc
  /** Used in legacy digital broadcasting */
  MPEG2_SIMPLE = 1,
  // @aidl-doc
  /** Most common for digital TV broadcasting */
  MPEG2_MAIN = 2,
  // @aidl-doc
  /** Low complexity, used in mobile and video conferencing */
  H264_BASELINE = 100,
  // @aidl-doc
  /** Standard for digital TV broadcasting (DVB, ATSC) */
  H264_MAIN = 101,
  // @aidl-doc
  /** Used in HD and Blu-ray content */
  H264_HIGH = 102,
  // @aidl-doc
  /** Used in standard UHD/4K broadcasting */
  H265_MAIN = 200,
  // @aidl-doc
  /** Supports 10-bit depth for HDR video */
  H265_MAIN_10 = 201,
  // @aidl-doc
  /** HDR10 support in broadcasting */
  H265_MAIN_10_HDR10 = 202,
  // @aidl-doc
  /** 8-bit 4:2:0 chroma subsampling */
  VP9_PROFILE_0 = 300,
  // @aidl-doc
  /** 8-bit 4:2:2 and 4:4:4 chroma subsampling */
  VP9_PROFILE_1 = 301,
  // @aidl-doc
  /** 10-bit 4:2:0 chroma subsampling (HDR support) */
  VP9_PROFILE_2 = 302,
  // @aidl-doc
  /** 10-bit 4:2:2 and 4:4:4 chroma subsampling */
  VP9_PROFILE_3 = 303,
  // @aidl-doc
  /** 8 or 10-bit color depth with 4:2:0 chroma subsampling */
  AV1_MAIN = 400,
  // @aidl-doc
  /** Supports 4:2:2 and 4:4:4 chroma subsampling */
  AV1_HIGH = 401,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(CodecProfile val) {
  switch(val) {
  case CodecProfile::MPEG2_SIMPLE:
    return "MPEG2_SIMPLE";
  case CodecProfile::MPEG2_MAIN:
    return "MPEG2_MAIN";
  case CodecProfile::H264_BASELINE:
    return "H264_BASELINE";
  case CodecProfile::H264_MAIN:
    return "H264_MAIN";
  case CodecProfile::H264_HIGH:
    return "H264_HIGH";
  case CodecProfile::H265_MAIN:
    return "H265_MAIN";
  case CodecProfile::H265_MAIN_10:
    return "H265_MAIN_10";
  case CodecProfile::H265_MAIN_10_HDR10:
    return "H265_MAIN_10_HDR10";
  case CodecProfile::VP9_PROFILE_0:
    return "VP9_PROFILE_0";
  case CodecProfile::VP9_PROFILE_1:
    return "VP9_PROFILE_1";
  case CodecProfile::VP9_PROFILE_2:
    return "VP9_PROFILE_2";
  case CodecProfile::VP9_PROFILE_3:
    return "VP9_PROFILE_3";
  case CodecProfile::AV1_MAIN:
    return "AV1_MAIN";
  case CodecProfile::AV1_HIGH:
    return "AV1_HIGH";
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
constexpr inline std::array<::com::rdk::hal::videodecoder::CodecProfile, 14> enum_values<::com::rdk::hal::videodecoder::CodecProfile> = {
  ::com::rdk::hal::videodecoder::CodecProfile::MPEG2_SIMPLE,
  ::com::rdk::hal::videodecoder::CodecProfile::MPEG2_MAIN,
  ::com::rdk::hal::videodecoder::CodecProfile::H264_BASELINE,
  ::com::rdk::hal::videodecoder::CodecProfile::H264_MAIN,
  ::com::rdk::hal::videodecoder::CodecProfile::H264_HIGH,
  ::com::rdk::hal::videodecoder::CodecProfile::H265_MAIN,
  ::com::rdk::hal::videodecoder::CodecProfile::H265_MAIN_10,
  ::com::rdk::hal::videodecoder::CodecProfile::H265_MAIN_10_HDR10,
  ::com::rdk::hal::videodecoder::CodecProfile::VP9_PROFILE_0,
  ::com::rdk::hal::videodecoder::CodecProfile::VP9_PROFILE_1,
  ::com::rdk::hal::videodecoder::CodecProfile::VP9_PROFILE_2,
  ::com::rdk::hal::videodecoder::CodecProfile::VP9_PROFILE_3,
  ::com::rdk::hal::videodecoder::CodecProfile::AV1_MAIN,
  ::com::rdk::hal::videodecoder::CodecProfile::AV1_HIGH,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

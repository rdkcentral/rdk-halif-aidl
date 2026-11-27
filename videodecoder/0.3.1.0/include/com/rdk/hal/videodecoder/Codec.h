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
 *  @brief     Video decoder codec type definitions.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */
enum class Codec : int32_t {
  // @aidl-doc
  /** MPEG-2 Video (ISO/IEC 13818-2) */
  MPEG2_VIDEO = 1,
  // @aidl-doc
  /** H.264/AVC (ITU-T H.264 | ISO/IEC 14496-10) */
  H264_AVC = 2,
  // @aidl-doc
  /** H.265/HEVC (ITU-T H.265 | ISO/IEC 23008-2) */
  H265_HEVC = 3,
  // @aidl-doc
  /** VP9 (IETF RFC 7741) */
  VP9 = 4,
  // @aidl-doc
  /** AV1 (AOMedia Video 1) */
  AV1 = 5,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(Codec val) {
  switch(val) {
  case Codec::MPEG2_VIDEO:
    return "MPEG2_VIDEO";
  case Codec::H264_AVC:
    return "H264_AVC";
  case Codec::H265_HEVC:
    return "H265_HEVC";
  case Codec::VP9:
    return "VP9";
  case Codec::AV1:
    return "AV1";
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
constexpr inline std::array<::com::rdk::hal::videodecoder::Codec, 5> enum_values<::com::rdk::hal::videodecoder::Codec> = {
  ::com::rdk::hal::videodecoder::Codec::MPEG2_VIDEO,
  ::com::rdk::hal::videodecoder::Codec::H264_AVC,
  ::com::rdk::hal::videodecoder::Codec::H265_HEVC,
  ::com::rdk::hal::videodecoder::Codec::VP9,
  ::com::rdk::hal::videodecoder::Codec::AV1,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

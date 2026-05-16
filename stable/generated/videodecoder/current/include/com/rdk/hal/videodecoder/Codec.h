#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
enum class Codec : int32_t {
  MPEG2_VIDEO = 1,
  H264_AVC = 2,
  H265_HEVC = 3,
  VP9 = 4,
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

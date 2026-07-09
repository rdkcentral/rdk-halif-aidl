#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
enum class CSDVideoFormat : int32_t {
  AVC_DECODER_CONFIGURATION_RECORD = 0,
  HEVC_DECODER_CONFIGURATION_RECORD = 1,
  AV1_DECODER_CONFIGURATION_RECORD = 2,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(CSDVideoFormat val) {
  switch(val) {
  case CSDVideoFormat::AVC_DECODER_CONFIGURATION_RECORD:
    return "AVC_DECODER_CONFIGURATION_RECORD";
  case CSDVideoFormat::HEVC_DECODER_CONFIGURATION_RECORD:
    return "HEVC_DECODER_CONFIGURATION_RECORD";
  case CSDVideoFormat::AV1_DECODER_CONFIGURATION_RECORD:
    return "AV1_DECODER_CONFIGURATION_RECORD";
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
constexpr inline std::array<::com::rdk::hal::videodecoder::CSDVideoFormat, 3> enum_values<::com::rdk::hal::videodecoder::CSDVideoFormat> = {
  ::com::rdk::hal::videodecoder::CSDVideoFormat::AVC_DECODER_CONFIGURATION_RECORD,
  ::com::rdk::hal::videodecoder::CSDVideoFormat::HEVC_DECODER_CONFIGURATION_RECORD,
  ::com::rdk::hal::videodecoder::CSDVideoFormat::AV1_DECODER_CONFIGURATION_RECORD,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

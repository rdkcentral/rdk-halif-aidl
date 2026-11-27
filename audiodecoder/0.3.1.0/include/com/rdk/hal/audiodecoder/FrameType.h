#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
// @aidl-doc
/**
 * @brief	Different frame types the Audio Decoder can output
 * @author	Luc Kennedy-Lamb
 * @author	Peter Stieglitz
 * @author	Douglas Adler
 */
enum class FrameType : int8_t {
  // @aidl-doc
  /**
   * The decoded audio data is PCM
   * The PCMMetadata in FrameMetadata is valid
   *
   */
  PCM = 0,
  // @aidl-doc
  /**
   * The decoded audio data is an opaque proprietary format.
   * The PCMMetadata in FrameMetadata is not valid
   * The FrameMetadata contains a SoCPrivate field that if of
   * non-zero length is used by the HAL implementation to pass
   * SoC HAL specific opaque metadata.
   *
   */
  SOC_PROPRIETARY = 1,
};
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
[[nodiscard]] static inline std::string toString(FrameType val) {
  switch(val) {
  case FrameType::PCM:
    return "PCM";
  case FrameType::SOC_PROPRIETARY:
    return "SOC_PROPRIETARY";
  default:
    return std::to_string(static_cast<int8_t>(val));
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
constexpr inline std::array<::com::rdk::hal::audiodecoder::FrameType, 2> enum_values<::com::rdk::hal::audiodecoder::FrameType> = {
  ::com::rdk::hal::audiodecoder::FrameType::PCM,
  ::com::rdk::hal::audiodecoder::FrameType::SOC_PROPRIETARY,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

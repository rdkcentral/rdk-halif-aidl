#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
// @aidl-doc
/**
 *  @brief     HDMI pixel format enum.
 *
 *  Maps to the AVI InfoFrame Y field, defining how chroma subsampling
 *  is encoded in HDMI video output. The selected format affects color fidelity,
 *  bandwidth consumption, and compatibility with the sink device.
 *
 *  Reference: HDMI Specification — AVI InfoFrame Y Field.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
enum class PixelFormat : int32_t {
  // @aidl-doc
  /**
   * RGB 4:4:4 pixel format.
   * Full bandwidth, no chroma subsampling.
   * AVI InfoFrame Y = 0
   */
  RGB_444 = 0,
  // @aidl-doc
  /**
   * YCbCr 4:2:2 pixel format.
   * Horizontal chroma subsampling.
   * AVI InfoFrame Y = 1
   */
  YCBCR_422 = 1,
  // @aidl-doc
  /**
   * YCbCr 4:4:4 pixel format.
   * No chroma subsampling, full fidelity.
   * AVI InfoFrame Y = 2
   */
  YCBCR_444 = 2,
  // @aidl-doc
  /**
   * YCbCr 4:2:0 pixel format.
   * Subsampled horizontally and vertically — typically used for 4K/60Hz.
   * AVI InfoFrame Y = 3
   */
  YCBCR_420 = 3,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
[[nodiscard]] static inline std::string toString(PixelFormat val) {
  switch(val) {
  case PixelFormat::RGB_444:
    return "RGB_444";
  case PixelFormat::YCBCR_422:
    return "YCBCR_422";
  case PixelFormat::YCBCR_444:
    return "YCBCR_444";
  case PixelFormat::YCBCR_420:
    return "YCBCR_420";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::hdmioutput::PixelFormat, 4> enum_values<::com::rdk::hal::hdmioutput::PixelFormat> = {
  ::com::rdk::hal::hdmioutput::PixelFormat::RGB_444,
  ::com::rdk::hal::hdmioutput::PixelFormat::YCBCR_422,
  ::com::rdk::hal::hdmioutput::PixelFormat::YCBCR_444,
  ::com::rdk::hal::hdmioutput::PixelFormat::YCBCR_420,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

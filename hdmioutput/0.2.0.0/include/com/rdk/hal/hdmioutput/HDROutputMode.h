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
 *  @brief     HDMI HDR output mode enum.
 *
 *  Defines the HDR output encoding mode for HDMI video signals.
 *  These modes control how video frames are signalled to the sink device,
 *  based on content tone-mapping and desired output format.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
enum class HDROutputMode : int32_t {
  // @aidl-doc
  /**
   * Automatically switches based on primary video content,
   * or outputs SDR when no HDR content is active.
   */
  AUTO = 0,
  // @aidl-doc
  /** Output is encoded using Hybrid Log-Gamma (HLG) HDR. */
  HLG = 1,
  // @aidl-doc
  /** Output is encoded using HDR10 (static metadata). */
  HDR10 = 2,
  // @aidl-doc
  /** Output is encoded using HDR10+ (dynamic metadata). */
  HDR10_PLUS = 3,
  // @aidl-doc
  /** Output is encoded using Dolby Vision HDR. */
  DOLBY_VISION = 4,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
[[nodiscard]] static inline std::string toString(HDROutputMode val) {
  switch(val) {
  case HDROutputMode::AUTO:
    return "AUTO";
  case HDROutputMode::HLG:
    return "HLG";
  case HDROutputMode::HDR10:
    return "HDR10";
  case HDROutputMode::HDR10_PLUS:
    return "HDR10_PLUS";
  case HDROutputMode::DOLBY_VISION:
    return "DOLBY_VISION";
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
constexpr inline std::array<::com::rdk::hal::hdmioutput::HDROutputMode, 5> enum_values<::com::rdk::hal::hdmioutput::HDROutputMode> = {
  ::com::rdk::hal::hdmioutput::HDROutputMode::AUTO,
  ::com::rdk::hal::hdmioutput::HDROutputMode::HLG,
  ::com::rdk::hal::hdmioutput::HDROutputMode::HDR10,
  ::com::rdk::hal::hdmioutput::HDROutputMode::HDR10_PLUS,
  ::com::rdk::hal::hdmioutput::HDROutputMode::DOLBY_VISION,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

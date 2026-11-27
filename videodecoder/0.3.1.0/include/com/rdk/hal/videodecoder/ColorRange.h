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
 *  @brief     Video sample range — limited (studio) vs full (computer)
 *             quantisation.
 *
 *  Enum ordinals are aligned with ITU-T H.273 / ISO/IEC 23091-2
 *  `video_full_range_flag` (CICP VideoFullRangeFlag) so middleware can
 *  forward the bitstream value verbatim by casting to `int`. The
 *  `UNKNOWN` sentinel uses `-1` (repo convention, see
 *  `hdmiinput.SignalState.UNKNOWN`).
 *
 *  - `LIMITED` is the standard studio (head/foot-room) range:
 *      8-bit  → 16..235 (luma), 16..240 (chroma)
 *      10-bit → 64..940 (luma), 64..960 (chroma)
 *  - `FULL` uses the full code range (0..255 / 0..1023). Common for
 *    sRGB content, JPEG-derived imagery, and some HDR mastering pipes.
 *
 *  @author    Gerald Weatherup
 */
enum class ColorRange : int32_t {
  // @aidl-doc
  /** Range not signalled / unknown. */
  UNKNOWN = -1,
  // @aidl-doc
  /** Limited / studio / head-room range. CICP `video_full_range_flag` = 0. */
  LIMITED = 0,
  // @aidl-doc
  /** Full / PC / 0..255 (8-bit) range. CICP `video_full_range_flag` = 1. */
  FULL = 1,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(ColorRange val) {
  switch(val) {
  case ColorRange::UNKNOWN:
    return "UNKNOWN";
  case ColorRange::LIMITED:
    return "LIMITED";
  case ColorRange::FULL:
    return "FULL";
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
constexpr inline std::array<::com::rdk::hal::videodecoder::ColorRange, 3> enum_values<::com::rdk::hal::videodecoder::ColorRange> = {
  ::com::rdk::hal::videodecoder::ColorRange::UNKNOWN,
  ::com::rdk::hal::videodecoder::ColorRange::LIMITED,
  ::com::rdk::hal::videodecoder::ColorRange::FULL,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

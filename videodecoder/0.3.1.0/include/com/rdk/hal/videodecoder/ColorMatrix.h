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
 *  @brief     YCbCr → RGB conversion matrix coefficients.
 *
 *  Identifies the matrix used to derive luma and chroma from the
 *  red/green/blue components (and the inverse for display). Enum ordinals
 *  are aligned with ITU-T H.273 / ISO/IEC 23091-2 `MatrixCoefficients`
 *  (CICP) so middleware can forward bitstream VUI values verbatim by
 *  casting to `int`. The `UNKNOWN` sentinel uses `-1` (repo convention,
 *  see `hdmiinput.SignalState.UNKNOWN`).
 *
 *  Critical distinction for HDR: `BT2020_NCL` (non-constant luminance)
 *  and `BT2020_CL` (constant luminance) differ — the bitstream signals
 *  which is in use. PQ/HLG HDR streams typically use `BT2020_NCL`.
 *
 *  CICP values not listed here (2 = unspecified, 3 = reserved, 4 = FCC,
 *  8 = YCgCo, 11 = SMPTE 2085, 12–14 = chroma-derived variants) are
 *  uncommon in distribution-grade content and are omitted; add them on
 *  demand.
 *
 *  @author    Gerald Weatherup
 */
enum class ColorMatrix : int32_t {
  // @aidl-doc
  /** Matrix not signalled / unknown. */
  UNKNOWN = -1,
  // @aidl-doc
  /** Identity (RGB / GBR) — no YCbCr conversion. CICP value 0. */
  IDENTITY = 0,
  // @aidl-doc
  /** ITU-R BT.709 / SMPTE RP 177. CICP value 1. */
  BT709 = 1,
  // @aidl-doc
  /**
   * Unspecified by the bitstream — distinct from UNKNOWN. The stream
   * explicitly signalled "unspecified" (CICP value 2); downstream code
   * should apply a default. UNKNOWN by contrast means no signal was
   * carried at all (no AIDL override sent, no VUI in the bitstream).
   */
  UNSPECIFIED = 2,
  // @aidl-doc
  /** ITU-R BT.601-7 625-line (PAL/SECAM). CICP value 5. */
  BT601_625 = 5,
  // @aidl-doc
  /** ITU-R BT.601-7 525-line / SMPTE 170M (NTSC). CICP value 6. */
  BT601_525 = 6,
  // @aidl-doc
  /** SMPTE 240M. CICP value 7. */
  SMPTE240M = 7,
  // @aidl-doc
  /** ITU-R BT.2020 non-constant luminance. CICP value 9. */
  BT2020_NCL = 9,
  // @aidl-doc
  /** ITU-R BT.2020 constant luminance. CICP value 10. */
  BT2020_CL = 10,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(ColorMatrix val) {
  switch(val) {
  case ColorMatrix::UNKNOWN:
    return "UNKNOWN";
  case ColorMatrix::IDENTITY:
    return "IDENTITY";
  case ColorMatrix::BT709:
    return "BT709";
  case ColorMatrix::UNSPECIFIED:
    return "UNSPECIFIED";
  case ColorMatrix::BT601_625:
    return "BT601_625";
  case ColorMatrix::BT601_525:
    return "BT601_525";
  case ColorMatrix::SMPTE240M:
    return "SMPTE240M";
  case ColorMatrix::BT2020_NCL:
    return "BT2020_NCL";
  case ColorMatrix::BT2020_CL:
    return "BT2020_CL";
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
constexpr inline std::array<::com::rdk::hal::videodecoder::ColorMatrix, 9> enum_values<::com::rdk::hal::videodecoder::ColorMatrix> = {
  ::com::rdk::hal::videodecoder::ColorMatrix::UNKNOWN,
  ::com::rdk::hal::videodecoder::ColorMatrix::IDENTITY,
  ::com::rdk::hal::videodecoder::ColorMatrix::BT709,
  ::com::rdk::hal::videodecoder::ColorMatrix::UNSPECIFIED,
  ::com::rdk::hal::videodecoder::ColorMatrix::BT601_625,
  ::com::rdk::hal::videodecoder::ColorMatrix::BT601_525,
  ::com::rdk::hal::videodecoder::ColorMatrix::SMPTE240M,
  ::com::rdk::hal::videodecoder::ColorMatrix::BT2020_NCL,
  ::com::rdk::hal::videodecoder::ColorMatrix::BT2020_CL,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

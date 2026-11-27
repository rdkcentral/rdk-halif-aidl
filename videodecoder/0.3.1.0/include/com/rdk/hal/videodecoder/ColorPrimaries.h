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
 *  @brief     CIE chromaticity coordinates of the display primaries (the
 *             "colour gamut" of the stream).
 *
 *  Enum ordinals are aligned with ITU-T H.273 / ISO/IEC 23091-2
 *  `ColourPrimaries` (CICP) so middleware can forward bitstream VUI
 *  values verbatim by casting to `int`. The `UNKNOWN` sentinel uses `-1`
 *  (repo convention, see `hdmiinput.SignalState.UNKNOWN`).
 *
 *  In HDR signalling, primaries are typically `BT2020` while the transfer
 *  function (`TransferCharacteristics`) distinguishes the HDR system in use
 *  (PQ vs HLG).
 *
 *  CICP values 0 (reserved), 2 (unspecified), 3 (reserved), and 13–21
 *  (reserved) are omitted; the rest match their CICP code points.
 *
 *  @author    Gerald Weatherup
 */
enum class ColorPrimaries : int32_t {
  // @aidl-doc
  /** Primaries not signalled / unknown. */
  UNKNOWN = -1,
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
  /** ITU-R BT.470 System M. CICP value 4. */
  BT470M = 4,
  // @aidl-doc
  /** ITU-R BT.470 System B/G (PAL/SECAM). CICP value 5. */
  BT470BG = 5,
  // @aidl-doc
  /** SMPTE 170M / ITU-R BT.601 525-line (NTSC). CICP value 6. */
  BT601_525 = 6,
  // @aidl-doc
  /** SMPTE 240M. CICP value 7. */
  SMPTE240M = 7,
  // @aidl-doc
  /** Generic film (Illuminant C). CICP value 8. */
  FILM = 8,
  // @aidl-doc
  /** ITU-R BT.2020 / BT.2100. CICP value 9. */
  BT2020 = 9,
  // @aidl-doc
  /** SMPTE ST 428-1 / DCDM. CICP value 10. */
  SMPTE428 = 10,
  // @aidl-doc
  /** DCI-P3 with D60 white point (theatrical). CICP value 11. */
  DCI_P3_D60 = 11,
  // @aidl-doc
  /** Display P3 — DCI-P3 with D65 white point (home video / streaming). CICP value 12. */
  DISPLAY_P3 = 12,
  // @aidl-doc
  /** EBU Tech 3213-E. CICP value 22. */
  EBU3213 = 22,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(ColorPrimaries val) {
  switch(val) {
  case ColorPrimaries::UNKNOWN:
    return "UNKNOWN";
  case ColorPrimaries::BT709:
    return "BT709";
  case ColorPrimaries::UNSPECIFIED:
    return "UNSPECIFIED";
  case ColorPrimaries::BT470M:
    return "BT470M";
  case ColorPrimaries::BT470BG:
    return "BT470BG";
  case ColorPrimaries::BT601_525:
    return "BT601_525";
  case ColorPrimaries::SMPTE240M:
    return "SMPTE240M";
  case ColorPrimaries::FILM:
    return "FILM";
  case ColorPrimaries::BT2020:
    return "BT2020";
  case ColorPrimaries::SMPTE428:
    return "SMPTE428";
  case ColorPrimaries::DCI_P3_D60:
    return "DCI_P3_D60";
  case ColorPrimaries::DISPLAY_P3:
    return "DISPLAY_P3";
  case ColorPrimaries::EBU3213:
    return "EBU3213";
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
constexpr inline std::array<::com::rdk::hal::videodecoder::ColorPrimaries, 13> enum_values<::com::rdk::hal::videodecoder::ColorPrimaries> = {
  ::com::rdk::hal::videodecoder::ColorPrimaries::UNKNOWN,
  ::com::rdk::hal::videodecoder::ColorPrimaries::BT709,
  ::com::rdk::hal::videodecoder::ColorPrimaries::UNSPECIFIED,
  ::com::rdk::hal::videodecoder::ColorPrimaries::BT470M,
  ::com::rdk::hal::videodecoder::ColorPrimaries::BT470BG,
  ::com::rdk::hal::videodecoder::ColorPrimaries::BT601_525,
  ::com::rdk::hal::videodecoder::ColorPrimaries::SMPTE240M,
  ::com::rdk::hal::videodecoder::ColorPrimaries::FILM,
  ::com::rdk::hal::videodecoder::ColorPrimaries::BT2020,
  ::com::rdk::hal::videodecoder::ColorPrimaries::SMPTE428,
  ::com::rdk::hal::videodecoder::ColorPrimaries::DCI_P3_D60,
  ::com::rdk::hal::videodecoder::ColorPrimaries::DISPLAY_P3,
  ::com::rdk::hal::videodecoder::ColorPrimaries::EBU3213,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

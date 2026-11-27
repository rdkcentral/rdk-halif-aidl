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
 *  @brief     Opto-electrical transfer function (OETF / EOTF) — the
 *             gamma / HDR curve of the stream.
 *
 *  Enum ordinals are aligned with ITU-T H.273 / ISO/IEC 23091-2
 *  `TransferCharacteristics` (CICP) so middleware can forward bitstream
 *  VUI values verbatim by casting to `int`. The `UNKNOWN` sentinel uses
 *  `-1` (repo convention, see `hdmiinput.SignalState.UNKNOWN`).
 *
 *  This is the field that distinguishes HDR from SDR even when primaries
 *  are the same: HDR10 uses `SMPTE2084_PQ`, HLG uses
 *  `ARIB_STD_B67_HLG`, while their primaries are typically `BT.2020`.
 *
 *  CICP values 0 (reserved), 2 (unspecified), and 3 (reserved) are
 *  omitted; the rest are present and equal their CICP code points.
 *
 *  @author    Gerald Weatherup
 */
enum class TransferCharacteristics : int32_t {
  // @aidl-doc
  /** Transfer characteristics not signalled / unknown. */
  UNKNOWN = -1,
  // @aidl-doc
  /** ITU-R BT.709 / BT.601 / BT.2020 10-bit SDR. CICP value 1. */
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
  /** ITU-R BT.470 System M. Assumed display gamma 2.2. CICP value 4. */
  BT470M_GAMMA22 = 4,
  // @aidl-doc
  /** ITU-R BT.470 System B/G (PAL/SECAM). Assumed display gamma 2.8. CICP value 5. */
  BT470BG_GAMMA28 = 5,
  // @aidl-doc
  /** SMPTE 170M (NTSC). CICP value 6. */
  SMPTE170M = 6,
  // @aidl-doc
  /** SMPTE 240M. CICP value 7. */
  SMPTE240M = 7,
  // @aidl-doc
  /** Linear (no transfer). CICP value 8. */
  LINEAR = 8,
  // @aidl-doc
  /** Logarithmic, 100:1 contrast range. CICP value 9. */
  LOG_100 = 9,
  // @aidl-doc
  /** Logarithmic, 316.2:1 contrast range. CICP value 10. */
  LOG_316 = 10,
  // @aidl-doc
  /** IEC 61966-2-4 (xvYCC). CICP value 11. */
  IEC61966_2_4 = 11,
  // @aidl-doc
  /** ITU-R BT.1361 extended colour gamut. CICP value 12. */
  BT1361 = 12,
  // @aidl-doc
  /** IEC 61966-2-1 sRGB / sYCC. CICP value 13. */
  SRGB = 13,
  // @aidl-doc
  /** ITU-R BT.2020 10-bit SDR. CICP value 14. */
  BT2020_10 = 14,
  // @aidl-doc
  /** ITU-R BT.2020 12-bit SDR. CICP value 15. */
  BT2020_12 = 15,
  // @aidl-doc
  /** SMPTE ST 2084 (Perceptual Quantiser) — HDR10. CICP value 16. */
  SMPTE2084_PQ = 16,
  // @aidl-doc
  /** SMPTE ST 428-1 / DCDM. CICP value 17. */
  SMPTE428 = 17,
  // @aidl-doc
  /** ARIB STD-B67 (Hybrid Log-Gamma) — HLG. CICP value 18. */
  ARIB_STD_B67_HLG = 18,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(TransferCharacteristics val) {
  switch(val) {
  case TransferCharacteristics::UNKNOWN:
    return "UNKNOWN";
  case TransferCharacteristics::BT709:
    return "BT709";
  case TransferCharacteristics::UNSPECIFIED:
    return "UNSPECIFIED";
  case TransferCharacteristics::BT470M_GAMMA22:
    return "BT470M_GAMMA22";
  case TransferCharacteristics::BT470BG_GAMMA28:
    return "BT470BG_GAMMA28";
  case TransferCharacteristics::SMPTE170M:
    return "SMPTE170M";
  case TransferCharacteristics::SMPTE240M:
    return "SMPTE240M";
  case TransferCharacteristics::LINEAR:
    return "LINEAR";
  case TransferCharacteristics::LOG_100:
    return "LOG_100";
  case TransferCharacteristics::LOG_316:
    return "LOG_316";
  case TransferCharacteristics::IEC61966_2_4:
    return "IEC61966_2_4";
  case TransferCharacteristics::BT1361:
    return "BT1361";
  case TransferCharacteristics::SRGB:
    return "SRGB";
  case TransferCharacteristics::BT2020_10:
    return "BT2020_10";
  case TransferCharacteristics::BT2020_12:
    return "BT2020_12";
  case TransferCharacteristics::SMPTE2084_PQ:
    return "SMPTE2084_PQ";
  case TransferCharacteristics::SMPTE428:
    return "SMPTE428";
  case TransferCharacteristics::ARIB_STD_B67_HLG:
    return "ARIB_STD_B67_HLG";
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
constexpr inline std::array<::com::rdk::hal::videodecoder::TransferCharacteristics, 18> enum_values<::com::rdk::hal::videodecoder::TransferCharacteristics> = {
  ::com::rdk::hal::videodecoder::TransferCharacteristics::UNKNOWN,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::BT709,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::UNSPECIFIED,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::BT470M_GAMMA22,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::BT470BG_GAMMA28,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::SMPTE170M,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::SMPTE240M,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::LINEAR,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::LOG_100,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::LOG_316,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::IEC61966_2_4,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::BT1361,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::SRGB,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::BT2020_10,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::BT2020_12,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::SMPTE2084_PQ,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::SMPTE428,
  ::com::rdk::hal::videodecoder::TransferCharacteristics::ARIB_STD_B67_HLG,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

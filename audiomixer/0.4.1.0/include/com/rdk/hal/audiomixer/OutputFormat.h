#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
// @aidl-doc
/**
 * @brief     Supported audio output formats for an output port.
 * Enumerates the possible encoded or uncompressed audio formats
 *            that may be supported by an audio output port (HDMI, SPDIF, speakers, etc.).
 *            Used to configure the desired output, or query available modes
 *            for format negotiation and passthrough.
 *
 * Typical usages:
 * - Used in IAudioOutputPort to select or report output format.
 * - Used in OutputPortCapabilities to enumerate what is supported.
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 */
enum class OutputFormat : int32_t {
  // @aidl-doc
  /** Automatically select the best supported format for the connected sink. */
  AUTO = 0,
  // @aidl-doc
  /** Output is passed through as received (bitstream, no re-encoding). */
  PASSTHROUGH = 1,
  // @aidl-doc
  /** Output as uncompressed STEREO PCM. */
  PCM_STEREO = 2,
  // @aidl-doc
  /** Output as AC-3 (Dolby Digital) bitstream. */
  AC3 = 3,
  // @aidl-doc
  /** Output as E-AC-3 (Dolby Digital Plus) bitstream. */
  EAC3 = 4,
  // @aidl-doc
  /** Output as Dolby MAT (Metadata-enhanced Audio Transmission). */
  MAT = 5,
  // @aidl-doc
  /** Output as Dolby TrueHD bitstream. */
  TRUEHD = 6,
  // @aidl-doc
  /** Output as DTS bitstream. */
  DTS = 7,
  // @aidl-doc
  /** Output as DTS-HD Master Audio bitstream. */
  DTS_HD = 8,
  // @aidl-doc
  /** Output as uncompressed Multichannel PCM. */
  PCM_MULTICHANNEL = 9,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(OutputFormat val) {
  switch(val) {
  case OutputFormat::AUTO:
    return "AUTO";
  case OutputFormat::PASSTHROUGH:
    return "PASSTHROUGH";
  case OutputFormat::PCM_STEREO:
    return "PCM_STEREO";
  case OutputFormat::AC3:
    return "AC3";
  case OutputFormat::EAC3:
    return "EAC3";
  case OutputFormat::MAT:
    return "MAT";
  case OutputFormat::TRUEHD:
    return "TRUEHD";
  case OutputFormat::DTS:
    return "DTS";
  case OutputFormat::DTS_HD:
    return "DTS_HD";
  case OutputFormat::PCM_MULTICHANNEL:
    return "PCM_MULTICHANNEL";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiomixer::OutputFormat, 10> enum_values<::com::rdk::hal::audiomixer::OutputFormat> = {
  ::com::rdk::hal::audiomixer::OutputFormat::AUTO,
  ::com::rdk::hal::audiomixer::OutputFormat::PASSTHROUGH,
  ::com::rdk::hal::audiomixer::OutputFormat::PCM_STEREO,
  ::com::rdk::hal::audiomixer::OutputFormat::AC3,
  ::com::rdk::hal::audiomixer::OutputFormat::EAC3,
  ::com::rdk::hal::audiomixer::OutputFormat::MAT,
  ::com::rdk::hal::audiomixer::OutputFormat::TRUEHD,
  ::com::rdk::hal::audiomixer::OutputFormat::DTS,
  ::com::rdk::hal::audiomixer::OutputFormat::DTS_HD,
  ::com::rdk::hal::audiomixer::OutputFormat::PCM_MULTICHANNEL,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

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
 * @brief    Physical / logical type of an audio output port.
 * @details  Provides a programmatic identification of an output port,
 *           independent of the human-readable `OutputPortCapabilities.portName`.
 *           Declared per output port in the HFP YAML and surfaced via
 *           `OutputPortCapabilities.portType`.
 *
 *           Middleware should branch on `portType` (not `portName`) when
 *           applying type-specific policy — e.g. transcode-to-AC3 only on
 *           SPDIF, hot-unplug handling only on HDMI/ARC/EARC, pairing flow
 *           only on BLUETOOTH.
 *
 * @author    Gerald Weatherup
 * @copyright Copyright 2026 RDK Management
 */
enum class OutputPortType : int32_t {
  // @aidl-doc
  /** Type cannot be determined or is platform-specific. */
  UNKNOWN = 0,
  // @aidl-doc
  /** HDMI output (supports PCM, AC3, EAC3, MAT, TrueHD passthrough). */
  HDMI = 1,
  // @aidl-doc
  /** S/PDIF coaxial digital output (supports PCM, AC3, DTS passthrough). */
  SPDIF = 2,
  // @aidl-doc
  /** TOSLINK / optical digital output (electrically distinct from SPDIF coax, same protocol). */
  OPTICAL = 3,
  // @aidl-doc
  /** Analogue line-out / internal speakers / amplifier (PCM only). */
  SPEAKERS = 4,
  // @aidl-doc
  /**
   * Bluetooth audio output (A2DP sink — TV streams to BT speaker / headphones).
   * Connection lifecycle is platform-specific; pairing is typically handled outside
   * the audiomixer HAL. CONNECTION_STATE reflects the active A2DP link.
   */
  BLUETOOTH = 5,
  // @aidl-doc
  /**
   * HDMI Audio Return Channel — TV sends audio back to AVR/soundbar.
   * Logically an output even though the cable is the HDMI input. Format negotiation
   * uses CEC; capability subset of HDMI direct (typically PCM + AC3).
   */
  ARC = 6,
  // @aidl-doc
  /**
   * HDMI Enhanced Audio Return Channel (eARC) — higher bandwidth than ARC.
   * Supports the full HDMI audio format set (MAT, TrueHD, Atmos object audio)
   * via the dedicated Audio Return Data Channel on TMDS.
   */
  EARC = 7,
  // @aidl-doc
  /** Composite analogue audio output bundled with composite video. */
  COMPOSITE = 8,
  // @aidl-doc
  /**
   * Vendor-specific / platform-internal port not covered by the standard types.
   * Use `portName` for differentiation.
   */
  INTERNAL = 1000,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(OutputPortType val) {
  switch(val) {
  case OutputPortType::UNKNOWN:
    return "UNKNOWN";
  case OutputPortType::HDMI:
    return "HDMI";
  case OutputPortType::SPDIF:
    return "SPDIF";
  case OutputPortType::OPTICAL:
    return "OPTICAL";
  case OutputPortType::SPEAKERS:
    return "SPEAKERS";
  case OutputPortType::BLUETOOTH:
    return "BLUETOOTH";
  case OutputPortType::ARC:
    return "ARC";
  case OutputPortType::EARC:
    return "EARC";
  case OutputPortType::COMPOSITE:
    return "COMPOSITE";
  case OutputPortType::INTERNAL:
    return "INTERNAL";
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
constexpr inline std::array<::com::rdk::hal::audiomixer::OutputPortType, 10> enum_values<::com::rdk::hal::audiomixer::OutputPortType> = {
  ::com::rdk::hal::audiomixer::OutputPortType::UNKNOWN,
  ::com::rdk::hal::audiomixer::OutputPortType::HDMI,
  ::com::rdk::hal::audiomixer::OutputPortType::SPDIF,
  ::com::rdk::hal::audiomixer::OutputPortType::OPTICAL,
  ::com::rdk::hal::audiomixer::OutputPortType::SPEAKERS,
  ::com::rdk::hal::audiomixer::OutputPortType::BLUETOOTH,
  ::com::rdk::hal::audiomixer::OutputPortType::ARC,
  ::com::rdk::hal::audiomixer::OutputPortType::EARC,
  ::com::rdk::hal::audiomixer::OutputPortType::COMPOSITE,
  ::com::rdk::hal::audiomixer::OutputPortType::INTERNAL,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

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
 * @brief    Enumerates extensible property keys for Audio Output Port.
 * Used as the key in setProperty/getProperty and onPropertyChanged for
 *           forward-compatible and vendor-specific configuration.
 *           All properties can be read in any state unless otherwise specified.
 *
 * Each property must be documented with:
 *   - Value type (int, boolean, int[], etc.)
 *   - Access (Read-only, Read-write)
 *   - Writeable in states (output ports are written only in READY,
 *     through IAudioOutputPortController)
 *   - Value semantics (enum, range, etc.)
 *
 * @author   Luc Kennedy-Lamb
 * @author   Peter Stieglitz
 * @author   Douglas Adler
 */
enum class OutputPortProperty : int32_t {
  // @aidl-doc
  /**
   * Output port volume.
   * Type: int
   * Range: 0..100
   * Access: Read-write.
   * Writeable in states: READY
   */
  VOLUME = 0,
  // @aidl-doc
  /**
   * Output port audio delay in milliseconds.
   * Type: int
   * Range: Implementation-dependent.
   * Access: Read-write.
   * Writeable in states: READY
   */
  DELAY_MS = 1,
  // @aidl-doc
  /**
   * Output port mute state.
   * Type: boolean
   * Access: Read-write.
   * Writeable in states: READY
   */
  MUTE = 2,
  // @aidl-doc
  /**
   * Output port enabled/disabled state.
   * Type: boolean
   * Access: Read-write.
   * Writeable in states: READY
   */
  ENABLED = 3,
  // @aidl-doc
  /**
   * Configured output audio format.
   * Type: int (OutputFormat enum value)
   * Access: Read-write.
   * Writeable in states: READY
   */
  OUTPUT_FORMAT = 4,
  // @aidl-doc
  /**
   * Supported audio output formats.
   * Type: int[] (com.rdk.hal.audiomixer.OutputFormat enum values)
   * Access: Read-only.
   */
  SUPPORTED_AUDIO_FORMATS = 5,
  // @aidl-doc
  /**
   * True if Dolby Atmos is supported on this output port.
   * Type: boolean
   * Access: Read-only.
   */
  DOLBY_ATMOS_SUPPORT = 6,
  // @aidl-doc
  /**
   * Output port logical state.
   * Type: int (@see com.rdk.hal.audiomixer.State enum)
   * Access: Read-only.
   */
  STATE = 7,
  // @aidl-doc
  /**
   * Physical/logical connection state.
   * Type: int (@see com.rdk.hal.audiomixer.ConnectionState enum)
   * Access: Read-only.
   */
  CONNECTION_STATE = 9,
  // @aidl-doc
  /**
   * Sets the Dolby MS12 Audio Profile/Preset (e.g. "Music", "Movie", "Sports", etc)
   *
   * Type: String
   * Access: Read-write.
   * Writeable in states: READY
   *
   * The value must correspond to a platform-defined AQ profile configuration
   *
   * @see com.rdk.hal.audiomixer.OutputPortCapabilities.dolbyMs12AudioProfiles
   */
  DOLBY_MS12_AUDIO_PROFILE = 10,
  // @aidl-doc
  /**
   * Output port underflows.
   * Type: int
   * Access: Read-only.
   *
   * A count of the underflow (starvation) events that the consumer of the output port has experienced since the port
   * was enabled. A single underflow event is considered to be when the consumer, unexpectedly, has no data to consume
   * until normal data flow resumes. When the port is disabled, the last count should be held until the port is
   * re-enabled, and the count reset.
   */
  METRIC_UNDERFLOWS = 11,
  // @aidl-doc
  /**
   * Output port overflows.
   * Type: int
   * Access: Read-only.
   *
   * A count of the overflow events that the producer has experienced since the port was enabled.
   * A single overflow event is considered to be when the producer, unexpectedly, has no buffer space available to
   * write the data. When the port is disabled, the last count should be held until the port is re-enabled, and the
   * count reset.
   */
  METRIC_OVERFLOWS = 12,
  // @aidl-doc
  /**
   * Vendor-specific extension.
   * Type: Implementation-defined.
   * Access: Read-write or read-only as documented.
   */
  VENDOR_EXTENSION = 1000,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(OutputPortProperty val) {
  switch(val) {
  case OutputPortProperty::VOLUME:
    return "VOLUME";
  case OutputPortProperty::DELAY_MS:
    return "DELAY_MS";
  case OutputPortProperty::MUTE:
    return "MUTE";
  case OutputPortProperty::ENABLED:
    return "ENABLED";
  case OutputPortProperty::OUTPUT_FORMAT:
    return "OUTPUT_FORMAT";
  case OutputPortProperty::SUPPORTED_AUDIO_FORMATS:
    return "SUPPORTED_AUDIO_FORMATS";
  case OutputPortProperty::DOLBY_ATMOS_SUPPORT:
    return "DOLBY_ATMOS_SUPPORT";
  case OutputPortProperty::STATE:
    return "STATE";
  case OutputPortProperty::CONNECTION_STATE:
    return "CONNECTION_STATE";
  case OutputPortProperty::DOLBY_MS12_AUDIO_PROFILE:
    return "DOLBY_MS12_AUDIO_PROFILE";
  case OutputPortProperty::METRIC_UNDERFLOWS:
    return "METRIC_UNDERFLOWS";
  case OutputPortProperty::METRIC_OVERFLOWS:
    return "METRIC_OVERFLOWS";
  case OutputPortProperty::VENDOR_EXTENSION:
    return "VENDOR_EXTENSION";
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
constexpr inline std::array<::com::rdk::hal::audiomixer::OutputPortProperty, 13> enum_values<::com::rdk::hal::audiomixer::OutputPortProperty> = {
  ::com::rdk::hal::audiomixer::OutputPortProperty::VOLUME,
  ::com::rdk::hal::audiomixer::OutputPortProperty::DELAY_MS,
  ::com::rdk::hal::audiomixer::OutputPortProperty::MUTE,
  ::com::rdk::hal::audiomixer::OutputPortProperty::ENABLED,
  ::com::rdk::hal::audiomixer::OutputPortProperty::OUTPUT_FORMAT,
  ::com::rdk::hal::audiomixer::OutputPortProperty::SUPPORTED_AUDIO_FORMATS,
  ::com::rdk::hal::audiomixer::OutputPortProperty::DOLBY_ATMOS_SUPPORT,
  ::com::rdk::hal::audiomixer::OutputPortProperty::STATE,
  ::com::rdk::hal::audiomixer::OutputPortProperty::CONNECTION_STATE,
  ::com::rdk::hal::audiomixer::OutputPortProperty::DOLBY_MS12_AUDIO_PROFILE,
  ::com::rdk::hal::audiomixer::OutputPortProperty::METRIC_UNDERFLOWS,
  ::com::rdk::hal::audiomixer::OutputPortProperty::METRIC_OVERFLOWS,
  ::com::rdk::hal::audiomixer::OutputPortProperty::VENDOR_EXTENSION,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

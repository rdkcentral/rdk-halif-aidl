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
 * @brief    Audio Mixer properties used in property get/set functions.
 *           All properties can be read in any state unless otherwise noted.
 * @author   Luc Kennedy-Lamb
 * @author   Peter Stieglitz
 * @author   Douglas Adler
 */
enum class Property : int32_t {
  // @aidl-doc
  /**
   * Current latency of the mixer in milliseconds.
   *
   * Type: Integer
   * Access: Read-only.
   */
  LATENCY_MS = 0,
  // @aidl-doc
  /**
   * Enables or disables debug tap output for audio analysis.
   *
   * Type: Boolean
   * Access: Read-write.
   * Writeable in states: READY
   */
  DEBUG_TAP_ENABLED = 1,
  // @aidl-doc
  /**
   * Mixer operating mode (e.g., NORMAL, DUCKED).
   *
   * Designed for runtime changes in response to policy or stream priority.
   * TODO: Future Expansion
   *
   * Type: MixingMode (Enum) @see com.rdk.hal.audiomixer.MixingMode
   * Access: Read-write.
   * Writeable in states: READY, STARTED
   *
   * @see MixingMode
   */
  MIXING_MODE = 2,
  // @aidl-doc
  /**
   * Mute state for the mixer output path.
   *
   * Type: Boolean
   * Access: Read-write.
   * Writeable in states: READY, STARTED
   * - false: unmuted (default on open)
   * - true: muted
   */
  MUTE = 3,
  // @aidl-doc
  /**
   * Fader level controlling balance between main and associated audio.
   *
   * Range: 0..100.
   *  - 0   = main audio only (associated fully attenuated)
   *  - 50  = balanced mix (default)
   *  - 100 = associated audio only (main fully attenuated)
   *
   * Used by accessibility features such as descriptive audio (audio
   * description) where the associated audio track narrates the scene
   * over the main programme.
   *
   * <b>Orthogonal to per-input volume:</b> FADER_LEVEL is a cross-input
   * balance control between the main and associated audio inputs only.
   * It is applied <i>after</i> per-input volumes set via
   * IAudioMixerController.setInputVolume() / setInputVolumeRamp().
   *
   * <b>Not a ducking control:</b> for system-sound ducking over arbitrary
   * inputs (e.g. notification beep over main programme), use
   * IAudioMixerController.setInputVolumeRamp() on the main input.
   * FADER_LEVEL is scoped to the main/associated pair only.
   *
   * Type: Integer
   * Access: Read-write.
   * Writeable in states: READY, STARTED
   */
  FADER_LEVEL = 4,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(Property val) {
  switch(val) {
  case Property::LATENCY_MS:
    return "LATENCY_MS";
  case Property::DEBUG_TAP_ENABLED:
    return "DEBUG_TAP_ENABLED";
  case Property::MIXING_MODE:
    return "MIXING_MODE";
  case Property::MUTE:
    return "MUTE";
  case Property::FADER_LEVEL:
    return "FADER_LEVEL";
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
constexpr inline std::array<::com::rdk::hal::audiomixer::Property, 5> enum_values<::com::rdk::hal::audiomixer::Property> = {
  ::com::rdk::hal::audiomixer::Property::LATENCY_MS,
  ::com::rdk::hal::audiomixer::Property::DEBUG_TAP_ENABLED,
  ::com::rdk::hal::audiomixer::Property::MIXING_MODE,
  ::com::rdk::hal::audiomixer::Property::MUTE,
  ::com::rdk::hal::audiomixer::Property::FADER_LEVEL,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

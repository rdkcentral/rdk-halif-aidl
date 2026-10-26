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
 * @brief     Audio source types for mixer input routing.
 * Defines the types of audio sources that can be routed to mixer inputs.
 *            Follows the pattern established by planecontrol::SourceType.
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 */
enum class AudioSourceType : int32_t {
  // @aidl-doc
  /** No audio source is connected to the mixer input. Default/disconnected state. */
  NONE = 0,
  // @aidl-doc
  /** Audio sink output is connected to the mixer input. */
  AUDIO_SINK = 1,
  // @aidl-doc
  /** HDMI input audio is connected to the mixer input. */
  HDMI_INPUT = 2,
  // @aidl-doc
  /** Composite input audio is connected to the mixer input. */
  COMPOSITE_INPUT = 3,
  // @aidl-doc
  /** Application audio is connected to the mixer input. */
  APPLICATION_AUDIO = 4,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(AudioSourceType val) {
  switch(val) {
  case AudioSourceType::NONE:
    return "NONE";
  case AudioSourceType::AUDIO_SINK:
    return "AUDIO_SINK";
  case AudioSourceType::HDMI_INPUT:
    return "HDMI_INPUT";
  case AudioSourceType::COMPOSITE_INPUT:
    return "COMPOSITE_INPUT";
  case AudioSourceType::APPLICATION_AUDIO:
    return "APPLICATION_AUDIO";
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
constexpr inline std::array<::com::rdk::hal::audiomixer::AudioSourceType, 5> enum_values<::com::rdk::hal::audiomixer::AudioSourceType> = {
  ::com::rdk::hal::audiomixer::AudioSourceType::NONE,
  ::com::rdk::hal::audiomixer::AudioSourceType::AUDIO_SINK,
  ::com::rdk::hal::audiomixer::AudioSourceType::HDMI_INPUT,
  ::com::rdk::hal::audiomixer::AudioSourceType::COMPOSITE_INPUT,
  ::com::rdk::hal::audiomixer::AudioSourceType::APPLICATION_AUDIO,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

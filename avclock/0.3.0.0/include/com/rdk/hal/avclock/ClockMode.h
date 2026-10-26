#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
// @aidl-doc
/**
 *  @brief     AV clock modes.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
enum class ClockMode : int32_t {
  // @aidl-doc
  /**
   * AUTO will use AUDIO_MASTER if there is an audio source available otherwise VIDEO_MASTER.
   * AUTO is the default clock mode after a call to `open()`.
   */
  AUTO = 0,
  // @aidl-doc
  /**
   * Use PCR samples as the clock source as provided in successive calls to `notifyPCRSample()`.
   * PCR can only be used on live broadcasts and calls to `setPlaybackRate()` are not allowed.
   * The AV Clock timebase is phase locked to the incoming PCR sample values.
   */
  PCR = 1,
  // @aidl-doc
  /**
   * Use the audio source as the clock master.
   * The AV Clock is crash locked to the first audio sample PTS received for playback.
   * The AV Clock timebase is linked to the audio subsystem clock.
   */
  AUDIO_MASTER = 2,
  // @aidl-doc
  /**
   * Use the video source as the clock master.
   * The AV Clock is crash locked to the first video frame PTS received for playback.
   * The AV Clock timebase is driven by the vendor implementation.
   */
  VIDEO_MASTER = 3,
};
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace avclock {
[[nodiscard]] static inline std::string toString(ClockMode val) {
  switch(val) {
  case ClockMode::AUTO:
    return "AUTO";
  case ClockMode::PCR:
    return "PCR";
  case ClockMode::AUDIO_MASTER:
    return "AUDIO_MASTER";
  case ClockMode::VIDEO_MASTER:
    return "VIDEO_MASTER";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::avclock::ClockMode, 4> enum_values<::com::rdk::hal::avclock::ClockMode> = {
  ::com::rdk::hal::avclock::ClockMode::AUTO,
  ::com::rdk::hal::avclock::ClockMode::PCR,
  ::com::rdk::hal::avclock::ClockMode::AUDIO_MASTER,
  ::com::rdk::hal::avclock::ClockMode::VIDEO_MASTER,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

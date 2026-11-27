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
 * @brief Defines the available mixer operating modes.
 *
 * These modes influence how audio streams are blended within the mixer,
 * including attenuation behaviour during interruptive or priority playback scenarios.
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @copyright Copyright 2024 RDK Management
 */
enum class MixingMode : int32_t {
  // @aidl-doc
  /**
   * Standard mixing behaviour. All streams mix at their configured volumes.
   * FIXME: Only supported format required today
   */
  NORMAL = 0,
  // @aidl-doc
  /**
   * All streams are forcibly muted at the mixer level.
   * TODO: Future expansion
   */
  MUTED = 1,
  // @aidl-doc
  /**
   * Background streams are attenuated while a priority (interruptive) stream plays.
   * TODO: Future expansion
   */
  DUCKED = 2,
  // @aidl-doc
  /**
   * Only the designated stream is played; all others are temporarily muted.
   * TODO: Future expansion
   */
  SOLO = 3,
  // @aidl-doc
  /**
   * Overrides standard mixing rules for special stream behaviour (e.g., emergency alerts).
   * TODO: Future expansion
   */
  MIXED_OVERRIDE = 4,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(MixingMode val) {
  switch(val) {
  case MixingMode::NORMAL:
    return "NORMAL";
  case MixingMode::MUTED:
    return "MUTED";
  case MixingMode::DUCKED:
    return "DUCKED";
  case MixingMode::SOLO:
    return "SOLO";
  case MixingMode::MIXED_OVERRIDE:
    return "MIXED_OVERRIDE";
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
constexpr inline std::array<::com::rdk::hal::audiomixer::MixingMode, 5> enum_values<::com::rdk::hal::audiomixer::MixingMode> = {
  ::com::rdk::hal::audiomixer::MixingMode::NORMAL,
  ::com::rdk::hal::audiomixer::MixingMode::MUTED,
  ::com::rdk::hal::audiomixer::MixingMode::DUCKED,
  ::com::rdk::hal::audiomixer::MixingMode::SOLO,
  ::com::rdk::hal::audiomixer::MixingMode::MIXED_OVERRIDE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

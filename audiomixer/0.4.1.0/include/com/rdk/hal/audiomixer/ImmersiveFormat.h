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
 * @brief    Immersive (object-based) audio carried on an output port.
 * @details  Reported in ActiveOutputFormat.immersive. Combined with
 *           ActiveOutputFormat.format it tells middleware how the immersive
 *           content leaves the port:
 *           - a bitstream format (EAC3, MAT, TRUEHD, DTS_HD) — the objects
 *             are delivered to an external decoder (AVR, soundbar);
 *           - PCM_STEREO or PCM_MULTICHANNEL — the HAL renders the objects
 *             itself to the port's channel layout.
 *
 * @author    Gerald Weatherup
 * @copyright Copyright 2026 RDK Management
 */
enum class ImmersiveFormat : int32_t {
  // @aidl-doc
  /** No immersive content; channel-based audio only. */
  NONE = 0,
  // @aidl-doc
  /** Dolby Atmos. */
  DOLBY_ATMOS = 1,
  // @aidl-doc
  /** DTS:X. */
  DTS_X = 2,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(ImmersiveFormat val) {
  switch(val) {
  case ImmersiveFormat::NONE:
    return "NONE";
  case ImmersiveFormat::DOLBY_ATMOS:
    return "DOLBY_ATMOS";
  case ImmersiveFormat::DTS_X:
    return "DTS_X";
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
constexpr inline std::array<::com::rdk::hal::audiomixer::ImmersiveFormat, 3> enum_values<::com::rdk::hal::audiomixer::ImmersiveFormat> = {
  ::com::rdk::hal::audiomixer::ImmersiveFormat::NONE,
  ::com::rdk::hal::audiomixer::ImmersiveFormat::DOLBY_ATMOS,
  ::com::rdk::hal::audiomixer::ImmersiveFormat::DTS_X,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

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
 * @brief Audio channel position definitions for PCM audio layouts.
 *
 * Defines the standardised channel positions used in multi-channel audio capture.
 * These enumeration values describe the physical or logical placement of audio
 * channels within the audio frame (e.g., front left, surround right, overhead, etc.).
 *
 * Channel positions are typically arranged as:
 * - **Front**: Left, Right, Centre
 * - **Low-Frequency**: Subwoofer / LFE
 * - **Surround/Rear**: Side Left, Side Right, Rear Left, Rear Right, Rear Centre
 * - **Height/Overhead**: Top Front Left, Top Front Right, Top Front Centre, Top Side Left, Top Side Right, Top Rear
 * Left, Top Rear Right
 * - **Wide**: Wide Left, Wide Right
 */
enum class Channel : int32_t {
  // @aidl-doc
  /** Front Left */
  CH_FL = 0,
  // @aidl-doc
  /** Front Right */
  CH_FR = 1,
  // @aidl-doc
  /** Front Centre */
  CH_FC = 2,
  // @aidl-doc
  /** Subwoofer / Low-Frequency Effects */
  CH_LFE = 3,
  // @aidl-doc
  /** Side Left */
  CH_SL = 4,
  // @aidl-doc
  /** Side Right */
  CH_SR = 5,
  // @aidl-doc
  /** Rear Left */
  CH_RL = 6,
  // @aidl-doc
  /** Rear Right */
  CH_RR = 7,
  // @aidl-doc
  /** Rear Centre */
  CH_RC = 8,
  // @aidl-doc
  /** Top Front Left */
  CH_TFL = 9,
  // @aidl-doc
  /** Top Front Right */
  CH_TFR = 10,
  // @aidl-doc
  /** Top Front Centre */
  CH_TFC = 11,
  // @aidl-doc
  /** Top Side Left */
  CH_TSL = 12,
  // @aidl-doc
  /** Top Side Right */
  CH_TSR = 13,
  // @aidl-doc
  /** Top Rear Left */
  CH_TRL = 14,
  // @aidl-doc
  /** Top Rear Right */
  CH_TRR = 15,
  // @aidl-doc
  /** Wide Left */
  CH_WL = 16,
  // @aidl-doc
  /** Wide Right */
  CH_WR = 17,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(Channel val) {
  switch(val) {
  case Channel::CH_FL:
    return "CH_FL";
  case Channel::CH_FR:
    return "CH_FR";
  case Channel::CH_FC:
    return "CH_FC";
  case Channel::CH_LFE:
    return "CH_LFE";
  case Channel::CH_SL:
    return "CH_SL";
  case Channel::CH_SR:
    return "CH_SR";
  case Channel::CH_RL:
    return "CH_RL";
  case Channel::CH_RR:
    return "CH_RR";
  case Channel::CH_RC:
    return "CH_RC";
  case Channel::CH_TFL:
    return "CH_TFL";
  case Channel::CH_TFR:
    return "CH_TFR";
  case Channel::CH_TFC:
    return "CH_TFC";
  case Channel::CH_TSL:
    return "CH_TSL";
  case Channel::CH_TSR:
    return "CH_TSR";
  case Channel::CH_TRL:
    return "CH_TRL";
  case Channel::CH_TRR:
    return "CH_TRR";
  case Channel::CH_WL:
    return "CH_WL";
  case Channel::CH_WR:
    return "CH_WR";
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
constexpr inline std::array<::com::rdk::hal::audiomixer::Channel, 18> enum_values<::com::rdk::hal::audiomixer::Channel> = {
  ::com::rdk::hal::audiomixer::Channel::CH_FL,
  ::com::rdk::hal::audiomixer::Channel::CH_FR,
  ::com::rdk::hal::audiomixer::Channel::CH_FC,
  ::com::rdk::hal::audiomixer::Channel::CH_LFE,
  ::com::rdk::hal::audiomixer::Channel::CH_SL,
  ::com::rdk::hal::audiomixer::Channel::CH_SR,
  ::com::rdk::hal::audiomixer::Channel::CH_RL,
  ::com::rdk::hal::audiomixer::Channel::CH_RR,
  ::com::rdk::hal::audiomixer::Channel::CH_RC,
  ::com::rdk::hal::audiomixer::Channel::CH_TFL,
  ::com::rdk::hal::audiomixer::Channel::CH_TFR,
  ::com::rdk::hal::audiomixer::Channel::CH_TFC,
  ::com::rdk::hal::audiomixer::Channel::CH_TSL,
  ::com::rdk::hal::audiomixer::Channel::CH_TSR,
  ::com::rdk::hal::audiomixer::Channel::CH_TRL,
  ::com::rdk::hal::audiomixer::Channel::CH_TRR,
  ::com::rdk::hal::audiomixer::Channel::CH_WL,
  ::com::rdk::hal::audiomixer::Channel::CH_WR,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

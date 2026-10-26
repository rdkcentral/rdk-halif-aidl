#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
// @aidl-doc
/** @brief       Device types as defined in the HDMI specification 2-0 section 11.3.2 */
enum class DeviceType : int32_t {
  // @aidl-doc
  /** No device type */
  NONE = -1,
  // @aidl-doc
  /** Render the video from HDMI input on a screen */
  TV = 0,
  // @aidl-doc
  /**
   * Generic Source with recording functionality
   * that is expressed via CEC Feature "One Touch Record"
   */
  RECORDING_DEVICE = 1,
  // @aidl-doc
  /**
   * Generic Source with tuner functionality that is
   * expressed via CEC Feature "Tuner Control"
   */
  TUNER = 2,
  // @aidl-doc
  /** Generic Source which is not a recording device or a tuner. */
  PLAYBACK_DEVICE = 3,
  // @aidl-doc
  /**
   * Render the audio from HDMI input (or alternate audio input);
   * implements System Audio Control Feature
   */
  AUDIO_SYSTEM = 4,
  // @aidl-doc
  /**
   * A device according to H14b Section CEC 11.1 which has no other
   * functionality or device type.
   */
  CEC_SWITCH = 5,
  // @aidl-doc
  /**
   * A device that performs processing functions:
   * Cannot itself become an Active Source.
   * has an HDMI output and at least one input.
   * passes video from input to output modified or unmodified.
   * has its own physical address.
   * requires direct addressing.
   * has no other device types.
   */
  PROCESSOR = 6,
};
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
[[nodiscard]] static inline std::string toString(DeviceType val) {
  switch(val) {
  case DeviceType::NONE:
    return "NONE";
  case DeviceType::TV:
    return "TV";
  case DeviceType::RECORDING_DEVICE:
    return "RECORDING_DEVICE";
  case DeviceType::TUNER:
    return "TUNER";
  case DeviceType::PLAYBACK_DEVICE:
    return "PLAYBACK_DEVICE";
  case DeviceType::AUDIO_SYSTEM:
    return "AUDIO_SYSTEM";
  case DeviceType::CEC_SWITCH:
    return "CEC_SWITCH";
  case DeviceType::PROCESSOR:
    return "PROCESSOR";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::hdmicec::DeviceType, 8> enum_values<::com::rdk::hal::hdmicec::DeviceType> = {
  ::com::rdk::hal::hdmicec::DeviceType::NONE,
  ::com::rdk::hal::hdmicec::DeviceType::TV,
  ::com::rdk::hal::hdmicec::DeviceType::RECORDING_DEVICE,
  ::com::rdk::hal::hdmicec::DeviceType::TUNER,
  ::com::rdk::hal::hdmicec::DeviceType::PLAYBACK_DEVICE,
  ::com::rdk::hal::hdmicec::DeviceType::AUDIO_SYSTEM,
  ::com::rdk::hal::hdmicec::DeviceType::CEC_SWITCH,
  ::com::rdk::hal::hdmicec::DeviceType::PROCESSOR,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

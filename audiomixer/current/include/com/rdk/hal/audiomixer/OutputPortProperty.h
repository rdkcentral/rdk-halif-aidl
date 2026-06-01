#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
enum class OutputPortProperty : int32_t {
  VOLUME = 0,
  DELAY_MS = 1,
  MUTE = 2,
  ENABLED = 3,
  OUTPUT_FORMAT = 4,
  SUPPORTED_AUDIO_FORMATS = 5,
  DOLBY_ATMOS_SUPPORT = 6,
  STATE = 7,
  TRANSCODE_FORMAT = 8,
  CONNECTION_STATE = 9,
  AQ_PROCESSOR_ID = 10,
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
  case OutputPortProperty::TRANSCODE_FORMAT:
    return "TRANSCODE_FORMAT";
  case OutputPortProperty::CONNECTION_STATE:
    return "CONNECTION_STATE";
  case OutputPortProperty::AQ_PROCESSOR_ID:
    return "AQ_PROCESSOR_ID";
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
constexpr inline std::array<::com::rdk::hal::audiomixer::OutputPortProperty, 12> enum_values<::com::rdk::hal::audiomixer::OutputPortProperty> = {
  ::com::rdk::hal::audiomixer::OutputPortProperty::VOLUME,
  ::com::rdk::hal::audiomixer::OutputPortProperty::DELAY_MS,
  ::com::rdk::hal::audiomixer::OutputPortProperty::MUTE,
  ::com::rdk::hal::audiomixer::OutputPortProperty::ENABLED,
  ::com::rdk::hal::audiomixer::OutputPortProperty::OUTPUT_FORMAT,
  ::com::rdk::hal::audiomixer::OutputPortProperty::SUPPORTED_AUDIO_FORMATS,
  ::com::rdk::hal::audiomixer::OutputPortProperty::DOLBY_ATMOS_SUPPORT,
  ::com::rdk::hal::audiomixer::OutputPortProperty::STATE,
  ::com::rdk::hal::audiomixer::OutputPortProperty::TRANSCODE_FORMAT,
  ::com::rdk::hal::audiomixer::OutputPortProperty::CONNECTION_STATE,
  ::com::rdk::hal::audiomixer::OutputPortProperty::AQ_PROCESSOR_ID,
  ::com::rdk::hal::audiomixer::OutputPortProperty::VENDOR_EXTENSION,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
enum class AQParameter : int32_t {
  VOLUME_LEVELLER = 0,
  DIALOGUE_ENHANCER = 1,
  DIALOGUE_CLARITY = 2,
  AC4_DIALOGUE_ENHANCER = 3,
  BASS_ENHANCER_GAIN = 4,
  BASS_ENHANCER_WIDTH = 5,
  BASS_ENHANCER_CUTOFF = 6,
  SURROUND_DECODER = 7,
  SURROUND_VIRTUALIZER = 8,
  MI_STEERING = 9,
  GRAPHIC_EQUALIZER = 10,
  INTELLIGENT_EQUALIZER = 11,
  POST_GAIN = 12,
  VOLUME_MODELER = 13,
  AUDIO_OPTIMIZER = 14,
  ACTIVE_DOWNMIX = 15,
  CENTER_SPREADING = 16,
  DRC = 17,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(AQParameter val) {
  switch(val) {
  case AQParameter::VOLUME_LEVELLER:
    return "VOLUME_LEVELLER";
  case AQParameter::DIALOGUE_ENHANCER:
    return "DIALOGUE_ENHANCER";
  case AQParameter::DIALOGUE_CLARITY:
    return "DIALOGUE_CLARITY";
  case AQParameter::AC4_DIALOGUE_ENHANCER:
    return "AC4_DIALOGUE_ENHANCER";
  case AQParameter::BASS_ENHANCER_GAIN:
    return "BASS_ENHANCER_GAIN";
  case AQParameter::BASS_ENHANCER_WIDTH:
    return "BASS_ENHANCER_WIDTH";
  case AQParameter::BASS_ENHANCER_CUTOFF:
    return "BASS_ENHANCER_CUTOFF";
  case AQParameter::SURROUND_DECODER:
    return "SURROUND_DECODER";
  case AQParameter::SURROUND_VIRTUALIZER:
    return "SURROUND_VIRTUALIZER";
  case AQParameter::MI_STEERING:
    return "MI_STEERING";
  case AQParameter::GRAPHIC_EQUALIZER:
    return "GRAPHIC_EQUALIZER";
  case AQParameter::INTELLIGENT_EQUALIZER:
    return "INTELLIGENT_EQUALIZER";
  case AQParameter::POST_GAIN:
    return "POST_GAIN";
  case AQParameter::VOLUME_MODELER:
    return "VOLUME_MODELER";
  case AQParameter::AUDIO_OPTIMIZER:
    return "AUDIO_OPTIMIZER";
  case AQParameter::ACTIVE_DOWNMIX:
    return "ACTIVE_DOWNMIX";
  case AQParameter::CENTER_SPREADING:
    return "CENTER_SPREADING";
  case AQParameter::DRC:
    return "DRC";
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
constexpr inline std::array<::com::rdk::hal::audiomixer::AQParameter, 18> enum_values<::com::rdk::hal::audiomixer::AQParameter> = {
  ::com::rdk::hal::audiomixer::AQParameter::VOLUME_LEVELLER,
  ::com::rdk::hal::audiomixer::AQParameter::DIALOGUE_ENHANCER,
  ::com::rdk::hal::audiomixer::AQParameter::DIALOGUE_CLARITY,
  ::com::rdk::hal::audiomixer::AQParameter::AC4_DIALOGUE_ENHANCER,
  ::com::rdk::hal::audiomixer::AQParameter::BASS_ENHANCER_GAIN,
  ::com::rdk::hal::audiomixer::AQParameter::BASS_ENHANCER_WIDTH,
  ::com::rdk::hal::audiomixer::AQParameter::BASS_ENHANCER_CUTOFF,
  ::com::rdk::hal::audiomixer::AQParameter::SURROUND_DECODER,
  ::com::rdk::hal::audiomixer::AQParameter::SURROUND_VIRTUALIZER,
  ::com::rdk::hal::audiomixer::AQParameter::MI_STEERING,
  ::com::rdk::hal::audiomixer::AQParameter::GRAPHIC_EQUALIZER,
  ::com::rdk::hal::audiomixer::AQParameter::INTELLIGENT_EQUALIZER,
  ::com::rdk::hal::audiomixer::AQParameter::POST_GAIN,
  ::com::rdk::hal::audiomixer::AQParameter::VOLUME_MODELER,
  ::com::rdk::hal::audiomixer::AQParameter::AUDIO_OPTIMIZER,
  ::com::rdk::hal::audiomixer::AQParameter::ACTIVE_DOWNMIX,
  ::com::rdk::hal::audiomixer::AQParameter::CENTER_SPREADING,
  ::com::rdk::hal::audiomixer::AQParameter::DRC,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

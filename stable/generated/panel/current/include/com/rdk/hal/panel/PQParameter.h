#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
enum class PQParameter : int32_t {
  BRIGHTNESS = 0,
  CONTRAST = 1,
  SHARPNESS = 2,
  SATURATION = 3,
  HUE = 4,
  MANUAL_BACKLIGHT = 5,
  SDR_GAMMA = 6,
  COLOR_TEMPERATURE = 7,
  DIMMING_MODE = 8,
  DIMMING_LEVEL = 9,
  LOW_LATENCY_STATE = 10,
  SATURATION_RED = 11,
  SATURATION_BLUE = 12,
  SATURATION_GREEN = 13,
  SATURATION_YELLOW = 14,
  SATURATION_CYAN = 15,
  SATURATION_MAGENTA = 16,
  HUE_RED = 17,
  HUE_BLUE = 18,
  HUE_GREEN = 19,
  HUE_YELLOW = 20,
  HUE_CYAN = 21,
  HUE_MAGENTA = 22,
  LUMA_RED = 23,
  LUMA_BLUE = 24,
  LUMA_GREEN = 25,
  LUMA_YELLOW = 26,
  LUMA_CYAN = 27,
  LUMA_MAGENTA = 28,
  MEMC = 29,
  LOCAL_CONTRAST_LEVEL = 30,
  MPEG_NOISE_REDUCTION = 31,
  NOISE_REDUCTION = 32,
  AI_PQ_ENGINE = 33,
  AMBIENT_LIGHT_SENSOR_CONTROL = 34,
};
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace panel {
[[nodiscard]] static inline std::string toString(PQParameter val) {
  switch(val) {
  case PQParameter::BRIGHTNESS:
    return "BRIGHTNESS";
  case PQParameter::CONTRAST:
    return "CONTRAST";
  case PQParameter::SHARPNESS:
    return "SHARPNESS";
  case PQParameter::SATURATION:
    return "SATURATION";
  case PQParameter::HUE:
    return "HUE";
  case PQParameter::MANUAL_BACKLIGHT:
    return "MANUAL_BACKLIGHT";
  case PQParameter::SDR_GAMMA:
    return "SDR_GAMMA";
  case PQParameter::COLOR_TEMPERATURE:
    return "COLOR_TEMPERATURE";
  case PQParameter::DIMMING_MODE:
    return "DIMMING_MODE";
  case PQParameter::DIMMING_LEVEL:
    return "DIMMING_LEVEL";
  case PQParameter::LOW_LATENCY_STATE:
    return "LOW_LATENCY_STATE";
  case PQParameter::SATURATION_RED:
    return "SATURATION_RED";
  case PQParameter::SATURATION_BLUE:
    return "SATURATION_BLUE";
  case PQParameter::SATURATION_GREEN:
    return "SATURATION_GREEN";
  case PQParameter::SATURATION_YELLOW:
    return "SATURATION_YELLOW";
  case PQParameter::SATURATION_CYAN:
    return "SATURATION_CYAN";
  case PQParameter::SATURATION_MAGENTA:
    return "SATURATION_MAGENTA";
  case PQParameter::HUE_RED:
    return "HUE_RED";
  case PQParameter::HUE_BLUE:
    return "HUE_BLUE";
  case PQParameter::HUE_GREEN:
    return "HUE_GREEN";
  case PQParameter::HUE_YELLOW:
    return "HUE_YELLOW";
  case PQParameter::HUE_CYAN:
    return "HUE_CYAN";
  case PQParameter::HUE_MAGENTA:
    return "HUE_MAGENTA";
  case PQParameter::LUMA_RED:
    return "LUMA_RED";
  case PQParameter::LUMA_BLUE:
    return "LUMA_BLUE";
  case PQParameter::LUMA_GREEN:
    return "LUMA_GREEN";
  case PQParameter::LUMA_YELLOW:
    return "LUMA_YELLOW";
  case PQParameter::LUMA_CYAN:
    return "LUMA_CYAN";
  case PQParameter::LUMA_MAGENTA:
    return "LUMA_MAGENTA";
  case PQParameter::MEMC:
    return "MEMC";
  case PQParameter::LOCAL_CONTRAST_LEVEL:
    return "LOCAL_CONTRAST_LEVEL";
  case PQParameter::MPEG_NOISE_REDUCTION:
    return "MPEG_NOISE_REDUCTION";
  case PQParameter::NOISE_REDUCTION:
    return "NOISE_REDUCTION";
  case PQParameter::AI_PQ_ENGINE:
    return "AI_PQ_ENGINE";
  case PQParameter::AMBIENT_LIGHT_SENSOR_CONTROL:
    return "AMBIENT_LIGHT_SENSOR_CONTROL";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::panel::PQParameter, 35> enum_values<::com::rdk::hal::panel::PQParameter> = {
  ::com::rdk::hal::panel::PQParameter::BRIGHTNESS,
  ::com::rdk::hal::panel::PQParameter::CONTRAST,
  ::com::rdk::hal::panel::PQParameter::SHARPNESS,
  ::com::rdk::hal::panel::PQParameter::SATURATION,
  ::com::rdk::hal::panel::PQParameter::HUE,
  ::com::rdk::hal::panel::PQParameter::MANUAL_BACKLIGHT,
  ::com::rdk::hal::panel::PQParameter::SDR_GAMMA,
  ::com::rdk::hal::panel::PQParameter::COLOR_TEMPERATURE,
  ::com::rdk::hal::panel::PQParameter::DIMMING_MODE,
  ::com::rdk::hal::panel::PQParameter::DIMMING_LEVEL,
  ::com::rdk::hal::panel::PQParameter::LOW_LATENCY_STATE,
  ::com::rdk::hal::panel::PQParameter::SATURATION_RED,
  ::com::rdk::hal::panel::PQParameter::SATURATION_BLUE,
  ::com::rdk::hal::panel::PQParameter::SATURATION_GREEN,
  ::com::rdk::hal::panel::PQParameter::SATURATION_YELLOW,
  ::com::rdk::hal::panel::PQParameter::SATURATION_CYAN,
  ::com::rdk::hal::panel::PQParameter::SATURATION_MAGENTA,
  ::com::rdk::hal::panel::PQParameter::HUE_RED,
  ::com::rdk::hal::panel::PQParameter::HUE_BLUE,
  ::com::rdk::hal::panel::PQParameter::HUE_GREEN,
  ::com::rdk::hal::panel::PQParameter::HUE_YELLOW,
  ::com::rdk::hal::panel::PQParameter::HUE_CYAN,
  ::com::rdk::hal::panel::PQParameter::HUE_MAGENTA,
  ::com::rdk::hal::panel::PQParameter::LUMA_RED,
  ::com::rdk::hal::panel::PQParameter::LUMA_BLUE,
  ::com::rdk::hal::panel::PQParameter::LUMA_GREEN,
  ::com::rdk::hal::panel::PQParameter::LUMA_YELLOW,
  ::com::rdk::hal::panel::PQParameter::LUMA_CYAN,
  ::com::rdk::hal::panel::PQParameter::LUMA_MAGENTA,
  ::com::rdk::hal::panel::PQParameter::MEMC,
  ::com::rdk::hal::panel::PQParameter::LOCAL_CONTRAST_LEVEL,
  ::com::rdk::hal::panel::PQParameter::MPEG_NOISE_REDUCTION,
  ::com::rdk::hal::panel::PQParameter::NOISE_REDUCTION,
  ::com::rdk::hal::panel::PQParameter::AI_PQ_ENGINE,
  ::com::rdk::hal::panel::PQParameter::AMBIENT_LIGHT_SENSOR_CONTROL,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

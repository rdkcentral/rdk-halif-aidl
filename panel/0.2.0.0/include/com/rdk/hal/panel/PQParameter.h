#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
// @aidl-doc
/**
 *  @brief     PQ Parameter enumeration.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 */
enum class PQParameter : int32_t {
  // @aidl-doc
  /** Brightness control for video pixels. Integer value. */
  BRIGHTNESS = 0,
  // @aidl-doc
  /** Contrast control for the video plane. Integer value. */
  CONTRAST = 1,
  // @aidl-doc
  /** Sharpness control for the video plane. Integer value. */
  SHARPNESS = 2,
  // @aidl-doc
  /** Saturation control for the video plane. Integer value. */
  SATURATION = 3,
  // @aidl-doc
  /** Hue control for the video plane. Integer value. */
  HUE = 4,
  // @aidl-doc
  /**
   * Manual backlight control. Integer value.
   * Setting will fail if ALS control is enabled.
   */
  MANUAL_BACKLIGHT = 5,
  // @aidl-doc
  /**
   * SDR gamma control. Enum value represented as SDRGamma.
   * Use getPQParameters() / setPQParameters() with the sdrGamma
   * variant of PQParameterValue for this parameter.
   */
  SDR_GAMMA = 6,
  // @aidl-doc
  /**
   * Colour temperature preset. String value.
   * Use getPQParameters() / setPQParameters() with the stringValue
   * variant of PQParameterValue for this parameter.
   */
  COLOR_TEMPERATURE = 7,
  // @aidl-doc
  /**
   * Dimming settings. Parcelled as DimmingSettings.
   * Use getPQParameters() / setPQParameters() with the dimmingSettings
   * variant of PQParameterValue for this parameter.
   */
  DIMMING_SETTINGS = 8,
  // @aidl-doc
  /** Low-latency mode enable state. Integer value, typically 0 or 1. */
  LOW_LATENCY_STATE = 9,
  // @aidl-doc
  /** Motion estimation / motion compensation control. Integer value. */
  MEMC = 10,
  // @aidl-doc
  /** Local contrast level. Integer value. */
  LOCAL_CONTRAST_LEVEL = 11,
  // @aidl-doc
  /** MPEG noise reduction. Integer value. */
  MPEG_NOISE_REDUCTION = 12,
  // @aidl-doc
  /** Noise reduction. Integer value. */
  NOISE_REDUCTION = 13,
  // @aidl-doc
  /** AI picture quality management engine. Boolean-like integer value, typically 0 or 1. */
  AI_PQ_ENGINE = 14,
  // @aidl-doc
  /** Ambient light sensor (ALS) control. Boolean-like integer value, typically 0 or 1. */
  AMBIENT_LIGHT_SENSOR_CONTROL = 15,
  // @aidl-doc
  /** Precision detail enhancement level. Integer value. */
  PRECISION_DETAIL = 16,
  // @aidl-doc
  /**
   * Dolby Vision calibration settings. Parcelled as DolbyVisionCalibrationSettings.
   * Use getPQParameters() / setPQParameters() with the dvCalibrationSettings
   * variant of PQParameterValue for this parameter.
   */
  DV_CALIBRATION = 17,
  // @aidl-doc
  /**
   * 2-point white balance calibration settings. Parcelled as TwoPointWB.
   * Use getPQParameters() / setPQParameters() with the twoPointWBSettings
   * variant of PQParameterValue for this parameter.
   */
  TWO_POINT_WB = 18,
  // @aidl-doc
  /**
   * Multi-point white balance calibration settings. Parcelled as WhiteBalanceMultiPointSettings.
   * Use getPQParameters() / setPQParameters() with the multiPointWBSettings
   * variant of PQParameterValue for this parameter.
   */
  MULTI_POINT_WB = 19,
  // @aidl-doc
  /**
   * Dynamic contrast. Integer value.
   * A platform offering only on/off declares a maximum of 1.
   */
  DYNAMIC_CONTRAST_LEVEL = 20,
  // @aidl-doc
  /** AI super resolution (AISR). Integer value. */
  AISR = 21,
  // @aidl-doc
  /**
   * Grouped colour-management settings. Parcelled as ColourManagementSettings.
   * Use getPQParameters() / setPQParameters() with the colourManagementSettings
   * variant of PQParameterValue for this parameter.
   */
  COLOUR_MANAGEMENT_SETTINGS = 22,
  // @aidl-doc
  /**
   * Tone mapping settings. Parcelled as ToneMappingSettings.
   * Use getPQParameters() / setPQParameters() with the toneMappingSettings
   * variant of PQParameterValue for this parameter.
   */
  TONE_MAPPING_SETTINGS = 23,
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
  case PQParameter::DIMMING_SETTINGS:
    return "DIMMING_SETTINGS";
  case PQParameter::LOW_LATENCY_STATE:
    return "LOW_LATENCY_STATE";
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
  case PQParameter::PRECISION_DETAIL:
    return "PRECISION_DETAIL";
  case PQParameter::DV_CALIBRATION:
    return "DV_CALIBRATION";
  case PQParameter::TWO_POINT_WB:
    return "TWO_POINT_WB";
  case PQParameter::MULTI_POINT_WB:
    return "MULTI_POINT_WB";
  case PQParameter::DYNAMIC_CONTRAST_LEVEL:
    return "DYNAMIC_CONTRAST_LEVEL";
  case PQParameter::AISR:
    return "AISR";
  case PQParameter::COLOUR_MANAGEMENT_SETTINGS:
    return "COLOUR_MANAGEMENT_SETTINGS";
  case PQParameter::TONE_MAPPING_SETTINGS:
    return "TONE_MAPPING_SETTINGS";
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
constexpr inline std::array<::com::rdk::hal::panel::PQParameter, 24> enum_values<::com::rdk::hal::panel::PQParameter> = {
  ::com::rdk::hal::panel::PQParameter::BRIGHTNESS,
  ::com::rdk::hal::panel::PQParameter::CONTRAST,
  ::com::rdk::hal::panel::PQParameter::SHARPNESS,
  ::com::rdk::hal::panel::PQParameter::SATURATION,
  ::com::rdk::hal::panel::PQParameter::HUE,
  ::com::rdk::hal::panel::PQParameter::MANUAL_BACKLIGHT,
  ::com::rdk::hal::panel::PQParameter::SDR_GAMMA,
  ::com::rdk::hal::panel::PQParameter::COLOR_TEMPERATURE,
  ::com::rdk::hal::panel::PQParameter::DIMMING_SETTINGS,
  ::com::rdk::hal::panel::PQParameter::LOW_LATENCY_STATE,
  ::com::rdk::hal::panel::PQParameter::MEMC,
  ::com::rdk::hal::panel::PQParameter::LOCAL_CONTRAST_LEVEL,
  ::com::rdk::hal::panel::PQParameter::MPEG_NOISE_REDUCTION,
  ::com::rdk::hal::panel::PQParameter::NOISE_REDUCTION,
  ::com::rdk::hal::panel::PQParameter::AI_PQ_ENGINE,
  ::com::rdk::hal::panel::PQParameter::AMBIENT_LIGHT_SENSOR_CONTROL,
  ::com::rdk::hal::panel::PQParameter::PRECISION_DETAIL,
  ::com::rdk::hal::panel::PQParameter::DV_CALIBRATION,
  ::com::rdk::hal::panel::PQParameter::TWO_POINT_WB,
  ::com::rdk::hal::panel::PQParameter::MULTI_POINT_WB,
  ::com::rdk::hal::panel::PQParameter::DYNAMIC_CONTRAST_LEVEL,
  ::com::rdk::hal::panel::PQParameter::AISR,
  ::com::rdk::hal::panel::PQParameter::COLOUR_MANAGEMENT_SETTINGS,
  ::com::rdk::hal::panel::PQParameter::TONE_MAPPING_SETTINGS,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android

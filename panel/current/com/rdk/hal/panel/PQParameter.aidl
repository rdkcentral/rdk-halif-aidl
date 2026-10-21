/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.panel;

/**
 *  @brief     PQ Parameter enumeration.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 */

@VintfStability
@Backing(type = "int")
enum PQParameter {
    /** Brightness control for video pixels. Integer value. */
    BRIGHTNESS = 0,

    /** Contrast control for the video plane. Integer value. */
    CONTRAST = 1,

    /** Sharpness control for the video plane. Integer value. */
    SHARPNESS = 2,

    /** Saturation control for the video plane. Integer value. */
    SATURATION = 3,

    /** Hue control for the video plane. Integer value. */
    HUE = 4,

    /**
     * Manual backlight control. Integer value.
     * Setting will fail if ALS control is enabled.
     */
    MANUAL_BACKLIGHT = 5,

    /**
     * SDR gamma control. Enum value represented as SDRGamma.
     * Use getPQParameters() / setPQParameters() with the sdrGamma
     * variant of PQParameterValue for this parameter.
     */
    SDR_GAMMA = 6,

    /**
     * Colour temperature preset. String value.
     * Use getPQParameters() / setPQParameters() with the stringValue
     * variant of PQParameterValue for this parameter.
     */
    COLOR_TEMPERATURE = 7,

    /**
     * Dimming settings. Parcelled as DimmingSettings.
     * Use getPQParameters() / setPQParameters() with the dimmingSettings
     * variant of PQParameterValue for this parameter.
     */
    DIMMING_SETTINGS = 8,

    /** Low-latency mode enable state. Integer value, typically 0 or 1. */
    LOW_LATENCY_STATE = 9,

    /** Motion estimation / motion compensation control. Integer value. */
    MEMC = 10,

    /** Local contrast level. Integer value. */
    LOCAL_CONTRAST_LEVEL = 11,

    /**
     * MPEG noise reduction. Integer value.
     */
    MPEG_NOISE_REDUCTION = 12,

    /**
     * Noise reduction. Integer value.
     */
    NOISE_REDUCTION = 13,

    /**
     * AI picture quality management engine. Boolean-like integer value, typically 0 or 1.
     */
    AI_PQ_ENGINE = 14,

    /**
     * Ambient light sensor (ALS) control. Boolean-like integer value, typically 0 or 1.
     */
    AMBIENT_LIGHT_SENSOR_CONTROL = 15,

    /**
     * Precision detail enhancement level. Integer value.
     */
    PRECISION_DETAIL = 16,

    /**
     * Dolby Vision calibration settings. Parcelled as DolbyVisionCalibrationSettings.
     * Use getPQParameters() / setPQParameters() with the dvCalibrationSettings
     * variant of PQParameterValue for this parameter.
     */
    DV_CALIBRATION = 17,

    /**
     * 2-point white balance calibration settings. Parcelled as TwoPointWB.
     * Use getPQParameters() / setPQParameters() with the twoPointWBSettings
     * variant of PQParameterValue for this parameter.
     */
    TWO_POINT_WB = 18,

    /**
     * Multi-point white balance calibration settings. Parcelled as WhiteBalanceMultiPointSettings.
     * Use getPQParameters() / setPQParameters() with the multiPointWBSettings
     * variant of PQParameterValue for this parameter.
     */
    MULTI_POINT_WB = 19,

    /**
     * Dynamic contrast. Integer value.
     * A platform offering only on/off declares a maximum of 1.
     */
    DYNAMIC_CONTRAST_LEVEL = 20,

    /**
     * AI super resolution (AISR). Integer value.
     */
    AISR = 21,

    /**
     * Grouped colour-management settings. Parcelled as ColourManagementSettings.
     * Use getPQParameters() / setPQParameters() with the colourManagementSettings
     * variant of PQParameterValue for this parameter.
     */
    COLOUR_MANAGEMENT_SETTINGS = 22,

    /**
     * Tone mapping settings. Parcelled as ToneMappingSettings.
     * Use getPQParameters() / setPQParameters() with the toneMappingSettings
     * variant of PQParameterValue for this parameter.
     */
    TONE_MAPPING_SETTINGS = 23,
}

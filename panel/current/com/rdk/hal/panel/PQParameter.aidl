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
 *  @brief     PQ parameter canonical name vocabulary.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 *
 *  PQ parameters are identified by string keys, mirroring the open string set
 *  already used for picture modes.  The constants below define the canonical
 *  vocabulary for standard parameters.  A platform declares which parameters it
 *  supports — and their ranges and applicable contexts — via
 *  `Capabilities.pqParameters`; clients must rely on that declaration rather
 *  than assuming any parameter from this vocabulary is present.
 *
 *  Vendor-specific parameters use the namespace prefix `vendor.<vendorname>.`
 *  e.g. "vendor.acme.super_resolution".  Names outside the `vendor.` namespace
 *  must match a constant defined here; the Vendor Test Suite validates this.
 *  Vendor parameters are discovered and rendered generically by clients from
 *  their `PQParameterCapability` (range, discrete values, contexts).
 */
@VintfStability
parcelable PQParameter
{
    /** Brightness (video pixels). */
    const @utf8InCpp String BRIGHTNESS = "BRIGHTNESS";

    /** Contrast (video plane). */
    const @utf8InCpp String CONTRAST = "CONTRAST";

    /** Sharpness (video plane). */
    const @utf8InCpp String SHARPNESS = "SHARPNESS";

    /** Saturation (video plane). */
    const @utf8InCpp String SATURATION = "SATURATION";

    /** Hue (video plane). */
    const @utf8InCpp String HUE = "HUE";

    /**
     * Backlight (fixed/global) (not the ALS value).
     * Setting will fail if ALS is enabled.
     */
    const @utf8InCpp String MANUAL_BACKLIGHT = "MANUAL_BACKLIGHT";

    /** SDR gamma.  Valid gamma values are defined in enum SDRGamma. */
    const @utf8InCpp String SDR_GAMMA = "SDR_GAMMA";

    /**
     * Colour temperature preset index 0..n.
     * Each index corresponds to an entry in `Capabilities.colorTemperatureNames`.
     */
    const @utf8InCpp String COLOR_TEMPERATURE = "COLOR_TEMPERATURE";

    /** Dimming mode. 0=Fixed 1=Global 2=Local */
    const @utf8InCpp String DIMMING_MODE = "DIMMING_MODE";

    /** Local dimming level. 0..n presets defined by vendor (for global or local dimming). */
    const @utf8InCpp String DIMMING_LEVEL = "DIMMING_LEVEL";

    /** Low latency state. Boolean. */
    const @utf8InCpp String LOW_LATENCY_STATE = "LOW_LATENCY_STATE";

    /** Component saturation red. */
    const @utf8InCpp String SATURATION_RED = "SATURATION_RED";

    /** Component saturation blue. */
    const @utf8InCpp String SATURATION_BLUE = "SATURATION_BLUE";

    /** Component saturation green. */
    const @utf8InCpp String SATURATION_GREEN = "SATURATION_GREEN";

    /** Component saturation yellow. */
    const @utf8InCpp String SATURATION_YELLOW = "SATURATION_YELLOW";

    /** Component saturation cyan. */
    const @utf8InCpp String SATURATION_CYAN = "SATURATION_CYAN";

    /** Component saturation magenta. */
    const @utf8InCpp String SATURATION_MAGENTA = "SATURATION_MAGENTA";

    /** Component hue red. */
    const @utf8InCpp String HUE_RED = "HUE_RED";

    /** Component hue blue. */
    const @utf8InCpp String HUE_BLUE = "HUE_BLUE";

    /** Component hue green. */
    const @utf8InCpp String HUE_GREEN = "HUE_GREEN";

    /** Component hue yellow. */
    const @utf8InCpp String HUE_YELLOW = "HUE_YELLOW";

    /** Component hue cyan. */
    const @utf8InCpp String HUE_CYAN = "HUE_CYAN";

    /** Component hue magenta. */
    const @utf8InCpp String HUE_MAGENTA = "HUE_MAGENTA";

    /** Component luma red. */
    const @utf8InCpp String LUMA_RED = "LUMA_RED";

    /** Component luma blue. */
    const @utf8InCpp String LUMA_BLUE = "LUMA_BLUE";

    /** Component luma green. */
    const @utf8InCpp String LUMA_GREEN = "LUMA_GREEN";

    /** Component luma yellow. */
    const @utf8InCpp String LUMA_YELLOW = "LUMA_YELLOW";

    /** Component luma cyan. */
    const @utf8InCpp String LUMA_CYAN = "LUMA_CYAN";

    /** Component luma magenta. */
    const @utf8InCpp String LUMA_MAGENTA = "LUMA_MAGENTA";

    /** Motion estimation / motion compensation (MEMC). Integer 0..n (0=off, n=maximum level). */
    const @utf8InCpp String MEMC = "MEMC";

    /** Local contrast. Integer 0..n (0=off, n=maximum level). */
    const @utf8InCpp String LOCAL_CONTRAST_LEVEL = "LOCAL_CONTRAST_LEVEL";

    /** MPEG noise reduction. Integer 0..n (0=off, n=maximum level). */
    const @utf8InCpp String MPEG_NOISE_REDUCTION = "MPEG_NOISE_REDUCTION";

    /** Noise reduction. Integer 0..n (0=off, n=maximum level). */
    const @utf8InCpp String NOISE_REDUCTION = "NOISE_REDUCTION";

    /** AI picture quality management engine. Boolean. */
    const @utf8InCpp String AI_PQ_ENGINE = "AI_PQ_ENGINE";

    /** Ambient light sensor (ALS) control. Boolean. */
    const @utf8InCpp String AMBIENT_LIGHT_SENSOR_CONTROL = "AMBIENT_LIGHT_SENSOR_CONTROL";
}

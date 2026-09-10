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
package com.rdk.hal.videodecoder;

/**
 *  @brief     Mastering display colour volume metadata (SMPTE ST 2086).
 *
 *  Field layout and scaling factors match HEVC SEI message type 137
 *  (mastering_display_colour_volume) and CTA-861.3 Static Metadata
 *  Descriptor Type 1, ensuring direct compatibility with both standards.
 *
 *  @author    Gerald Weatherup
 */

@VintfStability
parcelable MasteringDisplayInfo {

    /**
     * CIE 1931 chromaticity coordinate for the green display primary, x-axis.
     * Scaled by 50000. Range: 0-50000.
     * e.g. BT.2020 green x = 0.17 -> 8500
     */
    int greenPrimaryX;

    /**
     * CIE 1931 chromaticity coordinate for the green display primary, y-axis.
     * Scaled by 50000. Range: 0-50000.
     */
    int greenPrimaryY;

    /**
     * CIE 1931 chromaticity coordinate for the blue display primary, x-axis.
     * Scaled by 50000. Range: 0-50000.
     */
    int bluePrimaryX;

    /**
     * CIE 1931 chromaticity coordinate for the blue display primary, y-axis.
     * Scaled by 50000. Range: 0-50000.
     */
    int bluePrimaryY;

    /**
     * CIE 1931 chromaticity coordinate for the red display primary, x-axis.
     * Scaled by 50000. Range: 0-50000.
     */
    int redPrimaryX;

    /**
     * CIE 1931 chromaticity coordinate for the red display primary, y-axis.
     * Scaled by 50000. Range: 0-50000.
     */
    int redPrimaryY;

    /**
     * CIE 1931 chromaticity coordinate for the white point, x-axis.
     * Scaled by 50000. Range: 0-50000.
     * e.g. D65 white point x = 0.3127 -> 15635
     */
    int whitePointX;

    /**
     * CIE 1931 chromaticity coordinate for the white point, y-axis.
     * Scaled by 50000. Range: 0-50000.
     * e.g. D65 white point y = 0.3290 -> 16450
     */
    int whitePointY;

    /**
     * Maximum display mastering luminance in units of 0.0001 cd/m^2.
     * Range: 1-10,000,000 (0.0001-1000 cd/m^2).
     * e.g. 1000 nits peak -> 10,000,000
     * @see HEVC SEI type 137, max_display_mastering_luminance
     */
    int maxLuminance;

    /**
     * Minimum display mastering luminance in units of 0.0001 cd/m^2.
     * Range: 0-50,000 (0-5 cd/m^2).
     * e.g. 0.05 nits black level -> 500
     * @see HEVC SEI type 137, min_display_mastering_luminance
     */
    int minLuminance;
}

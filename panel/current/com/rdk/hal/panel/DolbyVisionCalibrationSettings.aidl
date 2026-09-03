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
 *  @brief     Dolby Vision calibration settings.
 *             Holds the calibration parameters for Dolby Vision including peak and minimum
 *             luminance (Tmax, Tmin), gamma correction (Tgamma), and the CIE 1931 xy
 *             chromaticity coordinates for Red, Green, Blue and White primaries.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 */

@VintfStability
parcelable DolbyVisionCalibrationSettings
{
    /**
     * Peak luminance in nits.
     * Valid range is 0 to 10000.
     */
    double Tmax;

    /**
     * Minimum luminance in nits.
     * Valid range is 0 to 10000.
     */
    double Tmin;

    /**
     * Gamma correction value.
     * Valid range is 1.80 to 2.60.
     */
    double Tgamma;

    /**
     * CIE 1931 xy chromaticity x-coordinate of the Red primary.
     * Valid range is 0.0 to 1.0.
     */
    double Rx;

    /**
     * CIE 1931 xy chromaticity y-coordinate of the Red primary.
     * Valid range is 0.0 to 1.0.
     */
    double Ry;

    /**
     * CIE 1931 xy chromaticity x-coordinate of the Green primary.
     * Valid range is 0.0 to 1.0.
     */
    double Gx;

    /**
     * CIE 1931 xy chromaticity y-coordinate of the Green primary.
     * Valid range is 0.0 to 1.0.
     */
    double Gy;

    /**
     * CIE 1931 xy chromaticity x-coordinate of the Blue primary.
     * Valid range is 0.0 to 1.0.
     */
    double Bx;

    /**
     * CIE 1931 xy chromaticity y-coordinate of the Blue primary.
     * Valid range is 0.0 to 1.0.
     */
    double By;

    /**
     * CIE 1931 xy chromaticity x-coordinate of the White point.
     * Valid range is 0.0 to 1.0.
     */
    double Wx;

    /**
     * CIE 1931 xy chromaticity y-coordinate of the White point.
     * Valid range is 0.0 to 1.0.
     */
    double Wy;
}

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
import com.rdk.hal.panel.PQParameter;
import com.rdk.hal.panel.DolbyVisionCalibrationSettings;
import com.rdk.hal.panel.TwoPointWBSettings;
import com.rdk.hal.videodecoder.DynamicRange;
import com.rdk.hal.AVSource;

/** 
 *  @brief     Panel PQ parameter capabilities.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 */
 
@VintfStability
parcelable PQParameterCapabilities
{
    /**
     * The PQ parameter being referenced in the PQCapabilities.
     */
    PQParameter pqParameter;

	/** 
     * Whether this PQ parameter is supported on the platform.
     * If unsupported (false) all other values below should be ignored.
     */
    boolean isSupported;

	/** 
     * Whether this PQ parameter globally affects the composite image, including
     * the graphics plane and all video planes, or is limited to video.
     * e.g. PQParameter.MANUAL_BACKLIGHT will be global if it represents an LED backlight
     *      but PQParameter.SHARPNESS may only operate on video.
     */
    boolean isGlobal;

    /**
     * Scalar integer minimum/maximum bounds used by all PQ parameters except DV_CALIBRATION.
     */
    parcelable IntBounds {
        /** The minimum value for this PQ parameter. */
        int minValue;
        /** The maximum value for this PQ parameter. */
        int maxValue;
    }

    /**
     * Dolby Vision calibration bounds used when pqParameter == PQParameter.DV_CALIBRATION.
     * minBound and maxBound contain the per-field minimum and maximum calibration values.
     */
    parcelable DvCalibrationBounds {
        /** Per-field minimum calibration values. */
        DolbyVisionCalibrationSettings minBound;
        /** Per-field maximum calibration values. */
        DolbyVisionCalibrationSettings maxBound;
    }

    /**
     * 2-point white balance bounds used when pqParameter == PQParameter.TWO_POINT_WB.
     * minBound and maxBound contain the per-field minimum and maximum WB values.
     */
    parcelable TwoPointWBBounds {
        /** Per-field minimum 2-point WB values. */
        TwoPointWBSettings.TwoPointWB minBound;
        /** Per-field maximum 2-point WB values. */
        TwoPointWBSettings.TwoPointWB maxBound;
    }

    /**
     * Union of scalar integer range bounds, Dolby Vision calibration bounds, or
     * 2-point white balance bounds.
     * For all PQ parameters except DV_CALIBRATION and TWO_POINT_WB, use `intBounds`.
     * For PQParameter.DV_CALIBRATION, use `dvCalibrationBounds`.
     * For PQParameter.TWO_POINT_WB, use `twoPointWBBounds`.
     */
    union RangeBound {
        IntBounds intBounds;
        DvCalibrationBounds dvCalibrationBounds;
        TwoPointWBBounds twoPointWBBounds;
    }
    RangeBound rangeBound;

    /**
     * Union of a list of supported integer values or a list of supported Dolby Vision
        * calibration settings values.
        * For all PQ parameters except DV_CALIBRATION and TWO_POINT_WB,
        * use the `intValues` variant.
     * For PQParameter.DV_CALIBRATION, use the `dvCalibrationValues` variant.
        * For PQParameter.TWO_POINT_WB, use the `twoPointWBValues` variant.
     * This only needs to be populated if not all values between min and max are supported.
     */
    union SupportedValues {
        /**
         * Specific integer values between minValue and maxValue that are supported.
         * Empty array means all integer values in [minValue, maxValue] are valid.
         */
        int[] intValues;

        /**
         * Specific DolbyVisionCalibrationSettings presets that are supported.
         * Empty array means any value within the DvCalibrationBounds range is valid.
         */
        DolbyVisionCalibrationSettings[] dvCalibrationValues;

        /**
         * Specific TwoPointWB presets that are supported.
         * Empty array means any value within the TwoPointWBBounds range is valid.
         */
        TwoPointWBSettings.TwoPointWB[] twoPointWBValues;
    }
    SupportedValues supportedValues;

    /**
     * Nested PQ parameter picture mode capabilities definition.
     */
    parcelable PQParamPictureModeCapabilities
    {
        /**
         * The name of the picture mode.
         */
        String pictureMode;

        /**
         * Nested PQ parameter video format capabilities definition.
         */
        parcelable PQParamVideoFormatCapabilities
        {
            /**
             * The video format dynamic range.
             */
            DynamicRange drFormat;

            /**
             * The array of AV sources supported by this PQ parameter for the video format and picture mode.
             */
            AVSource[] supportedAVSources;
        }

        /**
         * Array of PQ parameter video format capabilities, for this picture mode.
         */
        PQParamVideoFormatCapabilities[] pqParamVideoFormatCapabilities;
    }

    /**
     * Array of PQ parameter capabilties for picture modes.
     */
    PQParamPictureModeCapabilities[] pqParamPictureModeCapabilities;
}

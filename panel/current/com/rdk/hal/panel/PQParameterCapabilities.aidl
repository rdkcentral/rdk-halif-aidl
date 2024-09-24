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
     * The minimum and maximum values for this PQ parameter.
     */
    int minValue;
    int maxValue;

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

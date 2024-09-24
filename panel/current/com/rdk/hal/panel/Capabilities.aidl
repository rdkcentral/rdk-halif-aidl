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
import com.rdk.hal.panel.PanelType;
import com.rdk.hal.videodecoder.DynamicRange;
import com.rdk.hal.AVSource;
 
/** 
 *  @brief     Panel capabilities definition.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 */

@VintfStability
parcelable Capabilities
{
    /**
     * The panel type.
     */
    PanelType panelType;

    /**
     * Whether frame rate matching is supported by the device.
     */
    boolean frameRateMatchingSupported;

    /**
     * Whether display fade control is supported by the device.
     */
    boolean fadeDisplaySupported;

    /**
     * The list of supported PQParameters.
     */
    PQParameter[] supportedPQParameters;

    /**
     * Panel display refresh rates supported in Hz, used in frame rate matching.
     */
    double[] supportedRefreshRatesHz;

    /*
     * Defines the video format and AV source capabilities for a picture mode.
     */
    parcelable PictureModeCapabilities
    {
        /**
         * The picture mode.
         */
        String pictureMode;

        /**
         * Defines a video format capability for a picture mode.
         */
        parcelable VideoFormatCapabilities
        {
            /**
             * The dynamic range video format.
             */
            DynamicRange videoFormat;

            /**
             * Lists the AV sources supported by this picture mode and video format.
             */
            AVSource[] supportedAVSources;
        }

        /**
         * Lists the video format capabilities for a picture mode.
         */
        VideoFormatCapabilities[] videoFormatCapabilities;
    }

    /**
     * Array of picture modes and their capabilities, listing the video formats and AV sources supported.
     */
    PictureModeCapabilities[] pictureModeCapabilities;

    /**
     * Array of color temperature names.
     * e.g. { "Cool", "Normal", "Warm" }.
     * Each index of the String[] corresponds to the index of a color temperature preset
     * used in `PQParameter.COLOR_TEMPERATURE` and functions such as `set2PointWhiteBalance()`.
     */
    String[] colorTemperatureNames;
}

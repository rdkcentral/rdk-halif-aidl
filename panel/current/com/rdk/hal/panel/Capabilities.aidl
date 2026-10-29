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
import com.rdk.hal.panel.DynamicRange;
import com.rdk.hal.panel.PQParameter;
import com.rdk.hal.panel.PanelSource;

/**
 *  @brief     Panel capabilities definition.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 */

@VintfStability
parcelable Capabilities {
    /**
     * The panel type.
     */
    @utf8InCpp String panelType;

    /** Panel width in pixels. */
    int pixelWidth;

    /** Panel height in pixels. */
    int pixelHeight;

    /** Panel width in centimetres. */
    int widthCm;

    /** Panel height in centimetres. */
    int heightCm;

    /**
     * Whether frame rate matching is supported by the device.
     */
    boolean frameRateMatchingSupported;

    /**
     * The list of supported PQParameters.
     */
    PQParameter[] supportedPQParameters;

    /**
     * Panel display refresh rates supported in Hz, used in frame rate matching.
     */
    double[] supportedRefreshRatesHz;

    /**
     * Array of supported colour temperature presets.
     *
     * These strings are used directly by `PQParameter.COLOR_TEMPERATURE`
     * and by colour-temperature-scoped white balance operations.
     */
    @utf8InCpp String[] supportedColourTemperatures;

    /**
     * All AV sources supported by the panel.
     */
    PanelSource[] supportedAVSources;

    /**
     * All dynamic ranges supported by the panel.
     */
    DynamicRange[] supportedDynamicRanges;

    /**
     * Defines the dynamic range and AV source capabilities for a picture mode.
     */
    parcelable PictureModeCapabilities {
        /**
         * The picture mode.
         */
        @utf8InCpp String pictureMode;

        /**
         * Defines the list of dynamic ranges, and the list of AV sources for each
         * dynamic range, that can be associated with a given picture mode.
         */
        parcelable DynamicRangeCapabilities {
            /**
             * The dynamic range that can be associated for the picture mode.
             */
            DynamicRange dynamicRange;

            /**
             * Defines list of AV sources that can be associated for a given
             * picture mode and a given dynamic range.
             */
            PanelSource[] supportedAVSources;
        }

        /**
         * Lists the dynamic range capabilities for a picture mode.
         */
        DynamicRangeCapabilities[] dynamicRangeCapabilities;
    }

    /**
     * Array of picture modes and their capabilities, listing the dynamic ranges and AV sources supported.
     */
    PictureModeCapabilities[] pictureModeCapabilities;
}

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
 *  @brief     2-point white balance settings.
 *             Holds the gain, offset and colour temperature source offset for a
 *             2-point white balance calibration entry. Used as the value type for
 *             PQParameter.TWO_POINT_WB in set/get/getDefault/getCapabilities operations.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 */

@VintfStability
parcelable TwoPointWBSettings
{
    /**
     * Colour temperature source offset.
     * Maps to tvColorTempSourceOffset_e in tvTypes.h.
     */
    @VintfStability
    @Backing(type="int")
    enum ColorTempSourceOffset {
        /** WB calibration applies to all video sources. */
        ALL_SRC = -1,
        /** WB calibration source offset is HDMI (applicable for all HDMI and Tuner). */
        HDMI    =  0,
        /** WB calibration source offset is IP/TV. */
        TV      =  1,
        /** WB calibration source offset is Composite (AV). */
        AV      =  2,
        /** Upper bound (not a valid source offset). */
        MAX     =  3,
    }

    /**
     * 2-point white balance entry containing gain, offset and source offset.
     */
    parcelable TwoPointWB {
        /**
         * White balance gain value.
         * Valid range is 0 to 2047.
         */
        int gain;

        /**
         * White balance offset value.
         * Valid range is -1024 to 1023.
         */
        int offset;

        /**
         * The colour temperature source offset this entry applies to.
         */
        ColorTempSourceOffset clrTempSrcOffset;
    }
}

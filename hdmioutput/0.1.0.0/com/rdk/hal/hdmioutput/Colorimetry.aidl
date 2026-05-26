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
package com.rdk.hal.hdmioutput;

/** 
 *  @brief     HDMI Colorimetry enum.
 *
 *  Represents the base colorimetry values encoded in the AVI InfoFrame field C.
 *  These values define the default colour matrix used by the HDMI sink device,
 *  unless overridden by extended colorimetry settings.
 *
 *  Reference: HDMI Specification – AVI InfoFrame (Colorimetry Field).
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type = "int")
enum Colorimetry 
{
    /**
     * No colorimetry data – AVI InfoFrame C=0
     */
    NO_DATA = 0,

    /**
     * SMPTE 170M / ITU-R BT.601 – AVI InfoFrame C=1
     */
    SMPTE_170M = 1,

    /**
     * ITU-R BT.709 – AVI InfoFrame C=2
     */
    ITU_R_BT709 = 2,

    /**
     * Extended colorimetry – AVI InfoFrame C=3.
     * Requires use of the EC (Extended Colorimetry) field.
     *
     * @see ExtendedColorimetry
     */
    EXTENDED_COLORIMETRY = 3
}

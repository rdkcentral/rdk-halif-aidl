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
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.hdmioutput;

/** 
 *  @brief     HDMI extended colorimetry enum.
 *
 *  Defines the extended colorimetry values used in the HDMI AVI InfoFrame when
 *  Colorimetry (C) is set to 3. These settings refine how the HDMI sink interprets
 *  colour space beyond standard ITU-R BT.709 or SMPTE 170M.
 *
 *  Reference: HDMI Specification – AVI InfoFrame EC (Extended Colorimetry) Field.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type = "int")
enum ExtendedColorimetry 
{
    /**
     * xvYCC601 – AVI InfoFrame C=3, EC=0
     */
    XV_YCC_601 = 0,

    /**
     * xvYCC709 – AVI InfoFrame C=3, EC=1
     */
    XV_YCC_709 = 1,

    /**
     * sYCC601 – AVI InfoFrame C=3, EC=2
     */
    S_YCC_601 = 2,

    /**
     * opYCC601 – AVI InfoFrame C=3, EC=3
     */
    OP_YCC_601 = 3,

    /**
     * opRGB – AVI InfoFrame C=3, EC=4
     */
    OP_RGB = 4,

    /**
     * ITU-R BT.2020 YCC (constant luminance) – AVI InfoFrame C=3, EC=5
     */
    BT2020_C_YCC = 5,

    /**
     * ITU-R BT.2020 RGB or YCC – AVI InfoFrame C=3, EC=6
     *
     * RGB interpretation when Y=0,
     * YCC interpretation when Y=1, 2, or 3.
     */
    BT2020_RGB_YCC = 6,

    /**
     * Additional Colorimetry Extension – AVI InfoFrame C=3, EC=7
     *
     * @see AdditionalColorimetryExtension for ACE field values.
     */
    ADDITIONAL_COLORIMETRY_EXTENSION = 7
}

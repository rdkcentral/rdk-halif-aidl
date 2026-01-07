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
 *  @brief     HDMI HDR output mode enum.
 *
 *  Defines the HDR output encoding mode for HDMI video signals.
 *  These modes control how video frames are signalled to the sink device,
 *  based on content tone-mapping and desired output format.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type = "int")
enum HDROutputMode
{
    /**
     * Automatically switches based on primary video content,
     * or outputs SDR when no HDR content is active.
     */
    AUTO = 0,

    /**
     * Output is encoded using Hybrid Log-Gamma (HLG) HDR.
     */
    HLG = 1,

    /**
     * Output is encoded using HDR10 (static metadata).
     */
    HDR10 = 2,

    /**
     * Output is encoded using HDR10+ (dynamic metadata).
     */
    HDR10_PLUS = 3,

    /**
     * Output is encoded using Dolby Vision HDR.
     */
    DOLBY_VISION = 4
}

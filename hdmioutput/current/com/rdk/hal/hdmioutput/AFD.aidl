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
 *  @brief     HDMI AFD (Active Format Description) enum.
 *  
 *  Represents the AFD values as specified in the HDMI AVI InfoFrame.
 *  These values indicate how the video content should be displayed
 *  with respect to aspect ratio and centring.
 * 
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type = "int")
enum AFD 
{
    /**
     * Unspecified AFD - AVI InfoFrame A0=0
     */
    UNSPECIFIED = -1,

    /**
     * Same as picture - AVI InfoFrame A0=1, R=1000b
     */
    SAME_AS_PICTURE = 8,

    /**
     * Centre 4:3 - AVI InfoFrame A0=1, R=1001b
     */
    CENTER_4_3 = 9,

    /**
     * Centre 16:9 - AVI InfoFrame A0=1, R=1010b
     */
    CENTER_16_9 = 10,

    /**
     * Centre 14:9 - AVI InfoFrame A0=1, R=1011b
     */
    CENTER_14_9 = 11
}

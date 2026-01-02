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
 *  @brief     HDMI AMD FreeSync enum.
 *
 *  Describes the level of AMD FreeSync support provided by the HDMI output.
 *  This is used in conjunction with `Capabilities.supportsFreeSync` to specify
 *  the actual feature tier supported.
 *
 *  Reference: AMD FreeSync specification.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type = "int")
enum FreeSync 
{
    /**
     * No FreeSync support.
     */
    UNSUPPORTED = 0,

    /**
     * AMD FreeSync basic tier.
     */
    FREESYNC = 1,

    /**
     * AMD FreeSync Premium tier.
     */
    FREESYNC_PREMIUM = 2,

    /**
     * AMD FreeSync Premium Pro tier.
     */
    FREESYNC_PREMIUM_PRO = 3
}

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
 *  @brief     HDMI AVI InfoFrame Scan Information enum.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 */
 
@VintfStability
@Backing(type = "int")
enum ScanInformation
{
    /**
     * No scan information.
     * AVI InfoFrame S=0
     */
    NO_DATA = 0,

    /**
     * Composed for an overscanned display.
     * AVI InfoFrame S=1
     */
    OVERSCAN = 1,

    /**
     * Composed for an underscanned display.
     * All active pixels and lines are displayed.
     * AVI InfoFrame S=2
     */
    UNDERSCAN = 2,

    /**
     * Reserved.
     * AVI InfoFrame S=3
     */
    RESERVED = 3
}

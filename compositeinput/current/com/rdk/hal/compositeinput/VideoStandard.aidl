/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
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

package com.rdk.hal.compositeinput;

/**
 * @brief Composite video standard types.
 * 
 * Enumerates the different composite video broadcast standards.
 * These standards differ in line count, frame rate, and color encoding.
 */
@VintfStability
@Backing(type="int")
enum VideoStandard
{
    /** Unknown or not yet detected video standard. */
    UNKNOWN = -1,
    
    /** NTSC-M: 525 lines, 60Hz (North America, Japan). */
    NTSC_M = 0,
    
    /** PAL-B: 625 lines, 50Hz (Europe, Australia). */
    PAL_B = 1,
    
    /** PAL-M: 525 lines, 60Hz (Brazil). */
    PAL_M = 2,
    
    /** PAL-N: 625 lines, 50Hz (Argentina, Paraguay, Uruguay). */
    PAL_N = 3,
    
    /** SECAM: 625 lines, 50Hz (France, Eastern Europe, Russia). */
    SECAM = 4,
}

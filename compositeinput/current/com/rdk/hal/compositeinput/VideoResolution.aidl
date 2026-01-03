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

import com.rdk.hal.compositeinput.VideoStandard;
import com.rdk.hal.compositeinput.ColorSpace;

/**
 * @brief Video resolution and format information.
 * 
 * Describes the detected video resolution, format, and timing
 * for a composite input signal.
 */
@VintfStability
parcelable VideoResolution
{
    /**
     * @brief Color information.
     */
    @VintfStability
    parcelable ColorInfo
    {
        /** Color space/encoding. */
        ColorSpace colorSpace;
        
        /** Bit depth per color component. */
        int bitDepth;
    }
    
    /** Detected video standard (NTSC/PAL/SECAM). */
    VideoStandard standard;
    
    /** Horizontal resolution in pixels (e.g., 720). */
    int pixelWidth;
    
    /** Vertical resolution in pixels (e.g., 480 or 576). */
    int pixelHeight;
    
    /** True if interlaced, false if progressive. */
    boolean interlaced;
    
    /** Frame rate in Hz (e.g., 25.0, 29.97, 50.0, 59.94). */
    float frameRate;
    
    /** Optional color information, or null if not available. */
    @nullable ColorInfo colorInfo;
}

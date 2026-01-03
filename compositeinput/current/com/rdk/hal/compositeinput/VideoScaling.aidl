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

import com.rdk.hal.compositeinput.ScalingMode;
import com.rdk.hal.compositeinput.VideoRectangle;
import com.rdk.hal.compositeinput.FilterQuality;

/**
 * @brief Video scaling configuration.
 * 
 * Defines how video should be scaled and positioned, including
 * the scaling mode, target rectangle, and optional parameters.
 */
@VintfStability
parcelable VideoScaling
{
    /**
     * @brief Additional scaling parameters.
     */
    @VintfStability
    parcelable ScalingParams
    {
        /** True to enable deinterlacing for interlaced content. */
        boolean deinterlaceEnabled;
        
        /** Filter quality for scaling. */
        FilterQuality filterQuality;
    }
    
    /** Scaling mode to apply. */
    ScalingMode mode;
    
    /** Target rectangle for video output. */
    VideoRectangle rectangle;
    
    /** Optional advanced scaling parameters, or null for defaults. */
    @nullable ScalingParams params;
}

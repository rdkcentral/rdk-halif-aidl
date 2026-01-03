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
import com.rdk.hal.compositeinput.ScalingMode;
import com.rdk.hal.compositeinput.Property;

/**
 * @brief Port-specific capabilities.
 * 
 * Describes the capabilities of an individual composite input port,
 * which may differ from platform capabilities if ports have varying features.
 */
@VintfStability
parcelable PortCapabilities
{
    /** Array of video standards supported by this port. */
    VideoStandard[] supportedVideoStandards;
    
    /** Array of scaling modes supported by this port. */
    ScalingMode[] supportedScalingModes;
    
    /** Array of properties supported by this port. */
    Property[] supportedProperties;
    
    /** True if this port supports audio. */
    boolean audioSupported;
    
    /** True if this port supports signal quality metrics. */
    boolean metricsSupported;
}

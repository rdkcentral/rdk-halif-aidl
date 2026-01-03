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
 * @brief Platform-wide capabilities for composite input.
 * 
 * Describes the overall capabilities of the composite input subsystem,
 * including supported features, video standards, and available ports.
 */
@VintfStability
parcelable PlatformCapabilities
{
    /**
     * @brief Feature flags for optional functionality.
     */
    @VintfStability
    parcelable FeatureFlags
    {
        /** True if audio detection and routing is supported. */
        boolean audioSupported;
        
        /** True if advanced scaling with filters is supported. */
        boolean advancedScalingSupported;
        
        /** True if signal quality metrics are available. */
        boolean signalMetricsSupported;
        
        /** True if color space conversion is supported. */
        boolean colorSpaceConversionSupported;
        
        /** True if Macrovision copy protection detection is supported. */
        boolean macrovisionDetectionSupported;
    }
    
    /** HAL version (semantic versioning, e.g., "1.0.0"). */
    @utf8InCpp String halVersion;
    
    /** Maximum number of ports supported. */
    byte maxPorts;
    
    /** Array of supported video standards. */
    VideoStandard[] supportedVideoStandards;
    
    /** Array of supported scaling modes. */
    ScalingMode[] supportedScalingModes;
    
    /** Array of supported properties. */
    Property[] supportedProperties;
    
    /** Feature flags indicating optional capabilities. */
    FeatureFlags features;
}

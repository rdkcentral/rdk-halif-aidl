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

import com.rdk.hal.compositeinput.PortProperty;
import com.rdk.hal.compositeinput.PropertyMetadata;

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
        /** True if signal quality metrics are available. */
        boolean signalMetricsSupported;

        /** True if Macrovision copy protection detection is supported. */
        boolean macrovisionDetectionSupported;
    }
    
    /** HAL version (semantic versioning, e.g., "1.0.0"). */
    @utf8InCpp String halVersion;
    
    /** Maximum number of ports supported. */
    byte maxPorts;

    /**
     * Maximum number of ports that may be in STARTED state simultaneously.
     *
     * Declared by the platform in the HFP. Most platforms will set this to 1
     * (single active port). ICompositeInputController.start() throws
     * EX_ILLEGAL_STATE if this limit would be exceeded.
     */
    int maximumConcurrentStartedPorts;

    /**
     * Array of PortProperty enum values supported across the platform.
     *
     * Declared in the platform HFP. Includes both runtime status keys and
     * telemetry metric keys. Individual ports may support a subset (see
     * PortCapabilities.supportedProperties).
     */
    PortProperty[] supportedProperties;

    /**
     * Property metadata for all supported properties (optional).
     *
     * Provides type information and access flags for each property.
     * Array indices correspond to supportedProperties array.
     * May be null if metadata is not available.
     */
    @nullable PropertyMetadata[] propertyMetadata;

    /** Feature flags indicating optional capabilities. */
    FeatureFlags features;
}

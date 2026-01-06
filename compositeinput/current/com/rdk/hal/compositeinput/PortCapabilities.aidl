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
import com.rdk.hal.compositeinput.PropertyMetadata;

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

    /**
     * Array of property key strings supported by this port.
     *
     * May be a subset of platform supportedProperties if different ports
     * have different capabilities. Contains keys defined in HFP YAML.
     */
    @utf8InCpp String[] supportedProperties;

    /**
     * Property metadata for this port's supported properties (optional).
     *
     * Array indices correspond to supportedProperties array.
     * May be null if metadata is not available.
     */
    @nullable PropertyMetadata[] propertyMetadata;

    /** True if this port supports audio. */
    boolean audioSupported;

    /** True if this port supports signal quality metrics. */
    boolean metricsSupported;
}

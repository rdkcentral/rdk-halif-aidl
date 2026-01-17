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

import com.rdk.hal.PropertyValue;

/**
 * @brief Key-value pair for composite input properties.
 *
 * Used by getPropertyMulti() and setPropertyMulti() for batch operations.
 * Property keys are defined in the HFP YAML and discoverable via capabilities.
 */
@VintfStability
parcelable PropertyKVPair
{
    /**
     * Property key string (e.g., "SIGNAL_STRENGTH", "VIDEO_STANDARD").
     *
     * Should match one of the keys in the platform's supportedProperties array
     * returned by getCapabilities().
     */
    @utf8InCpp String key;

    /**
     * Property value.
     *
     * - For getPropertyMulti(), this field is populated by the HAL on return.
     * - For setPropertyMulti(), this field must be pre-filled by the caller.
     *
     * The appropriate union field should be used based on the property type:
     * - booleanValue for boolean properties
     * - intValue for integer/enum properties
     * - longValue for numeric properties (e.g., SIGNAL_STRENGTH, metrics)
     * - doubleValue for floating-point properties
     * - stringValue for text properties
     */
    PropertyValue value;
}

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
import com.rdk.hal.PropertyValue;

/**
 * @brief Key-value pair for composite input port properties.
 *
 * Used by ICompositeInputPort.getPropertyMulti() and
 * ICompositeInputController.setPropertyMulti() for batch operations.
 */
@VintfStability
parcelable PropertyKVPair
{
    /**
     * Property key (from the PortProperty enum).
     *
     * Must be one of the values declared in the platform HFP under
     * ports[].supportedProperties and discoverable via
     * PortCapabilities.supportedProperties.
     */
    PortProperty property;

    /**
     * Property value.
     *
     * - For getPropertyMulti(), this field is populated by the HAL on return.
     * - For setPropertyMulti(), this field must be pre-filled by the caller.
     *
     * The appropriate union field must match PropertyMetadata.type:
     * - booleanValue for BOOLEAN properties
     * - intValue for INTEGER/enum properties
     * - longValue for LONG properties (e.g., SIGNAL_STRENGTH, metrics)
     * - floatValue for FLOAT properties
     * - doubleValue for DOUBLE properties
     * - stringValue for STRING properties
     */
    PropertyValue value;
}

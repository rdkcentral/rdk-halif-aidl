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
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.hdmioutput;

import com.rdk.hal.hdmioutput.Property;
import com.rdk.hal.PropertyValue;

/**
 *  @brief     Key-value pair for HDMI output properties.
 *
 *  Used by `getPropertyMulti()` and `setPropertyMulti()` to pass or return
 *  batched property requests. Each instance pairs a `Property` key with a
 *  `PropertyValue`, which may represent configuration, runtime state, or metrics.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */
@VintfStability
parcelable PropertyKVPair
{
    /**
     * The property key to access.
     *
     * Must be one of the valid enum values from @see Property.
     * This field is mandatory when issuing a request.
     */
    Property property;

    /**
     * The value associated with the key.
     *
     * - For `getPropertyMulti()`, this field is populated by the HAL on return.
     * - For `setPropertyMulti()`, this field must be pre-filled by the caller.
     *
     * If a property is unsupported or fails validation, the returned
     * `propertyValue` may be null or default-constructed.
     */
    PropertyValue propertyValue;
}

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
 * @brief Metadata describing a composite input property.
 *
 * Provides type information and access flags for properties,
 * enabling runtime discovery and validation. Property keys and
 * metadata are defined in the HFP YAML configuration.
 */
@VintfStability
parcelable PropertyMetadata
{
    /**
     * @brief Property value type enumeration.
     *
     * Indicates which field of PropertyValue union should be used.
     */
    @VintfStability
    @Backing(type="int")
    enum PropertyType
    {
        /** Boolean value - maps to PropertyValue.booleanValue */
        BOOLEAN = 0,

        /** Integer value - maps to PropertyValue.intValue (often used for enums) */
        INTEGER = 1,

        /** Long value - maps to PropertyValue.longValue */
        LONG = 2,

        /** Float value - maps to PropertyValue.floatValue */
        FLOAT = 3,

        /** Double value - maps to PropertyValue.doubleValue */
        DOUBLE = 4,

        /** String value - maps to PropertyValue.stringValue */
        STRING = 5,
    }

    /** Property key string (e.g., "SIGNAL_STRENGTH"). */
    @utf8InCpp String key;

    /** Data type of the property value. */
    PropertyType type;

    /** True if property is read-only. */
    boolean readOnly;

    /** True if property is a metric (for categorization). */
    boolean isMetric;

    /** Human-readable description of the property. */
    @utf8InCpp String description;
}

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
package com.rdk.hal;

/**
 * @file      PropertyType.aidl
 * @brief     Common property value type enumeration shared across HAL interfaces.
 *
 *            Indicates which field of the common PropertyValue union should be
 *            read or written for a given property. Used by any component that
 *            ships metadata describing a runtime-discovered property set —
 *            e.g. compositeinput's PropertyMetadata, audiomixer's
 *            AQParameterMetadata.
 *
 *            Each enumerator maps 1:1 to a field of com.rdk.hal.PropertyValue.Value:
 *
 *            <ul>
 *              <li>BOOLEAN -> PropertyValue.value.booleanValue</li>
 *              <li>INTEGER -> PropertyValue.value.intValue</li>
 *              <li>LONG    -> PropertyValue.value.longValue</li>
 *              <li>FLOAT   -> PropertyValue.value.floatValue</li>
 *              <li>DOUBLE  -> PropertyValue.value.doubleValue</li>
 *              <li>STRING  -> PropertyValue.value.stringValue</li>
 *            </ul>
 *
 *            Promoted from compositeinput.PropertyMetadata.PropertyType so it
 *            can be shared without cross-package imports between consumer
 *            components.
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 * @copyright Copyright 2026 RDK Management
 */
@VintfStability
@Backing(type="int")
enum PropertyType
{
    /** Boolean value - maps to PropertyValue.value.booleanValue. */
    BOOLEAN = 0,

    /** 32-bit signed integer value - maps to PropertyValue.value.intValue (often used for enums). */
    INTEGER = 1,

    /** 64-bit signed integer value - maps to PropertyValue.value.longValue. */
    LONG = 2,

    /** 32-bit floating-point value - maps to PropertyValue.value.floatValue. */
    FLOAT = 3,

    /** 64-bit floating-point value - maps to PropertyValue.value.doubleValue. */
    DOUBLE = 4,

    /** String value - maps to PropertyValue.value.stringValue. */
    STRING = 5,
}

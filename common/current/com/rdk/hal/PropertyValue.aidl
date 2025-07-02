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
 * @brief       RDK HAL common property value variant type.
 * @author      Luc Kennedy-Lamb
 * @author      Peter Stieglitz
 * @author      Douglas Adler
 */

@VintfStability
parcelable PropertyValue 
{
    /**
    * Union Value type.
    */
    @VintfStability
    union Value
    {
        boolean booleanValue; /**< Boolean value. */
        byte byteValue;       /**< 8-bit integer value. */
        char charValue;       /**< 16-bit Unicode character value. */
        int intValue;         /**< 32-bit signed integer value. */
        long longValue;       /**< 64-bit signed integer value. */
        float floatValue;     /**< 32-bit floating-point value. */
        double doubleValue;   /**< 64-bit floating-point value. */
        String stringValue;   /**< String value. */
        int[] intArrayValue; // for arrays of enums */
    }

    /**
    * Value of property or null if not defined.
    */
    @nullable Value value;
}

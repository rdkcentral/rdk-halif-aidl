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
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.audiomixer;

import com.rdk.hal.PropertyValue;

/**
 * @file      AQParameterKV.aidl
 * @brief     Single AQ parameter name/value pair used by batch read and
 *            write entry points on IAQProcessor and IAQProcessorController.
 *
 * @details   The @c name field matches an entry returned from
 *            IAQProcessor.getSupportedParameters() (i.e. the canonical
 *            spelling declared in the platform HFP). The @c value carries
 *            the value in the common PropertyValue union; the active union
 *            field MUST match the @c type recorded in the corresponding
 *            AQParameterMetadata entry.
 *
 *            Used by:
 *              - IAQProcessor.getAQParameters() to return a coherent
 *                snapshot of multiple parameters.
 *              - IAQProcessorController.setAQParameters() to apply a
 *                batch atomically (all-or-nothing).
 *
 * @see       AQParameterMetadata
 * @see       IAQProcessor.getAQParameters()
 * @see       IAQProcessorController.setAQParameters()
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 */
@VintfStability
parcelable AQParameterKV {

    /**
     * @brief Canonical parameter name (matches AQParameterMetadata.name).
     */
    @utf8InCpp String name;

    /**
     * @brief Parameter value carried in the common PropertyValue union.
     *
     * @details The active union field MUST match the PropertyType declared
     *          for this name in the matching AQParameterMetadata entry.
     *          Mismatched union fields cause setAQParameters() to fail
     *          atomically with EX_ILLEGAL_ARGUMENT.
     */
    PropertyValue value;
}

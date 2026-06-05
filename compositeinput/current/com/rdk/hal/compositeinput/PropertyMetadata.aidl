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
import com.rdk.hal.PropertyType;

/**
 * @brief Metadata describing a composite input property.
 *
 * Provides type information and access flags for properties,
 * enabling runtime discovery and validation. Property keys and
 * metadata are defined in the HFP YAML configuration.
 *
 * @note  The PropertyType enum was promoted out of this parcelable into
 *        the shared com.rdk.hal package so multiple HAL components can
 *        reuse the same type taxonomy without cross-package imports.
 */
@VintfStability
parcelable PropertyMetadata
{
    /** Property key (from the PortProperty enum). */
    PortProperty key;

    /** Data type of the property value (shared PropertyType enum). */
    PropertyType type;

    /** True if property is read-only. */
    boolean readOnly;

    /** True if property is a metric (for categorization). */
    boolean isMetric;

    /** Human-readable description of the property. */
    @utf8InCpp String description;
}

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
package com.rdk.hal.panel;

/**
 *  @brief     Capability of a single PQ parameter — its identity, scope and value range.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 *
 *  Returned by `IPanelOutput.getSupportedPQParameters()` for a queried context,
 *  and embedded in `Capabilities.pqParameters` alongside the contexts the
 *  parameter applies in.  A parameter's presence in either implies it is
 *  supported by the platform; unsupported parameters are never listed.
 */
@VintfStability
parcelable PQParameterCapability
{
    /**
     * The PQ parameter name.
     * Canonical names are defined in `PQParameter`; vendor-specific parameters
     * use the `vendor.<vendorname>.` namespace.
     */
    @utf8InCpp String pqParameter;

    /**
     * Whether this PQ parameter globally affects the composite image, including
     * the graphics plane and all video planes, or is limited to video.
     * e.g. PQParameter.MANUAL_BACKLIGHT will be global if it represents an LED backlight
     *      but PQParameter.SHARPNESS may only operate on video.
     * Global parameters apply in every context.
     */
    boolean isGlobal;

    /**
     * The minimum and maximum values for this PQ parameter.
     */
    int minValue;
    int maxValue;

    /**
     * The list of specific values ranging from minValue to maxValue inclusive, which are supported.
     * This array of values only needs to be specified if not all integer values
     * between minValue and maxValue are supported.  e.g. From an enum list of values.
     */
    int[] values;
}

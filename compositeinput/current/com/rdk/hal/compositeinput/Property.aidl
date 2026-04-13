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
 * @brief Composite input property keys used in property get/set functions.
 *
 * These keys identify runtime attributes and telemetry metrics of a composite
 * input port. They are the canonical reference for the property key strings
 * declared in hfp-compositeinput.yaml under supportedProperties[],
 * supportedMetrics[] and propertyMetadata[].key.
 *
 * The string-keyed getProperty()/setProperty()/getPropertyMulti()/
 * setPropertyMulti() methods on ICompositeInputPort are the transitional
 * form of this API. A future revision of the compositeinput HAL will migrate
 * those methods to take Property enum values directly, aligning with the
 * convention used by sibling HALs (hdmiinput, videodecoder, planecontrol).
 * Until then, this enum serves as the single source of truth for the key
 * strings platforms must declare in their HFP.
 *
 * Numeric slots are sparse so that future additions never renumber existing
 * values: runtime/status keys occupy 0..999, metric keys occupy 1000 upward.
 *
 * @author Gerald Weatherup
 */
@VintfStability
@Backing(type="int")
enum Property
{
    /**
     * Signal strength of the composite input, in dBm.
     *
     * Type: Long
     * Access: Read-only
     */
    SIGNAL_STRENGTH = 0,

    /**
     * Average time taken for the composite input to achieve signal lock,
     * in milliseconds. Reset by resetMetrics().
     *
     * Type: Long
     * Access: Read-only
     */
    METRIC_SIGNAL_LOCK_TIME = 1000,

    /**
     * Total count of signal drops observed on the composite input since
     * the last call to resetMetrics().
     *
     * Type: Long
     * Access: Read-only
     */
    METRIC_SIGNAL_DROPS = 1001,

    /**
     * Total uptime of the composite input since the last call to
     * resetMetrics(), in milliseconds.
     *
     * Type: Long
     * Access: Read-only
     */
    METRIC_UPTIME = 1002

    /**
     * Additional keys may be introduced in future revisions.
     * Clients must tolerate unknown keys gracefully.
     */
}

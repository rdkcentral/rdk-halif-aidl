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

import com.rdk.hal.compositeinput.Port;
import com.rdk.hal.compositeinput.PortMetrics;

/**
 * @brief Listener interface for port telemetry.
 * 
 * Callbacks for signal quality changes and metrics updates.
 * These callbacks are used for monitoring and diagnostics.
 * 
 * @author Gerald Weatherup
 */
@VintfStability
oneway interface IPortTelemetryListener
{
    /**
     * @brief Callback for signal quality changes.
     * 
     * Called when the signal quality percentage changes significantly.
     * This can be used for UI indicators or adaptive behavior.
     * 
     * @param[in] portId The port ID with quality change.
     * @param[in] quality Signal quality percentage (0-100).
     */
    void onSignalQualityChanged(in int portId, in byte quality);
    
    /**
     * @brief Callback for metrics updates.
     * 
     * Called periodically or when significant metrics changes occur.
     * Update frequency is implementation-defined.
     * 
     * @param[in] portId The port ID with updated metrics.
     * @param[in] metrics The current metrics snapshot.
     */
    void onMetricsUpdated(in int portId, in PortMetrics metrics);
}

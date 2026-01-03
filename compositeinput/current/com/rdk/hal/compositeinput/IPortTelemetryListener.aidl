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
 * Provides asynchronous callbacks for signal quality changes and metrics updates.
 * These callbacks are used for monitoring, diagnostics, and performance analysis.
 * Requires port metrics support (PortCapabilities.metricsSupported).
 *
 * Register instances of this interface using ICompositeInputPort.registerTelemetryListener().
 * Callbacks are delivered via oneway binder calls and do not block the HAL service.
 */
@VintfStability
oneway interface IPortTelemetryListener
{
    /**
     * Callback for signal quality changes.
     *
     * Called when the signal quality percentage changes significantly (implementation-defined
     * threshold, typically 5-10% change). Quality represents an overall assessment of signal
     * health and can be used for UI indicators or adaptive behavior.
     *
     * @param[in] portId     The port ID with quality change (0 to maxPorts-1).
     * @param[in] quality    Signal quality percentage (0-100).
     *                       - 0: No signal or very poor quality
     *                       - 1-30: Poor quality (unstable, artifacts expected)
     *                       - 31-70: Fair quality (acceptable but not optimal)
     *                       - 71-90: Good quality (stable, clear picture)
     *                       - 91-100: Excellent quality (optimal signal)
     *
     * @pre Port must support metrics (PortCapabilities.metricsSupported == true).
     * @post Clients may adjust UI indicators or trigger warnings based on quality thresholds.
     *
     * @see ICompositeInputPort.registerTelemetryListener(), ICompositeInputPort.getMetrics()
     */
    void onSignalQualityChanged(in int portId, in byte quality);

    /**
     * Callback for metrics updates.
     *
     * Called periodically or when significant metrics changes occur (e.g., signal drops,
     * lock time spikes). Update frequency is implementation-defined but typically ranges
     * from 1-10 seconds during active monitoring. Provides a snapshot of telemetry counters.
     *
     * @param[in] portId     The port ID with updated metrics (0 to maxPorts-1).
     * @param[in] metrics    The current metrics snapshot containing signal lock times,
     *                       drop counts, uptime, and last reset timestamp.
     *
     * @pre Port must support metrics (PortCapabilities.metricsSupported == true).
     * @post Clients can log, analyze, or display metrics for diagnostics and performance monitoring.
     *
     * @see PortMetrics, ICompositeInputPort.getMetrics(), ICompositeInputPort.resetMetrics()
     */
    void onMetricsUpdated(in int portId, in PortMetrics metrics);
}

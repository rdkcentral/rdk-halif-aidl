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
 * @brief Composite input port property keys used in get/set functions.
 *
 * Port-scoped runtime state and telemetry keys for a composite input port.
 * Used by ICompositeInputPort.getProperty() / getPropertyMulti() for reads
 * and ICompositeInputController.setProperty() / setPropertyMulti() for writes.
 *
 * Keys are declared per port by the platform in hfp-compositeinput.yaml
 * under ports[].supportedProperties and surfaced through
 * PortCapabilities.supportedProperties.
 *
 * Numeric slots are sparse so additions never renumber existing values:
 * - 0..999    runtime status keys
 * - 1000+     telemetry metric counters (reset by ICompositeInputController.resetMetrics())
 *
 * Metrics are first-class property keys. There is no separate metrics
 * parcelable — metrics are read with the same get/getMulti methods
 * used for status, matching the convention used by videodecoder,
 * videosink, hdmiinput and hdmioutput.
 *
 * @author Gerald Weatherup
 */
@VintfStability
@Backing(type="int")
enum PortProperty
{
    /**
     * Signal strength of the composite input, in dBm.
     *
     * Type: Long
     * Access: Read-only.
     */
    SIGNAL_STRENGTH = 0,

    /**
     * Aggregated signal quality score.
     *
     * Overall signal-health percentage used for UI indicators and adaptive
     * behaviour. Implementation-defined weighting of strength, lock stability,
     * and error rates.
     *
     * Type: Integer (0..100)
     *   0         No signal or very poor quality
     *   1..30     Poor quality (unstable, artifacts expected)
     *   31..70    Fair quality (acceptable but not optimal)
     *   71..90    Good quality (stable, clear picture)
     *   91..100   Excellent quality (optimal signal)
     * Access: Read-only.
     */
    SIGNAL_QUALITY = 1,

    /**
     * Average time taken for the composite input to achieve signal lock,
     * in milliseconds.
     *
     * Type: Long
     * Access: Read-only.
     * Reset by ICompositeInputController.resetMetrics().
     */
    METRIC_SIGNAL_LOCK_TIME = 1000,

    /**
     * Total count of signal drops (lock-loss events) observed on the
     * composite input since the last call to resetMetrics().
     *
     * Type: Long
     * Access: Read-only.
     * Reset by ICompositeInputController.resetMetrics().
     */
    METRIC_SIGNAL_DROPS = 1001,

    /**
     * Total uptime of the composite input since the last call to
     * resetMetrics(), in milliseconds.
     *
     * Type: Long
     * Access: Read-only.
     * Reset by ICompositeInputController.resetMetrics().
     */
    METRIC_UPTIME = 1002,

    /**
     * Total count of successful signal lock acquisitions since the last
     * call to resetMetrics().
     *
     * Type: Long
     * Access: Read-only.
     * Reset by ICompositeInputController.resetMetrics().
     */
    METRIC_SIGNAL_LOCK_COUNT = 1003,

    /**
     * Most recent signal lock time, in milliseconds.
     *
     * The time the most recent successful lock acquisition took.
     *
     * Type: Long
     * Access: Read-only.
     * Reset by ICompositeInputController.resetMetrics().
     */
    METRIC_LAST_SIGNAL_LOCK_TIME = 1004,

    /**
     * Timestamp when metrics were last reset, in milliseconds since epoch.
     *
     * Set to the current wall-clock time by ICompositeInputController.resetMetrics().
     *
     * Type: Long
     * Access: Read-only.
     */
    METRIC_LAST_RESET_TIMESTAMP = 1005

    /**
     * Additional keys may be introduced in future revisions.
     * Clients must tolerate unknown keys gracefully.
     */
}

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
package com.rdk.hal.hdmiinput.metrics;

/**
 * @brief Metrics served by the HDMI input port.
 *
 * Read with IHDMIInput.getMetrics() or getMetric(). Values are append-
 * only: a member is never renumbered or reused. Each counter starts at
 * zero when the service initialises, only rises, and is kept per resource
 * instance.
 */
@VintfStability
@Backing(type = "int")
enum Metric {
    /**
     * @brief HDMI packet errors detected.
     *
     * Measures: packets received on the port in which the receiver
     * detected an error it could not correct, counted at the receiver
     * while the port is STARTED.
     *
     * Excludes: errors corrected by the receiver, and packets received
     * before the signal is stable after a hotplug or a mode change.
     *
     * Used for: judging the quality of the HDMI link and its cable.
     *
     * How to use: difference two snapshots and divide by the
     * difference in timestampNs for an error rate. A run of errors is
     * reported as an Episode::PACKET_ERROR episode.
     *
     * Unit: packets. Kind: counter.
     */
    PACKET_ERRORS = 0,
}

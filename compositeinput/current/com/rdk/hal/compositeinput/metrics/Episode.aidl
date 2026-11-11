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
package com.rdk.hal.compositeinput.metrics;

/**
 * @brief Episodes the composite input port reports.
 *
 * An episode is something with a start and an end. Each is reported once
 * when it starts, by
 * ICompositeInputEventListener.onMetricEpisodeStarted(), and once when it
 * ends, by onMetricEpisodeResolved(); nothing is raised per occurrence.
 * Per-occurrence figures are read with ICompositeInputPort.getMetrics().
 *
 * An episode still open at stop() or close() ends there. A product raises
 * an episode where it supports the metric named on the member. Values are
 * append-only: a member is never renumbered or reused.
 */
@VintfStability
@Backing(type = "int")
enum Episode {
    /**
     * @brief A loss of signal lock while STARTED.
     *
     * Starts when an acquired lock is lost while the port is STARTED,
     * and ends when lock is gained again. Each episode adds one to
     * Metric::SIGNAL_DROPS.
     *
     * durationNs runs from the started event to the resolved event;
     * count is not used and is 0.
     *
     * presentationTimeNs is not used by the composite input port and
     * is -1.
     *
     * Support: optional.
     */
    SIGNAL_LOSS = 0,
}

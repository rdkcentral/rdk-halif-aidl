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
package com.rdk.hal.audiomixer.metrics;

/**
 * @brief Episodes the audio output port reports.
 *
 * An episode is something with a start and an end. Each is reported once
 * when it starts, by IAudioOutputPortListener.onMetricEpisodeStarted(),
 * and once when it ends, by onMetricEpisodeResolved(); nothing is raised
 * per occurrence. Per-occurrence figures are read with
 * IAudioOutputPort.getMetrics().
 *
 * An episode still open at stop() or close() ends there. A product raises
 * an episode where it supports the metric named on the member. Values are
 * append-only: a member is never renumbered or reused.
 */
@VintfStability
@Backing(type = "int")
enum Episode {
    /**
     * @brief An underflow: the output port's consumer starved.
     *
     * Starts when the consumer of the output port needs audio and
     * finds none, and ends when audio flows to it again. Each episode
     * adds one to Metric::UNDERFLOW_EPISODES.
     *
     * durationNs runs from the started event to the resolved event;
     * count is not used and is 0.
     *
     * presentationTimeNs is not used by the audio output port and is
     * -1.
     */
    UNDERFLOW = 0,

    /**
     * @brief A run of writes refused for lack of buffer space.
     *
     * Covers overflows counted by Metric::OVERFLOWS. The episode
     * starts at the first overflow when no such episode is open and
     * ends when 1 second has passed without another.
     *
     * durationNs runs from the first overflow to the last; count is
     * the overflows.
     *
     * presentationTimeNs is not used by the audio output port and is
     * -1.
     */
    OVERFLOW = 1,
}

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
 * @brief Metrics served by the audio output port.
 *
 * Read with IAudioOutputPort.getMetrics() or getMetric(). Values are
 * append-only: a member is never renumbered or reused. Each counter starts
 * at zero when the service initialises, only rises, and is kept per
 * resource instance.
 */
@VintfStability
@Backing(type = "int")
enum Metric {
    /**
     * @brief Underflows started at the output port.
     *
     * Measures: occasions on which the consumer of the output port
     * needed audio and found none while the port was enabled, counted
     * when the starvation is detected; one per Episode::UNDERFLOW
     * episode.
     *
     * Excludes: silence the mixer outputs because no input is playing,
     * and any period in which the port is disabled.
     *
     * Used for: counting audible dropouts at an output.
     *
     * How to use: difference two snapshots; pair with
     * UNDERFLOW_DURATION_NS for the mean dropout length.
     *
     * Unit: episodes. Kind: counter. Support: mandatory.
     */
    UNDERFLOW_EPISODES = 0,

    /**
     * @brief Total time spent in underflow at the output port.
     *
     * Measures: time from each underflow starting to audio flowing to
     * the consumer again, summed over all episodes and including the
     * elapsed part of an episode still open at the latch.
     *
     * Excludes: as UNDERFLOW_EPISODES.
     *
     * Used for: measuring how long the listener heard nothing.
     *
     * How to use: dropout ratio = delta UNDERFLOW_DURATION_NS / delta
     * timestampNs between two snapshots.
     *
     * Unit: nanoseconds. Kind: counter. Support: mandatory.
     */
    UNDERFLOW_DURATION_NS = 1,

    /**
     * @brief Writes refused for lack of buffer space at the output
     * port.
     *
     * Measures: occasions on which the producer feeding the output
     * port had audio to write and no buffer space to write it into,
     * counted at each refused write while the port was enabled.
     *
     * Excludes: waits for buffer space that are part of normal pacing,
     * and any period in which the port is disabled.
     *
     * Used for: detecting an output whose consumer is not draining at
     * the rate audio is produced.
     *
     * How to use: difference two snapshots. A run of overflows is
     * reported as an Episode::OVERFLOW episode.
     *
     * Unit: overflows. Kind: counter. Support: optional.
     */
    OVERFLOWS = 2,
}

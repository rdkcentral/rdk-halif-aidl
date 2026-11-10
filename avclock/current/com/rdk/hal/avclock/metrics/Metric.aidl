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
package com.rdk.hal.avclock.metrics;

/**
 * @brief Metrics served by the AV clock.
 *
 * Each member is one figure, read through IAVClock.getMetrics() or getMetric().
 * A counter starts at zero when the service initialises and only rises: open(),
 * close(), flush(), start() and stop() do not reset it, so a client takes the
 * difference of two snapshots for a session or an interval. A gauge is the
 * level at the instant of the read.
 *
 * Each resource instance keeps its own figures: a counter covers that
 * instance only, across every session opened on it.
 *
 * The metrics a product serves are listed under supportedMetrics in its HAL
 * Feature Profile. Values are append-only: a member is never renumbered or
 * reused.
 */
@VintfStability
@Backing(type = "int")
enum Metric {
    /**
     * @brief Current audio to video offset.
     *
     * Measures: the difference between audio and video presentation as the
     * clock last measured it, negative when audio is ahead of video, taken at
     * the clock.
     *
     * Excludes: any period in which the sync group does not hold both an audio
     * and a video sink; the metric is then left out of the snapshot.
     *
     * Used for: checking lip sync against the product's tolerance.
     *
     * How to use: sample it at intervals; it is a level, so do not difference
     * it. Read it with RESYNC_COUNT to see whether an offset was corrected.
     *
     * Unit: nanoseconds, signed. Kind: gauge.
     */
    SYNC_OFFSET_NS = 0,

    /**
     * @brief Corrections made to restore lip sync.
     *
     * Measures: occasions on which the clock adjusted presentation to bring
     * audio and video back into sync, counted at the clock.
     *
     * Excludes: the alignment made when a session starts or after a flush, and
     * rate changes the client asked for.
     *
     * Used for: judging how stable sync is over a session.
     *
     * How to use: difference two snapshots and divide by the difference in
     * timestampNs for corrections per unit time.
     *
     * Unit: corrections. Kind: counter.
     */
    RESYNC_COUNT = 1,
}

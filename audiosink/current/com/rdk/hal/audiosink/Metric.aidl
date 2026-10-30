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
package com.rdk.hal.audiosink;

/**
 * @brief     The figures audiosink measures.
 * @author    Gerald Weatherup
 */

/**
 * @brief The figures audiosink measures.
 *
 * Each member states its unit and kind. `MetricValue.id` carries the member's
 * value, which is scoped to this component. Values are append-only.
 */

@VintfStability
@Backing(type="long")
enum Metric
{

    /**
     * Unit: episodes. Kind: counter. Count of audio buffer-underflow episodes,
     * one per episode start, where an episode starts when there is no decoded
     * audio to present and ends when output resumes. The counterpart of
     * `videosink`'s UNDERFLOWED — without it an audio underflow rate cannot be
     * computed at all.
     */
    UNDERFLOWED = 0,

    /**
     * Unit: ms. Kind: counter. Cumulative time the audio path was starved of
     * decoded data. Paired with underflowed, so the mean episode length is
     * this divided by that.
     */
    UNDERFLOW_DURATION_MS = 1,

    /**
     * Unit: ms. Kind: counter. Cumulative emitted digital silence, counting
     * only periods that reached SILENCE_THRESHOLD_MS. Distinguishes an
     * unexpected absence of audio output from starvation, which is
     * UNDERFLOW_DURATION_MS.
     */
    SILENCE_DURATION_MS = 2,

    /**
     * Unit: events. Kind: counter. Count of completed digital-silence periods
     * that reached SILENCE_THRESHOLD_MS. Paired with SILENCE_DURATION_MS, so
     * the mean silence length is that divided by this.
     */
    SILENCE_EVENT_COUNT = 3,

    /**
     * Unit: ms. Kind: current. Buffered decoded audio ahead of the play
     * position now. A live sample re-read each capture rather than a
     * cumulative figure. This is SoC- and use-case-specific, so compare it
     * against itself over time rather than across products.
     */
    BUFFER_DEPTH_MS = 4,

    /**
     * Unit: none. Kind: current. Cause of the most recent audio underflow
     * episode, with the same values as `videosink`'s
     * LAST_UNDERFLOW_TRIGGER.
     *
     * The value is a `MetricUnderflowTrigger`.
     */
    LAST_UNDERFLOW_TRIGGER = 5,

    /**
     * Unit: ms. Kind: current. Length of the most recent completed audio
     * underflow episode. Read with underflowed and UNDERFLOW_DURATION_MS,
     * which give the count and the total.
     */
    LAST_UNDERFLOW_DURATION_MS = 6,

    /**
     * Unit: ms. Kind: current. Length of the most recent completed
     * digital-silence period. Read with SILENCE_EVENT_COUNT and
     * SILENCE_DURATION_MS.
     */
    LAST_SILENCE_DURATION_MS = 7,

    /**
     * Unit: ms. Kind: config. Shortest digital-silence period that counts as
     * one. Silence is normal output — a gap between programmes, a muted
     * stream, a silent passage — so this is the line between that and a fault
     * worth reporting. Default 500 ms, and set by product configuration rather
     * than over this interface. Reading it is what the key is for:
     * SILENCE_DURATION_MS and SILENCE_EVENT_COUNT count only periods that
     * reached it, so neither is interpretable without it.
     */
    SILENCE_THRESHOLD_MS = 8,
}

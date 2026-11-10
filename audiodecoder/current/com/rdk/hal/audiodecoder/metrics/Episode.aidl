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
package com.rdk.hal.audiodecoder.metrics;

/**
 * @brief Episodes the audio decoder reports.
 *
 * An episode is something with a start and an end. Each is reported once when
 * it starts, by IAudioDecoderEventListener.onEpisodeStarted(), and once when it
 * ends, by onEpisodeResolved(); nothing is raised per frame. Per-frame figures
 * are read with IAudioDecoder.getMetrics().
 *
 * An episode still open at flush() or stop() ends there. A product raises an
 * episode where it supports the metric named on the member. Values are append-
 * only: a member is never renumbered or reused.
 */
@VintfStability
@Backing(type = "int")
enum Episode {
    /**
     * @brief A run of dropped frames.
     *
     * Covers frames counted by Metric::FRAMES_DROPPED. The episode starts at
     * the first dropped frame when no such episode is open and ends when 1
     * second has passed without another.
     *
     * durationNs runs from the first dropped frame to the last; count is the
     * frames dropped. presentationTimeNs is that of the first dropped frame on
     * the started event and of the last on the resolved event.
     */
    FRAME_DROP = 0,

    /**
     * @brief A run of decode errors.
     *
     * Covers errors counted by Metric::DECODE_ERRORS. The episode starts at the
     * first error when no such episode is open and ends when 1 second has
     * passed without another. Each error is still reported, with its error
     * code, by onDecodeError().
     *
     * durationNs runs from the first error to the last; count is the errors
     * raised. presentationTimeNs is that of the frame being decoded at the
     * first error on the started event and at the last on the resolved event.
     */
    DECODE_ERROR = 1,
}

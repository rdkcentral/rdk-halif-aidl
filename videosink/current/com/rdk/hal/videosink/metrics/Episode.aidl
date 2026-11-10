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
package com.rdk.hal.videosink.metrics;

/**
 * @brief Episodes the video sink reports.
 *
 * An episode is something with a start and an end. Each is reported once when
 * it starts, by IVideoSinkEventListener.onEpisodeStarted(), and once when it
 * ends, by onEpisodeResolved(); nothing is raised per frame. Per-frame figures
 * are read with IVideoSink.getMetrics().
 *
 * An episode still open at flush() or stop() ends there. A product raises an
 * episode where it supports the metric named on the member. Values are append-
 * only: a member is never renumbered or reused.
 */
@VintfStability
@Backing(type = "int")
enum Episode {
    /**
     * @brief A run of frames dropped for arriving late.
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
     * @brief A freeze: a run of repeated frames.
     *
     * Starts when the sink shows a frame again because the frame due was
     * missing or late, and ends when a new frame is presented. Each episode
     * adds one to Metric::FRAME_REPEAT_EPISODES.
     *
     * durationNs runs from the started event to the resolved event; count is
     * the repeats, as counted by Metric::FRAMES_REPEATED. presentationTimeNs is
     * that of the frame repeated on the started event and of the new frame on
     * the resolved event.
     */
    FRAME_REPEAT = 1,

    /**
     * @brief An underflow: nothing queued when a frame was due.
     *
     * Starts when the frame queue is empty at the presentation time of the next
     * frame, and ends when a frame is presented. Each episode adds one to
     * Metric::UNDERFLOW_EPISODES. The started event is raised with
     * onVideoUnderflow() and the resolved event with onVideoResumed().
     *
     * durationNs runs from the started event to the resolved event; count is
     * not used and is 0. presentationTimeNs is that of the first frame due and
     * missing on the started event and of the frame that ended the underflow on
     * the resolved event.
     */
    UNDERFLOW = 2,
}

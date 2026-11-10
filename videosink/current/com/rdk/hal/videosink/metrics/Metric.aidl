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
 * @brief Metrics served by the video sink.
 *
 * Each member is one figure, read through IVideoSink.getMetrics() or
 * getMetric(). A counter starts at zero when the service initialises and only
 * rises: open(), close(), flush(), start() and stop() do not reset it, so a
 * client takes the difference of two snapshots for a session or an interval. A
 * gauge is the level at the instant of the read.
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
     * @brief Frames presented at their time.
     *
     * Measures: frames the sink released for display at their presentation time
     * on the attached clock, each counted once, at the sink output. With no
     * video plane mapped the frame is counted when it is consumed at its
     * presentation time.
     *
     * Excludes: repeats of a frame already counted (FRAMES_REPEATED) and frames
     * discarded (FRAMES_DROPPED).
     *
     * Used for: the denominator for presentation quality, and the delivered
     * frame rate.
     *
     * How to use: FRAMES_RENDERED and FRAMES_DROPPED come from one latch when
     * asked for in one getMetrics() call; difference two snapshots and divide
     * by the difference in timestampNs for the delivered frame rate.
     *
     * Unit: frames. Kind: counter.
     */
    FRAMES_RENDERED = 0,

    /**
     * @brief Frames discarded because they arrived too late.
     *
     * Measures: frames queued to the sink and discarded without being presented
     * because their presentation time had passed, counted at the sink.
     *
     * Excludes: frames discarded on purpose by flush(), a seek, a stream
     * reconfiguration, stop() or end of stream, frames removed by frame rate
     * conversion or pacing, and frames the decoder never output
     * (com.rdk.hal.videodecoder.metrics.Metric::FRAMES_DROPPED).
     *
     * Used for: measuring stutter the viewer saw.
     *
     * How to use: rate = delta FRAMES_DROPPED / (delta FRAMES_RENDERED + delta
     * FRAMES_DROPPED), from one getMetrics() call per snapshot. A run of drops
     * is reported as an Episode::FRAME_DROP episode.
     *
     * Unit: frames. Kind: counter.
     */
    FRAMES_DROPPED = 1,

    /**
     * @brief Extra display periods spent on a frame already shown.
     *
     * Measures: display refreshes on which the sink showed the previous frame
     * again because the frame due was missing or late, counted at the sink
     * while STARTED.
     *
     * Excludes: repeats made on purpose by frame rate conversion or pacing, and
     * the hold of the last frame while paused, flushing or after end of stream.
     *
     * Used for: measuring freeze the viewer saw, in frames.
     *
     * How to use: divide delta FRAMES_REPEATED by delta FRAME_REPEAT_EPISODES
     * for the mean length of a freeze in frames.
     *
     * Unit: frames. Kind: counter.
     */
    FRAMES_REPEATED = 2,

    /**
     * @brief Freezes started.
     *
     * Measures: runs of one or more repeated frames, counted when the first
     * repeat of the run is shown; one per Episode::FRAME_REPEAT episode.
     *
     * Excludes: as FRAMES_REPEATED.
     *
     * Used for: counting how often the picture froze, whatever the length.
     *
     * How to use: difference two snapshots; pair with FRAMES_REPEATED for the
     * mean length.
     *
     * Unit: episodes. Kind: counter.
     */
    FRAME_REPEAT_EPISODES = 3,

    /**
     * @brief Underflows started.
     *
     * Measures: occasions on which the frame queue was empty at the
     * presentation time of the next frame while STARTED, counted when the queue
     * is found empty; one per Episode::UNDERFLOW episode. Underflow is measured at
     * the sink because that is where the audience experiences it. A decoder
     * with no input is ordinary, at start-up, after a seek, in trick play and
     * whenever the client feeds on demand, and says nothing about what was
     * presented; a sink with nothing to present when a frame is due is a stall
     * the audience sees.
     *
     * Excludes: an empty queue before the first frame of a session or after a
     * flush, while paused, and after end of stream has been signalled.
     *
     * Used for: counting stalls caused by late delivery to the sink.
     *
     * How to use: difference two snapshots; pair with UNDERFLOW_DURATION_NS for
     * the mean stall length.
     *
     * Unit: episodes. Kind: counter.
     */
    UNDERFLOW_EPISODES = 4,

    /**
     * @brief Total time spent in underflow.
     *
     * Measures: time from each underflow starting to the next frame being
     * presented, summed over all episodes and including the elapsed part of an
     * episode still open at the latch.
     *
     * Excludes: as UNDERFLOW_EPISODES.
     *
     * Used for: measuring how long the viewer waited, the stall ratio.
     *
     * How to use: stall ratio = delta UNDERFLOW_DURATION_NS / delta timestampNs
     * between two snapshots; mean stall = delta UNDERFLOW_DURATION_NS / delta
     * UNDERFLOW_EPISODES.
     *
     * Unit: nanoseconds. Kind: counter.
     */
    UNDERFLOW_DURATION_NS = 5,
}

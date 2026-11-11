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
package com.rdk.hal.audiosink.metrics;

/**
 * @brief Metrics served by the audio sink.
 *
 * Each member is one figure, read through IAudioSink.getMetrics() or
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
     * @brief Frames played at their time.
     *
     * Measures: audio frames the sink passed to the mixer at their presentation
     * time on the attached clock, counted at the sink output.
     *
     * Excludes: frames discarded (FRAMES_DROPPED) and silence inserted in place
     * of missing audio (GAP_FRAMES).
     *
     * Used for: the denominator for audio presentation quality.
     *
     * How to use: FRAMES_RENDERED and FRAMES_DROPPED come from one latch when
     * asked for in one getMetrics() call.
     *
     * Unit: frames. Kind: counter. Support: optional.
     */
    FRAMES_RENDERED = 0,

    /**
     * @brief Frames discarded because they arrived too late.
     *
     * Measures: audio frames queued to the sink and discarded without being
     * played because their presentation time had passed, counted at the sink.
     *
     * Excludes: frames discarded on purpose by flush(), a seek, a stream
     * reconfiguration, stop() or end of stream, frames removed to hold lip sync
     * or pace playback, and frames the decoder never output
     * (com.rdk.hal.audiodecoder.metrics.Metric::FRAMES_DROPPED).
     *
     * Used for: measuring audio the listener lost.
     *
     * How to use: rate = delta FRAMES_DROPPED / (delta FRAMES_RENDERED + delta
     * FRAMES_DROPPED), from one getMetrics() call per snapshot. A run of drops
     * is reported as an Episode::FRAME_DROP episode.
     *
     * Unit: frames. Kind: counter. Support: mandatory.
     */
    FRAMES_DROPPED = 1,

    /**
     * @brief Audio gaps started.
     *
     * Measures: runs of one or more frame periods in which the sink output
     * silence because the audio due was missing or late, counted when the run
     * starts while STARTED; one per Episode::GAP episode.
     *
     * Excludes: silence that is in the content, mute, and silence output while
     * paused, flushing or after end of stream.
     *
     * Used for: counting how often the listener heard a dropout.
     *
     * How to use: difference two snapshots; pair with GAP_DURATION_NS for the
     * mean dropout length.
     *
     * Unit: episodes. Kind: counter. Support: mandatory.
     */
    GAP_EPISODES = 2,

    /**
     * @brief Frame periods of silence output in gaps.
     *
     * Measures: frame periods filled with silence in place of missing or late
     * audio, summed over all gaps.
     *
     * Excludes: as GAP_EPISODES.
     *
     * Used for: measuring dropout in the unit FRAMES_RENDERED uses.
     *
     * How to use: gap ratio = delta GAP_FRAMES / (delta FRAMES_RENDERED + delta
     * GAP_FRAMES).
     *
     * Unit: frames. Kind: counter. Support: mandatory.
     */
    GAP_FRAMES = 3,

    /**
     * @brief Total time spent in audio gaps.
     *
     * Measures: time from each gap starting to audio playing again, summed over
     * all gaps and including the elapsed part of a gap still open at the latch.
     *
     * Excludes: as GAP_EPISODES.
     *
     * Used for: measuring how long the listener heard nothing.
     *
     * How to use: mean gap = delta GAP_DURATION_NS / delta GAP_EPISODES between
     * two snapshots.
     *
     * Unit: nanoseconds. Kind: counter. Support: mandatory.
     */
    GAP_DURATION_NS = 4,

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
     * the audience hears.
     *
     * Excludes: an empty queue before the first frame of a session or after a
     * flush, while paused, and after end of stream has been signalled.
     *
     * Used for: counting stalls caused by late delivery to the sink.
     *
     * How to use: difference two snapshots; pair with UNDERFLOW_DURATION_NS for
     * the mean stall length.
     *
     * Unit: episodes. Kind: counter. Support: mandatory.
     */
    UNDERFLOW_EPISODES = 5,

    /**
     * @brief Total time spent in underflow.
     *
     * Measures: time from each underflow starting to the next frame being
     * played, summed over all episodes and including the elapsed part of an
     * episode still open at the latch.
     *
     * Excludes: as UNDERFLOW_EPISODES.
     *
     * Used for: measuring how long the listener waited, the stall ratio.
     *
     * How to use: stall ratio = delta UNDERFLOW_DURATION_NS / delta timestampNs
     * between two snapshots.
     *
     * Unit: nanoseconds. Kind: counter. Support: mandatory.
     */
    UNDERFLOW_DURATION_NS = 6,

    /**
     * @brief Latency from leaving the sink queue to leaving the device.
     *
     * Measures: the time from a frame being taken from the sink's queue to
     * its sound leaving the output in use (HDMI, ARC, Bluetooth or the
     * internal speakers), as the sink currently estimates it for that output.
     *
     * Excludes: time the frame spends queued in the sink (QUEUE_DEPTH_NS), the
     * per-port delay set by com.rdk.hal.audiomixer.OutputPortProperty::DELAY_MS,
     * and any latency added by an external device after the output.
     *
     * Used for: aligning audio with video or with other outputs, and checking
     * the latency a product declares for each output.
     *
     * How to use: sample it at intervals or after an output change; it is a
     * level, so do not difference it.
     *
     * Unit: nanoseconds. Kind: gauge. Support: optional.
     */
    RENDER_LATENCY_NS = 7,

    /**
     * @brief Audio queued in the sink and not yet played, as time.
     *
     * Measures: the playing time of the audio held in the sink's queue and
     * output path at the latch, from the next frame to be played to the last
     * frame queued.
     *
     * Excludes: audio still in the decoder or in the client, and the output
     * latency counted by RENDER_LATENCY_NS.
     *
     * Used for: seeing how close the sink is to underflow, and sizing how far
     * ahead a client feeds.
     *
     * How to use: sample it at intervals; it is a level, so do not difference
     * it. A value that falls towards zero while STARTED precedes an
     * Episode::UNDERFLOW episode.
     *
     * Unit: nanoseconds. Kind: gauge. Support: optional.
     */
    QUEUE_DEPTH_NS = 8,
}

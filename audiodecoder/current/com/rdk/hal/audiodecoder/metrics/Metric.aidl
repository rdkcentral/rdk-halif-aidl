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
 * @brief Metrics served by the audio decoder.
 *
 * Each member is one figure, read through IAudioDecoder.getMetrics() or
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
     * @brief Frames the decoder has output.
     *
     * Measures: every audio frame handed onwards by the decoder, through
     * onFrameOutput() or to the vendor audio path when tunnelled, counted at
     * the decoder output.
     *
     * Excludes: input frames that produced no output (see FRAMES_DROPPED).
     *
     * Used for: the denominator for the decoder's drop and error rates.
     *
     * How to use: read it in the same getMetrics() call as the figure it
     * divides.
     *
     * Unit: frames. Kind: counter.
     */
    FRAMES_DECODED = 0,

    /**
     * @brief Input frames for which the decoder output nothing.
     *
     * Measures: audio frames the decoder received and neither output nor will
     * output, because they could not be decoded, counted at the decoder.
     *
     * Excludes: frames discarded on purpose by flush(), a seek, a stream
     * reconfiguration, stop() or end of stream, and frames the sink drops for
     * arriving late (com.rdk.hal.audiosink.metrics.Metric::FRAMES_DROPPED).
     *
     * Used for: telling a stream or decoder fault from a presentation fault:
     * frames lost here never reached the sink.
     *
     * How to use: rate = delta FRAMES_DROPPED / (delta FRAMES_DECODED + delta
     * FRAMES_DROPPED) between two snapshots. A run of drops is
     * reported as an Episode::FRAME_DROP episode.
     *
     * Unit: frames. Kind: counter.
     */
    FRAMES_DROPPED = 1,

    /**
     * @brief Errors the decoder has raised.
     *
     * Measures: decode errors detected in the bitstream or by the decode
     * hardware, counted at the decoder. A run of errors is reported as an
     * Episode::DECODE_ERROR episode.
     *
     * Excludes: errors returned from API calls, and the number of frames an
     * error affected (FRAMES_DROPPED).
     *
     * Used for: judging stream health and fault frequency.
     *
     * How to use: difference two snapshots for errors in the interval; use the
     * events for the time, the frame and the cause of each.
     *
     * Unit: errors. Kind: counter.
     */
    DECODE_ERRORS = 2,
}

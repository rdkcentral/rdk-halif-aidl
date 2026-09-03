/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
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
package com.rdk.hal.audiodecoder;

/**
 *  @brief     Per-buffer metadata carried with input buffers submitted via
 *             `IAudioDecoderController.decodeBufferWithMetadata()`.
 *
 *  Describes properties of the encoded audio frame that cannot be derived from
 *  the buffer contents alone, such as its presentation time and trim
 *  durations.
 *
 *  Each `decodeBufferWithMetadata()` call is self-describing: the HAL MUST NOT
 *  carry state from this parcelable across calls. In particular, `trimStartNs`
 *  and `trimEndNs` apply only to the buffer of the current call and do not
 *  carry forward.
 *
 *  @see IAudioDecoderController.decodeBufferWithMetadata()
 *
 *  @author    Gerald Weatherup
 */

@VintfStability
parcelable InputBufferMetadata {

    /**
     * Presentation time of the encoded audio frame in nanoseconds.
     */
    long nsPresentationTime;

    /**
     * Marks this buffer as the first following a PTS discontinuity.
     *
     * When true, the PTS of this buffer is discontinuous with previously
     * submitted buffers: the decoder MUST reset its PTS tracking and
     * interpolation state before decoding this buffer, and MUST NOT
     * interpolate timestamps across the discontinuity. Decoded output from
     * this buffer onward reports the new timeline; the first output frame
     * decoded from this buffer carries `FrameMetadata.discontinuity = true`.
     *
     * This is the sole discontinuity signal and is per-buffer in-band.
     * `flush()` also resets PTS state; this flag covers in-band
     * discontinuities without flushing queued data.
     *
     * @see FrameMetadata.discontinuity
     */
    boolean discontinuity;

    /**
     * Duration to trim from the start of the decoded audio frame, in nanoseconds.
     *
     * Per-frame trim — applied to the single decoded frame produced from this
     * input buffer, not to the stream as a whole. Relative to the frame's own
     * boundaries (a duration to discard from the leading edge), not an absolute
     * timestamp. Applies only to the buffer of the current
     * `decodeBufferWithMetadata()` call; not carried forward across calls.
     *
     * Set to 0 (the common case) to apply no trim to this frame's start.
     *
     * Primary use cases:
     * - Codec priming / encoder delay (e.g. AAC LC/HE prepended silence)
     * - Opus pre-skip
     * - AAC SBR padding
     * - Gapless playback across track boundaries
     *
     * Data flow: the middleware sets this here on each
     * `decodeBufferWithMetadata()` call; the HAL carries it through unchanged to
     * the matching `FrameMetadata.trimStartNs` on the corresponding
     * `IAudioDecoderControllerListener.onFrameOutput()` callback; the AudioSink
     * applies the trim when presenting PCM to the mixer.
     *
     * Type rationale: `int` (not `long`) — at nanosecond precision, max value is
     * ~2.1 seconds, sufficient for any per-frame priming/padding trim.
     *
     * @see FrameMetadata.trimStartNs
     */
    int trimStartNs;

    /**
     * Duration to trim from the end of the decoded audio frame, in nanoseconds.
     *
     * Per-frame trim — applied to the single decoded frame produced from this
     * input buffer, not to the stream as a whole. Relative to the frame's own
     * boundaries (a duration to discard from the trailing edge), not an
     * absolute timestamp. Applies only to the buffer of the current
     * `decodeBufferWithMetadata()` call; not carried forward across calls.
     *
     * Set to 0 (the common case) to apply no trim to this frame's end.
     *
     * Use cases, data flow, and type rationale as for `trimStartNs` above.
     *
     * @see FrameMetadata.trimEndNs
     */
    int trimEndNs;
}

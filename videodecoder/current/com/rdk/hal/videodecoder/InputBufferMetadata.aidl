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
package com.rdk.hal.videodecoder;

/**
 *  @brief     Per-buffer metadata carried with input buffers submitted via
 *             `IVideoDecoderController.decodeBufferWithMetadata()`.
 *
 *  Describes properties of the encoded frame that cannot be derived from the
 *  buffer contents alone (presentation time) or that signal decode-pipeline
 *  events (end of stream) which must be ordered precisely with respect to
 *  buffer flow.
 *
 *  Each `decodeBufferWithMetadata()` call is self-describing: the HAL MUST NOT
 *  carry state from this parcelable across calls. A subsequent call with
 *  default-valued fields replaces, it does not preserve, the previous call's
 *  values.
 *
 *  @see IVideoDecoderController.decodeBufferWithMetadata()
 *
 *  @author    Gerald Weatherup
 */

@VintfStability
parcelable InputBufferMetadata {

    /**
     * Presentation time of the encoded frame in nanoseconds.
     */
    long nsPresentationTime;

    /**
     * End-of-stream marker.
     *
     * When true, this is the final input buffer of the current decode session.
     * The buffer referenced by the `bufferHandle` parameter of
     * `decodeBufferWithMetadata()` MUST be a valid encoded frame - EOS is
     * always carried on a real final buffer, never signalled after it and
     * never on an EOS-only marker.
     *
     * The HAL shall decode this buffer, drain any held frames, and deliver
     * the final `IVideoDecoderControllerListener.onFrameOutput()` callback
     * with `FrameMetadata.endOfStream = true`.
     *
     * A client that has no more data to send ends the session via
     * `IVideoDecoderController.stop()` (or `flush(reset=true)` if the decoder
     * is to be reused). There is no way to signal EOS without data.
     */
    boolean endOfStream;

    /**
     * Reserved for a future release. Clients MUST set this to false in v1.
     *
     * Use `IVideoDecoderController.signalDiscontinuity()` to signal a PTS
     * discontinuity in v1. This field will become authoritative in a later
     * release once migration is complete.
     *
     * @see IVideoDecoderController.signalDiscontinuity()
     */
    boolean discontinuity;
}

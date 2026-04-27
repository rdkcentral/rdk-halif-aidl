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
import com.rdk.hal.audiodecoder.FrameMetadata;

/**
 *  @brief     Callbacks listener interface from audio decoder controller.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
oneway interface IAudioDecoderControllerListener {
    /**
    * Called when an audio frame has been decoded or when frame metadata needs notification.
    *
    * In tunnelled mode, audio data is consumed by the vendor layer, so no PCM buffer is returned.
    *
    * Otherwise, `frameAVBufferHandle` is a valid AVBuffer handle to a decoded PCM buffer,
    * and `metadata` is non-null for the first frame after `State::START` or `State::FLUSHING`,
    * or whenever stream metadata changes. Metadata may be null if unchanged since the last callback.
    *
    * Ownership semantics for `frameAVBufferHandle`:
    * - The client receives ownership of the AVBuffer handle when this callback is invoked.
    * - The client is responsible for managing the handle's lifecycle: either passing it to the next
    *   module (e.g., audio sink) or explicitly freeing it via IAVBuffer.free() when no longer needed.
    *
    * End-of-stream delivery:
    * - EOS is signalled on this callback by `metadata.endOfStream = true`. The HAL
    *   delivers it exactly once per decode session, strictly after the final
    *   decoded-frame callback (or, in tunnelled mode, the vendor-internal
    *   consumption of the final audio frame).
    * - On the EOS callback, `metadata` is GUARANTEED to be non-null even though
    *   the parameter is annotated `@nullable`. The general "may be null in
    *   tunnelled mode or if unchanged" rule does NOT apply to the EOS callback —
    *   clients can rely on `metadata != null && metadata.endOfStream` for
    *   unambiguous EOS detection, including in tunnelled mode where
    *   `frameAVBufferHandle = -1` is the normal case.
    * - When `metadata.endOfStream = true`, only that field is authoritative; all
    *   other fields of `FrameMetadata` are undefined and MUST be ignored by the
    *   client. `frameAVBufferHandle` is irrelevant for EOS detection.
    * - See `FrameMetadata.endOfStream` for the full contract.
    *
    * @param[in] nsPresentationTime    The presentation timestamp in nanoseconds, or -1 if only metadata is being returned.
    * @param[in] frameAVBufferHandle   AVBuffer handle to the decoded audio frame buffer. Valid handle in
    *                                   non-tunnelled mode; -1 in tunnelled mode.
    * @param[in] metadata              FrameMetadata for the audio frame. Nullable on routine
    *                                  callbacks (in tunnelled mode or when unchanged); non-null
    *                                  on the EOS callback.
    *
    * @see IAudioDecoderController.decodeBufferWithMetadata(), IAVBuffer.free(),
    *      FrameMetadata.endOfStream
    */
    void onFrameOutput(in long nsPresentationTime, in long frameAVBufferHandle, in @nullable FrameMetadata metadata);

    /**
     * Callback that signals the audio decoder input buffer queue has space again.
     *
     * Fired exactly once per back-pressure episode: when the internal queue transitions
     * from full to has-space after `IAudioDecoderController.decodeBufferWithMetadata()`
     * returned `false`. If the client continues to call `decodeBufferWithMetadata()`
     * during back-pressure (receiving `false` repeatedly), only one callback is
     * delivered per transition, regardless of the number of intermediate `false` returns.
     *
     * The client SHOULD wait for this callback before retrying
     * `decodeBufferWithMetadata()` to avoid wasted binder transactions. Continuing
     * to call it while the queue is full is permitted but will return `false`
     * repeatedly until space is available.
     *
     * Not fired in steady-state operation - only after a refused buffer.
     *
     * @see IAudioDecoderController.decodeBufferWithMetadata()
     */
    void onDecodeBufferAvailable();
}

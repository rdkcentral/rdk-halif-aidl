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
package com.rdk.hal.videocapture;

import com.rdk.hal.videocapture.VideoFrameView;

/**
 *  @brief     Video capture session controller interface.
 *
 *  Returned by `IVideoCapture.open()` and valid until `IVideoCapture.close()`.
 *
 *  <h3>Frame flow</h3>
 *  Each pool buffer is Free, Ready or Locked. The source writes into Free buffers and
 *  marks them Ready when the frame is complete. `acquireLatestFrame()` moves the buffer
 *  due for presentation to Locked and returns it; the source never writes into a Locked
 *  buffer. `releaseFrame()`, or the next `acquireLatestFrame()`, returns a Locked buffer
 *  to Free. A client may hold several buffers Locked at once and release them in any
 *  order.
 *
 *  The frame returned is the one due for presentation now - AV synchronised, with audio
 *  latency and sync correction already applied by the vendor layer. Frames whose
 *  presentation time has passed and which can therefore never be shown are dropped
 *  rather than handed over; frames still in the future stay queued until their time
 *  comes. A client that draws each frame on receipt is in sync without computing
 *  anything.
 *
 *  <h3>Pool depth</h3>
 *  The pool has two parts. The client states how many buffers it will hold Locked at
 *  once, with `setHeldFrames()` - a property of its own rendering pipeline, the same on
 *  every platform. The platform adds the buffers it needs in flight to keep writing at
 *  rate, calibrated from its own memory bandwidth and decode throughput, and reserves
 *  the sum within its video memory. The client never supplies a platform number, and
 *  the platform never guesses the client's pipeline.
 *
 *  Decode proceeds at full rate regardless of how sparsely or slowly the client acquires,
 *  and capture never stalls it. With no Free buffer, a new frame is written over the
 *  oldest Ready one, whose frame is dropped. With every buffer Locked, the new frame is
 *  dropped. Decode, presentation, audio and the clock continue in both cases.
 *
 *  <h3>Buffer addressing</h3>
 *  Every buffer's file descriptors, offsets, strides, size and format are delivered once
 *  at `IVideoCaptureControllerListener.onPoolReady()`, as one `VideoBufferView` per buffer.
 *  A frame therefore carries only its buffer index and presentation time, and a client
 *  resolves it against the pool it already holds.
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 *
 *  @author    Peter Stieglitz
 *  @author    Gerald Weatherup
 */

@VintfStability
interface IVideoCaptureController
{
    /**
     * Sets how many buffers the client will hold Locked at once.
     *
     * A property of the client's own rendering pipeline - a frame being sampled, frames
     * in GPU flight, frames waiting on the consumer's completion - and the same on every
     * platform. It is not the pool depth: the platform adds the buffers it needs in
     * flight to keep writing at rate and sizes the pool from the sum, delivering it at
     * `IVideoCaptureControllerListener.onPoolReady()`.
     *
     * One when not set, which serves a client that releases through
     * `acquireLatestFrame()` as it acquires. A count the platform cannot back within its
     * video memory fails `start()` with `ErrorCode.OUT_OF_MEMORY`.
     *
     * @param[in] heldFrames    The most buffers the client will hold Locked at once.
     *                          One or more.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT If `heldFrames` is less than one.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If the resource is not in the READY state.
     *
     * @pre The resource must be in State::READY.
     *
     * @see start(), acquireLatestFrame()
     */
    void setHeldFrames(in int heldFrames);

    /**
     * Starts the capture session.
     *
     * Reserves the capture pool from the platform's video
     * memory region, sized for the format and frame size this session was configured
     * with, and wires the bound source's decoded output into the pool.
     *
     * The pool is `Capabilities.format`, in buffers of `Capabilities.maxFrameWidth` x
     * `maxFrameHeight`: the `setHeldFrames()` count plus the buffers the platform needs
     * in flight, reserved from its video memory.
     *
     * The capture resource transitions to a `STARTING` state and then a `STARTED` state,
     * and `IVideoCaptureControllerListener.onPoolReady()` is raised once the pool is addressable.
     *
     * Whatever configuration the bound source needs in order to deliver those
     * frames is applied by the vendor layer here, over its own internal path. A client
     * arranges nothing on the decoder.
     *
     * The codec being decoded is checked here rather than at bind time, because a source
     * is opened for a codec independently of when a capture binds to it.
     *
     * A source may already be decoding when this is called. Frames it produced before
     * the session started were discarded, and starting capture may require the vendor
     * layer to reconfigure the decoder, which can interrupt decode visibly for the
     * duration of the reconfiguration. Starting capture before the source starts
     * decoding avoids both.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If the resource is not in the READY state.
     * A failure raised by this call leaves the resource in `READY`; it never entered
     * `STARTING`. A failure found after this call has returned is reported through
     * `IVideoCaptureControllerListener.onCaptureError()` and moves the resource from
     * `STARTING` back to `READY`, with no `onPoolReady()`.
     *
     * @exception binder::Status::Exception::EX_SERVICE_SPECIFIC with an ErrorCode value:
     *            `OUT_OF_MEMORY` if the platform cannot reserve a pool for the held-frame
     *            count plus its own buffers in flight,
     *            `SOURCE_UNAVAILABLE` if the bound sink became unavailable since the bind,
     *            `CODEC_NOT_CAPTURABLE` if the bound source is decoding a codec outside
     *            `Capabilities.supportedCodecs`,
     *            `RESOLUTION_MISMATCH` if the bound source is decoding beyond
     *            `Capabilities.maxFrameWidth` or `maxFrameHeight`,
     *            `PROTECTED_CONTENT` if the bound source is carrying protected content,
     *            `COLOR_CONVERSION_UNSUPPORTED` if `Capabilities.format` requires a colour
     *            conversion of the bound source this capture cannot perform,
     *            `FORMAT_UNSUPPORTED` if `Capabilities.format` cannot be delivered for the
     *            bound source.
     *
     * @pre The resource must be in State::READY.
     *
     * @see stop(), IVideoCaptureControllerListener.onPoolReady()
     */
    void start();

    /**
     * Stops the capture session.
     *
     * Unwires the source from the pool and drops the implementation's references to
     * its Dma-Bufs, and returns when that is done, with the capture resource in the
     * `READY` state. The source's decoder and its plane mapping are left as they are.
     *
     * Buffers still Locked by the client are returned to the free state, so the
     * implementation owes nothing further for them.
     *
     * The client's own references outlive this call. A client received its own
     * duplicated file descriptors at `onPoolReady()`, and an image imported from one
     * holds a reference of its own; a Dma-Buf stays alive while any reference to it
     * does. The memory therefore remains valid for as long as the client holds it,
     * and the client releases it by destroying its imported images and closing those
     * descriptors. Doing so is what returns the memory to the platform.
     *
     * Nothing writes to the pool after this call: the source is unwired, and a later
     * `start()` delivers a new pool in new memory. Every buffer's content is therefore
     * fixed from here, and the client may go on sampling what it imported for as long as
     * it holds its references, or drop them - its choice. The same holds when the
     * session ends through `IVideoCaptureEventListener.onSourceLost()` or
     * `IVideoCaptureControllerListener.onCaptureError()`.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If the resource is not in the STARTED state.
     *
     * @pre The resource must be in State::STARTED.
     *
     * @see start()
     */
    void stop();

    /**
     * Releases the previously acquired buffer and acquires the frame due for presentation.
     *
     * The client may hold up to its `setHeldFrames()` count of buffers Locked at once:
     * passing `VideoFrameView.NO_BUFFER` acquires without releasing, and `releaseFrame()`
     * releases any held buffer, in any order. An acquire that would take the client past
     * that count raises `EX_ILLEGAL_STATE` - the platform reserved buffers for that many,
     * and a client holding more would take the ones it keeps writing into.
     *
     * Release and acquire are one call because a client redrawing at frame rate does
     * both every frame, and two calls would put two binder round trips in a path that
     * runs at 60 Hz.
     *
     * The frame returned is the one due for presentation now. Audio latency and AV-sync
     * correction have already been applied by the vendor layer, so a client that draws
     * it on receipt is in sync. Frames whose presentation time has passed are dropped;
     * frames still in the future stay queued.
     *
     * This function never blocks. It returns null when no frame is due, and never
     * returns a frame it has already returned.
     *
     * @param[in] releaseBufferIndex    A `VideoFrameView.bufferIndex` previously returned
     *                                  by this function, transitioned from Locked to
     *                                  Free before the next frame is acquired. Pass
     *                                  `VideoFrameView.NO_BUFFER` when there is nothing
     *                                  to release, which is the case on the first call
     *                                  of a session. An index that is already Free is
     *                                  ignored, so a repeated release is harmless. An
     *                                  index outside the pool is a client error and
     *                                  raises `EX_ILLEGAL_ARGUMENT` rather than being
     *                                  absorbed, because nothing else would show it.
     *
     * @returns VideoFrameView carrying the buffer index, presentation time and visible
     *          size of the acquired frame, or null if no frame is due.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If the resource is not in the
     *            STARTED state, or the client already holds its `setHeldFrames()` count of
     *            buffers and releases none in this call.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT If `releaseBufferIndex` is neither `VideoFrameView.NO_BUFFER` nor a valid pool index.
     *
     * @pre The resource must be in State::STARTED.
     *
     * @see releaseFrame(), IVideoCaptureControllerListener.onPoolReady()
     */
    @nullable VideoFrameView acquireLatestFrame(in int releaseBufferIndex);

    /**
     * Releases a previously acquired buffer without acquiring another.
     *
     * A client drawing continuously releases through `acquireLatestFrame()` instead, in
     * the same call that takes the next frame. This is for the last frame of a session,
     * for a client that has stopped drawing but still holds a buffer, and for a client
     * holding several buffers that releases them independently.
     *
     * `bufferIndex` must be a `VideoFrameView.bufferIndex` value previously returned by
     * `acquireLatestFrame()`. Releasing a buffer that is already Free returns without
     * raising an exception, so the call is idempotent - including after `stop()`,
     * which has already returned every buffer to Free. An index outside the pool is a
     * client error rather than a repeat release, and raises `EX_ILLEGAL_ARGUMENT` - a
     * client holding an index the pool cannot name has lost track of what it holds, and
     * absorbing that silently is how a stale index survives to release another client's
     * frame.
     *
     * @param[in] bufferIndex   The pool buffer to release.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT If `bufferIndex` is outside the pool.
     *
     * @see acquireLatestFrame()
     */
    void releaseFrame(in int bufferIndex);
}

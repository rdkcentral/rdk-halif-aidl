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
package com.rdk.hal.capture;

import com.rdk.hal.capture.FormatLayout;
import com.rdk.hal.capture.VideoFrameView;
import com.rdk.hal.capture.Property;
import com.rdk.hal.PropertyValue;

/**
 *  @brief     Capture session controller interface.
 *
 *  Returned by `ICapture.open()` and valid until `ICapture.close()`.
 *
 *  <h3>Frame flow</h3>
 *  Each pool buffer is Free, Ready or Locked. The source's decoder writes into Free
 *  buffers and marks them Ready when the frame is complete. `acquireLatestFrame()` moves
 *  the buffer due for presentation to Locked and returns it; the decoder never writes
 *  into a Locked buffer. `releaseFrame()`, or the next `acquireLatestFrame()`, returns a
 *  Locked buffer to Free.
 *
 *  The frame returned is the one due for presentation now - AV synchronised, with audio
 *  latency and sync correction already applied by the vendor layer. Frames whose
 *  presentation time has passed and which can therefore never be shown are dropped
 *  rather than handed over; frames still in the future stay queued until their time
 *  comes. A client that draws each frame on receipt is in sync without computing
 *  anything.
 *
 *  Decode proceeds at full rate regardless of how sparsely or slowly the client acquires.
 *  The behaviour when every buffer is Locked is declared per product in
 *  `CaptureCapabilities.stallsWhenPoolExhausted`.
 *
 *  <h3>Buffer addressing</h3>
 *  Every buffer's file descriptors, offsets, strides, size and format are delivered once
 *  at `ICaptureControllerListener.onPoolReady()`, as one `VideoBufferView` per buffer.
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
interface ICaptureController
{
    /**
     * Starts the capture session.
     *
     * Reserves the capture pool from the platform's video
     * memory region, sized for the format and frame size this session was configured
     * with, and wires the mapped source's decoded output into the pool.
     *
     * A format shall have been selected with `setFormat()` first. There is no default
     * pair, so a session that has selected none has nothing to size a pool for.
     *
     * The capture resource transitions to a `STARTING` state and then a `STARTED` state,
     * and `ICaptureControllerListener.onPoolReady()` is raised once the pool is addressable.
     *
     * Whatever configuration the mapped source's decoder needs in order to deliver those
     * frames is applied by the vendor layer here, over its own internal path. A client
     * arranges nothing on the decoder.
     *
     * The codec being decoded is checked here rather than at `open()`, because a source
     * is opened for a codec independently of when it is mapped to this plane.
     *
     * A source may already be decoding when this is called. Frames it produced before
     * the session started were discarded, and starting capture may require the vendor
     * layer to reconfigure the decoder, which can interrupt decode visibly for the
     * duration of the reconfiguration. Starting capture before the source starts
     * decoding avoids both.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If the resource is not in the READY state.
     * @exception binder::Status::Exception::EX_SERVICE_SPECIFIC with a CaptureErrorCode value:
     *            `OUT_OF_MEMORY` if the pool reservation was refused,
     *            `SOURCE_UNAVAILABLE` if the bound source became unavailable since `open()`,
     *            `CODEC_NOT_CAPTURABLE` if the mapped source is decoding a codec outside
     *            `CaptureCapabilities.supportedCodecs`,
     *            `INVALID_CONFIGURATION` if no format was selected with `setFormat()`,
     *            `RESOLUTION_MISMATCH` if the plane declares `resize` false and the
     *            frame size does not equal the decoded resolution.
     *
     * @pre The resource must be in State::READY.
     *
     * @see setFormat(), stop(), ICaptureControllerListener.onPoolReady()
     */
    void start();

    /**
     * Stops the capture session.
     *
     * Unwires the source from the pool and drops the implementation's references to
     * its Dma-Bufs. The capture resource transitions to a `STOPPING` state and then a
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
     * A frame's CONTENT is fixed only while its buffer is Locked. Once a buffer is
     * released - by `releaseFrame()`, by the next `acquireLatestFrame()`, or by this
     * call - the implementation may write into it again, so a client sampling it
     * beyond that point reads a frame being overwritten. A client that needs a frame
     * to outlive the period it holds the buffer copies it while it still holds it.
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
     * @returns VideoFrameView carrying the buffer index and presentation time of the
     *          acquired frame, or null if no frame is due.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If the resource is not in the STARTED state.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT If `releaseBufferIndex` is neither `VideoFrameView.NO_BUFFER` nor a valid pool index.
     *
     * @pre The resource must be in State::STARTED.
     *
     * @see releaseFrame(), ICaptureControllerListener.onPoolReady()
     */
    @nullable VideoFrameView acquireLatestFrame(in int releaseBufferIndex);

    /**
     * Releases a previously acquired buffer without acquiring another.
     *
     * A client drawing continuously releases through `acquireLatestFrame()` instead, in
     * the same call that takes the next frame. This is for the last frame of a session,
     * and for a client that has stopped drawing but still holds a buffer.
     *
     * `bufferIndex` must be a `VideoFrameView.bufferIndex` value previously returned by
     * `acquireLatestFrame()`. Releasing a buffer that is already Free returns without
     * raising an exception, so the call is idempotent. An index outside the pool is a
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

    /**
     * Selects the pixel format and memory layout the session delivers.
     *
     * Takes one entry of `CaptureCapabilities.supportedFormats`, which pairs a
     * format with a layout valid for it.
     *
     * This is the client's decision. `DRM_FORMAT_MOD_LINEAR` serves a client that
     * touches the pixels - CPU readback, an encoder, or a GPU from another vendor;
     * a vendor-namespaced tiled or compressed layout serves one whose GPU is the
     * same vendor's.
     *
     * A format shall be selected before `start()`. There is no default: what a plane
     * can deliver is whatever it declares, so there is no pair the interface could
     * assume on the client's behalf.
     *
     * @param[in] format : one entry of `CaptureCapabilities.supportedFormats`.
     * @returns boolean : true on success.
     *
     * @pre The resource must be in State::READY.
     *
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT if `format` is not one
     *            of the declared pairs.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if called in a state other
     *            than READY.
     *
     * @see CaptureCapabilities.supportedFormats, FormatLayout
     */
    boolean setFormat(in FormatLayout format);

    /**
     * Sets a property of the capture session.
     *
     * The frame size is set here. A capture is an output in its own right, so it
     * carries its own size rather than taking one from another module's resource.
     *
     * Properties are set in the `READY` state, before `start()`. The pool is built
     * from them, so they are fixed for the life of a running session.
     *
     * @param[in] property      The property to set.
     * @param[in] propertyValue The value to set it to.
     *
     * @returns boolean
     * @retval true     Property was set.
     * @retval false    Value out of range for the resource, or wrong type.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If the session is not in the READY state.
     *
     * @pre The session must be in State::READY.
     *
     * @see ICapture.getProperty(), Property, CaptureCapabilities
     */
    boolean setProperty(in Property property, in PropertyValue propertyValue);

}

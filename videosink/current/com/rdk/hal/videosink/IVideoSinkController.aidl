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
package com.rdk.hal.videosink;
import com.rdk.hal.videodecoder.IVideoDecoder;
import com.rdk.hal.videodecoder.FrameMetadata;
import com.rdk.hal.videosink.Property;
import com.rdk.hal.PropertyValue;
import com.rdk.hal.avclock.IAVClock;

/**
 *  @brief     Video Sink Controller HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *
 *  <h3>AVClock association and video output</h3>
 *  A video sink presents output only when an AVClock is attached and started.
 *  The clock association is owned by the sink — clients call `attachClock()` /
 *  `detachClock()` / `getClock()` on this controller to manage it. The AVClock
 *  itself does not need to be made aware of which sinks present against it.
 *  <ul>
 *  <li><b>No AVClock attached</b> (the default after `open()`, or after
 *      `detachClock()`): the sink does NOT consume frames and does NOT
 *      present output. Frames passed to `queueVideoFrame()` accumulate in the
 *      internal queue until the queue fills, after which `queueVideoFrame()`
 *      returns `false` until queue space becomes available again. Frames
 *      remain in the queue across the no-clock period.</li>
 *  <li><b>AVClock attached and started</b>: the sink consumes queued frames
 *      at the rate dictated by the clock and renders them on the mapped video
 *      plane — AV synchronisation is in effect (lip-synced with any audio
 *      sink presenting against the same clock). If the clock is paused,
 *      consumption pauses with it and the queue will eventually fill.</li>
 *  </ul>
 *  `attachClock()` / `detachClock()` are callable in `READY` or `STARTED` and
 *  do not change the sink's state-machine state. Detaching during `STARTED`
 *  suspends consumption but does not flush the queue or stop the sink.
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 */

@VintfStability
interface IVideoSinkController
{
    /**
     * Sets a property.
     *
     * @param[in] property              The key of a property from the Property enum.
     * @param[in] propertyValue         Holds the value to set.
     *
     * @returns boolean
     * @retval true     The property was successfully set.
     * @retval false    Invalid property key or value.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     *
     *
     * @see getProperty()
     */
    boolean setProperty(in Property property, in PropertyValue propertyValue);

    /**
     * Sets the Video Decoder ID linked to this Video Sink.
     *
     * When the Video Sink is opened, the default is set to `IVideoDecoder.Id.UNDEFINED`.
     * When set to `IVideoDecoder.Id.UNDEFINED` then no Video Decoder source is set.
     *
     * @param[in] videoDecoderId		The ID of the Video Decoder source.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
     * @returns boolean
     * @retval true     The Video Decoder ID was set successfully.
     * @retval false    Invalid Video Decoder ID.
     *
     *
     * @pre The resource must be in State::READY.
     *
     * @see getVideoDecoder(), IVideoDecoderManager.getVideoDecoderIds()
     */
    boolean setVideoDecoder(in IVideoDecoder.Id videoDecoderId);

    /**
     * Gets the Video Decoder ID linked to this Video Sink.
     *
     * @returns IVideoDecoder.Id which can be IVideoDecoder.Id.UNDEFINED.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
     *
     * @pre The resource must be in State::READY or State::STARTED.
     *
     * @see setVideoDecoder()
     */
    IVideoDecoder.Id getVideoDecoder();

    /**
     * Attaches an AVClock to this video sink for AV synchronisation.
     *
     * The sink consumes queued frames and renders them on the mapped video
     * plane only while the attached clock is started. With no clock attached,
     * frames queued via `queueVideoFrame()` accumulate but are not consumed
     * or rendered. See the interface @brief for the full AVClock-association
     * contract.
     *
     * The same AVClock may be attached to multiple sinks (typically one audio
     * sink and one video sink for AV-synchronised playback). The sink owns its
     * clock relationship; the AVClock does not need to be made aware.
     *
     * If a different clock is already attached, this call replaces the
     * attachment. Calling with `IAVClock.Id.UNDEFINED` is equivalent to
     * `detachClock()`.
     *
     * Can be called in `READY` or `STARTED` state. Attaching during `STARTED`
     * causes the sink to begin clock-paced presentation from the next frame
     * once the clock is started; the call does not change the sink's
     * state-machine state.
     *
     * @param[in] clockId   The ID of the AVClock to attach, or
     *                      `IAVClock.Id.UNDEFINED` to detach.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT if `clockId`
     *            does not refer to an existing AVClock instance.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if the sink is
     *            not in `READY` or `STARTED`.
     *
     * @pre The resource must be in State::READY or State::STARTED.
     *
     * @see detachClock(), getClock(), IAVClockManager.getAVClockIds()
     */
    void attachClock(in IAVClock.Id clockId);

    /**
     * Detaches the currently attached AVClock from this video sink.
     *
     * After this call the sink does NOT consume or render further frames
     * until a clock is attached again. Equivalent to calling
     * `attachClock(IAVClock.Id.UNDEFINED)`. See the interface @brief for the
     * full AVClock-association contract.
     *
     * Idempotent: calling when no clock is attached is a no-op.
     *
     * Does not change the sink's state-machine state and does not flush the
     * internal queue — frames already queued remain queued and will be
     * presented once a clock is attached and started.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if the sink is
     *            not in `READY` or `STARTED`.
     *
     * @pre The resource must be in State::READY or State::STARTED.
     *
     * @see attachClock(), getClock()
     */
    void detachClock();

    /**
     * Gets the AVClock ID currently attached to this video sink.
     *
     * @returns IAVClock.Id, which is `IAVClock.Id.UNDEFINED` when no clock is
     *          attached. With no clock attached the sink does not consume or
     *          render output — see the interface @brief.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if the sink is
     *            not in `READY` or `STARTED`.
     *
     * @pre The resource must be in State::READY or State::STARTED.
     *
     * @see attachClock(), detachClock()
     */
    IAVClock.Id getClock();

    /**
	 * Starts the Video Sink.
     *
     * The Video Sink must be in a READY state before it can be started.
     * If successful the Video Sink transitions to a `STARTING` state and then a `STARTED` state.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
     * @pre The resource must be in State::READY.
     *
     * @see stop(), IVideoSink.open()
     */
    void start();

    /**
	 * Stops the Video Sink.
     *
     * The sink enters the `STOPPING` state and then the sink enters the `READY` state.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
     * @pre The resource must be in State::STARTED.
     *
     * @see start(), IVideoSink.close()
     */
    void stop();

    /**
     * Queues a video frame for display.
     *
     * When the presentation time occurs for the video frame the current mapped video plane is used
     * to render the video frame.
     *
     * Consumption is gated by the AVClock attachment — see the interface
     * @brief for the full contract. Summary: the sink consumes queued frames
     * and renders them on the mapped video plane only while an AVClock
     * attached via `attachClock()` is started. With no clock attached (default
     * after `open()` or after `detachClock()`), or with the clock paused, this
     * method accepts frames into the internal queue but the sink does NOT
     * consume or render them; once the queue fills, the method returns `false`
     * until queue space becomes available again.
     *
     * When an AVClock is attached and started, the presentation time of the
     * video frame is controlled by the clock and will be lip-synced with an
     * audio sink presenting against the same clock.
     *
     *
     * Buffer Ownership: Ownership of the buffer transfers to the Video Sink HAL only
     * when `queueVideoFrame()` accepts the buffer (returns true). Once accepted, the HAL is
     * responsible for freeing the buffer after processing. The caller must not modify or
     * access the buffer after a successful call. If the call returns false or throws an
     * exception, ownership remains with the caller.
     *
     *
     * End-of-stream signalling: the client signals EOS by setting
     * `metadata.endOfStream = true` on the final queued frame. Both
     * `frameBufferHandle` and `nsPresentationTime` MUST be valid for the final
     * real frame - the same as for any other frame submitted to this method.
     * The other fields of `FrameMetadata` describe the final frame as normal.
     * The sink shall continue to render all previously queued frames in the
     * usual way and deliver `IVideoSinkControllerListener.onEndOfStream()` once
     * the final frame has been rendered. If a video frame is passed to
     * `queueVideoFrame()` after EOS, then the `binder::Status EX_ILLEGAL_STATE`
     * exception is raised. The video sink must be stopped and restarted or
     * flushed to accept new buffers.
     *
     *
     * @param[in] nsPresentationTime    The presentation time of the video frame in nanoseconds.
     * @param[in] frameBufferHandle     A handle to the video frame buffer.
     * @param[in] metadata              A FrameMetadata object with metadata relating to the video frame.
     *                                  Set `endOfStream = true` on the final queued frame to
     *                                  signal EOS.
     *
     * @returns boolean
     * @retval true  Frame successfully queued for display. Buffer ownership transfers to HAL.
     * @retval false Video sink queue is full. Buffer ownership remains with caller.
     *               The client SHOULD wait for `IVideoSinkControllerListener.onFrameBufferAvailable()`
     *               before retrying, to avoid wasted binder transactions. Continuing to call this
     *               method while the queue is full is permitted but will return `false` repeatedly
     *               until space is available.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT
     *
     * @pre The resource must be in State::STARTED.
     */
    boolean queueVideoFrame(in long nsPresentationTime, in long frameBufferHandle, in FrameMetadata metadata);

    /**
     * Flushes the internal queue of video frames.
     *
     * Once the flush operation has completed the `onFlushComplete()` callback is made to the client.
     *
     * When `holdLastFrame` is set true, the current displayed video frame is held on the display
     * until either a new video frame is presented, a new `flush()` call with `holdLastFrame` set to false is made
     * or the video sink is closed.
     *
     * @param[in] holdLastFrame         If true then the current displayed video frame is held.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
     * @pre The resource must be in State::STARTED.
     *
     * @see discardFramesUntil(), IVideoSinkControllerListener.onFlushComplete()
     */
    void flush(in boolean holdLastFrame);

    /**
     * Sets the earliest presentation time stamp for the Video Sink to display its next frame.
     *
     * The next video frame to display shall be >= `nsPresentationTime` after this call.
     * Any frames in tunnelled or non-tunnelled operational mode which are before this time
     * shall be freed and not displayed.
     *
     * If there is a frame already displayed then it remains displayed until a new frame arrives.
     * The `discardFramesUntil()` function is often used to perform accurate seek operations to a specific presentation
     * time inside a video stream and called after `flush()` with `holdLastFrame` set to true.
     *
     * @param[in] nsPresentationTime    The earliest presentation time of a video frame to display.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
     * @pre The resource must be in State::STARTED.
     *
     * @see flush()
     */
    void discardFramesUntil(in long nsPresentationTime);
}

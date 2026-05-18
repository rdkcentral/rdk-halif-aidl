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
package com.rdk.hal.audiosink;
import com.rdk.hal.audiosink.Volume;
import com.rdk.hal.audiosink.VolumeRamp;
import com.rdk.hal.audiodecoder.IAudioDecoder;
import com.rdk.hal.audiodecoder.FrameMetadata;
import com.rdk.hal.avclock.IAVClock;

/**
 *  @brief     Audio Sink Controller HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *
 *  <h3>AVClock association and audio output</h3>
 *  An audio sink presents output only when an AVClock is attached and started.
 *  The clock association is owned by the sink — clients call `attachClock()` /
 *  `detachClock()` / `getClock()` on this controller to manage it. The AVClock
 *  itself does not need to be made aware of which sinks present against it.
 *  <ul>
 *  <li><b>No AVClock attached</b> (the default after `open()`, or after
 *      `detachClock()`): the sink does NOT produce audio output. Frames passed
 *      to `queueAudioFrame()` accumulate in the internal queue until the queue
 *      fills, after which `queueAudioFrame()` returns `false` until queue
 *      space becomes available again. Frames remain in the queue across the
 *      no-clock period.</li>
 *  <li><b>AVClock attached and started</b>: the sink consumes queued frames
 *      at the rate dictated by the clock — AV synchronisation is in effect.
 *      If the clock is paused, consumption pauses with it and the queue will
 *      eventually fill in the same way as the no-clock state.</li>
 *  </ul>
 *  `attachClock()` / `detachClock()` are callable in `READY` or `STARTED` and
 *  do not change the sink's state-machine state. Detaching during `STARTED`
 *  suspends consumption but does not flush the queue or stop the sink; the
 *  same is true of attaching to a clock that is paused.
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 */

@VintfStability
interface IAudioSinkController {

	/**
	 * Sets the audio decoder ID linked to this audio sink.
     *
     * When the audio sink is opened, the default is set to `IAudioDecoder.Id.UNDEFINED`
	 * which indicates no audio decoder source is set.
	 *
 	 * @param[in] audioDecoderId		The ID of the audio decoder source.
	 *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
     * @returns boolean - true on success or false if the ID is invalid or not IAudioDecoder.Id.UNDEFINED.
     *
     * @pre The resource must be in State::READY.
     *
     * @see getAudioDecoder(), IAudioDecoderManager.getAudioDecoderIds()
	 */
	boolean setAudioDecoder(in IAudioDecoder.Id audioDecoderId);

	/**
	 * Gets the audio decoder ID linked to this audio sink.
	 *
     * @returns IAudioDecoder.Id which can be `IAudioDecoder.Id.UNDEFINED`.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
     * @pre The resource must be in State::READY or State::STARTED.
     *
     * @see setAudioDecoder()
	 */
    IAudioDecoder.Id getAudioDecoder();

    /**
     * Attaches an AVClock to this audio sink for AV synchronisation.
     *
     * The sink consumes and presents queued frames only while the attached
     * clock is started. With no clock attached, frames queued via
     * `queueAudioFrame()` accumulate but are not consumed. See the interface
     * @brief for the full AVClock-association contract.
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
     * causes the sink to begin clock-paced consumption from the next frame
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
     * Detaches the currently attached AVClock from this audio sink.
     *
     * After this call the sink does NOT consume or present further frames
     * until a clock is attached again. Equivalent to calling
     * `attachClock(IAVClock.Id.UNDEFINED)`. See the interface @brief for the
     * full AVClock-association contract.
     *
     * Idempotent: calling when no clock is attached is a no-op.
     *
     * Does not change the sink's state-machine state and does not flush the
     * internal queue — frames already queued remain queued and will be
     * consumed once a clock is attached and started.
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
     * Gets the AVClock ID currently attached to this audio sink.
     *
     * @returns IAVClock.Id, which is `IAVClock.Id.UNDEFINED` when no clock is
     *          attached. With no clock attached the sink does not consume or
     *          present output — see the interface @brief.
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
	 * Starts the audio sink.
     *
     * The audio sink must be in a `READY` state before it can be started.
     * If successful the audio sink transitions to a `STARTING` state and then a `STARTED` state.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
     * @pre The resource must be in State::READY.
     *
     * @see stop(), close()
     */
    void start();

    /**
	 * Stops the audio sink.
     *
     * The sink enters the `STOPPING` state and then the `READY` state.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
     * @pre The resource must be in State::STARTED.
     *
     * @see start()
     */
    void stop();

    /**
     * Queues an audio frame for mixing.
     *
     * The audio sink must be in the `STARTED` state.
     * Buffers can be either non-secure or secure to support SAP (Secure Audio Path).
     * Each call shall reference a single audio frame with a presentation timestamp.
     *
     * Consumption is gated by the AVClock attachment — see the interface
     * @brief for the full contract. Summary: the sink consumes queued frames
     * only while an AVClock attached via `attachClock()` is started. With no
     * clock attached (default after `open()` or after `detachClock()`), or
     * with the clock paused, this method accepts frames into the internal
     * queue but the sink does NOT consume them; once the queue fills, the
     * method returns `false` until queue space becomes available again.
     *
     * The audio sink may also refuse the buffer if its internal resource usage prevents it from accepting it at that time.
     *
     * Buffer Ownership: Ownership of the buffer transfers to the Audio Sink HAL only
     * when `queueAudioFrame()` accepts the buffer (returns true). Once accepted, the HAL is
     * responsible for freeing the buffer after processing. The caller must not modify or
     * access the buffer after a successful call. If the call returns false or throws an
     * exception, ownership remains with the caller.
     *
     * End-of-stream signalling: the client signals EOS by setting
     * `metadata.endOfStream = true` on the final queued frame. Both
     * `bufferHandle` and `nsPresentationTime` MUST be valid for the final real
     * frame - the same as for any other frame submitted to this method. The
     * other fields of `FrameMetadata` describe the final frame as normal. The
     * sink shall continue to mix all previously queued frames in the usual way
     * and deliver `IAudioSinkControllerListener.onEndOfStream()` once the final
     * frame has been completely passed to the mixer. If an audio frame is
     * passed to `queueAudioFrame()` after EOS, then the
     * `binder::Status EX_ILLEGAL_STATE` exception is raised. The audio sink must
     * be stopped and restarted or flushed to accept new buffers.
     *
     * @param[in] nsPresentationTime The presentation time of the audio frame in nanoseconds.
     * @param[in] bufferHandle       A handle to the AV buffer containing the audio frame.
     * @param[in] metadata           A FrameMetadata parcelable describing the audio frame.
     *                               Set `endOfStream = true` on the final queued frame to
     *                               signal EOS.
     *
     * @returns boolean
     * @retval true  Buffer successfully queued for mixing. Buffer ownership transfers to HAL.
     * @retval false Buffer queue is full. Buffer ownership remains with caller.
     *               The client SHOULD wait for `IAudioSinkControllerListener.onFrameBufferAvailable()`
     *               before retrying, to avoid wasted binder transactions. Continuing to call this
     *               method while the queue is full is permitted but will return `false` repeatedly
     *               until space is available.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE    If the resource is not in the `STARTED` state or an audio frame is passed after EOS.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT If an invalid argument is provided.
     *
     * @pre The resource must be in the `STARTED` state.
     */
    boolean queueAudioFrame(in long nsPresentationTime, in long bufferHandle, in FrameMetadata metadata);

    /**
	 * Starts a flush operation on the sink.
     *
     * The audio sink must be in a state of STARTED.
     * Any data buffers that have been passed for mixing but have
     * not yet been processed are freed by the audio sink.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
     * @pre The resource must be in State::STARTED.
     *
     * @see IAudioSinkControllerListener.onFlushComplete()
     */
	void flush();

    /**
     * Gets the current volume for this audio sink.
     *
     * @returns Volume parcelable.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
     * @pre The resource must be in State::READY or State::STARTED.
     */
    Volume getVolume();

    /**
     * Set the audio sink volume level and mute state.
     *
     * @param[in] volume    Volume parcelable.
     *
     * @returns boolean - true if the volume was successfully set or false if the Volume parcelable was invalid.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
     * @pre The resource must be in State::READY or State::STARTED.
     */
    boolean setVolume(in Volume volume);

    /**
     * Set a volume ramp.
     *
	 * The volume ramp operation is set to run over a period of time starting now from the current volume level
     * to the target volume level.  The muted state is unaffected, which means the volume ramp operation
     * continues while muted and can by unmuted at any time.
     *
	 * The VolumeRamp type describes the curve to follow during the ramp.
     *
	 * If any volume ramp is in progress then it is stopped and replaced with this new volume ramp request
	 * and the ramp starts from the interrupted ramp last volume level.
     * When stop() is called, any volume ramp in progress is stopped and the volume is set to targetVolume.
     *
     * @param[in] targetVolume    	    Target volume level at end of ramp.
     * @param[in] overMs    		    The duration of the ramp in milliseconds.
     * @param[in] volumeRamp    	    The curve type for the ramp.
     *
     * @returns boolean - true if the volume ramp is started or false if any parameters are invalid.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
     * @pre The resource must be in State::STARTED.
     */
    boolean setVolumeRamp(in double targetVolume, in int overMs, in VolumeRamp volumeRamp);

}

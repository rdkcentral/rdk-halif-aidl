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

/** 
 *  @brief     Audio Sink Controller HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
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
     * @exception binder::Status EX_ILLEGAL_STATE
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
     * @exception binder::Status EX_ILLEGAL_STATE
     * 
     * @pre The resource must be in State::READY or State::STARTED.
     * 
     * @see setAudioDecoder()
	 */
    IAudioDecoder.Id getAudioDecoder();

    /**
	 * Starts the audio sink.
     * 
     * The audio sink must be in a `READY` state before it can be started.
     * If successful the audio sink transitions to a `STARTING` state and then a `STARTED` state.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
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
     * @exception binder::Status EX_ILLEGAL_STATE 
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
    * Buffers can be either non-secure or secure to support SAP.
    * Each call shall reference a single audio frame with a presentation timestamp.
    * The audio sink may refuse the buffer if its internal resource usage prevents it from accepting it at that time.
    * All buffers passed into `queueAudioFrame()` are the responsibility of the Audio Sink to free once they are
    * no longer required.
    *
    * If an audio frame is passed to `queueAudioFrame()` after EOS, then the `binder::Status EX_ILLEGAL_STATE` exception
    * is raised. The audio sink must be stopped and restarted or flushed to accept new buffers.
    *
    * @param[in] nsPresentationTime The presentation time of the audio frame in nanoseconds.
    * @param[in] bufferHandle       A handle to the AV buffer containing the audio frame.
    * @param[in] metadata           A FrameMetadata parcelable describing the audio frame.
    *
    * @returns boolean
    * @retval true  On success.
    * @retval false If the buffer is full.
    *
    * @exception binder::Status EX_ILLEGAL_STATE    If the resource is not in the `STARTED` state or an audio frame is passed after EOS.
    * @exception binder::Status EX_ILLEGAL_ARGUMENT If an invalid argument is provided.
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
     * @exception binder::Status EX_ILLEGAL_STATE 
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
     * @exception binder::Status EX_ILLEGAL_STATE 
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
     * @exception binder::Status EX_ILLEGAL_STATE 
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
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre The resource must be in State::STARTED.
     */
    boolean setVolumeRamp(in double targetVolume, in int overMs, in VolumeRamp volumeRamp);

}

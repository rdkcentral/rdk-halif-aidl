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
package com.rdk.hal.avclock;
import com.rdk.hal.audiosink.IAudioSink;
import com.rdk.hal.videosink.IVideoSink;
import com.rdk.hal.avclock.ClockMode;
import com.rdk.hal.avclock.ClockTime;

/** 
 *  @brief     AV Clock Controller HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
interface IAVClockController {

    /**
	 * Starts the AV Clock.
     * 
     * The AV Clock must be in a `READY` state before it can be started.
     * If successful the AV Clock transitions to the `STARTING` state and then to the `STARTED` state.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre AV Clock is in State::READY state.
     * 
     * @see stop(), close()
     */
    void start();

    /**
	 * Stops the AV Clock.
     * 
     * The AV Clock enters the `STOPPING` state and then the enters the `READY` state.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre AV Clock is in State::STARTED state.
     * 
     * @see start()
     */
    void stop();

	/**
	 * Sets the primary audio sink for presentation against the AV Clock.
     * 
     * When the AV Clock is opened, the default is set to `IAudioSink.Id.UNDEFINED`.
	 * When set to `IAudioSink.Id.UNDEFINED` then no audio sink is set.  
     * 
 	 * @param[in] audioSinkId				    The ID of the Audio Sink source.
     * 
     * @returns boolean
     * @retval true     Successfully set the audio sink.
     * @retval false    The ID is invalid or not `IAudioSink.Id.UNDEFINED`.
     * 
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre AV Clock is in State::READY or State::STARTED state.
     * 
     * @see getAudioSink()
	 */
	boolean setAudioSink(in IAudioSink.Id audioSinkId);

    /**
     * Gets the primary Audio Sink ID for presentation against the AV Clock.
     * 
     * @returns IAudioSink.Id which can be `IAudioSink.Id.UNDEFINED`.
     * 
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre AV Clock is in State::READY or State::STARTED state.
     * 
     * @see setAudioSink()
     */
    IAudioSink.Id getAudioSink();
    
 	/**
	 * Sets the supplementary Audio Sink ID for presentation against the AV Clock.
     * 
	 * The supplementary Audio Sink is only used for receiver side mixing where
	 * the primary audio and supplementary audio are mixed from 2 separate Audio Sinks.
     * e.g. A primary audio language track and an audio description track.
     * 
     * Both audio tracks sources must be from the same stream sharing a common clock source.
     * Receiver mixing is most commonly found in TV broadcast networks.
	 *
	 * @param[in] supplementaryAudioSinkId	    Supplementary Audio Sink ID source.
     * 
     * @returns boolean
     * @retval true     Successfully set the supplementary audio sink.
     * @retval false    The ID is invalid or not `IAudioSink.Id.UNDEFINED`.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre AV Clock is in State::READY or State::STARTED state.
     * 
     * @see getSupplementaryAudioSink()
	 */
    boolean setSupplementaryAudioSink(in IAudioSink.Id supplementaryAudioSinkId);

    /**
     * Gets the supplementary Audio Sink ID for presentation against the AV Clock.
     * 
     * @returns IAudioSink.Id which can be `IAudioSink.Id.UNDEFINED`.
     * 
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre AV Clock is in State::READY or State::STARTED state.
     * 
     * @see setSupplementaryAudioSink()
     */
    IAudioSink.Id getSupplementaryAudioSink();

	/**
	 * Sets the Video Sink for presentation against the AV Clock.
     * 
     * When the AV Clock is opened, the default is set to `IVideoSink.Id.UNDEFINED`.
	 * When set to `IVideoSink.Id.UNDEFINED` then no video sink is set.  
     * 
 	 * @param[in] videoSinkId				    The ID of the Video Sink source.
     * 
     * @returns boolean
     * @retval true     Successfully set the video sink.
     * @retval false    The ID is invalid or not `IVideoSink.Id.UNDEFINED`.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre AV Clock is in State::READY or State::STARTED state.
     * 
     * @see getVideoSink()
	 */
	boolean setVideoSink(in IVideoSink.Id videoSinkId);

    /**
     * Gets the Video Sink ID for presentation against the AV Clock.
     * 
     * @returns IVideoSink.Id which can be `IVideoSink.Id.UNDEFINED`.
     * 
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre AV Clock is in State::READY or State::STARTED state.
     * 
     * @see setVideoSink()
     */
    IVideoSink.Id getVideoSink();

	/** 
	 * Sets the mode of the AV Clock.
     * 
     * The default mode is `ClockMode::AUTO` and can only be changed in the `READY` state.
 	 *
 	 * @param[in] clockMode		        The AV Clock mode.
  	 *
     * @returns boolean
     * @retval true     Successfully set the clock mode.
     * @retval false    The clock mode is invalid.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre AV Clock is in State::READY state.
     * 
     * @see getClockMode()
     */
	boolean setClockMode(in ClockMode clockMode);

    /**
     * Gets the mode of the AV Clock.
     * 
     * @returns	ClockMode
     * 
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre AV Clock is in State::READY or State::STARTED state.
     * 
     * @see setClockMode()
     */
    ClockMode getClockMode();

	/**
	 * Notifies the AV Clock of a new PCR sample filtered from the broadcast stream.
     * 
	 * When the AV Clock source is set to `ClockMode::PCR` then the client must deliver PCR samples
	 * filtered from the broadcast stream through calls to `notifyPCRSample()`.
     * 
	 * It is important that the sampleTimestamp is recorded as soon as possible when the PCR
	 * is seen in the broadcast stream to reduce sample jitter.
     * 
     * If the AV clock is not `STARTED` or not in `PCR` clock mode then the `binder::Status EX_ILLEGAL_STATE` exception
     * is returned.
	 *
	 * @param[in] pcrTimeNs			    The PCR time converted to nanoseconds.
	 * @param[in] sampleTimestampNs	    CLOCK_MONOTONIC_RAW timestamp in nanoseconds when the PCR sample was received.
   	 *
     * @returns boolean
     * @retval true     Successfully notified the PCR sample.
     * @retval false    One or more invalid parameters.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre AV Clock is in State::STARTED state and in PCR clock mode.
     * 
     * @see setClockMode()
     */
	boolean notifyPCRSample(in long pcrTimeNs, in long sampleTimestampNs);

	/**
	 * Gets the current AV Clock time.
     * 
	 * For `ClockMode::PCR` driven clocks this returns the equivalent of the MPEG system time clock (STC) in nanoseconds units.
     * 
	 * For other clock modes this returns the clock used for presentation of AV frames in the system.
	 *
  	 * @returns ClockTime
	 *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre AV Clock is in State::STARTED state.
     */  
 	ClockTime getCurrentClockTime();

	/**
	 * Sets the playback rate for the AV Clock.
     * 
	 * Not available when `ClockMode::PCR` mode is used.
     * 
     * When the rate is set between 0.5 and 2.0, the AV presentation has audio pitch correction.
     * 
     * The rate 0.0 will pause the playback.
	 *
	 * @param[in] rate      The playback rate.  Default is 1.0 for normal play forward speed.
	 * 
     * @returns boolean
     * @retval true     Successfully set the playback state.
     * @retval false    Invalid rate parameter.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre AV Clock is in State::READY or State::STARTED state and clock mode is not ClockMode::PCR.
     * 
     * @see getPlaybackRate()
     */
    boolean setPlaybackRate(in double rate);

	/**
	 * Gets the playback rate.
     * 
	 * Not valid for `ClockMode::PCR` mode driven clocks, which shall return `binder::Status EX_ILLEGAL_STATE`.
	 *
  	 * @returns double representing the playback rate where 1.0 is normal speed.
	 *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre AV Clock is in State::READY or State::STARTED state and mode is not ClockMode::PCR.
     */  
    double getPlaybackRate();

}

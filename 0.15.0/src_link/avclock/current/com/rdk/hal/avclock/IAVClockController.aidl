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
import com.rdk.hal.avclock.ClockMode;
import com.rdk.hal.avclock.ClockTime;

/** 
 *  @brief     AV Clock Controller HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 */

@VintfStability
interface IAVClockController {

    /**
	 * Starts the AV Clock.
     * 
     * The AV Clock must be in a `READY` state before it can be started.
     * If successful the AV Clock transitions to the `STARTING` state and then to the `STARTED` state.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
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
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     * 
     * @pre AV Clock is in State::STARTED state.
     * 
     * @see start()
     */
    void stop();

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
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
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
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
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
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
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
     * Priming: the AV Clock has a primed/unprimed sub-state inside `STARTED`.
     * Until the clock receives its first priming event for the configured
     * `ClockMode`, it is `STARTED` but unprimed and `getCurrentClockTime()`
     * returns `null`. Once primed, it returns a valid `ClockTime`. Clients
     * that need to react to the priming transition without polling can
     * register for the `IAVClockControllerListener.onPrimed()` callback.
     *
     * Priming source per `ClockMode`:
     * - `ClockMode::PCR`          → first call to `notifyPCRSample()`
     * - `ClockMode::AUDIO_MASTER` → first audio frame PTS received by the linked audio sink
     * - `ClockMode::VIDEO_MASTER` → first video frame PTS received by the linked video sink
     * - `ClockMode::AUTO`         → whichever of the above arrives first, given the configured sources
     *
     * The unprimed → primed transition is one-way per started session;
     * re-priming requires `stop()` followed by `start()`.
	 *
  	 * @returns ClockTime, or `null` if the clock is `STARTED` but not yet primed.
	 *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if the clock is not in `STARTED`.
     *
     *
     * @pre AV Clock is in State::STARTED state.
     *
     * @see IAVClockControllerListener.onPrimed()
     */
 	@nullable ClockTime getCurrentClockTime();

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
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
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
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE
     *
     * 
     * @pre AV Clock is in State::READY or State::STARTED state and mode is not ClockMode::PCR.
     */  
    double getPlaybackRate();

}

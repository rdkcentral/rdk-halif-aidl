/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
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
package com.rdk.hal.farfieldvoice;
 
/**
 *  @brief     Far Field Voice service state definitions.
 *
 *  The service moves CLOSED -> OPENING -> READY on IFarFieldVoice.open() and
 *  READY -> CLOSING -> CLOSED on IFarFieldVoice.close(). Each transition is
 *  notified through IFarFieldVoiceEventListener.onStateChanged().
 *
 *  Values 4 to 7 are unassigned.
 *
 *  @author    Philip Stick
 *  @author    Gary Skrabutenas
 */

@VintfStability
@Backing(type="int")
enum State {
	/**
	 *  The service is initialising, before transitioning to the closed state,
	 *  or the state of the service is unknown.
	 */
    UNKNOWN = 0,

	/**
	 * Initial state entered when the service connection is established.
	 * No client controls the service.
	 */
    CLOSED = 1,

	/**
	 * The service is transitioning from the closed state to the ready state.
	 */
    OPENING = 2,

	/**
	 * The service is open. The IFarFieldVoiceController returned by open() is valid
	 * and audio channels can be opened through it.
	 */
    READY = 3,

	/**
	 * The service is transitioning from the ready state to the closed state.
	 */
    CLOSING = 8
}

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

/** 
 *  @brief     AV clock modes.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
@Backing(type="int")
enum ClockMode {

	/**
	 * AUTO will use AUDIO_MASTER if there is an audio source available otherwise VIDEO_MASTER.
	 * AUTO is the default clock mode after a call to `open()`.
	 */
	AUTO = 0,
	
	/**
	 * Use PCR samples as the clock source as provided in successive calls to `notifyPCRSample()`. 
	 * PCR can only be used on live broadcasts and calls to `setPlaybackRate()` are not allowed.
     * The AV Clock timebase is phase locked to the incoming PCR sample values.
     */
	PCR = 1,

	/** 
	 * Use the audio source as the clock master. 
     * The AV Clock is crash locked to the first audio sample PTS received for playback.
     * The AV Clock timebase is linked to the audio subsystem clock.
     */
	AUDIO_MASTER = 2,

	/** 
	 * Use the video source as the clock master. 
     * The AV Clock is crash locked to the first video frame PTS received for playback.
     * The AV Clock timebase is driven by the vendor implementation.
     */
	VIDEO_MASTER = 3,
}

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
import com.rdk.hal.State;
import com.rdk.hal.avclock.ClockTime;

/** 
 *  @brief     Controller callbacks listener interface from AV Clock.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
oneway interface IAVClockControllerListener {
  
    /**
	 * Callback when the AV Clock has transitioned to a new state.
     *
     * @param[in] oldState	            The state transitioned from.
     * @param[in] newState              The new state transitioned to.
     */
    void onStateChanged(in State oldState, in State newState);

    /**
     * Callback delivered when the AV Clock transitions from `STARTED`-but-unprimed
     * to primed — the first valid clock value is now available. Fires exactly
     * once per started session, ordered after the configured `ClockMode`'s
     * priming event arrives:
     *
     * - `ClockMode::PCR`          → after the first `notifyPCRSample()` call
     * - `ClockMode::AUDIO_MASTER` → after the first audio frame PTS from the linked audio sink
     * - `ClockMode::VIDEO_MASTER` → after the first video frame PTS from the linked video sink
     * - `ClockMode::AUTO`         → after whichever of the above arrives first
     *
     * Until this callback fires, `IAVClockController.getCurrentClockTime()`
     * returns `null`. After it fires, `getCurrentClockTime()` returns valid
     * times for the remainder of the started session. The unprimed → primed
     * transition is one-way per session; re-priming requires `stop()` + `start()`.
     *
     * @param[in] currentClockTime  The first valid clock value, so clients do
     *                              not need to immediately call `getCurrentClockTime()`
     *                              after the callback.
     *
     * @see IAVClockController.getCurrentClockTime()
     * @see IAVClockController.notifyPCRSample()
     * @see ClockMode
     */
    void onPrimed(in ClockTime currentClockTime);
 }

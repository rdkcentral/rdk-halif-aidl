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
import com.rdk.hal.State;
import com.rdk.hal.farfieldvoice.PowerMode;
import com.rdk.hal.farfieldvoice.FailureCode;

/**
 *  @brief     Events callbacks listener interface from Far Field Voice.
 *  @author    Philip Stick
 *  @author    Gary Skrabutenas
 */

@VintfStability
oneway interface IFarFieldVoiceEventListener {

    /**
	 * Callback when Far Field Voice has transitioned to a new state.
     *
     * @param[in] oldState	    The state that the Far Field Voice has transitioned from.
     * @param[in] newState      The new state that the Far Field Voice has transitioned to.
     */
    void onStateChanged(in State oldState, in State newState);

    /**
	 * Callback when Far Field Voice has transitioned to a new power mode.
     */
    void onEnteredPowerMode(in PowerMode powerMode);

    /**
	 * Callback when Far Field Voice has failed.
     *
     * This may be due to a transient hardware error. Closing and reopening
     * the Far Field Voice Service may recover. Repeated errors likely indicates
     * a permanent hardware error. It is useful to log this occurrence for later
     * analysis.
     *
     * @param[in] failureCode	The reason for the failure.
     */
    void onHardwareFailed(in FailureCode failureCode);
}

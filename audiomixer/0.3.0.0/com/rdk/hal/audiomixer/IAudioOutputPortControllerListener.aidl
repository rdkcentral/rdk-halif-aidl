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
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.audiomixer;

import com.rdk.hal.audiomixer.State;

/**
 * @brief    Audio Output Port Controller callback listener.
 * @details  Passed into IAudioOutputPort.open(). Delivers lifecycle state
 *           transitions to the exclusive controller owner. All callbacks are
 *           oneway (non-blocking, fire-and-forget).
 *
 *           Property change events (volume changes, format changes, etc.) are
 *           delivered separately on IAudioOutputPortListener to any registered
 *           observer.
 *
 * @author   Gerald Weatherup
 */
@VintfStability
oneway interface IAudioOutputPortControllerListener {

    /**
     * @brief    Called when the output port transitions to a new lifecycle state.
     *
     *           Fired for all transitions driven by open() and close()
     *           (e.g., CLOSED → OPENING → READY, READY → CLOSING → CLOSED).
     *
     * @param[in] oldState  The state being left.
     * @param[in] newState  The state being entered.
     */
    void onStateChanged(in State oldState, in State newState);
}

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
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.compositeinput;

import com.rdk.hal.compositeinput.SignalStatus;
import com.rdk.hal.compositeinput.State;

/**
 * @brief     Listener interface for composite input controller callbacks.
 * @details   Passed into ICompositeInputPort.open(). Delivers state transitions
 *            and signal status changes to the controller owner.
 *            All callbacks are oneway (non-blocking, fire-and-forget).
 * @author    Gerald Weatherup
 */
@VintfStability
oneway interface ICompositeInputControllerListener {

    /**
     * Called when the port state changes.
     *
     * Fired for all transitions driven by open(), close(), start(), and stop().
     *
     * @param[in] oldState  The state being left.
     * @param[in] newState  The state being entered.
     */
    void onStateChanged(in State oldState, in State newState);

    /**
     * Called when the composite input signal status changes.
     *
     * Always fired at least once during the STARTING transition to indicate
     * the current signal state before STARTED is reached.
     *
     * @param[in] signalStatus  The new signal status.
     */
    void onSignalStatusChanged(in SignalStatus signalStatus);
}

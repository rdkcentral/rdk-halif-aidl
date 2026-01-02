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
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.hdmioutput;

import com.rdk.hal.State;

/**
 *  @brief     Event callbacks listener interface from HDMI output.
 *
 *  This listener is notified of asynchronous lifecycle changes during the operation of
 *  the HDMI output port. It reflects changes to internal state caused by client operations
 *  such as `open()`, `start()`, `stop()`, and `close()`, or internal recovery actions.
 *
 *  Transitions always follow the legal state machine as defined in the HAL interface contract.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */
@VintfStability
oneway interface IHDMIOutputEventListener
{
    /**
     * Callback triggered when the HDMI output changes state.
     *
     * State transitions may be client-driven (e.g., via `open()`, `start()`, `close()`),
     * or HAL-driven (e.g., upon device loss or failure recovery).
     *
     * This callback is always invoked **after** the internal state transition is complete
     * and the resource is stable in its new state. Clients should interpret this as the
     * current, authoritative lifecycle state of the output port.
     *
     * It is valid for this callback to fire multiple times with the same `newState` in
     * the event of reentry or redundant transitions.
     *
     * @param[in] oldState  The state the HDMI output transitioned from.
     * @param[in] newState  The state the HDMI output transitioned to.
     *
     * @see State enum in com.rdk.hal
     * @see IHDMIOutput.open(), IHDMIOutput.close()
     */
    void onStateChanged(in State oldState, in State newState);
}

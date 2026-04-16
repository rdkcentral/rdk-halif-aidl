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
import com.rdk.hal.compositeinput.VideoResolution;

/**
 * @brief     Controller callback listener interface for composite input.
 * @details   Passed into ICompositeInputPort.open(). Delivers real-time A/V
 *            signal events to the exclusive controller owner: connection
 *            detection, signal status, and video mode changes.
 *
 *            State transition events (onStateChanged) are delivered on
 *            ICompositeInputEventListener instead — any observer (including
 *            the controller owner) may register an event listener to observe
 *            port lifecycle without needing exclusive ownership.
 *
 *            All callbacks are oneway (non-blocking, fire-and-forget).
 *
 * @author    Gerald Weatherup
 */
@VintfStability
oneway interface ICompositeInputControllerListener {

    /**
     * Called when the port connection state changes.
     *
     * Fired by hardware detection of cable presence. Indicates physical
     * connection only, not signal validity.
     *
     * Always fires at least once during the OPENING transition to report
     * the current connected/disconnected state before READY is reached.
     *
     * @param[in] connected  True if a cable is now connected, false if disconnected.
     *
     * @see ICompositeInputPort.getStatus()
     */
    void onConnectionChanged(in boolean connected);

    /**
     * Called when the composite input signal status changes.
     *
     * Fired for transitions between signal states
     * (e.g. NO_SIGNAL → UNSTABLE → STABLE).
     *
     * Always fires at least once during the STARTING transition to report
     * the current signal state before STARTED is reached.
     *
     * @param[in] signalStatus  The new signal status.
     *
     * @see SignalStatus, ICompositeInputPort.getStatus()
     */
    void onSignalStatusChanged(in SignalStatus signalStatus);

    /**
     * Called when the detected video mode changes.
     *
     * Fired when the digitized resolution, format, or frame rate changes —
     * typically after initial signal stabilization or when the source device
     * switches video modes.
     *
     * @param[in] resolution  The newly detected video resolution and format.
     *
     * @see VideoResolution, ICompositeInputPort.getStatus()
     */
    void onVideoModeChanged(in VideoResolution resolution);
}

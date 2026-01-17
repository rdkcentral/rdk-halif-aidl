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

import com.rdk.hal.compositeinput.Port;
import com.rdk.hal.compositeinput.SignalStatus;
import com.rdk.hal.compositeinput.VideoResolution;

/**
 * @brief Listener interface for port events.
 *
 * Provides asynchronous callbacks for connection status changes, signal status changes,
 * and video mode changes on a composite input port. Callbacks are delivered via oneway
 * binder calls and do not block the HAL service.
 *
 * Register instances of this interface using ICompositeInputPort.registerEventListener().
 * Multiple listeners can be registered for the same port.
 */
@VintfStability
oneway interface IPortEventListener
{
    /**
     * Callback for port connection status changes.
     *
     * Called when a composite source is physically connected or disconnected from the port.
     * This callback is triggered by hardware detection of cable presence. It does not
     * indicate signal validity, only physical connection state.
     *
     * @param[in] portId     The port ID that changed connection status (0 to maxPorts-1).
     * @param[in] connected  True if a cable is now connected, false if disconnected.
     *
     * @post Clients should call getStatus() to retrieve full port state after connection changes.
     *
     * @see ICompositeInputPort.registerEventListener(), ICompositeInputPort.getStatus()
     */
    void onConnectionChanged(in int portId, in boolean connected);

    /**
     * Callback for signal status changes.
     *
     * Called when the signal status changes (e.g., NO_SIGNAL → UNSTABLE → STABLE,
     * or STABLE → UNSTABLE). This indicates changes in signal detection and stability,
     * which affects whether the port can be activated for presentation.
     *
     * @param[in] portId     The port ID with signal status change (0 to maxPorts-1).
     * @param[in] status     The new signal status.
     *
     * @post If status is STABLE, the port can be activated via setActive(true).
     * @post If status is not STABLE and port was active, it may be automatically deactivated.
     *
     * @see SignalStatus, ICompositeInputPort.setActive(), ICompositeInputPort.getStatus()
     */
    void onSignalStatusChanged(in int portId, in SignalStatus status);

    /**
     * Callback for video mode changes.
     *
     * Called when the detected video resolution, format, or standard changes.
     * This typically occurs after initial signal stabilization or when the
     * source device switches video modes.
     *
     * @param[in] portId        The port ID with video mode change (0 to maxPorts-1).
     * @param[in] resolution    The newly detected video resolution and format information.
     *
     * @pre Signal status should be STABLE before video mode can be reliably detected.
     * @post Resolution information can be used for display configuration.
     *
     * @see VideoResolution, ICompositeInputPort.getStatus()
     */
    void onVideoModeChanged(in int portId, in VideoResolution resolution);
}

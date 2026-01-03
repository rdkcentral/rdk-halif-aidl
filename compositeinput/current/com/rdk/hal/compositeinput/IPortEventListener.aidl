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
 * Callbacks for connection status changes, signal status changes,
 * and video mode changes on a composite input port.
 * 
 * @author Gerald Weatherup
 */
@VintfStability
oneway interface IPortEventListener
{
    /**
     * @brief Callback for port connection status changes.
     * 
     * Called when a composite source is physically connected or disconnected from the port.
     * 
     * @param[in] portId The port ID that changed connection status.
     * @param[in] connected True if connected, false if disconnected.
     */
    void onConnectionChanged(in int portId, in boolean connected);
    
    /**
     * @brief Callback for signal status changes.
     * 
     * Called when the signal status changes (e.g., from unstable to stable,
     * or from no signal to signal detected).
     * 
     * @param[in] portId The port ID with signal status change.
     * @param[in] status The new signal status.
     */
    void onSignalStatusChanged(in int portId, in SignalStatus status);
    
    /**
     * @brief Callback for video mode changes.
     * 
     * Called when the detected video resolution or format changes.
     * This typically occurs after signal stabilization or when the
     * source video format changes.
     * 
     * @param[in] portId The port ID with video mode change.
     * @param[in] resolution The new video resolution and format information.
     */
    void onVideoModeChanged(in int portId, in VideoResolution resolution);
}

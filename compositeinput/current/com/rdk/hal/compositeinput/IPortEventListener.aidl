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

import com.rdk.hal.compositeinput.PortProperty;
import com.rdk.hal.compositeinput.SignalStatus;
import com.rdk.hal.compositeinput.VideoResolution;
import com.rdk.hal.PropertyValue;

/**
 * @brief Listener interface for port events.
 *
 * Provides asynchronous callbacks for connection, signal status, video mode,
 * and property change notifications on a composite input port. Callbacks are
 * delivered via oneway binder calls and do not block the HAL service.
 *
 * Multiple listeners can be registered on the same port via
 * ICompositeInputPort.registerEventListener(). Observers do not need to own
 * the controller — this is the multi-client observation channel for UI,
 * diagnostics, telemetry, and other watchers.
 */
@VintfStability
oneway interface IPortEventListener
{
    /**
     * Callback for port connection state changes.
     *
     * Triggered by hardware detection of cable presence. Indicates physical
     * connection state only, not signal validity.
     *
     * @param[in] connected  True if a cable is now connected, false if disconnected.
     *
     * @see ICompositeInputPort.getStatus()
     */
    void onConnectionChanged(in boolean connected);

    /**
     * Callback for signal status changes.
     *
     * Fired when the signal status transitions between states
     * (e.g. NO_SIGNAL → UNSTABLE → STABLE).
     *
     * @param[in] status  The new signal status.
     *
     * @see SignalStatus, ICompositeInputPort.getStatus()
     */
    void onSignalStatusChanged(in SignalStatus status);

    /**
     * Callback for video mode changes.
     *
     * Fired when the detected video resolution, format, or standard changes.
     * Typically occurs after initial signal stabilization or when the source
     * device switches video modes.
     *
     * @param[in] resolution  The newly detected video resolution and format.
     *
     * @see VideoResolution, ICompositeInputPort.getStatus()
     */
    void onVideoModeChanged(in VideoResolution resolution);

    /**
     * Callback for property value changes.
     *
     * Fired when any runtime property or telemetry metric on this port
     * changes. Clients receive the same PortProperty keys they would read
     * via ICompositeInputPort.getProperty(). Update frequency is
     * implementation-defined; typically bursty for status changes and
     * periodic (1–10 s) for metric counters during active monitoring.
     *
     * @param[in] property  The property key whose value changed.
     * @param[in] value     The new property value.
     *
     * @see PortProperty, ICompositeInputPort.getProperty()
     */
    void onPropertyChanged(in PortProperty property, in PropertyValue value);
}

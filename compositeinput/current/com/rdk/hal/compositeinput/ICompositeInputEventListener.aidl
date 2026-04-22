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
import com.rdk.hal.compositeinput.State;
import com.rdk.hal.PropertyValue;

/**
 * @brief Event listener interface for composite input port observation.
 *
 * Provides asynchronous lifecycle and property callbacks for a composite
 * input port. Callbacks are delivered via oneway binder calls and do not
 * block the HAL service.
 *
 * This is the multi-client observation channel: any client (UI, diagnostics,
 * telemetry, system monitors) may register an event listener without needing
 * to own the controller. Real-time A/V signal events (connection, signal
 * status, video mode) are delivered on ICompositeInputControllerListener
 * instead, exclusively to the controller owner.
 *
 * Multiple listeners may be registered on the same port via
 * ICompositeInputPort.registerEventListener(). Register the listener before
 * calling open() if you need to observe the CLOSED → OPENING → READY
 * transitions.
 */
@VintfStability
oneway interface ICompositeInputEventListener
{
    /**
     * Callback when the port has transitioned to a new state.
     *
     * Fired for all transitions driven by open(), close(), start(), and
     * stop() on any registered event listener.
     *
     * @param[in] oldState  The state that the port has transitioned from.
     * @param[in] newState  The new state that the port has transitioned to.
     *
     * @see State, ICompositeInputPort.getState()
     */
    void onStateChanged(in State oldState, in State newState);

    /**
     * Callback for property value changes.
     *
     * Fired when any runtime property or telemetry metric on this port
     * changes. Listeners receive the same PortProperty keys they would read
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

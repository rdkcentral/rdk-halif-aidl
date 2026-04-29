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
package com.rdk.hal.audiomixer;

import com.rdk.hal.audiomixer.IAudioOutputPortController;
import com.rdk.hal.audiomixer.IAudioOutputPortControllerListener;
import com.rdk.hal.audiomixer.IAudioOutputPortListener;
import com.rdk.hal.audiomixer.OutputPortCapabilities;
import com.rdk.hal.audiomixer.OutputPortProperty;
import com.rdk.hal.audiomixer.State;
import com.rdk.hal.PropertyValue;

/**
 * @brief    Audio Output Port HAL interface.
 * @details  Per-port interface returned by IAudioMixer.getAudioOutputPort().
 *           Provides read access (capabilities, state, property reads) plus
 *           open()/close() to acquire an exclusive IAudioOutputPortController
 *           for property writes.
 *
 *           Lifecycle:
 *             CLOSED → (open) → OPENING → READY → (close) → CLOSING → CLOSED
 *
 *           If the client holding the controller crashes, the HAL implicitly
 *           calls close() to release the port.
 *
 *           Read access (getCapabilities, getProperty, getState, listener
 *           registration) does not require ownership and is available in any
 *           state. Property writes are gated on holding the controller — see
 *           IAudioOutputPortController.setProperty().
 */
@VintfStability
interface IAudioOutputPort {

    /**
     * @brief    Returns this port's static and property capabilities.
     *
     *           Capabilities are immutable for the lifetime of the port.
     *
     * @returns  OutputPortCapabilities describing this port.
     */
    OutputPortCapabilities getCapabilities();

    /**
     * @brief    Gets the current lifecycle state of this output port.
     * @details  Output ports use a subset of the shared State enum:
     *           CLOSED, OPENING, READY, CLOSING. Output ports do NOT enter
     *           STARTING / STARTED / STOPPING / FLUSHING — those values
     *           apply to the mixer instance lifecycle. Audio routing and
     *           emission to the port are driven by the mixer's start/stop;
     *           the port itself only tracks ownership of write access.
     *
     *           The OutputPortProperty.STATE read-only property mirrors this
     *           value for clients accessing it via getProperty().
     *
     * @returns  Current State (CLOSED, OPENING, READY, or CLOSING).
     */
    State getState();

    /**
     * @brief    Gets a property value from this port.
     *
     *           Property reads do not require ownership; they are available
     *           in any state. Property writability and write-state gating are
     *           handled via IAudioOutputPortController.setProperty().
     *
     * @param[in] property  Property key (from OutputPortProperty enum).
     * @returns             Property value.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if the property is not
     *            supported by this port.
     */
    PropertyValue getProperty(in OutputPortProperty property);

    /**
     * @brief    Opens this output port for exclusive property control.
     *
     *           On success the port transitions from CLOSED through OPENING
     *           to READY. The returned IAudioOutputPortController is used to
     *           write properties (volume, mute, output format, etc.).
     *
     *           Only one controller may exist per port at a time. If the
     *           client holding the controller crashes, the HAL implicitly
     *           calls close().
     *
     *           A second open() call on a port already held by another client
     *           throws EX_ILLEGAL_STATE — null is returned only for internal
     *           failures (resource allocation, vendor-specific init errors).
     *
     * @param[in] listener  Listener for controller callbacks (state transitions).
     * @returns   IAudioOutputPortController on success; null on internal/init
     *            failure (port stays in CLOSED state).
     *
     * @exception binder::Status EX_ILLEGAL_STATE if the port is not in CLOSED
     *            state (i.e. another client already holds the controller).
     * @exception binder::Status EX_NULL_POINTER if listener is null.
     *
     * @see close(), IAudioOutputPortController
     */
    @nullable IAudioOutputPortController open(in IAudioOutputPortControllerListener listener);

    /**
     * @brief    Closes this output port and releases the controller.
     *
     *           The port must be in READY state. On success the controller is
     *           invalidated and another client may open() the port.
     *
     * @param[in] controller  The controller instance returned by open().
     * @returns   true on successful close, false if the supplied controller is
     *            not the instance returned by open().
     *
     * @exception binder::Status EX_ILLEGAL_STATE if the port is not in READY state.
     * @exception binder::Status EX_NULL_POINTER if controller is null.
     *
     * @see open()
     */
    boolean close(in IAudioOutputPortController controller);

    /**
     * @brief    Registers a listener for port property change events.
     *
     *           Multiple listeners may be registered. Listener registration
     *           does not require ownership of the controller.
     *
     * @param[in] listener  Listener for property change notifications.
     */
    void registerListener(in IAudioOutputPortListener listener);

    /**
     * @brief    Un-registers a previously registered listener.
     */
    void unregisterListener(in IAudioOutputPortListener listener);
}

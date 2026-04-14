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

import com.rdk.hal.compositeinput.ICompositeInputController;
import com.rdk.hal.compositeinput.ICompositeInputControllerListener;
import com.rdk.hal.compositeinput.IPortEventListener;
import com.rdk.hal.compositeinput.Port;
import com.rdk.hal.compositeinput.PortCapabilities;
import com.rdk.hal.compositeinput.PortProperty;
import com.rdk.hal.compositeinput.PortStatus;
import com.rdk.hal.compositeinput.PropertyKVPair;
import com.rdk.hal.compositeinput.State;
import com.rdk.hal.PropertyValue;

/**
 * @brief     Composite Input Port HAL interface.
 * @details   Provides control and monitoring for a single composite video input port.
 *            State lifecycle is managed via open() / close() on this interface and
 *            start() / stop() on the ICompositeInputController returned by open().
 *
 *            State transitions:
 *              CLOSED → (open) → OPENING → READY → (start) → STARTING → STARTED
 *              STARTED → (stop) → STOPPING → READY → (close) → CLOSING → CLOSED
 *
 *            If the client that opened the controller crashes, stop() and close()
 *            are implicitly called to perform cleanup.
 *
 *            Runtime state and telemetry metrics are both exposed as read-only
 *            PortProperty keys read via getProperty() / getPropertyMulti(). There
 *            is no separate metrics parcelable.
 *
 * @note Video scaling, positioning and aspect-ratio control are intentionally
 *       not exposed on this interface. Composite input video, once presented
 *       via setActive(true), is scaled and positioned by the display pipeline
 *       through the planecontrol HAL (package com.rdk.hal.planecontrol, see
 *       IPlaneControl and its Property enum: X, Y, WIDTH, HEIGHT, ASPECT_RATIO,
 *       OVERSCAN). Clients migrating from the legacy dsCompositeInScaleVideo()
 *       API should configure the video plane via IPlaneControl rather than
 *       looking for an equivalent method on this interface.
 *
 * @author    Gerald Weatherup
 *
 * <h3>Exception Handling</h3>
 * Unless otherwise specified:
 * - Success: returns EX_NONE; all output parameters are valid.
 * - Failure: returns a service-specific exception; output parameters are undefined.
 */
@VintfStability
interface ICompositeInputPort
{
    /**
     * Gets the port ID.
     *
     * @returns Port ID for this port instance (0 to maxPorts-1).
     */
    int getId();

    /**
     * Gets port metadata.
     *
     * Returns constant human-readable metadata. Value does not change between calls.
     *
     * @returns Port parcelable containing port metadata.
     * @see Port
     */
    Port getPortInfo();

    /**
     * Gets the capabilities of this specific port.
     *
     * Returns constant port-specific capabilities. Value does not change between calls.
     *
     * @returns PortCapabilities parcelable.
     * @see PortCapabilities, ICompositeInputManager.getPlatformCapabilities()
     */
    PortCapabilities getCapabilities();

    /**
     * Gets the current state of this port.
     *
     * @returns State enum value.
     * @see ICompositeInputControllerListener.onStateChanged()
     */
    State getState();

    /**
     * Gets the current status of this port.
     *
     * Returns a polled snapshot of connection state, signal status, and detected
     * video mode. Use in conjunction with IPortEventListener for async updates.
     *
     * @returns PortStatus parcelable with current port state.
     * @see PortStatus, IPortEventListener
     */
    PortStatus getStatus();

    /**
     * Gets a property value for this port.
     *
     * PortProperty keys identify both runtime status (e.g. SIGNAL_STRENGTH) and
     * telemetry metrics (e.g. METRIC_SIGNAL_DROPS). Supported keys are declared
     * by the platform in hfp-compositeinput.yaml under ports[].supportedProperties
     * and discoverable via PortCapabilities.supportedProperties.
     *
     * @param[in] property  Property key (from PortProperty enum).
     * @returns PropertyValue, or null if the property is unknown or unavailable.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property is not a valid enum value.
     *
     * @see PortProperty, getPropertyMulti(), ICompositeInputController.setProperty()
     */
    @nullable PropertyValue getProperty(in PortProperty property);

    /**
     * Gets multiple property values in a single call.
     *
     * Efficient batch read. If any property in the array is unknown,
     * EX_ILLEGAL_ARGUMENT is thrown and no values are returned.
     *
     * @param[in] properties  Array of PortProperty enum values to retrieve.
     * @returns Array of PropertyKVPair with keys and values populated;
     *          same length and order as the input array.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if properties is empty or
     *            contains an unknown PortProperty value.
     *
     * @see PropertyKVPair, getProperty()
     */
    PropertyKVPair[] getPropertyMulti(in PortProperty[] properties);

    /**
     * Opens this composite input port for runtime control.
     *
     * On success the port transitions from CLOSED through OPENING to READY.
     * The ICompositeInputControllerListener.onStateChanged() callback is fired
     * for each transition.
     *
     * onSignalStatusChanged() is not fired during OPENING — it is guaranteed
     * during the STARTING transition (driven by ICompositeInputController.start())
     * to report the current signal state before STARTED is reached.
     *
     * The returned ICompositeInputController is used to start/stop the port
     * and mutate properties. If the client that opened the controller crashes,
     * stop() and close() are implicitly called.
     *
     * @param[in] listener  Listener for controller callbacks (state, signal status).
     * @returns ICompositeInputController, or null on failure.
     *
     * @exception binder::Status EX_ILLEGAL_STATE if port is not in CLOSED state.
     * @exception binder::Status EX_NULL_POINTER if listener is null.
     *
     * @see close(), ICompositeInputController, State
     */
    @nullable ICompositeInputController open(in ICompositeInputControllerListener listener);

    /**
     * Closes this composite input port.
     *
     * The port must be in READY state. On success it transitions through
     * CLOSING to CLOSED. onStateChanged() is fired for each transition.
     *
     * @param[in] controller  The ICompositeInputController instance returned by open().
     * @retval true   Successfully closed.
     * @retval false  The supplied controller is not the instance returned by open().
     *
     * @exception binder::Status EX_ILLEGAL_STATE if port is not in READY state.
     * @exception binder::Status EX_NULL_POINTER if controller is null.
     *
     * @see open()
     */
    boolean close(in ICompositeInputController controller);

    /**
     * Registers an event listener for this port.
     *
     * Multiple listeners may be registered. Callbacks are delivered asynchronously
     * via oneway binder calls. Registration does not require the port to be open.
     *
     * Event listeners receive connection, signal status, video mode, and property
     * change notifications.
     *
     * @param[in] listener  The event listener to register.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if listener is null.
     *
     * @see IPortEventListener, unregisterEventListener()
     */
    void registerEventListener(in IPortEventListener listener);

    /**
     * Unregisters a previously registered event listener.
     *
     * @param[in] listener  The event listener to unregister.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if listener is null or not registered.
     *
     * @see registerEventListener()
     */
    void unregisterEventListener(in IPortEventListener listener);
}

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
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.panel;
import com.rdk.hal.panel.Capabilities;
import com.rdk.hal.panel.IPanelOutputController;
import com.rdk.hal.panel.IPanelOutputControllerListener;
import com.rdk.hal.panel.IPanelOutputEventListener;

/** 
 *  @brief     Display Panel Output HAL interface.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 *  - <b>Boolean / ErrorCode results</b>: A returned boolean `false` or a non-success `ErrorCode`
 *    indicates that the call was accepted and processed but could not complete successfully for the
 *    documented reasons. Input validation and invalid controller state are still reported via Binder
 *    exceptions unless a method explicitly documents otherwise.
 */
@VintfStability
interface IPanelOutput
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "PanelOutput";

    /**
     * Gets the capabilities of the panel service.
     *
     * This function can be called at any time and the returned value is not allowed to change between calls.
     *
     * @returns Capabilities parcelable.
     */
    Capabilities getCapabilities();
    
    /**
     * @brief Open this panel output for exclusive control.
     *
        * On success this returns the exclusive IPanelOutputController for the
        * panel output. The controller may already be in any retained lifecycle
        * state, so the client must call `getState()` before deciding whether to
        * start, wait for an in-progress transition, continue with STARTED-state
        * operations, or recover from ERROR.
     *
     * Only one controller may exist at a time. If the owning client crashes,
     * the HAL releases exclusive ownership of the controller but retains the
     * current panel state and the latest stored configuration so a later client
     * can reopen the panel and continue from the existing state.
     *
     * @param listener Listener for exclusive controller callbacks.
     *
        * A client that reopens the panel after the previous controller owner died
        * must call `getState()` on the returned controller and continue from that
        * state rather than assuming the panel has been stopped or reset.
     *
     * @returns IPanelOutputController, or null if the panel output cannot be opened.
     *
     * @exception binder::Status EX_ILLEGAL_STATE if panel output is already open.
     * @exception binder::Status EX_NULL_POINTER if listener is null.
     *
     * Lifecycle state changes are reported through registered
     * `IPanelOutputEventListener` instances.
     *
     * @see close(), IPanelOutputController, registerListener()
     */
    @nullable IPanelOutputController open(in IPanelOutputControllerListener listener);

    /**
     * @brief Close this panel output and release the controller.
     *
     * Accepted from STOPPED or ERROR. From STOPPED this is the normal close
     * path. From ERROR this is the recovery path: after a start() failure
     * (which transitions the panel output to ERROR), the client calls close()
     * to release the controller and the panel output returns to a state where
     * it can be opened again. On success the controller is invalidated and
     * another client may `open()` the panel output.
     *
     * If the panel remains in ERROR after a close()/open()/start() recovery
     * attempt, the platform may require a full device reboot or power cycle to
     * clear latched display hardware. Treat that as a last resort and a
     * platform-specific recovery action rather than a normal API flow.
     *
     * Client death is handled separately from `close()`: the HAL releases the
     * controller ownership automatically, but it does not force the panel back
     * to STOPPED or discard the last stored configuration.
     *
     * If the panel output is in STARTED, STARTING, or STOPPING the call fails
     * with EX_ILLEGAL_STATE - the client must call stop() first (or, from
     * ERROR, close() directly).
     *
     * @param controller The IPanelOutputController instance returned by open().
     *
     * @returns Success flag.
     * @retval true  Successfully closed.
     * @retval false The supplied controller is not the instance returned by open().
     *
     * @exception binder::Status EX_ILLEGAL_STATE if panel output is not in STOPPED or ERROR state.
     * @exception binder::Status EX_NULL_POINTER if controller is null.
     *
     * @see open(), IPanelOutputController.start()
     */
    boolean close(in IPanelOutputController controller);

    /**
     * Registers a callback listener for events generated by the panel output.
     *
     * An `IPanelOutputEventListener` can only be registered once and will fail on subsequent
     * registration attempts.
     *
     * Listener registration is independent of open()/close() and does not require
     * exclusive control of the panel output.
     *
     * @param[in] listener      IPanelOutputEventListener interface.
     *
     * @returns boolean
     * @retval true     The event listener was registered.
     * @retval false    The event listener is already registered.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_NULL_POINTER for a null object.
     *
     * @see unregisterListener(), IPanelOutputEventListener
     */
    boolean registerListener(in IPanelOutputEventListener listener);

    /**
     * Unregisters a callback listener for events generated by the panel output.
     *
     * @param[in] listener      Reference to a previously registered IPanelOutputEventListener interface.
     *
     * @returns boolean
     * @retval true     The event listener was unregistered.
     * @retval false    The event listener was not found registered.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_NULL_POINTER for a null object.
     *
     * @see registerListener(), IPanelOutputEventListener
     */
    boolean unregisterListener(in IPanelOutputEventListener listener);
}

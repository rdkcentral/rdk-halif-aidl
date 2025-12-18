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
package com.rdk.hal.broadcast.frontend;
import com.rdk.hal.broadcast.frontend.Capabilities;
import com.rdk.hal.broadcast.frontend.FrontendType;
import com.rdk.hal.broadcast.frontend.IFrontendListener;
import com.rdk.hal.broadcast.frontend.IFrontendController;
import com.rdk.hal.broadcast.frontend.IFrontendControllerListener;
import com.rdk.hal.State;

/**
 *  @brief     FrontEnd HAL interface.
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 */

@VintfStability
interface IFrontend {

    /** Frontend resource ID type */
    @VintfStability
    parcelable Id {
        /** The undefined ID value. */
        const int UNDEFINED = -1;

        /** The actual resource ID */
        int value;
    }

    /** 
     * Gets the supported frontend types
     *
     * Can be called any time and is not depended o
     *
     * @returns FrontendType array
     */
    FrontendType[] getFrontendTypes();

    /**
     * Get the supported capabilities for the given frontend type
     *
     * @param[in] frontendType The type of capabilites to request
     *
     * @returns Capabilities or null if the type is not supported
     */
    @nullable Capabilities getCapabilities(in FrontendType frontendType);

    /**
	 * Gets the current frontend state.
     *
     * @returns State enum value.
	 *
     * @see IFrontendListener.onStateChanged().
     */  
    State getState();

    /**
	 * Opens the frontend in a mode where it is ready to tune
     * 
     * If successful the frontend transitions to an OPENING state and then a READY state
     * which is notified to any registered `IFrontendListener` interfaces.
     * 
     * Controller related callbacks are made through the `IFrontendControllerListener`
     * passed into the call.
     * 
     * The returned `IFrontendController` interface is used by the client facilitate all tune
     * related operations.
     *
     * If the client that opened the `IFrontEndController` crashes,
     * then the `IFrontEndController` has stop() and close() implicitly called to perform clean up.
     *
     * @param[in] frontendControllerListener    Listener object for controller callbacks.
     *
     * @returns IFrontendController or null on error.
     * 
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre The resource must be in State::CLOSED.
     * 
     * @see IFrontendController, IFrontendController.close(), registerListener()
     */
    @nullable IFrontendController open(in IFrontendControllerListener frontendControllerListener);

    /**
	 * Registers a frontend listener.
     * 
     * A `IFrontendListener` can only be registered once and will fail on subsequent
     * registration attempts.
     *
     * @param[in] frontendListener	    Listener object for event callbacks.
     *
     * @return boolean
     * @retval true     The listener was registered.
     * @retval false    The listener is already registered.
     *
     * @see unregisterListener()
     */
    boolean registerListener(in IFrontendListener frontendListener);

    /**
	 * Unregisters a frontend listener.
     * 
     * @param[in] frontendListener	    Listener object for event callbacks.
     *
     * @return boolean
     * @retval true     The listener was unregistered.
     * @retval false    The listener was not found registered.
     *
     * @see registerListener()
     */
    boolean unregisterListener(in IFrontendListener frontendListener);
}

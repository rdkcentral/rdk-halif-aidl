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
package com.rdk.hal.avclock;
import com.rdk.hal.avclock.Capabilities;
import com.rdk.hal.avclock.IAVClockController;
import com.rdk.hal.avclock.IAVClockControllerListener;
import com.rdk.hal.avclock.IAVClockEventListener;
import com.rdk.hal.avclock.Property;
import com.rdk.hal.PropertyValue;
import com.rdk.hal.State; 

/** 
 *  @brief     AV Clock HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
interface IAVClock 
{

    /** AV Clock resource ID type */
    @VintfStability
    parcelable Id {
        /** The undefined ID value. */
        const int UNDEFINED = -1;

        /** The actual resource ID */
        int value;
    }

    /**
     * Gets the capabilities for this AV Clock.
     * 
     * This function can be called at any time and is not dependant on any AV Clock state.
     * The returned value is not allowed to change between calls.
     *
     * @returns Capabilities parcelable.
     */
    Capabilities getCapabilities();

	/**
	 * Gets the current AV Clock state.
     *
     * @returns State enum value.
     * 
     * @see IAVClockEventListener.onStateChanged(),  IAVClockControllerListener.onStateChanged().
     */  
    State getState();

    /**
     * Gets a property.
     *
     * @param[in] property              The key of a property from the Property enum.
     *
     * @returns PropertyValue or null if property is invalid.
     * 
     * @exception binder::Status EX_NONE for success.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT for invalid property value.
     *
     * @see setProperty()
     */
    @nullable PropertyValue getProperty(in Property property);
 
    /**
     * Sets a property.
     *
     * @param[in] property              The key of a property from the Property enum.
     * @param[in] propertyValue         Holds the value to set.
     *
     * @returns boolean
     * @retval true     Property was successfully set.
     * @retval false    A parameter is invalid.
     *
     * @exception binder::Status EX_NONE for success.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT for invalid parameters. 
     *
     * @see getProperty()
     */
    boolean setProperty(in Property property, in PropertyValue propertyValue);

    /**
	 * Opens the AV Clock.
     * 
     * While the AV Clock is in the `OPENING` state, these defaults are set on the AV Clock:
     *  - Primary audio sink is set to -1
     *  - Supplementary audio sink is set to -1
     *  - Video sink is set to -1
     *  - Mode is set to `ClockMode::AUTO`
     *  - Playback rate is set to 1.0
     * 
     * If successful the AV Clock transitions to the `OPENING` state and then to the `READY` state.
     * If an internal errors occurs, the AV Clock transitions to the `OPENING` state and then back to the `CLOSED` state
     * with a null interface returned.
     *
     * If the client that opened the `IAVClockController` crashes,
     * then the `IAVClockController` has `stop()` and `close()` implicitly called to perform clean up.
     *
     * @param[in] avClockControllerListener		    Listener object for controller callbacks.
     *
     * @returns IAVClockController interface or null on internal error.
     * 
     * @exception binder::Status EX_NONE for success.
     * @exception binder::Status EX_ILLEGAL_STATE If the resource is not in the CLOSED state.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT for invalid parameters.
     * @exception binder::Status EX_NULL_POINTER for Null object.
     * 
     * @pre AV Clock is in State::CLOSED state.
     * 
     * @see close(), IAVClockController
     */
    @nullable IAVClockController open(in IAVClockControllerListener avClockControllerListener);

    /**
     * Closes the AV Clock.
     *
     * The AV Clock must be in a `READY` state before it can be closed.
     * If successful the AV Clock transitions to the `CLOSING` state and then to the `CLOSED` state.
     * `onStateChanged(CLOSING, CLOSED)` will be the last notification received on the `IAVClockControllerListener`.
     *
     * @param[in] avClockController     Instance of IAVClockController.
     *
     * @return boolean
     * @retval true     Successfully closed.
     * @retval false    Invalid state or unrecognised parameter.
     *
     * @exception binder::Status EX_NONE for success.
     * @exception binder::Status EX_ILLEGAL_STATE If instance is not in OPENED State.
     * @exception binder::Status EX_NULL_POINTER for Null object. 
     *
     * @pre AV Clock has been successfully opened and is in the State::READY state.
     *
     * @see open(), IAVClockController
     */
    boolean close(in IAVClockController avClockController);


    /**
	 * Registers an AV Clock event listener.
     * 
     * An `IAVClockEventListener` can only be registered once and will fail on subsequent
     * registration attempts.
     *
     * @param[in] avClockEventListener	    Listener object for event callbacks.
     *
     * @return boolean
     * @retval true     The event listener was registered.
     * @retval false    The event listener is already registered.
     *
     * @exception binder::Status EX_NONE for success.
     * @exception binder::Status EX_NULL_POINTER for Null object.
     *
     * @see unregisterEventListener()
     */
    boolean registerEventListener(in IAVClockEventListener avClockEventListener);

    /**
	 * Unregisters an AV Clock event listener.
     * 
     * @param[in] avClockEventListener	    Listener object for event callbacks.
     *
     * @return boolean
     * @retval true     The event listener was unregistered.
     * @retval false    The event listener was not found registered.
     *
     * @exception binder::Status EX_NONE for success.
     * @exception binder::Status EX_NULL_POINTER for Null object.
     *
     * @see registerEventListener()
     */
    boolean unregisterEventListener(in IAVClockEventListener avClockEventListener);

}

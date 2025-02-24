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
package com.rdk.hal.hdmioutput;
import com.rdk.hal.hdmioutput.Capabilities;
import com.rdk.hal.hdmioutput.IHDMIOutputController;
import com.rdk.hal.hdmioutput.Property;
import com.rdk.hal.hdmioutput.PropertyKVPair;
import com.rdk.hal.hdmioutput.IHDMIOutputControllerListener;
import com.rdk.hal.hdmioutput.IHDMIOutputEventListener;
import com.rdk.hal.PropertyValue;
import com.rdk.hal.State;

/** 
 *  @brief     HDMI Output HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
interface IHDMIOutput 
{

    /** HDMI Output resource ID type */
    @VintfStability
    parcelable Id {
        /** The undefined ID value. */
        const int UNDEFINED = -1;

        /** The actual resource ID */
        int value;
    }

    /**
     * Gets the capabilities for this HDMI output.
     * 
     * This function can be called at any time and is not dependant on any HDMI output state.
     * The returned value is not allowed to change between calls.
     *
     * @returns Capabilities parcelable.
     */
    Capabilities getCapabilities();

    /**
     * Gets a property.
     *
     * @param[in] property              The key of a property from the Property enum.
     *
     * @returns PropertyValue or null if the property key is unknown.
     * 
     * @see setProperty(), getPropertyMulti()
     */
    @nullable PropertyValue getProperty(in Property property);
 
    /**
     * Gets multiple properties.
     *
     * When calling `getPropertyMulti()` the `propertyKVList` parameter contains an array of
     * `PropertyKVPair` parcelables that have their `property` key set.
     * On success the `propertyValue` is set in the returned array.
     * It is an error to pass in an empty array, which results in false being returned.
     * 
     * @param[in,out] propertyKVList        Holds the properties to get and the values on return.
     *
     * @returns boolean - true on success or false if any property keys are invalid.
     * @retval true     The property values were retrieved successfully.
     * @retval false    One or more property keys are invalid or the input array is empty.
     * 
     * @see getProperty()
     */
    boolean getPropertyMulti(inout PropertyKVPair[] propertyKVList);

    /**
	 * Gets the current HDMI output state.
     *
     * @returns State enum value.
	 *
     * @see IHDMIOutputEventListener.onStateChanged().
     */  
    State getState();
 
    /**
	 * Opens the HDMI output port instance.
     * 
     * If successful the HDMI output transitions to an `OPENING` state and then a `READY` state
     * which is notified to any registered `IHDMIOutputEventListener` interfaces.
     * 
     * Controller related callbacks are made through the `IHDMIOutputControllerListener`
     * passed into the call.
     * 
     * The `IHDMIOutputControllerListener.onHotPlugDetectStateChanged()` callback always fires
     * during the `OPENING` state to reflect the current hot plug state.
     * 
     * If the client that opened the `IHDMIOutputController` crashes,
     * then the `IHDMIOutputController.stop()` and `close()` functions are implicitly called to perform clean up.
     *
     * @param[in] hdmiOutputControllerListener    Listener object for controller callbacks.
     *
     * @returns IHDMIOutputController or null if the parameter is invalid.
     * 
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre Resource is in State::CLOSED state.
     * 
     * @see IHDMIOutputController, close(), registerEventListener()
     */
    @nullable IHDMIOutputController open(in IHDMIOutputControllerListener hdmiOutputControllerListener);

    /**
     * Closes the HDMI output.
     *
     * The HDMI output must be in a `READY` state before it can be closed.
     * If successful the HDMI output transitions to a `CLOSING` state and then a `CLOSED` state.
     * Then `onStateChanged(CLOSING, CLOSED)` will be notified on any registered event listener interfaces.
     *
     * The `hdmiOutputController` parameter must be the same instance returned from the `open()` function
     * otherwise `false` is returned.
     *
     * @param[in] hdmiOutputController     Instance of the IHDMIOutputController.
     *
     * @return boolean
     * @retval true     Successfully closed.
     * @retval false    Invalid state or unrecognised parameter.
     *
     * @pre Resource is in State::READY state.
     *
     * @see open()
     */
    boolean close(in IHDMIOutputController hdmiOutputController);

    /**
	 * Registers a HDMI output event listener.
     * 
     * An `IHDMIOutputEventListener` can only be registered once and will fail on subsequent
     * registration attempts.
     *
     * @param[in] hdmiOutputEventListener	    Listener object for event callbacks.
     *
     * @return boolean
     * @retval true     The event listener was registered.
     * @retval false    The event listener is already registered.
     *
     * @see unregisterEventListener()
     */
    boolean registerEventListener(in IHDMIOutputEventListener hdmiOutputEventListener);

    /**
	 * Unregisters a HDMI output event listener.
     * 
     * @param[in] hdmiOutputEventListener	    Listener object for event callbacks.
     *
     * @return boolean
     * @retval true     The event listener was unregistered.
     * @retval false    The event listener was not found registered.
     *
     * @see registerEventListener()
     */
    boolean unregisterEventListener(in IHDMIOutputEventListener hdmiOutputEventListener);
}

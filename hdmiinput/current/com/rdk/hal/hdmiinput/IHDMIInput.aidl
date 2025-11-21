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
package com.rdk.hal.hdmiinput;
import com.rdk.hal.hdmiinput.Capabilities;
import com.rdk.hal.hdmiinput.IHDMIInputController;
import com.rdk.hal.hdmiinput.Property;
import com.rdk.hal.hdmiinput.PropertyKVPair;
import com.rdk.hal.hdmiinput.HDMIVersion;
import com.rdk.hal.hdmiinput.IHDMIInputControllerListener;
import com.rdk.hal.hdmiinput.IHDMIInputEventListener;
import com.rdk.hal.PropertyValue;
import com.rdk.hal.State;

/** 
 *  @brief     HDMI Input HAL interface for a single port.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
interface IHDMIInput 
{

    /** HDMI input resource ID type */
    @VintfStability
    parcelable Id {
        /** The undefined ID value. */
        const int UNDEFINED = -1;

        /** The actual resource ID */
        int value;
    }

    /**
     * Gets the capabilities for this HDMI input port.
     * 
     * This function can be called at any time and is not dependant on any HDMI input state.
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
     * @see IHDMIInputController.setProperty(), getPropertyMulti()
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
     * @returns boolean
     * @retval true     The property values were retrieved successfully.
     * @retval false    One or more property keys are invalid or the input array is empty.
     * 
     * @see getProperty()
     */
    boolean getPropertyMulti(inout PropertyKVPair[] propertyKVList);

    /**
	 * Gets the current HDMI input state.
     *
     * @returns State enum value.
	 *
     * @see IHDMIInputEventListener.onStateChanged().
     */  
    State getState();
 
    /**
     * Sets the EDID for the HDMI input port.
     *
     * Spec Info : CTA 861 standards
     *
     * The EDID defined in `edid` is set for the HDMI input port.
     * The HPD line is toggled if in the `STARTED` state.
     * 
     * The RDK middleware is responsible for providing an EDID that only reflects the
     * known capabilities of this HDMI input port.
     * 
     * @param[in] edid      The EDID data.
     * 
     * @return boolean
     * @retval true         The EDID was set successfully.
     * @retval false        The EDID was not set.
     *
     * @see getEDID(), getCapabilities()
     */
    boolean setEDID(in byte[] edid);

    /**
     * Gets the current EDID set for the HDMI input port.
     *
     * Spec Info : CTA 861 standards
     *
     * The EDID returned in `edid` is set for the HDMI input port.
     *
     * @param[out] edid     The EDID data.
     * 
     * @return boolean
     * @retval true         The EDID was retrieved successfully.
     * @retval false        The EDID was not available.
     *
     * @see setEDID()
     */
    boolean getEDID(out byte[] edid);
    
    /**
     * Gets the default EDID for the HDMI input port for a given HDMI version.
     * 
     * Spec Info : CTA 861 standards
     *
     * A default EDID is defined for each HDMIVersion listed as as supported in the
     * `Capabilities.supportedVersions[]`.
     * 
     * The RDK middleware is expected to set an EDID based on the defined default
     * EDID for a port/version after feature modification.
     *
     * @param[in] version   The HDMI version to retrieve.
     * @param[out] edid     The EDID data.
     *
     * @return boolean
     * @retval true         The EDID was retrieved successfully.
     * @retval false        The EDID was not available.
     *
     * @see setEDID(), getCapabilities()
     */
    boolean getDefaultEDID(in HDMIVersion version, out byte[] edid);

    /**
	 * Opens the HDMI input port instance.
     * 
     * If successful the HDMI input transitions to an `OPENING` state and then a `READY` state
     * which is notified to any registered `IHDMIInputEventListener` interfaces.
     * 
     * Controller related callbacks are made through the `IHDMIInputControllerListener`
     * passed into the call.
     * 
     * The `IHDMIInputControllerListener.onConnectionStateChanged()` callback is always fired during
     * the `OPENING` state to indicate the current connected/disconnected state.
     * 
     * The returned `IHDMIInputController` interface is used to control the HDMI input port interface
     * including starting and stopping the port for display.
     *
     * If the client that opened the `IHDMIInputController` crashes,
     * then the `IHDMIInputController.stop()` and `close()` functions are implicitly called to perform
     * clean up.
     *
     * Once opened to a `READY` state the HDMI input port HPD line is asserted and CEC remains active.
     *
     * @param[in] hdmiInputControllerListener    Listener object for controller callbacks.
     *
     * @returns IHDMIInputController or null if the port cannot be opened - e.g. No EDID set.
     * 
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre The resource must be in State::CLOSED.
     * 
     * @see IHDMIInputController, close(), registerEventListener()
     */
    @nullable IHDMIInputController open(in IHDMIInputControllerListener hdmiInputControllerListener);

    /**
     * Closes the HDMI input.
     *
     * The HDMI input must be in a `READY` state before it can be closed.
     * If successful the HDMI input transitions to a `CLOSING` state and then a `CLOSED` state.
     * Then `onStateChanged(CLOSING, CLOSED)` will be notified on any registered event listener interfaces.
     * 
     * The `hdmiInputController` parameter must be the same instance returned from the `open()` function
     * otherwise `false` is returned.
     * 
     * @param[in] hdmiInputController     Instance of the IHDMIInputController.
     *
     * @return boolean
     * @retval true     Successfully closed.
     * @retval false    Invalid state or unrecognised parameter.
     *
     * @pre The resource must be in State::READY.
     *
     * @see open()
     */
    boolean close(in IHDMIInputController hdmiInputController);

    /**
	 * Registers a HDMI input event listener.
     * 
     * An `IHDMIInputEventListener` can only be registered once and will fail on subsequent
     * registration attempts.
     *
     * @param[in] hdmiInputEventListener	    Listener object for event callbacks.
     *
     * @return boolean
     * @retval true     The event listener was registered.
     * @retval false    The event listener is already registered.
     *
     * @see unregisterEventListener()
     */
    boolean registerEventListener(in IHDMIInputEventListener hdmiInputEventListener);

    /**
	 * Unregisters a HDMI input event listener.
     * 
     * @param[in] hdmiInputEventListener	    Listener object for event callbacks.
     *
     * @return boolean
     * @retval true     The event listener was unregistered.
     * @retval false    The event listener was not found registered.
     *
     * @see registerEventListener()
     */
    boolean unregisterEventListener(in IHDMIInputEventListener hdmiInputEventListener);
}

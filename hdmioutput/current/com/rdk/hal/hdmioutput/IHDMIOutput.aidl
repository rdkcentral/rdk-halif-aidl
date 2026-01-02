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
 *
 *  This interface manages HDMI output resources, including capability queries,
 *  state transitions, and client lifecycle for output control.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
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
     * This function can be called at any time and is not dependent on HDMI output state.
     * The returned value is constant and must not change between calls.
     *
     * @returns Capabilities parcelable.
     */
    Capabilities getCapabilities();

    /**
     * Gets a property value.
     *
     * @param[in] property     The key of a property from the Property enum.
     * @returns PropertyValue or null if the property key is unknown.
     *
     * @see setProperty()
     */
    @nullable PropertyValue getProperty(in Property property);

    /**
     * Gets the current HDMI output state.
     *
     * @returns State enum value.
     *
     * @see IHDMIOutputEventListener.onStateChanged()
     */
    State getState();

    /**
     * Opens the HDMI output port instance.
     *
     * The output transitions to `OPENING` and then to `READY` on success.
     * Callbacks are delivered to the supplied controller listener.
     *
     * The `onHotPlugDetectStateChanged()` callback always fires during the `OPENING` state.
     *
     * If the client crashes, `stop()` and `close()` are called automatically.
     *
     * @param[in] hdmiOutputControllerListener  Listener for controller callbacks.
     * @returns IHDMIOutputController or null if input is invalid.
     *
     * @exception binder::Status EX_ILLEGAL_STATE
     * @pre Must be in State::CLOSED.
     *
     * @see IHDMIOutputController, close(), registerEventListener()
     */
    @nullable IHDMIOutputController open(in IHDMIOutputControllerListener hdmiOutputControllerListener);

    /**
     * Closes the HDMI output.
     *
     * Transitions from `READY` to `CLOSING` to `CLOSED`, notifying listeners via
     * `onStateChanged(CLOSING, CLOSED)`.
     *
     * The supplied controller instance must match the one returned by `open()`.
     *
     * @param[in] hdmiOutputController  Instance from open().
     * @returns boolean
     * @retval true     Successfully closed.
     * @retval false    Invalid state or mismatched instance.
     *
     * @pre Must be in State::READY.
     *
     * @see open()
     */
    boolean close(in IHDMIOutputController hdmiOutputController);

    /**
     * Registers a HDMI output event listener.
     *
     * Only one listener can be registered at a time.
     *
     * @param[in] hdmiOutputEventListener  Listener object.
     * @returns boolean
     * @retval true     Listener registered.
     * @retval false    Already registered.
     *
     * @see unregisterEventListener()
     */
    boolean registerEventListener(in IHDMIOutputEventListener hdmiOutputEventListener);

    /**
     * Unregisters a HDMI output event listener.
     *
     * @param[in] hdmiOutputEventListener  Listener object.
     * @returns boolean
     * @retval true     Listener unregistered.
     * @retval false    Listener not found.
     *
     * @see registerEventListener()
     */
    boolean unregisterEventListener(in IHDMIOutputEventListener hdmiOutputEventListener);
}

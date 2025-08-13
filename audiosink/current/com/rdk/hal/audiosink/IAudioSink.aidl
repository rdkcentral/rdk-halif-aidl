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
package com.rdk.hal.audiosink; 
import com.rdk.hal.audiosink.IAudioSinkController; 
import com.rdk.hal.audiosink.IAudioSinkControllerListener; 
import com.rdk.hal.audiosink.IAudioSinkEventListener; 
import com.rdk.hal.audiosink.Capabilities; 
import com.rdk.hal.audiosink.ContentType;
import com.rdk.hal.audiosink.Property;
import com.rdk.hal.PropertyValue;
import com.rdk.hal.State;

/** 
 *  @brief     Audio Sink HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
interface IAudioSink 
{   

    /** Audio Sink resource ID type */
    @VintfStability
    parcelable Id {
        /** The undefined ID value. */
        const int UNDEFINED = -1;

        /** The actual resource ID */
        int value;
    }

    /**
     * Gets the capabilities for this audio sink.
     * 
     * This function can be called at any time and is not dependant on any audio sink state.
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
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid property value.
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
     * @returns true if the property was successfully set, otherwise false on error.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid parameters.
     * 
     * @see getProperty()
     */
    boolean setProperty(in Property property, in PropertyValue propertyValue);

	/**
	 * Gets the current audio sink state.
     * 
     * @returns State enum value.
     * 
     * @see IAudioSinkEventListener.onStateChanged().
     */  
    State getState();
 
    /**
    * Opens the audio sink.
    *
    * If successful, the audio sink transitions to an OPENING state and then a READY state.
    * The following guarantees are made for an opened audio sink:
    *  - Volume is set to the default of 1.0 and unmuted.
    *  - The linked Audio Decoder is set to IAudioDecoder.Id.UNDEFINED.
    *  - All `Property` values are set to their defaults.
    *
    * If the client that opened the `IAudioSinkController` crashes,
    * then `stop()` and `close()` are implicitly called on the `IAudioSinkController` to perform cleanup.
    *
    * @param[in] contentType                     The content type of the audio sink.
    * @param[in] audioSinkControllerListener     Callback listener for controller events.
    *
    * @returns IAudioSinkController or null On error
    *
    * @exception binder::Status::Exception::EX_NONE for success.
    * @exception binder::Status::Exception::EX_ILLEGAL_STATE If the resource is not in the CLOSED state.
    * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid parameters.
    * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
    *
    * @pre The resource must be in the CLOSED state.
    *
    * @see close()
    */
    @nullable IAudioSinkController open(in ContentType contentType, in IAudioSinkControllerListener audioSinkControllerListener);

    /**
     * Closes the audio sink.
     *
     * The audio sink must be in a READY state before it can be closed.
     * If successful the audio sink transitions to a CLOSING state and then a CLOSED state.
     * onStateChanged(CLOSING, CLOSED) will be notified on any registered IAudioSinkListener interfaces.
     *
     * @param[in] audioSinkController     Instance of the IAudioSinkController.
     * 
     * @return boolean
     * @retval true     Successfully closed.
     * @retval false    Invalid state or unrecognised parameter.
     * 
     * @pre The resource must be in State::READY.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If instance is not in OPENED State.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.     
     *
     * @see open()
     */
    boolean close(in IAudioSinkController audioSinkController);

    /**
	 * Registers an audio sink event listener.
     * 
     * An `IAudioSinkEventListener` can only be registered once and will fail on subsequent
     * registration attempts.
     *
     * @param[in] audioSinkEventListener	    Listener object for event callbacks.
     *
     * @return boolean
     * @retval true     The event listener was registered.
     * @retval false    The event listener is already registered.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     *
     * @see unregisterEventListener()
     */
    boolean registerEventListener(in IAudioSinkEventListener audioSinkEventListener);

    /**
	 * Unregisters an audio sink event listener.
     * 
     * @param[in] audioSinkEventListener	    Listener object for event callbacks.
     *
     * @return boolean
     * @retval true     The event listener was unregistered.
     * @retval false    The event listener was not found registered.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     *
     * @see registerEventListener()
     */
    boolean unregisterEventListener(in IAudioSinkEventListener audioSinkEventListener);
}

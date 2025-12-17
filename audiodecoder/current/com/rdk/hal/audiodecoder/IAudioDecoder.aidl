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
package com.rdk.hal.audiodecoder; 
import com.rdk.hal.audiodecoder.IAudioDecoderControllerListener; 
import com.rdk.hal.audiodecoder.IAudioDecoderEventListener; 
import com.rdk.hal.audiodecoder.IAudioDecoderController; 
import com.rdk.hal.audiodecoder.Capabilities;
import com.rdk.hal.audiodecoder.Property;
import com.rdk.hal.audiodecoder.Codec;
import com.rdk.hal.audiodecoder.Profile;
import com.rdk.hal.audiodecoder.CSDAudioFormat;
import com.rdk.hal.audiodecoder.State;
import com.rdk.hal.PropertyValue;
 
/** 
 *  @brief     Audio Decoder HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
interface IAudioDecoder
{
    /** Audio Decoder resource ID type */
    @VintfStability
    parcelable Id {
        /** The undefined ID value. */    
        const int UNDEFINED = -1;

        /** The actual resource ID */
        int value;
    }


    /**
     * Gets the audio decoder capabilities.
     * 
     * The returned value is not allowed to change between calls.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
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
     * @see setProperty()
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid property value.
     *
     */
    @nullable PropertyValue getProperty(in Property property);
 
	/**
	 * Gets the current state of the audio decoder resource.
     *
     * @returns State enum value.
	 *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @see IAudioDecoderListener.onStateChanged().
     */  
    State getState();

    /**
     * Opens the specified audio decoder resource to decode the requested codec and profile.
     * 
     * On success, the decoder transitions to the `OPENING` state, then the `READY` state. These
     * transitions are notified to registered `IAudioDecoderEventListener` listeners.
     * 
     * If the `secure` flag is set to `true`, but the decoder's reported capabilities (via
     * `IAudioDecoder.getCapabilities().supportsSecure`) are false, this method fails and returns `null`.
     * 
     * A successful call returns an `IAudioDecoderController` instance. This controller interface
     * enables clients to feed audio buffers and control the decoding session.
     * 
     * If the client process that owns the `IAudioDecoderController` crashes or exits unexpectedly,
     * the controller is automatically stopped and closed by the HAL implementation.
     *
     * @param codec                          The codec to configure the decoder for.
     * @param profile                        The profile variant for the selected codec.
     * @param secure                         Whether to enable secure audio path mode.
     * @param audioDecoderControllerListener Listener for controller lifecycle callbacks.
     * 
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If instance is not in CLOSED state.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid parameters.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     *
     * @returns A configured `IAudioDecoderController`, or `null` if the codec/profile or secure
     *          mode is unsupported.
     *
     * @pre Decoder must be in the `CLOSED` state before calling this method.
     *
     * @see IAudioDecoderController, IAudioDecoderController.close(), registerEventListener()
     */
    @nullable IAudioDecoderController open( in Codec codec,
                                            in Profile profile,
                                            in boolean secure,
                                            in IAudioDecoderControllerListener audioDecoderControllerListener );

    /**
     * Closes the audio decoder.
     *
     * The audio decoder must be in a `READY` state before it can be closed.
     * If successful the audio decoder transitions to a `CLOSING` state and then a `CLOSED` state.
     * `onStateChanged(CLOSING, CLOSED)` will be notified on any registered listener interfaces.
     *
     * @param[in] audioDecoderController     Instance of the IAudioDecoderController.
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
    boolean close(in IAudioDecoderController audioDecoderController);

    /**
	 * Registers an audio decoder event listener.
     * 
     * An `IAudioDecoderEventListener` can only be registered once and will fail on subsequent
     * registration attempts.
     *
     * @param[in] audioDecoderEventListener	    Listener object for callbacks.
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
    boolean registerEventListener(in IAudioDecoderEventListener audioDecoderEventListener);

    /**
	 * Unregisters an audio decoder event listener.
     * 
     * @param[in] audioDecoderEventListener	    Listener object for callbacks.
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
    boolean unregisterEventListener(in IAudioDecoderEventListener audioDecoderEventListener);
}

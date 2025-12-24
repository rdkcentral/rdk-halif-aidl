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
	 * Opens the specified audio decoder resource index to decode the specified codec.
     *
     * If successful the audio decoder transitions to an `OPENING` state and then a `READY` state
     * which is notified to any registered `IAudioDecoderEventListener` interfaces.
     *
     * Controller related callbacks are made through the `IAudioDecoderControllerListener`
     * passed into the call.
     *
     * The returned `IAudioDecoderController` interface is used by the client to feed data buffers
     * for decode and manage the decoding flow.
     *
     * If `secure` is requested (true) and the `Capabilties.supportsSecure` is false then the `open()`
     * fails with a null return.
     *
     * If the client that opened the `IAudioDecoderController` crashes,
     * then the `IAudioDecoderController` has `stop()` and `close()` implicitly called to perform clean up.

     * @param[in] codec					            The codec to configure the audio decoder for.
     * @param[in] secure                            The audio decoder secure audio path mode.
     * @param[in] audioDecoderControllerListener    Listener object for controller callbacks.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If instance is not in CLOSED state.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid parameters.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     *
     * @returns IAudioDecoderController or null if the codec or secure is not supported if requested.
     *
     * @pre The resource must be in State::CLOSED.
     *
     * @see IAudioDecoderController, IAudioDecoderController.close(), registerEventListener()
     */
    @nullable IAudioDecoderController open(in Codec codec, in boolean secure, in IAudioDecoderControllerListener audioDecoderControllerListener);

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

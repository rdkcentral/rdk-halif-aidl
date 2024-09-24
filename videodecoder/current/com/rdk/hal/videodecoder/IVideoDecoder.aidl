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
package com.rdk.hal.videodecoder;
import com.rdk.hal.videodecoder.Capabilities;
import com.rdk.hal.videodecoder.IVideoDecoderController;
import com.rdk.hal.videodecoder.Property;
import com.rdk.hal.videodecoder.PropertyKVPair;
import com.rdk.hal.videodecoder.Codec;
import com.rdk.hal.videodecoder.IVideoDecoderControllerListener;
import com.rdk.hal.videodecoder.IVideoDecoderEventListener;
import com.rdk.hal.PropertyValue;
import com.rdk.hal.State;

/** 
 *  @brief     Video Decoder HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
interface IVideoDecoder 
{

    /** Video decoder resource ID type */
    @VintfStability
    parcelable Id {
        /** The undefined ID value. */
        const int UNDEFINED = -1;

        /** The actual resource ID */
        int value;
    }

    /**
     * Gets the capabilities for this Video Decoder.
     * 
     * This function can be called at any time and is not dependant on any Video Decoder state.
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
	 * Gets the current Video Decoder state.
     *
     * @returns State enum value.
	 *
     * @see IVideoDecoderEventListener.onStateChanged().
     */  
    State getState();
 
    /**
	 * Opens the Video Decoder to decode the specified codec.
     * 
     * If successful the Video Decoder transitions to an `OPENING` state and then a `READY` state
     * which is notified to any registered `IVideoDecoderEventListener` interfaces.
     * 
     * Controller related callbacks are made through the `IVideoDecoderControllerListener`
     * passed into the call.
     * 
     * The returned `IVideoDecoderController` interface is used by the client to feed data buffers
     * for decode and manage the decoding flow.
     *
     * If the client that opened the `IVideoDecoderController` crashes,
     * then the `IVideoDecoderController` has `stop()` and `close()` implicitly called to perform clean up.
     *
     * @param[in] codec                             The codec to configure the Video Decoder for.
     * @param[in] secure                            The Video Decoder secure mode.
     * @param[in] videoDecoderControllerListener    Listener object for controller callbacks.
     *
     * @returns IVideoDecoderController or null if the codec or the requested secure mode is not supported.
     * 
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre Resource is in State::CLOSED state.
     * 
     * @see IVideoDecoderController, IVideoDecoderController.close(), registerEventListener()
     */
    @nullable IVideoDecoderController open(in Codec codec, in boolean secure, in IVideoDecoderControllerListener videoDecoderControllerListener);

    /**
     * Closes the Video Decoder.
     *
     * The Video Decoder must be in a `READY` state before it can be closed.
     * If successful the video decoder transitions to a `CLOSING` state and then a `CLOSED` state.
     * Then `onStateChanged(CLOSING, CLOSED)` will be notified on any registered event listener interfaces.
     *
     * @param[in] videoDecoderController     Instance of the IVideoDecoderController.
     *
     * @return boolean
     * @retval true     Successfully closed.
     * @retval false    Invalid state or unrecognised parameter.
     *
     * @pre Resource is in State::READY state.
     *
     * @see open()
     */
    boolean close(in IVideoDecoderController videoDecoderController);

    /**
	 * Registers a Video Decoder event listener.
     * 
     * An `IVideoDecoderEventListener` can only be registered once and will fail on subsequent
     * registration attempts.
     *
     * @param[in] videoDecoderEventListener	    Listener object for event callbacks.
     *
     * @return boolean
     * @retval true     The event listener was registered.
     * @retval false    The event listener is already registered.
     *
     * @see unregisterEventListener()
     */
    boolean registerEventListener(in IVideoDecoderEventListener videoDecoderEventListener);

    /**
	 * Unregisters a Video Decoder event listener.
     * 
     * @param[in] videoDecoderEventListener	    Listener object for event callbacks.
     *
     * @return boolean
     * @retval true     The event listener was unregistered.
     * @retval false    The event listener was not found registered.
     *
     * @see registerEventListener()
     */
    boolean unregisterEventListener(in IVideoDecoderEventListener videoDecoderEventListener);
}

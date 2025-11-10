/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
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
package com.rdk.hal.farfieldvoice;
import com.rdk.hal.farfieldvoice.State;
import com.rdk.hal.farfieldvoice.Capabilities;
import com.rdk.hal.farfieldvoice.Status;
import com.rdk.hal.farfieldvoice.ChannelStatus;
import com.rdk.hal.farfieldvoice.IFarFieldVoiceEventListener;
import com.rdk.hal.farfieldvoice.IFarFieldVoiceController;
import com.rdk.hal.farfieldvoice.IFarFieldVoiceControllerListener;

/**
 *  @brief     Far Field Voice HAL interface.
 *  @author    Philip Stick
 *  @author    Gary Skrabutenas
 */

/**
 *  The Far Field Voice HAL provides a stream of far field audio input to the client
 *  upon detection of a keyword in the audio stream. Following detection of the keyword,
 *  the HAL detects a voice command in the stream and reports it's occurrence to the client.
 *  This stream is referred to as the Keyword channel.
 *
 *  The Far Field Voice HAL also provides a stream of raw microphone data to the client
 *  that is continual in nature. There is no keyword or voice command detection. This stream
 *  is referred to as the Microphones channel.
 *
 *  Multiple clients may obtain information from the service but only one client at a time
 *  may control the service.
 */

@VintfStability
interface IFarFieldVoice
{
    /**
     * Get the capabilities of the Far Field Voice service.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns Capabilities parcelable.
     */
    Capabilities getCapabilities();

	/**
	 * Gets the current state of the Far Field Voice service.
	 *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns State enum value.
	 *
     * @see IFarFieldVoiceEventListener.onStateChanged().
     */
    State getState();

    /**
     * Get the current status of the Far Field Voice service.
	 *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns Status parcelable.
     */
    Status getStatus();

    /**
     * Get the current status of a Far Field Voice channel.
	 *
     * @param[in] channelType       Selected channel type.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT    Invalid channel type.
     *
     * @returns ChannelStatus parcelable or null if the channel type is invalid.
     */
    @nullable ChannelStatus getChannelStatus(in @utf8InCpp String channelType);

    /**
     * Register a Far Field Voice event listener.
     * 
     * An `IFarFieldVoiceEventListener` can only be registered once and will fail on subsequent
     * registration attempts.
     *
     * The listener is notified when a Far Field Voice event occurs.
     *
     * @param[in] farFieldVoiceEventListener    Listener object for callbacks.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     *
     * @return boolean
     * @retval true     The event listener was registered.
     * @retval false    The event listener is already registered.
     *
     * @see unregisterEventListener()
     */
    boolean registerEventListener(in IFarFieldVoiceEventListener farFieldVoiceEventListener);

    /**
     * Unregister a Far Field Voice event listener.
     *
     * @param[in] farFieldVoiceEventListener    Listener object for callbacks.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     *
     * @return boolean
     * @retval true     The event listener was unregistered.
     * @retval false    The event listener was not found registered.
     *
     * @see registerEventListener()
     */
    boolean unregisterEventListener(in IFarFieldVoiceEventListener farFieldVoiceEventListener);

    /**
	 * Open the Far Field Voice service.
     *
     * If successful, the Far Field Voice service transitions to an `OPENING`
     * state and then a `READY` state which is notified to any registered
     * `IFarFieldVoiceEventListener` interface.
     *
     * Controller related callbacks are made through the `IFarFieldVoiceControllerListener`
     * passed into the call.
     *
     * The returned `IFarFieldVoiceController` interface is used by the client
     * to configure and control voice processing. There can only be one client
     * in control of voice processing.
     *
     * If the client that opened the `IFarFieldVoiceController` crashes,
     * then `close()` is implicitly called to perform clean up.
     * 
     * @pre The resource must be in State::CLOSED.
     *
     * @param[in] farFieldVoiceControllerListener   Listener object for controller callbacks.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if instance is not in State::CLOSED state.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     * 
     * @returns IFarFieldVoiceController or null if not in the State::CLOSED state.
     * 
     * @see IFarFieldVoiceController, close(), registerEventListener()
     */
    @nullable IFarFieldVoiceController open(in IFarFieldVoiceControllerListener farFieldVoiceControllerListener);

    /**
     * Close the Far Field Voice service.
     *
     * The Far Field Voice service must be in a `READY` state before it can be
     * closed. If successful the Far Field Voice service transitions to a
     * `CLOSING` state and then a `CLOSED` state.
     * `onStateChanged(CLOSING, CLOSED)` will be notified on any registered
     * listener interface.
     *
     * @pre The resource must be in State::READY.
     *
     * @param[in] farFieldVoiceController    Instance of IFarFieldVoiceController returned by open().
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If instance is not in OPENED State.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     *
     * @return boolean
     * @retval true     Successfully closed.
     * @retval false    Invalid state or unrecognised parameter.
     *
     * @see open()
     */
    boolean close(in IFarFieldVoiceController farFieldVoiceController);
}

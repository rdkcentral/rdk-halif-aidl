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
 package com.rdk.hal.audiomixer;

import com.rdk.hal.audiomixer.Capabilities;
import com.rdk.hal.audiomixer.IAudioMixerController;
import com.rdk.hal.audiomixer.IAudioMixerEventListener;
import com.rdk.hal.audiomixer.IAudioOutputPort;
import com.rdk.hal.audiomixer.Property;
import com.rdk.hal.audiomixer.InputRouting;
import com.rdk.hal.PropertyValue;
import com.rdk.hal.audiodecoder.Codec;

/**
 * @brief Audio Mixer HAL interface.
 *
 * Exposes all mixer functions for the identified resource,
 * including audio routing, output port enumeration, and audio
 * quality (AQ) processor management. Supports both secure and
 * non-secure audio paths. Each instance represents a single mixer.
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 * @copyright Copyright 2024 RDK Management
 */
@VintfStability
interface IAudioMixer {
    /**
     * @brief Mixer resource IDs.
     *
     * MIXER_SYSTEM is always present; additional IDs are vendor/platform defined.
     */
    @Backing(type="int")
    enum Id {
        MIXER_SYSTEM = 0,
        MIX1 = 1,
        MIX2 = 2,
        MIX3 = 3,
        MIX4 = 4,
        MIX5 = 5,
    }

    /**
    * @brief Returns the list of audio output port IDs on this mixer.
    *
    * @return Array of int values representing port IDs.
    */
    int[] getAudioOutputPortIds();

    /**
    * @brief Gets an audio output port interface by ID.
    *
    * Returns null if the port is not supported on this mixer instance.
    *
    * @param id Output port identifier (as int).
    * @return IAudioOutputPort interface or null.
    */
    @nullable IAudioOutputPort getAudioOutputPort(in int id);

    /**
     * @brief Gets the capabilities of this mixer instance.
     *
     * Capabilities include secure path, number/types of supported inputs,
     * and supported content types/codecs per input.
     *
     * @return Capabilities description for the mixer.
     */
    Capabilities getCapabilities();

    /**
     * @brief     Gets a property value from the mixer instance.
     * @param[in] property      The property key (from Property enum).
     * @returns   The current property value.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property not supported.
     */
    PropertyValue getProperty(in Property property);

    /**
     * @brief Opens this mixer instance for runtime control.
     *
     * If successful, the mixer transitions from CLOSED to OPENING and then READY.
     * The returned controller is used to start/stop/flush and manage mixer runtime behaviour.
     *
     * If `secure` is requested (true) and `Capabilities.supportsSecure` is false, open fails
     * with a null return.
     *
     * If the client that opened the controller crashes, `stop()` and `close()` are implicitly
     * called to perform cleanup.
     *
     * @param[in] secure                  The mixer secure audio path mode.
     * @param[in] audioMixerEventListener Listener for state/error/runtime mixer callbacks.
     * @return IAudioMixerController interface, or null on internal/open failure.
     * @exception binder::Status EX_ILLEGAL_STATE if mixer is not in CLOSED state.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if parameters are invalid.
     * @exception binder::Status EX_NULL_POINTER if listener is null.
     * @see close()
     */
    @nullable IAudioMixerController open(in boolean secure, in IAudioMixerEventListener audioMixerEventListener);

    /**
     * @brief Closes this mixer instance.
     *
     * The mixer must be in READY state before it can be closed. On success it transitions
     * to CLOSING and then CLOSED.
     *
     * @param[in] audioMixerController Instance returned by open().
     * @return true on successful close, false for invalid state or unknown controller.
     * @exception binder::Status EX_ILLEGAL_STATE if mixer is not in READY state.
     * @exception binder::Status EX_NULL_POINTER if controller is null.
     * @see open()
     */
    boolean close(in IAudioMixerController audioMixerController);

    /**
    * @brief Registers a listener to receive events from this mixer instance.
    * @param[in] listener Instance of IAudioMixerEventListener to receive callbacks.
    */
    void registerListener(in IAudioMixerEventListener listener);

    /**
     * @brief     Un-registers a previously registered mixer event listener.
     * @param[in] listener   Instance of IAudioMixerEventListener to remove.
     */
    void unregisterListener(in IAudioMixerEventListener listener);

    /**
    * @brief Gets the list of currently active source codecs being mixed.
    *
    * Useful for clients to discover what input formats are currently processed
    * by the mixer for debugging, display, or selection logic.
    *
    * The length and order of the returned array correspond to the current active
    * mixer inputs; each entry matches the input at the same index as returned
    * by capability or enumeration APIs.
    *
    * @return List of codecs for active sources.
    */
    Codec[] getCurrentSourceCodecs();

    /**
     * @brief     Gets the current audio source routing for all mixer inputs.
     * @details   Returns an array with one element for each mixer input (as declared in Capabilities.inputs).
     *            If a mixer input has no source connected, `AudioSourceType.NONE` is indicated.
     *
     * @returns   Array of audio source to mixer tree input routing configurations.
     * @exception binder::Status EX_NONE for success.
     * @see       IAudioMixerController.setInputRouting()
     */
    InputRouting[] getInputRouting();
}

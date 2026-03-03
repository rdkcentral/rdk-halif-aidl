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
     * @brief     Sets the audio source routing for one or more mixer inputs.
     * @details   Allows multiple audio [source -> mixer input] mappings to be configured.
     *            This enables operations such as switching between decoders, routing
     *            HDMI input audio, or connecting application audio to mixer inputs.
     *
     *            Each InputRouting element specifies:
     *            - mixerInputIndex: Which mixer input to configure (from Capabilities.inputs[])
     *            - sourceType/sourceIndex: Which audio source to connect
     *
     *            To disconnect a source from a mixer input, set `sourceType` to `AudioSourceType.NONE`.
     *
     *            Validation:
     *            - If a mixer input index appears multiple times in the routing array, the call fails.
     *            - If a source type and source index appear multiple times in the routing array, the call fails.
     *            - If a mixer input is already mapped to a different source, returns false.
     *
     * @param[in] routing   Array of audio source to mixer input routing configurations.
     * @returns   Success status.
     * @retval true     All routing mappings were successfully applied.
     * @retval false    One or more routing configurations were invalid or conflicted.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if routing array contains invalid values.
     * @exception binder::Status EX_ILLEGAL_STATE if mixer is in a state that prevents routing changes.
     * @see       getInputRouting()
     */
    boolean setInputRouting(in InputRouting[] routing);

    /**
     * @brief     Gets the current audio source routing for all mixer inputs.
     * @details   Returns an array with one element for each mixer input (as declared in Capabilities.inputs).
     *            If a mixer input has no source connected, `AudioSourceType.NONE` is indicated.
     *
     * @returns   Array of audio source to mixer tree input routing configurations.
     * @exception binder::Status EX_NONE for success.
     * @see       setInputRouting()
     */
    InputRouting[] getInputRouting();
}

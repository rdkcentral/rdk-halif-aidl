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

import com.rdk.hal.audiomixer.InputRouting;
import com.rdk.hal.audiomixer.Property;
import com.rdk.hal.PropertyValue;

/**
 * @brief     Audio Mixer Controller HAL interface.
 * @details   Provides stateful and runtime control over a specific platform audio mixer resource.
 *            This includes lifecycle management (start/stop), flushing, signalling end-of-stream,
 *            routing configuration, and property configuration. Intended for use by the
 *            middleware audio server and platform integrators.
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 * @copyright Copyright 2024 RDK Management
 */
@VintfStability
interface IAudioMixerController {

    /**
     * @brief     Sets the audio source routing for one or more inputs on this mixer instance.
     * @details   Allows multiple audio [source -> mixer input] mappings to be configured.
     *            This enables operations such as switching between decoders, routing
     *            HDMI input audio, or connecting application audio to mixer inputs.
     *
     *            The target mixer input is defined by the array position:
     *            - routing[0] configures mixer input 0
     *            - routing[1] configures mixer input 1
     *            - etc.
     *
     *            Each InputRouting element specifies sourceType/sourceIndex for that input.
     *
     *            To disconnect a source from a mixer input, set `sourceType` to `AudioSourceType.NONE`.
     *
     *            Validation:
     *            - If a source type and source index appear multiple times in the routing array, the call fails.
     *            - If a mixer input is already mapped to a different source, returns false.
     *
     * @param[in] routing   Array of audio source to mixer input routing configurations.
     * @returns   Success status.
     * @retval true     All routing mappings were successfully applied.
     * @retval false    One or more routing configurations were invalid or conflicted.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if routing array contains invalid values.
     * @exception binder::Status EX_ILLEGAL_STATE if mixer is in a state that prevents routing changes.
     * @see       IAudioMixer.getInputRouting()
     */
    boolean setInputRouting(in InputRouting[] routing);

    /**
     * @brief     Sets a property on the controlled mixer instance.
     * @param[in] property      The property key (from Property enum).
     * @param[in] propertyValue The value to set (PropertyValue union).
     * @returns   true if successfully set, false otherwise.
     * @see       IAudioMixer.getProperty()
     */
    boolean setProperty(in Property property, in PropertyValue propertyValue);

    /**
     * @brief     Starts audio mixing for this mixer instance.
     * @details   The mixer transitions to the STARTED state and processes configured audio inputs and outputs.
     * @exception binder::Status EX_ILLEGAL_STATE if already started or not ready.
     * @pre       The mixer must be in READY state.
     * @see       stop(), flush()
     */
    void start();

    /**
     * @brief     Stops audio mixing for this mixer instance.
     * @details   The mixer transitions through STOPPING to READY state, ceasing output and freeing any buffered resources.
     * @exception binder::Status EX_ILLEGAL_STATE if not started.
     * @pre       The mixer must be in STARTED state.
     * @see       start(), flush()
     */
    void stop();

    /**
     * @brief     Flushes the mixer, discarding all buffered audio data.
     * @param[in] reset   When true, resets internal state to READY; when false, retains configuration but flushes data.
     * @exception binder::Status EX_ILLEGAL_STATE if not started.
     * @pre       The mixer must be in STARTED state.
     */
    void flush(in boolean reset);

    /**
     * @brief     Signals a stream discontinuity in the mixer pipeline.
     * @details   Used when a break or change in input PTS or format occurs, such as switching sources or seeking.
     * @exception binder::Status EX_ILLEGAL_STATE if not started.
     * @pre       The mixer must be in STARTED state.
     */
    void signalDiscontinuity();

    /**
     * @brief     Signals end-of-stream for all active mixer inputs.
     * @details   After all buffered frames are processed, the mixer drains remaining data
     *            and transitions through STOPPING to READY state.
     * @exception binder::Status EX_ILLEGAL_STATE if not started.
     * @pre       The mixer must be in STARTED state.
     */
    void signalEOS();

    /**
     * @brief     Sets the volume level for a specific mixer input.
     * @details   Allows per-input attenuation for use cases such as TTS overlay,
     *            system sound mixing, or audio description level adjustment.
     *
     *            The input index corresponds to the mixer input as declared in
     *            Capabilities.inputs (e.g., 0 = main, 1 = assoc, 2 = pcm1).
     *
     * @param[in] inputIndex  Mixer input index (0-based, matching Capabilities.inputs).
     * @param[in] volume      Volume level in range 0..100 (0 = silent, 100 = full).
     *
     * @returns   true if the volume was set, false if the input index is invalid.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if volume is outside 0..100 range.
     * @exception binder::Status EX_ILLEGAL_STATE if mixer is not in READY or STARTED state.
     * @pre       The mixer must be in READY or STARTED state.
     * @see       getInputVolume()
     */
    boolean setInputVolume(in int inputIndex, in int volume);

    /**
     * @brief     Gets the current volume level for a specific mixer input.
     *
     * @param[in] inputIndex  Mixer input index (0-based, matching Capabilities.inputs).
     *
     * @returns   Current volume level in range 0..100.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if inputIndex is invalid.
     * @see       setInputVolume()
     */
    int getInputVolume(in int inputIndex);
}

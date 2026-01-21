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

import com.rdk.hal.audiomixer.Property;
import com.rdk.hal.PropertyValue;
import com.rdk.hal.audiomixer.IAudioMixerControllerListener;

/**
 * @brief     Audio Mixer Controller HAL interface.
 * @details   Provides stateful and runtime control over a specific platform audio mixer resource.
 *            This includes lifecycle management (start/stop), flushing, signaling end-of-stream,
 *            property configuration, and event listener management. Intended for use by the
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
     * @brief     Sets a property on the controlled mixer instance.
     * @param[in] property      The property key (from Property enum).
     * @param[in] propertyValue The value to set (PropertyValue union).
     * @return    true if successfully set, false otherwise.
     * @see       getProperty()
     */
    boolean setProperty(in Property property, in PropertyValue propertyValue);

    /**
     * @brief     Gets a property value from the controlled mixer instance.
     * @param[in] property      The property key (from Property enum).
     * @return    The current property value.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property not supported.
     * @see       setProperty()
     */
    PropertyValue getProperty(in Property property);

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
     * @details   The mixer enters the STOPPED state, ceasing output and freeing any buffered resources.
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
     * @details   After all buffered frames are processed, the mixer transitions to an EOS state.
     * @exception binder::Status EX_ILLEGAL_STATE if not started.
     * @pre       The mixer must be in STARTED state.
     */
    void signalEOS();

    /**
    * @brief Registers a listener to receive events from this mixer instance.
    * @param[in] listener Instance of IAudioMixerEventListener to receive callbacks.
    */
    void registerListener(in IAudioMixerEventListener listener);

    /**
     * @brief     Unregisters a previously registered mixer event listener.
     * @param[in] listener   Instance of IAudioMixerEventListener to remove.
     */
    void unregisterListener(in IAudioMixerEventListener listener);
}

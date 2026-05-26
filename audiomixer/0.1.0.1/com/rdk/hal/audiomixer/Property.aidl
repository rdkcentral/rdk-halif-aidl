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

/**
 * @brief    Audio Mixer properties used in property get/set functions.
 *           All properties can be read in any state unless otherwise noted.
 * @author   Luc Kennedy-Lamb
 * @author   Peter Stieglitz
 * @author   Douglas Adler
 */
@VintfStability
@Backing(type="int")
enum Property {
    /**
     * Current latency of the mixer in milliseconds.
     *
     * Type: Integer
     * Access: Read-only.
     */
    LATENCY_MS = 0,

    /**
     * Enables or disables debug tap output for audio analysis.
     *
     * Type: Boolean
     * Access: Read-write.
     * Writeable in states: READY
     */
    DEBUG_TAP_ENABLED = 1,

    /**
     * Gets or sets the currently active AQ (Audio Quality) profile or preset.
     *
     * Type: String
     * Access: Read-write
     * Writeable States: READY, STARTED
     *
     * The value must correspond to a named AQ parameter configuration supported
     * by the system. These profiles internally control one or more parameters
     * defined in @see AQParameter, such as DIALOGUE_ENHANCER, BASS_ENHANCER_GAIN,
     * or GRAPHIC_EQUALIZER.
     *
     * Example values: "DIALOGUE_ENHANCER", "GRAPHIC_EQUALIZER", "SURROUND_VIRTUALIZER"
     *
     * @see com.rdk.hal.audiomixer.AQParameter
     */
    ACTIVE_AQ_PROFILE = 2,

    /**
    * Mixer operating mode (e.g., NORMAL, DUCKED).
    *
    * Designed for runtime changes in response to policy or stream priority.
    * TODO: Future Expansion
    *
    * Type: MixingMode (Enum) @see com.rdk.hal.audiomixer.MixingMode
    * Access: Read-write.
    * Writeable in states: READY, STARTED
    *
    * @see MixingMode
    */
    MIXING_MODE = 3,

    /**
     * Mute state for the mixer output path.
     *
     * Type: Boolean
     * Access: Read-write.
     * Writeable in states: READY, STARTED
     * - false: unmuted (default on open)
     * - true: muted
     */
    MUTE = 4
}

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
 * @brief    Enumerates extensible property keys for Audio Output Port.
 * @details  Used as the key in setProperty/getProperty and onPropertyChanged for 
 *           forward-compatible and vendor-specific configuration. 
 *           All properties can be read in any state unless otherwise specified.
 *
 * Each property must be documented with:
 *   - Value type (int, boolean, int[], etc.)
 *   - Access (Read-only, Read-write)
 *   - Writeable in states (READY, ENABLED, etc.)
 *   - Value semantics (enum, range, etc.)
 *
 * @author   Luc Kennedy-Lamb
 * @author   Peter Stieglitz
 * @author   Douglas Adler
 * @copyright Copyright 2024 RDK Management
 */
@VintfStability
@Backing(type="int")
enum OutputPortProperty {
    /**
     * Output port volume.
     * Type: int
     * Range: 0..100
     * Access: Read-write.
     * Writeable in states: ENABLED
     */
    VOLUME = 0,

    /**
     * Output port audio delay in milliseconds.
     * Type: int
     * Range: Implementation-dependent.
     * Access: Read-write.
     * Writeable in states: ENABLED
     */
    DELAY_MS = 1,

    /**
     * Output port mute state.
     * Type: boolean
     * Access: Read-write.
     * Writeable in states: ENABLED
     */
    MUTE = 2,

    /**
     * Output port enabled/disabled state.
     * Type: boolean
     * Access: Read-write.
     * Writeable in states: Any except CLOSED
     */
    ENABLED = 3,

    /**
     * Configured output audio format.
     * Type: int (AudioOutputFormat enum value)
     * Access: Read-write.
     * Writeable in states: READY, ENABLED
     */
    OUTPUT_FORMAT = 4,

    /**
     * Supported audio output formats.
     * Type: int[] (com.rdk.hal.audiosink.AudioOutputFormat enum values)
     * Access: Read-only.
     */
    SUPPORTED_AUDIO_FORMATS = 5,

    /**
     * True if Dolby Atmos is supported on this output port.
     * Type: boolean
     * Access: Read-only.
     */
    DOLBY_ATMOS_SUPPORT = 6,

    /**
     * Output port logical state.
     * Type: int (@see com.rdk.hal.audiomixer.State enum)
     * Access: Read-only.
     */
    STATE = 7,

    /**
    * Audio transcoding output format.
    * Type: int (TranscodeFormat enum @see com.rdk.hal.audiomixer.TranscodeFormat)
    * Access: Read-write.
    * Writeable in states: READY
    */
    TRANSCODE_FORMAT = 8,

    /**
     * Physical/logical connection state.
     * Type: int (@see com.rdk.hal.audiomixer.ConnectionState enum)
     * Access: Read-only.
     */
    CONNECTION_STATE = 9,

    /**
    * Select active AQ processor instance.
    * Type: int (AQProcessor enum @see com.rdk.hal.audiomixer.AQProcessor)
    * Access: Read-write.
    * Writeable in states: READY
    */
    AQ_PROCESSOR_ID = 10,

    /**
     * Vendor-specific extension.
     * Type: Implementation-defined.
     * Access: Read-write or read-only as documented.
     */
    VENDOR_EXTENSION = 1000
}

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
 * Used as the key in setProperty/getProperty and onPropertyChanged for 
 *           forward-compatible and vendor-specific configuration. 
 *           All properties can be read in any state unless otherwise specified.
 *
 * Each property must be documented with:
 *   - Value type (int, boolean, int[], etc.)
 *   - Access (Read-only, Read-write)
 *   - Writeable in states (READY, STARTED, etc.)
 *   - Value semantics (enum, range, etc.)
 *
 * @author   Luc Kennedy-Lamb
 * @author   Peter Stieglitz
 * @author   Douglas Adler
 */
@VintfStability
@Backing(type="int")
enum OutputPortProperty {
    /**
     * Output port volume.
     * Type: int
     * Range: 0..100
     * Access: Read-write.
     * Writeable in states: READY, STARTED
     */
    VOLUME = 0,

    /**
     * Output port audio delay in milliseconds.
     * Type: int
     * Range: Implementation-dependent.
     * Access: Read-write.
     * Writeable in states: READY, STARTED
     */
    DELAY_MS = 1,

    /**
     * Output port mute state.
     * Type: boolean
     * Access: Read-write.
     * Writeable in states: READY, STARTED
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
     * Type: int (OutputFormat enum value)
     * Access: Read-write.
     * Writeable in states: READY, ENABLED
     */
    OUTPUT_FORMAT = 4,

    /**
     * Supported audio output formats.
     * Type: int[] (com.rdk.hal.audiomixer.OutputFormat enum values)
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
     * Physical/logical connection state.
     * Type: int (@see com.rdk.hal.audiomixer.ConnectionState enum)
     * Access: Read-only.
     */
    CONNECTION_STATE = 9,

    /**
     * Sets the Dolby MS12 Audio Profile/Preset (e.g. "Music", "Movie", "Sports", etc)
     * 
     * Type: String 
     * Access: Read-write.
     * Writeable in states: READY, STARTED
     * 
     * The value must correspond to a platform-defined AQ profile configuration
     *
     * @see com.rdk.hal.audiomixer.OutputPortCapabilities.DolbyMs12AudioProfiles
     */
    DOLBY_MS12_AUDIO_PROFILE = 10,

    /**
     * Output port underflows.
     * Type: int
     * Access: Read-only.
     *
     * A count of the underflows (starvation) events that the consumer of the output port has experienced since the port was enabled.
     * A single underflow event is considered to be when the consumer, unexpectedly, has no data to consume until normal data flow resumes.
     * When the port is disabled, the last count should be held until the port is re-enabled and the count reset.
     */
    METRIC_UNDERFLOWS = 11,

    /**
     * Output port overflows.
     * Type: int
     * Access: Read-only.
     *
     * A count of the overflow events that the producer has experienced since the port was enabled.
     * A single overflow event is considered to be when the producer, unexpectedly, has no buffer space available to write the data.
     * When the port is disabled the last count should be held until the port is re-enabled and the count reset.
     */
    METRIC_OVERFLOWS = 12,

    /**
     * Vendor-specific extension.
     * Type: Implementation-defined.
     * Access: Read-write or read-only as documented.
     */
    VENDOR_EXTENSION = 1000,
}

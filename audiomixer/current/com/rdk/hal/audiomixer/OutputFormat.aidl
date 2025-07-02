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
 * @brief     Supported audio output formats for an output port.
 * @details   Enumerates the possible encoded or uncompressed audio formats
 *            that may be supported by an audio output port (HDMI, SPDIF, speakers, etc.).
 *            Used to configure the desired output, or query available modes
 *            for format negotiation and passthrough.
 *
 * Typical usages:
 * - Used in IAudioOutputPort to select or report output format.
 * - Used in OutputPortCapabilities to enumerate what is supported.
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @copyright Copyright 2024 RDK Management
 */
@VintfStability
@Backing(type="int")
enum OutputFormat {
    /** Automatically select the best supported format for the connected sink. */
    AUTO = 0,

    /** Output is passed through as received (bitstream, no re-encoding). */
    PASSTHROUGH = 1,

    /** Output as uncompressed PCM (typically stereo). */
    PCM_STEREO = 2,

    /** Output as Dolby Digital (AC-3) bitstream. */
    DOLBY_DIGITAL = 3,

    /** Output as Dolby Digital Plus (E-AC-3) bitstream. */
    DOLBY_DIGITAL_PLUS = 4,

    /** Output as Dolby MAT (Metadata-enhanced Audio Transmission). */
    DOLBY_MAT = 5
    // Extend with additional formats as needed, e.g., DTS, TrueHD, etc.
};

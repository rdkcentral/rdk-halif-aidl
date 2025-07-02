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
 * @brief     Enumerates supported audio output transcode formats.
 * @details   Indicates the possible output audio encoding formats supported by an audio output port
 *            for transcoding or passthrough. Used in capability queries and output configuration.
 * @author    (Add your author list)
 */
@VintfStability
@Backing(type="int")
enum TranscodeFormat {
    /** No transcoding. */
    NONE = 0,

    /** Linear PCM (uncompressed). */
    PCM = 1,

    /** Dolby Digital (AC-3) bitstream. */
    DOLBY_AC3 = 2,

    /** Dolby Digital Plus (E-AC-3) bitstream. */
    DOLBY_AC3_PLUS = 3,

    /** Dolby MAT (Metadata-enhanced Audio Transmission). */
    DOLBY_MAT = 4,

    /** Dolby TrueHD bitstream. */
    DOLBY_TRUEHD = 5,

    /** DTS bitstream. */
    DTS = 6,

    /** MPEG-1/2 audio layer II. */
    MPEG2 = 7,

    /** Other (add vendor-specific or future codecs here as needed). */
    OTHER = 100
}

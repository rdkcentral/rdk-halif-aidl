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
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.audiodecoder;

/** 
 *  @brief     Audio codec definitions.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */

@VintfStability
@Backing(type="int")
/**
 * @brief Enumeration of supported audio codecs.
 * 
 * ID ranges are used to indicate implementation support expectations:
 * - 0–99:     Mandatory support
 * - 100–199:  Conditionally mandatory (e.g., licensed codecs)
 * - 200–255:  Optional codecs
 */
enum Codec
{
    // === Mandatory (0–99) ===

    PCM = 0,               /**< Pulse Code Modulation. Used in raw LPCM streams. */
    AAC = 1,               /**< Advanced Audio Coding base codec. Used in broadcast, IP streams, and files. */
    MPEG_AUDIO = 2,        /**< MPEG-1/2 Layer II. Used in broadcast and file-based delivery. */
    MP3 = 3,               /**< MPEG-1/2 Layer III (MP3). Common in file-based playback. */
    AAC_ELD = 4,           /**< Enhanced Low Delay AAC. Used in Apple AirPlay and low-latency scenarios. */
    ALAC = 5,              /**< Apple Lossless Audio Codec. Used in Apple AirPlay. */
    SBC = 6,               /**< Subband Codec. Used in Bluetooth A2DP audio streaming. */

    // === Conditionally Mandatory / Licensed (100–199) ===

    DOLBY_AC3 = 100,       /**< Dolby AC-3. Requires Dolby license. */
    DOLBY_AC4 = 101,       /**< Dolby AC-4. Requires Dolby license. */
    DOLBY_MAT = 102,       /**< Dolby MAT. Typically used for HDMI bitstreams. Requires Dolby license. */
    DOLBY_TRUEHD = 103,    /**< Dolby TrueHD. Lossless format used in Blu-ray. Requires Dolby license. */

    // === Optional (200+) ===

    FLAC = 200,            /**< Free Lossless Audio Codec. Used in Amazon Music, file-based playback. */
    VORBIS = 201,          /**< Vorbis. Used in WebM containers and open streaming platforms. */
    OPUS = 202,            /**< Opus. Real-time streaming and WebRTC applications. */
    WMA = 203,             /**< Windows Media Audio. Legacy Microsoft ecosystem support. */
    REALAUDIO = 204,       /**< RealAudio. Historical streaming format. */
    USAC = 205,            /**< Unified Speech and Audio Coding. Emerging IP streaming codec. */
    DTS = 206,             /**< Digital Theater Systems codec. Home theatre and disc-based media. */
    AVS = 207              /**< Audio Video Standard codec (China). Used in regional broadcast and files. */
}

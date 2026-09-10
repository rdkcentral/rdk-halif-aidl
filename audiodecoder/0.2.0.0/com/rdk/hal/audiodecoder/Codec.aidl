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
 */

@VintfStability
@Backing(type="int")
/** @brief Enumeration defining different audio codecs. */
enum Codec {
    PCM = 0,             /**< Pulse Coded Modulation. */
    AAC_LC = 1,          /**< Advanced Audio Coding Low Complexity. */
    HE_AAC = 2,          /**< High Efficiency Advanced Audio Coding. */
    HE_AAC2 = 3,         /**< High Efficiency Advanced Audio Coding v2. */
    AAC_ELD = 4,         /**< Advanced Audio Coding Enhanced Low Delay. */
    DOLBY_AC3 = 5,       /**< Dolby AC-3. */
    DOLBY_AC3_PLUS = 6,  /**< Dolby AC-3+ (E-AC-3). */
    DOLBY_AC3_PLUS_JOC = 7, /**< Dolby AC-3+ (E-AC-3) with Joint Object Coding. */
    DOLBY_AC4 = 8,       /**< Dolby AC-4. */
    DOLBY_MAT = 9,       /**< Dolby MAT. */
    DOLBY_MAT2 = 10,      /**< Dolby MAT2. */
    DOLBY_TRUEHD = 11,   /**< Dolby TrueHD. */
    MPEG2 = 12,          /**< MPEG-1/2 audio layer II. */
    MP3 = 13,            /**< MPEG-1/2 audio layer III. */
    FLAC = 14,           /**< Free Lossless Audio Codec. */
    VORBIS = 15,         /**< Vorbis. */
    DTS = 16,            /**< Digital Theater Systems. */
    OPUS = 17,           /**< Opus. */
    WMA = 18,            /**< Windows Media Audio. */
    REALAUDIO = 19,      /**< RealAudio. */
    USAC = 20,           /**< Unified Speech and Audio Coding. */
    X_HE_AAC = 21,       /**< AAC speech codec. */
    SBC = 22,            /**< SBC Bluetooth codec. */
    AVS = 23             /**< Audio Video Standard codec. */
}

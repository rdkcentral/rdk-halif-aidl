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
 *  @brief     Audio codec specific data formats.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */

/**
 * Enumeration of supported audio codec-specific data formats.
 *
 * These values define the format of initialization data required for certain audio codecs
 * used in DVB, ISDB, HLS, and DASH applications in STB/TV systems.
 */
@VintfStability
@Backing(type="int")
enum CSDAudioFormat
{
    /**
     * AAC AudioSpecificConfig (ASC) per ISO/IEC 14496-3.
     * Used for AAC-LC, HE-AAC, HE-AAC v2 in MP4/fMP4.
     * Required in encrypted DASH, HLS fMP4, CMAF.
     */
    MP4_AUDIO_SPECIFIC_CONFIG = 0,

    /**
     * MPEG-4 ALS AudioSpecificConfig (14496-3 subpart 11).
     * Rare, but valid in ISOBMFF with encryption.
     */
    ALS_SPECIFIC_CONFIG = 1,

    /**
     * Apple Lossless Audio Codec (ALAC), codec_data from 'alac' atom.
     * Used in MP4; decoder expects this for both clear/encrypted tracks.
     */
    ALAC_SPECIFIC_CONFIG = 2,

    /**
     * Dolby Digital Plus (E-AC-3) with 'dec3' box and possible proprietary config.
     * Used in ISOBMFF with encryption for HLS/DASH and HDMI passthrough.
     */
    EAC3_SPECIFIC_CONFIG = 3,

    /**
     * Dolby AC-4 with 'dac4' box per ETSI TS 103 190.
     * Used in fMP4 and CMAF for DVB-I and ATSC 3.0 systems.
     */
    AC4_SPECIFIC_CONFIG = 4
}

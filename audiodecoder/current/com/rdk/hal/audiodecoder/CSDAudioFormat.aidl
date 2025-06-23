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
enum CSDAudioFormat {
    /**
     * MPEG-4 AudioSpecificConfig (used with AAC in fMP4 containers).
     * Used in DASH, HLS fMP4, and DVB-DASH.
     */
    MP4_AUDIO_SPECIFIC_CONFIG = 0,

    /**
     * AAC in ADTS format. Typical in HLS MPEG-2 TS streams and broadcast systems.
     */
    AAC_ADTS_HEADER = 1,

    /**
     * AAC in LATM/LOAS format. Used primarily in ISDB-T and occasionally in DVB-T2.
     */
    LATM_MPEG4_CONFIG = 2,

    /**
     * MPEG-1 Layer II audio configuration (commonly used in DVB systems).
     */
    MPEG1_LAYER2_CONFIG = 3,

    /**
     * Dolby Digital AC-3 specific header. Used in DVB, ISDB, HDMI passthrough.
     */
    AC3_SPECIFIC_CONFIG = 4,

    /**
     * Dolby Digital Plus (E-AC-3) specific header. Used in DVB-DASH, HLS, HDMI.
     */
    EAC3_SPECIFIC_CONFIG = 5,

    /**
     * MPEG-4 ALS (Audio Lossless Coding). Rare, but used in some ISDB profiles.
     */
    ALS_SPECIFIC_CONFIG = 6
}

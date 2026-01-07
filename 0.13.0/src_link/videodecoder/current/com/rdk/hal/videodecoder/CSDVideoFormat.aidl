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
package com.rdk.hal.videodecoder;

/** 
 *  @brief     Video codec specific data formats.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */

/**
 * Enum representing the video format for decoder configuration records.
 *
 * This enum defines the different video formats associated with decoder configuration records.
 * Each enum value corresponds to a specific video codec and its corresponding
 * configuration record structure. The configuration record starts with a version byte.
 *
 * These configuration records provide necessary codec parameters such as sequence headers, 
 * SPS (Sequence Parameter Set), PPS (Picture Parameter Set), and codec initialization details.
 *
 * @enum CSDVideoFormat
 */
@VintfStability
@Backing(type="int")
enum CSDVideoFormat {
    /**
     * AVC Decoder Configuration Record (H.264/AVC).
     *
     * Represents the `AVCDecoderConfigurationRecord` as defined in:
     * - **ISO/IEC 14496-15:2022**, Section 5.3.3.1.2
     * - More info: @see https://www.iso.org/standard/83336.html
     */
    AVC_DECODER_CONFIGURATION_RECORD = 0,

    /**
     * HEVC Decoder Configuration Record (H.265/HEVC).
     *
     * Represents the `HEVCDecoderConfigurationRecord` as defined in:
     * - **ISO/IEC 23008-2 (HEVC)**
     * - More info: @see https://www.iso.org/standard/85457.html
     */
    HEVC_DECODER_CONFIGURATION_RECORD = 1,

    /**
     * AV1 Decoder Configuration Record.
     *
     * Represents the `AV1CodecConfigurationRecord` as defined in:
     * - **AOM AV1 ISOBMFF specification**
     * - More info: @see https://aomediacodec.github.io/av1-isobmff/#av1codecconfigurationbox-section
     */
    AV1_DECODER_CONFIGURATION_RECORD = 2
}



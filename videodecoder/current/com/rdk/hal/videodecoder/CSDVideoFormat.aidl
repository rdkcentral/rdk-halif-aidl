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
 */

@VintfStability
@Backing(type="int")
enum CSDVideoFormat {
    /**
    * Enum representing the video format for decoder configuration records.
    *
    * This enum defines the different video formats associated with decoder configuration records.
    * Each enum value corresponds to a specific video codec and its corresponding
    * configuration record structure.  The configuration record starts with a version byte.
    *
    * For AVC_DECODER_CONFIGURATION_RECORD (H.264/AVC), this represents the
    * AVCDecoderConfigurationRecord.  See ISO/IEC 14496-15:2022, 5.3.3.1.2 and
    * https://www.iso.org/standard/83336.html for more details.
    *
    * For HEVC_DECODER_CONFIGURATION_RECORD (H.265/HEVC), this represents the
    * HEVCDecoderConfigurationRecord. See ISO/IEC 23008-2 and
    * https://www.iso.org/standard/85457.html for further information.
    *
    * For AV1_DECODER_CONFIGURATION_RECORD (AV1 video), this represents the
    * AV1CodecConfigurationRecord. See
    * https://aomediacodec.github.io/av1-isobmff/#av1codecconfigurationbox-section
    * for more details.
    */
    AVC_DECODER_CONFIGURATION_RECORD = 0, /**< This value represents the AVCDecoderConfigurationRecord for H.264/AVC video. */
    HEVC_DECODER_CONFIGURATION_RECORD = 1, /**< This value represents the HEVCDecoderConfigurationRecord for H.265/HEVC video. */
    AV1_DECODER_CONFIGURATION_RECORD = 2  /**< This value represents the AV1CodecConfigurationRecord for AV1 video. */
};



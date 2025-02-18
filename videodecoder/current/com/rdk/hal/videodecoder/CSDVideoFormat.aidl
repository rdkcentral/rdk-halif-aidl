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
	* For AVC_DECODER_CONFIGURATION_RECORD H.264/AVC this is the AVCDecoderConfigurationRecord, starting with the configuration version byte.
	* @see ISO/IEC 14496-15:2022, 5.3.3.1.2
	* @see https://www.iso.org/standard/83336.html
	* 
	* For HEVC_DECODER_CONFIGURATION_RECORD H.265/HEVC video, this is the HEVCDecoderConfigurationRecord, starting with the configuration version byte.
	* @see ISO/IEC 23008-2
	* @see https://www.iso.org/standard/85457.html
	* 
	* For AV1_DECODER_CONFIGURATION_RECORD AV1 video, this is the AV1CodecConfigurationRecord, starting with the first configuration version byte.
	* @see https://aomediacodec.github.io/av1-isobmff/#av1codecconfigurationbox-section
	**/
	AVC_DECODER_CONFIGURATION_RECORD = 0,  /** H.264/AVC this is the AVCDecoderConfigurationRecord */
	HEVC_DECODER_CONFIGURATION_RECORD = 1, /** H.265/HEVC video, this is the HEVCDecoderConfigurationRecord */
	AV1_DECODER_CONFIGURATION_RECORD = 2   /** AV1 video, this is the AV1CodecConfigurationRecord */
}



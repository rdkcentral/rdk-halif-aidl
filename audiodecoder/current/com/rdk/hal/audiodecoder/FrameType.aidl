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
 * @brief	Different frame types the Audio Decoder can output	
 * @author	Luc Kennedy-Lamb
 * @author	Peter Stieglitz
 * @author	Douglas Adler
 */
 
@VintfStability
@Backing(type="byte")
enum Property FrameType {
	/**
	 * The decoded audio data is PCM
	 * The PCMMetadata in FrameMetadata is valid 
	 *
	 */
	PCM = 0,

    /**
	 * The decoded audio data is an opaque proprietary format.
     * The PCMMetadata in FrameMetadata is not valid 
     * The FrameMetadata contains a SoCPrivate field that if of 
     * non-zero length is used by the HAL implementation to pass 
     * SoC HAL specific opaque metadata. 
	 *
     */
	SOC_PROPRIETARY = 1,

}
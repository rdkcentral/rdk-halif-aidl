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
 *  @brief     PCM audio formats.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
@Backing(type="int")
enum PCMFormat {
	F64LE = 0, 
	F64BE = 1, 
	F32LE = 2, 
	F32BE = 3, 
	S32LE = 4, 
	S32BE = 5, 
	U32LE = 6, 
	U32BE = 7, 
	S24_32LE = 8, 
	S24_32BE = 9, 
	U24_32LE = 10, 
	U24_32BE = 11, 
	S24LE = 12, 
	S24BE = 13, 
	U24LE = 14, 
	U24BE = 15, 
	S20LE = 16, 
	S20BE = 17, 
	U20LE = 18, 
	U20BE = 19, 
	S18LE = 20, 
	S18BE = 21, 
	U18LE = 22, 
	U18BE = 23, 
	S16LE = 24, 
	S16BE = 25, 
	U16LE = 26, 
	U16BE = 27, 
	S8 = 28, 
	U8 = 29,
}

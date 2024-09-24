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
enum Codec {
	/** Pulse coded modulation. */
	PCM = 0, 

	/** Advanced audio coding low complexity. */
	AAC_LC = 1, 

	/** High efficiency Advanced audio coding. */
	HE_AAC = 2, 

	/** High efficiency Advanced audio coding v2. */
	HE_AAC2 = 3, 

	/** Advanced audio coding enhanced low delay. */
	AAC_ELD = 4, 

	/** Dolby AC-3. */
	DOLBY_AC3 = 5, 

 	/** Dolby AC-3+ (E-AC-3). */ 
	DOLBY_AC3_PLUS = 6,

  	/** Dolby AC-3+ (E-AC-3) with Joint Object Coding. */  
	DOLBY_AC3_PLUS_JOC = 7, 

  	/** Dolby AC-4 */  
	DOLBY_AC4 = 8, 

  	/** Dolby MAT */  
	DOLBY_MAT = 9, 

  	/** Dolby MAT2 */  
	DOLBY_MAT2 = 10, 

  	/** Dolby TrueHD */  
	DOLBY_TRUEHD = 11, 

	/** MPEG-1/2 audio layer II. */
    MPEG2 = 12,

 	/** MPEG-1/2 audio layer III. */
	MP3 = 13,
  
  	/** Free Lossless Audio Codec. */
	FLAC = 14,

  	/** Vorbis. */
    VORBIS = 15,

  	/** Digital Theater Systems. */
	DTS = 16,

	/** Opus. */
	OPUS = 17,

 	/** Windows Media Audio. */
	WMA = 18,

	/** RealAudio. */
    REALAUDIO = 19,

	/** Unified Speech and Audio Coding. */
    USAC = 20,

	/** AAC speech codec */
    X_HE_AAC = 21,

	/** SBC Bluetooth codec */
    SBC = 22,

	/** Audio Video Standard codec */
    AVS = 23,
}

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
 * @brief	Audio decoder properties used in property get/set functions.
 *			All properties can be read in any state.	
 * @author	Luc Kennedy-Lamb
 * @author	Peter Stieglitz
 * @author	Douglas Adler
 */
 
@VintfStability
@Backing(type="int")
enum Property {
	/**
	 * Unique ID of the audio decoder resource instance.
	 * 
	 * Type: Integer
	 * Access: Read-only.
	 */
	RESOURCE_ID = 0,
	
	/**
	 * Controls the low latency mode.
	 * The low latency mode is also set inside the FrameMetadata when output by a decoder.
	 * 
	 * Type: Integer
	 *  0 - off (default on open)
	 *  1 - on (only if supported)
	 * Access: Read-write.
	 * Write in states: READY
	 */
	LOW_LATENCY_MODE = 1,

	/**
	 * Set by the client to specify the AV source of the stream.
	 * 
	 * The AVSource is also set inside the FrameMetadata when output by a decoder.
	 * Type: Integer
	 *  Default is 0 - AVSource::UNKNOWN.
	 * Access: Read-write.
	 * Write in states: READY
	 * @see enum AVSource for possible values.
	 */
	AV_SOURCE = 3,

	/**
	 * Indicates if the audio decoder was opened for secure audio path.
	 * 
	 * Type: Integer
	 *  0 - off
	 *  1 - on (only if supported)
	 * Access: Read-only.
	 * @see Capabilities.supportsSecure IAudioDecoder.open()
	 */
	SECURE_AUDIO = 4,

	/**
	 * Dolby AC-4 audio presentation group index.
	 * 
	 * Type: Integer
	 *  -1 - automatic selection by language and associated type. (default)
	 *  0..n - AC-4 presentation group index.
	 * Access: Read-write.
	 * Writeable in states: All
	 */
	AC4_PRESENTATION_GROUP_INDEX = 200,
	
	/**
	 * Dolby AC-4 audio primary preferred language.
	 * 
	 * Type: String
	 *  "" - no override, selection should use the user preference set in audio mixer. (default)
	 *  Otherwise the string should be a 3 letter language code from ISO 639.
	 * Access: Read-write.
	 * Writeable in states: All
	 */
	AC4_PREFERRED_LANG1 = 201,

	/**
	 * Dolby AC-4 audio secondary preferred language.
	 * 
	 * Type: String
	 *  "" - no override, selection should use the user preference set in audio mixer. (default)
	 *  Otherwise the string should be a 3 letter language code from ISO 639.
	 * Access: Read-write.
	 * Writeable in states: All
	 */
	AC4_PREFERRED_LANG2 = 202,

	/**
	 * Dolby AC-4 audio associated audio stream type.
	 * 
	 * Type: Integer
	 *  -1 - no override, selection should use the user preference set in audio mixer. (default)
	 *  0 - visually impaired
	 *  1 - hearing impaired
	 *  2 - commentary
	 * Access: Read-write.
	 * Writeable in states: All
	 */
	AC4_ASSOCIATED_TYPE = 203,
	
	/**
	 * Dolby AC-4 audio automatic presentation group selection priority.
	 * 
	 * Type: Integer
	 *  -1 - no override, selection should use the user preference set in audio mixer. (default)
	 *  0 - language - Prioritize preferred language in the automatic selection of the presentation group.
	 *  1 - associated type - Prioritize the preferred associated type in the automatic selection of the presentation group.
	 * Access: Read-write.
	 * Writeable in states: All
	 */
	AC4_AUTO_SELECTION_PRIORITY = 204,
	
	/**
	 * Dolby AC-4 audio mixer balance between associated audio and main audio.
	 * 
	 * Type: Integer
	 *  255 - no override, selection should use the user preference set in audio mixer. (default)
	 *  -32..32 - Mixer balance from -32 (mute associated) to 32 (mute main).
	 * Access: Read-write.
	 * Writeable in states: All
	 */
	AC4_MIXER_BALANCE = 205,
	
	/**
	 * Dolby AC-4 audio associated audio mixing control.
	 * 
	 * Type: Integer
	 *  -1 - no override, selection should use the user preference set in audio mixer. (default)
	 *  0 - off
	 *  1 - on
	 * Access: Read-write.
	 * Writeable in states: All
	 */
	AC4_ASSOCIATED_AUDIO_MIXING_ENABLE = 206,
	
	/**
	 * Count of decoded frames.
	 * This metric is reset on open() and flush() calls.
	 * 
	 * Type: Integer
	 *  -1 means this metric is not yet implemented by the vendor.
	 * Access: Read-only.
	 */
	METRIC_FRAMES_DECODED = 1000,

	/**
	 * Count of decode errors.
	 * This metric is reset on open() and flush() calls.
	 * 
	 * Type: Integer
	 *  -1 means this metric is not yet implemented by the vendor.
	 * Access: Read-only.
	 */
	METRIC_DECODE_ERRORS = 1001,

	/**
	 * Count of frames dropped.
	 * No frame was output due to corruption or decode error that could not 
	 * deliver a frame suitable for mixing.
	 * This metric is reset on open() and flush() calls.
	 * 
	 * Type: Integer
	 *  -1 means this metric is not yet implemented by the vendor.
	 * Access: Read-only.
	 */
	METRIC_FRAMES_DROPPED = 1002,
}

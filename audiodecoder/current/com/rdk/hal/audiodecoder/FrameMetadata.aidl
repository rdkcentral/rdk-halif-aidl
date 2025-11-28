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
import com.rdk.hal.audiodecoder.PCMMetadata;
import com.rdk.hal.audiodecoder.Codec;
import com.rdk.hal.AVSource;
import com.rdk.hal.FrameType;

/** 
 *  @brief     Audio frame metadata.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
parcelable FrameMetadata {

	/**
	 * The type of audio data output by the decoder
	 */
	FrameType type;

	/**
	 * The original source codec of the audio frame.
	 */
	Codec sourceCodec;

	/**
	 * The buffer contains Dolby Atmos audio and metadata.
	 */
	boolean isDolbyAtmos;
	
	/**
	 * Audio trimming to use on presentation.
	 */
	int trimStartNs;
	int trimEndNs;

	/**
	 * Indicates if the audio should be delivered in low latency mode.
	 */
	boolean lowLatency;

	/**
	 * End of stream indicator.
	 */
	boolean endOfStream;

	/**
	 * Discontinuity indicator where the PTS for this frame is likely to be discontinuous to the previous.
	 */
	boolean discontinuity;

	/**
	 * The source of the audio frame.
	 * When the frame is presented the source may be used to configure the audio settings.
	 */
	AVSource source;

	/**
	 * If the frame is PCM audio data this parcelable contains the PCM metadata.
	 * Else metadata is null.
	 */
	@nullable PCMMetadata metadata;

	/**
	 * Proprietary metadata passed from Decoder HAL to Sink HAL.
	 * When the frame type is SOC_PROPRIETARY SoCPrivate MAY contain indicated by a non-sero length.
	 * opaque HAL metadata that is is used by the Audio Sink and MUST be passed to the Audio Sink.
	 */
	byte[] SoCPrivate;

	/**
	 * Private extension for future use. 
	 */
	ParcelableHolder extension;
}

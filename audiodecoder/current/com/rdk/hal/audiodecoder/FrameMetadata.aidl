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
import com.rdk.hal.audiodecoder.ChannelType;
import com.rdk.hal.audiodecoder.PCMFormat;
import com.rdk.hal.audiodecoder.Codec;

import com.rdk.hal.AVSource;

/** 
 *  @brief     Audio frame metadata.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
parcelable FrameMetadata {

 	/**
	 * The original source codec of the audio frame.
	 */
        Codec sourceCodec;

	/**
	 * The buffer contains Dolby Atmos audio and metadata.
	 */
	boolean isDolbyAtmos;

	/**
	 * Number of audio channels.
	 */
	int numChannels;

   	/**
	 * Array of ChannelType enum values.
	 * The array size should match the number of channels.
	 */
        ChannelType[] channelTypes;

 	/**
	 * Sample rate in samples/second.
	 */
        int sampleRate;

 	/**
	 * Format of the output PCM data.
	 */
        PCMFormat format;

 	/**
	 * Indicated whether the audio data buffer is in planar format.
	 * If false, the data is interleaved with other channels.
	 */
	boolean planarFormat;

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
	 * Private extension for future use. 
	 */
        ParcelableHolder extension;

        /**
        * Proprietary metadata passed from Decoder HAL to Sink HAL
        */
        byte[] SoCPrivate;
}

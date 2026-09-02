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

/** 
 *  @brief     PCM Audio frame metadata.
 *
 *  Every field on this parcelable describes the format of the frame whose
 *  FrameMetadata carried it, and that format remains in effect for later
 *  frames until new metadata is delivered.
 *
 *  Frame metadata is only emitted when it changes, so where the decoder
 *  absorbs an in-codec format change mid-stream the first frame produced
 *  under the new format carries a non-null FrameMetadata holding the
 *  updated numChannels / channelTypes / sampleRate. That delivery is the
 *  only format-change notification: there is no out-of-band signal, and
 *  the client is not required to act before it arrives.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
parcelable PCMMetadata {

    /**
     * Number of audio channels in this frame.
     *
     * Reflects the format of THIS frame. On an in-codec format change the
     * value updates on the first frame produced under the new format,
     * and stays in effect until new metadata is delivered.
     */
    int numChannels;

    /**
     * Array of ChannelType enum values for this frame.
     * The array size should match the number of channels.
     *
     * Reflects the format of THIS frame. Updates on the first frame
     * produced after an in-codec channel-layout change.
     */
    ChannelType[] channelTypes;

    /**
     * Sample rate in samples/second for this frame.
     *
     * Reflects the format of THIS frame. On an in-codec format change the
     * value updates on the first frame produced under the new format,
     * and stays in effect until new metadata is delivered.
     */
    int sampleRate;

    /**
     * Format of the output PCM data.
     */
    PCMFormat format;

    /**
     * Indicates whether the audio data buffer is in planar format.
     * If false, the data is interleaved with other channels.
     */
    boolean planarFormat;

    /**
     * Private extension for future use. 
     */
    ParcelableHolder extension;
}

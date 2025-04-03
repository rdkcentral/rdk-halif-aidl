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
package com.rdk.hal.audiosink;
 
/** 
 *  @brief     Audio sink properties used in property get/set functions.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
@Backing(type="int")
enum Property {

    /**
     * Unique 0 based index per audio sink resource instance.
     *
     * Type: Integer
     * Access: Read-only.
     */
    RESOURCE_ID = 0,
    
    /**
     * dB reference level of the audio stream.
     * The default reference level for an audio sink session is -31dB.
     *
     * Type: Integer
     *  -31 is default on open
     * Access: Read-write.
     * Write in states: READY
     */
    REFERENCE_LEVEL = 1,
    
    /**
     * The render output latency in nanoseconds.
     * This is the time from an audio frame being rendered from the queue to being output (HDMI/ARC/BT/internal speakers).
     *
     * Type: Integer
     * Access: Read-only.
     */
    RENDER_LATENCY_NS = 2,
    
    /**
    * The queue depth of the audio output path in nanoseconds.
    *
    * This value represents the total amount of audio data, measured in nanoseconds,
    * that is currently buffered and queued for playback in the audio output path.
    *
    * Type: Integer
    * Access: Read-only.
    */
    QUEUE_DEPTH_NS = 3,

    /**
     * The index of the audio mixer that the audio sink is input to.
     *
     * Type: Integer
     *  0 is the default system mixer. (default on open)
     * Access: Read-write.
     * Write in states: READY
     */
    MIXER_ID = 4,

    /**
     * Set by the client to specify the AV source of the stream.  
     * The AVSource is also set inside the FrameMetadata when output by a decoder.
     *
     * Type: Integer
     *  0 - AVUNKNOWN (default on open)
     * @see enum AVSource for possible values.
     * Access: Read-write.
     * Write in states: READY
     */
    AV_SOURCE = 5,

    /**
     * When enabled, Dolby Atmos output is locked on audio ports (where possible).
     * This originated as a Netflix feature to avoid audio artefacts when starting and stopping Atmos stream content.
     * See https://docs.netflixpartners.com/docs/nrdp/nrdp2024/content-playback/audio-content/dolby-ms12-partner-guidance?selectednrdpRelease=NRDP+2024.1#atmos-locking
     *
     * Type: Integer
     *  0 - disabled (default on open)
     *  1 - enabled
     * Access: Read-write.
     * Write in states: READY
     */
    DOLBY_ATMOS_LOCK = 6,

    /**
     *
     */
    METRIC_xxxx = 1000,
}


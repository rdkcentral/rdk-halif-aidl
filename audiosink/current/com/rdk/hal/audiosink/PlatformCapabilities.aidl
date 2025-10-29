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
import com.rdk.hal.audiodecoder.PCMFormat;

/**
 *  @brief     Audio sink platform capabilities definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
parcelable PlatformCapabilities {

    /**
     * Indicates the platform support for low latency audio.
     */
    boolean supportsLowLatency;

    /**
     * The native sample rate of system mixer.
     * PCM audio must be delivered at this sample rate.
     */
    int systemMixerSampleRateHz;

    /**
     * The PCM format of the system mixer.
     * PCM audio must be delivered in this format.
     */
    PCMFormat systemMixerPCMFormat;

    /**
     * Indicated support for planar format of audio data buffers
     * where the audio samples for each channel are delivered
     * together in one plane, rather than interleaved with all other channels.
     */
    boolean supportsPlanarFormat;
}

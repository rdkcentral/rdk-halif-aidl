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
import com.rdk.hal.audiosink.IAudioSink; 
import com.rdk.hal.audiosink.PlatformCapabilities; 

/** 
 *  @brief     Audio Sink Manager HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
interface IAudioSinkManager
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "AudioSinkManager";

	/**
	 * Gets the list of platform audio sink IDs.
     * 
     * @returns IAudioSink.Id[] array.
     */
	IAudioSink.Id[] getAudioSinkIds();   

    /**
     * Gets the platform wide capabilities for audio sinks.
     * 
     * This includes the system mixer native PCM formats and sample rate that an audio sink
     * has to deliver for mixing.
     * The platform capabilities are determined at build time and cannot change.
     * 
     * @returns PlatformCapabilities parcelable.
     */
    PlatformCapabilities getPlatformCapabilities();

    /**
     * Gets the audio sink interface for a given ID.
     *
     * @param[in] audioSinkId       The ID of the audio sink resource.
     *
     * @returns IAudioSink or null on invalid audio sink ID.
     */
    @nullable IAudioSink getAudioSink(in IAudioSink.Id audioSinkId);

}

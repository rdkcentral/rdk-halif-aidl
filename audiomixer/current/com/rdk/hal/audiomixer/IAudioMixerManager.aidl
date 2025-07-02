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
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 package com.rdk.hal.audiomixer;

import com.rdk.hal.audiomixer.IAudioMixer;

/**
 * @brief Audio Mixer Manager HAL interface.
 *
 * Provides enumeration and access to available system audio mixers.
 * Each mixer represents a logical or physical audio mixing resource
 * on the platform, such as the system mixer or dedicated MS12/DTS instances.
 * This interface is implemented by the vendor layer and allows the RDK
 * middleware to discover and control available mixer resources.
 */
interface IAudioMixerManager {
    /**
     * @brief Returns a list of available audio mixer instance IDs.
     * 
     * This function can be called at any time. The returned set must
     * be stable for the lifetime of the process.
     *
     * @return Array of IAudioMixer.Id values representing available mixers.
     */
    IAudioMixer.Id[] getAudioMixerIds();

    /**
     * @brief Acquires a specific audio mixer interface by ID.
     * 
     * @param id Mixer resource identifier.
     * @return IAudioMixer interface for controlling the mixer, or null if unavailable.
     */
    @nullable IAudioMixer getAudioMixer(in IAudioMixer.Id id);
}

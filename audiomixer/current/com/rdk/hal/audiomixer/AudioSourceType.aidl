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

/**
 * @brief     Audio source types for mixer input routing.
 * Defines the types of audio sources that can be routed to mixer inputs.
 *            Follows the pattern established by planecontrol::SourceType.
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 * @copyright Copyright 2024 RDK Management
 */
@VintfStability
@Backing(type="int")
enum AudioSourceType
{
    /**
     * No audio source is connected to the mixer input. Default/disconnected state.
     */
    NONE = 0,

    /**
     * Audio sink output is connected to the mixer input.
     */
    AUDIO_SINK = 1,

    /**
     * HDMI input audio is connected to the mixer input.
     */
    HDMI_INPUT = 2,

    /**
     * Composite input audio is connected to the mixer input.
     */
    COMPOSITE_INPUT = 3,

    /**
     * Application audio is connected to the mixer input.
     */
    APPLICATION_AUDIO = 4
}

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

import com.rdk.hal.audiomixer.MixerInput;

/**
 * @brief Capabilities structure for Audio Mixer.
 *
 * Describes whether the mixer supports secure audio processing and
 * details all supported input configurations, including the number
 * and type of inputs, supported content types and codecs.
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 * @copyright Copyright 2024 RDK Management
 */
@VintfStability
parcelable Capabilities {
    /**
     * @brief Indicates if this mixer instance supports secure audio path mode.
     */
    boolean supportsSecure;

    /**
     * @brief Describes the available audio mixer input specifications.
     *
     * Contains N mixer input capability definitions where each array element describes
     * the capabilities of the mixer input at that index position.
     *
     * The array index directly corresponds to the mixer input index:
     * - inputs[0] = mixer input 0 capabilities
     * - inputs[1] = mixer input 1 capabilities
     * - etc.
     *
     * When routing audio sources via setInputRouting(), check this array to:
     * 1. Find which mixer input(s) support your required codec (e.g., AC3, PCM)
     * 2. Verify the input supports your content type (STREAM, CLIP, TTS)
     * 3. Use the matching array index in the InputRouting array to connect your source
     *
     * The array length indicates the total number of mixer inputs available.
     */
    MixerInput[] inputs;

    /**
    * @brief Human-readable name for this audio mixer input.
    * @details May be null if not set by the platform.
    *          Although optional, this field is intended to aid debugging, logging, and platform introspection.
    */
    @nullable String name;

}

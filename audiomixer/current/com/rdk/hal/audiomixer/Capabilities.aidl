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

import com.rdk.hal.audiomixer.Input;

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
     * @brief Indicates whether this mixer instance supports secure audio path.
     */
    boolean isSecure;

    /**
     * @brief Describes the available audio mixer inputs.
     *
     * Each input specifies supported content types (e.g., STREAM, CLIP)
     * and codecs (e.g., PCM, AC3, AAC).
     * The number of entries indicates the number of concurrently supported input streams.
     */
    Input[] inputs;

    /**
    * @brief Human-readable name for this audio mixer input.
    * @details May be null if not set by the platform.
    *          Although optional, this field is intended to aid debugging, logging, and platform introspection.
    */
    @nullable String name;

}

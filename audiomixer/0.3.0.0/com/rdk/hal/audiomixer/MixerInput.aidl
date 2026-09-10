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

import com.rdk.hal.audiomixer.ContentType;
import com.rdk.hal.audiodecoder.Codec;

/**
 * @brief Audio Mixer Input Capability Definition.
 *
 * Describes the capabilities of a single mixer input, including supported
 * content types (STREAM, CLIP, TTS) and codecs (PCM, AC3, etc.).
 *
 * Usage workflow:
 * 1. Call IAudioMixer.getCapabilities() to retrieve Capabilities.inputs[] array
 * 2. Examine each inputs[i] to find a mixer input that supports your codec/content type
 * 3. Use the array index i in InputRouting to connect your audio source to that mixer input
 *
 * For example, to route compressed AC3 audio:
 * - Check inputs[0].supportedCodecs contains Codec.AC3
 * - Use setInputRouting() with routing[0] to connect your source to mixer input 0
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 */
@VintfStability
parcelable MixerInput {
    /**
     * @brief List of content types this input supports.
     */
    ContentType[] supportedContentTypes;

    /**
     * @brief List of codecs supported for this input.
     */
    Codec[] supportedCodecs;

    /**
     * @brief Human-readable name for this audio mixer input.
     * May be null if not set by the platform.
     *          Examples: "main", "assoc", "pcm1", "pcm2", "aux".
     *          Although optional, this field aids debugging, logging, and platform introspection.
     */
    @nullable String name;
}

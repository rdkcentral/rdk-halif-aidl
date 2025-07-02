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
 * @brief Audio Mixer Input Definition.
 *
 * Specifies the supported content types (STREAM, CLIP, TTS) and codecs
 * (PCM, AC3, etc.) for a given input on a mixer resource.
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 * @copyright Copyright 2024 RDK Management
 */
@VintfStability
parcelable Input {
    /**
     * @brief List of content types this input supports.
     */
    ContentType[] supportedContentTypes;

    /**
     * @brief List of codecs supported for this input.
     */
    Codec[] supportedCodecs;
}

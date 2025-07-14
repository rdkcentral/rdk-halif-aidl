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
package com.rdk.hal.audiodecoder;

import com.rdk.hal.audiodecoder.Codec;
import com.rdk.hal.audiodecoder.Profile;

@VintfStability
/**
 * @brief Describes platform support for a specific audio codec and its capabilities.
 */
parcelable CodecSupport {
    Codec codec;               /**< The audio codec type (e.g., AAC, FLAC, AC3). */

    /**
     * @brief List of supported profiles for codecs that define them (e.g., AAC, USAC, WMA).
     * For codecs without formal profiles (e.g., FLAC, Vorbis), this must be null or empty.
     */
    Profile[] profiles;

    int maxSampleRate;         /**< Maximum supported sample rate in Hz (e.g., 48000, 96000). */
    int maxChannels;           /**< Maximum number of audio channels supported (e.g., 2, 6, 8). */
    int maxBitDepth;           /**< Maximum supported bit depth (e.g., 16, 24). Applies to PCM, FLAC, etc. */
}

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
 package com.rdk.hal.audiodecoder;

import com.rdk.hal.audiodecoder.Codec;
import com.rdk.hal.audiodecoder.Profile;

@VintfStability
/**
 * @brief Describes platform support for a specific codec and its profile variants.
 */
parcelable CodecSupport {
    Codec codec;            /**< The codec type (e.g., AAC, Dolby AC-3). */
    Profile[] profiles;     /**< List of supported profiles. Empty if the codec has no profiles. */
    int maxSampleRate;      /**< Max supported sample rate in Hz (e.g., 48000). */
    int maxChannels;        /**< Max number of supported channels (e.g., 2, 6, 8). */
}

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

import com.rdk.hal.audiodecoder.CodecSupport;

@VintfStability
/**
 * @brief Describes the overall audio decoder capabilities of the platform.
 * 
 * This structure aggregates all codec-specific capabilities supported by the audio
 * decoder implementation. It includes version information to track capability schema
 * changes over time.
 */
parcelable Capabilities {
    /**
     * Array of codec-specific capabilities supported by the platform.
     * Each entry describes maximum capabilities for a specific codec, including:
     * - Supported profiles (if applicable)
     * - Maximum bitrate
     * - Maximum sample rate
     * - Maximum number of channels
     * - Maximum bit depth
     */
    CodecSupport[] codecCapabilities;
}

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

@VintfStability
@Backing(type="int")
/**
 * @brief Enumeration of profiles for the AAC codec (Codec.AAC).
 */
enum AACProfile {
    LC = 0,            /**< Low Complexity AAC. */
    HE_V1 = 1,         /**< High Efficiency AAC v1. */
    HE_V2 = 2,         /**< High Efficiency AAC v2. */
    ELD = 3,           /**< Enhanced Low Delay AAC. */
    XHE = 4           /**< Extended HE-AAC (exHE-AAC). */
} 

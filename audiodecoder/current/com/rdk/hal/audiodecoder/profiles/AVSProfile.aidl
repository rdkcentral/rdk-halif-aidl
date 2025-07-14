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
 * @brief Enumeration of profiles for the AVS codec (Codec.AVS).
 */
enum AVSProfile {
    AVS1_PART2 = 0,      /**< AVS1 Part 2 (mandatory for DTV) */
    AVS2 = 1,            /**< AVS2 Audio (UHD broadcast) */
    AVS3 = 2             /**< AVS3 Audio (emerging IP streaming) */
}


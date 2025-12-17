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
 * @brief Enumeration of profiles for Dolby AC-3 codec (Codec.DOLBY_AC3).
 */
enum DolbyAC3Profile {
    STANDARD = 0,      /**< Dolby AC-3. */
    PLUS = 1,          /**< Dolby Digital Plus (E-AC-3). */
    PLUS_JOC = 2       /**< Dolby Digital Plus with JOC (Atmos). */
}

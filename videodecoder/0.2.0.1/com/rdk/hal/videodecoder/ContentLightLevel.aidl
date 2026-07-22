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
package com.rdk.hal.videodecoder;

/**
 *  @brief     Content light level metadata (SMPTE ST 2094-10 / CTA-861.3).
 *
 *  Carried in HEVC SEI message type 144 (content_light_level_info).
 *  Both fields are integer cd/m^2 (nits) in the range 0-65535.
 *  A value of 0 indicates the field is not present or unknown.
 *
 *  @author    Gerald Weatherup
 */

@VintfStability
parcelable ContentLightLevel {

    /**
     * Maximum Content Light Level (MaxCLL).
     * The peak luminance of any single pixel across the entire content,
     * in integer cd/m^2 (nits). Range: 0-65535. 0 = not present.
     * @see HEVC SEI type 144, max_content_light_level
     */
    int maxCLL;

    /**
     * Maximum Frame-Average Light Level (MaxFALL).
     * The maximum average luminance of any single frame across the entire
     * content, in integer cd/m^2 (nits). Range: 0-65535. 0 = not present.
     * @see HEVC SEI type 144, max_pic_average_light_level
     */
    int maxFALL;
}

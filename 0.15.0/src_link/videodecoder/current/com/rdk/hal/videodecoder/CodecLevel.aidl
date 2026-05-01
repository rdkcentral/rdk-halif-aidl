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
 *  @brief     Codec capability definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */

@VintfStability
@Backing(type="int")
enum CodecLevel {
    // MPEG-2 Levels
    MPEG2_LEVEL_LOW = 1,
    MPEG2_LEVEL_MAIN = 2,
    MPEG2_LEVEL_HIGH = 3,

    // H.264 Levels (For SD/HD broadcasting)
    H264_LEVEL_3 = 100,    // Standard for SD and lower HD resolutions
    H264_LEVEL_3_1 = 101,  // Higher bitrate HD support
    H264_LEVEL_4 = 102,    // Supports Full HD (1080p) broadcasting
    H264_LEVEL_4_1 = 103,  // Used for Blu-ray and digital TV
    H264_LEVEL_5 = 104,    // Supports 4K broadcasting
    H264_LEVEL_5_1 = 105,  // High-bitrate 4K support
    H264_LEVEL_5_2 = 106,  // Advanced 4K applications

    // H.265 Levels (For 4K UHD and HDR broadcasting)
    H265_LEVEL_4 = 200,    // Standard 4K resolution support
    H265_LEVEL_4_1 = 201,  // High-bitrate 4K
    H265_LEVEL_5 = 202,    // Supports higher frame rates
    H265_LEVEL_5_1 = 203,  // High-efficiency UHD broadcast
    H265_LEVEL_5_2 = 204,  // Used for high-bitrate 4K HDR
    H265_LEVEL_6 = 205,    // 8K resolution support
    H265_LEVEL_6_1 = 206,  // High-bitrate 8K support
    H265_LEVEL_6_2 = 207,  // Highest efficiency for next-gen broadcasting

    // VP9 Levels (For streaming/IPTV applications)
    VP9_LEVEL_1 = 300,
    VP9_LEVEL_1_1 = 301,
    VP9_LEVEL_2 = 302,
    VP9_LEVEL_2_1 = 303,
    VP9_LEVEL_3 = 304,
    VP9_LEVEL_3_1 = 305,
    VP9_LEVEL_4 = 306,   // Standard for 1080p
    VP9_LEVEL_4_1 = 307,
    VP9_LEVEL_5 = 308,   // Standard for 4K UHD
    VP9_LEVEL_5_1 = 309,
    VP9_LEVEL_5_2 = 310, // High-bitrate 4K HDR
    VP9_LEVEL_6 = 311,
    VP9_LEVEL_6_1 = 312,
    VP9_LEVEL_6_2 = 313, // Advanced HDR and 8K

    // AV1 Levels (For next-gen UHD broadcasting)
    AV1_LEVEL_4_0 = 400,  // Standard 4K resolution
    AV1_LEVEL_4_1 = 401,
    AV1_LEVEL_5_0 = 402,  // 4K with high efficiency
    AV1_LEVEL_5_1 = 403,  // High-bitrate 4K HDR
    AV1_LEVEL_6_0 = 404,  // 8K support
    AV1_LEVEL_6_1 = 405,  // High-bitrate 8K HDR
}


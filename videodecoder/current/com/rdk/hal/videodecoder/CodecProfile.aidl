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
enum CodecProfile {
    // MPEG-2 Profiles
    MPEG2_SIMPLE = 1, // Used in legacy digital broadcasting
    MPEG2_MAIN = 2,   // Most common for digital TV broadcasting

    // H.264/AVC Profiles
    H264_BASELINE = 100, // Low complexity, used in mobile and video conferencing
    H264_MAIN = 101,     // Standard for digital TV broadcasting (DVB, ATSC)
    H264_HIGH = 102,     // Used in HD and Blu-ray content

    // H.265/HEVC Profiles
    H265_MAIN = 200,       // Used in standard UHD/4K broadcasting
    H265_MAIN_10 = 201,    // Supports 10-bit depth for HDR video
    H265_MAIN_10_HDR10 = 202, // HDR10 support in broadcasting

    // VP9 Profiles (Mainly used for streaming, but applicable to IPTV)
    VP9_PROFILE_0 = 300, // 8-bit 4:2:0 chroma subsampling
    VP9_PROFILE_1 = 301, // 8-bit 4:2:2 and 4:4:4 chroma subsampling
    VP9_PROFILE_2 = 302, // 10-bit 4:2:0 chroma subsampling (HDR support)
    VP9_PROFILE_3 = 303, // 10-bit 4:2:2 and 4:4:4 chroma subsampling

    // AV1 Profiles (Next-gen codec for future broadcast)
    AV1_MAIN = 400,    // 8 or 10-bit color depth with 4:2:0 chroma subsampling
    AV1_HIGH = 401,    // Supports 4:2:2 and 4:4:4 chroma subsampling
}


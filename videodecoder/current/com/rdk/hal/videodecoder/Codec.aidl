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
 *  @brief     Video decoder codec type definitions.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */
 
@VintfStability
@Backing(type="int")
enum Codec {   
    MPEG2_VIDEO = 1, // MPEG-2 Video (ISO/IEC 13818-2)
    H264_AVC = 2, // H.264/AVC (ITU-T H.264 | ISO/IEC 14496-10)
    H265_HEVC = 3, // H.265/HEVC (ITU-T H.265 | ISO/IEC 23008-2)
    VP9 = 4, // VP9 (IETF RFC 7741)
    AV1 = 5, // AV1 (AOMedia Video 1)
    // ... other codecs
}

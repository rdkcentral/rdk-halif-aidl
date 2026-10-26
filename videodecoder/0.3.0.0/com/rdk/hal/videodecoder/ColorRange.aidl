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
package com.rdk.hal.videodecoder;

/**
 *  @brief     Video sample range — limited (studio) vs full (computer)
 *             quantisation.
 *
 *  Enum ordinals are aligned with ITU-T H.273 / ISO/IEC 23091-2
 *  `video_full_range_flag` (CICP VideoFullRangeFlag) so middleware can
 *  forward the bitstream value verbatim by casting to `int`. The
 *  `UNKNOWN` sentinel uses `-1` (repo convention, see
 *  `hdmiinput.SignalState.UNKNOWN`).
 *
 *  - `LIMITED` is the standard studio (head/foot-room) range:
 *      8-bit  → 16..235 (luma), 16..240 (chroma)
 *      10-bit → 64..940 (luma), 64..960 (chroma)
 *  - `FULL` uses the full code range (0..255 / 0..1023). Common for
 *    sRGB content, JPEG-derived imagery, and some HDR mastering pipes.
 *
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type="int")
enum ColorRange {

    /** Range not signalled / unknown. */
    UNKNOWN = -1,

    /** Limited / studio / head-room range. CICP `video_full_range_flag` = 0. */
    LIMITED = 0,

    /** Full / PC / 0..255 (8-bit) range. CICP `video_full_range_flag` = 1. */
    FULL = 1,
}

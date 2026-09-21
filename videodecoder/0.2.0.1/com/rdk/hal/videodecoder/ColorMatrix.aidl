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
 *  @brief     YCbCr → RGB conversion matrix coefficients.
 *
 *  Identifies the matrix used to derive luma and chroma from the
 *  red/green/blue components (and the inverse for display). Enum ordinals
 *  are aligned with ITU-T H.273 / ISO/IEC 23091-2 `MatrixCoefficients`
 *  (CICP) so middleware can forward bitstream VUI values verbatim by
 *  casting to `int`. The `UNKNOWN` sentinel uses `-1` (repo convention,
 *  see `hdmiinput.SignalState.UNKNOWN`).
 *
 *  Critical distinction for HDR: `BT2020_NCL` (non-constant luminance)
 *  and `BT2020_CL` (constant luminance) differ — the bitstream signals
 *  which is in use. PQ/HLG HDR streams typically use `BT2020_NCL`.
 *
 *  CICP values not listed here (2 = unspecified, 3 = reserved, 4 = FCC,
 *  8 = YCgCo, 11 = SMPTE 2085, 12–14 = chroma-derived variants) are
 *  uncommon in distribution-grade content and are omitted; add them on
 *  demand.
 *
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type="int")
enum ColorMatrix {

    /** Matrix not signalled / unknown. */
    UNKNOWN = -1,

    /** Identity (RGB / GBR) — no YCbCr conversion. CICP value 0. */
    IDENTITY = 0,

    /** ITU-R BT.709 / SMPTE RP 177. CICP value 1. */
    BT709 = 1,

    /**
     * Unspecified by the bitstream — distinct from UNKNOWN. The stream
     * explicitly signalled "unspecified" (CICP value 2); downstream code
     * should apply a default. UNKNOWN by contrast means no signal was
     * carried at all (no AIDL override sent, no VUI in the bitstream).
     */
    UNSPECIFIED = 2,

    /** ITU-R BT.601-7 625-line (PAL/SECAM). CICP value 5. */
    BT601_625 = 5,

    /** ITU-R BT.601-7 525-line / SMPTE 170M (NTSC). CICP value 6. */
    BT601_525 = 6,

    /** SMPTE 240M. CICP value 7. */
    SMPTE240M = 7,

    /** ITU-R BT.2020 non-constant luminance. CICP value 9. */
    BT2020_NCL = 9,

    /** ITU-R BT.2020 constant luminance. CICP value 10. */
    BT2020_CL = 10,
}

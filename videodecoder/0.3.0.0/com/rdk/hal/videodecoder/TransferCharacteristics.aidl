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
 *  @brief     Opto-electrical transfer function (OETF / EOTF) — the
 *             gamma / HDR curve of the stream.
 *
 *  Enum ordinals are aligned with ITU-T H.273 / ISO/IEC 23091-2
 *  `TransferCharacteristics` (CICP) so middleware can forward bitstream
 *  VUI values verbatim by casting to `int`. The `UNKNOWN` sentinel uses
 *  `-1` (repo convention, see `hdmiinput.SignalState.UNKNOWN`).
 *
 *  This is the field that distinguishes HDR from SDR even when primaries
 *  are the same: HDR10 uses `SMPTE2084_PQ`, HLG uses
 *  `ARIB_STD_B67_HLG`, while their primaries are typically `BT.2020`.
 *
 *  CICP values 0 (reserved), 2 (unspecified), and 3 (reserved) are
 *  omitted; the rest are present and equal their CICP code points.
 *
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type="int")
enum TransferCharacteristics {

    /** Transfer characteristics not signalled / unknown. */
    UNKNOWN = -1,

    /** ITU-R BT.709 / BT.601 / BT.2020 10-bit SDR. CICP value 1. */
    BT709 = 1,

    /**
     * Unspecified by the bitstream — distinct from UNKNOWN. The stream
     * explicitly signalled "unspecified" (CICP value 2); downstream code
     * should apply a default. UNKNOWN by contrast means no signal was
     * carried at all (no AIDL override sent, no VUI in the bitstream).
     */
    UNSPECIFIED = 2,

    /** ITU-R BT.470 System M. Assumed display gamma 2.2. CICP value 4. */
    BT470M_GAMMA22 = 4,

    /** ITU-R BT.470 System B/G (PAL/SECAM). Assumed display gamma 2.8. CICP value 5. */
    BT470BG_GAMMA28 = 5,

    /** SMPTE 170M (NTSC). CICP value 6. */
    SMPTE170M = 6,

    /** SMPTE 240M. CICP value 7. */
    SMPTE240M = 7,

    /** Linear (no transfer). CICP value 8. */
    LINEAR = 8,

    /** Logarithmic, 100:1 contrast range. CICP value 9. */
    LOG_100 = 9,

    /** Logarithmic, 316.2:1 contrast range. CICP value 10. */
    LOG_316 = 10,

    /** IEC 61966-2-4 (xvYCC). CICP value 11. */
    IEC61966_2_4 = 11,

    /** ITU-R BT.1361 extended colour gamut. CICP value 12. */
    BT1361 = 12,

    /** IEC 61966-2-1 sRGB / sYCC. CICP value 13. */
    SRGB = 13,

    /** ITU-R BT.2020 10-bit SDR. CICP value 14. */
    BT2020_10 = 14,

    /** ITU-R BT.2020 12-bit SDR. CICP value 15. */
    BT2020_12 = 15,

    /** SMPTE ST 2084 (Perceptual Quantiser) — HDR10. CICP value 16. */
    SMPTE2084_PQ = 16,

    /** SMPTE ST 428-1 / DCDM. CICP value 17. */
    SMPTE428 = 17,

    /** ARIB STD-B67 (Hybrid Log-Gamma) — HLG. CICP value 18. */
    ARIB_STD_B67_HLG = 18,
}

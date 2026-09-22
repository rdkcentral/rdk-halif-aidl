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
 *  @brief     CIE chromaticity coordinates of the display primaries (the
 *             "colour gamut" of the stream).
 *
 *  Enum ordinals are aligned with ITU-T H.273 / ISO/IEC 23091-2
 *  `ColourPrimaries` (CICP) so middleware can forward bitstream VUI
 *  values verbatim by casting to `int`. The `UNKNOWN` sentinel uses `-1`
 *  (repo convention, see `hdmiinput.SignalState.UNKNOWN`).
 *
 *  In HDR signalling, primaries are typically `BT2020` while the transfer
 *  function (`TransferCharacteristics`) distinguishes the HDR system in use
 *  (PQ vs HLG).
 *
 *  CICP values 0 (reserved), 2 (unspecified), 3 (reserved), and 13–21
 *  (reserved) are omitted; the rest match their CICP code points.
 *
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type="int")
enum ColorPrimaries {

    /** Primaries not signalled / unknown. */
    UNKNOWN = -1,

    /** ITU-R BT.709 / SMPTE RP 177. CICP value 1. */
    BT709 = 1,

    /**
     * Unspecified by the bitstream — distinct from UNKNOWN. The stream
     * explicitly signalled "unspecified" (CICP value 2); downstream code
     * should apply a default. UNKNOWN by contrast means no signal was
     * carried at all (no AIDL override sent, no VUI in the bitstream).
     */
    UNSPECIFIED = 2,

    /** ITU-R BT.470 System M. CICP value 4. */
    BT470M = 4,

    /** ITU-R BT.470 System B/G (PAL/SECAM). CICP value 5. */
    BT470BG = 5,

    /** SMPTE 170M / ITU-R BT.601 525-line (NTSC). CICP value 6. */
    BT601_525 = 6,

    /** SMPTE 240M. CICP value 7. */
    SMPTE240M = 7,

    /** Generic film (Illuminant C). CICP value 8. */
    FILM = 8,

    /** ITU-R BT.2020 / BT.2100. CICP value 9. */
    BT2020 = 9,

    /** SMPTE ST 428-1 / DCDM. CICP value 10. */
    SMPTE428 = 10,

    /** DCI-P3 with D60 white point (theatrical). CICP value 11. */
    DCI_P3_D60 = 11,

    /** Display P3 — DCI-P3 with D65 white point (home video / streaming). CICP value 12. */
    DISPLAY_P3 = 12,

    /** EBU Tech 3213-E. CICP value 22. */
    EBU3213 = 22,
}

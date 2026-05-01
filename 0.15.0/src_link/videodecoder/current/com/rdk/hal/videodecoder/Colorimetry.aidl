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
 *  @brief     Colorimetry (colour primaries and matrix) of a video stream.
 *
 *  Identifies the colour space of the decoded video content. This is distinct
 *  from the HDMI output colorimetry signalling (hdmioutput.Colorimetry), which
 *  describes how the signal is carried over the HDMI link.
 *
 *  Values correspond to ITU-R and SMPTE colour primaries standards as
 *  referenced in ISO/IEC 23091-2 (CICP colour primaries).
 *
 *  @author    Gerald Weatherup
 */

@VintfStability
@Backing(type="int")
enum Colorimetry {

    /**
     * Colorimetry is unknown or not signalled in the stream.
     */
    UNKNOWN = 0,

    /**
     * ITU-R BT.601 525-line (NTSC).
     * Used for standard-definition NTSC content.
     */
    BT601_525 = 1,

    /**
     * ITU-R BT.601 625-line (PAL/SECAM).
     * Used for standard-definition PAL and SECAM content.
     */
    BT601_625 = 2,

    /**
     * ITU-R BT.709.
     * Used for high-definition content. The default for most HD streams.
     */
    BT709 = 3,

    /**
     * ITU-R BT.2020 (non-constant luminance).
     * Used for ultra-high-definition HDR content including HDR10 and HLG.
     * @see DynamicRange::HDR10, DynamicRange::HLG
     */
    BT2020 = 4,

    /**
     * ITU-R BT.2020 (constant luminance).
     * Variant of BT.2020 using a constant-luminance signal encoding.
     */
    BT2020_CL = 5,

    /**
     * DCI-P3 with D65 white point.
     * Used for HDR content mastered for home video display (HDR Blu-ray,
     * streaming with P3 mastering).
     */
    DCI_P3_D65 = 6,

    /**
     * DCI-P3 with D60 white point.
     * Used for content mastered for theatrical presentation.
     */
    DCI_P3_D60 = 7,
}

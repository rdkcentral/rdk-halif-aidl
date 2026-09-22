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

import com.rdk.hal.videodecoder.ColorRange;
import com.rdk.hal.videodecoder.ColorMatrix;
import com.rdk.hal.videodecoder.TransferCharacteristics;
import com.rdk.hal.videodecoder.ColorPrimaries;

/**
 *  @brief     Full colorimetry signalling for a video stream — the four
 *             independent axes carried by the bitstream VUI / container
 *             metadata.
 *
 *  Replaces the prior single-enum `Colorimetry` (which conflated all four
 *  axes into a single "BT709 / BT2020 / ..." label and could not, e.g.,
 *  distinguish PQ from HLG when primaries are the same). Field shape
 *  matches:
 *
 *  - ITU-T H.273 / ISO/IEC 23091-2 CICP (the H.264/HEVC VUI carries these
 *    four values as `video_full_range_flag`, `matrix_coefficients`,
 *    `transfer_characteristics`, `colour_primaries`).
 *  - GStreamer `GstVideoColorimetry` — middleware extracts the same four
 *    values from caps' `colorimetry` field. See issue #367 for the
 *    extraction pattern (`vci.range`, `vci.matrix`, `vci.transfer`,
 *    `vci.primaries`).
 *
 *  <h3>Default values</h3>
 *  All four fields default to their `UNKNOWN` sentinel so an unset
 *  parcelable equals "no colorimetry signalled". Carriers using this
 *  parcelable as an `@nullable` field can additionally distinguish
 *  "no override" (null) from "explicitly all UNKNOWN" (non-null with
 *  every field = UNKNOWN).
 *
 *  <h3>Common configurations</h3>
 *  - SDR BT.709 :  range=LIMITED, matrix=BT709,      transfer=BT709,            primaries=BT709
 *  - SDR BT.601 :  range=LIMITED, matrix=BT601_525,  transfer=SMPTE170M,        primaries=BT601_525  (NTSC)
 *  - HDR10 (PQ) :  range=LIMITED, matrix=BT2020_NCL, transfer=SMPTE2084_PQ,     primaries=BT2020
 *  - HLG        :  range=LIMITED, matrix=BT2020_NCL, transfer=ARIB_STD_B67_HLG, primaries=BT2020
 *  - sRGB       :  range=FULL,    matrix=IDENTITY,   transfer=SRGB,             primaries=BT709
 *
 *  @author    Gerald Weatherup
 */
@VintfStability
parcelable Colorimetry {

    /**
     * Sample quantisation range (limited / studio vs full / computer).
     * GStreamer mapping: `GstVideoColorimetry.range` → `hdrColorimetry[0]`.
     */
    ColorRange range = ColorRange.UNKNOWN;

    /**
     * YCbCr → RGB conversion matrix coefficients.
     * GStreamer mapping: `GstVideoColorimetry.matrix` → `hdrColorimetry[1]`.
     */
    ColorMatrix matrix = ColorMatrix.UNKNOWN;

    /**
     * Opto-electrical transfer function (gamma / HDR curve).
     * GStreamer mapping: `GstVideoColorimetry.transfer` → `hdrColorimetry[2]`.
     * This is the field that distinguishes HDR systems (PQ vs HLG) when
     * primaries are the same.
     */
    TransferCharacteristics transfer = TransferCharacteristics.UNKNOWN;

    /**
     * Colour primaries (the gamut chromaticities).
     * GStreamer mapping: `GstVideoColorimetry.primaries` → `hdrColorimetry[3]`.
     */
    ColorPrimaries primaries = ColorPrimaries.UNKNOWN;
}

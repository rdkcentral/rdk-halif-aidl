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

import com.rdk.hal.videodecoder.CodecProfile;
import com.rdk.hal.videodecoder.CodecLevel;

/**
 *  @brief     Per-profile capability descriptor for a codec — pairs a
 *             `CodecProfile` with the maximum level and bitrate the
 *             decoder advertises for that profile.
 *
 *  Used inside `CodecCapabilities.profiles[]` so a codec entry can
 *  advertise multiple profiles independently. The previous model
 *  (single `profile` + `level` per codec) couldn't express the common
 *  case where hardware supports several profiles per codec at the same
 *  level (e.g. H.265 supporting MAIN, MAIN_10, and MAIN_10_HDR10 each
 *  at LEVEL_5_2).
 *
 *  <h3>"Max" semantics</h3>
 *  Both `maxLevel` and `maxBitrateInBps` are inclusive ceilings. All
 *  lower levels for the same profile are implicitly supported. A
 *  bitstream at or below `maxLevel` and at or below `maxBitrateInBps`
 *  is in-spec for this profile.
 *
 *  Shape mirrors `rdk-hpk-documentation/hfp-reference/videodecoder/
 *  hfp-videodecoder.yaml` field-for-field so the HFP YAML reads as a
 *  direct serialisation of the AIDL parcelable.
 *
 *  @author    Gerald Weatherup
 */
@VintfStability
parcelable Profile {

    /**
     * The codec profile this descriptor applies to (e.g. `H265_MAIN`,
     * `H265_MAIN_10`, `AV1_MAIN`).
     */
    CodecProfile profile;

    /**
     * The maximum supported level for this profile. All lower levels
     * for the same profile are also supported.
     */
    CodecLevel maxLevel;

    /**
     * The maximum decode bitrate in bits per second for this
     * profile/level combination.
     *
     * Use `0` to indicate "no explicit limit advertised" — most
     * platforms should report a real ceiling here, but `0` keeps the
     * field non-null for cases where the SoC vendor genuinely doesn't
     * publish a bitrate cap.
     */
    long maxBitrateInBps;
}

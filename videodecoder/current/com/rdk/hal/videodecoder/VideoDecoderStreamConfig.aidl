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

import com.rdk.hal.videodecoder.Resolution;
import com.rdk.hal.videodecoder.Fraction;
import com.rdk.hal.videodecoder.Colorimetry;
import com.rdk.hal.videodecoder.MasteringDisplayInfo;
import com.rdk.hal.videodecoder.ContentLightLevel;
import com.rdk.hal.videodecoder.DolbyVisionLayerFlags;

/**
 *  @brief     Atomic stream-configuration batch for the video decoder.
 *
 *  Carries the full set of container/manifest-derived stream-description
 *  hints in a single parcelable. Submitted via
 *  `IVideoDecoderController.setStreamConfig()` in `State::READY`, before
 *  decoding starts, as one atomic transaction.
 *
 *  Fields are `@nullable` except `colorimetry`, which carries its own
 *  `UNKNOWN` sentinel because AIDL does not permit `@nullable` on enums.
 *  Semantics:
 *  - non-null (or `colorimetry` ≠ `UNKNOWN`) — apply this value as the hint
 *  - null (or `colorimetry == UNKNOWN`)      — leave the existing hint
 *                                              unchanged (no-op for that field)
 *
 *  The "no change" semantics let clients send partial updates without
 *  having to repeat values they have already configured.
 *
 *  <h3>Hint precedence and persistence</h3>
 *  - Bitstream-derived metadata wins over the hint when both are present;
 *    the hint is the fallback used only when the bitstream is silent.
 *  - The decoder reports the value it actually used in `FrameMetadata`.
 *  - Hints persist across `flush()` and are cleared on `close()`.
 *
 *  <h3>Validation</h3>
 *  - `resolution`        — `width` and `height` MUST be > 0.
 *  - `frameRate`         — `denominator` MUST be > 0 unless `numerator`
 *                          is also 0 (encodes "unknown").
 *  - `pixelAspectRatio`  — both fields MUST be >= 0; the only valid
 *                          "unknown" encoding is 0/0.
 *
 *  @see IVideoDecoderController.setStreamConfig()
 *  @see Resolution
 *  @see Fraction
 *  @see Colorimetry
 *  @see MasteringDisplayInfo
 *  @see ContentLightLevel
 *  @see DolbyVisionLayerFlags
 *
 *  @author    Gerald Weatherup
 */
@VintfStability
parcelable VideoDecoderStreamConfig {

    /**
     * Coded frame dimensions.
     * null = leave existing resolution hint unchanged.
     */
    @nullable Resolution resolution;

    /**
     * Stream frame rate as numerator / denominator.
     * 0/0 encodes "unknown".
     * null = leave existing frame rate hint unchanged.
     */
    @nullable Fraction frameRate;

    /**
     * Pixel aspect ratio as numerator / denominator.
     * 0/0 encodes "unknown".
     * null = leave existing PAR hint unchanged.
     */
    @nullable Fraction pixelAspectRatio;

    /**
     * Colorimetry (colour primaries and matrix) for the stream.
     * AIDL enums cannot be `@nullable`,
     * so this field uses `Colorimetry::UNKNOWN` (the default for an unset
     * enum) to encode "leave existing colorimetry hint unchanged".
     * Any other value applies as a hint.
     */
    Colorimetry colorimetry = Colorimetry.UNKNOWN;

    /**
     * Mastering display colour volume metadata (SMPTE ST 2086).
     * null = leave existing mastering display hint unchanged.
     */
    @nullable MasteringDisplayInfo masteringDisplayInfo;

    /**
     * Content light level metadata (CTA-861.3 MaxCLL / MaxFALL).
     * null = leave existing content light level hint unchanged.
     */
    @nullable ContentLightLevel contentLightLevel;

    /**
     * Dolby Vision layer presence flags. Only applicable when the
     * stream DynamicRange is DOLBY_VISION.
     * null = leave existing Dolby Vision layer hint unchanged.
     */
    @nullable DolbyVisionLayerFlags dolbyVisionLayerFlags;
}

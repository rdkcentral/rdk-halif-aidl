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

import com.rdk.hal.videodecoder.Fraction;
import com.rdk.hal.videodecoder.Colorimetry;
import com.rdk.hal.videodecoder.MasteringDisplayInfo;
import com.rdk.hal.videodecoder.ContentLightLevel;
import com.rdk.hal.videodecoder.DolbyVisionLayerFlags;

/**
 *  @brief     Per-buffer metadata carried with input buffers submitted via
 *             `IVideoDecoderController.decodeBufferWithMetadata()`.
 *
 *  Describes properties of the encoded frame that cannot be derived from the
 *  buffer contents alone, such as its presentation time, plus optional
 *  container-derived metadata overrides that apply from this frame onward.
 *
 *  <h3>Field semantics</h3>
 *  The fields fall into two categories with distinct semantics:
 *
 *  <h4>Non-nullable per-buffer fields (`nsPresentationTime`, `discontinuity`)</h4>
 *  These describe the encoded frame itself. Each `decodeBufferWithMetadata()`
 *  call is self-describing for these fields: the HAL MUST NOT carry state
 *  from this parcelable across calls. A subsequent call with default-valued
 *  fields replaces, it does not preserve, the previous call's values.
 *
 *  <h4>Override fields (`colorimetry`, `masteringDisplayInfo`,
 *  `contentLightLevel`, `dolbyVisionLayerFlags`, `pixelAspectRatio`)</h4>
 *  All five are `@nullable`. For `colorimetry`, sub-axes the caller
 *  doesn't want to override are left at their `UNKNOWN` sentinel within
 *  a non-null parcelable — e.g. setting `colorimetry.matrix` to
 *  `BT2020_NCL` while leaving `range`/`transfer`/`primaries` at
 *  `UNKNOWN` overrides only the matrix axis. (Pass `null` to leave all
 *  four axes unchanged from the prior override / setStreamConfig
 *  state.)
 *  These mirror the matching fields on `VideoDecoderStreamConfig` and let
 *  middleware push container-derived metadata that changes mid-stream
 *  (e.g. ABR per-Period HDR transition, SSAI ad insertion, live→VOD switch).
 *
 *  - non-null                — apply this override from this buffer onward;
 *                              persists for subsequent buffers until a later
 *                              override (or a `setStreamConfig()` call)
 *                              replaces it.
 *  - null                    — no change for this field; the previously
 *                              applied override (or the value set in
 *                              `State::READY` via `setStreamConfig()`)
 *                              remains in effect.
 *
 *  Override precedence and persistence matches the `VideoDecoderStreamConfig`
 *  contract: bitstream-derived metadata still wins over the override;
 *  overrides are the fallback used only when the bitstream is silent.
 *  Overrides persist across `flush()` and are cleared on `close()`.
 *
 *  <h3>Scope</h3>
 *  Bitstream-driven properties (resolution / frame rate) are intentionally
 *  omitted from the override fields — on modern codecs these are signalled
 *  per-SPS in the bitstream and middleware should not override them
 *  mid-stream. Codec or encryption-mode changes are also out of scope and
 *  require a decoder teardown / `IVideoDecoder.open()` cycle.
 *
 *  @see IVideoDecoderController.decodeBufferWithMetadata()
 *  @see IVideoDecoderController.setStreamConfig()
 *  @see VideoDecoderStreamConfig
 *
 *  @author    Gerald Weatherup
 */

@VintfStability
parcelable InputBufferMetadata {

    /**
     * Presentation time of the encoded frame in nanoseconds.
     */
    long nsPresentationTime;

    /**
     * Marks this buffer as the first following a PTS discontinuity.
     *
     * When true, the PTS of this buffer is discontinuous with previously
     * submitted buffers: the decoder MUST reset its PTS tracking and
     * interpolation state before decoding this buffer, and MUST NOT
     * interpolate timestamps across the discontinuity. Decoded output from
     * this buffer onward reports the new timeline; the first output frame
     * decoded from this buffer carries `FrameMetadata.discontinuity = true`.
     *
     * This is the sole discontinuity signal and is per-buffer in-band.
     * `flush()` also resets PTS state; this flag covers in-band
     * discontinuities without flushing queued data.
     *
     * @see FrameMetadata.discontinuity
     */
    boolean discontinuity;

    /**
     * Optional colorimetry override applied from this buffer onward.
     * null = no change. Non-null applies the override; sub-axes the
     * caller doesn't want to override are left at their `UNKNOWN`
     * sentinel within the non-null parcelable.
     *
     * @see VideoDecoderStreamConfig.colorimetry, IVideoDecoderController.setStreamConfig()
     */
    @nullable Colorimetry colorimetry;

    /**
     * Optional mastering display colour volume override (SMPTE ST 2086)
     * applied from this buffer onward. null = no change.
     *
     * @see VideoDecoderStreamConfig.masteringDisplayInfo, IVideoDecoderController.setStreamConfig()
     */
    @nullable MasteringDisplayInfo masteringDisplayInfo;

    /**
     * Optional content light level override (CTA-861.3 MaxCLL / MaxFALL)
     * applied from this buffer onward. null = no change.
     *
     * @see VideoDecoderStreamConfig.contentLightLevel, IVideoDecoderController.setStreamConfig()
     */
    @nullable ContentLightLevel contentLightLevel;

    /**
     * Optional Dolby Vision layer-flags override applied from this buffer
     * onward. Only meaningful when the stream DynamicRange is
     * DOLBY_VISION.
     * null = no change.
     *
     * @see VideoDecoderStreamConfig.dolbyVisionLayerFlags, IVideoDecoderController.setStreamConfig()
     */
    @nullable DolbyVisionLayerFlags dolbyVisionLayerFlags;

    /**
     * Optional pixel aspect ratio override applied from this buffer onward.
     * 0/0 encodes "unknown" (matching the
     * `VideoDecoderStreamConfig.pixelAspectRatio` rule).
     * null = no change.
     *
     * @see VideoDecoderStreamConfig.pixelAspectRatio, IVideoDecoderController.setStreamConfig()
     */
    @nullable Fraction pixelAspectRatio;
}

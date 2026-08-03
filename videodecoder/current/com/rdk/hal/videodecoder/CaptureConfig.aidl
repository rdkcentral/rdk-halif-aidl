/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
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
 *  @brief     Output configuration for a decoder producing frames for capture.
 *
 *  Capture is decode-to-texture: the decoder writes frames the client imports as GPU
 *  textures rather than emitting them to a display plane. The format and size of those
 *  frames are properties of the decoder's output, so they are configured here and
 *  nowhere else. A capture destination consumes what the decoder produces; it does not
 *  negotiate a second format, which is what keeps the two from disagreeing.
 *
 *  Submitted via `IVideoDecoderController.setCaptureConfig()` in `State::READY`, before
 *  the decoder is started. Applying a configuration is what puts the decoder into
 *  capture output - there is no separate mode to select, because a decoder configured
 *  to produce capture frames is in capture mode by construction. It is cleared on
 *  `close()`.
 *
 *  A configuration the decoder cannot produce is rejected at
 *  `setCaptureConfig()` rather than accepted and silently substituted.
 *
 *  <h3>The decoder does not transform the frame</h3>
 *  Frames are emitted at the resolution the stream decodes to and in its source
 *  colorimetry. The decoder MUST NOT scale, rotate, crop, colour-convert,
 *  tone-map or gamma-adjust on this path. Shape and colour belong to the
 *  consumer, which applies them per frame as it textures the frame onto its
 *  scene, and they may change on any frame - so a transform applied here would
 *  have to be undone, and a frame the consumer cannot untransform is a frame it
 *  cannot use. `width` and `height` size the buffers; they do not request a
 *  scale.
 *
 *  `drmFourcc` says what the pixels are; `drmModifier` says how those bytes are
 *  arranged in memory. The same format under two modifiers is the same picture in two
 *  layouts, and a consumer that cannot read the layout cannot read the frame. Choosing
 *  between them trades memory bandwidth against portability - see the module
 *  documentation, "Pixel Format and Memory Layout".
 *
 *  @see IVideoDecoderController.setCaptureConfig()
 *  @see Capabilities.supportedCaptureFourCCs, Capabilities.supportedCaptureModifiers
 *
 *  @author    Gerald Weatherup
 */
@VintfStability
parcelable CaptureConfig {

    /**
     * The DRM FOURCC pixel format the decoder emits in capture mode.
     *
     * FOURCC codes are defined by the Linux kernel in `include/uapi/drm/drm_fourcc.h`,
     * not by this interface. They are carried as an integer rather than an enum because
     * the kernel owns that namespace: new formats arrive with new kernel versions, and
     * enumerating them here would make every kernel addition an interface change to a
     * value this HAL neither defines nor controls.
     *
     * Must be one of `Capabilities.supportedCaptureFourCCs`.
     * `DRM_FORMAT_NV12` (0x3231564E) is required to be supported by every decoder that
     * supports capture at all.
     */
    int drmFourcc;

    /**
     * The DRM format modifier describing the memory layout the decoder writes.
     *
     * Modifiers are defined by the Linux kernel in `include/uapi/drm/drm_fourcc.h`.
     * A modifier is 64 bits composed as `(vendor << 56) | value`: the top 8 bits are a
     * registered vendor namespace and the rest means whatever that vendor says, so most
     * modifiers are specific to the hardware that defines them. A compressed layout is
     * usually a parameterised family rather than a single value, which is why the
     * declaration lists exact values rather than layout names, and why these are
     * integers rather than an enum.
     *
     * `DRM_FORMAT_MOD_LINEAR` (0) is the one vendor-neutral layout, and the only one a
     * consumer that must touch the pixels - CPU readback, an encoder, or a GPU from a
     * different vendor - can rely on.
     *
     * Must be one of `Capabilities.supportedCaptureModifiers`.
     * `DRM_FORMAT_MOD_LINEAR` (0) is required to be supported by every decoder that
     * supports capture at all.
     */
    long drmModifier;

    /**
     * The maximum frame width in pixels the capture buffers must accommodate.
     *
     * THIS IS NOT A SCALING REQUEST. Frames are emitted at the resolution the
     * stream decodes to, and this sizes the buffers that hold them. A stream
     * that decodes smaller produces smaller frames, and
     * `VideoFrameView.width` reports what each frame actually is.
     *
     * Must not exceed the `CodecCapabilities.maxFrameWidth` of the codec the decoder
     * was opened for.
     */
    int width;

    /**
     * The maximum frame height in pixels the capture buffers must accommodate.
     *
     * As `width`, this sizes the buffers rather than requesting a scale.
     *
     * Must not exceed the `CodecCapabilities.maxFrameHeight` of the codec the decoder
     * was opened for.
     */
    int height;
}

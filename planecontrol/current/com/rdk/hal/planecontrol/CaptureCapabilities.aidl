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
package com.rdk.hal.planecontrol;

import com.rdk.hal.videodecoder.Codec;

/**
 *  @brief     Capture capabilities definition for a plane resource.
 *
 *  Describes what frames this capture plane can deliver and how its buffer pool
 *  behaves. This is the whole of the capture declaration: a client reads it, selects
 *  from it through `CaptureProperty`, and the vendor layer configures whatever it needs
 *  to on the decoder to satisfy the selection.
 *
 *  @author    Gerald Weatherup
 */

@VintfStability
parcelable CaptureCapabilities
{
    /**
     * The maximum number of buffers that can be reserved in the capture pool.
     *
     * A reservation that exceeds what the platform's video memory region can satisfy
     * fails at `ICaptureController.start()` with `CaptureErrorCode.OUT_OF_MEMORY`.
     *
     * @see CaptureProperty.BUFFER_COUNT, CaptureErrorCode.OUT_OF_MEMORY
     */
    int maxBufferCount;

    /**
     * Indicates the behaviour when every buffer in the pool is locked by the client and
     * the decoder has a new frame to write.
     *
     * When true, the decoder stalls until a buffer is released.
     * When false, the oldest Ready buffer is recycled and its frame is dropped.
     * Decode proceeds at full rate in both cases for as long as buffers are available.
     */
    boolean stallsWhenPoolExhausted;

    /**
     * The DRM FOURCC pixel formats this capture plane can deliver.
     *
     * FOURCC codes are defined by the Linux kernel in `include/uapi/drm/drm_fourcc.h`,
     * not by this interface, so they are carried as integers rather than an enum: the
     * kernel owns that namespace and new formats arrive with new kernel versions.
     *
     * These are opaque values passed through this interface to the client EGL
     * implementation without interpretation by the HAL client.
     *
     * `DRM_FORMAT_NV12` (0x3231564E) is required to be present.
     *
     * @see CaptureProperty.DRM_FOURCC
     */
    int[] supportedFourCCs;

    /**
     * The DRM format modifiers this capture plane can deliver.
     *
     * Also defined by the kernel in `include/uapi/drm/drm_fourcc.h`. A modifier is a
     * 64-bit namespaced value whose top 8 bits carry a vendor prefix, which is what
     * lets a vendor declare its own tiling or compression layouts.
     *
     * These are opaque values passed through this interface to the client EGL
     * implementation without interpretation by the HAL client.
     *
     * `DRM_FORMAT_MOD_LINEAR` (0) is required to be present.
     *
     * @see CaptureProperty.DRM_MODIFIER
     */
    long[] supportedModifiers;

    /**
     * The maximum frame width in pixels this capture plane can deliver.
     *
     * @see CaptureProperty.WIDTH
     */
    int maxFrameWidth;

    /**
     * The maximum frame height in pixels this capture plane can deliver.
     *
     * @see CaptureProperty.HEIGHT
     */
    int maxFrameHeight;

    /**
     * The video codecs whose decoded frames this plane can capture.
     *
     * Capture is not required of every codec a platform can decode. A decoder opened
     * for a codec outside this list decodes and displays normally; what it cannot do is
     * feed a capture plane.
     *
     * `Codec.H264` is required to be present on every capture plane. It is the codec
     * decode-to-texture is certified against, and a client that can negotiate nothing
     * else always has a working path.
     *
     * @see com.rdk.hal.videodecoder.Codec
     */
    Codec[] supportedCodecs;

    /**
     * Whether this plane can deliver frames at a resolution other than the one the
     * mapped source is decoding.
     *
     * When false, `CaptureProperty.WIDTH` and `HEIGHT` must equal the resolution the
     * mapped source decodes to, and `ICaptureController.start()` fails with
     * `CaptureErrorCode.RESOLUTION_MISMATCH` if they do not. Nothing is scaled: the
     * frames the client receives are the frames the decoder produced.
     *
     * Declaring false is what keeps the tested surface small - a plane that never
     * scales has no scaling quality to validate and no resolution permutations to
     * cover.
     *
     * @see CaptureProperty.WIDTH, CaptureProperty.HEIGHT, CaptureErrorCode.RESOLUTION_MISMATCH
     */
    boolean resize;
}

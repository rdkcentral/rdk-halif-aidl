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
import com.rdk.hal.videodecoder.CodecCapabilities;
import com.rdk.hal.videodecoder.Colorimetry;
import com.rdk.hal.videodecoder.DynamicRange;

/**
 *  @brief     Video decoder capabilities definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
parcelable Capabilities
{
	/**
	 * Array of CodecCapability parcelables supported by this video decoder instance.
	 */
    CodecCapabilities[] supportedCodecs;

	/**
	 * Array of DynamicRange values supported by this video decoder instance.
	 */
    DynamicRange[] supportedDynamicRanges;

	/**
	 * Array of Colorimetry values that this decoder instance can detect and report
	 * in FrameMetadata.colorimetry. An empty array indicates colorimetry detection
	 * is not supported.
	 */
    Colorimetry[] supportedColorimetries;

	/**
	 * Indicates if this decoder instance can work in secure video path (SVP) mode.
	 * @see Property.SECURE_VIDEO
	 */
    boolean supportsSecure;

	/**
	 * DRM FOURCC pixel formats this decoder can emit for capture (decode-to-texture).
	 *
	 * A non-empty list is what declares that this decoder supports capture at all;
	 * there is no separate mode flag to advertise.
	 *
	 * FOURCC codes are defined by the Linux kernel in
	 * `include/uapi/drm/drm_fourcc.h`, not by this interface, so they are carried as
	 * integers rather than an enum: the kernel owns that namespace and new formats
	 * arrive with new kernel versions.
	 *
	 * Empty where the decoder does not support capture. Where it is non-empty,
	 * `DRM_FORMAT_NV12` (0x3231564E) is required to be present.
	 *
	 * @see CaptureConfig.drmFourcc, IVideoDecoderController.setCaptureConfig()
	 */
    int[] supportedCaptureFourCCs;

	/**
	 * DRM format modifiers this decoder can emit for capture (decode-to-texture).
	 *
	 * Also defined by the kernel in `include/uapi/drm/drm_fourcc.h`. A modifier is a
	 * 64-bit namespaced value whose top 8 bits carry a vendor prefix, which is what
	 * lets a vendor declare its own tiling or compression layouts.
	 *
	 * Empty where the decoder does not support capture. Where it is non-empty,
	 * `DRM_FORMAT_MOD_LINEAR` (0) is required to be present.
	 *
	 * @see CaptureConfig.drmModifier
	 */
    long[] supportedCaptureModifiers;
}

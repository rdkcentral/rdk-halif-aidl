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
import com.rdk.hal.videodecoder.Codec;
import com.rdk.hal.videodecoder.CodecProfile;
import com.rdk.hal.videodecoder.CodecLevel;
import com.rdk.hal.videodecoder.PixelFormat;

/**
 *  @brief     Codec capability definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */

@VintfStability
parcelable CodecCapabilities
{
	/**
	 * Defines the video codec type.
	 */
    Codec codec;

  	/**
     * Defines the profile for this Codec.
     */
    CodecProfile profile;

    /**
     * Defines the level for this Codec.
     */
    CodecLevel level;
	/**
	 * The maximum frame rate (FPS) supported for decode for this Codec.
	 * e.g. 25, 30, 50, 60, 120.
	 */
    int maxFrameRate;

	/**
	 * The maximum frame width (pixels) supported for decode for this Codec.
	 */
    int maxFrameWidth;

	/**
	 * The maximum frame height (pixels) supported for decode for this Codec.
	 */
    int maxFrameHeight;

    /**
     * Pixel formats the decoder can produce on its output for this
     * codec/profile/level entry.
     *
     * Captures the chroma format constraint at the level where it physically
     * lives — the decoder. For example, a SoC whose H.264 hardware is profile-
     * locked at silicon and only outputs 4:2:0 advertises
     * `[YCBCR420]` here; a part that decodes the High profile bitstream but
     * downsamples to 4:2:0 on output also advertises `[YCBCR420]`. A SoC
     * supporting both 4:2:0 and 4:4:4 advertises `[YCBCR420, YCBCR444]`.
     *
     * Hardware support typically varies per codec block — a SoC's VP9 path
     * might do 4:4:4 on the same silicon where the H.264 path does not — so
     * the list is per-codec/profile/level entry rather than a single global
     * list on `Capabilities`.
     *
     * Used by the middleware at capability-discovery time to reject
     * incompatible streams before binding the decoder, rather than failing
     * inside `decodeBufferWithMetadata()` after start.
     *
     * @see PixelFormat
     */
    PixelFormat[] supportedOutputPixelFormats;
}

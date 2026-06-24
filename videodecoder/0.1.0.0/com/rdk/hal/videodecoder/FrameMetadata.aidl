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
import com.rdk.hal.videodecoder.ScanType;
import com.rdk.hal.videodecoder.PixelFormat;
import com.rdk.hal.videodecoder.DynamicRange;
import com.rdk.hal.videodecoder.MasteringDisplayInfo;
import com.rdk.hal.videodecoder.ContentLightLevel;
import com.rdk.hal.videodecoder.Colorimetry;
import com.rdk.hal.AVSource;

/**
 *  @brief     Decoded video frame metadata, relating to the frame output from the video decoder.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
parcelable FrameMetadata {

    /**
	 * Pixel aspect ratio (PAR) defined as the ratio parX:parY.
     * e.g. 1:1 for square pixels, 480i=10:11, 576i=59:54
     * @see Rec.601 and https://en.wikipedia.org/wiki/Pixel_aspect_ratio
     */
    int parX;
    int parY;

    /**
	 * Source aspect ratio (SAR) defined as the ratio sarX:sarY.
     * e.g. 720:480, 3840:2160
     */
    int sarX;
    int sarY;

	/**
	 * The coded width and height of the video frame in pixels.
	 * Decoded video frame buffers hold the video frame in coded dimensions.
	 */
    int codedWidth;
    int codedHeight;

	/**
	 * The active display dimensions of the video frame in pixels.
	 * These dimensions can be smaller than the coded dimensions to specify a
	 * smaller central region to display inside the coded video frame.
	 * The active dimensions should reflect any display frame or bar data from the stream.
	 */
    int activeX;
	int activeY;
    int activeWidth;
	int activeHeight;

	/**
	 * The color depth in bits.
	 * e.g. 8, 10, 12.
	 */
    int colorDepth;

	/**
	 * Pixel format of the video frame.
	 */
	PixelFormat pixelFormat;

	/**
	 * Dynamic range of the video frame.
	 */
	DynamicRange dynamicRange;

	/**
	 * The picture scan type output from the decoder.
	 */
    ScanType scanType;

	/**
	 * Active format description code.
	 * See https://en.wikipedia.org/wiki/Active_Format_Description
	 */
    int afd;

	/**
	 * Frame rate decoded from the video stream expressed as a fraction.
	 * Use 0/0 if unknown.e
	 * e.g. 24fps = 24/1, 59.94fps = 60000/1001
	 */
	int frameRateNumerator;
	int frameRateDenominator;

	/**
	 * End-of-stream marker delivered to the client on the FINAL
	 * `IVideoDecoderControllerListener.onFrameOutput()` callback of the
	 * decode session.
	 *
	 * When true, this is the final `onFrameOutput()` callback of the session.
	 * The HAL delivers it exactly once per session. There is no separate
	 * EOS-only marker callback - `endOfStream = true` rides on the metadata
	 * of the last real decoded frame in non-tunnelled mode, or on the final
	 * tunnelled-mode metadata callback in tunnelled mode (where
	 * `frameAVBufferHandle = -1` is the normal case).
	 *
	 * The HAL MUST deliver a non-null `FrameMetadata` on the EOS callback so
	 * clients can reliably detect EOS via `metadata.endOfStream`. This follows
	 * from the existing "metadata is non-null when it changes" rule -
	 * `endOfStream` transitioning from false to true is a metadata change.
	 * The other fields of this parcelable describe the final frame as normal.
	 *
	 * EOS originates either from the HAL detecting an in-bitstream EOS marker
	 * (MPEG-2 sequence_end_code, H.264/H.265 end_of_stream NAL, MPEG-4 Part 2
	 * visual_object_sequence_end_code) or from the client submitting a final
	 * buffer via `IVideoDecoderController.decodeBufferWithMetadata()` with
	 * `InputBufferMetadata.endOfStream = true`. Both sources collapse to a
	 * single event on this side.
	 *
	 * After this callback the decoder remains in `State::STARTED` but is
	 * drained. No further `onFrameOutput()` is delivered until `flush()` or
	 * `stop()` + `start()`.
	 *
	 * @see IVideoDecoderController.decodeBufferWithMetadata()
	 * @see InputBufferMetadata.endOfStream
	 */
	boolean endOfStream;

	/**
	 * Discontinuity indicator where the PTS for this frame is likely to be discontinuous to the previous.
	 */
	boolean discontinuity;

	/**
	 * Indicates if the video should be delivered in low latency mode.
	 */
	boolean lowLatency;

	/**
	 * Colorimetry (colour primaries and matrix) of the video frame as reported by the decoder.
	 * Set to Colorimetry::UNKNOWN if not signalled in the stream.
	 */
	Colorimetry colorimetry;

	/**
	 * Mastering display colour volume metadata (SMPTE ST 2086).
	 * Extracted from HEVC SEI type 137 or equivalent. Null if not present in the stream.
	 */
	@nullable MasteringDisplayInfo masteringDisplayInfo;

	/**
	 * Content light level static HDR metadata (MaxCLL/MaxFALL as defined in CTA-861.3).
	 * Extracted from HEVC SEI type 144 or equivalent. Null if not present in the stream.
	 */
	@nullable ContentLightLevel contentLightLevel;

	/**
	 * The source of the video frame.
	 * When the frame is presented the source may be used to configure the TV picture mode settings.
	 */
	AVSource source;

	/**
	 * SHA1 calculation value.
	 * Only set when SHA1_CALC is set 1=on
	 */
	byte[] sha1;

	/**
	 * Private extension for future use.
	 */
    ParcelableHolder extension;
}

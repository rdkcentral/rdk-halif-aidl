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
 *  @brief     Video decoder properties used in property get/set functions.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
@Backing(type="int")
enum Property {
	/**
	 * Unique ID per decoder resource instance.
	 *
	 * Type: Integer
	 * Access: Read-only.
	 *
	 * @exception binder::Status::Exception::EX_NONE for success
	 * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
	 *
	 */
	RESOURCE_ID = 0,

	/**
	 * Video decode buffer input queue size in bytes.
	 * The default is set by the vendor to best suit the platform.
	 *
	 * Type: Integer
	 * Access: Read-only.
	 *
	 * @exception binder::Status::Exception::EX_NONE for success
	 * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
	 *
	 */
	INPUT_QUEUE_DEPTH = 1,

	/**
	 * Number of frame buffers in the vendor frame buffer pool.
	 * The default is vendor defined.
	 *
	 * Type: Integer
	 * Access: Read-only
	 *
	 * @exception binder::Status::Exception::EX_NONE for success
	 * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
	 *.
	 */
    OUTPUT_FRAME_POOL_SIZE = 2,

	/**
	 * The current selected operational mode.
	 * 
	 * Only modes returned by `IVideoDecoderManager.getSupportedOperationalModes()` can be set.
	 * The default must be either `OperationalMode::TUNNELLED` or `OperationalMode::NON_TUNNELLED`
	 * which is chosen by the OEM/vendor.
	 * `OperationalMode::TUNNELLED` and `OperationalMode::NON_TUNNELLED` are mutually exclusive.
	 * If `OperationalMode::GRAPHICS_TEXTURE` is supported, it can be set on its own or ORed with 
	 * `OperationalMode::TUNNELLED` or `OperationalMode::NON_TUNNELLED`
	 *
	 * Type: Integer
	 * @see enum OperationalMode for possible values.
	 * Access: Read-write.
	 * Write in states: READY, STARTED
	 *
	 * @exception binder::Status::Exception::EX_NONE for success
	 * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state or non STARTED state.
	 *
	 */
    OPERATIONAL_MODE = 3,

	/**
	 * Low latency mode sets the expectation that no B-frames will be delivered in
	 * the video stream or B-frames can be skipped over and the decoder should 
	 * output decoded frames as soon as possible.
	 * Low latency video is often combined with low latency audio decoder/sink
	 * operation for gaming and casting applications.
	 * Can be set while video decoder resource is in READY.
	 *
	 * Type: Integer
	 *  0 - off (default on open)
	 *  1 - on
	 * Access: Read-write.
	 * Write in states: READY
	 *
	 * @exception binder::Status::Exception::EX_NONE for success
	 * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
	 *
	 */
	LOW_LATENCY_MODE = 4,

	/**
	 * The policy to follow when video decode errors occur.
	 *
	 * Type: Integer
	 *  0 - output corrupt frames (default on open)
	 *  1 - conceal corrupt frames, not output from decoder
	 * Access: Read-write.
	 * Write in states: READY
	 *
	 * @exception binder::Status::Exception::EX_NONE for success
	 * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
	 *
	 */
	DECODE_ERROR_POLICY = 5,

	/**
	 * Set by the client to specify the AV source of the stream.
	 * The AVSource is also set inside the FrameMetadata when output by a decoder.
	 *
	 * Type: Integer
	 *  0 - AVUNKNOWN (default on open)
	 * @see enum AVSource for possible values.
	 * Access: Read-write.
	 * Write in states: READY
	 *
	 * @exception binder::Status::Exception::EX_NONE for success
	 * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
	 *
	 */
	AV_SOURCE = 6,

	/**
	 * Set by the client to request SHA-1 calculation for the decoded video frame.
	 * Scans pixel locations from the top left, along lines and down all rows.
	 * The SHA-1 is returned in the frame metadata.
	 * 
	 * Type: Integer
	 *  0 - off (default on open)
	 *  1 - on
	 * Access: Read-write.
	 * Write in states: READY, STARTED
	 *
	 * @exception binder::Status::Exception::EX_NONE for success
	 * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state or non STARTED state.
	 *
	 */
	SHA1_CALC = 7,

	/**
	 * Indicates if the video decoder was opened for secure video path.
	 *
	 * Type: Integer
	 *  0 - off
	 *  1 - on (only if supported)
	 * Access: Read-only.
	 * @see Capabilities.supportsSecure IVideoDecoder.open()
	 *
	 * @exception binder::Status::Exception::EX_NONE for success
	 * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
	 *
	 */
	SECURE_VIDEO = 8,

	/**
	 * Count of decoded frames.
	 * This metric is reset on open() and flush() calls.
	 *
	 * Type: Integer
	 *  -1 means this metric is not yet implemented by the vendor.
	 * Access: Read-only.
	 *
	 * @exception binder::Status::Exception::EX_NONE for success
	 * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
	 *
	 */
	METRIC_FRAMES_DECODED = 1000,

	/**
	 * Count of decode errors.
	 * This metric is reset on open() and flush() calls.
	 *
	 * Type: Integer
	 *  -1 means this metric is not yet implemented by the vendor.
	 * Access: Read-only.
	 *
	 * @exception binder::Status::Exception::EX_NONE for success
	 * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
	 *
	 */
	METRIC_DECODE_ERRORS = 1001,

	/**
	 * Count of frames dropped.
	 * No frame was output due to corruption or decode error that could not 
	 * deliver a frame suitable for display.
	 * This count includes any frames received before the first reference frame.
	 * This metric is reset on open() and flush() calls.
	 *
	 * Type: Integer
	 *  -1 means this metric is not yet implemented by the vendor.
	 * Access: Read-only.
	 *
	 * @exception binder::Status::Exception::EX_NONE for success
	 * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
	 *
	 */
	METRIC_FRAMES_DROPPED = 1002,


        /**
         * Stream resolution width in pixels.
         * Represents the coded/decoded video frame width.
         * Can be set while the video decoder resource is in READY.
         *
         * Type: Integer
         * Units: pixels
         * Access: Read-write.
         * Write in states: READY Only
         *
         * @exception binder::Status::Exception::EX_NONE for success
         * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
         */
        STREAM_RESOLUTION_WIDTH = 1003,

        /**
         * Stream resolution height in pixels.
         * Represents the coded/decoded video frame height.
         * Can be set while the video decoder resource is in READY.
         *
         * Type: Integer
         * Units: pixels
         * Access: Read-write.
         * Write in states: READY only
         *
         * @exception binder::Status::Exception::EX_NONE for success
         * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
         */
        STREAM_RESOLUTION_HEIGHT = 1004,

        /**
         * Mastering display information (SMPTE ST 2086) as a textual payload.
         * Typically encodes primaries, white point, and luminance (min/max).
         * Can be set while the video decoder resource is in READY.
         *
         * Type: String
         * Format: Implementation-defined (e.g., JSON or "G(x,y),B(x,y),R(x,y),WP(x,y),L(min,max)")
         * Access: Read-write.
         * Write in states: READY only
         *
         * @exception binder::Status::Exception::EX_NONE for success
         * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
         */
        MASTERING_DISPLAY_INFO = 1005,

        /**
         * Content light level information (SMPTE ST 2094/MaxCLL/MaxFALL) as a textual payload.
         * Used to convey per-title light level metadata.
         * Can be set while the video decoder resource is in READY.
         *
         * Type: String
         * Format: Implementation-defined (e.g., "MaxCLL=<nits>;MaxFALL=<nits>")
         * Access: Read-write.
         * Write in states: READY only
         *
         * @exception binder::Status::Exception::EX_NONE for success
         * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
         */
        CONTENT_LIGHT_LEVEL = 1006,

        /**
         * Mastering display metadata as a textual payload.
         * This may include a superset or alternate representation of mastering info.
         * Can be set while the video decoder resource is in READY.
         *
         * Type: String
         * Format: Implementation-defined (may be vendor/HDR10/HDR10+ specific)
         * Access: Read-write.
         * Write in states: READY only
         *
         * @exception binder::Status::Exception::EX_NONE for success
         * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
         */
        MASTERING_DISPLAY_METADATA = 1007,

       /**
        * Colorimetry specification for the stream.
        * Common values include "BT.709", "BT.2020", "BT.601", etc.
        * Can be set while the video decoder resource is in READY.
        *
        * Type: String
        * Allowed values: Implementation-defined (e.g., "BT.709", "BT.2020", "BT.601", "DCI-P3")
        * Access: Read-write.
        * Write in states: READY only
        *
        * @exception binder::Status::Exception::EX_NONE for success
        * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
        */
       COLORIMETRY = 1008,

       /**
        * Dolby Vision Base Layer (BL) present flag.
        * Indicates whether a Dolby Vision Base Layer is present in the bitstream.
        * Can be set while the video decoder resource is in READY.
        *
        * Type: Boolean
        *  false - BL not present
        *  true  - BL present
        * Access: Read-write.
        * Write in states: READY only
        *
        * @exception binder::Status::Exception::EX_NONE for success
        * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
        */
       DV_BL_PRESENT_FLAG = 1009,

       /**
        * Dolby Vision Enhancement Layer (EL) present flag.
        * Indicates whether a Dolby Vision Enhancement Layer is present in the bitstream.
        * Can be set while the video decoder resource is in READY.
        *
        * Type: Boolean
        *  false - EL not present
        *  true  - EL present
        * Access: Read-write.
        * Write in states: READY only
        *
        * @exception binder::Status::Exception::EX_NONE for success
        * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
        */
       DV_EL_PRESENT_FLAG = 1010,

       /**
        * Stream frame rate numerator.
        * Together with FrameRateDenominator defines the rational frame rate (N/D).
        * Can be set while the video decoder resource is in READY.
        *
        * Type: Integer
        * Range: >= 0
        * Access: Read-write.
        * Write in states: READY only
        *
        * @exception binder::Status::Exception::EX_NONE for success
        * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
        */
       FRAME_RATE_NUMERATOR = 1011,

       /**
        * Stream frame rate denominator.
        * Together with FrameRateNumerator defines the rational frame rate (N/D).
        * Can be set while the video decoder resource is in READY.
        *
        * Type: Integer
        * Range: > 0 (must be non-zero)
        * Access: Read-write.
        * Write in states: READY only
        *
        * @exception binder::Status::Exception::EX_NONE for success
        * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
        */
       FRAME_RATE_DENOMINATOR = 1012,

}

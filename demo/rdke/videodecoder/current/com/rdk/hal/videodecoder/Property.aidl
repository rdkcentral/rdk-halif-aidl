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
	 */
	RESOURCE_ID = 0,

	/**
	 * Video decode buffer input queue size in bytes.
	 * The default is set by the vendor to best suit the platform.
	 *
	 * Type: Integer
	 * Access: Read-only.
	 */
	INPUT_QUEUE_DEPTH = 1,

	/**
	 * Number of frame buffers in the vendor frame buffer pool.
	 * The default is vendor defined.
	 *
	 * Type: Integer
	 * Access: Read-only.
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
	 */
	SECURE_VIDEO = 8,

	/**
	 * Count of decoded frames.
	 * This metric is reset on open() and flush() calls.
	 *
	 * Type: Integer
	 *  -1 means this metric is not yet implemented by the vendor.
	 * Access: Read-only.
	 */
	METRIC_FRAMES_DECODED = 1000,

	/**
	 * Count of decode errors.
	 * This metric is reset on open() and flush() calls.
	 *
	 * Type: Integer
	 *  -1 means this metric is not yet implemented by the vendor.
	 * Access: Read-only.
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
	 */
	METRIC_FRAMES_DROPPED = 1002,
}

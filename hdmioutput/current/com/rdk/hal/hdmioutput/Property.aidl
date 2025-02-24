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
package com.rdk.hal.hdmioutput;
 
/** 
 *  @brief     HDMI output properties used in property get/set functions.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 */
 
@VintfStability
@Backing(type="int")
enum Property
{
	/**
	 * Unique ID per decoder resource instance.
	 *
	 * Type: Integer
	 * Access: Read-only.
	 */
	RESOURCE_ID = 0,

	/**
	 * Video Identification Code (VIC).
	 * AVI InfoFrame VIC0..7
	 * The HDMI output signal is driven the specified VIC resolution, frame rate, etc.
	 * The AVMUTE should be controlled according to HDMI spec on VIC changes.
	 *
	 * Type: Integer - enum VIC
	 * Default: VIC.VIC0_UNAVAILABLE
	 * Access: Read-write.
	 */
	VIC = 1,

	/**
	 * Content type as defined by CTA-861.
	 * AVI InfoFrame ITC and CN0..1
	 *
	 * Type: Integer - enum ContentType value.
	 * Default: ContentType.UNSPECIFIED on open()
	 * Access: Read-write.
	 */
	CONTENT_TYPE = 2,

	/**
	 * Active format description / active portion aspect ratio.
	 * AVI InfoFrame A0 and R0..3
	 *
	 * Type: Integer - enum AFD value.
	 * Default: AFD.UNSPECIFIED on open()
	 * Access: Read-write.
	 */
	AFD = 3,

	/**
	 * HDR output mode.
	 * Allows the HDR output format signalling to be fixed and the video content to be converted to the output format.
	 *
	 * Type: Integer - enum HDROutputMode value.
	 * Default: HDROutputMode.AUTO on open()
	 * Access: Read-write.
	 */
	HDR_OUTPUT_MODE = 4,

	/**
	 * Scan information.
     * AVI InfoFrame S0..1
	 *
	 * Type: Integer - enum ScanInformation value.
	 * Default: ScanInformation.NO_DATA on open()
	 * Access: Read-write.
	 */
	SCAN_INFORMATION = 5,

	/**
	 * foo bar count.
	 * This metric is reset on open() and flush() calls.
	 *
	 * Type: Integer
	 *  -1 means this metric is not yet implemented by the vendor.
	 * Access: Read-only.
	 */
	METRIC_xxx = 1000,
}

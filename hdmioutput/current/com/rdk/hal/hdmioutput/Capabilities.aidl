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
import com.rdk.hal.hdmioutput.HDMIVersion;
import com.rdk.hal.hdmioutput.VIC;
 
/** 
 *  @brief     HDMI output port device capabilities definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
parcelable Capabilities
{
	/**
	 * The array of HDMI versions the port supports.
	 */
	HDMIVersion[] supportedVersions;

	/**
	 * The array of VIC the port supports.
	 */
	VIC[] supportedVICs;

	/**
	 * The array of HDR modes the HDMI output port supports.
	 */
	HDROutputMode[] supportedHDROutputModes;

	/**
	 * Whether the SoC supports forced HDR modes out of the HDMI port.
	 * When forced on, the current dynamic range is locked as the output
	 * format and is not dependant on the primary video format.
	 */
	boolean supportsForcedHDROutputModes;

	/**
	 * The array of HDCP protocol versions the HDMI output port supports.
	 */
	HDCPProtocolVersion[] supportedHDCPProtocolVersions;

	/**
	 * The array of colorimetries the HDMI output port supports.
	 */
	Colorimetry[] supportedColorimetries;

	/**
	 * The array of extended colorimetries the HDMI output port supports.
	 */
	ExtendedColorimetry[] supportedExtendedColorimetries;

	/**
	 * The array of additional colorimetries extensions the HDMI output port supports.
	 */
	AdditionalColorimetryExtension[] supportedAdditionalColorimetryExtensions;

	/**
	 * The array of color bit depths the HDMI output port supports.
	 * e.g. [ 8, 10, 12, 16 ]
	 */
	int[] supportedColorDepths;

	/**
	 * The array of pixel formats the HDMI output port supports.
	 */
	PixelFormat[] supportedPixelFormats;

	/**
	 * Indicates support for stereo (3D) video.
	 */
	boolean supports3D;

	/**
	 * Indicates support for fixed rate link (FRL).
	 */
	boolean supportsFRL;

	/**
	 * Indicates support for variable refresh rate (VRR).
	 */
	boolean supportsVRR;

	/**
	 * Indicates support for AMD FreeSync.
	 * @see PlatformCapabilities.freeSync to determine the type of FreeSync.
	 */
	boolean supportsFreeSync;

	/**
	 * Indicates support quick media switching (QMS is VRR with M_CONST).
	 */
	boolean supportsQMS;

	/**
	 * Indicates support for automatic low latency mode (ALLM).
	 */
	boolean supportsALLM;

	/**
	 * Indicates support for quick frame transport (QFT is Fast VActive).
	 */
	boolean supportsQFT;
}

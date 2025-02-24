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
	 * Whether the port supports RX sense to detect whether a HDMI sink is connected.
	 * Can be used as an alternative to hot plug detect (HPD) if unreliable.
	 */
	boolean supportsRXSense;

    boolean supports3D;     // 3D video formats
    boolean supportsFRL;    // Fixed rate link
	boolean supportsVRR;	// Variable refresh rate
	boolean supportsQMS;    // Quick media switching (VRR with M_CONST)
	boolean supportsFVA;	// Fast Vactive (Quick frame transport)
    boolean supportsALLM;   // Auto low latency mode
}

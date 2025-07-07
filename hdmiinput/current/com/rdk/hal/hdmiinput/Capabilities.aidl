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
package com.rdk.hal.hdmiinput;
import com.rdk.hal.hdmiinput.HDMIVersion;
import com.rdk.hal.hdmiinput.VIC;
import com.rdk.hal.hdmiinput.HDCPProtocolVersion;
 
/** 
 *  @brief     HDMI input port device capabilities definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
parcelable Capabilities
{
	/**
	 * The array of HDMI versions the port supports.
	 * Specifying more than one HDMI version indicates support for switching between versions.
	 * @Note: supportsQMS requires supportsVRR to be true. supportsFreeSync is only meaningful if supportsVRR is true.
	 */
	HDMIVersion[] supportedVersions;

	/**
	 * The array of VIC the port supports.
	 */
	VIC[] supportedVICs;

	/**
	 * The array of HDCP protocol versions the HDMI input port supports.
	 */
	HDCPProtocolVersion[] supportedHDCPProtocolVersions;

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
	 * Indicates support for quick frame transport (QFT is aka Fast VActive).
	 */
	boolean supportsQFT;

	/**
	 * Indicates support for audio return channel (ARC).
	 */
	boolean supportsARC;

	/**
	 * Indicates support for enhanced audio return channel (eARC).
	 */
	boolean supportsEARC;
}

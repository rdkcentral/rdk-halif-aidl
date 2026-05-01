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
import com.rdk.hal.hdmioutput.PixelFormat;
import com.rdk.hal.hdmioutput.HDROutputMode;
import com.rdk.hal.hdmioutput.HDCPProtocolVersion;
import com.rdk.hal.hdmioutput.Colorimetry;
import com.rdk.hal.hdmioutput.ExtendedColorimetry;
import com.rdk.hal.hdmioutput.AdditionalColorimetryExtension;

/** 
 *  @brief     HDMI output port device capabilities definition.
 *
 *  This parcelable encapsulates all HDMI output-related feature support
 *  exposed by a specific output port. It provides a comprehensive overview
 *  of supported resolutions, formats, protocols, and HDMI-specific extensions.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */
@VintfStability
parcelable Capabilities 
{
    /**
     * The array of HDMI versions the port supports.
     */
    HDMIVersion[] supportedVersions;

    /**
     * The array of VICs (Video Identification Codes) the port supports.
     */
    VIC[] supportedVICs;

    /**
     * The array of HDR modes the HDMI output port supports.
     */
    HDROutputMode[] supportedHDROutputModes;

    /**
     * Whether the SoC supports forced HDR modes on the HDMI output.
     *
     * When forced, the current HDR dynamic range is locked as the output
     * format and does not change based on the primary video content.
     */
    boolean supportsForcedHDROutputModes;

    /**
     * The array of HDCP protocol versions the HDMI output port supports.
     */
    HDCPProtocolVersion[] supportedHDCPProtocolVersions;

    /**
     * The array of base colorimetries the HDMI output port supports.
     */
    Colorimetry[] supportedColorimetries;

    /**
     * The array of extended colorimetries the HDMI output port supports.
     */
    ExtendedColorimetry[] supportedExtendedColorimetries;

    /**
     * The array of additional colorimetry extensions the HDMI output port supports.
     */
    AdditionalColorimetryExtension[] supportedAdditionalColorimetryExtensions;

    /**
     * The array of color bit depths the HDMI output port supports.
     * Example values: [8, 10, 12, 16]
     */
    int[] supportedColorDepths;

    /**
     * The array of pixel formats the HDMI output port supports.
     */
    PixelFormat[] supportedPixelFormats;

    /**
     * Indicates whether the HDMI output port supports stereo (3D) video.
     */
    boolean supports3D;

    /**
     * Indicates support for Fixed Rate Link (FRL).
     */
    boolean supportsFRL;

    /**
     * Indicates support for Variable Refresh Rate (VRR).
     */
    boolean supportsVRR;

    /**
     * Indicates support for AMD FreeSync.
     *
     * @see PlatformCapabilities.freeSync for FreeSync capability level.
     */
    boolean supportsFreeSync;

    /**
     * Indicates support for Quick Media Switching (QMS).
     * QMS is implemented using VRR with M_CONST.
     */
    boolean supportsQMS;

    /**
     * Indicates support for Auto Low Latency Mode (ALLM).
     */
    boolean supportsALLM;

    /**
     * Indicates support for Quick Frame Transport (QFT).
     * QFT is based on Fast VActive signaling.
     */
    boolean supportsQFT;
}

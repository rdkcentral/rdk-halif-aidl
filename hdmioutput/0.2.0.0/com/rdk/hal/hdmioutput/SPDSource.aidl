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
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.hdmioutput;

/**
 *  @brief     HDMI SPD InfoFrame source type enumeration (Data Byte 25).
 *
 *  Enumerates the source device class reported in the HDMI SPD InfoFrame,
 *  as defined in CTA-861. This field helps receivers interpret and adapt
 *  rendering modes (e.g., game mode, cinema presets).
 *
 *  This value is set in SPDInfoFrame.spdSourceInformation.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type = "byte")
enum SPDSource
{
    /** Unknown or undefined source */
    UNKNOWN = 0x00,

    /** Digital Set-Top Box */
    DIGITAL_STB = 0x01,

    /** DVD player */
    DVD_PLAYER = 0x02,

    /** D-VHS device */
    D_VHS = 0x03,

    /** HDD-based video recorder */
    HDD_VIDEORECORDER = 0x04,

    /** Digital Video Camera (DVC) */
    DVC = 0x05,

    /** Digital Still Camera (DSC) */
    DSC = 0x06,

    /** Video CD player */
    VIDEO_CD = 0x07,

    /** Game console */
    GAME = 0x08,

    /** Personal computer (general use) */
    PC_GENERAL = 0x09,

    /** Blu-ray Disc player */
    BLU_RAY_DISC = 0x0A,

    /** Super Audio CD (SACD) player */
    SUPER_AUDIO_CD = 0x0B,

    /** HD-DVD player */
    HD_DVD = 0x0C
}

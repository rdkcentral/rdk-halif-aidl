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
 *  @brief     HDMI SPD InfoFrame source information enum for data byte 25.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 */
 
@VintfStability
@Backing(type = "byte")
enum SPDSource
{
    /**
     * Unknown
     */
    UNKNOWN = 0x00,

    /**
     * Digital STB
     */
    DIGITAL_STB = 0x01, 

    /**
     * DVD player
     */
    DVD_PLAYER = 0x02, 

    /**
     * D-VHS
     */
    D_VHS = 0x03, 

    /**
     * HDD Videorecorder
     */
    HDD_VIDEORECORDER = 0x04, 

    /**
     * DVC
     */
    DVC = 0x05, 

    /**
     * DSC
     */
    DSC = 0x06, 

    /**
     * Video CD
     */
    VIDEO_CD = 0x07, 

    /**
     * Game
     */
    GAME = 0x08, 

    /**
     * PC general
     */
    PC_GENERAL = 0x09, 

    /**
     * Blu-Ray Disc (BD)
     */
    BLU_RAY_DISC = 0x0A, 

    /**
     * Super Audio CD
     */
    SUPER_AUDIO_CD = 0x0B, 

    /**
     * HD DVD
     */
    HD_DVD = 0x0C,
}

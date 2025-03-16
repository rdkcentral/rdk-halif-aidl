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
 *  @brief     Video decoder dynamic range definitions.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */
 
/**
 * Enum representing different dynamic range formats supported by video decoders.
 *
 * Dynamic range determines the range of luminance levels in a video.
 * Higher dynamic ranges allow for better contrast, brightness, and color accuracy.
 *
 * @enum DynamicRange
 */
@VintfStability
@Backing(type="int")
enum DynamicRange {    
    /**
     * Dynamic range is unknown or not reported.
     */
    UNKNOWN = 0,

    /**
     * Standard Dynamic Range (SDR).
     * The most common format, typically using BT.709 color space with an 8-bit depth.
     */
    SDR = 1,

    /**
     * Hybrid Log-Gamma (HLG).
     * Designed for backward compatibility with SDR, used in live broadcasting.
     * @see ITU-R BT.2100
     */
    HLG = 2,

    /**
     * HDR10 (High Dynamic Range 10).
     * Uses static metadata for HDR and is widely used in streaming and UHD Blu-ray.
     * @see SMPTE ST 2084 (PQ Curve)
     */
    HDR10 = 3,

    /**
     * HDR10+ (High Dynamic Range 10 Plus).
     * An improved version of HDR10 that uses dynamic metadata for better tone mapping.
     * @see SMPTE ST 2094-40
     */
    HDR10PLUS = 4,

    /**
     * Dolby Vision (DV).
     * A premium HDR format supporting dynamic metadata and up to 12-bit color depth.
     * @see Dolby Laboratories Specification
     */
    DOLBY_VISION = 5
};

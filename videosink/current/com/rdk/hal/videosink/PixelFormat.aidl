/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
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
package com.rdk.hal.videosink;

/**
 *  @brief     Video Sink pixel format enumeration.
 *  @author    Gerald Weatherup
 *
 *  Identifies the concrete buffer pixel layouts that a Video Sink instance
 *  is able to consume. Mirrors the `supportedPixelFormats` field declared in
 *  the HFP (`hfp-videosink.yaml`).
 */
@VintfStability
@Backing(type="int")
enum PixelFormat
{
    /** Unknown / unspecified pixel format. */
    UNKNOWN = 0,

    /**
     * NV12 — 8-bit YUV 4:2:0, two planes (Y plane, interleaved UV plane).
     */
    NV12 = 1,

    /**
     * I420 — 8-bit YUV 4:2:0, three planes (Y, U, V).
     * Also known as YU12 / planar YUV 4:2:0.
     */
    I420 = 2,

    /**
     * P010 — 10-bit YUV 4:2:0, two planes (Y plane, interleaved UV plane),
     * with each component stored in the most significant 10 bits of a 16-bit word.
     */
    P010 = 3,
}

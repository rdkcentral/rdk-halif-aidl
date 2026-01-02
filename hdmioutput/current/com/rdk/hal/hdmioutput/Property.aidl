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
 *  @brief     HDMI output properties used in get/set functions.
 *
 *  These enumerated keys are used in property-based APIs such as `getProperty()`,
 *  `setProperty()`, and their multi-property equivalents.
 *
 *  Each key maps to a defined type and access model, and represents a field within
 *  the HDMI AVI InfoFrame or device-specific runtime metadata.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type = "int")
enum Property
{
    /**
     * Unique ID for the decoder resource instance.
     *
     * Type: Integer  
     * Access: Read-only.
     */
    RESOURCE_ID = 0,

    /**
     * Video Identification Code (VIC).
     * Controls resolution, refresh rate, and format for the HDMI output.
     * Maps to AVI InfoFrame VIC[0..7].
     *
     * AVMUTE must be asserted/deasserted per HDMI spec when changing this value.
     *
     * Type: Integer — enum VIC  
     * Default: VIC.VIC0_UNAVAILABLE  
     * Access: Read-write.
     */
    VIC = 1,

    /**
     * Content type as defined by CTA-861.
     * Maps to AVI InfoFrame ITC and CN[0..1].
     *
     * Type: Integer — enum ContentType  
     * Default: ContentType.UNSPECIFIED on open()  
     * Access: Read-write.
     */
    CONTENT_TYPE = 2,

    /**
     * Active Format Description — used to signal aspect ratio of active area.
     * Maps to AVI InfoFrame A0 and R[0..3].
     *
     * Type: Integer — enum AFD  
     * Default: AFD.UNSPECIFIED on open()  
     * Access: Read-write.
     */
    AFD = 3,

    /**
     * HDR output signalling mode.
     *
     * Allows selection of a fixed output HDR mode, where incoming video will be tone-mapped
     * or converted to the configured dynamic range as needed.
     *
     * Type: Integer — enum HDROutputMode  
     * Default: HDROutputMode.AUTO on open()  
     * Access: Read-write.
     */
    HDR_OUTPUT_MODE = 4,

    /**
     * Scan information metadata from the AVI InfoFrame.
     * Indicates whether the source signal is interlaced or progressive.
     * Maps to AVI InfoFrame S[0..1].
     *
     * Type: Integer — enum ScanInformation  
     * Default: ScanInformation.NO_DATA on open()  
     * Access: Read-write.
     */
    SCAN_INFORMATION = 5,

    /**
     * Placeholder vendor-specific metric.
     *
     * Tracks a debug or QoS-related count value, reset on `open()` and `flush()`.
     * A value of `-1` indicates the metric is not implemented by the vendor.
     *
     * Type: Integer  
     * Access: Read-only.
     */
    METRIC_xxx = 1000
}

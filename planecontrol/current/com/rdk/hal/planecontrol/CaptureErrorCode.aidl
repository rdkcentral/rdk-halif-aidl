/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
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
package com.rdk.hal.planecontrol;

/**
 *  @brief     Capture error code definitions.
 *  @author    Gerald Weatherup
 */

@VintfStability
@Backing(type="int")
enum CaptureErrorCode {

    /** The platform refused the buffer pool reservation from the video memory region. */
    OUT_OF_MEMORY = 1,

    /**
     * The bound video decoder has no `videodecoder.CaptureConfig` applied, so its output
     * is not routed to capture.
     */
    DECODER_NOT_CONFIGURED = 2,

    /** The bound video decoder is already bound to another capture session. */
    DECODER_BUSY = 4,

    /** An unrecoverable hardware fault occurred, such as an IOMMU fault. */
    HARDWARE_FAULT = 5,
}

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
package com.rdk.hal.capture;

/**
 *  @brief     Capture error code definitions.
 *  @author    Peter Stieglitz
 *  @author    Gerald Weatherup
 */

@VintfStability
@Backing(type="int")
enum CaptureErrorCode {

    /** The platform refused the buffer pool reservation from the video memory region. */
    OUT_OF_MEMORY = 1,

    /**
     * The requested source is not one this resource supports, or cannot carry a
     * further capture.
     *
     * @see ICapture.open(), CaptureCapabilities.supportedSources
     */
    SOURCE_UNAVAILABLE = 2,

    /**
     * The bound source is decoding a codec this capture cannot take.
     *
     * @see CaptureCapabilities.supportedCodecs
     */
    CODEC_NOT_CAPTURABLE = 3,

    /** An unrecoverable hardware fault occurred, such as an IOMMU fault. */
    HARDWARE_FAULT = 4,

    /**
     * The configured capture resolution does not match the resolution the bound
     * source is decoding, on a capture that cannot resize.
     *
     * @see CaptureCapabilities.resize, Property.WIDTH, Property.HEIGHT
     */
    RESOLUTION_MISMATCH = 5,

    /**
     * The colour conversion the configured format would require of the bound source
     * is not one this capture can perform.
     */
    COLOR_CONVERSION_UNSUPPORTED = 6,

    /**
     * The configured pixel format or memory layout cannot be delivered for the bound
     * source, even though the capture declares it.
     *
     * @see CaptureCapabilities.supportedFormats, ICaptureController.setFormat()
     */
    FORMAT_UNSUPPORTED = 7,

    /**
     * The session's configuration is not a combination this capture can deliver, or is
     * incomplete - `start()` raises this where no format was selected with
     * `ICaptureController.setFormat()`.
     */
    INVALID_CONFIGURATION = 8,
}

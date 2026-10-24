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
package com.rdk.hal.videocapture;

/**
 *  @brief     Video capture error code definitions.
 *  @author    Peter Stieglitz
 *  @author    Gerald Weatherup
 */

@VintfStability
@Backing(type="int")
enum ErrorCode {

    /** The platform refused the buffer pool reservation from the video memory region. */
    OUT_OF_MEMORY = 1,

    /**
     * The named source cannot take this capture.
     *
     * The source is one this capture serves, and it is already carrying a capture
     * session - a source carries at most one - or it became unavailable between the
     * bind and `IVideoCaptureController.start()`.
     *
     * @see IVideoCapture.open(), IVideoCaptureController.start()
     */
    SOURCE_UNAVAILABLE = 2,

    /**
     * The bound source is decoding a codec this capture cannot take.
     *
     * @see Capabilities.supportedCodecs
     */
    CODEC_NOT_CAPTURABLE = 3,

    /** An unrecoverable hardware fault occurred, such as an IOMMU fault. */
    HARDWARE_FAULT = 4,

    /**
     * The bound source is decoding, or has changed to, a resolution beyond
     * `Capabilities.maxFrameWidth` or `maxFrameHeight`.
     *
     * The pool is sized for that maximum, so a larger frame cannot be captured. Raised
     * by `IVideoCaptureController.start()`, or mid-session through
     * `IVideoCaptureControllerListener.onCaptureError()`, after which the session is
     * stopped. Playback of the source continues.
     *
     * @see Capabilities.maxFrameWidth, Capabilities.maxFrameHeight
     */
    RESOLUTION_MISMATCH = 5,

    /**
     * The colour conversion the declared format would require of the bound source
     * is not one this capture can perform.
     */
    COLOR_CONVERSION_UNSUPPORTED = 6,

    /**
     * The declared pixel format or memory layout cannot be delivered for the bound
     * source.
     *
     * @see Capabilities.format
     */
    FORMAT_UNSUPPORTED = 7,

    /**
     * The named source is not one this capture can take frames from.
     *
     * Distinct from `SOURCE_UNAVAILABLE`: the source is not in
     * `Capabilities.supportedSources` at all, so no capacity would make the bind
     * succeed. A client that enumerated `supportedSources` does not see this.
     *
     * @see IVideoCapture.open(), Capabilities.supportedSources, Source
     */
    SOURCE_NOT_CAPTURABLE = 9,

    /**
     * The bound source is carrying protected content.
     *
     * Capture is of clear content only. Raised by `IVideoCapture.open()` or
     * `IVideoCaptureController.start()` when the source is operating in its secure
     * video path, or mid-session through `IVideoCaptureControllerListener.onCaptureError()`
     * when it enters it, after which the session is stopped. Playback of the source
     * continues.
     *
     * @see IVideoCapture.open()
     */
    PROTECTED_CONTENT = 10,
}

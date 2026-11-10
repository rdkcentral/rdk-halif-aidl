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
package com.rdk.hal.audiodecoder;
import com.rdk.hal.audiodecoder.ErrorCode;

/**
 * @brief One decode error. Each occurrence adds one to Metric::DECODE_ERRORS.
 */
@VintfStability
parcelable DecodeErrorEvent {
    /**
     * CLOCK_MONOTONIC_RAW time, in nanoseconds, at which the service detected
     * the event.
     */
    long timestampNs;

    /**
     * Presentation time, in nanoseconds, of the frame being decoded, or -1
     * where the error is not tied to a frame.
     */
    long presentationTimeNs;

    /**
     * The error raised.
     */
    ErrorCode errorCode;

    /**
     * Vendor-specific code for diagnosis; 0 where the vendor has none.
     */
    int vendorErrorCode;
}

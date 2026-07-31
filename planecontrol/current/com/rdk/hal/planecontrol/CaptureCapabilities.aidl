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
 *  @brief     Capture capabilities definition for a plane resource.
 *
 *  Describes how the buffer pool behaves. The captured frames' pixel format and size
 *  are the decoder's output configuration, declared in
 *  `videodecoder.Capabilities.supportedCaptureFourCCs` and set through
 *  `videodecoder.CaptureConfig` - a capture plane consumes what the decoder produces
 *  rather than negotiating a second format.
 *  @author    Gerald Weatherup
 */

@VintfStability
parcelable CaptureCapabilities
{
    /**
     * The maximum number of buffers that can be reserved in the capture pool.
     *
     * A reservation that exceeds what the platform's video memory region can satisfy
     * fails at `ICaptureController.start()` with `CaptureErrorCode.OUT_OF_MEMORY`.
     *
     * @see CaptureProperty.BUFFER_COUNT, CaptureErrorCode.OUT_OF_MEMORY
     */
    int maxBufferCount;

    /**
     * Indicates the behaviour when every buffer in the pool is locked by the client and
     * the decoder has a new frame to write.
     *
     * When true, the decoder stalls until a buffer is released.
     * When false, the oldest Ready buffer is recycled and its frame is dropped.
     * Decode proceeds at full rate in both cases for as long as buffers are available.
     */
    boolean stallsWhenPoolExhausted;
}

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
 *  @brief     Capture properties used in the capture property get/set functions.
 *
 *  Named `CaptureProperty` because the module already defines a plane `Property` enum.
 *
 *  Only the pool's shape is set here. The captured frames' pixel format and size belong
 *  to the decoder's output configuration - see `videodecoder.CaptureConfig` - and the
 *  size of a buffer follows from them, so neither is a capture property.
 *
 *  @author    Gerald Weatherup
 */

@VintfStability
@Backing(type="int")
enum CaptureProperty {

    /**
     * The number of buffers in the capture pool.
     *
     * Must not exceed `CaptureCapabilities.maxBufferCount`. A pool the platform's video
     * memory region cannot satisfy fails at `ICaptureController.start()` with
     * `CaptureErrorCode.OUT_OF_MEMORY`.
     *
     * The size of each buffer is not set here: it follows from the pixel format and
     * frame size the decoder was configured with in `videodecoder.CaptureConfig`,
     * together with the vendor's own plane alignment. The resulting figure is reported
     * back to the client in `ICaptureControllerListener.onPoolReady()`.
     *
     * Type: Integer
     * Access: Read-write.
     * Write in states: READY
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if written in a state other than READY.
     */
    BUFFER_COUNT = 0,
}

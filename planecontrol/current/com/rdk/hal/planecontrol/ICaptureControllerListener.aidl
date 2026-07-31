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
 *  @brief     Callbacks listener interface from a capture session controller.
 *  @author    Gerald Weatherup
 */

@VintfStability
oneway interface ICaptureControllerListener
{
    /**
     * @brief     Called once per session after `ICaptureController.start()` has wired the
     *            video decoder into the pool, and before any `onFrameAvailable()`.
     *
     * Reports what the vendor actually allocated. The file descriptors that address each
     * frame arrive per frame in `VideoFrameView`, so a client needs nothing from here to
     * import a buffer - this is the pool's shape, not its addressing.
     *
     * @param[in] planeStrides      The number of bytes from the start of one row of pixels
     *                              to the start of the next, per plane. For NV12 this is
     *                              [Y stride, UV stride].
     * @param[in] bufferCount       The number of buffers reserved in the pool.
     * @param[in] bufferSizeBytes   The size in bytes of a single capture buffer.
     */
    void onPoolReady(in int[] planeStrides, in int bufferCount, in int bufferSizeBytes);

    /**
     * @brief     Called when a buffer has transitioned to Ready.
     *
     * Implementations may coalesce these callbacks. A client that pulls at a known cadence
     * can ignore this callback; `ICaptureController.acquireLatestFrame()` is complete
     * without it.
     */
    void onFrameAvailable();
}

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
     *            video decoder into the ring, and before any `onFrameAvailable()`.
     *
     * @param[in] ringFd            The shared ring Dma-Buf on platforms where
     *                              `CaptureCapabilities.sharedRingBuffer` is true.
     *                              Null where it is false, in which case each slot's
     *                              file descriptor arrives per frame in
     *                              `VideoFrameView.planeFds`.
     * @param[in] planeStrides      The number of bytes from the start of one row of pixels
     *                              to the start of the next, per plane. For NV12 this is
     *                              [Y stride, UV stride].
     * @param[in] slotCount         The number of slots reserved in the ring.
     * @param[in] slotSizeBytes     The size in bytes of a single ring slot.
     */
    void onRingReady(in @nullable ParcelFileDescriptor ringFd, in int[] planeStrides, in int slotCount, in int slotSizeBytes);

    /**
     * @brief     Called when a slot has transitioned to Ready.
     *
     * Implementations may coalesce these callbacks. A client that pulls at a known cadence
     * can ignore this callback; `ICaptureController.acquireLatestFrame()` is complete
     * without it.
     */
    void onFrameAvailable();
}

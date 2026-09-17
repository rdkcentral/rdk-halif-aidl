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

import com.rdk.hal.videocapture.ErrorCode;
import com.rdk.hal.videocapture.VideoBufferView;

/**
 *  @brief     Callbacks listener interface from a capture session controller.
 *  @author    Peter Stieglitz
 *  @author    Gerald Weatherup
 */

@VintfStability
oneway interface IVideoCaptureControllerListener
{
    /**
     * @brief     Called once per session after `IVideoCaptureController.start()` has wired the
     *            source into the pool, and before any `onFrameAvailable()`.
     *
     * Delivers the whole pool: one `VideoBufferView` per buffer, carrying the file
     * descriptors, offsets, strides, size and format that address it. None of that
     * changes while the session runs, so a client imports every buffer into an EGLImage
     * here and afterwards needs only the buffer index each frame arrives in.
     *
     * The array length is the number of buffers the platform reserved, calibrated for
     * the throughput it can sustain. The length of this array IS the pool depth - it
     * is not declared anywhere else, because there is nothing for a client to decide
     * before it and nothing to check it against.
     *
     * Raised once per `start()`. A later `start()` delivers a new pool whose buffer
     * indices name new memory, and a client discards whatever it imported from the
     * previous one before resolving any index against it.
     *
     * @param[in] buffers   One entry per pool buffer, indexed by `VideoBufferView.bufferIndex`.
     *
     *  Delivered on a binder thread. This interface is `oneway`, so the callback
     *  arrives on a thread of the client's binder pool - not the thread that owns
     *  its GL context, and an import needs that context current.
     *
     *  Every `planeFds` entry arrives as a descriptor already valid in the client's
     *  process: binder installs a new descriptor for each entry, referring to the
     *  same Dma-Buf. Entries that share a Dma-Buf on the implementation side
     *  therefore arrive with distinct numbers, and a descriptor number is not an
     *  identity - `bufferIndex` is.
     *
     *  Those descriptors belong to the parcel and are closed when this callback
     *  returns. A client that will use them afterwards duplicates each one before
     *  returning, preferably with `F_DUPFD_CLOEXEC`, and hands the duplicates to the
     *  thread that owns its GL context.
     *
     *  Each duplicate is a reference to the memory, and an image imported from it
     *  takes a further reference of its own. That is why a client may close a
     *  duplicate once it has imported from it, and why the memory outlives `stop()`.
     *  The client returns the memory by destroying its imported images, unmapping
     *  any CPU mappings and closing any descriptor it still holds.
     */
    void onPoolReady(in VideoBufferView[] buffers);

    /**
     * @brief     Called when a buffer has transitioned to Ready.
     *
     * Implementations may coalesce these callbacks. A client that pulls at a known cadence
     * can ignore this callback; `IVideoCaptureController.acquireLatestFrame()` is complete
     * without it.
     */
    void onFrameAvailable();

    /**
     * @brief     Called when the session cannot deliver frames as configured.
     *
     * Raised for failures the session runs into that are not tied to a single acquire
     * call - a bound source that changed to a resolution this capture cannot deliver, a
     * colour conversion or format that turns out to be unavailable for the bound
     * source, or a configuration the vendor cannot honour.
     *
     * The session stops delivering frames. The client stops and closes it, or corrects
     * the condition and starts again.
     *
     * @param[in] errorCode         A ErrorCode enum value.
     * @param[in] vendorErrorCode   A vendor specific error code.
     *
     * @see ErrorCode
     */
    void onCaptureError(in ErrorCode errorCode, in int vendorErrorCode);
}

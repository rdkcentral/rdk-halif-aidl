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

import com.rdk.hal.planecontrol.CaptureErrorCode;
import com.rdk.hal.planecontrol.VideoBufferView;

/**
 *  @brief     Callbacks listener interface from a capture session controller.
 *  @author    Gerald Weatherup
 */

@VintfStability
oneway interface ICaptureControllerListener
{
    /**
     * @brief     Called once per session after `ICaptureController.start()` has wired the
     *            source into the pool, and before any `onFrameAvailable()`.
     *
     * Delivers the whole pool: one `VideoBufferView` per buffer, carrying the file
     * descriptors, offsets, strides, size and format that address it. None of that
     * changes while the session runs, so a client imports every buffer into an EGLImage
     * here and afterwards needs only the buffer index each frame arrives in.
     *
     * The array length is the number of buffers the vendor reserved, which is what
     * `CaptureProperty.BUFFER_COUNT` asked for, or the vendor's own choice where the
     * session left it unset.
     *
     * @param[in] buffers   One entry per pool buffer, indexed by `VideoBufferView.bufferIndex`.
     */
    void onPoolReady(in VideoBufferView[] buffers);

    /**
     * @brief     Called when a buffer has transitioned to Ready.
     *
     * Implementations may coalesce these callbacks. A client that pulls at a known cadence
     * can ignore this callback; `ICaptureController.acquireLatestFrame()` is complete
     * without it.
     */
    void onFrameAvailable();

    /**
     * @brief     Called when the session cannot deliver frames as configured.
     *
     * Raised for failures the session runs into that are not tied to a single acquire
     * call - a mapped source that changed to a resolution this plane cannot deliver, a
     * colour conversion or format that turns out to be unavailable for the mapped
     * source, or a configuration the vendor cannot honour.
     *
     * The session stops delivering frames. The client stops and closes it, or corrects
     * the condition and starts again.
     *
     * @param[in] errorCode         A CaptureErrorCode enum value.
     * @param[in] vendorErrorCode   A vendor specific error code.
     *
     * @see CaptureErrorCode
     */
    void onCaptureError(in CaptureErrorCode errorCode, in int vendorErrorCode);
}

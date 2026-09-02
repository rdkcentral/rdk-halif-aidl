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
 *  @brief     A single captured decoded video frame.
 *
 *  Returned by `IVideoCaptureController.acquireLatestFrame()`, once per frame.
 *
 *  This carries only what differs from one frame to the next. Where the frame lives and
 *  how it is shaped were delivered once at `IVideoCaptureControllerListener.onPoolReady()`,
 *  as one `VideoBufferView` per pool buffer, so a client resolves a frame by looking up
 *  `bufferIndex` in what it already holds.
 *
 *  @see VideoBufferView, IVideoCaptureController.acquireLatestFrame()
 *
 *  @author    Peter Stieglitz
 *  @author    Gerald Weatherup
 */

@VintfStability
parcelable VideoFrameView
{
    /**
     * Passed as `IVideoCaptureController.acquireLatestFrame()`'s `releaseBufferIndex` when
     * the client holds no buffer to release.
     */
    const int NO_BUFFER = -1;

    /**
     * The pool buffer holding this frame.
     *
     * Indexes the `VideoBufferView` array delivered at `onPoolReady()`, which is where
     * the frame's file descriptors, offsets, strides, size and format are. This is also
     * the value passed to `IVideoCaptureController.releaseFrame()`, or to the next
     * `acquireLatestFrame()` to release and acquire in one call.
     */
    int bufferIndex;

    /**
     * The presentation time of this frame in nanoseconds, carried through from the
     * decoded elementary stream unaltered.
     *
     * The frame returned is the one due for presentation now, with audio latency and
     * AV-sync correction already applied, so a client that draws on receipt is in sync
     * without computing anything from this value. It is carried because a client
     * rendering to its own scene may need to place the frame on its own timeline.
     */
    long presentationTimeNs;
}

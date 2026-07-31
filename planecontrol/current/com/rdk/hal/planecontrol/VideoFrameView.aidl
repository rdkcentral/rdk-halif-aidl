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
 *  @brief     Addressing information for a single captured decoded video frame.
 *
 *  The per-plane arrays are ordered by plane index and are the direct inputs to
 *  `EGL_EXT_image_dma_buf_import`: element N feeds `EGL_DMA_BUF_PLANE<N>_FD_EXT`,
 *  `EGL_DMA_BUF_PLANE<N>_OFFSET_EXT` and `EGL_DMA_BUF_PLANE<N>_PITCH_EXT`.
 *  For NV12 there are two planes, [Y, UV].
 *
 *  The offsets address the actual buffer layout and are not to be inferred from
 *  the pixel format.
 *
 *  @author    Gerald Weatherup
 */

@VintfStability
parcelable VideoFrameView
{
    /**
     * The pool buffer this frame occupies, in the range [0, BUFFER_COUNT).
     * This value is passed to `ICaptureController.releaseFrame()`.
     *
     * The index is carried explicitly because where the pool is not a single shared
     * allocation every buffer has an offset of 0, so the offsets cannot identify it.
     */
    int bufferIndex;

    /**
     * One Dma-Buf file descriptor per plane.
     *
     * Each frame carries the file descriptors and offsets that address it, so a client
     * imports from `planeFds` and `planeOffsets` alone and needs to know nothing about
     * how the vendor allocated the pool - one Dma-Buf carved into offset-addressed
     * buffers and one Dma-Buf per buffer are both served by this.
     *
     * A file descriptor may repeat across frames. A client caching EGLImages keys the
     * cache on the descriptor, and at most `CaptureProperty.BUFFER_COUNT` distinct
     * descriptors are ever seen in a session.
     */
    ParcelFileDescriptor[] planeFds;

    /**
     * The byte offset of each plane from the start of its file descriptor.
     * An offset of 0 is valid.
     */
    int[] planeOffsets;

    /**
     * The number of bytes from the start of one row of pixels to the start of the
     * next row, for each plane.
     */
    int[] planeStrides;

    /**
     * The length in bytes of each plane.
     */
    int[] planeLengths;

    /**
     * The width of the frame in pixels.
     */
    int width;

    /**
     * The height of the frame in pixels.
     */
    int height;

    /**
     * The DRM FOURCC pixel format of the frame.
     * @see CaptureProperty.DRM_FOURCC
     */
    int drmFourcc;

    /**
     * The presentation time of the frame in nanoseconds, carried through from the
     * decoded elementary stream.
     */
    long presentationTimeNs;
}

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
     * An index rather than an address, because the two vendor allocation models
     * put the buffer's identity in different places. Where the pool is one shared
     * Dma-Buf, buffers differ by offset and share a file descriptor. Where it is
     * one Dma-Buf per buffer, they differ by file descriptor and every offset is
     * 0. An offset alone therefore identifies a buffer under the first model and
     * nothing under the second.
     *
     * The pair (file descriptor, offset) would identify one under both, and is
     * what the client used to import the frame. It is not what release is keyed
     * on, because naming a file descriptor across a binder boundary means passing
     * a ParcelFileDescriptor back - a dup and an SCM_RIGHTS pass on every
     * released frame - to name memory the implementation already has open. An
     * index carries the same information in an int.
     *
     * The index is also the safer key across teardown. A stale index after a
     * stop/start names nothing and is ignored; a stale file descriptor names
     * memory that may since have been freed.
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
     * The width of this frame in pixels, as the stream decoded it.
     *
     * Not necessarily the width configured on the decoder - that sizes the
     * buffers, while this is what the frame actually is. A stream that decodes
     * smaller produces smaller frames in the same pool.
     */
    int width;

    /**
     * The height of this frame in pixels, as the stream decoded it.
     */
    int height;

    /**
     * The DRM FOURCC pixel format of the frame.
     * @see CaptureProperty.DRM_FOURCC
     */
    int drmFourcc;

    /**
     * The presentation time of this frame in nanoseconds, carried through from the
     * decoded elementary stream unaltered.
     *
     * This is the frame's only timing reference and the value a consumer
     * synchronises against. Audio and video are not synchronised for the client
     * on this path - a captured frame goes to the client's own scene rather than
     * to a display plane, so the client decides when to present it, against the
     * clock its audio path is already running on.
     */
    long presentationTimeNs;
}

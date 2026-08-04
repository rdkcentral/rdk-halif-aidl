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
 *  @brief     Addressing information for one buffer in the capture pool.
 *
 *  Delivered once per session, for every buffer in the pool, in
 *  `ICaptureControllerListener.onPoolReady()`. A buffer's address and shape do not
 *  change while the session runs, so the client imports each one into an EGLImage on
 *  receipt and thereafter needs only to be told which buffer holds the current frame.
 *
 *  What changes per frame is the buffer index and the presentation time, and those are
 *  what `VideoFrameView` carries. Sending the addressing with every frame would move
 *  file descriptors across the binder boundary at frame rate to say what was already
 *  said at `onPoolReady()`.
 *
 *  The per-plane arrays are ordered by plane index and are the direct inputs to
 *  `EGL_EXT_image_dma_buf_import`: element N feeds `EGL_DMA_BUF_PLANE<N>_FD_EXT`,
 *  `EGL_DMA_BUF_PLANE<N>_OFFSET_EXT` and `EGL_DMA_BUF_PLANE<N>_PITCH_EXT`.
 *  For NV12 there are two planes, [Y, UV].
 *
 *  The offsets address the actual buffer layout and are not to be inferred from
 *  the pixel format.
 *
 *  @see VideoFrameView, ICaptureControllerListener.onPoolReady()
 *
 *  @author    Gerald Weatherup
 */

@VintfStability
parcelable VideoBufferView
{
    /**
     * The pool buffer this describes, in the range [0, pool buffer count).
     *
     * This is the value `VideoFrameView.bufferIndex` carries and the value passed to
     * `ICaptureController.releaseFrame()`.
     *
     * An index rather than an address, because the two vendor allocation models
     * put the buffer's identity in different places. Where the pool is one shared
     * Dma-Buf, buffers differ by offset and share a file descriptor. Where it is
     * one Dma-Buf per buffer, they differ by file descriptor and every offset is
     * 0. An offset alone therefore identifies a buffer under the first model and
     * nothing under the second.
     *
     * The pair (file descriptor, offset) would identify one under both, and is
     * what the client used to import the buffer. It is not what release is keyed
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
     * Each buffer carries the file descriptors and offsets that address it, so a client
     * imports from `planeFds` and `planeOffsets` alone and needs to know nothing about
     * how the vendor allocated the pool - one Dma-Buf carved into offset-addressed
     * buffers and one Dma-Buf per buffer are both served by this.
     *
     * A CLIENT CACHING EGLImages MUST KEY THE CACHE ON `bufferIndex`, or equivalently
     * on the pair (file descriptor, offset) - NEVER on the file descriptor alone.
     * Where the pool is one shared Dma-Buf, every buffer carries the SAME descriptor
     * and differs only by offset, so a cache keyed on the descriptor collapses the
     * whole pool onto one entry and the client re-textures a single buffer for the
     * rest of the session. The picture freezes while frames continue to arrive, which
     * is not a failure the client can see in what it was handed.
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
     * The width in pixels of the frames this buffer holds.
     *
     * @see CaptureProperty.WIDTH
     */
    int width;

    /**
     * The height in pixels of the frames this buffer holds.
     *
     * @see CaptureProperty.HEIGHT
     */
    int height;

    /**
     * The DRM FOURCC pixel format of the frames this buffer holds.
     *
     * @see CaptureProperty.DRM_FOURCC
     */
    int drmFourcc;

    /**
     * The DRM format modifier describing how this buffer's bytes are arranged in memory.
     *
     * @see CaptureProperty.DRM_MODIFIER
     */
    long drmModifier;
}

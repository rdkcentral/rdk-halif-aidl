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
 *  One of these is delivered for every buffer in the pool, once per session, in
 *  `ICaptureControllerListener.onPoolReady()`. A buffer's addressing and shape shall
 *  not change for the life of the session, so a client imports each buffer once on
 *  receipt and thereafter is told only which buffer holds the current frame.
 *
 *  `planeFds` and `planeOffsets` shall together address every plane of the buffer,
 *  and a client shall be able to import the buffer from this parcelable alone.
 *
 *  The per-plane arrays are ordered by plane index and are the direct inputs to
 *  `EGL_EXT_image_dma_buf_import`: element N feeds `EGL_DMA_BUF_PLANE<N>_FD_EXT`,
 *  `EGL_DMA_BUF_PLANE<N>_OFFSET_EXT` and `EGL_DMA_BUF_PLANE<N>_PITCH_EXT`.
 *
 *  The offsets shall address the buffer's actual layout, and a client shall not
 *  infer them from the pixel format.
 *
 *  @see VideoFrameView, ICaptureControllerListener.onPoolReady()
 *
 *  @author    Gerald Weatherup
 */

@VintfStability
parcelable VideoBufferView
{
    /**
     * The identity of this pool buffer, in the range [0, pool buffer count).
     *
     * The implementation shall assign each buffer an index that is unique within
     * the pool and stable for the life of the session. It is the value
     * `VideoFrameView.bufferIndex` carries on every frame, and the value passed to
     * `ICaptureController.releaseFrame()`.
     *
     * A BUFFER IS IDENTIFIED BY THIS INDEX AND BY NOTHING ELSE. The addressing in
     * `planeFds` and `planeOffsets` is how a client reaches the memory; it is not
     * an identity, and a client shall not treat either as one. Neither is
     * constrained by this interface beyond having to address the buffer, so a
     * client that keys on one of them keys on something the interface never
     * promised would be distinct.
     *
     * A file descriptor could not carry identity across a frame in any case: a
     * ParcelFileDescriptor is duplicated as it crosses the binder boundary, so
     * the same memory arrives as a different integer on each delivery. Sending
     * descriptors per frame would also cost a dup and an SCM_RIGHTS pass per
     * plane per frame, to name memory the implementation already holds open.
     *
     * The index is also the safer key across teardown. A stale index after a
     * stop/start names nothing and shall be ignored; a stale file descriptor
     * names memory that may since have been freed.
     */
    int bufferIndex;

    /**
     * One Dma-Buf file descriptor per plane of this buffer.
     *
     * PER PLANE, NOT PER BUFFER. `onPoolReady()` delivers one VideoBufferView per
     * buffer; these arrays index the planes within this one buffer. Every
     * per-plane array shall have one element per plane of the declared
     * `CaptureProperty.DRM_FOURCC`, in plane order. `DRM_FORMAT_NV12` is required
     * of every capture plane and has two planes, [Y, UV].
     *
     * A CLIENT CACHING IMPORTED IMAGES SHALL KEY THE CACHE ON `bufferIndex`, and
     * shall not key it on a file descriptor. Two buffers in a pool may carry the
     * same descriptor and differ only by offset, so a cache keyed on the
     * descriptor collapses the pool onto one entry and the client re-textures a
     * single buffer for the rest of the session. The picture freezes while frames
     * continue to arrive, which is not a failure the client can detect in what it
     * was handed.
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

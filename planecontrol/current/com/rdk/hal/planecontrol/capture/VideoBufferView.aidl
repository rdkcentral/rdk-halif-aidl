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
package com.rdk.hal.planecontrol.capture;

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
 *  The `plane` in these field names is an IMAGE plane - a colour component of one
 *  frame, such as the luma and interleaved chroma of `DRM_FORMAT_NV12` - and not the
 *  hardware plane this capture session runs on. The name follows
 *  `EGL_DMA_BUF_PLANE<N>_FD_EXT`, which these arrays feed directly.
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
 *  @author    Peter Stieglitz
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
     * This index is the buffer's identity. A client resolves a frame, keys any
     * cache, and releases a buffer by it.
     *
     * An index that names no buffer in the current pool is ignored, which is what
     * makes a release arriving after a stop safe.
     */
    int bufferIndex;

    /**
     * One Dma-Buf file descriptor per plane of this buffer.
     *
     * `onPoolReady()` delivers one VideoBufferView per pool buffer. Within it these
     * arrays are indexed by plane: element N addresses plane N of the selected
     * format, in plane order. `DRM_FORMAT_NV12`, for example, has two planes,
     * [Y, UV], so each array has two elements.
     *
     * A descriptor and its `planeOffsets` entry together address a plane. That pair
     * is the whole of what a client needs, and how the memory behind it was
     * allocated is the implementation's to choose - one descriptor shared across
     * planes or buffers at differing offsets, or a descriptor per plane at offset
     * zero, are equally valid and a client that imports from `planeFds` and
     * `planeOffsets` serves both without knowing which it was handed.
     *
     * A client caching imported images shall key the cache on `bufferIndex`, and
     * shall not key it on a file descriptor. Where buffers share a descriptor, a
     * cache keyed on it collapses the pool onto one entry and the client re-textures
     * a single buffer for the rest of the session. The picture freezes while frames
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
     * @see Property.WIDTH
     */
    int width;

    /**
     * The height in pixels of the frames this buffer holds.
     *
     * @see Property.HEIGHT
     */
    int height;

    /**
     * The DRM FOURCC pixel format of the frames this buffer holds.
     *
     * @see ICaptureController.setFormat(), FormatLayout.fourcc
     */
    int drmFourcc;

    /**
     * The DRM format modifier describing how this buffer's bytes are arranged in memory.
     *
     * @see ICaptureController.setFormat(), FormatLayout.modifier
     */
    long drmModifier;
}

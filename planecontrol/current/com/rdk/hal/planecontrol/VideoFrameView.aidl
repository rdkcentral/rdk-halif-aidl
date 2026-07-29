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
     * The ring slot this frame occupies, in the range [0, SLOT_COUNT).
     * This value is passed to `ICaptureController.releaseFrame()`.
     *
     * The slot is carried explicitly because on per-surface platforms every slot
     * has an offset of 0, so the offsets cannot identify the slot.
     */
    int slot;

    /**
     * One Dma-Buf file descriptor per plane.
     *
     * On a platform with `CaptureCapabilities.sharedRingBuffer` true, every entry
     * refers to the single ring file descriptor delivered by
     * `ICaptureControllerListener.onRingReady()` and is stable across frames.
     * Otherwise each entry is this slot's own file descriptor, cycling through at
     * most `CaptureProperty.SLOT_COUNT` distinct descriptors.
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

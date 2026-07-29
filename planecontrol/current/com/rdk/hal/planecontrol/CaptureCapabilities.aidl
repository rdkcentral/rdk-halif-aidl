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
 *  @brief     Capture capabilities definition for a plane resource.
 *  @author    Gerald Weatherup
 */

@VintfStability
parcelable CaptureCapabilities
{
    /**
     * The maximum number of slots that can be reserved in the capture ring.
     * @see CaptureProperty.SLOT_COUNT
     */
    int maxSlotCount;

    /**
     * The maximum size in bytes of a single ring slot.
     * @see CaptureProperty.SLOT_SIZE_BYTES
     */
    int maxSlotSizeBytes;

    /**
     * The DRM FOURCC pixel formats the capture ring can be configured for.
     * `DRM_FORMAT_NV12` is required to be present.
     * These are opaque values passed through this interface to the client EGL
     * implementation without interpretation by the HAL client.
     * @see CaptureProperty.DRM_FOURCC
     */
    int[] supportedFourCCs;

    /**
     * The DRM format modifiers the capture ring can be configured for.
     * `DRM_FORMAT_MOD_LINEAR` is required to be present.
     * These are opaque values passed through this interface to the client EGL
     * implementation without interpretation by the HAL client.
     * @see CaptureProperty.DRM_MODIFIER
     */
    long[] supportedModifiers;

    /**
     * Indicates whether the vendor layer exposes the ring as a single shared Dma-Buf
     * with offset-addressed slots, or as one Dma-Buf per slot.
     *
     * When true, `ICaptureControllerListener.onRingReady()` delivers a non-null ring
     * file descriptor and every `VideoFrameView.planeFds` entry refers to it.
     * When false, `onRingReady()` delivers a null ring file descriptor and each
     * frame carries its own slot file descriptor(s).
     */
    boolean sharedRingBuffer;

    /**
     * Indicates the behaviour when every ring slot is locked by the client and the
     * decoder has a new frame to write.
     *
     * When true, the decoder stalls until a slot is released.
     * When false, the oldest Ready slot is recycled and its frame is dropped.
     * Decode proceeds at full rate in both cases for as long as slots are available.
     */
    boolean stallsWhenRingFull;
}

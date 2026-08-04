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
 *  @brief     Capture properties used in the capture property get/set functions.
 *
 *  Named `CaptureProperty` because the module already defines a plane `Property` enum.
 *
 *  A capture session is configured entirely here: the frames the client wants, and the
 *  pool that holds them. The client states what it needs from a capture plane and the
 *  vendor layer configures the decoder to deliver it, so the decoder carries no capture
 *  configuration of its own and a client sets nothing on it.
 *
 *  `BUFFER_COUNT`, `WIDTH` and `HEIGHT` are written in the `READY` state, before
 *  `ICaptureController.start()`.
 *
 *  `DRM_FOURCC` and `DRM_MODIFIER` are read-only. They report the format and memory
 *  layout the plane delivers, which the client reads in order to import the frames
 *  correctly. The plane's own hardware determines both, so there is nothing for a client
 *  to choose and no request for the vendor to refuse.
 *
 *  @author    Gerald Weatherup
 */

@VintfStability
@Backing(type="int")
enum CaptureProperty {

    /**
     * The number of buffers in the capture pool.
     *
     * Optional. A session that does not write this leaves the count to the vendor,
     * which reports what it reserved in `ICaptureControllerListener.onPoolReady()`.
     * The vendor knows its own video memory region and its decoder's reference-frame
     * needs, so it is the party able to pick a working depth.
     *
     * Must not exceed `CaptureCapabilities.maxBufferCount`. A pool the platform's video
     * memory region cannot satisfy fails at `ICaptureController.start()` with
     * `CaptureErrorCode.OUT_OF_MEMORY`.
     *
     * The size of each buffer is not set here: it follows from the plane's `DRM_FOURCC`
     * and `DRM_MODIFIER` and the session's `WIDTH` and `HEIGHT`, together with the
     * vendor's own plane alignment. The resulting figure is reported back to the client in
     * `ICaptureControllerListener.onPoolReady()`.
     *
     * Type: Integer
     * Access: Read-write.
     * Write in states: READY
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if written in a state other than READY.
     */
    BUFFER_COUNT = 0,

    /**
     * The DRM FOURCC pixel format the captured frames are delivered in.
     *
     * FOURCC codes are defined by the Linux kernel in `include/uapi/drm/drm_fourcc.h`,
     * not by this interface. They are carried as an integer rather than an enum because
     * the kernel owns that namespace: new formats arrive with new kernel versions, and
     * enumerating them here would make every kernel addition an interface change to a
     * value this HAL neither defines nor controls.
     *
     * One of `CaptureCapabilities.supportedFourCCs`.
     * `DRM_FORMAT_NV12` (0x3231564E) is required to be supported by every product that
     * declares a capture plane.
     *
     * Type: Integer
     * Access: Read-only.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if a write is attempted.
     */
    DRM_FOURCC = 1,

    /**
     * The DRM format modifier describing how the bytes of a captured frame are arranged
     * in memory.
     *
     * Modifiers are defined by the Linux kernel in `include/uapi/drm/drm_fourcc.h`.
     * A modifier is 64 bits composed as `(vendor << 56) | value`: the top 8 bits are a
     * registered vendor namespace and the rest means whatever that vendor says, so most
     * modifiers are specific to the hardware that defines them. A compressed layout is
     * usually a parameterised family rather than a single value, which is why the
     * declaration lists exact values rather than layout names, and why these are
     * integers rather than an enum.
     *
     * `DRM_FORMAT_MOD_LINEAR` (0) is the one vendor-neutral layout, and the only one a
     * consumer that must touch the pixels - CPU readback, an encoder, or a GPU from a
     * different vendor - can rely on.
     *
     * One of `CaptureCapabilities.supportedModifiers`.
     * `DRM_FORMAT_MOD_LINEAR` (0) is required to be supported by every product that
     * declares a capture plane.
     *
     * Type: Long
     * Access: Read-only.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if a write is attempted.
     */
    DRM_MODIFIER = 2,

    /**
     * The frame width in pixels the capture buffers are sized for.
     *
     * On a plane that declares `CaptureCapabilities.resize` false, this must equal the
     * width the mapped source decodes to. It is not a scaling request there - it states
     * the resolution the client expects to receive, and
     * `ICaptureController.start()` fails with `CaptureErrorCode.RESOLUTION_MISMATCH`
     * if the source is decoding something else.
     *
     * Must not exceed `CaptureCapabilities.maxFrameWidth`.
     *
     * Type: Integer
     * Access: Read-write.
     * Write in states: READY
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT if the value exceeds
     *            `CaptureCapabilities.maxFrameWidth`.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if written in a state other than READY.
     *
     * @see CaptureCapabilities.resize
     */
    WIDTH = 3,

    /**
     * The frame height in pixels the capture buffers are sized for.
     *
     * As `WIDTH`, on a plane that cannot resize this states the resolution the client
     * expects rather than requesting a scale.
     *
     * Must not exceed `CaptureCapabilities.maxFrameHeight`.
     *
     * Type: Integer
     * Access: Read-write.
     * Write in states: READY
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT if the value exceeds
     *            `CaptureCapabilities.maxFrameHeight`.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if written in a state other than READY.
     *
     * @see CaptureCapabilities.resize
     */
    HEIGHT = 4,
}

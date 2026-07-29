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
 *  @author    Gerald Weatherup
 */

@VintfStability
@Backing(type="int")
enum CaptureProperty {

    /**
     * The number of slots in the capture ring.
     *
     * Must not exceed `CaptureCapabilities.maxSlotCount`.
     * The default is declared per product in the HAL Feature Profile.
     *
     * Type: Integer
     * Access: Read-write.
     * Write in states: READY
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if written in a state other than READY.
     */
    SLOT_COUNT = 0,

    /**
     * The size in bytes of a single ring slot, including per-plane alignment padding.
     *
     * Must not exceed `CaptureCapabilities.maxSlotSizeBytes`.
     *
     * Type: Integer
     * Access: Read-write.
     * Write in states: READY
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if written in a state other than READY.
     */
    SLOT_SIZE_BYTES = 1,

    /**
     * The DRM FOURCC pixel format the ring is configured for.
     *
     * Must be one of `CaptureCapabilities.supportedFourCCs`.
     * `DRM_FORMAT_NV12` is required to be supported by every product that declares a
     * capture resource.
     *
     * Type: Integer
     * Access: Read-write.
     * Write in states: READY
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if written in a state other than READY.
     */
    DRM_FOURCC = 2,

    /**
     * The DRM format modifier the ring is configured for.
     *
     * Must be one of `CaptureCapabilities.supportedModifiers`.
     * `DRM_FORMAT_MOD_LINEAR` is required to be supported by every product that declares
     * a capture resource.
     *
     * Type: Long
     * Access: Read-write.
     * Write in states: READY
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if written in a state other than READY.
     */
    DRM_MODIFIER = 3,

    /**
     * The width in pixels of the captured frames.
     *
     * Type: Integer
     * Access: Read-write.
     * Write in states: READY
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if written in a state other than READY.
     */
    WIDTH = 4,

    /**
     * The height in pixels of the captured frames.
     *
     * Type: Integer
     * Access: Read-write.
     * Write in states: READY
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if written in a state other than READY.
     */
    HEIGHT = 5,
}

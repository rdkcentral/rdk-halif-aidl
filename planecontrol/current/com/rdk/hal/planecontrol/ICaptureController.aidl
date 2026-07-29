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

import com.rdk.hal.planecontrol.CaptureProperty;
import com.rdk.hal.planecontrol.CapturePropertyKVPair;
import com.rdk.hal.planecontrol.VideoFrameView;
import com.rdk.hal.PropertyValue;

/**
 *  @brief     Capture session controller interface.
 *
 *  Returned by `ICapture.open()` and valid until `ICapture.close()`.
 *
 *  <h3>Frame flow</h3>
 *  Each ring slot is Free, Ready or Locked. The decoder writes into Free slots and marks
 *  them Ready when the frame is complete. `acquireLatestFrame()` moves the newest Ready
 *  slot to Locked and returns it; the decoder never writes into a Locked slot.
 *  `releaseFrame()` returns a Locked slot to Free.
 *
 *  Decode proceeds at full rate regardless of how sparsely or slowly the client acquires.
 *  The behaviour when every slot is Locked is declared per product in
 *  `CaptureCapabilities.stallsWhenRingFull`.
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 *
 *  @author    Gerald Weatherup
 */

@VintfStability
interface ICaptureController
{
    /**
     * Starts the capture session.
     *
     * Reserves a ring of `CaptureProperty.SLOT_COUNT` slots of
     * `CaptureProperty.SLOT_SIZE_BYTES` each from the platform's video memory region,
     * and wires the bound video decoder's `OperationalMode.GRAPHICS_TEXTURE` output into
     * the ring.
     *
     * The capture resource transitions to a `STARTING` state and then a `STARTED` state,
     * and `ICaptureControllerListener.onRingReady()` is raised once the ring is addressable.
     *
     * The bound video decoder must have `OperationalMode.GRAPHICS_TEXTURE` selected. A
     * decoder configured to emit a format other than the one the ring is configured for
     * fails here with `CaptureErrorCode.FORMAT_MISMATCH` rather than falling back to plane
     * output.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If the resource is not in the READY state.
     * @exception binder::Status::Exception::EX_SERVICE_SPECIFIC with a CaptureErrorCode value:
     *            `OUT_OF_MEMORY` if the ring reservation was refused,
     *            `DECODER_NOT_TEXTURE` if the bound decoder is not in GRAPHICS_TEXTURE mode,
     *            `FORMAT_MISMATCH` if the ring format differs from the decoder output format.
     *
     * @pre The resource must be in State::READY.
     *
     * @see stop(), ICaptureControllerListener.onRingReady()
     */
    void start();

    /**
     * Stops the capture session.
     *
     * Unwires the video decoder from the ring and releases the ring and all its Dma-Bufs.
     * The capture resource transitions to a `STOPPING` state and then a `READY` state.
     * The bound video decoder is left as it is.
     *
     * Any slots still Locked by the client are released.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If the resource is not in the STARTED state.
     *
     * @pre The resource must be in State::STARTED.
     *
     * @see start()
     */
    void stop();

    /**
     * Acquires the newest Ready slot and transitions it to Locked.
     *
     * This function never blocks. It returns null when no Ready slot exists, and never
     * returns a frame it has already returned.
     *
     * Older Ready slots that the newest frame overtakes are returned to Free.
     *
     * @returns VideoFrameView describing the acquired frame, or null if no new frame is
     *          available.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If the resource is not in the STARTED state.
     *
     * @pre The resource must be in State::STARTED.
     *
     * @see releaseFrame()
     */
    @nullable VideoFrameView acquireLatestFrame();

    /**
     * Releases a previously acquired slot, transitioning it from Locked to Free.
     *
     * `slot` must be a `VideoFrameView.slot` value previously returned by
     * `acquireLatestFrame()`. This function is idempotent - a slot that is already Free,
     * or a value outside the ring, returns without raising an exception.
     *
     * @param[in] slot      The ring slot to release.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @see acquireLatestFrame()
     */
    void releaseFrame(in int slot);

    /**
     * Sets a capture property.
     *
     * The ring shape properties are written in the `READY` state, before `start()`.
     *
     * @param[in] property              The key of a property from the CaptureProperty enum.
     * @param[in] propertyValue         Property value.
     *
     * @returns boolean
     * @retval true     Property was set successfully.
     * @retval false    Invalid property or property value parameter.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid value.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if the property cannot be written in the current state.
     *
     *
     * @see ICapture.getProperty(), setPropertyMultiAtomic()
     */
    boolean setProperty(in CaptureProperty property, in PropertyValue propertyValue);

    /**
     * Sets multiple capture properties atomically.
     *
     * For example, the `SLOT_COUNT`, `SLOT_SIZE_BYTES`, `DRM_FOURCC` and `DRM_MODIFIER`
     * properties can be set in a single call. Properties must only appear once in the list.
     *
     * @param[in] propertyKVList        Array of property key-value pairs.
     *
     * @returns boolean
     * @retval true     Properties were set successfully.
     * @retval false    Invalid property or property value parameter.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid parameters.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if the properties cannot be written in the current state.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     *
     *
     * @see setProperty(), ICapture.getPropertyMulti()
     */
    boolean setPropertyMultiAtomic(in CapturePropertyKVPair[] propertyKVList);
}

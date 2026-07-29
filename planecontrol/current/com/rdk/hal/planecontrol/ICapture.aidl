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

import com.rdk.hal.planecontrol.CaptureCapabilities;
import com.rdk.hal.planecontrol.CaptureProperty;
import com.rdk.hal.planecontrol.CapturePropertyKVPair;
import com.rdk.hal.planecontrol.ICaptureController;
import com.rdk.hal.planecontrol.ICaptureControllerListener;
import com.rdk.hal.planecontrol.State;
import com.rdk.hal.videodecoder.IVideoDecoder;
import com.rdk.hal.PropertyValue;

/**
 *  @brief     Decoded video frame capture interface.
 *
 *  A capture resource routes a video decoder's output into a ring of Dma-Buf slots
 *  which the client imports as GPU textures, instead of routing it to a display plane.
 *  It is obtained from `IPlaneControl.getCapture()` for the video plane resource the
 *  decoder would otherwise have been mapped to.
 *
 *  The `IVideoDecoder` contract is unchanged by capture - the decoder does not know
 *  where its output goes. `IPlaneControl.setVideoSourceDestinationPlaneMapping()` routes
 *  it to a display plane; `ICapture` routes it to a Dma-Buf ring.
 *
 *  Session lifecycle:
 *  @code
 *    ICapture capture = planeControl.getCapture(planeResourceIndex, captureEventListener);
 *    ICaptureController controller = capture.open(videoDecoderId, captureControllerListener);
 *    controller.setPropertyMultiAtomic(ringShape);   // slot count, size, format, modifier
 *    controller.start();                             // onRingReady() follows
 *    VideoFrameView frame = controller.acquireLatestFrame();
 *    controller.releaseFrame(frame.slot);
 *    controller.stop();
 *    capture.close(controller);
 *  @endcode
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
interface ICapture
{
    /**
     * Gets the capabilities of this capture resource.
     *
     * This function can be called at any time and is not dependent on any capture state.
     * The returned value is not allowed to change between calls.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns CaptureCapabilities parcelable.
     *
     */
    CaptureCapabilities getCapabilities();

    /**
     * Gets the current capture resource state.
     *
     * @returns State enum value.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     *
     * @see ICaptureEventListener.onStateChanged()
     */
    State getState();

    /**
     * Gets a capture property.
     *
     * @param[in] property              The key of a property from the CaptureProperty enum.
     *
     * @returns PropertyValue or null if the property key is unknown.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid property value.
     *
     *
     * @see ICaptureController.setProperty(), getPropertyMulti()
     */
    @nullable PropertyValue getProperty(in CaptureProperty property);

    /**
     * Gets multiple capture properties.
     *
     * Retrieves values for a list of property keys.
     *
     * Input `properties` is a non-null array of `CaptureProperty` keys. Each key must be a
     * valid enum value; unknown or out-of-range values are treated as invalid.
     *
     * Output `propertyKVList` returns one `CapturePropertyKVPair` per requested key, with
     * the same ordering as `properties`. For each pair, the `property` field echoes
     * the requested key and `propertyValue` is populated on success.
     *
     * Error handling and return semantics:
     * - Passing an empty `properties` array fails with `EX_ILLEGAL_ARGUMENT`.
     * - If any key in `properties` is invalid, no values are populated and the
     *   call fails with `EX_ILLEGAL_ARGUMENT`.
     * - If a required out-parameter is null (e.g. `propertyKVList`), the call fails
     *   with `EX_NULL_POINTER`.
     * - When an exception is raised, no return value is transmitted.
     *
     * @param[in] properties      Non-empty list of property keys to query.
     * @param[out] propertyKVList Returned key/value pairs corresponding to `properties`.
     *
     * @returns boolean
     * @retval true               All property values were returned successfully.
     * @retval false              The property values could not be retrieved.
     *
     * @exception binder::Status::Exception::EX_NONE             Success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT Invalid property key(s) or empty input list.
     * @exception binder::Status::Exception::EX_NULL_POINTER     Null out-parameter.
     *
     *
     * @see getProperty()
     */
    boolean getPropertyMulti(in CaptureProperty[] properties, out CapturePropertyKVPair[] propertyKVList);

    /**
     * Opens a capture session bound to a video decoder.
     *
     * If successful the capture resource transitions to an `OPENING` state and then a
     * `READY` state, which is notified to the registered `ICaptureEventListener`.
     *
     * The returned `ICaptureController` is used by the client to configure the ring,
     * start and stop the session, and acquire and release frames. Controller related
     * callbacks are made through the `ICaptureControllerListener` passed into the call.
     *
     * The client configures the ring shape through `ICaptureController.setProperty()` in
     * the `READY` state, before calling `ICaptureController.start()`.
     *
     * The bound decoder must have `OperationalMode.GRAPHICS_TEXTURE` selected in its
     * `Property.OPERATIONAL_MODE` before `ICaptureController.start()` is called. Whether
     * that mode is available is advertised by
     * `IVideoDecoderManager.getSupportedOperationalModes()`.
     *
     * A video decoder can be bound to at most one capture session at a time.
     *
     * If the client that opened the `ICaptureController` crashes, then the
     * `ICaptureController` has `stop()` and `close()` implicitly called to perform clean up.
     *
     * @param[in] videoDecoderId                The ID of the video decoder to capture from.
     * @param[in] captureControllerListener     Listener object for controller callbacks.
     *
     * @returns ICaptureController or null if the video decoder cannot be bound to this
     *          capture resource.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If the resource is not in the CLOSED state.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT If `videoDecoderId` is not a valid video decoder ID.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     * @exception binder::Status::Exception::EX_SERVICE_SPECIFIC with `CaptureErrorCode.DECODER_BUSY`
     *            if the video decoder is already bound to another capture session.
     *
     * @pre The resource must be in State::CLOSED.
     *
     * @see close(), ICaptureController
     */
    @nullable ICaptureController open(in IVideoDecoder.Id videoDecoderId, in ICaptureControllerListener captureControllerListener);

    /**
     * Closes the capture session.
     *
     * The capture resource must be in a `READY` state before it can be closed.
     * If successful the resource transitions to a `CLOSING` state and then a `CLOSED` state.
     *
     * The ring and all its Dma-Bufs are released, and the vendor wiring between the decoder
     * and the ring is undone. The bound video decoder is not stopped - only the capture
     * binding is undone.
     *
     * @param[in] captureController     Instance of the ICaptureController.
     *
     * @returns boolean
     * @retval true     Successfully closed.
     * @retval false    Invalid state or unrecognised parameter.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If the resource is not in the READY state.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     *
     * @pre The resource must be in State::READY.
     *
     * @see open()
     */
    boolean close(in ICaptureController captureController);
}

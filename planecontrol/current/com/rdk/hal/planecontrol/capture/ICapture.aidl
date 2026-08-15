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

import com.rdk.hal.planecontrol.capture.CaptureCapabilities;
import com.rdk.hal.planecontrol.capture.ICaptureController;
import com.rdk.hal.planecontrol.capture.ICaptureControllerListener;
import com.rdk.hal.planecontrol.capture.State;
import com.rdk.hal.PropertyValue;

/**
 *  @brief     Decoded video frame capture interface.
 *
 *  A capture resource routes a video source's decoded frames into a pool of Dma-Buf
 *  buffers which the client imports as GPU textures, instead of routing them to a
 *  display plane. It is obtained from `IPlaneControl.getCapture()` for a plane resource
 *  of type `PlaneType.CAPTURE`.
 *
 *  The source is chosen the same way it is for a display plane, with
 *  `IPlaneControl.setVideoSourceDestinationPlaneMapping()`. That mapping is the whole of
 *  the binding: a source mapped to a capture plane is captured, and the source mapped
 *  there is the source this session delivers. There is no second place a decoder is
 *  named, so there is no second place for the two to disagree.
 *
 *  The `IVideoDecoder` contract is unchanged by capture - the decoder does not know
 *  where its output goes, and nothing is set on it to arrange capture.
 *
 *  A capture session is configured here in full - the frames the client wants and the
 *  pool that holds them are settled by `CaptureCapabilities` and one `setFormat()` call.
 *  The client asks this plane for what it needs and the vendor layer configures the
 *  mapped source's decoder to deliver it, by whatever internal path that platform
 *  requires.
 *
 *  Session lifecycle:
 *  @code
 *    planeControl.setVideoSourceDestinationPlaneMapping(     // bind the source
 *        {{ SourceType.VIDEO_SINK, sinkIndex, planeResourceIndex }});
 *    ICapture capture = planeControl.getCapture(planeResourceIndex, captureEventListener);
 *    ICaptureController controller = capture.open(captureControllerListener);
 *    planeControl.setProperty(capturePlane, WIDTH, w);   // frame size, as any plane's
 *    planeControl.setProperty(capturePlane, HEIGHT, h);
 *    controller.setFormat(caps.supportedFormats[i]);     // format and layout, paired
 *    controller.start();                                 // onPoolReady() delivers the pool
 *
 *    // onPoolReady() arrives on a binder thread. Keep the buffers and hand them to
 *    // the thread that owns the GL context; that thread imports each one once,
 *    // keyed by bufferIndex. planeFds[0], planeOffsets[0] and planeStrides[0] feed
 *    // EGL_DMA_BUF_PLANE0_FD_EXT, _OFFSET_EXT and _PITCH_EXT - PLANE1 for NV12
 *    // chroma - with drmFourcc and drmModifier. No translation, no copy.
 *    for (VideoBufferView b : buffers)
 *        eglImage[b.bufferIndex] = eglCreateImageKHR(dpy, EGL_NO_CONTEXT,
 *                                      EGL_LINUX_DMA_BUF_EXT, NULL, attributesOf(b));
 *
 *    // Per frame - the index selects an image already imported, nothing is re-imported.
 *    frame = controller.acquireLatestFrame(VideoFrameView.NO_BUFFER);
 *    draw(eglImage[frame.bufferIndex]);
 *    frame = controller.acquireLatestFrame(frame.bufferIndex);   // release + acquire
 *    draw(eglImage[frame.bufferIndex]);
 *    controller.releaseFrame(frame.bufferIndex);      // last frame of the session
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
 *  @author    Peter Stieglitz
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
     * Opens a capture session on this plane.
     *
     * The source captured is whatever `IPlaneControl` currently has mapped to this
     * plane, so a source must be mapped to it before this is called.
     *
     * If successful the capture resource transitions to a
     * `READY` state, which is notified to the registered `ICaptureEventListener`.
     *
     * The returned `ICaptureController` is used by the client to configure the pool,
     * start and stop the session, and acquire and release frames. Controller related
     * callbacks are made through the `ICaptureControllerListener` passed into the call.
     *
     * The client selects the session's format through
     * `ICaptureController.setProperty()` in the `READY` state, before calling
     * `ICaptureController.start()` - the frame format and size it wants, and the depth
     * of the pool that holds them.
     *
     * Nothing is set on the mapped source's decoder. Making it deliver the frames this
     * session was configured for is the vendor layer's own business, arranged over
     * whatever internal path the platform provides.
     *
     * A source is mapped to at most one plane at a time, which is what limits a decoder
     * to a single capture session.
     *
     * If the client that opened the `ICaptureController` crashes, then the
     * `ICaptureController` has `stop()` and `close()` implicitly called to perform clean up.
     *
     * @param[in] captureControllerListener     Listener object for controller callbacks.
     *
     * @returns ICaptureController or null if a capture session cannot be opened on this
     *          plane.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If the resource is not in the CLOSED state.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     * @exception binder::Status::Exception::EX_SERVICE_SPECIFIC with `CaptureErrorCode.SOURCE_NOT_MAPPED`
     *            if no video source is mapped to this plane.
     *
     * @pre The resource must be in State::CLOSED.
     * @pre A video source must be mapped to this plane through
     *      `IPlaneControl.setVideoSourceDestinationPlaneMapping()`.
     *
     * @see close(), ICaptureController, IPlaneControl.setVideoSourceDestinationPlaneMapping()
     */
    @nullable ICaptureController open(in ICaptureControllerListener captureControllerListener);

    /**
     * Closes the capture session.
     *
     * The capture resource must be in a `READY` state before it can be closed.
     * If successful the resource transitions to a `CLOSED` state.
     *
     * The pool and all its Dma-Bufs are released, and the vendor wiring between the
     * source and the pool is undone. The source's decoder is not stopped, and its plane
     * mapping is left as it is - only the capture session ends.
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

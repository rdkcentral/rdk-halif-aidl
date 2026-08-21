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
package com.rdk.hal.capture;

import com.rdk.hal.capture.CaptureCapabilities;
import com.rdk.hal.capture.CaptureSource;
import com.rdk.hal.capture.ICaptureController;
import com.rdk.hal.capture.ICaptureControllerListener;
import com.rdk.hal.capture.State;
import com.rdk.hal.PropertyValue;

/**
 *  @brief     Frame capture bound to a pipeline source.
 *
 *  A capture resource takes frames from one stage of the pipeline and delivers them
 *  into a pool of Dma-Buf buffers the client imports as GPU textures. It is an output
 *  in its own right, not a destination within some other module's model: it is
 *  addressed by its own `Id`, obtained from `ICaptureManager`, and it carries its own
 *  frame size.
 *
 *  **The binding is the session.** `open()` names the stage to take frames from, and
 *  that stage is what the session delivers for its lifetime. A source may have a
 *  display path, a capture, both or neither - none of those is a special case, and a
 *  capture never needs a display destination to exist.
 *
 *  What flows through the bound stage is decided by the input feed exactly as before.
 *  A capture neither selects nor changes it, and the `IVideoDecoder` contract is
 *  unchanged - the decoder does not know where its output goes, and nothing is set on
 *  it to arrange capture.
 *
 *  Binding takes a view rather than diverting the frames. Anything already consuming
 *  the stage carries on unaffected, which is what allows a capture to be attached to a
 *  pipeline that is already running. `CaptureCapabilities.maxCapturesPerSource` says
 *  how many captures one stage can carry.
 *
 *  A session is configured here in full - the frames the client wants and the pool that
 *  holds them are settled by `CaptureCapabilities`, the size properties and one
 *  `setFormat()` call. The client asks for what it needs and the vendor layer arranges
 *  for the bound source to deliver it, by whatever internal path that platform requires.
 *
 *  Session lifecycle:
 *  @code
 *    ICapture.Id[] ids = captureManager.getCaptureIds();
 *    ICapture capture = captureManager.getCapture(ids[0], captureEventListener);
 *    CaptureCapabilities caps = capture.getCapabilities();
 *
 *    ICaptureController controller =                       // bind: this is the session
 *        capture.open(CaptureSource.VIDEO_DECODER, captureControllerListener);
 *    controller.setProperty(Property.WIDTH, w);            // the capture's own size
 *    controller.setProperty(Property.HEIGHT, h);
 *    controller.setFormat(caps.supportedFormats[i]);       // format and layout, paired
 *    controller.start();                                   // onPoolReady() delivers the pool
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
    /** Capture resource ID type */
    @VintfStability
    parcelable Id {
        /** The undefined ID value. */
        const int UNDEFINED = -1;

        /** The actual resource ID */
        int value;
    }

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
     * Opens a capture session bound to a pipeline source.
     *
     * The binding is the session. `captureSource` names the stage frames are taken
     * from, and it must be one of `CaptureCapabilities.supportedSources`. What flows
     * through that stage is decided by the input feed as it always was; a capture
     * neither selects nor changes it.
     *
     * Binding does not divert the frames. A stage that is already delivering to a
     * consumer continues to, and that consumer sees no change; the capture takes its
     * own view of the same frames. Whether a stage can carry more than one capture at
     * a time is declared by the platform, and a bind beyond that limit is refused.
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
     * Nothing is set on the bound source. Making it deliver the frames this session was
     * configured for is the vendor layer's own business, arranged over whatever
     * internal path the platform provides.
     *
     * If the client that opened the `ICaptureController` crashes, then the
     * `ICaptureController` has `stop()` and `close()` implicitly called to perform clean up.
     *
     * @param[in] captureSource                 The pipeline stage to bind this session to.
     * @param[in] captureControllerListener     Listener object for controller callbacks.
     *
     * @returns ICaptureController or null if a capture session cannot be opened against
     *          that source.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If the resource is not in the CLOSED state.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     * @exception binder::Status::Exception::EX_SERVICE_SPECIFIC with `CaptureErrorCode.SOURCE_UNAVAILABLE`
     *            if the source is not one this resource supports, or cannot carry a
     *            further capture.
     *
     * @pre The resource must be in State::CLOSED.
     * @pre `captureSource` is one of `CaptureCapabilities.supportedSources`.
     *
     * @see close(), ICaptureController, CaptureSource, CaptureCapabilities.supportedSources
     */
    @nullable ICaptureController open(in CaptureSource captureSource, in ICaptureControllerListener captureControllerListener);

    /**
     * Closes the capture session.
     *
     * The capture resource must be in a `READY` state before it can be closed.
     * If successful the resource transitions to a `CLOSED` state.
     *
     * The pool and all its Dma-Bufs are released, and the vendor wiring between the
     * source and the pool is undone. The bound source is not stopped and nothing else
     * consuming it is affected - only the capture session ends.
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

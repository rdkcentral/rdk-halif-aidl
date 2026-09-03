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
package com.rdk.hal.videocapture;

import com.rdk.hal.videocapture.Capabilities;
import com.rdk.hal.videocapture.IVideoCaptureController;
import com.rdk.hal.videocapture.IVideoCaptureControllerListener;
import com.rdk.hal.videocapture.Property;
import com.rdk.hal.videocapture.Source;
import com.rdk.hal.videocapture.State;
import com.rdk.hal.PropertyValue;

/**
 *  @brief     Video frame capture bound to a named pipeline source.
 *
 *  A capture resource takes frames from one stage of the pipeline and delivers them
 *  into a pool of Dma-Buf buffers the client imports as GPU textures. It is an output
 *  in its own right, not a destination within some other module's model: it is
 *  addressed by its own `Id`, obtained from `IVideoCaptureManager`, and it carries its own
 *  frame size.
 *
 *  **The binding is the session.** `open()` names the source frames are taken from -
 *  one arm of `Source`, naming a particular sink or decoder by its own ID - and that
 *  source is what the session delivers for its lifetime. A source may have a display
 *  path, a capture, both or neither - none of those is a special case, and a capture
 *  never needs a display destination to exist.
 *
 *  **A capture is served the frames of the stage it names,** and the stage decides what
 *  a frame means. A capture adds no scheduler, no clock and no timing policy of its own:
 *  bound to a sink it takes what that sink would present, under whatever presentation
 *  mode the sink is running; bound to a decoder it takes what the decoder produced, in
 *  the order it produced it. `Source` states the two.
 *
 *  **Which sources can be captured from is declared here,** in
 *  `Capabilities.supportedSources`, not on the sources themselves. Capture is a module
 *  in its own right, so what can be captured from is a property of the capture; a sink
 *  and a decoder carry no capture vocabulary and are unchanged by this module existing.
 *
 *  What flows through the bound source is decided by the input feed exactly as before.
 *  A capture neither selects nor changes it - nothing is set on the source to arrange
 *  capture, and its display path is untouched.
 *
 *  Binding takes a view rather than diverting the frames. Anything already consuming
 *  the stage carries on unaffected, which is what allows a capture to be attached to a
 *  pipeline that is already running. `Capabilities.maxCapturesPerSource` says how many
 *  captures one source can carry.
 *
 *  A session is configured here in full - the frames the client wants and the pool that
 *  holds them are settled by `Capabilities`, the size properties and one
 *  `setFormat()` call. The client asks for what it needs and the vendor layer arranges
 *  for the bound source to deliver it, by whatever internal path that platform requires.
 *
 *  Session lifecycle:
 *  @code
 *    IVideoCapture.Id[] ids = captureManager.getVideoCaptureIds();
 *    IVideoCapture capture = captureManager.getVideoCapture(ids[0], captureEventListener);
 *    Capabilities caps = capture.getCapabilities();
 *
 *    Source source = caps.supportedSources[0];             // what open() accepts, listed
 *
 *    IVideoCaptureController controller =                  // bind: this is the session
 *        capture.open(source, captureControllerListener);
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
interface IVideoCapture
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
     * @returns Capabilities parcelable.
     *
     */
    Capabilities getCapabilities();

    /**
     * Gets the current capture resource state.
     *
     * @returns State enum value.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     *
     * @see IVideoCaptureEventListener.onStateChanged()
     */
    State getState();


    /**
     * Opens a capture session bound to one pipeline source.
     *
     * The binding is the session. `source` names the stage frames are taken from - one
     * arm of `Source`, naming a particular sink or decoder - and it is that source, not
     * merely a source of its kind, for the session's lifetime. What flows through it is
     * decided by the input feed as it always was; a capture neither selects nor changes
     * it.
     *
     * Frames are delivered as the named stage produces them - see `HAL.VIDEOCAPTURE.10`.
     * Bound to a sink, that is what the sink would be presenting, under whatever
     * presentation mode it is running: where the sink presents against an attached
     * `IAVClock` it is the frame due now with audio latency and AV-sync correction
     * already applied, frames whose presentation time has passed dropped and frames
     * whose time has not yet come held. Bound to a decoder, it is what the decoder
     * produced, in the order it produced it, with no presentation scheduling applied.
     * Either way the stage keeps the timing policy and the capture adds no clock, no
     * scheduler and no policy of its own.
     *
     * The capture declares which sources it serves in `Capabilities.supportedSources`,
     * and the call is accepted only against a source listed there. A source outside the
     * list is refused with `ErrorCode.SOURCE_NOT_CAPTURABLE` however much capacity it
     * has.
     *
     * Binding does not divert the frames. A source already feeding a display path
     * continues to, and the display sees no change; the capture takes its own view of
     * the same frames. How many captures one source can carry at a time is declared in
     * `Capabilities.maxCapturesPerSource`, and a bind beyond that limit is refused with
     * `ErrorCode.SOURCE_UNAVAILABLE`.
     *
     * If successful the capture resource transitions to a `READY` state, which is
     * notified to the registered `IVideoCaptureEventListener`.
     *
     * The returned `IVideoCaptureController` is used by the client to configure the pool,
     * start and stop the session, and acquire and release frames. Controller related
     * callbacks are made through the `IVideoCaptureControllerListener` passed into the call.
     *
     * The client configures the session in the `READY` state, before calling
     * `IVideoCaptureController.start()`: the pixel format and memory layout with
     * `IVideoCaptureController.setFormat()`, and the frame size with
     * `IVideoCaptureController.setProperty()`. Pool depth is not configured; the
     * platform calibrates it and `onPoolReady()` delivers however many buffers it is.
     *
     * Nothing is set on the bound source. Making it deliver the frames this session was
     * configured for is the vendor layer's own business, arranged over whatever
     * internal path the platform provides.
     *
     * If the client that opened the `IVideoCaptureController` crashes, then the
     * `IVideoCaptureController` has `stop()` and `close()` implicitly called to perform clean up.
     *
     * @param[in] source                        The pipeline source to take frames from,
     *                                          named by one arm of `Source`.
     * @param[in] captureControllerListener     Listener object for controller callbacks.
     *
     * @returns IVideoCaptureController or null if a capture session cannot be opened against
     *          that source.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If the resource is not in the CLOSED state.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT If `source` names no resource of
     *            the arm's kind.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     * @exception binder::Status::Exception::EX_SERVICE_SPECIFIC with
     *            `ErrorCode.SOURCE_NOT_CAPTURABLE` if `source` is absent from
     *            `Capabilities.supportedSources`, or `ErrorCode.SOURCE_UNAVAILABLE` if that
     *            source cannot carry a further capture.
     *
     * @pre The resource must be in State::CLOSED.
     * @pre `source` appears in `Capabilities.supportedSources`.
     *
     * @see close(), IVideoCaptureController, Source, Capabilities.supportedSources,
     *      Capabilities.maxCapturesPerSource
     */
    @nullable IVideoCaptureController open(in Source source, in IVideoCaptureControllerListener captureControllerListener);

    /**
     * Gets a property of this capture resource.
     *
     * Readable by any holder of this interface and at any time; reading a property
     * does not require the session, and does not depend on capture state. Properties
     * are set through `IVideoCaptureController.setProperty()` by the client that opened
     * the session.
     *
     * @param[in] property      The key of a property from the Property enum.
     *
     * @returns PropertyValue or null if the property key is unknown.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid property value.
     *
     * @see IVideoCaptureController.setProperty(), Property
     */
    PropertyValue getProperty(in Property property);

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
     * @param[in] captureController     Instance of the IVideoCaptureController.
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
    boolean close(in IVideoCaptureController captureController);
}

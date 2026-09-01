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
import com.rdk.hal.videocapture.State;
import com.rdk.hal.PropertyValue;
import com.rdk.hal.videodecoder.IVideoDecoder;
import com.rdk.hal.videosink.IVideoSink;

/**
 *  @brief     Video frame capture bound to a named pipeline source.
 *
 *  A capture resource takes frames from one stage of the pipeline and delivers them
 *  into a pool of Dma-Buf buffers the client imports as GPU textures. It is an output
 *  in its own right, not a destination within some other module's model: it is
 *  addressed by its own `Id`, obtained from `IVideoCaptureManager`, and it carries its own
 *  frame size.
 *
 *  **The binding is the session.** `openWithDecoder()` and `openWithSink()` each name
 *  the resource frames are taken from - a particular `IVideoDecoder` or a particular
 *  `IVideoSink`, by its own ID - and that resource is what the session delivers for
 *  its lifetime. A source may have a display path, a capture, both or neither - none
 *  of those is a special case, and a capture never needs a display destination to
 *  exist.
 *
 *  **The two attach modes differ in what a frame means, which is why they are two
 *  calls.** A decoder-attached session delivers the most recently decoded frame, with
 *  no clock applied and nothing dropped or held for timing; the frame's presentation
 *  time is carried for a client scheduling on its own timeline. A sink-attached
 *  session delivers the frame the sink would be presenting against its attached
 *  `IAVClock` now, with audio and graphics latency compensation already applied, late
 *  frames dropped and early frames held. A client needing AV-synced frames must use
 *  `openWithSink()`.
 *
 *  What flows through the bound stage is decided by the input feed exactly as before.
 *  A capture neither selects nor changes it, and the `IVideoDecoder` contract is
 *  unchanged - the decoder does not know where its output goes, and nothing is set on
 *  it to arrange capture.
 *
 *  Binding takes a view rather than diverting the frames. Anything already consuming
 *  the stage carries on unaffected, which is what allows a capture to be attached to a
 *  pipeline that is already running. `Capabilities.maxCapturesPerSource` says
 *  how many captures one stage can carry.
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
 *    // Pick a sink that declares it can be captured from. The decoder-attach form is
 *    // openWithDecoder(decoderId, ...) against a decoder on a platform declaring
 *    // OperationalMode.GRAPHICS_TEXTURE.
 *    IVideoSink.Id sinkId = ...;                           // supportsCapture == true
 *
 *    IVideoCaptureController controller =                  // bind: this is the session
 *        capture.openWithSink(sinkId, captureControllerListener);
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
     * Opens a capture session bound to a video decoder.
     *
     * The binding is the session. `videoDecoderId` names the decoder frames are taken
     * from, and it is that decoder - not merely a decoder - for the session's
     * lifetime. What flows through it is decided by the input feed as it always was; a
     * capture neither selects nor changes it.
     *
     * Frames are delivered as the decoder emits them. No clock is attached and no
     * AV-sync, audio-latency or graphics-latency compensation is applied: nothing is
     * dropped for being late and nothing is held for being early, because there is no
     * presentation reference to be late or early against. Each frame carries its
     * presentation time in `VideoFrameView.presentationTimeNs`, which is what a client
     * scheduling on its own timeline uses. A client that needs AV-synced frames must
     * use `openWithSink()` instead - see `HAL.VIDEOCAPTURE.12`.
     *
     * The decoder declares its side of this: the call is accepted only against a
     * platform whose `IVideoDecoderManager.getSupportedOperationalModes()` contains
     * `OperationalMode.GRAPHICS_TEXTURE`, and only if `Source.VIDEO_DECODER` is in
     * `Capabilities.supportedSources`.
     *
     * Binding does not divert the frames. A decoder that is already delivering to a
     * display path continues to, and that path sees no change; the capture takes its
     * own view of the same frames. How many captures one decoder can carry at a time
     * is declared in `Capabilities.maxCapturesPerSource`, and a bind beyond that limit
     * is refused.
     *
     * If successful the capture resource transitions to a `READY` state, which is
     * notified to the registered `IVideoCaptureEventListener`.
     *
     * The returned `IVideoCaptureController` is used by the client to configure the pool,
     * start and stop the session, and acquire and release frames. Controller related
     * callbacks are made through the `IVideoCaptureControllerListener` passed into the call.
     *
     * The client selects the session's format through
     * `IVideoCaptureController.setProperty()` in the `READY` state, before calling
     * `IVideoCaptureController.start()` - the frame format and size it wants, and the depth
     * of the pool that holds them.
     *
     * Nothing is set on the bound decoder. Making it deliver the frames this session was
     * configured for is the vendor layer's own business, arranged over whatever
     * internal path the platform provides.
     *
     * If the client that opened the `IVideoCaptureController` crashes, then the
     * `IVideoCaptureController` has `stop()` and `close()` implicitly called to perform clean up.
     *
     * @param[in] videoDecoderId                The decoder to take frames from.
     * @param[in] captureControllerListener     Listener object for controller callbacks.
     *
     * @returns IVideoCaptureController or null if a capture session cannot be opened against
     *          that decoder.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If the resource is not in the CLOSED state.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT If `videoDecoderId` names no
     *            decoder, or the platform does not support `OperationalMode.GRAPHICS_TEXTURE`.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     * @exception binder::Status::Exception::EX_SERVICE_SPECIFIC with `ErrorCode.SOURCE_UNAVAILABLE`
     *            if `Source.VIDEO_DECODER` is not one this resource supports, or that
     *            decoder cannot carry a further capture.
     *
     * @pre The resource must be in State::CLOSED.
     * @pre `Source.VIDEO_DECODER` is one of `Capabilities.supportedSources`.
     *
     * @see openWithSink(), close(), IVideoCaptureController, Capabilities.supportedSources
     */
    @nullable IVideoCaptureController openWithDecoder(in IVideoDecoder.Id videoDecoderId, in IVideoCaptureControllerListener captureControllerListener);

    /**
     * Opens a capture session bound to a video sink.
     *
     * The binding is the session. `videoSinkId` names the sink frames are taken from,
     * and it is that sink - not merely a sink - for the session's lifetime. What flows
     * through it is decided by the input feed as it always was; a capture neither
     * selects nor changes it.
     *
     * Frames are delivered as the sink would present them: the frame due against the
     * `IAVClock` attached to that sink, with audio latency and AV-sync correction
     * already applied, frames whose presentation time has passed dropped and frames
     * whose time has not yet come held. A client that draws each frame on receipt is
     * then in sync without computing anything - see `HAL.VIDEOCAPTURE.10`. The sink
     * keeps the scheduler; the capture is a second consumer of the frames it has
     * already scheduled.
     *
     * The sink declares its side of this: the call is accepted only against a sink
     * whose `com.rdk.hal.videosink.Capabilities.supportsCapture` is true, and only if
     * `Source.VIDEO_SINK` is in `Capabilities.supportedSources`.
     *
     * Binding does not divert the frames. A sink that is already rendering to a mapped
     * video plane continues to, and the display sees no change; the capture takes its
     * own view of the same scheduled frames. How many captures one sink can carry at a
     * time is declared in `Capabilities.maxCapturesPerSource`, and a bind beyond that
     * limit is refused.
     *
     * If successful the capture resource transitions to a `READY` state, which is
     * notified to the registered `IVideoCaptureEventListener`.
     *
     * The returned `IVideoCaptureController` is used by the client to configure the pool,
     * start and stop the session, and acquire and release frames. Controller related
     * callbacks are made through the `IVideoCaptureControllerListener` passed into the call.
     *
     * The client selects the session's format through
     * `IVideoCaptureController.setProperty()` in the `READY` state, before calling
     * `IVideoCaptureController.start()` - the frame format and size it wants, and the depth
     * of the pool that holds them.
     *
     * Nothing is set on the bound sink. Making it deliver the frames this session was
     * configured for is the vendor layer's own business, arranged over whatever
     * internal path the platform provides.
     *
     * If the client that opened the `IVideoCaptureController` crashes, then the
     * `IVideoCaptureController` has `stop()` and `close()` implicitly called to perform clean up.
     *
     * @param[in] videoSinkId                   The video sink to take frames from.
     * @param[in] captureControllerListener     Listener object for controller callbacks.
     *
     * @returns IVideoCaptureController or null if a capture session cannot be opened against
     *          that sink.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If the resource is not in the CLOSED state.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT If `videoSinkId` names no sink,
     *            or that sink declares `supportsCapture` false.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     * @exception binder::Status::Exception::EX_SERVICE_SPECIFIC with `ErrorCode.SOURCE_UNAVAILABLE`
     *            if `Source.VIDEO_SINK` is not one this resource supports, or that sink
     *            cannot carry a further capture.
     *
     * @pre The resource must be in State::CLOSED.
     * @pre `Source.VIDEO_SINK` is one of `Capabilities.supportedSources`.
     *
     * @see openWithDecoder(), close(), IVideoCaptureController, Capabilities.supportedSources
     */
    @nullable IVideoCaptureController openWithSink(in IVideoSink.Id videoSinkId, in IVideoCaptureControllerListener captureControllerListener);

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
     * @see openWithDecoder(), openWithSink()
     */
    boolean close(in IVideoCaptureController captureController);
}

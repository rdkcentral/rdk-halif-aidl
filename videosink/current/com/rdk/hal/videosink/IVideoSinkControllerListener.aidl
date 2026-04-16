/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
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
package com.rdk.hal.videosink;
import com.rdk.hal.State;

/**
 *  @brief     Controller callbacks listener interface for Video Sink.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
oneway interface IVideoSinkControllerListener
{
    /**
     * Callback when the first video frame has been rendered.
     *
     * The behaviour is the same for tunnelled and non-tunnelled video operating modes.
     * This occurs on the first frame rendered after an `open()` or `flush()` call.
	 * The frame may not immediately be visible due to video pipeline and compositor functions.
	 * The associated plane `Capabilities.vsyncDisplayLatency` indicates the expected time between
     * this callback and actual display.
     *
     * @param[in] nsPresentationTime    The presentation time of the frame.
     */
    void onFirstFrameRendered(in long nsPresentationTime);

    /**
     * Callback when the last video frame has been rendered.
     *
     * The behaviour is the same for tunnelled and non-tunnelled video operating modes.
     * This occurs on the last frame rendered in the session.
	 * The frame may not immediately be visible due to video pipeline and compositor functions.
     * The associated plane `Capabilities.vsyncDisplayLatency` indicates the expected time between
     * this callback and actual display.
     *
     * @param[in] nsPresentationTime    The presentation time of the frame.
     */
    void onEndOfStream(in long nsPresentationTime);

    /**
     * Callback to indicate a video frame buffer underflow condition.
     *
     * This occurs if the frame queue is empty at the next expected AV Clock based
     * presentation time for a video frame.
	 * The callback occurs only once when the queue becomes empty.
	 * The `onVideoResumed()` callback informs the client when video playback restarts,
	 * which allows the `onVideoUnderflow()` to occur again.
     *
     * @see onVideoResumed()
     */
    void onVideoUnderflow();

    /**
     * Callback to indicate that video has resumed presentation after a video underflow event.
     *
	 * The `onVideoUnderflow()` can occur again after `onVideoResumed()` has been called.
     *
     * @see onVideoUnderflow()
     */
    void onVideoResumed();

    /**
     * Callback when a requested `flush()` operation has completed.
     *
     * @see IVideoSinkController.flush()
     */
    void onFlushComplete();

    /**
     * Callback when the Video Sink has transitioned to a new state.
     *
     * @param[in] oldState	The state that the sink has transitioned from.
     * @param[in] newState  The new state that the sink has transitioned to.
     */
    void onStateChanged(in State oldState, in State newState);

    /**
     * Callback that signals the video sink input frame buffer queue has space again.
     *
     * Fired exactly once after a previous `IVideoSinkController.queueVideoFrame()` call
     * returned `false` (internal queue full), when the queue subsequently has space.
     *
     * The client SHOULD wait for this callback before retrying `queueVideoFrame()` to avoid
     * wasted binder transactions. Continuing to call `queueVideoFrame()` while the queue is
     * full is permitted but will return `false` repeatedly until space is available.
     *
     * Not fired in steady-state operation - only after a refused frame.
     *
     * @see IVideoSinkController.queueVideoFrame()
     */
    void onFrameBufferAvailable();
}

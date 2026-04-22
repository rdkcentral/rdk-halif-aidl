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
package com.rdk.hal.audiosink;
import com.rdk.hal.audiosink.ErrorCode;
import com.rdk.hal.State;

/**
 *  @brief     Controller callbacks listener interface from audio sink.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
oneway interface IAudioSinkControllerListener {

    /**
     * Callback when the sink has transitioned to a new state.
     *
     * @param[in] oldState	            The state transitioned from.
     * @param[in] newState              The new state transitioned to.
     */
    void onStateChanged(in State oldState, in State newState);

    /**
     * Callback when the first audio frame has started to be mixed.
     *
     * The behaviour is the same for tunnelled and non-tunnelled audio.
     * This occurs on the first audio frame in the session or after a flush() call.
     * The frame may not immediately be heard due to the audio pipeline output latency.
     *
     * @param[in] nsPresentationTime	The presentation time of the audio frame in nanoseconds.
     */
    void onFirstFrameRendered(in long nsPresentationTime);

    /**
     * Callback when the last audio frame has been completely passed to the mixer.
     *
     * The behaviour is the same for tunnelled and non-tunnelled audio.
     * This occurs on the last frame mixed in the session.
     * The audio may not immediately be heard due to audio mixer and output latencies.
     *
     * @param[in] nsPresentationTime	The presentation time of the audio frame in nanoseconds.
     */
    void onEndOfStream(in long nsPresentationTime);

    /**
    * Callback to indicate an audio frame buffer underflow condition.
    *
    * This occurs when the frame queue is empty, or when buffers are present but none
    * are available for presentation at the AV sync clock based presentation time.
    *
    * The callback occurs only once when this condition is met.
    *
    * The `onAudioResumed()` callback informs the client when audio playback restarts,
    * which allows the `onAudioUnderflow()` callback to occur again if a subsequent
    * underflow occurs.
    */
    void onAudioUnderflow();

    /**
     * Callback to indicate that audio has resumed after an audio underflow event.
     *
     * The onAudioUnderflow() can occur again after onAudioResumed() has been called.
     *
     * @param[in] nsPresentationTime	The presentation time of the audio frame in nanoseconds.
     */
    void onAudioResumed(in long nsPresentationTime);

    /**
     * Callback when a requested flush() operation has completed.
     */
    void onFlushComplete();

    /**
     * Callback that signals the audio sink input frame buffer queue has space again.
     *
     * Fired exactly once per back-pressure episode: when the internal queue transitions
     * from full to has-space after `IAudioSinkController.queueAudioFrame()` returned `false`.
     * If the client continues to call `queueAudioFrame()` during back-pressure (receiving
     * `false` repeatedly), only one callback is delivered per transition, regardless of
     * the number of intermediate `false` returns.
     *
     * The client SHOULD wait for this callback before retrying `queueAudioFrame()` to avoid
     * wasted binder transactions. Continuing to call `queueAudioFrame()` while the queue is
     * full is permitted but will return `false` repeatedly until space is available.
     *
     * Not fired in steady-state operation - only after a refused frame.
     *
     * @see IAudioSinkController.queueAudioFrame()
     */
    void onFrameBufferAvailable();
}

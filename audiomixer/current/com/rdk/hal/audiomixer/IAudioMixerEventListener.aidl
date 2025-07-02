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
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.audiomixer;

import com.rdk.hal.audiodecoder.Codec;
import com.rdk.hal.audiomixer.ContentType;

/**
 * @brief     Listener interface for asynchronous Audio Mixer events.
 * @details   Provides callbacks for runtime events such as input codec changes, error notifications,
 *            resource state changes, and other dynamic mixer events. 
 *            Intended to be registered with the IAudioMixerController.
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @copyright Copyright 2024 RDK Management
 */
@VintfStability
oneway interface IAudioMixerEventListener {
    /**
     * @brief     Called when the codec or content type changes on any audio mixer input.
     * @param[in] audioMixerInputIndex  The input index affected.
     * @param[in] codec                 The new codec detected on the input.
     * @param[in] contentType           The content type (e.g., STREAM, CLIP, TTS).
     */
    void onInputCodecChanged(in int audioMixerInputIndex, in Codec codec, in ContentType contentType);

    /**
     * @brief     Called when a runtime error occurs on the mixer instance.
     * @param[in] errorCode  An implementation-defined or HAL-standard error code.
     * @param[in] message    Human-readable error message, may be empty.
     */
    void onError(in int errorCode, in String message);

    /**
     * @brief     Called when the mixer state changes (e.g., STARTED, STOPPED, FLUSHED).
     * @param[in] oldState  The previous state.
     * @param[in] newState  The new state.
     */
    void onStateChanged(in int oldState, in int newState);

    // Add more events as needed, e.g. onResourceAvailable(), onEndOfStream(), etc.
}

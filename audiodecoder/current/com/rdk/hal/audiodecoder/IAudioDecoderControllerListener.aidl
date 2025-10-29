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
package com.rdk.hal.audiodecoder;
import com.rdk.hal.audiodecoder.FrameMetadata;

/**
 *  @brief     Callbacks listener interface from audio decoder controller.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
oneway interface IAudioDecoderControllerListener {
    /**
    * Called when an audio frame has been decoded or when frame metadata needs notification.
    *
    * In tunneled mode, audio data is consumed by the vendor layer, so no PCM buffer is returned.
    *
    * Otherwise, {@code frameBufferHandle} is a valid handle to a decoded PCM buffer,
    * and {@code metadata} is non-null for the first frame after {@code State::START} or {@code State::FLUSHING},
    * or whenever stream metadata changes. Metadata may be null if unchanged since the last callback.
    *
    * @param[in] nsPresentationTime  The presentation timestamp in nanoseconds.
    * @param[in] frameBufferHandle   Handle to the decoded audio frame buffer, or -1 in tunneled mode.
    * @param[in] metadata            FrameMetadata for the audio frame, or null in tunneled mode or if unchanged.
    *
    * @see IAudioDecoderController.decodeBuffer()
    */
    void onFrameOutput(in long nsPresentationTime, in long frameBufferHandle, in @nullable FrameMetadata metadata);
}

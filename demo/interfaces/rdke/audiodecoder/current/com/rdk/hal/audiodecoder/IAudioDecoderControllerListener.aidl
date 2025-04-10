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
	 * Callback when an audio frame has been decoded and/or the frame metadata needs to be notified.
     * 
     * The frame buffer handle can be -1 to indicate no decoded PCM audio is returned because audio is being
     * tunnelled inside the vendor layer.
     * 
     * The metadata must be non-null on the first frame after start() or flush() call or
     * when the metadata changes in the stream. 
     * It can only be null if the contents have not changed since the last callback.
     *
     * @param[in] nsPresentationTime	The presentation time
     * @param[in] frameBufferHandle		Handle to audio frame buffer.
     * @param[in] metadata				A FrameMetadata parcelable of metadata related to the audio frame.
     * 
     * @see IAudioDecoderController.decodeBuffer()
     */
    void onFrameOutput(in long nsPresentationTime, in long frameBufferHandle, in @nullable FrameMetadata metadata);
}

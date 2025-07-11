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
import com.rdk.hal.audiodecoder.ErrorCode;
import com.rdk.hal.audiodecoder.State;

/** 
 *  @brief     Events callbacks listener interface from audio decoder.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
oneway interface IAudioDecoderEventListener {

    /**
	 * Callback when the decoder has raised an error.
     *
     * @param[in] errorCode 		    An ErrorCode enum value.
     * @param[in] vendorErrorCode  	    A vendor specific error code.
     */
    void onDecodeError(in ErrorCode errorCode, in int vendorErrorCode);
 
    /**
	 * Callback when the decoder has transitioned to a new state.
     *
     * @param[in] oldState	            The state that the decoder has transitioned from.
     * @param[in] newState              The new state that the decoder has transitioned to.
     * 
     * @see getState()
     */
    void onStateChanged(in State oldState, in State newState);
 }
 
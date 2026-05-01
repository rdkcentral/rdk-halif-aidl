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

/**
 * @brief     Audio Decoder States
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 */

@VintfStability
@Backing(type="int")
enum State {
    UNKNOWN   = 0, ///< The audio decoder HAL is in an unknown or uninitialized state.
    CLOSED    = 1, ///< The service connection is established but decoder not yet configured.
    OPENING   = 2, ///< Decoder is loading resources and initializing internal structures.
    READY     = 3, ///< Decoder is configured and ready to start decoding but idle.
    STARTING  = 4, ///< Decoder is transitioning from READY to DECODING; priming buffers.
    STARTED   = 5, ///< Decoder is actively decoding audio frames.
    FLUSHING  = 6, ///< Decoder is flushing pending input/output buffers; after flushing, returns to DECODING or READY.
    STOPPING  = 7, ///< Decoder is stopping and flushing; will revert to READY after complete.
    CLOSING   = 8  ///< Decoder is releasing resources and transitioning to CLOSED.
}

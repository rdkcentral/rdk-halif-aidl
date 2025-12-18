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
import com.rdk.hal.audiodecoder.IAudioDecoder;
 
/** 
 *  @brief     Audio Decoder Manager HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 */

@VintfStability
interface IAudioDecoderManager
{

    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "audiodecodermanager";


    /**
	 * Get all audio decoder resource IDs.
     * 
     * The list of audio decoders is static in the system and does not change
     * between calls.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns IAudioDecoder.Id[]
     */
    IAudioDecoder.Id[] getAudioDecoderIds();

    /**
	 * Gets an audio decoder resource index interface.
     *
     * @param[in] decoderResourceId     The ID of the audio decoder resource.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns IAudioDecoder which can be null if the resource index is invalid.
     */
    @nullable IAudioDecoder getAudioDecoder(in IAudioDecoder.Id decoderResourceId);
}

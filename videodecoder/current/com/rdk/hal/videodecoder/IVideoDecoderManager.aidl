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
package com.rdk.hal.videodecoder;
import com.rdk.hal.videodecoder.OperationalMode;
import com.rdk.hal.videodecoder.IVideoDecoder;

/** 
 *  @brief     Video Decoder Manager HAL interface.
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
interface IVideoDecoderManager
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "VideoDecoderManager";

    /**
	 * Gets the platform list of Video Decoder IDs.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns IVideoDecoder.Id[]
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IVideoDecoderManager}} for exception handling behavior).
     */
	IVideoDecoder.Id[] getVideoDecoderIds();
 
    /**
	 * Gets the operational modes supported by the video decoders on the platform.
     * 
     * The platform must support either tunnelled or non-tunnelled.  Both are not required to be supported.
     * Each video decoder resource must share the same operational mode(s) as all other video decoder resources.
     * Graphics texture support is optional.
     * 
     * This function can be called at any time and is not dependant on any Video Decoder state.
     * The returned value is not allowed to change between calls.
     *
     * @returns OperationalMode[] one or more OperationalMode enum values.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IVideoDecoderManager}} for exception handling behavior).
     * 
     * @see enum OperationalMode
     */
    OperationalMode[] getSupportedOperationalModes();

    /**
	 * Gets a Video Decoder interface.
     *
     * @param[in] videoDecoderId	The ID of the video decoder.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns IVideoDecoder or null if the ID is invalid.
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IVideoDecoderManager}} for exception handling behavior).
     */
    @nullable IVideoDecoder getVideoDecoder(in IVideoDecoder.Id videoDecoderId);

}

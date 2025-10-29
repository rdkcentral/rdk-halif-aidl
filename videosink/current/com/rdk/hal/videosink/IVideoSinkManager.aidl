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
import com.rdk.hal.videosink.IVideoSink;

/**
 *  @brief     Video Sink Manager HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
interface IVideoSinkManager
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "VideoSinkManager";

    /**
     * Gets the list of platform Video Sink IDs.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     *
     * @returns IVideoSink.Id[]
     */
    IVideoSink.Id[] getVideoSinkIds();

    /**
	 * Gets a Video Sink interface.
     *
     * @param[in] videoSinkId	    The ID of the Video Sink.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     *
     * @returns IVideoSink or null if the ID is invalid.
     */
    @nullable IVideoSink getVideoSink(in IVideoSink.Id videoSinkId);
}

/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
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
package com.rdk.hal.videocapture;
import com.rdk.hal.videocapture.IVideoCapture;
import com.rdk.hal.videocapture.IVideoCaptureEventListener;

/**
 *  @brief     Video Capture Manager HAL interface.
 *  @author    Gerald Weatherup
 *
 *  The entry point to the capture module. A client asks the manager which
 *  capture resources the platform has, and takes an `IVideoCapture` for the one it
 *  wants. A capture resource is addressed by its own ID; it is not reached
 *  through, or identified by, any other module's resource.
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 */

@VintfStability
interface IVideoCaptureManager
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "VideoCaptureManager";

    /**
     * Gets the platform list of capture resource IDs.
     *
     * A platform that offers no capture returns an empty array.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns IVideoCapture.Id[]
     */
    IVideoCapture.Id[] getVideoCaptureIds();

    /**
     * Gets a capture interface.
     *
     * @param[in] captureId              The ID of the capture resource.
     * @param[in] captureEventListener   Listener object for capture resource events.
     *
     * @returns IVideoCapture or null if the ID is not a capture resource on this platform.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     *
     * @see getVideoCaptureIds()
     */
    @nullable IVideoCapture getVideoCapture(in IVideoCapture.Id captureId, in IVideoCaptureEventListener captureEventListener);
}

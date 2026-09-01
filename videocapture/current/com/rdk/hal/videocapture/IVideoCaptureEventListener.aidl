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

import com.rdk.hal.videocapture.ErrorCode;
import com.rdk.hal.videocapture.State;

/**
 *  @brief     Event callbacks listener interface from a capture resource.
 *  @author    Peter Stieglitz
 *  @author    Gerald Weatherup
 */

@VintfStability
oneway interface IVideoCaptureEventListener
{
    /**
     * @brief     Called when the capture resource has raised an error that is not tied to a
     *            single frame.
     *
     * Examples are video memory exhaustion mid-session and an IOMMU fault.
     *
     * @param[in] errorCode         A ErrorCode enum value.
     * @param[in] vendorErrorCode   A vendor specific error code.
     */
    void onSystemError(in ErrorCode errorCode, in int vendorErrorCode);

    /**
     * @brief     Called when the bound video sink went away - closed, or
     *            otherwise no longer able to deliver frames.
     *
     * The session is implicitly stopped and the capture resource transitions to `READY`.
     * Binding a sink again with `IVideoCapture.open()` makes the session startable.
     */
    void onSourceLost();

    /**
     * @brief     Called when the capture resource has transitioned to a new state.
     *
     * @param[in] oldState          The state that the capture resource has transitioned from.
     * @param[in] newState          The new state that the capture resource has transitioned to.
     */
    void onStateChanged(in State oldState, in State newState);
}

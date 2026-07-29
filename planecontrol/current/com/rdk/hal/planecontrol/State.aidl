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
package com.rdk.hal.planecontrol;

/**
 *  @brief     Lifecycle state of a planecontrol resource instance.
 *
 *  Applies to the capture resources reached through `IPlaneControl.getCapture()`.
 *  Plane resources themselves are stateless and are not described by this enum.
 *
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type="int")
enum State {

    /** Initial / unknown state. */
    UNKNOWN = 0,

    /** Resource is closed; no open() call has succeeded yet. */
    CLOSED = 1,

    /** Resource is in the process of opening. */
    OPENING = 2,

    /** Resource is open and ready to be configured / started. */
    READY = 3,

    /** Resource is transitioning from READY to STARTED. */
    STARTING = 4,

    /** Resource is actively running. */
    STARTED = 5,

    /** Resource is transitioning from STARTED back to READY. */
    STOPPING = 6,

    /** Resource is transitioning to CLOSED. */
    CLOSING = 7,
}

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
package com.rdk.hal.planecontrol.capture;

/**
 *  @brief     Lifecycle state of a planecontrol resource instance.
 *
 *  Applies to the capture resources reached through `IPlaneControl.getCapture()`.
 *  Plane resources themselves are stateless and are not described by this enum.
 *
 *  @author    Peter Stieglitz
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type="int")
enum State {

    /**
     * Not open. No controller is held for this capture resource.
     *
     * Zero, so a default-constructed value reads as closed - which is what a
     * resource nobody has opened is.
     */
    CLOSED = 0,

    /** Open and configurable. `setFormat()` is written here, before `start()`. */
    READY = 1,

    /**
     * `start()` has returned and the pool is not yet delivered.
     *
     * The session is not usable in this state: the addressing arrives at
     * `ICaptureControllerListener.onPoolReady()`, and reaching STARTED is what says
     * it has. This is the one transition with an end a client can observe, which is
     * what makes it a state rather than an interval nobody sees.
     */
    STARTING = 2,

    /** Running. The pool is delivered and frames can be acquired. */
    STARTED = 3,

    /**
     * `stop()` has returned and teardown is in progress.
     *
     * Buffers the client still holds Locked are reclaimed here. The resource reaches
     * READY when it is done, and can be started again.
     */
    STOPPING = 4,
}

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
package com.rdk.hal.compositeinput;

/**
 * @brief     HAL component states for a composite input port.
 * @details   State transitions are driven by open(), close() on ICompositeInputPort
 *            and start(), stop() on ICompositeInputController.
 * @author    Gerald Weatherup
 */
@VintfStability
@Backing(type="int")
enum State {

    /**
     * Initial state. The port is not open; no controller exists.
     * Entered on service connection or after a successful close().
     */
    CLOSED = 0,

    /**
     * Transitional state entered immediately after open() is called.
     * The HAL is allocating resources and initialising the port.
     */
    OPENING = 1,

    /**
     * The port is open and ready to be started.
     * open() completes here; close() may be called from this state.
     */
    READY = 2,

    /**
     * Transitional state entered immediately after start() is called.
     */
    STARTING = 3,

    /**
     * The port is active and presenting video.
     * stop() may be called from this state.
     */
    STARTED = 4,

    /**
     * Transitional state entered immediately after stop() is called.
     */
    STOPPING = 5,

    /**
     * Transitional state entered immediately after close() is called.
     */
    CLOSING = 6,
}

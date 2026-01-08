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
package com.rdk.hal.hdmiinput;
 
/** 
 * @brief     HAL component states.
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 */
 
@VintfStability
@Backing(type="int")
enum State {

    /**
     * Initial state entered when the service connection is established.
     */
    CLOSED = 0,

    /**
     * The HAL server component session is transitioning from closed to ready state.
     */
    OPENING = 1,

    /** 
     * The HAL server component session is open and ready to start. 
     */
    READY = 2,

    /**
     * The HAL server component session is in the process of starting.
     */
    STARTING = 3,

    /**
     * The opened HAL server component session has been started.
     */
    STARTED = 4,

    /**
     * The HAL server component session is in the process of stopping.
     */
    STOPPING = 5,

    /**
     * The HAL server component session is in the process of closing.
     */
    CLOSING = 6,
}

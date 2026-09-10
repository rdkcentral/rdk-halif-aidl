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
package com.rdk.hal.audiomixer;
 
/** 
 * @brief     HAL component states.
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 */

/**
 * @brief   HAL component connection states.
 *          Used in output port properties to describe physical or logical connection status.
 */
@VintfStability
@Backing(type="int")
enum ConnectionState {
    UNKNOWN = 0,      /**< Connection state cannot be determined (e.g., not supported by hardware) */
    DISCONNECTED = 1, /**< Explicitly disconnected */
    CONNECTED = 2,    /**< Explicitly connected */
    PENDING = 3,      /**< Pending connection (e.g., handshake in progress, BT pairing, etc.) */
    FAULT = 4         /**< Error/fault state (e.g., shorted, unsupported device, HDCP failure) */
}

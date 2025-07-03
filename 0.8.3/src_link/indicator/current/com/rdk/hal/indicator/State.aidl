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
package com.rdk.hal.indicator;

/** 
 *  @brief     Indicator states.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
@Backing(type="int")
enum State
{
    /** The curent state cannot be determined. Cannot be set. */
    ERROR_UNKNOWN = -1,

    /** Initial state at indicator service initialisation, typically set by the bootloader. Cannot be set. */
    BOOT = 0,

    /** Active power state. */
    ACTIVE = 1,

    /** Active standby and deep sleep states. */
    STANDBY = 2,

    /** All indicators off. Used for dark standby state. */
    OFF = 3,

    /** Connecting via WPS state. */
    WPS_CONNECTING = 4,

    /** WPS has connected state. */
    WPS_CONNECTED = 5,

    /** WPS error state. */
    WPS_ERROR = 6,

    /** Full system reset (aka FSR or factory reset) state. */
    FULL_SYSTEM_RESET = 7,

    /** USB upgrading state. */
    USB_UPGRADE = 8,

    /** Software download error state. */
    SOFTWARE_DOWNLOAD_ERROR = 9
}

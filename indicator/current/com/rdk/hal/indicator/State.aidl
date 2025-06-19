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
 * /**
 * * @brief Indicator states.
 * *
 * * Defines the various states for a system indicator.
 * * @author Luc Kennedy-Lamb
 * * @author Peter Stieglitz
 * * @author Douglas Adler
 * * @author Gerald Weatherup
 * */

@VintfStability
@Backing(type="int")
enum State
{
    ERROR_UNKNOWN = -1, /**< The current state cannot be determined. This state cannot be set. */
    BOOT = 0, /**< Initial state at indicator service initialization, typically set by the bootloader. This state cannot be set. */
    ACTIVE = 1, /**< Active power state. */
    STANDBY = 2, /**< Active standby. */
    OFF = 3, /**< All indicators are off. Used for dark standby state. */
    WPS_CONNECTING = 4, /**< Connecting via WPS state. */
    WPS_CONNECTED = 5, /**< WPS has connected state. */
    WPS_ERROR = 6, /**< WPS error state. */
    FULL_SYSTEM_RESET = 7, /**< Full system reset (also known as FSR or factory reset) state. */
    USB_UPGRADE = 8, /**< USB upgrading state. */
    SOFTWARE_DOWNLOAD_ERROR = 9, /**< Software download error state. */
    DEEP_SLEEP = 10, /**< Deep sleep state. */
    PSU_FAILURE = 11, /**< Power supply failure state. */
    WPS_SES_OVERLAP = 12, /**< WPS session overlap detected. */
    WIFI_ERROR = 13, /**< Wi-Fi error state. */
    IP_ACQUIRED = 14, /**< Device acquired an IP address. */
    NO_IP = 15, /**< Device did not get any IP address assigned. */
    RCU_COMMAND = 16 /**< RCU command received by the device. */
}
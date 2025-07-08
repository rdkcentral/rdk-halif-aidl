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
 * @brief Indicator states.
 *
 * Represents the persistent, mutually exclusive states that the system indicator can be in.
 * These states reflect the current condition of the device (e.g., booting, active, error)
 * and remain in effect until explicitly changed. The HAL implementation is expected to
 * reflect these states via hardware-controlled visual indicators (e.g., LEDs, panels).
 *
 * ### Key Characteristics:
 * - Each state describes a long-lived condition, not a short-lived event.
 * - Only one state should be active at a time; transitions must be explicitly managed.
 * - Transient signals like "blink on RCU press" are **not** indicator states and must be
 *   handled independently in vendor logic—they should not be represented in this enum.
 *
 * ### Platform-Specific Extensions:
 * Vendors may define additional persistent states by extending the enum starting from
 * `USER_DEFINED_BASE = 1000`. These must follow the same semantics (i.e., persistent state)
 * and be documented in the HAL Feature Profile (HFP) for discoverability and testability.
 *
 * @author Luc Kennedy-Lamb
 * @author Peter Stieglitz
 * @author Douglas Adler
 * @author Gerald Weatherup
 */
@VintfStability
@Backing(type="int")
enum State
{
    // General and boot-related states
    ERROR_UNKNOWN = -1, /**< The current state cannot be determined. This state cannot be set. */
    BOOT = 0,           /**< Initial state at indicator service initialization, typically set by the bootloader. This state cannot be set. */
    ACTIVE = 1,         /**< Normal operational state. */
    STANDBY = 2,        /**< System is in standby mode. */
    OFF = 3,            /**< All indicators are off. Used for dark standby or screen-off states. */
    DEEP_SLEEP = 4,     /**< Deep sleep state (lower power mode). */

    // WPS-related states
    WPS_CONNECTING = 100,  /**< Wi-Fi Protected Setup (WPS) in progress. */
    WPS_CONNECTED = 101,   /**< WPS connection successfully established. */
    WPS_ERROR = 102,       /**< WPS process failed (e.g., timeout, bad PIN). */
    WPS_SES_OVERLAP = 103, /**< WPS session overlap detected. */

    // Network and IP states
    WIFI_ERROR = 200,    /**< Wi-Fi hardware or configuration error. */
    IP_ACQUIRED = 201,   /**< Device successfully obtained an IP address. */
    NO_IP = 202,         /**< Device failed to obtain an IP address. */

    // System and maintenance states
    FULL_SYSTEM_RESET = 300,       /**< Factory reset or full system reset in progress. */
    USB_UPGRADE = 301,             /**< Firmware/software being upgraded via USB. */
    SOFTWARE_DOWNLOAD_ERROR = 302, /**< Download error during update process. */
    PSU_FAILURE = 303,             /**< Power supply unit failure or voltage anomaly. */

    /**
     * Reserved base value for platform- or product-specific persistent indicator states.
     * These must behave like the other states in this enum—persistent, mutually exclusive,
     * and clearly reflecting a system condition. They must not be used for transient events
     * such as remote control presses or button flashes.
     */
    USER_DEFINED_BASE = 1000
}

/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
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

/**
 * @file ActionType.aidl
 * @brief Enumerates actions a thermal policy may trigger.
 *
 * @details
 * Encodes critical or platform-level thermal actions without exposing raw thresholds.
 */
package com.rdk.hal.sensor.thermal;

@VintfStability
enum ActionType {
    /** @brief No action. */
    NONE = 0,

    // --- Power / critical paths ---
    /** @brief Entering deep sleep due to thermal policy. */
    ENTERING_DEEPSLEEP = 10,

    /** @brief Critical thermal breach leading to imminent reboot. */
    ENTERING_CRITICAL_REBOOT = 11,

    /** @brief Critical thermal breach leading to imminent full shutdown. */
    ENTERING_CRITICAL_SHUTDOWN = 12,

    // --- Cooling device hints (optional) ---
    /** @brief Cooling increased (e.g., fan speed up). */
    FAN_SPEED_INCREASED = 20,

    /** @brief Cooling returned to nominal. */
    FAN_SPEED_NORMAL = 21,

    // --- Recovery ---
    /** @brief System has thermally recovered to normal operating conditions. */
    THERMAL_RECOVERY_NORMAL = 30,

    // --- Vendor extension hook ---
    /** @brief Vendor-specific action; use with vendor fields in ActionEvent. */
    OTHER = 0x7FFF
}

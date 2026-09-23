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
 * @file State.aidl
 * @brief High-level current thermal state for quick health checks.
 *
 * @details
 * One state covers all thermal sensors: it is the worst state across
 * every sensor the platform declares. Thresholds named below are the
 * per-sensor HFP `triggers` values; the cooldown is the per-sensor HFP
 * `policy.recovery.min_cooldown_seconds`.
 *
 * Between a sensor's recovered and exceeded thresholds the state does
 * not change (hysteresis).
 */
package com.rdk.hal.sensor.thermal;

@VintfStability
enum State {
    /**
     * @brief Normal thermal conditions; no mitigation active.
     *
     * Entered at service start, unless a sensor is already at or above
     * its critical_temperature_exceeded_celsius (the service then starts in
     * CRITICAL_TEMPERATURE_EXCEEDED).
     * Entered from CRITICAL_TEMPERATURE_RECOVERED once every sensor has
     * stayed below its critical_temperature_recovered_celsius for its
     * cooldown period. No temperature threshold enters NORMAL directly.
     */
    NORMAL = 0,

    /**
     * @brief Temperature has exceeded a critical threshold.
     *  Platform will be in active mitigation if possible.
     *
     * Entered from NORMAL or CRITICAL_TEMPERATURE_RECOVERED when any sensor
     * reaches its critical_temperature_exceeded_celsius.
     */
    CRITICAL_TEMPERATURE_EXCEEDED = 1,

    /**
     * @brief Temperature has recovered from a critical event; cooldown in progress.
     *
     * Entered from CRITICAL_TEMPERATURE_EXCEEDED when every sensor is below
     * its critical_temperature_recovered_celsius. Moves to NORMAL when the
     * cooldown period completes, or back to CRITICAL_TEMPERATURE_EXCEEDED if
     * any sensor reaches its critical_temperature_exceeded_celsius first.
     */
    CRITICAL_TEMPERATURE_RECOVERED = 2,

    /**
     * @brief Shutdown is imminent due to critical thermal breach.
     *
     * Entered from any other state when any sensor reaches its
     * entering_critical_shutdown_celsius. Terminal: no transition leaves
     * this state.
     *
     * The HAL thermal policy service initiates the shutdown autonomously.
     * Clients receiving this event via IThermalEventListener should
     * perform only time-critical cleanup (flush caches, persist critical
     * state) and must not attempt to manage the reboot themselves.
     *
     * The thermal HAL records the shutdown reason so that on the next boot
     * it can be reported by the Boot Reason HAL via IBootReason.getBootCause() as
     * BootCause.THERMAL_RESET.
     */
    CRITICAL_SHUTDOWN_IMMINENT = 3
}

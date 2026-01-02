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
 */
package com.rdk.hal.sensor.thermal;

@VintfStability
enum State {
    /**
     * @brief Normal thermal conditions.
     */
    NORMAL = 0,

    /**
    * @brief Temperature has exceeded a critical threshold.
    *  Platform will be in active mitigation if possible.
    */
    CRITICAL_TEMPERATURE_EXCEEDED = 1,

    /**
    * @brief Temperature has recovered from a critical event.
    *  Platform will return to normal state
    */
    CRITICAL_TEMPERATURE_RECOVERED = 2,

    /**
     * @brief Shutdown is imminent due to critical thermal breach.
     */
    CRITICAL_SHUTDOWN_IMMINENT = 3
}

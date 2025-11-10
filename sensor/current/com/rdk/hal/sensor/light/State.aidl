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
 * @brief Lifecycle states for an ambient light sensor instance.
 *
 * @details
 * Typical transitions:
 * - STOPPED → STARTING → STARTED
 * - STARTED → STOPPING → STOPPED
 * - Any state → ERROR on fault
 */
package com.rdk.hal.sensor.light;

@VintfStability
enum State {
    /**
     * @brief Sensor is inactive; no sampling in progress.
     */
    STOPPED = 0,

    /**
     * @brief Sensor is initializing (power-up, configure, warm-up).
     */
    STARTING = 1,

    /**
     * @brief Sensor is actively sampling and ready for reads.
     */
    STARTED = 2,

    /**
     * @brief Sensor is stopping (tear-down in progress).
     */
    STOPPING = 3,

    /**
     * @brief A fault occurred (I/O error, probe failure, etc.). Recovery is implementation-defined.
     */
    ERROR = 4,
}

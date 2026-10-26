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
 * @brief Lifecycle states for a motion sensor instance.
 *
 * Typical transitions:
 *  - STOPPED → STARTING → STARTED
 *  - STARTED → STOPPING → STOPPED
 *  - Any state → ERROR on fault
 */
package com.rdk.hal.sensor.motion;

@VintfStability
enum State {
    /**
     * @brief Sensor is inactive; no monitoring in progress.
     */
    STOPPED = 0,

    /**
     * @brief Sensor is initializing (configure, warm-up, timing windows).
     */
    STARTING = 1,

    /**
     * @brief Sensor is actively monitoring for motion/no-motion.
     */
    STARTED = 2,

    /**
     * @brief Sensor is stopping (tear-down in progress).
     */
    STOPPING = 3,

    /**
     * @brief A fault occurred (I/O error, probe failure, etc.).
     */
    ERROR = 4,
}

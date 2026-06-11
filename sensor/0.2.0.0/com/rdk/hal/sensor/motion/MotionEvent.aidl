/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
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
 * @file MotionEvent.aidl
 * @brief Event payload delivered to motion sensor event listeners.
 */
package com.rdk.hal.sensor.motion;

import com.rdk.hal.sensor.motion.OperationalMode;

/**
 * @brief Event payload delivered to motion sensor event listeners.
 *
 * @details
 * Provides context for a motion-state change event:
 *  - The active operational mode whose condition was met
 *  - A monotonic timestamp for event ordering and correlation with
 *    other system events (thermal, deep sleep, etc.)
 *
 * Mirrors the shape of `ActionEvent` on the thermal sensor side so
 * downstream listeners that consume both sensors get a consistent
 * payload contract.
 */
@VintfStability
parcelable MotionEvent {
    /**
     * @brief The active mode whose condition was met (MOTION or NO_MOTION).
     */
    OperationalMode mode;

    /**
     * @brief Monotonic timestamp (ms) when the event occurred.
     * @details Use monotonic time for event ordering; not wall-clock time.
     *          Sourced from `CLOCK_MONOTONIC` (or equivalent) at the
     *          point the vendor layer detects the state change.
     */
    long timestampMonotonicMs;
}

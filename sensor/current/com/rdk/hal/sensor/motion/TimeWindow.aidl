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
 * @file TimeWindow.aidl
 * @brief Defines a daily time window when the motion sensor should be active.
 *
 * Time windows allow scheduling when the sensor actively monitors for motion.
 * Outside these windows, motion events are suppressed. Multiple windows can
 * be configured for different periods throughout the day (e.g., business hours
 * and evening hours).
 */
package com.rdk.hal.sensor.motion;

@VintfStability
parcelable TimeWindow {
    /**
     * @brief Start time in seconds since midnight (0-86399).
     *
     * Value must be in range [0, 86399]. For 24-hour monitoring,
     * set both startTimeOfDaySeconds and endTimeOfDaySeconds to 0.
     */
    int startTimeOfDaySeconds;

    /**
     * @brief End time in seconds since midnight (0-86399).
     *
     * Value must be in range [0, 86399]. If endTimeOfDaySeconds is
     * less than startTimeOfDaySeconds, the window wraps across midnight.
     * For 24-hour monitoring, set both values to 0.
     */
    int endTimeOfDaySeconds;
}

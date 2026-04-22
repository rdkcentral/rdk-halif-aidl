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
 * @file StartConfig.aidl
 * @brief Configuration parameters for starting a motion sensor session.
 *
 * Passed to {@link IMotionSensorController#start(StartConfig)} and
 * retrievable via {@link IMotionSensorController#getStartConfig()}.
 */
package com.rdk.hal.sensor.motion;

import com.rdk.hal.sensor.motion.OperationalMode;

@VintfStability
parcelable StartConfig {
    /**
     * @brief Operational mode — determines which event type the sensor reports.
     *
     * MOTION: fire onEvent when motion is detected.
     * NO_MOTION: fire onEvent after noMotionSeconds of inactivity.
     */
    OperationalMode operationalMode;

    /**
     * @brief Contiguous seconds without motion before a NO_MOTION event fires.
     *
     * Only meaningful when operationalMode is NO_MOTION. Use 0 to disable.
     */
    int noMotionSeconds;

    /**
     * @brief Delay in seconds before the sensor becomes active after start().
     *
     * Allows the caller to vacate the detection area before monitoring begins.
     * Use 0 for immediate activation.
     */
    int activeStartSeconds;

    /**
     * @brief Duration in seconds after which the sensor automatically stops.
     *
     * Use 0 for no automatic stop (sensor runs until stop() is called).
     */
    int activeStopSeconds;
}

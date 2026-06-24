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
 * @file OperationalMode.aidl
 * @brief Operation trigger mode for motion detection.
 *
 * When {@link IMotionSensorController#start(StartConfig)} is called,
 * the sensor fires events only for the mode specified in StartConfig.operationalMode.
 */
package com.rdk.hal.sensor.motion;

@VintfStability
enum OperationalMode {
    /**
     * @brief Report an event when motion is detected.
     */
    MOTION = 0,

    /**
     * @brief Report an event when a period of no motion is achieved.
     */
    NO_MOTION = 1,
}

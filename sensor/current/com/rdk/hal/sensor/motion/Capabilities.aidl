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
 * @file Capabilities.aidl
 * @brief Static properties describing a specific motion sensor instance.
 *
 * @details
 * Values returned by this parcelable are immutable across the lifetime of the
 * process and must not change between calls to
 * {@link com.rdk.hal.sensor.motion.IMotionSensor#getCapabilities()}.
 */
package com.rdk.hal.sensor.motion;

@VintfStability
parcelable Capabilities {
    /**
     * @brief Human-readable sensor name (e.g. "PIR-Front-1" or "Radar-SoC-0").
     */
    String sensorName;

    /**
     * @brief Minimum supported sensitivity (0 if sensitivity not supported).
     */
    int minSensitivity;

    /**
     * @brief Maximum supported sensitivity (0 if sensitivity not supported).
     */
    int maxSensitivity;

    /**
     * @brief Indicates whether the sensor can autonomously detect events during deep sleep.
     * @details If true, platform may support wake-from-motion without full SoC resume.
     */
    boolean supportsDeepSleepAutonomy;
}

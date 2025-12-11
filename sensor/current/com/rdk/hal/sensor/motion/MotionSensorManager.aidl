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
 * @file IMotionSensorManager.aidl
 * @brief Service entry point for discovering and accessing motion sensors.
 *
 * @details
 * The manager enumerates available sensors and returns interfaces to them.
 * Service implementations should register under {@link #serviceName}.
 */
package com.rdk.hal.sensor.motion;

import com.rdk.hal.sensor.motion.IMotionSensor;

interface IMotionSensorManager {
    /**
     * @brief Binder service registration name.
     * Vendors should publish the service with this name at system startup.
     */
    const @utf8InCpp String serviceName = "MotionSensorManager";

    /**
     * @brief Enumerate all platform-specific motion sensor identifiers.
     *
     * @return IMotionSensor.Id[] Array of available motion sensor IDs, or null if none.
     */
    @nullable IMotionSensor.Id[] getMotionSensorIds();

    /**
     * @brief Retrieve a motion sensor interface by ID.
     *
     * @param motionSensorId The identifier of the requested sensor.
     * @return IMotionSensor The sensor interface, or null if the ID is invalid.
     */
    @nullable IMotionSensor getMotionSensor(in IMotionSensor.Id motionSensorId);
}

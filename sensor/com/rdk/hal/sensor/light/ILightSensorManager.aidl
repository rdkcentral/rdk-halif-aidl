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
 * @file ILightSensorManager.aidl
 * @brief Service entry point for discovering and accessing light sensors.
 *
 * @details
 * The manager enumerates available sensors and returns interfaces to them.
 * Service implementations should register under {@link #serviceName}.
 */

package com.rdk.hal.sensor.light;

import com.rdk.hal.sensor.light.ILightSensor;

interface ILightSensorManager {
    /**
     * @brief Binder service registration name.
     * Vendors should publish the service with this name at system startup.
     */
    const @utf8InCpp String serviceName = "LightSensorManager";

    /**
     * @brief Enumerate all platform-specific light sensor identifiers.
     * @return ILightSensor.Id[] Array of available light sensor IDs.
     */
    ILightSensor.Id[] getLightSensorIds();

    /**
     * @brief Retrieve a light sensor interface by ID.
     * @param lightSensorId The identifier of the requested sensor.
     * @return ILightSensor The sensor interface, or null if the ID is invalid.
     */
    @nullable ILightSensor getLightSensor(in ILightSensor.Id lightSensorId);
}

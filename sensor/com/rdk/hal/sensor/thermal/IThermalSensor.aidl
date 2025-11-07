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
 * @file IThermalSensor.aidl
 * @brief Thermal policy service interface (singleton).
 *
 * @details
 * Exposes high-level policy decisions via events and a summarized state query.
 * Does not expose raw thresholds to clients.
 */
package com.rdk.hal.sensor.thermal;

import com.rdk.hal.sensor.thermal.IThermalEventListener;
import com.rdk.hal.sensor.thermal.State;
import com.rdk.hal.sensor.thermal.TemperatureReading;

interface IThermalSensor {
    /** @brief Binder service registration name. */
    const @utf8InCpp String serviceName = "ThermalSensor";

    /**
     * @brief Register for event-driven thermal actions.
     * @param listener Listener to receive thermal action events.
     * @retval true Listener registered.
     * @retval false Listener already registered.
     */
    boolean registerEventListener(in IThermalEventListener listener);

    /**
     * @brief Unregister a previously registered listener.
     * @param listener Listener to remove.
     * @retval true Listener unregistered.
     * @retval false Listener not found.
     */
    boolean unregisterEventListener(in IThermalEventListener listener);

    /**
     * @brief Query the current high-level thermal state.
     * @return State Current thermal state.
     */
    State getCurrentThermalState();

    /**
     * @brief Optional temperature telemetry snapshot.
     * @details Implementations may return an empty array if unsupported.
     * @return TemperatureReading[] Zero or more temperature readings.
     */
    TemperatureReading[] getCurrentTemperatures();
}

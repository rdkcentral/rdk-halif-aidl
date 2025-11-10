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
 * @file ILightSensor.aidl
 * @brief Instance interface for an ambient light sensor (ALS).
 *
 * @details
 * A single ILightSensor corresponds to one physical ALS device or one logical
 * channel on a multi-channel device. Implementations must ensure that
 * {@link #getLuxLevel()} supports a sampling cadence compatible with Dolby Vision IQ
 * use cases (i.e., at least 6 Hz when polled in a loop).
 */
package com.rdk.hal.sensor.light;

import com.rdk.hal.sensor.light.ILightSensor.State;
import com.rdk.hal.sensor.light.ILightSensor.Capabilities;

interface ILightSensor {

    /**
     * @brief Light sensor resource identifier type.
     */
    @VintfStability parcelable Id {
        /**
         * @brief Undefined/invalid ID value.
         */
        const int UNDEFINED = -1;

        /**
         * @brief The concrete resource identifier value.
         */
        int value;
    }

    /**
     * @brief Returns immutable capabilities for this sensor.
     * @return Capabilities describing this sensor.
     */
    Capabilities getCapabilities();

    /**
     * @brief Start data acquisition for this sensor.
     * @details On success, the state transitions STOPPED → STARTING → STARTED.
     *          If initialization fails, the state becomes ERROR.
     * @retval true Sensor successfully started (or already STARTED).
     * @retval false Sensor could not be started (e.g. invalid hw state).
     */
    boolean start();

    /**
     * @brief Stop data acquisition for this sensor.
     * @details On success, the state transitions STARTED → STOPPING → STOPPED.
     * @retval true Sensor successfully stopped (or already STOPPED).
     * @retval false Sensor could not be stopped.
     */
    boolean stop();

    /**
     * @brief Get the current lifecycle state of the sensor.
     * @return State Current state (e.g. STARTED, STOPPED, ERROR).
     */
    State getState();

    /**
     * @brief Get the current illuminance level in lux.
     * @details Implementations must support at least 6 Hz effective read cadence
     *          to satisfy Dolby Vision IQ responsiveness requirements.
     * @return int Current illuminance (lux).
     * @exception binder::Status EX_ILLEGAL_STATE if the state is not STARTED.
     */
    int getLuxLevel();

    /**
     * @brief Get the current raw sensor code (device-specific units).
     * @return int Current raw code.
     * @exception binder::Status EX_ILLEGAL_STATE if the state is not STARTED.
     */
    int getRawLevel();
}

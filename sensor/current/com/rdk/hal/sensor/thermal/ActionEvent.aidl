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
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.rdk.hal.sensor.thermal;

import com.rdk.hal.sensor.thermal.State;
import com.rdk.hal.sensor.thermal.TemperatureReading;

/**
 * @file ActionEvent.aidl
 * @brief Event payload delivered to thermal event listeners.
 *
 * @details
 * Provides context for a thermal state change event, including:
 *  - New thermal state
 *  - Monotonic event timestamp
 *  - Temperature reading with vendor metadata
 */
@VintfStability
parcelable ActionEvent {
    /** @brief The new thermal state. */
    State state;

    /**
     * @brief Monotonic timestamp (ms) when the state change occurred.
     * @details Use monotonic time for event ordering; not wall-clock time.
     */
    long timestampMonotonicMs;

    /**
     * @brief Temperature reading captured at the time of the state change.
     * @details May be null if not associated with a specific sensor.
     */
    @nullable TemperatureReading temperatureReading;
}

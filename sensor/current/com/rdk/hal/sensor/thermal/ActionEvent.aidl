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
package com.rdk.hal.sensor.thermal;

import com.rdk.hal.sensor.thermal.ActionType;

/**
 * @file ActionEvent.aidl
 * @brief Event payload delivered to thermal event listeners.
 *
 * @details
 * Includes the action type, timestamp, and optional origin metadata.
 */
@VintfStability
parcelable ActionEvent {
    /** @brief The action the policy has decided to take. */
    ActionType action;

    /**
     * @brief Monotonic timestamp (ms) when the action was decided.
     */
    long timestampMonotonicMs;

    /**
     * @brief Identifier of the sensor or domain that triggered the action.
     * @details May be null or empty if the event represents an aggregate/system-level condition.
     * Example: "soc_die", "board", "psu", or "composite".
     */
    String originSensorId;

    /** @brief Optional vendor reason/diagnostic code. */
    int vendorCode;

    /** @brief Optional vendor info string (domain, details, etc.). */
    String vendorInfo;
}

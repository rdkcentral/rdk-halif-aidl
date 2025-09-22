/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
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
package com.rdk.hal.broadcast.frontend;

/**
 *  @brief     Available guard intervals
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler 
 */

/**
 * Note that this enum is shared across all frontend types and thus includes values that are only
 * usable on some of them. You should always request and consult the list of supported guard
 * intervals from the frontend before using any of them.
 */
@VintfStability
enum RollOff {
    /** Clean value when default initialized */
    UNDEFINED = 0,
    /** @brief Auto-selected */
    AUTO,
    /** @brief Roll off value 0.35 used by DVB-S2 and DVB-S2X */
    ROLL_OFF_0_35,
    /** @brief Roll off value 0.25 used by DVB-S2 and DVB-S2X */
    ROLL_OFF_0_25,
    /** @brief Roll off value 0.20 used by DVB-S2 and DVB-S2X */
    ROLL_OFF_0_20,
    /** @brief Roll off value 0.15 used by DVB-S2X */
    ROLL_OFF_0_15,
    /** @brief Roll off value 0.10 used by DVB-S2X */
    ROLL_OFF_0_10,
    /** @brief Roll off value 0.05 used by DVB-S2X */
    ROLL_OFF_0_05,
}

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
package com.rdk.hal.boot;

/** 
 *  @brief     Boot reasons.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
@Backing(type="int")
enum BootReason
{
    /** Boot Reason is unknown. */
    ERROR_UNKNOWN = -1,

    /** Boot Reason is due to Watchdog Timer. */
    WATCHDOG = 0,

    /** Boot Reason is due to software Reset. */
    SOFTWARE_RESET = 1,

    /** Boot Reason is due to Thermal Reset. */
    THERMAL_RESET = 2,

    /** Boot Reason is due to Warm Temperature Reset. */
    WARM_RESET = 3,

    /** Boot Reason is due to Cold Boot. */
    COLD_BOOT = 4,

    /** Boot Reason is due to Suspend to RAM Authentication Failure. */
    STR_AUTH_FAILURE = 5,
}

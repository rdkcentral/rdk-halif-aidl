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
package com.rdk.hal.farfieldvoice;

/**
 *  @brief     Far Field Voice power mode definitions.
 *  @author    Philip Stick
 *  @author    Gary Skrabutenas
 */

@VintfStability
@Backing(type="int")

enum PowerMode
{
   /**
     * Power mode never set or power mode change in progress (not ready).
     */
	NONE = 0,

    /**
     * Full Power.
     */
	FULL_POWER = 1,

    /**
     * Standby.
     */
	STANDBY = 2,

    /**
     * Deep Sleep.
     */
	DEEP_SLEEP = 3,
}

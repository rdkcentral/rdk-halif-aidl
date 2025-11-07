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
* @file Location.aidl
* @brief Enumerates physical placement/orientation of an ambient light sensor.
*/

package com.rdk.hal.sensor.light;

@VintfStability
enum Location {
    /**
    * @brief The sensor faces outward toward the user/environment (e.g. front panel).
    */
    FRONT = 0,

    /**
    * @brief The sensor is mounted on the rear/inside (e.g. for chassis or wall-reflected light).
    */
    BACK = 1,
}
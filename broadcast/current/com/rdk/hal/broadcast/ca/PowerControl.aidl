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
package com.rdk.hal.broadcast.ca;

/**
 *  @brief  Describes how power line control is managed for a CA slot.
 */
@VintfStability
@Backing(type="int")
enum PowerControl {
    /** @brief Clean value when default initialized */
    UNDEFINED = 0,
    /** @brief Power line can not be controlled */
    NONE = 1,
    /** @brief The power line is shared with other components */
    SHARED = 2,
    /** @brief The power line is dedicated to this slot */
    DEDICATED = 3,
}
